cmake_minimum_required(VERSION 3.12)
project(rayturbo C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#add_subdirectory(libs) usage: #look in subdirectory for CMakeLists.txt to process

#set(RAYLIB_DIR "/home/kot/raylib/src" CACHE PATH "Raylib install directory here-->")
#message("Raylib directory: " ${RAYLIB_DIR})


#include_directories(${RAYLIB_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src)

file(GLOB SOURCE "src/*.cpp")

message("cmake working directory: " ${CMAKE_SOURCE_DIR})
link_directories(${CMAKE_SOURCE_DIR}/libs)

add_executable(rayturbo  ${SOURCE})
target_link_libraries(rayturbo PRIVATE raylib pthread ${CMAKE_DL_LIBS})
target_compile_definitions(rayturbo PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/") # Set the asset path macro to the absolute path on the dev machine







