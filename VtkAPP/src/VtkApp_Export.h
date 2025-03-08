// VtkApp_Export.h - 动态库导出宏定义
#pragma once

// Windows平台导出/导入宏
#ifdef _WIN32
  #ifdef VTKAPP_EXPORTS
    #define VTKAPP_API __declspec(dllexport)  // 编译DLL时导出
  #else
    #define VTKAPP_API __declspec(dllimport)  // 使用DLL时导入
  #endif
#else
  #define VTKAPP_API  // Linux/macOS不需要特殊声明
#endif

// VTK模块初始化宏（必须包含）
#include <vtkABI.h>