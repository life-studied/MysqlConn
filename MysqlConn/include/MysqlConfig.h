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
		size_t maxSize;		//����
		size_t minSize;		//����
		size_t timeOut;		//��ʱ
		size_t maxIdleTime;	//����

		bool parseJsonFile(string filename = "dbConfig.json");
	};
}


