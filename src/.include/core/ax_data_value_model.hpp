#pragma once

#ifndef AX_DATA_VALUE_MODEL_HPP
#define AX_DATA_VALUE_MODEL_HPP

#include <variant>
#include <string>

namespace AxDataValueModel
{
    using std::string;
    using AxValue = std::variant<long long, long, short, int, string, char, double, float, bool>;

    class AxDataValueObject
    {
    private:
        AxDataValueObject() = delete;
        ~AxDataValueObject() = delete;

    public:
        static auto stringToApexValue(const string &value) -> AxValue;
        static auto apexValueToString(const AxValue &value) -> string;
    };
}; /* namespace AxDataValueModel */
#endif // AX_DATA_VALUE_MODEL_HPP
