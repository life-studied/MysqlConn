# MysqlConn
封装Mysql C API为C++ Class

## 使用示例

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

### 连接池

```C++
	auto& instance = SinglePool::getInstance();
    auto conn = instance.getConntion();
    conn->query(sql);
    auto colNum = conn->colNum();
    for (int i = 0; i < colNum; i++)
        std::cout << conn->title(i) << '\t';
    while (conn->next())
    {
        std::cout << conn->value(0) << '\n';
    }
```

### OP类

```C++
	using namespace DBConn::MysqlOP;
	auto table = MysqlOP::query("select * from activity");
	for (const auto& i : table.titles)
		std::cout << i << '\t';
	std::cout << std::endl;
	for (const auto& row : table.content)
	{
		for (const auto& i : row)
			std::cout << i << '\t';
		std::cout << std::endl;
	}
	
	auto res = MysqlOP::countNumber("select count(*) number from activity");
	std::cout << res.name << '\n' << res.data << std::endl;
```

