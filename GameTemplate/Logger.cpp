#include "stdafx.h"
#include "Logger.h"
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include "Constants.h"
#include <filesystem>
#include <libloaderapi.h>

static log4cplus::ConfigureAndWatchThread* configurator = nullptr;
static CLogger PrivateImpl;

CLogger::CLogger() : initializer()
{
}


CLogger::~CLogger()
{
    if (configurator != nullptr)
    {
        delete configurator;
        configurator = nullptr;
    }
}

void CLogger::log(std::string const& context, size_t const line, std::wstring const & text, const log4cplus::LogLevel ll)
{
    wchar_t buffer[MAX_PATH];
    GetModuleFileName( nullptr, buffer, MAX_PATH );
    std::experimental::filesystem::path path( buffer );
    path = path.remove_filename();

    if (configurator == nullptr && std::experimental::filesystem::exists( path.append( L"\\" + CONST_LOG_FILE_NAME ) ))
    {
        configurator = new log4cplus::ConfigureAndWatchThread( path );
    }

    if (configurator != nullptr)
    {
        auto logger = log4cplus::Logger::getInstance( StringToolbox::StringToWide( context ) );
        auto format = L"Line number " + std::to_wstring( line ) + L" : " + text;

        switch (ll)
        {
        case log4cplus::FATAL_LOG_LEVEL:
            LOG4CPLUS_FATAL( logger, format );
            break;
        case log4cplus::ERROR_LOG_LEVEL:
            LOG4CPLUS_ERROR( logger, format );
            break;
        case log4cplus::WARN_LOG_LEVEL:
            LOG4CPLUS_WARN( logger, format );
            break;
        case log4cplus::INFO_LOG_LEVEL:
            LOG4CPLUS_INFO( logger, format );
            break;
        case log4cplus::DEBUG_LOG_LEVEL:
            LOG4CPLUS_DEBUG( logger, format );
            break;
        case log4cplus::TRACE_LOG_LEVEL:
            LOG4CPLUS_TRACE( logger, format );
            break;
        default:
            break;
        }
    }
}