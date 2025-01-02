# MysqlConn
封装Mysql C API为C++ Class

## 使用本项目

```shell
git clone https://github.com/life-studied/MysqlConn.git
cd MysqlConn
git submodule update --init --recursive
cmake -S . -B build
cmake --build build
```

## 使用示例

### cmake

```cmake
cmake_minimum_required(VERSION 3.20)

project(HelloWorld)

# 设置输出路径：子目录会根据 CMAKE_RUNTIME_OUTPUT_DIRECTORY 保证dll与exe在同一目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# 17是当前唯一版本
set(CMAKE_CXX_STANDARD 17)

add_executable(HelloWorld main.cpp)

# 添加如下命令
add_subdirectory(MysqlConn)
target_include_directories(HelloWorld PRIVATE ${MysqlConn_INCLUDE_DIRS})
target_link_directories(HelloWorld PRIVATE ${MysqlConn_LIB_DIRS})
target_link_libraries(HelloWorld MysqlConn)
```

### 配置dbConfig.json文件

```json
{
  "ip": "127.0.0.1",
  "port": 3306,
  "user": "root",
  "password": "root",
  "dbName": "testdb",
  "minSize": 100,
  "maxSize": 1024,
  "maxIdleTime": 5000,
  "timeOut": 1000
}
```

### OP类

```C++
#include "MysqlOP.h"
#include <iostream>

int main(int argc, char *argv[])
{
    using namespace DBConn::MysqlOP;
    std::cout << "Hello, World!" << std::endl;
	auto table = MysqlOP::query("select * from activity").execute();
    for(auto& title : table.titles)
    {
        std::cout << title << " ";
    }
    std::cout << std::endl;
    for(auto& row : table.content)
    {
        for(auto& cell : row)
        {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
```

