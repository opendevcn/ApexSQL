#include "ax_show_tables.hpp"
#include "ax_kernel_format.hpp"
#include "ax_kernel_manage.hpp"
#include "ax_unique_object.hpp"

auto AxShowTables::ShowTablesObject::showTables(const std::string &database_name) -> void
{
    auto database_index{AxKernelManage::KernelManageObject::getDatabaseIndex(database_name)};
    if (database_index == -1)
    {
        std::cerr << "error: database object exist, but can not find database index: '" << database_name << "' -> '" << database_index << "'." << std::endl;
        return;
    }

    auto table_name_max_width{AxKernelManage::KernelManageObject::getTableNameMaxWidth(database_name)};
    auto table_names{AxUniqueObject::UniqueObject::databases.at(database_index).tables};

    if (table_names.empty())
    {
        std::cout << "infor: current database have no table in -> '" << database_name << "'." << std::endl;
        return;
    }

    if (table_name_max_width == 0)
    {
        std::cerr << "fatal error: exist database object '" << database_name << "' and table object, but can not get table object max width -> '" << table_name_max_width << "'!" << std::endl;
        return;
    }

    AxKernelFormat::KernelFormatObject::printLine(table_name_max_width);
    for (auto &item : table_names)
    {
        AxKernelFormat::KernelFormatObject::printLine(item.name, table_name_max_width);
    }
    AxKernelFormat::KernelFormatObject::printLine(table_name_max_width);
}
