#include "stdafx.h"
#include "CSingleInstanceChecker.h"
#include "Translator.h"


CSingleInstanceChecker::CSingleInstanceChecker( std::wstring const& name )
    : unique_name( name ), 
      mutex_handle(nullptr)
{
}


CSingleInstanceChecker::~CSingleInstanceChecker()
{
    LOG_TRACE( "Closing single instance handle" );

    CloseHandle( mutex_handle );
}

bool CSingleInstanceChecker::check()
{
    size_t iButton = 0;
    mutex_handle = nullptr;
    do
    {
        CloseHandle( mutex_handle );

        mutex_handle = CreateMutex( nullptr, false, unique_name.c_str() );

        if (GetLastError() == ERROR_ALREADY_EXISTS)
        {
            iButton = MessageBox( nullptr, 
                                  TRANSLATE( TXT_KEY_SYSTEM_MESSAGEBOX_ALREADY_EXISTS ), 
                                  TRANSLATE( TXT_KEY_SYSTEM_MESSAGEBOX_TITLE_ERROR ), 
                                  MB_RETRYCANCEL + MB_ICONERROR + MB_SETFOREGROUND );
        }

        if (iButton == IDCANCEL)
        {
            LOG_FATAL("cancelling a non-unique instance");
            return false;
        }

    }
    while (iButton == IDRETRY);

    LOG_TRACE("Single instance check sucessful");

    return true;
}
