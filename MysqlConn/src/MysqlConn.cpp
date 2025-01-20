#include "MysqlConn.h"

DBConn::MysqlConn::MysqlConn()
{
    m_conn = mysql_init(nullptr);
    mysql_set_character_set(m_conn, "utf8");
}

DBConn::MysqlConn::~MysqlConn()
{
    if (m_conn)  mysql_close(m_conn);
}

bool DBConn::MysqlConn::connect(string user, string password, string dbName, string ip, unsigned short port)
{
    auto m_ptr =  mysql_real_connect(m_conn, ip.c_str(), user.c_str(), password.c_str(), dbName.c_str(), port, nullptr, 0);
    return m_ptr != nullptr;
}

bool DBConn::MysqlConn::connect(MysqlConfig::MysqlConfig&& config)
{
    return connect(config.user, config.password, config.dbName, config.ip, config.port);
}

bool DBConn::MysqlConn::connect(MysqlConfig::MysqlConfig& config)
{
    return connect(config.user, config.password, config.dbName, config.ip, config.port);
}

bool DBConn::MysqlConn::update(string sql)
{
    constexpr int success = 0;
    return success == mysql_query(m_conn, sql.c_str());
}

bool DBConn::MysqlConn::query(string sql, MYSQL_RES*& res)
{
    constexpr int success = 0;
    if(success != mysql_query(m_conn, sql.c_str()))
        return false;

    res = mysql_store_result(m_conn);
    return true;
}

bool DBConn::MysqlConn::transaction()
{
    return mysql_autocommit(m_conn, false);     // open commit manually
}

bool DBConn::MysqlConn::commit()
{
    return mysql_commit(m_conn);
}

bool DBConn::MysqlConn::rollback()
{
    return mysql_rollback(m_conn);
}

void DBConn::MysqlConn::refreshAliveTime()
{
    m_aliveTime = steady_clock::now();
}

size_t DBConn::MysqlConn::getAliveTime()
{
    using namespace std::chrono;
    auto res = duration_cast<milliseconds>(steady_clock::now() - m_aliveTime);
    return res.count();
}