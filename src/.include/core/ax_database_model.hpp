#pragma once

#ifndef AX_DATABASE_MODEL_HPP
#define AX_DATABASE_MODEL_HPP

#include "ax_data_value_model.hpp"
#include "ax_data_type_model.hpp"
#include <variant>
#include <string>
#include <vector>

namespace AxDatabaseModel
{
    using std::string;
    using std::vector;
    struct AxField
    {
        string name;
        AxDataTypeModel::AxDataType type;
    };
    struct AxTable
    {
        string name;
        vector<AxField> fields;
        vector<vector<AxDataValueModel::AxValue>> rows;
    };
    struct AxDatabase
    {
        string name;
        vector<AxTable> tables;
    };
}; /* namespace AxDatabaseModel */

#endif // AX_DATABASE_MODEL_HPP
