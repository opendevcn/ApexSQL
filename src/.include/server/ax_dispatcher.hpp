#pragma once

#ifndef AX_DISPATCHER_HPP
#define AX_DISPATCHER_HPP

#include "ax_status_code.hpp"
#include <string>

namespace AxDispatcher
{
    class DispatcherObject
    {
    private:
        DispatcherObject() = delete;
        ~DispatcherObject() = delete;

    public:
        static auto apexDispatcher(const std::string &line) -> AxStatusCode::ApexStatusCode;
    };
}; /* namespace AxDispatcher */

#endif // AX_DISPATCHER_HPP
