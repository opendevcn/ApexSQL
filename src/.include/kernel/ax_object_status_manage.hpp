#pragma once

#ifndef AX_OBJECT_STATUS_MANAGE_HPP
#define AX_OBJECT_STATUS_MANAGE_HPP

#include <string>

namespace AxObjectStatusManage
{
    class ObjectStatusManage
    {
    private:
        ObjectStatusManage() = delete;
        ~ObjectStatusManage() = delete;

    private:
        static std::string _database_object_name;
        static std::string _database_table_number;

    public:
        static auto getDatabaseObjectName() -> std::string;
        static auto getDatabaseTableNumber() -> std::string;
        static auto setDatabaseObjectName(const std::string &object_name) -> void;
        static auto setDatabaseTableNumber(const int &table_number) -> void;
    };
}; /* namespace AxObjectStatusManage */

#endif // AX_OBJECT_STATUS_MANAGE_HPP
