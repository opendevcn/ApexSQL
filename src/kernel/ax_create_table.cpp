#include "ax_kernel_manage_public_method.hpp"
#include "ax_kernel_manage.hpp"
#include "ax_create_table.hpp"
#include "ax_unique_object.hpp"

namespace _AxCreateTable
{
    /* pubom -> AxKernelManagePublicMethod::KernelManagePublicMethodObject */
    using pubom = AxKernelManagePublicMethod::KernelManagePublicMethodObject;

    /**
     * @brief 检查表是否存在
     * @return true 表存在
     * @return false 表不存在
     */
    static auto _tableIsExist(const std::string &database_name, const std::string &table_name) -> bool
    {
        if (-1 != AxKernelManage::KernelManageObject::tableIsExist(database_name, table_name))
        {
            return true;
        }
        return false;
    }

    /**
     * @brief 获取数据库索引
     * @return int 数据库索引 -1 表示数据库不存在
     */
    static auto _getDatabaseIndex(const std::string &database_name) -> int
    {
        return AxKernelManage::KernelManageObject::databaseIsExist(database_name);
    }

    /**
     * @brief 同步表信息到映射
     * @param database_name 数据库名称
     * @param table_name 表名称
     * @param table_index 表索引
     */
    static auto _synchronizeTableInfoToMap(const std::string &database_name, const std::string &table_name, const int &table_index) -> void
    {
        AxKernelManage::KernelManageObject::synchronizeTableInfoToMap(database_name, table_name, table_index);
    }

    /**
     * @brief 查找重复的字符串名称
     * @param target_strings_array 目标字符串数组
     * @return std::unordered_map<std::string, int> 重复字符串名称和名称索引的映射表
     */
    static auto _findRepeatStringName(const std::vector<std::string> &target_strings_array) -> std::tuple<std::string, int>
    {
        return pubom::findRepeatStringName(target_strings_array);
    }

    /**
     * @brief 同步字段信息到映射
     * @param database_name 数据库名称
     * @param table_name 表名称
     * @param field_name 字段名称
     * @param field_type 字段类型
     * @param pub_index 公共索引(有序映射索引)，用于同步字段索引和字段类型索引到映射中
     */
    static auto _synchronizeFieldAndTypeInfoToMap(const std::string &database_name, const std::string &table_name, const std::string &field_name,
                                                  const std::string &field_type, int &pub_index) -> void
    {
        AxKernelManage::KernelManageObject::synchronizeFieldIndexInfoToMap(database_name, table_name, field_name, pub_index);
        AxKernelManage::KernelManageObject::synchronizeFTypeIndexInfoToMap(database_name, table_name, field_type, pub_index);
    }

    /**
     * @brief 计算字段名称和字段类型的最大宽度
     * @param database_name 数据库名称
     * @param table_name 表名称
     * @param field_name 字段名称
     * @param field_type 字段类型
     */
    static auto _computeFieldNameAndTypeMaxWidth(const std::string &database_name, const std::string &table_name, const std::string &field_name,
                                                 const std::string &field_type) -> void
    {

        AxKernelManage::KernelManageObject::computeFieldNameMaxWidth(database_name, table_name, field_name);
        AxKernelManage::KernelManageObject::computeFieldTypeMaxWidth(database_name, table_name, field_type);
    }

}

auto AxCreateTable::CreateTableObject::createTableObject(const std::string &database_name, const std::string &table_name,
                                                         const std::vector<std::string> &field_names, const std::vector<std::string> &field_types) -> void
{
    /* check table name already exist */
    if (_AxCreateTable::_tableIsExist(database_name, table_name))
    {
        std::cout << "error: table object already exist: '" << table_name << "'." << std::endl;
        return;
    }

    /* check database name already exist, but can not found object index */
    int database_index{_AxCreateTable::_getDatabaseIndex(database_name)};
    if (-1 == database_index)
    {
        std::cout << "fatal error: database object exist, but can not found object index: '" << database_name << "' " << "index: '" << database_index << "'!" << std::endl;
        return;
    }

    /* check field names and field types size not equal */
    if (field_names.size() != field_types.size())
    {
        std::cout << "error: field names and field types size not equal." << std::endl;
        return;
    }

    /* check field types is unexpected apex type */
    for (const auto &type : field_types)
    {
        if (!AxKernelManagePublicMethod::KernelManagePublicMethodObject::findUnexpectedAxType(type))
        {
            std::cout << "error: field type is unexpected apex type: '" << type << "'." << std::endl;
            return;
        }
    }

    /* check field names repeat */
    auto [repeat_field_name, repeat_field_index]{_AxCreateTable::_findRepeatStringName(field_names)};
    if (repeat_field_index != -1)
    {
        std::cout << "error: field name repeat: '" << repeat_field_name << "' index: '" << repeat_field_index << "'." << std::endl;
        return;
    }

    int table_index{0};
    AxUniqueObject::UniqueObject::databases.at(database_index).tables.push_back({table_name, {}, {}});
    table_index = AxUniqueObject::UniqueObject::databases.at(database_index).tables.size() - 1;
    _AxCreateTable::_synchronizeTableInfoToMap(database_name, table_name, table_index);

    for (int index{0}; index < field_names.size(); index++)
    {
        AxUniqueObject::UniqueObject::databases
            .at(database_index)
            .tables
            .at(table_index)
            .fields
            .push_back({field_names.at(index), AxDataTypeModel::AxDataTypeObject::stringToDataType(field_types.at(index))});
        _AxCreateTable::_synchronizeFieldAndTypeInfoToMap(database_name, table_name, field_names.at(index), field_types.at(index), index);
        _AxCreateTable::_computeFieldNameAndTypeMaxWidth(database_name, table_name, field_names.at(index), field_types.at(index));
    }
}
