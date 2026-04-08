#pragma once

#ifndef AX_PARSER_DATABASE_NAME_HPP
#define AX_PARSER_DATABASE_NAME_HPP

#include <iostream>
#include <string>

namespace AxParserDatabaseName
{
    class ParserDatabaseNameObject
    {
    private:
        ParserDatabaseNameObject() = delete;
        ~ParserDatabaseNameObject() = delete;

    public:
        static auto parseDatabaseName(const std::string &line) -> std::string;
    };
}; /* namespace AxParserDatabaseName */

#endif // AX_PARSER_DATABASE_NAME_HPP
