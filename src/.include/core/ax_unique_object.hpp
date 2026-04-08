#pragma once

#ifndef AX_UNIQUE_OBJECT_HPP
#define AX_UNIQUE_OBJECT_HPP

#include "ax_database_model.hpp"
#include <shared_mutex>
#include <vector>

namespace AxUniqueObject
{
    class UniqueObject
    {
    private:
        UniqueObject() = delete;
        ~UniqueObject() = delete;

    public:
        static std::shared_mutex apex_global_mutex;
        static std::vector<AxDatabaseModel::AxDatabase> databases;
    };
}; /* namespace AxUniqueObject */

#endif // AX_UNIQUE_OBJECT_HPP
