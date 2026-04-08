#include "ax_show_databases.hpp"
#include "ax_kernel_format.hpp"
#include "ax_kernel_manage.hpp"
#include "ax_unique_object.hpp"

/**
 * @brief 显示数据库列表
 *
 * @return void
 */
auto AxShowDatabases::ShowDatabasesObject::showDatabases() -> void
{
    if (AxKernelManage::KernelManageObject::databaseIsEmpty() || AxUniqueObject::UniqueObject::databases.empty())
    {
        std::cerr << "error: database is empty!" << std::endl;
        return;
    }

    int database_name_max_width = AxKernelManage::KernelManageObject::getDatabaseNameMaxWidth();
    if (database_name_max_width == 0)
    {
        std::cerr << "error: database name max width is zero!" << std::endl;
        return;
    }

    std::cout << "ApexSQL Database List:" << std::endl;
    AxKernelFormat::KernelFormatObject::printLine(database_name_max_width);
    for (const auto &item : AxKernelManage::KernelManageObject::getDatabaseNamesObjects())
    {
        AxKernelFormat::KernelFormatObject::printLine(item, database_name_max_width);
    }
    AxKernelFormat::KernelFormatObject::printLine(database_name_max_width);
}