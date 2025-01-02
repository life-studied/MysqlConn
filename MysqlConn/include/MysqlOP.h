#pragma once

#include <vector>
#include <string>
#include <type_traits>

namespace DBConn
{
    using std::vector;
    using std::string;
	struct Table
	{
		vector<string> titles;
		vector<vector<string>> content;
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
						sql.replace(idx, 1, std::string("\"") + data + "\"");
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
					sql.replace(idx, 1, std::string("\"") + data + "\"");
				}
				return *this;
			}

			Table execute();

			void print();
		private:
			MysqlOP(const std::string &_sql) : sql(_sql) {}
			std::string sql;
		};
	}
}

