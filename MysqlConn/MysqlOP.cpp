#include "MysqlOP.h"

DBConn::Table DBConn::MysqlOP::MysqlOP::query(string sql)
{
    Table table;
    auto& instance = SinglePool::getInstance();
    auto conn = instance.getConntion();
    conn->query(sql);
    auto colNum = conn->colNum();
    for (int i = 0; i < colNum; i++)
        table.titles.push_back(conn->title(i));
    while (conn->next())
    {
        vector<string> row;
        for (int i = 0; i < colNum; i++)
            row.push_back(conn->value(i));
        table.content.push_back(row);
    }
    return table;
}

DBConn::Number DBConn::MysqlOP::MysqlOP::countNumber(string sql)
{
    Number n;
    auto& instance = SinglePool::getInstance();
    auto conn = instance.getConntion();
    conn->query(sql);
    n.name = conn->title(0);
    if (conn->next())
        n.data = conn->value(0);
    return n;
}
