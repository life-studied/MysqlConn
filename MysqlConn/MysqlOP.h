#pragma once
#include "MysqlConnPool.h"
#include <vector>
#include <string>
namespace DBConn
{
	using std::vector;
	struct Table
	{
		vector<string> titles;
		vector<vector<string>> content;
	};

	struct Number
	{
		string name;
		string data;
	};

	namespace MysqlOP
	{
		class MysqlOP
		{
		public:
			// query result is a table
			static Table query(string sql);

			// query result is a number
			static Number countNumber(string sql);


		};

		
	}
}

