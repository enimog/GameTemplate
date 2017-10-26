#include "stdafx.h"
#include "Logger.h"
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include "Constants.h"
#include <filesystem>
#include <libloaderapi.h>

static log4cplus::ConfigureAndWatchThread* configurator = nullptr;
static size_t instance_count = 0;

CLogger::CLogger()
    : initializer()
{
    wchar_t buffer[MAX_PATH];
    GetModuleFileName(nullptr, buffer, MAX_PATH);
    std::experimental::filesystem::path path(buffer);
    path = path.remove_filename();
    if (configurator == nullptr && std::experimental::filesystem::exists(path.append(L"\\" + CONST_LOG_FILE_NAME)))
    {
        configurator = new log4cplus::ConfigureAndWatchThread(path);
    }
    ++instance_count;
}


CLogger::~CLogger()
{
    if (--instance_count == 0 && configurator != nullptr)
    {
        delete configurator;
        configurator = nullptr;
    }
}

void CLogger::log_trace(std::string const& context, std::wstring const & text)
{
    logger = log4cplus::Logger::getInstance(StringToolbox::StringToWide(context));
    LOG4CPLUS_TRACE(logger, text);
}

void CLogger::log_debug(std::string const& context, std::wstring const & text)
{
    logger = log4cplus::Logger::getInstance(StringToolbox::StringToWide(context));
    LOG4CPLUS_DEBUG(logger, text);
}

void CLogger::log_info(std::string const& context, std::wstring const & text)
{
    logger = log4cplus::Logger::getInstance(StringToolbox::StringToWide(context));
    LOG4CPLUS_INFO(logger, text);
}

void CLogger::log_warn(std::string const& context, std::wstring const & text)
{
    logger = log4cplus::Logger::getInstance(StringToolbox::StringToWide(context));
    LOG4CPLUS_WARN(logger, text);
}

void CLogger::log_error(std::string const& context, std::wstring const & text)
{
    logger = log4cplus::Logger::getInstance(StringToolbox::StringToWide(context));
    LOG4CPLUS_ERROR(logger, text);
}

void CLogger::log_fatal(std::string const& context, std::wstring const & text)
{
    logger = log4cplus::Logger::getInstance(StringToolbox::StringToWide(context));
    LOG4CPLUS_FATAL(logger, text);
}