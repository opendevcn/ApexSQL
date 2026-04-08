#pragma once

#ifndef AX_MULTI_LANGUAGE_WIDTH_HPP
#define AX_MULTI_LANGUAGE_WIDTH_HPP

#include <string>

namespace AxMultiLanguageWidth
{
    class MultiLanguageWidthObject
    {
    private:
        MultiLanguageWidthObject() = delete;
        ~MultiLanguageWidthObject() = delete;

    public:
        static auto getAdaptationDisplayWidth(const std::string &str) -> int;
    };
}; /* namespace AxMultiLanguageWidth */

#endif // AX_MULTI_LANGUAGE_WIDTH_HPP
