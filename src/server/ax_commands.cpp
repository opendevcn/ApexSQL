#include "ax_commands.hpp"

auto AxCommands::CommandsObject::commands(const std::string &line) -> AxStatusCode::ApexStatusCode
{
    /* process exit command */
    if ("exit" == line || "quit" == line)
    {
        return AxStatusCode::ApexStatusCode::NO;
    }
    return AxStatusCode::ApexStatusCode::UNEXPECTED;
}