#include "ax_multi_language_width.hpp"

/**
 * @brief 获取字符串的适应显示宽度
 *
 * @param str 输入字符串
 * @return int 字符串的适应显示宽度
 */
auto AxMultiLanguageWidth::MultiLanguageWidthObject::getAdaptationDisplayWidth(const std::string &str) -> int
{
    int width = 0;
    for (size_t i = 0; i < str.size();)
    {
        unsigned char c = str[i];
        if (c >= 0x80)
        {
            width += 2;
            if ((c & 0xF0) == 0xF0)
                i += 4;
            else if ((c & 0xE0) == 0xE0)
                i += 3;
            else if ((c & 0xC0) == 0xC0)
                i += 2;
            else
                i++;
        }
        else
        {
            width += 1;
            i++;
        }
    }
    return width;
}
