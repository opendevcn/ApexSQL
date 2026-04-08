#pragma once

#ifndef AX_KERNEL_FORMAT_HPP
#define AX_KERNEL_FORMAT_HPP

#include <string>

namespace AxKernelFormat
{
    class KernelFormatObject
    {
    private:
        KernelFormatObject() = delete;
        ~KernelFormatObject() = delete;

    public:
        static auto printLine(const int &width) -> void;
        static auto printLine(const int &item_number, const int &width) -> void;
        static auto printLine(const std::string &str, const int &width) -> void;
        static auto printLine(const std::string &item, const int &width, int &ref_line_break_counter, const int &item_number) -> void;
    };
}; /* namespace AxKernelFormat */

#endif // AX_KERNEL_FORMAT_HPP
