cmake_minimum_required(VERSION 3.15)
project(Thaum1el_Chat)

set(CMAKE_CXX_STANDARD 17)

# set compiler
set(CMAKE_C_COMPILER "D:\\vscode\\mingw_gcc_13.2.0\\mingw64\\bin\\gcc.exe")
set(CMAKE_CXX_COMPILER "D:\\vscode\\mingw_gcc_13.2.0\\mingw64\\bin\\g++.exe")

# set makefile generator
set(CMAKE_GENERATOR "MinGW Makefiles")
set(CMAKE_MAKE_PROGRAM "D:\\vscode\\mingw_gcc_13.2.0\\mingw64\\bin\\make")

# don't generate clangd commands
set(CMAKE_EXPORT_COMPILE_COMMANDS OFF)

# enable debug function
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

# redirect the build output to a subdirectory of build
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)

# redirect the binary program to bin directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(include)

# test config
add_executable(config source/config.cpp test/config.cpp)
