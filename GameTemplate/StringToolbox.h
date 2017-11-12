#pragma once

#include <memory>
#include <vector>

namespace Toolbox
{
    class StringToolbox
    {
    public:
        /*
         * DO NOT USE constructors or destructors.
         * This class should never be built and you should only
         * use the static methods.
         */
        StringToolbox() = delete;
        ~StringToolbox() = delete;

        static std::wstring StringToWide( std::string const& string );

        static std::string WideToString( std::wstring const& string );

        static std::vector<std::wstring> StringToolbox::Split( std::wstring const& string, std::wstring const & delimiter );
        static std::vector<std::string> StringToolbox::Split( std::string const & string, std::string const & delimiter );
        static std::vector<std::wstring> StringToolbox::Split( std::wstring const& string, wchar_t const & delimiter );
        static std::vector<std::string> StringToolbox::Split( std::string const& string, char const & delimiter );

        template<typename ... Args>
        static std::wstring Format( const std::wstring& format, Args ... args )
        {
            if (sizeof...(Args) > 0)
            {
                size_t size = std::swprintf( nullptr, 0, format.c_str(), args ... ) + 1;
                std::unique_ptr<wchar_t[]> buf( new wchar_t[size] );
                std::swprintf( buf.get(), size, format.c_str(), args ... );
                return std::wstring( buf.get(), buf.get() + size - 1 );
            }
            return format;
        }

        template<typename ... Args>
        static std::string Format( const std::string& format, Args ... args )
        {
            if (sizeof...(Args) > 0)
            {
                size_t size = sprintf_s( nullptr, 0, format.c_str(), args ... ) + 1;
                std::unique_ptr<char[]> buf( new char[size] );
                sprintf_s( buf.get(), size, format.c_str(), args ... );
                return std::string( buf.get(), buf.get() + size - 1 );
            }
            return format;
        }
    };
}
