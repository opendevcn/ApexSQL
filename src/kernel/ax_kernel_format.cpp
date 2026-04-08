#include "ax_kernel_format.hpp"
#include "ax_multi_language_width.hpp"
#include <iostream>
#include <iomanip>

/**
 * @brief 打印行
 *
 * @param width 行的宽度 (width + 2)
 * @return void
 */
auto AxKernelFormat::KernelFormatObject::printLine(const int &width) -> void
{
    std::cout << '+';
    std::cout << std::string(width + 2, '-');
    std::cout << '+';
    std::cout << std::endl;
}

/**
 * @brief 打印行
 *
 * @param item_number 元素数量
 * @param width 行的宽度 (width + 2)
 * @return void
 */
auto AxKernelFormat::KernelFormatObject::printLine(const int &item_number, const int &width) -> void
{
    std::cout << '+';
    std::cout << std::string(((width + 2) * item_number) + (item_number - 1), '-');
    std::cout << '+';
    std::cout << std::endl;
}

/**
 * @brief 打印行
 *
 * @param str 要打印的字符串
 * @param width 行的宽度 (width + 2)
 * @return void
 */
auto AxKernelFormat::KernelFormatObject::printLine(const std::string &str, const int &width) -> void
{
    std::cout << '|';
    std::cout << ' ';
    std::cout << str;
    int current_width = AxMultiLanguageWidth::MultiLanguageWidthObject::getAdaptationDisplayWidth(str);
    int spaces_needed = width - current_width;
    std::cout << std::string(spaces_needed, ' ');
    std::cout << ' ';
    std::cout << '|';
    std::cout << std::endl;
}

/**
 * @brief 打印行
 *
 * @param item 要打印的字符串
 * @param width 行的宽度 (width + 2)
 * @param ref_line_break_counter 行换行计数器
 * @param item_number 元素数量
 * @return void
 */
auto AxKernelFormat::KernelFormatObject::printLine(const std::string &item, const int &width, int &ref_line_break_counter, const int &item_number) -> void
{
    std::cout << '|';
    std::cout << ' ';
    std::cout << item;
    int current_width = AxMultiLanguageWidth::MultiLanguageWidthObject::getAdaptationDisplayWidth(item);
    int spaces_needed = width - current_width;
    std::cout << std::string(spaces_needed, ' ');
    std::cout << ' ';
    ref_line_break_counter++;

    if (ref_line_break_counter == item_number)
    {
        std::cout << '|';
        std::cout << std::endl;
        ref_line_break_counter = 0;
    }
}