#include "ax_dispatcher.hpp"
#include "ax_commands.hpp"
#include "ax_helps.hpp"
#include "ax_settings.hpp"
#include "ax_querys.hpp"

auto AxDispatcher::DispatcherObject::apexDispatcher(const std::string &line) -> AxStatusCode::ApexStatusCode
{
    /* process comment line */
    if ("#" == line.substr(0, 1) || "--" == line.substr(0, 2) || "//" == line.substr(0, 2))
    {
        return AxStatusCode::ApexStatusCode::CONTINUE;
    }

    /* process help command */
    if ("help -" == line.substr(0, 6))
    {
        if (AxStatusCode::ApexStatusCode::UNEXPECTED == AxHelps::HelpsObject::helps(line))
        {
            std::cerr << "error: unexpected help command: '" << line << "'!" << std::endl;
            return AxStatusCode::ApexStatusCode::CONTINUE;
        }
    }

    /* process settings command */
    if ("set -" == line.substr(0, 5))
    {
        if (AxStatusCode::ApexStatusCode::UNEXPECTED == AxSettings::SettingsObject::settings(line))
        {
            std::cerr << "error: unexpected settings command: '" << line << "'!" << std::endl;
            return AxStatusCode::ApexStatusCode::CONTINUE;
        }
    }

    /* process commands */
    if (AxStatusCode::ApexStatusCode::NO == AxCommands::CommandsObject::commands(line))
    {
        return AxStatusCode::ApexStatusCode::NO;
    }

    /* process querys sentence */
    if (AxStatusCode::ApexStatusCode::UNEXPECTED == AxQuerys::QuerysObject::querys(line))
    {
        std::cerr << "error: unexpected query sentence or command: '" << line << "'!" << std::endl;
        return AxStatusCode::ApexStatusCode::CONTINUE;
    }
    return AxStatusCode::ApexStatusCode::CONTINUE;
}