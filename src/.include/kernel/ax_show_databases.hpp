#pragma once

#ifndef AX_SHOW_DATABASES_HPP
#define AX_SHOW_DATABASES_HPP

namespace AxShowDatabases
{
    class ShowDatabasesObject
    {
    private:
        ShowDatabasesObject() = delete;
        ~ShowDatabasesObject() = delete;

    public:
        static auto showDatabases() -> void;
    };
}; /* namespace AxShowDatabases */

#endif // AX_SHOW_DATABASES_HPP
