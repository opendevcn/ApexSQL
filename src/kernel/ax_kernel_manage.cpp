#include "ax_kernel_manage.hpp"
#include "ax_multi_language_width.hpp"

/* 数据库映射共享互斥锁 */
std::shared_mutex AxKernelManage::KernelManageObject::map_for_database_shared_mutex;
/* 表映射共享互斥锁 */
std::shared_mutex AxKernelManage::KernelManageObject::map_for_table_shared_mutex;
/* 字段映射共享互斥锁 */
std::shared_mutex AxKernelManage::KernelManageObject::map_for_field_shared_mutex;
/* 字段类型映射共享互斥锁 */
std::shared_mutex AxKernelManage::KernelManageObject::map_for_ftype_shared_mutex;

/* 数据库映射: 数据库名称 -> 数据库索引 */
std::unordered_map<std::string, int> AxKernelManage::KernelManageObject::map_for_database;

/* 数据库名称最大宽度: 默认初始化为零 */
int AxKernelManage::KernelManageObject::database_name_max_width{0};

/* 表映射: 数据库名称 -> 表名称 -> 表索引 */
std::unordered_map<std::string, std::unordered_map<std::string, int>> AxKernelManage::KernelManageObject::map_for_table;

/* 表名称最大宽度 */
std::unordered_map<std::string, int> AxKernelManage::KernelManageObject::table_name_max_width;

/* 字段名称最大宽度: 数据库名称 -> 表名称 -> 字段名称的最大宽度 */
std::unordered_map<std::string, std::unordered_map<std::string, int>>
    AxKernelManage::KernelManageObject::map_for_field_name_max_width;

/* 字段类型最大宽度： 数据库名称 -> 表名称 -> 字段类型的最大宽度 */
std::unordered_map<std::string, std::unordered_map<std::string, int>>
    AxKernelManage::KernelManageObject::map_for_field_type_max_width;

/* 字段名称索引: 数据库名称 -> 表名称 -> 字段名称 -> 字段索引 */
std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_map<std::string, int>>>
    AxKernelManage::KernelManageObject::map_for_field_name_index;

/* 字段类型索引: 数据库名称 -> 表名称 -> 字段类型 -> 字段类型索引 */
std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_map<std::string, int>>>
    AxKernelManage::KernelManageObject::map_for_field_type_index;

/**
 * @brief 获取数据库索引
 *
 * @param database_name 数据库名称
 * @return int 数据库索引
 * @note 如果数据库名称不存在，则返回-1
 */
auto AxKernelManage::KernelManageObject::getDatabaseIndex(const std::string &database_name) -> int
{
    std::shared_lock<std::shared_mutex> lock(map_for_database_shared_mutex);
    if (map_for_database.empty())
    {
        return -1;
    }
    if (map_for_database.find(database_name) != map_for_database.end())
    {
        return map_for_database[database_name];
    }
    return -1;
}

/**
 * @brief 获取表索引
 *
 * @param database_name 数据库名称
 * @param table_name 表名称
 * @return int 表索引
 * @note 如果表名称不存在，则返回-1
 */
auto AxKernelManage::KernelManageObject::getTableIndex(const std::string &database_name, const std::string &table_name) -> int
{
    std::shared_lock<std::shared_mutex> lock(map_for_table_shared_mutex);
    if (map_for_table.empty())
    {
        return -1;
    }
    if (map_for_table.find(database_name) != map_for_table.end())
    {
        if (map_for_table[database_name].find(table_name) != map_for_table[database_name].end())
        {
            return map_for_table[database_name][table_name];
        }
    }
    return -1;
}

/**
 * @brief 获取字段名称索引
 *
 * @param database_name 数据库名称
 * @param table_name 表名称
 * @param field_name 字段名称
 * @return int 字段索引
 * @note 如果字段名称不存在，则返回-1
 */
auto AxKernelManage::KernelManageObject::getFieldNameIndex(const std::string &database_name, const std::string &table_name,
                                                           const std::string &field_name) -> int
{
    std::shared_lock<std::shared_mutex> lock(map_for_field_shared_mutex);
    if (map_for_field_name_index.empty())
    {
        return -1;
    }
    if (map_for_field_name_index.find(database_name) != map_for_field_name_index.end())
    {
        if (map_for_field_name_index[database_name].find(table_name) != map_for_field_name_index[database_name].end())
        {
            if (map_for_field_name_index[database_name][table_name].find(field_name) != map_for_field_name_index[database_name][table_name].end())
            {
                return map_for_field_name_index[database_name][table_name][field_name];
            }
        }
    }
    return -1;
}

/**
 * @brief 获取字段类型索引
 *
 * @param database_name 数据库名称
 * @param table_name 表名称
 * @param field_type 字段类型
 * @return int 字段索引
 * @note 如果字段类型不存在，则返回-1
 */
auto AxKernelManage::KernelManageObject::getFieldTypeIndex(const std::string &database_name, const std::string &table_name,
                                                           const std::string &field_type) -> int
{
    std::shared_lock<std::shared_mutex> lock(map_for_ftype_shared_mutex);
    if (map_for_field_type_index.empty())
    {
        return -1;
    }
    if (map_for_field_type_index.find(database_name) != map_for_field_type_index.end())
    {
        if (map_for_field_type_index[database_name].find(table_name) != map_for_field_type_index[database_name].end())
        {
            if (map_for_field_type_index[database_name][table_name].find(field_type) != map_for_field_type_index[database_name][table_name].end())
            {
                return map_for_field_type_index[database_name][table_name][field_type];
            }
        }
    }
    return -1;
}

/**
 * @brief 检查数据库是否为空
 *
 * @return bool 如果数据库为空，则返回true，否则返回false
 */
auto AxKernelManage::KernelManageObject::databaseIsEmpty() -> bool
{
    std::shared_lock<std::shared_mutex> lock(map_for_database_shared_mutex);
    return map_for_database.empty();
}

/**
 * @brief 检查数据库是否存在
 *
 * @param database_name 数据库名称
 * @return int 数据库索引
 * @note 如果数据库对象不存在，则返回-1， 否则返回数据库索引
 */
auto AxKernelManage::KernelManageObject::databaseIsExist(const std::string &database_name) -> int
{
    std::shared_lock<std::shared_mutex> lock(map_for_database_shared_mutex);
    return map_for_database.find(database_name) != map_for_database.end() ? map_for_database[database_name] : -1;
}

/**
 * @brief 同步数据库索引到映射表
 *
 * @param database_name 数据库名称
 * @param database_index 数据库索引
 *
 * @details 同步数据库索引到映射表，更新数据库名称最大宽度
 */
auto AxKernelManage::KernelManageObject::synchronizeDatabaseInfoToMap(const std::string &database_name, const int &database_index) -> void
{
    std::unique_lock<std::shared_mutex> lock(map_for_database_shared_mutex);
    map_for_database[database_name] = database_index;
    database_name_max_width = std::max(database_name_max_width, AxMultiLanguageWidth::MultiLanguageWidthObject::getAdaptationDisplayWidth(database_name));
    table_name_max_width[database_name] = 0;
}

/**
 * @brief 获取数据库名称最大宽度
 *
 * @return int 数据库名称最大宽度
 */
auto AxKernelManage::KernelManageObject::getDatabaseNameMaxWidth() -> int
{
    return database_name_max_width;
}

/**
 * @brief 获取数据库名称对象
 *
 * @return std::vector<std::string> 数据库名称对象
 */
auto AxKernelManage::KernelManageObject::getDatabaseNamesObjects() -> std::vector<std::string>
{
    std::shared_lock<std::shared_mutex> lock(map_for_database_shared_mutex);
    std::vector<std::string> database_names;
    database_names.reserve(map_for_database.size());
    for (const auto &item : map_for_database)
    {
        database_names.push_back(item.first);
    }
    return database_names;
}

/**
 * @brief 检查表是否为空
 *
 * @param database_name 数据库名称
 * @param table_name 表名称
 * @return bool 如果表为空，则返回true，否则返回false
 */
auto AxKernelManage::KernelManageObject::tableIsEmpty(const std::string &database_name, const std::string &table_name) -> bool
{
    std::shared_lock<std::shared_mutex> lock(map_for_table_shared_mutex);
    return map_for_table.find(database_name) == map_for_table.end() ||
           map_for_table[database_name].find(table_name) == map_for_table[database_name].end();
}

/**
 * @brief 检查表是否存在
 *
 * @param database_name 数据库名称
 * @param table_name 表名称
 * @return int 表索引
 * @note 如果表对象不存在，则返回-1， 否则返回表索引
 */
auto AxKernelManage::KernelManageObject::tableIsExist(const std::string &database_name, const std::string &table_name) -> int
{
    std::shared_lock<std::shared_mutex> lock(map_for_table_shared_mutex);
    return map_for_table.find(database_name) != map_for_table.end() &&
                   map_for_table[database_name].find(table_name) != map_for_table[database_name].end()
               ? map_for_table[database_name][table_name]
               : -1;
}

/**
 * @brief 同步表索引到映射表
 *
 * @param database_name 数据库名称
 * @param table_name 表名称
 * @param table_index 表索引
 *
 * @details 同步表索引到映射表，更新表名称最大宽度
 */
auto AxKernelManage::KernelManageObject::synchronizeTableInfoToMap(const std::string &database_name, const std::string &table_name, const int &table_index) -> void
{
    std::unique_lock<std::shared_mutex> lock(map_for_table_shared_mutex);
    map_for_table[database_name][table_name] = table_index;
    table_name_max_width.at(database_name) = std::max(table_name_max_width.at(database_name), AxMultiLanguageWidth::MultiLanguageWidthObject::getAdaptationDisplayWidth(table_name));
}

/**
 * @brief 获取表名称最大宽度
 *
 * @param database_name 数据库名称
 * @return int 表名称最大宽度
 */
auto AxKernelManage::KernelManageObject::getTableNameMaxWidth(const std::string &database_name) -> int
{
    return table_name_max_width.at(database_name);
}

/**
 * @brief 同步字段索引到映射表
 *
 * @param database_name 数据库名称
 * @param table_name 表名称
 * @param field_name 字段名称
 * @param field_index 字段索引
 */
auto AxKernelManage::KernelManageObject::synchronizeFieldIndexInfoToMap(
    const std::string &database_name, const std::string &table_name, const std::string &field_name, const int field_index) -> void
{
    std::unique_lock<std::shared_mutex> lock(map_for_field_shared_mutex);
    map_for_field_name_index[database_name][table_name][field_name] = field_index;
}

/**
 * @brief 同步字段类型索引到映射表
 *
 * @param database_name 数据库名称
 * @param table_name 表名称
 * @param field_type 字段类型
 * @param ftype_index 字段类型索引
 */
auto AxKernelManage::KernelManageObject::synchronizeFTypeIndexInfoToMap(
    const std::string &database_name, const std::string &table_name, const std::string &field_type, const int ftype_index) -> void
{
    std::unique_lock<std::shared_mutex> lock(map_for_ftype_shared_mutex);
    map_for_field_type_index[database_name][table_name][field_type] = ftype_index;
}

/**
 * @brief 计算字段名称最大宽度
 *
 * @param database_name 数据库名称
 * @param table_name 表名称
 * @param field_name 字段名称
 */
auto AxKernelManage::KernelManageObject::computeFieldNameMaxWidth(const std::string &database_name, const std::string &table_name,
                                                                  const std::string &field_name) -> void
{
    std::unique_lock<std::shared_mutex> lock(map_for_field_shared_mutex);
    map_for_field_name_max_width[database_name][table_name] = std::max(
        map_for_field_name_max_width[database_name][table_name],
        AxMultiLanguageWidth::MultiLanguageWidthObject::getAdaptationDisplayWidth(field_name));
}

/**
 * @brief 计算字段类型最大宽度
 *
 * @param database_name 数据库名称
 * @param table_name 表名称
 * @param field_type 字段类型
 */
auto AxKernelManage::KernelManageObject::computeFieldTypeMaxWidth(const std::string &database_name, const std::string &table_name,
                                                                  const std::string &field_type) -> void
{
    std::unique_lock<std::shared_mutex> lock(map_for_ftype_shared_mutex);
    map_for_field_type_max_width[database_name][table_name] = std::max(
        map_for_field_type_max_width[database_name][table_name],
        AxMultiLanguageWidth::MultiLanguageWidthObject::getAdaptationDisplayWidth(field_type));
}

/**
 * @brief 获取字段名称最大宽度
 *
 * @param database_name 数据库名称
 * @param table_name 表名称
 * @return int 字段名称最大宽度
 */
auto AxKernelManage::KernelManageObject::getFieldNameMaxWidth(const std::string &database_name, const std::string &table_name) -> int
{
    return map_for_field_name_max_width[database_name][table_name];
}

/**
 * @brief 获取字段类型最大宽度
 *
 * @param database_name 数据库名称
 * @param table_name 表名称
 * @return int 字段类型最大宽度
 */
auto AxKernelManage::KernelManageObject::getFieldTypeMaxWidth(const std::string &database_name, const std::string &table_name) -> int
{
    return map_for_field_type_max_width[database_name][table_name];
}
