# 自动追踪源文件变化（CONFIGURE_DEPENDS是CMake 3.20+特性）
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    "src/*.cpp"
    "src/*.h"
)

# 创建动态库目标（SHARED表示生成DLL）
add_library(VtkApp SHARED ${SRC_FILES})

# 链接VTK和Qt库（使用现代CMake目标模式）
target_link_libraries(VtkApp PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    VTK::GUISupportQt
    VTK::RenderingOpenGL2
)

# 设置DLL导出宏（Windows下需要）
if(WIN32)
    target_compile_definitions(VtkApp PRIVATE "VTKAPP_EXPORTS")
endif()

# 自动初始化VTK模块
vtk_module_autoinit(
    TARGETS VtkApp
    MODULES ${VTK_LIBRARIES}
)

# 包含头文件目录
target_include_directories(VtkApp PRIVATE ${VTK_INCLUDE_DIRS})