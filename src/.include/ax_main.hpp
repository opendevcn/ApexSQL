#pragma once

#ifndef AX_MAIN_HPP
#define AX_MAIN_HPP

#include <iostream>
#include <string>

namespace AxMain
{
    class MainObject
    {
    private:
        MainObject() = delete;
        ~MainObject() = delete;

    public:
        static auto initApexSQL() -> void;
    };
}; /* namespace AxMain */

#endif // AX_MAIN_HPP
