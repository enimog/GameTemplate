#include "stdafx.h"
#include "StringToolbox.h"
#include <locale>
#include <codecvt>

std::wstring StringToolbox::StringToWide(std::string const & string)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(string);
}

std::string StringToolbox::WideToString(std::wstring const & string)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.to_bytes(string);
}
