#pragma once

#ifndef AX_KERNEL_MANAGE_PUBLIC_METHOD_HPP
#define AX_KERNEL_MANAGE_PUBLIC_METHOD_HPP

#include <unordered_map>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>

namespace AxKernelManagePublicMethod
{
    class KernelManagePublicMethodObject
    {
    private:
        KernelManagePublicMethodObject() = delete;
        ~KernelManagePublicMethodObject() = delete;

    public:
        static auto findRepeatStringName(const std::vector<std::string> &target_strings_array) -> std::tuple<std::string, int>;
        static auto findUnexpectedAxType(const std::string &target_string) -> bool;
    };
}; /* namespace AxKernelManagePublicMethod */

#endif // AX_KERNEL_MANAGE_PUBLIC_METHOD_HPP
