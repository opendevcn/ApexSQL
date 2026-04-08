#include "ax_show_table_struct.hpp"
#include "ax_kernel_format.hpp"
#include "ax_kernel_manage.hpp"
#include "ax_unique_object.hpp"
#include "ax_data_type_model.hpp"

auto AxShowTableStruct::ShowTableStructObject::showTableStructObject(const std::string &database_name, const std::string &table_name) -> void
{
    int database_index{AxKernelManage::KernelManageObject::getDatabaseIndex(database_name)};
    if (database_index == -1)
    {
        return;
    }

    int table_index{AxKernelManage::KernelManageObject::getTableIndex(database_name, table_name)};
    if (table_index == -1)
    {
        return;
    }

    int field_max_width{AxKernelManage::KernelManageObject::getFieldNameMaxWidth(database_name, table_name)};
    int ftype_max_width{AxKernelManage::KernelManageObject::getFieldTypeMaxWidth(database_name, table_name)};
    if (field_max_width == 0 || ftype_max_width == 0)
    {
        return;
    }

    int lasted_max_width{std::max(field_max_width, ftype_max_width)};

    auto fields{AxUniqueObject::UniqueObject::databases.at(database_index).tables.at(table_index).fields};
    int item_number{fields.size()};
    if (item_number == 0)
    {
        return;
    }

    int ref_line_break_counter{0};
    std::cout << "infor: table struct from database '" << database_name << "' table '" << table_name << "'." << std::endl;
    AxKernelFormat::KernelFormatObject::printLine(item_number, lasted_max_width);
    for (int index{0}; index < item_number; index++)
    {
        AxKernelFormat::KernelFormatObject::printLine(
            fields.at(index).name,
            lasted_max_width,
            ref_line_break_counter,
            item_number);
    }
    AxKernelFormat::KernelFormatObject::printLine(item_number, lasted_max_width);
    for (int index{0}; index < item_number; index++)
    {
        AxKernelFormat::KernelFormatObject::printLine(
            AxDataTypeModel::AxDataTypeObject::dataTypeToString(fields.at(index).type),
            lasted_max_width,
            ref_line_break_counter,
            item_number);
    }
    AxKernelFormat::KernelFormatObject::printLine(item_number, lasted_max_width);
}