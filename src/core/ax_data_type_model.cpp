#include "ax_data_type_model.hpp"

/* 数据类型映射表 string to apex data type */
const static std::unordered_map<std::string, AxDataTypeModel::AxDataType> string_to_data_type_map{
    {"maxint", AxDataTypeModel::AxDataType::MAXINT},
    {"bigint", AxDataTypeModel::AxDataType::BIGINT},
    {"minint", AxDataTypeModel::AxDataType::MININT},
    {"int", AxDataTypeModel::AxDataType::INT},
    {"string", AxDataTypeModel::AxDataType::STRING},
    {"char", AxDataTypeModel::AxDataType::CHAR},
    {"double", AxDataTypeModel::AxDataType::DOUBLE},
    {"float", AxDataTypeModel::AxDataType::FLOAT},
    {"bool", AxDataTypeModel::AxDataType::BOOL},
};

/* 数据类型映射表 apex data type to string */
const static std::unordered_map<AxDataTypeModel::AxDataType, std::string> data_type_to_string_map{
    {AxDataTypeModel::AxDataType::MAXINT, "maxint"},
    {AxDataTypeModel::AxDataType::BIGINT, "bigint"},
    {AxDataTypeModel::AxDataType::MININT, "minint"},
    {AxDataTypeModel::AxDataType::INT, "int"},
    {AxDataTypeModel::AxDataType::STRING, "string"},
    {AxDataTypeModel::AxDataType::CHAR, "char"},
    {AxDataTypeModel::AxDataType::DOUBLE, "double"},
    {AxDataTypeModel::AxDataType::FLOAT, "float"},
    {AxDataTypeModel::AxDataType::BOOL, "bool"},
};

/* 字符串转换为数据类型 */
auto AxDataTypeModel::AxDataTypeObject::stringToDataType(const std::string &type) -> AxDataTypeModel::AxDataType
{
    if (string_to_data_type_map.find(type) == string_to_data_type_map.end())
    {
        return AxDataTypeModel::AxDataType::ERROR_TYPE;
    }
    return string_to_data_type_map.at(type);
}

/* 数据类型转换为字符串 */
auto AxDataTypeModel::AxDataTypeObject::dataTypeToString(const AxDataTypeModel::AxDataType &type) -> std::string
{
    if (data_type_to_string_map.find(type) == data_type_to_string_map.end())
    {
        return "error_type";
    }
    return data_type_to_string_map.at(type);
}