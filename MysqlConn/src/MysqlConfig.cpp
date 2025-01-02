#include "MysqlConfig.h"
#include <fstream>
#include "nlohmann/json.hpp"
#include <iostream>
#include <string>

bool MysqlConfig::MysqlConfig::parseJsonFile(string filename)
{
    std::ifstream ifs(filename);
    using nlohmann::json;
    auto root = json::parse(ifs);
    if (!root.empty())
    {
        ip = root["ip"];
        dbName = root["dbName"];
        password = root["password"];
        port = root["port"];
        user = root["user"];
        maxSize = root["maxSize"];
        minSize = root["minSize"];
        maxIdleTime = root["maxIdleTime"];
        timeOut = root["timeOut"];
		return true;
	}
	else
		return false;
}
