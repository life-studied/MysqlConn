#include "MysqlOP.h"
#include "MysqlConn.h"
#include "MysqlConnPool.h"

#include <iostream>

#include <mysql.h>

DBConn::MysqlOP::MysqlOP DBConn::MysqlOP::MysqlOP::query(const string& _sql)
{
	return MysqlOP(_sql);
}

std::shared_ptr<DBConn::query_result> DBConn::MysqlOP::MysqlOP::execute()
{
	auto result = std::make_shared<query_result>();
	auto conn = SinglePool::getInstance().getConntion();

	if(!conn->query(sql, result->m_result))
	{
		return nullptr;
	}
	
	result->fetch();
	return result;
}

void DBConn::MysqlOP::MysqlOP::print()
{
	std::cout << sql << std::endl;
}

DBConn::query_result::~query_result()
{
	if (m_result)
	{
		mysql_free_result(m_result);
		m_result = nullptr;
	}
}

void DBConn::query_result::fetch()
{
	using std::vector;
	using std::string_view;

	if (!m_result) {
		return;
	}

	// 获取title
	auto col_num = mysql_num_fields(m_result);
	auto col = mysql_fetch_fields(m_result);
	for (auto i = 0; i < col_num; ++i)
		titles.emplace_back(col[i].name, col[i].name_length);

	// 获取content
	auto row = mysql_fetch_row(m_result);
	while (row) {
		vector<string_view> row_data;
		for (auto index = 0; index < col_num; ++index) {
			char* valStr = row[index];
			auto strLen = mysql_fetch_lengths(m_result)[index];     // value after \0 may be miss
			row_data.emplace_back(valStr, strLen);
		}
		content.emplace_back(std::move(row_data));
		row = mysql_fetch_row(m_result);
	}
}

void DBConn::query_result::print() const
{
	if (!m_result) {
		return;
	}

	using std::cout;
	for (const auto& i : titles)
		cout << i << '\t';
	cout << '\n';
	for (const auto& row : content)
	{
		for (const auto& i : row)
			std::cout << i << '\t';
		cout << '\n';
	}
	cout << '\n';
}

int DBConn::query_result::col_num() const
{
	return titles.size();
}

int DBConn::query_result::row_num() const
{
	return content.size();
}
