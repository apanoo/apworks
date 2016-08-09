# 添加头文件的查找目录
include_directories(${PROJECT_SOURCE_DIR}/include/asio1.10.6)
include_directories(${PROJECT_SOURCE_DIR}/include/aprpc)

# 指定可执行文件的输出目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 编译可执行文件
add_executable(client client.cpp)

# 链接库
set( EXTRA_LIBS ${EXTRA_LIBS} aprpc )
target_link_libraries(client  ${EXTRA_LIBS})