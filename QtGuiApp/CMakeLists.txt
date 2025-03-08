cmake_minimum_required(VERSION 3.20)
project(QtGuiApp LANGUAGES CXX)

# 启用自动MOC（必须！）
set(CMAKE_AUTOMOC ON)

# 收集源文件
file(GLOB SRC_FILES CONFIGURE_DEPENDS
    "src/*.cpp"
    "src/*.h"
)

# 创建可执行文件
add_executable(QtGuiApp ${SRC_FILES})

# 包含目录
target_include_directories(QtGuiApp PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    # 添加VTK头文件路径
    ${VTK_INCLUDE_DIRS}
)

# 链接库
target_link_libraries(QtGuiApp PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::OpenGLWidgets  # QVTKOpenGLNativeWidget依赖此组件
    VTK::GUISupportQt
    VTK::RenderingOpenGL2  # 必须添加！
    VTK::InteractionStyle
    VTK::CommonCore
)