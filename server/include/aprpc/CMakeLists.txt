# 指定库文件输出路径  
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)  

# 生成静态库  
add_library(aprpc STATIC aprpc.cpp)