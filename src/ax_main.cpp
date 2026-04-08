#include "ax_handle_system.hpp"
#include "ax_main.hpp"
#include "ax_dispatcher.hpp"

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <io.h>
#else
#include <unistd.h>
#endif

namespace _AxMain
{
    class _MainObject
    {
    private:
        _MainObject() = delete;
        ~_MainObject() = delete;

    public:
        static auto _multiStatementParsing(const std::string &line, bool &ref_result) -> void;
        static auto _inspectPlatform() -> int;
        static auto _inspectRedirect() -> int;
    };

    auto _MainObject::_multiStatementParsing(const std::string &line, bool &ref_result) -> void
    {
        std::string single_statement_line;
        for (auto &c : line)
        {
            if (c == ';')
            {
                AxHandleSystem::HandleSystemObject::strip(single_statement_line);
                if (AxStatusCode::ApexStatusCode::NO == AxDispatcher::DispatcherObject::apexDispatcher(single_statement_line))
                {
                    ref_result = false;
                    return;
                }
                single_statement_line += c;
                single_statement_line.clear();
            }
            else
            {
                single_statement_line += c;
            }
        }

        if (!single_statement_line.empty())
        {
            if (single_statement_line.back() == ';')
            {
                single_statement_line.pop_back();
            }
            if (single_statement_line.empty())
            {
                ref_result = false;
            }
            AxHandleSystem::HandleSystemObject::strip(single_statement_line);
            if (AxStatusCode::ApexStatusCode::NO == AxDispatcher::DispatcherObject::apexDispatcher(single_statement_line))
            {
                single_statement_line.clear();
                ref_result = false;
            }
            single_statement_line.clear();
        }
    }

    /* -1: unknown platform, 0: windows, 1: linux, 2: macos */
    auto _MainObject::_inspectPlatform() -> int
    {
#if defined(_WIN32) || defined(_WIN64)
        return 0;
#elif defined(__linux__)
        return 1;
#elif defined(__APPLE__)
        return 2;
#endif
        return -1;
    }

    /* -1: unknown redirect, 0: interactive mode, 1: redirect to file */
    auto _MainObject::_inspectRedirect() -> int
    {
#if defined(_WIN32) || defined(_WIN64)
        return _isatty(_fileno(stdin)) ? 0 : 1;
#elif defined(__linux__) || defined(__APPLE__)
        return isatty(0) ? 0 : 1;
#endif
        return -1;
    }
}

auto AxMain::MainObject::initApexSQL() -> void
{
    const char delimiter{';'};
    bool result{true};

    while (true)
    {
        std::string line;
        if (_AxMain::_MainObject::_inspectRedirect() == 0)
        {
            std::cout << "ApexSQL> ";
        }
        if (!std::getline(std::cin, line))
        {
            break;
        }

        AxHandleSystem::HandleSystemObject::lower(line);
        AxHandleSystem::HandleSystemObject::strip(line);

        _AxMain::_MainObject::_multiStatementParsing(line, result);
        if (!result)
        {
            break;
        }
    }
}

int main()
{
#if defined(_WIN32) || defined(_WIN64)
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    AxMain::MainObject::initApexSQL();
    return 0;
}
