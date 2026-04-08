#pragma once

#ifndef AX_KERNEL_MANAGE_HPP
#define AX_KERNEL_MANAGE_HPP

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <map>
#include <shared_mutex>

namespace AxKernelManage
{

    class KernelManageObject
    {
    private:
        KernelManageObject() = delete;
        ~KernelManageObject() = delete;

    private:
        static std::shared_mutex map_for_database_shared_mutex;
        static std::shared_mutex map_for_table_shared_mutex;
        static std::shared_mutex map_for_field_shared_mutex;
        static std::shared_mutex map_for_ftype_shared_mutex;

    private:
        static std::unordered_map<std::string, int> map_for_database;
        static int database_name_max_width;

    private:
        static std::unordered_map<std::string, std::unordered_map<std::string, int>> map_for_table;
        static std::unordered_map<std::string, int> table_name_max_width;

    private:
        static std::unordered_map<std::string, std::unordered_map<std::string, int>> map_for_field_name_max_width;
        static std::unordered_map<std::string, std::unordered_map<std::string, int>> map_for_field_type_max_width;

    private:
        static std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_map<std::string, int>>>
            map_for_field_name_index;
        static std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_map<std::string, int>>>
            map_for_field_type_index;

    public:
        static auto computeFieldNameMaxWidth(const std::string &database_name, const std::string &table_name, const std::string &field_name) -> void;
        static auto computeFieldTypeMaxWidth(const std::string &database_name, const std::string &table_name, const std::string &field_type) -> void;
        static auto getFieldNameMaxWidth(const std::string &database_name, const std::string &table_name) -> int;
        static auto getFieldTypeMaxWidth(const std::string &database_name, const std::string &table_name) -> int;

    public:
        static auto databaseIsEmpty() -> bool;
        static auto databaseIsExist(const std::string &database_name) -> int;
        static auto synchronizeDatabaseInfoToMap(const std::string &database_name, const int &database_index) -> void;
        static auto getDatabaseNameMaxWidth() -> int;
        static auto getDatabaseNamesObjects() -> std::vector<std::string>;

    public:
        static auto tableIsEmpty(const std::string &database_name, const std::string &table_name) -> bool;
        static auto tableIsExist(const std::string &database_name, const std::string &table_name) -> int;
        static auto synchronizeTableInfoToMap(const std::string &database_name, const std::string &table_name, const int &table_index) -> void;
        static auto getTableNameMaxWidth(const std::string &database_name) -> int;

    public:
        static auto getDatabaseIndex(const std::string &database_name) -> int;
        static auto getTableIndex(const std::string &database_name, const std::string &table_name) -> int;
        static auto getFieldNameIndex(const std::string &database_name, const std::string &table_name, const std::string &field_name) -> int;
        static auto getFieldTypeIndex(const std::string &database_name, const std::string &table_name, const std::string &field_type) -> int;

    public:
        static auto synchronizeFieldIndexInfoToMap(const std::string &databasse_name, const std::string &table_name, const std::string &field_name, const int field_index) -> void;
        static auto synchronizeFTypeIndexInfoToMap(const std::string &databasse_name, const std::string &table_name, const std::string &field_type, const int ftype_index) -> void;
    };
}; /* namespace AxKernelManage */

#endif // AX_KERNEL_MANAGE_HPP
