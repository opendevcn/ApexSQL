#pragma once

#ifndef AX_SETTINGS_HPP
#define AX_SETTINGS_HPP

#include "ax_status_code.hpp"
#include <string>
#include <iostream>

namespace AxSettings
{
    class SettingsObject
    {
    private:
        SettingsObject() = delete;
        ~SettingsObject() = delete;

    public:
        static auto settings(const std::string &line) -> AxStatusCode::ApexStatusCode;
    };
}; /* namespace AxSettings */

#endif // AX_SETTINGS_HPP
