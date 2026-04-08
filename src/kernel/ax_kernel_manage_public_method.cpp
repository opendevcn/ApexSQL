#include "ax_kernel_manage_public_method.hpp"
#include "ax_data_type_model.hpp"

auto AxKernelManagePublicMethod::KernelManagePublicMethodObject::findRepeatStringName(const std::vector<std::string> &target_strings_array)
    -> std::tuple<std::string, int>
{
    std::unordered_map<std::string, int> string_map;
    auto inner_string_list{target_strings_array};

    for (size_t index = 0; index < inner_string_list.size(); index++)
    {
        const auto &str = inner_string_list[index];
        if (string_map.find(str) != string_map.end())
        {
            return std::make_tuple(str, string_map[str]);
        }
        else
        {
            string_map[str] = static_cast<int>(index);
        }
    }
    return std::make_tuple(std::string(), -1);
}

auto AxKernelManagePublicMethod::KernelManagePublicMethodObject::findUnexpectedAxType(const std::string &target_string) -> bool
{
    if (AxDataTypeModel::AxDataType::ERROR_TYPE == AxDataTypeModel::AxDataTypeObject::stringToDataType(target_string))
    {
        return false; /* default return false, symbol is unexpected apex type */
    }
    return true; /* symbol is unexpected apex type */
}