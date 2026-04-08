#pragma once

#ifndef AX_QUERYS_HPP
#define AX_QUERYS_HPP

#include "ax_object_status_manage.hpp"
#include "ax_status_code.hpp"
#include "ax_public.hpp"
#include "ax_parser.hpp"
#include "ax_handle_system.hpp"
#include <string>

namespace AxQuerys
{
    class QuerysObject
    {
    private:
        QuerysObject() = delete;
        ~QuerysObject() = delete;

    public:
        static auto querys(const std::string &line) -> AxStatusCode::ApexStatusCode;
    };
}; /* namespace AxQuerys */

#endif // AX_QUERYS_HPP
