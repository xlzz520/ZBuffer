#cmake版本
cmake_minimum_required(VERSION 3.16)

#项目名字
project(CG_ZBUFFER LANGUAGES CXX)

#c++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Suppress warnings of the deprecation of glut functions on macOS. 
if(APPLE)
    add_definitions(-Wno-deprecated-declarations) 
endif()

# Find the packages we need. 
find_package(OpenGL REQUIRED) 
find_package(GLUT REQUIRED)
find_package(OpenMP REQUIRED)

# Linux
# If not on macOS, we need glew. 
if(UNIX AND NOT APPLE)
    find_package(GLEW REQUIRED) 
endif()

# OPENGL_INCLUDE_DIR, GLUT_INCLUDE_DIR, OPENGL_LIBRARIES, and GLUT_LIBRARIES are CMake built-in variables defined when the packages are found.
set(INCLUDE_DIRS ${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR}  ${OPENMP_INCLUDE_DIR}) 
set(LIBRARIES ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${OPENMP_INCLUDE_DIR})
message(${INCLUDE_DIRS})
message(" ")
message(${LIBRARIES}})


# If not on macOS, add glew include directory and library path to lists.
if(UNIX AND NOT APPLE)
    list(APPEND INCLUDE_DIRS ${GLEW_INCLUDE_DIRS})
    list(APPEND LIBRARIES ${GLEW_LIBRARIES}) 
endif()

# Add the list of include paths to be used to search for include files.
include_directories(${INCLUDE_DIRS})


# 包含 Eigen, igl, spdlog 的头文件
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(/opt/homebrew/include/eigen3)
include_directories(/opt/homebrew/include)


# Search all the .cpp files in the directory where CMakeLists lies and set them to ${SOURCE_FILES}.
# Search all the .h files in the directory where CMakeLists lies and set them to ${INCLUDE_FILES}.

file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp) 
file(GLOB INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

add_executable(CG_ZBUFFER
    ${SOURCE_FILES} 
    ${INCLUDE_FILES}
)

# Link the executable to the libraries. 
target_link_libraries(CG_ZBUFFER ${LIBRARIES})