#include "ax_create_database.hpp"
#include "ax_unique_object.hpp"
#include "ax_kernel_manage.hpp"

namespace _AxCreateDatabase
{

    using mobj = AxKernelManage::KernelManageObject; /* mobj -> AxKernelManage::KernelManageObject */

    /**
     * @brief 检查数据库是否为空
     *
     * @return bool 如果数据库为空，则返回true，否则返回false
     */
    static auto _databaseIsEmpty() -> bool
    {
        return mobj::databaseIsEmpty();
    }

    /**
     * @brief 检查数据库是否存在
     *
     * @param name 数据库名称
     * @return bool 如果数据库存在，则返回true，否则返回false
     */
    static auto _databaseIsExist(const std::string &name) -> bool
    {
        return mobj::databaseIsExist(name) != -1;
    }

    /**
     * @brief 同步数据库索引到映射表
     *
     * @param name 数据库名称
     * @param database_index 数据库索引
     */
    static auto _synchronizeDatabaseInfoToMap(const std::string &name, const int &database_index) -> void
    {
        mobj::synchronizeDatabaseInfoToMap(name, database_index);
    }
}

/**
 * @brief 创建数据库
 * 创建成功不会返回信息，创建失败会返回错误信息
 *
 * @param name 数据库名称
 */
auto AxCreateDatabase::CreateDatabaseObject::createDatabase(const std::string &name) -> void
{
    std::unique_lock<std::shared_mutex> lock(AxUniqueObject::UniqueObject::apex_global_mutex);

    if (name.empty())
    {
        std::cerr << "error: database name is empty: '" << name << "'." << std::endl;
        return;
    }
    if (_AxCreateDatabase::_databaseIsExist(name))
    {
        std::cerr << "error: database already exist: '" << name << "'." << std::endl;
        return;
    }
    int database_index{0};
    {
        AxUniqueObject::UniqueObject::databases.push_back({name, {}});
        database_index = AxUniqueObject::UniqueObject::databases.size() - 1;
    }
    _AxCreateDatabase::_synchronizeDatabaseInfoToMap(name, database_index);
}