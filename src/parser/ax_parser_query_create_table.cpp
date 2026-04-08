#include "ax_parser_query_create_table.hpp"
#include "ax_handle_system.hpp"

/**
 * @brief 解析 create table 查询语句
 *
 * @param query_sentence 查询语句
 * @return std::tuple<std::string, std::vector<std::string>, std::vector<std::string>, bool> 表名、字段名数组、字段类型数组、是否成功
 */
auto AxParserQueryCreateTable::ParserQueryCreateTableObject::parserQueryCreateTable(const std::string &query_sentence)
    -> std::tuple<std::string, std::vector<std::string>, std::vector<std::string>, bool>
{

    const char bracket_left{'('};
    const char bracket_right{')'};
    const char comma{','};
    const char space{' '};
    const bool ok{true};
    const bool no{false};

    std::string inner_string{query_sentence.substr(13)};
    std::string table_name;
    std::vector<std::string> column_names;
    std::vector<std::string> column_types;

    if (inner_string.find(bracket_left) == std::string::npos)
    {
        std::cout << "error: invalid query sentence, because bracket left is not found: '" << bracket_left << "'!" << std::endl;
        return std::make_tuple(table_name, column_names, column_types, no);
    }

    if (inner_string.find(bracket_right) == std::string::npos)
    {
        std::cout << "error: invalid query sentence, because bracket right is not found: '" << bracket_right << "'!" << std::endl;
        return std::make_tuple(table_name, column_names, column_types, no);
    }

    if (inner_string.find(comma) == std::string::npos)
    {
        std::cout << "error: invalid query sentence, because comma is not found: '" << comma << "'!" << std::endl;
        return std::make_tuple(table_name, column_names, column_types, no);
    }

    /* 理想查询语句格式: create table table_name (column_name1 column_type1, column_name2 column_type2, ...) */

    size_t bracket_left_pos = inner_string.find(bracket_left);
    table_name = inner_string.substr(0, bracket_left_pos);
    AxHandleSystem::HandleSystemObject::strip(table_name);
    if (table_name.empty())
    {
        std::cout << "error: invalid query sentence, because table name is empty -> table name: '" << table_name << "'!" << std::endl;
        return std::make_tuple(table_name, column_names, column_types, no);
    }

    size_t bracket_right_pos = inner_string.find(bracket_right, bracket_left_pos);
    std::string columns_str = inner_string.substr(bracket_left_pos + 1, bracket_right_pos - bracket_left_pos - 1);
    AxHandleSystem::HandleSystemObject::strip(columns_str);

    size_t start = 0;
    size_t end = columns_str.find(comma);
    while (end != std::string::npos)
    {
        std::string column_def = columns_str.substr(start, end - start);
        AxHandleSystem::HandleSystemObject::strip(column_def);
        if (!column_def.empty())
        {
            size_t space_pos = column_def.find(space);
            if (space_pos != std::string::npos)
            {
                std::string col_name = column_def.substr(0, space_pos);
                std::string col_type = column_def.substr(space_pos + 1);
                AxHandleSystem::HandleSystemObject::strip(col_name);
                AxHandleSystem::HandleSystemObject::strip(col_type);
                if (!col_name.empty() && !col_type.empty())
                {
                    column_names.push_back(col_name);
                    column_types.push_back(col_type);
                }
            }
        }
        start = end + 1;
        end = columns_str.find(comma, start);
    }

    std::string last_column_def = columns_str.substr(start);
    AxHandleSystem::HandleSystemObject::strip(last_column_def);
    if (!last_column_def.empty())
    {
        size_t space_pos = last_column_def.find(space);
        if (space_pos != std::string::npos)
        {
            std::string col_name = last_column_def.substr(0, space_pos);
            std::string col_type = last_column_def.substr(space_pos + 1);
            AxHandleSystem::HandleSystemObject::strip(col_name);
            AxHandleSystem::HandleSystemObject::strip(col_type);
            if (!col_name.empty() && !col_type.empty())
            {
                column_names.push_back(col_name);
                column_types.push_back(col_type);
            }
        }
    }

    return std::make_tuple(table_name, column_names, column_types, ok);
}