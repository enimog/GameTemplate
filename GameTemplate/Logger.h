#pragma once

#include <log4cplus/logger.h>
#include <log4cplus/initializer.h>
#include <log4cplus/configurator.h>
#include <log4cplus/loggingmacros.h>
#include "StringToolbox.h"
#include <filesystem>

#define LOG_TRACE(x) log_trace(typeid(*this).name(), L"Line number " + std::to_wstring(__LINE__) + L" : " + x)
#define LOG_DEBUG(x) log_debug(typeid(*this).name(), L"Line number " + std::to_wstring(__LINE__) + L" : " + x)
#define LOG_INFO(x) log_info(typeid(*this).name(), L"Line number " + std::to_wstring(__LINE__) + L" : " + x)
#define LOG_WARN(x) log_warn(typeid(*this).name(), L"Line number " + std::to_wstring(__LINE__) + L" : " + x)
#define LOG_ERROR(x) log_error(typeid(*this).name(), L"Line number " + std::to_wstring(__LINE__) + L" : " + x)
#define LOG_FATAL(x) log_fatal(typeid(*this).name(), L"Line number " + std::to_wstring(__LINE__) + L" : " + x)

class CLogger
{
public:
    CLogger();
    ~CLogger();

protected:
    void log_trace(std::string const& context, std::wstring const & text);
    void log_debug(std::string const& context, std::wstring const & text);
    void log_info(std::string const& context, std::wstring const & text);
    void log_warn(std::string const& context, std::wstring const& text);
    void log_error(std::string const& context, std::wstring const & text);
    void log_fatal(std::string const& context, std::wstring const & text);

private:
    log4cplus::Initializer initializer;
    log4cplus::Logger logger;

};

