#pragma once

#ifndef AX_USE_DATABASE_HPP
#define AX_USE_DATABASE_HPP

#include <iostream>
#include <string>

namespace AxUseDatabase
{
    class UseDatabaseObject
    {
    private:
        UseDatabaseObject() = delete;
        ~UseDatabaseObject() = delete;

    public:
        static auto useDatabaseObject(const std::string &database_name) -> void;
    };
}; /* namespace AxUseDatabase */

#endif // AX_USE_DATABASE_HPP
