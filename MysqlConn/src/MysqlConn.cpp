#include "MysqlConn.h"
DBConn::MysqlConn::MysqlConn()
{
    m_conn = mysql_init(nullptr);
    mysql_set_character_set(m_conn, "utf8");        //set default charset to utf8
}

DBConn::MysqlConn::~MysqlConn()
{
    if (m_conn)  mysql_close(m_conn);
    freeRes();
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
    freeRes();
    constexpr int success = 0;
    return success == mysql_query(m_conn, sql.c_str());
}

bool DBConn::MysqlConn::query(string sql)
{
    freeRes();
    constexpr int success = 0;
    if(success != mysql_query(m_conn, sql.c_str()))     // execute query
        return false;
    else
    {
        m_result = mysql_store_result(m_conn);          // store result set
        return true;
    }
}

bool DBConn::MysqlConn::next()
{
    if (m_result)
    {
        m_row = mysql_fetch_row(m_result);
    }
    return m_row != nullptr;
}

std::string DBConn::MysqlConn::title(size_t index)
{
    auto cn = colNum();
    auto* fields = mysql_fetch_fields(m_result);
    return fields[index].name;
}

std::string DBConn::MysqlConn::value(size_t index)
{
    if (m_result)
    {
        auto colNum = mysql_num_fields(m_result);
        if (index >= colNum || index < 0)       // out of range
            return {};
    }
    char* valStr = m_row[index];

    auto strLen = mysql_fetch_lengths(m_result)[index];     // value after \0 may be miss
    return std::string(valStr, strLen);                     // std::string(valStr) is wrong!
}

size_t DBConn::MysqlConn::colNum()
{
    if (m_result)
    {
        return mysql_num_fields(m_result);
    }
    return 0;
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

void DBConn::MysqlConn::freeRes()
{
    if (m_result)
    {
        mysql_free_result(m_result);
        m_result = nullptr;
    }
}
