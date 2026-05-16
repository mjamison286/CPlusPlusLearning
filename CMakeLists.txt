cmake_minimum_required(VERSION 3.10.0)
project(CPlusPlus VERSION 0.1.0 LANGUAGES C CXX)

#set(CMAKE_VERBOSE_MAKEFILE ON)

include_directories(
    vendor/glfw/include
    vendor/glm
    source/include
    source/resources
)

add_subdirectory(vendor/glfw glfw)

#find_package(glfw3 REQUIRED)

#add_executable(FirstProgram source/FirstProgram.cpp source/Log.cpp source/QueryAndPrint.cpp source/Query.cpp source/Calc.cpp)

#add_executable(CQA CQA/Addiply.cpp)

add_executable(OpenGLApp 
    source/OpenGLApp.cpp 
    source/Renderer.cpp 
    source/glad.c 
    source/VertexBuffer.cpp 
    source/IndexBuffer.cpp 
    source/VertexArray.cpp 
    source/Shader.cpp
    source/Texture.cpp
)

target_link_libraries(OpenGLApp glfw)

#target_link_libraries(OpenGLApp GL glfw)

