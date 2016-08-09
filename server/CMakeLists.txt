# CMake最低要求版
cmake_minimum_required(VERSION 2.8)

# Release
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

# 支持c++11
add_compile_options(-std=c++11)

# 定义项目(工程)名称,  
# 同时定义了以下默认变量:  
# PROJECT_SOURCE_DIR 或 HELLO_SOURCE_DIR, 代指CMake开始构建的根目录(通常是项目根目录)  
# PROJECT_BINARY_DIR 或 HELLO_BINARY_DIR, 代指CMake的编译目录(即执行cmake命令的目录)  
PROJECT(server)  

# 添加参与编译的子目录
add_subdirectory(servers/chat)
add_subdirectory(include/aprpc)
add_subdirectory(client)