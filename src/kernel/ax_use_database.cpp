#include "ax_object_status_manage.hpp"
#include "ax_kernel_manage.hpp"
#include "ax_use_database.hpp"
#include "ax_unique_object.hpp"
#include <algorithm>

auto AxUseDatabase::UseDatabaseObject::useDatabaseObject(const std::string &database_name) -> void
{
    int database_index{AxKernelManage::KernelManageObject::databaseIsExist(database_name)};

    if (-1 != database_index && std::find_if(AxUniqueObject::UniqueObject::databases.begin(),
                                             AxUniqueObject::UniqueObject::databases.end(), [&database_name](const AxDatabaseModel::AxDatabase &db)
                                             { return db.name == database_name; }) != AxUniqueObject::UniqueObject::databases.end())
    {
        AxObjectStatusManage::ObjectStatusManage::setDatabaseObjectName(database_name);
        AxObjectStatusManage::ObjectStatusManage::setDatabaseTableNumber(AxUniqueObject::UniqueObject::databases[database_index].tables.size());
        return;
    }

    std::cout << "error: database object not found: '" << database_name << "'." << std::endl;
}