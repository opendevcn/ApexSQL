#pragma once

#ifndef AX_HELPS_HPP
#define AX_HELPS_HPP

#include "ax_status_code.hpp"
#include <string>
#include <iostream>

namespace AxHelps
{
    class HelpsObject
    {
    private:
        HelpsObject() = delete;
        ~HelpsObject() = delete;

    public:
        static auto helps(const std::string &line) -> AxStatusCode::ApexStatusCode;
    };
}; /* namespace AxHelps */

#endif // AX_HELPS_HPP
