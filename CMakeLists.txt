cmake_minimum_required(VERSION 3.14)

# 检查父级CMakeLists.txt是否设置了输出路径，如果没有直接报错
if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    message(FATAL_ERROR "Please set CMAKE_RUNTIME_OUTPUT_DIRECTORY in parent CMakeLists.txt")
endif()

# 设置输出dll的目录
set(MysqlConn_LIB_DIRS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# 导出变量给上层CMakeLists.txt使用
set(MysqlConn_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/MysqlConn/include PARENT_SCOPE)
set(MysqlConn_LIB_DIRS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} PARENT_SCOPE)

# 特别设置：MSVC库输出目录
# 1. 保证后文拷贝的文件在正确的dll输出目录
# 2. 保证上层CMakeLists.txt能够正确找到dll
if(${CMAKE_GENERATOR} MATCHES "Visual Studio*")
    if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE "Debug")
    endif()
    # 修改MysqlConn_LIB_DIRS至bin/Debug或bin/Release
    set(MysqlConn_LIB_DIRS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE})
    set(MysqlConn_LIB_DIRS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE} PARENT_SCOPE)
endif()

# Windows: dll导出静态库符号表
if(WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

# 创建dll
add_library(MysqlConn SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/MysqlConn/src/MysqlConfig.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MysqlConn/src/MysqlConn.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MysqlConn/src/MysqlConnPool.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MysqlConn/src/MysqlOP.cpp
)

# 查找头文件
target_include_directories(MysqlConn PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Singleton
    ${CMAKE_CURRENT_SOURCE_DIR}/Mysql/include
    ${CMAKE_CURRENT_SOURCE_DIR}/MysqlConn/include
    ${CMAKE_CURRENT_SOURCE_DIR}/nlohmann-json/include
)

# 导入mysql库路径
target_link_directories(MysqlConn PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Mysql/lib
)

# 导入mysql库
target_link_libraries(MysqlConn 
    PRIVATE libmysql.dll
)

# 拷贝必要文件
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Mysql/lib/libmysql.dll DESTINATION ${MysqlConn_LIB_DIRS})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/MysqlConn/dbConfig.json DESTINATION ${MysqlConn_LIB_DIRS})


# 使用示例：
# add_subdirectory(MysqlConn)
# target_include_directories(target PRIVATE ${MysqlConn_INCLUDE_DIRS})
# target_link_directories(target PRIVATE ${MysqlConn_LIB_DIRS})
# target_link_libraries(target MysqlConn)