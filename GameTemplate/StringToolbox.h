#pragma once
class StringToolbox
{
public:
    StringToolbox() = delete;
    ~StringToolbox() = delete;

    static std::wstring StringToWide(std::string const& string);
    static std::string WideToString(std::wstring const& string);
};

