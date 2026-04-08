#pragma once

#ifndef AX_STATUS_CODE_HPP
#define AX_STATUS_CODE_HPP

namespace AxStatusCode
{
    enum class ApexStatusCode
    {
        OK,         /* NO -> BOOL -> TRUE */
        NO,         /* NO -> BOOL -> FALSE */
        CONTINUE,   /* CONTINUE -> continue */
        UNEXPECTED, /* UNEXPECTED -> unexpected */
    };
}; /* namespace AxStatusCode */
#endif // AX_STATUS_CODE_HPP
