#pragma once

#include <log4cplus/initializer.h>
#include <log4cplus/loglevel.h>

#define LOG_TRACE(x) CLogger::log(__FILE__, __LINE__, x, log4cplus::TRACE_LOG_LEVEL)
#define LOG_DEBUG(x) CLogger::log(__FILE__, __LINE__, x, log4cplus::DEBUG_LOG_LEVEL)
#define LOG_INFO(x) CLogger::log(__FILE__, __LINE__, x, log4cplus::INFO_LOG_LEVEL)
#define LOG_WARN(x) CLogger::log(__FILE__, __LINE__, x, log4cplus::WARN_LOG_LEVEL)
#define LOG_ERROR(x) CLogger::log(__FILE__, __LINE__, x, log4cplus::ERROR_LOG_LEVEL)
#define LOG_FATAL(x) CLogger::log(__FILE__, __LINE__, x, log4cplus::FATAL_LOG_LEVEL)

class CLogger
{
public:
    CLogger();
    ~CLogger();

    /*
     * Logging function. Please do not use directly and use macro instead.
     * @Param context : Name of the context. Context with the same name will be grouped.
     * @Param line : Line number of the macro. MUST be __LINE__.
     * @Param text : custom text entered by the user that will be displayed inside the log
     * @Param LogLevel : FATAL < ERROR < WARN < INFO < DEBUG < TRACE
     */
    static void log(std::string const& context, size_t const line, std::wstring const & text, const log4cplus::LogLevel ll);

private:
    const log4cplus::Initializer initializer;

};

