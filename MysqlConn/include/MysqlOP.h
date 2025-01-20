#pragma once

#include <vector>
#include <string>
#include <type_traits>
#include <iostream>
#include <string_view>

struct MYSQL_RES;	// forward declaration

namespace DBConn
{
    using std::vector;
    using std::string;

	struct query_result {
		query_result() = default;
		
		~query_result();
		
		// 用于将MYSQL_RES*中的查询结果转为string_view，方便后续操作
		void fetch();

		void print() const;

		int col_num() const;

		int row_num() const;
		
		std::vector<std::string_view> titles;
		std::vector<std::vector<std::string_view>> content;
		MYSQL_RES* m_result = nullptr;
	};

	namespace MysqlOP
	{
		class MysqlOP
		{
		public:
			// query result is a table
			static MysqlOP query(const string& _sql);

			template <typename T>
			MysqlOP& arg(const T& data)
			{
				if (auto idx = sql.find('?');idx == std::string::npos)
					throw std::invalid_argument("no args need to parse");
				else
				{
					if constexpr (std::is_same_v<std::string, T>)
					{
						sql.replace(idx, 1, data);
					}
					else
					{
						using namespace std;
						sql.replace(idx, 1, to_string(data));
					}
				}

				return *this;
			}

			template <size_t size>
			MysqlOP& arg(const char(&data)[size])
			{
				if (auto idx = sql.find('?'); idx == std::string::npos)
					throw std::invalid_argument("no args need to parse");
				else
				{
					sql.replace(idx, 1, data);
				}
				return *this;
			}

			template <typename T, typename F>
			MysqlOP& arg(T&& data, F&& func)
			{
				if(!func(std::forward<T>(data)))
					throw std::invalid_argument("args need to parse");

				return arg(std::forward<T>(data));
			}

			std::shared_ptr<query_result> execute();

			void print();
		private:
			MysqlOP(const std::string &_sql) : sql(_sql) {}
			std::string sql;
		};
	}
}

