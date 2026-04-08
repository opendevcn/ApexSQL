#pragma once

#ifndef AX_SHOW_TABLE_STRUCT_HPP
#define AX_SHOW_TABLE_STRUCT_HPP

#include <iostream>
#include <string>

namespace AxShowTableStruct
{
    class ShowTableStructObject
    {
    private:
        ShowTableStructObject() = delete;
        ~ShowTableStructObject() = delete;

    public:
        static auto showTableStructObject(const std::string &database_name, const std::string &table_name) -> void;
    };
}; /* namespace AxShowTableStruct */

#endif // AX_SHOW_TABLE_STRUCT_HPP
