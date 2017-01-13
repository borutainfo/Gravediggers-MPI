project(Gravediggers)
cmake_minimum_required(VERSION 3.6)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MAKE_PROGRAM "C:\\Program Files\\CMake\\bin\\mingw32-make.exe")
set(CMAKE_C_COMPILER "C:\\MinGW\\bin\\gcc.exe")
set(CMAKE_CXX_COMPILER "C:\\MinGW\\bin\\g++.exe")

include_directories("C:\\Program Files (x86)\\MPICH2\\include\\")
link_directories("C:\\Program Files (x86)\\MPICH2\\lib\\")

file(GLOB gravediggers_src "src/*/*.cpp")
add_executable(${PROJECT_NAME} src/gravediggers.cpp ${gravediggers_src})

target_link_libraries(${PROJECT_NAME} mpi cxx)