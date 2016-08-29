# Common include 
INCLUDE_DIRECTORIES(../)

# Common library
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib)

ADD_EXECUTABLE( example main.cpp )

TARGET_LINK_LIBRARIES( example nario )

# 指定二进制文件输出路径
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)