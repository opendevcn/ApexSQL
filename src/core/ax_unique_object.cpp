#include "ax_unique_object.hpp"

/* 全局互斥锁 作用于 -> 全局唯一数据库对象 */
std::shared_mutex AxUniqueObject::UniqueObject::apex_global_mutex;

/* 全局唯一数据库对象 */
std::vector<AxDatabaseModel::AxDatabase> AxUniqueObject::UniqueObject::databases;