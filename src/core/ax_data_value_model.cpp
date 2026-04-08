#include "ax_data_value_model.hpp"

/* 字符串转换为 ApexSQL 数据值 */
auto AxDataValueModel::AxDataValueObject::stringToApexValue(const string &value) -> AxValue
{
    return AxValue(value);
}

/* ApexSQL 数据值转换为字符串 */
auto AxDataValueModel::AxDataValueObject::apexValueToString(const AxValue &value) -> string
{
    return std::get<string>(value);
}