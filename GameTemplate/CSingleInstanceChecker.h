#pragma once
class CSingleInstanceChecker
{
public:
    explicit CSingleInstanceChecker(std::wstring const& unique_name);
    ~CSingleInstanceChecker();

    bool check();

private:
    const std::wstring unique_name;
    HANDLE mutex_handle;
};

