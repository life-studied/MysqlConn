#pragma once
#include <string>
#include <chrono>
#include "MysqlConfig.h"
#include "mysql.h"
namespace DBConn
{
	using std::string;
	using std::chrono::steady_clock;
	class DBConn
	{
		// connect DataBase
		virtual bool connect(string user, string password, string dbName, string ip, unsigned short port) = 0;

		// update DataBase
		virtual bool update(string sql) = 0;

		// query DataBase
		virtual bool query(string sql) = 0;

		// loop the result set
		virtual bool next() = 0;
		virtual string value(size_t index) = 0;

		// transaction operation
		virtual bool transaction() = 0;		//create a transaction
		virtual bool commit() = 0;			//commit it
		virtual bool rollback() = 0;		//fail and rollback it

	};

	class MysqlConn : public DBConn
	{
	public:
		MysqlConn();
		~MysqlConn();
		virtual bool connect(string user, string password, string dbName, string ip, unsigned short port = 3306) override;
		bool connect(MysqlConfig::MysqlConfig&& config);
		bool connect(MysqlConfig::MysqlConfig& config);
		virtual bool update(string sql) override;
		virtual bool query(string sql) override;
		virtual bool next() override;

		string title(size_t index);
		virtual string value(size_t index) override;
		size_t colNum();

		virtual bool transaction() override;
		virtual bool commit() override;
		virtual bool rollback() override;

		void refreshAliveTime();
		size_t getAliveTime();
	private:
		void freeRes();
	private:
		MYSQL* m_conn = nullptr;
		MYSQL_RES* m_result = nullptr;
		MYSQL_ROW m_row = nullptr;
		steady_clock::time_point m_aliveTime;
	};

	
}

