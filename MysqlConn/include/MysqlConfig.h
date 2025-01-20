#pragma once
#include <string>
namespace MysqlConfig
{
	using std::string;
	struct MysqlConfig
	{
		string user;
		string password;
		string dbName;
		string ip;
		unsigned short port;
		size_t maxSize;		//上限
		size_t minSize;		//下限
		size_t timeOut;		//超时
		size_t maxIdleTime;	//空闲

		bool parseJsonFile(string filename = "dbConfig.json");
	};
}


