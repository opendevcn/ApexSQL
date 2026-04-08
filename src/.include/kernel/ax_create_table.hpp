#pragma once

#ifndef AX_CREATE_TABLE_HPP
#define AX_CREATE_TABLE_HPP

#include <iostream>
#include <string>
#include <vector>

namespace AxCreateTable
{
    class CreateTableObject
    {
    private:
        CreateTableObject() = delete;
        ~CreateTableObject() = delete;

    public:
        static auto createTableObject(const std::string &database_name, const std::string &table_name,
                                      const std::vector<std::string> &field_names, const std::vector<std::string> &field_types) -> void;
    };
}; /* namespace AxCreateTable */

#endif // AX_CREATE_TABLE_HPP
