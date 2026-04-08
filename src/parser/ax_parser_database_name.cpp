#include "ax_parser_database_name.hpp"
#include "ax_handle_system.hpp"

/* 预期接受语句: create database database_name*/
/**
 * @brief 解析数据库名称
 *
 * @param line 输入的SQL语句
 * @return std::string 数据库名称, 如果解析失败则返回空字符串
 */
auto AxParserDatabaseName::ParserDatabaseNameObject::parseDatabaseName(const std::string &line) -> std::string
{
    if (line.empty())
    {
        std::cerr << "error: empty line: '" << line << "'" << std::endl;
        return "";
    }
    std::string database_name{line.substr(16)};
    AxHandleSystem::HandleSystemObject::strip(database_name);
    if (database_name.empty())
    {
        std::cerr << "error: empty database name: '" << line << "'" << std::endl;
        return "";
    }
    return database_name;
}