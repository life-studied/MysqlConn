#pragma once
#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>
#include "MysqlConn.h"
#include "Singleton.hpp"
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
		MysqlConfig::MysqlConfig config;
		

		queue<shared_ptr<MysqlConn>> pool;
		bool isOver = false;
		mutex mtx;
		condition_variable cv;
	};
	using SinglePool = Singleton<MysqlConnPool>;
}

