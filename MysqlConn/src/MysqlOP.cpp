#include "MysqlOP.h"
#include "MysqlConnPool.h"
#include <iostream>

DBConn::MysqlOP::MysqlOP DBConn::MysqlOP::MysqlOP::query(const string& _sql)
{
	return MysqlOP(_sql);
}

DBConn::Table DBConn::MysqlOP::MysqlOP::execute()
{
	Table table;
	auto& instance = SinglePool::getInstance();
	auto conn = instance.getConntion();
	conn->query(sql);
	auto colNum = conn->colNum();
	for (int i = 0; i < colNum; i++)
		table.titles.push_back(conn->title(i));
	while (conn->next())
	{
		vector<string> row;
		for (int i = 0; i < colNum; i++)
			row.push_back(conn->value(i));
		table.content.push_back(row);
	}
	return table;
}

void DBConn::MysqlOP::MysqlOP::print()
{
	std::cout << sql << std::endl;
}
