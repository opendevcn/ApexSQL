#pragma once

#ifndef AX_DATA_TYPE_MODEL_HPP
#define AX_DATA_TYPE_MODEL_HPP

#include <unordered_map>
#include <string>

namespace AxDataTypeModel
{
    enum class AxDataType
    {
        MAXINT,    /* c++ -> MAXINT -> long long */
        BIGINT,    /* c++ -> BIGINT -> long */
        MININT,    /* c++ -> MININT -> short */
        INT,       /* c++ -> INT -> int */
        STRING,    /* c++ -> STRING -> string */
        CHAR,      /* c++ -> CHAR -> char */
        DOUBLE,    /* c++ -> DOUBLE -> double */
        FLOAT,     /* c++ -> FLOAT -> float */
        BOOL,      /* c++ -> BOOL -> bool */
        ERROR_TYPE /* ERROR_TYPE -> unexpected_type */
    };

    class AxDataTypeObject
    {
    private:
        AxDataTypeObject() = delete;
        ~AxDataTypeObject() = delete;

    public:
        static auto stringToDataType(const std::string &type) -> AxDataType;
        static auto dataTypeToString(const AxDataType &type) -> std::string;
    };
}; /* namespace AxDataTypeModel */

#endif // AX_DATA_TYPE_MODEL_HPP
