include(GenerateExportHeader)
cmake_minimum_required (VERSION 2.6)
project (wglfw)
add_subdirectory(glfw)
include_directories(glfw/include)
add_definitions(-DGLFW_DLL)
add_library(wglfw SHARED wrapper.c)
target_link_libraries(wglfw glfw ${GLFW_LIBRARIES})
