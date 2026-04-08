#include "ax_handle_system.hpp"
#include <algorithm>

std::mutex AxHandleSystem::HandleSystemObject::mtx;

/* 移除首尾字符串的空格符号 */
auto AxHandleSystem::HandleSystemObject::strip(std::string &string_line) -> void
{
    std::lock_guard<std::mutex> lock(mtx);
    if (string_line.empty())
    {
        return;
    }
    string_line.erase(0, string_line.find_first_not_of(" \t\n\v\r"));
    string_line.erase(string_line.find_last_not_of(" \t\n\v\r") + 1);
}

/* 移除字符串中所包含的所有空格符号 */
auto AxHandleSystem::HandleSystemObject::nospace(std::string &string_line) -> void
{
    std::lock_guard<std::mutex> lock(mtx);
    if (string_line.empty())
    {
        return;
    }
    string_line.erase(std::remove(string_line.begin(), string_line.end(), ' '), string_line.end());
}

/* 将字符串中的所有字符全部转为小写字符 */
auto AxHandleSystem::HandleSystemObject::lower(std::string &string_line) -> void
{
    std::lock_guard<std::mutex> lock(mtx);
    if (string_line.empty())
    {
        return;
    }
    for (auto &cr : string_line)
    {
        cr = static_cast<char>(std::tolower(static_cast<unsigned char>(cr)));
    }
}