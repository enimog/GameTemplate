#include "stdafx.h"
#include "CNamedMutex.h"


CNamedMutex::CNamedMutex( const std::wstring& name )
{
    m_Handle = CreateMutex( nullptr, false, std::to_wstring( std::hash<std::wstring>{}(name) ).c_str() );

    if (m_Handle == nullptr)
    {
        LOG_ERROR(L"CreateMutex error: %d", GetLastError());
    }
}

CNamedMutex::~CNamedMutex()
{
    CloseHandle( m_Handle );
}

volatile void CNamedMutex::acquire() const
{
    WaitForSingleObject( m_Handle, INFINITE );
}

volatile void CNamedMutex::release() const
{
    ReleaseMutex( m_Handle );
}
