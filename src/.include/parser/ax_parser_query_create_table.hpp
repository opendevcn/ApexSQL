#pragma once

#ifndef AX_PARSER_QUERY_CREATE_TABLE_HPP
#define AX_PARSER_QUERY_CREATE_TABLE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <tuple>

namespace AxParserQueryCreateTable
{

    class ParserQueryCreateTableObject
    {
    private:
        ParserQueryCreateTableObject() = delete;
        ~ParserQueryCreateTableObject() = delete;

    public:
        static auto parserQueryCreateTable(const std::string &query_sentence)
            -> std::tuple<std::string, std::vector<std::string>, std::vector<std::string>, bool>;

    public:
    };
}; /* namespace AxParserQueryCreateTable */

#endif // AX_PARSER_QUERY_CREATE_TABLE_HPP
