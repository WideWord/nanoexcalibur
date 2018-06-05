cmake_minimum_required(VERSION 3.2.0)

project(df)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
SET (CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -rpath .")

file(GLOB_RECURSE DDE_SOURCE source/*.cpp source/*.hpp source/*.c source/*.h)

include_directories(/usr/include)
include_directories(/usr/local/include)
include_directories(source/3rdparty)
link_directories(/usr/local/lib)

# OpenGL
find_package(OpenGL)
include_directories(${OPENGL_INCLUDE_DIRS})

# GLFW
find_package(GLFW)
include_directories(${GLFW_INCLUDE_DIR})

# GLM
find_package(GLM)
include_directories(${GLM_INCLUDE_DIRS})

add_executable(df ${DDE_SOURCE})
target_link_libraries(df ${OPENGL_LIBRARY} ${GLFW_LIBRARIES})
