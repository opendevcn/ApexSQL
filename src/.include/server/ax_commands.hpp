#pragma once

#ifndef AX_COMMANDS_HPP
#define AX_COMMANDS_HPP

#include "ax_status_code.hpp"
#include <string>
#include <iostream>

namespace AxCommands
{
    class CommandsObject
    {
    private:
        CommandsObject() = delete;
        ~CommandsObject() = delete;

    public:
        static auto commands(const std::string &line) -> AxStatusCode::ApexStatusCode;
    };
}; /* namespace AxCommands */

#endif // AX_COMMANDS_HPP
