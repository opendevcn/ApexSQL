#pragma once

#ifndef AX_HANDLE_SYSTEM_HPP
#define AX_HANDLE_SYSTEM_HPP

#include <string>
#include <mutex>

namespace AxHandleSystem
{
    class HandleSystemObject
    {
    private:
        HandleSystemObject() = delete;
        ~HandleSystemObject() = delete;

    private:
        static std::mutex mtx;

    public:
        static auto strip(std::string &string_line) -> void;
        static auto nospace(std::string &string_line) -> void;
        static auto lower(std::string &string_line) -> void;
    };
}; /* namespace AxHandleSystem */

#endif // AX_HANDLE_SYSTEM_HPP
