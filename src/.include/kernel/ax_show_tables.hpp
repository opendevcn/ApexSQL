#pragma once

#ifndef AX_SHOW_TABLES_HPP
#define AX_SHOW_TABLES_HPP

#include <iostream>
#include <string>

namespace AxShowTables
{
    class ShowTablesObject
    {
    private:
        ShowTablesObject() = delete;
        ~ShowTablesObject() = delete;

    public:
        static auto showTables(const std::string &database_name) -> void;
    };
}; /* namespace AxShowTables */

#endif // AX_SHOW_TABLES_HPP
