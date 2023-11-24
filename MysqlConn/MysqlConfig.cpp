#include "MysqlConfig.h"
#include <fstream>
#include "json.h"
bool MysqlConfig::MysqlConfig::parseJsonFile(string filename)
{
	std::ifstream ifs(filename);
	Json::Reader rd{};
	Json::Value root{};
	rd.parse(ifs, root);
	if (root.isObject())
	{
		ip = root["ip"].asString();
		dbName = root["dbName"].asString();
		password = root["password"].asString();
		port = root["port"].asInt();
		user = root["user"].asString();
		maxSize = root["maxSize"].asInt();
		minSize = root["minSize"].asInt();
		maxIdleTime = root["maxIdleTime"].asInt();
		timeOut = root["timeOut"].asInt();
		return true;
	}
	else
		return false;
}