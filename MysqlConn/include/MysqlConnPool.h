#pragma once
#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>

#include "Singleton.hpp"
#include "MysqlConfig.h"
#include "MysqlConn.h"

namespace DBConn
{
	using std::queue;
	using std::shared_ptr;
	using std::mutex;
	using std::condition_variable;
	class MysqlConnPool
	{
	public:
		MysqlConnPool();
		~MysqlConnPool();
		shared_ptr<MysqlConn> getConntion();
	private:
		void addConn();
	private:
		// 配置信息
		MysqlConfig::MysqlConfig config;
		
		// 连接池
		queue<shared_ptr<MysqlConn>> pool;
		bool isOver = false;
		mutex mtx;
		condition_variable cv;
	};
	using SinglePool = Singleton<MysqlConnPool>;
}

