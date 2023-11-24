#pragma once
#include "MysqlConn.h"
#include <vector>
namespace DBConn
{
	namespace MysqlOP
	{
		using std::vector;
		class MysqlOP
		{
			// query result is a table
			static vector<vector<string>> query(string sql);

			// query result is a number
			template <typename T>
			static T countNumber(string sql);

		private:
			static auto& getPoolInstance();
		};
	}
}

