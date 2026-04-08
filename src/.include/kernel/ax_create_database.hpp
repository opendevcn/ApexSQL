#pragma once

#ifndef AX_CREATE_DATABASE_HPP
#define AX_CREATE_DATABASE_HPP

#include <iostream>
#include <string>
#include <algorithm>

namespace AxCreateDatabase
{
    class CreateDatabaseObject
    {
    private:
        CreateDatabaseObject() = delete;
        ~CreateDatabaseObject() = delete;

    public:
        static auto createDatabase(const std::string &name) -> void;
    };
}; /* namespace AxCreateDatabase */

#endif // AX_CREATE_DATABASE_HPP
