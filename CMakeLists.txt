cmake_minimum_required(VERSION 3.6)

find_package(MPI REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MAKE_PROGRAM "C:\\Program Files\\CMake\\bin\\mingw32-make.exe")
set(CMAKE_C_COMPILER "C:\\MinGW\\bin\\gcc.exe")
set(CMAKE_CXX_COMPILER "C:\\MinGW\\bin\\g++.exe")
#set(CMAKE_C_COMPILER "C:\\Program Files (x86)\\OpenMPI_v1.5.5-x64\\bin\\mpicc.exe")
#set(CMAKE_CXX_COMPILER "C:\\Program Files (x86)\\OpenMPI_v1.5.5-x64\\bin\\mpicxx.exe")

include_directories("C:\\Program Files (x86)\\OpenMPI_v1.5.5-x64\\include\\")
link_directories("C:\\Program Files (x86)\\OpenMPI_v1.5.5-x64\\lib\\")
#link_directories("C:\\MinGW\\lib")

file(GLOB gravediggers_src "src/*/*.cpp")

add_executable(Gravediggers src/gravediggers.cpp ${gravediggers_src})