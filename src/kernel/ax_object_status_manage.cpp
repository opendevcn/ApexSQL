#include "ax_object_status_manage.hpp"

std::string AxObjectStatusManage::ObjectStatusManage::_database_object_name;
std::string AxObjectStatusManage::ObjectStatusManage::_database_table_number;

auto AxObjectStatusManage::ObjectStatusManage::getDatabaseObjectName() -> std::string
{
    return _database_object_name;
}

auto AxObjectStatusManage::ObjectStatusManage::getDatabaseTableNumber() -> std::string
{
    return _database_table_number;
}

auto AxObjectStatusManage::ObjectStatusManage::setDatabaseObjectName(const std::string &object_name) -> void
{
    _database_object_name = object_name;
}

auto AxObjectStatusManage::ObjectStatusManage::setDatabaseTableNumber(const int &table_number) -> void
{
    _database_table_number = std::to_string(table_number);
}
