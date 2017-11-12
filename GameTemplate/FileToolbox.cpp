#include "stdafx.h"
#include "FileToolbox.h"
#include <fstream>
#include <algorithm>
#include <codecvt>
#include <filesystem>

std::wstring Toolbox::FileToolbox::ToAbsolutePath( std::wstring const & path )
{
    auto path_no_const( path );
    replace( path_no_const.begin(), path_no_const.end(), L'/', L'\\' );

    auto directories = StringToolbox::Split( path_no_const, L'\\' );

    // If the path doesn't begin with a root directory, append the current path
    if (!IsRoot(directories[0] + L"\\" ))
    {
        auto current_path = StringToolbox::Split( GetCurrentPath(), L'\\' );
        current_path.insert( current_path.end(), directories.begin(), directories.end() );
        directories = current_path;
    }

    // replace .. and ., and rebuild the path
    std::wstring result = L"";
    for (size_t index = 0; index < directories.size(); index++)
    {
        if (directories[index].length() > 0 && directories[index].compare(L".") != 0)
        {
            if (directories[index].compare( L".." ) == 0)
            {
                if (!IsRoot( directories[index] + L"\\" ))
                {
                    auto test = result.substr( 0, result.find_last_of( L'\\' ) );
                    auto test2 = test.substr( 0, test.find_last_of( L'\\' ) );
                    result = test2 + L'\\';
                }
            }
            else
            {
                result += directories[index];

                if (index + 1 < directories.size())
                {
                    result += L'\\';
                }
            }
        }
    }

    return result;
}

std::wstring Toolbox::FileToolbox::SetExtension( std::wstring const & path, std::wstring const & ext )
{
    std::wstring result;

    if (path.find(L'.') != std::wstring::npos)
    {
        auto pos = path.find_last_of( L'.' );
        auto without_ext = path.substr( 0, pos );
        result = without_ext + L'.' + ext;
    }
    // There is no extension, so we simply append it
    else
    {
        result = path + L'.' + ext;
    }

    return result;
}

void Toolbox::FileToolbox::Write( std::wstring const & file, std::vector<std::wstring> content, bool append )
{
    FILE* file_handle = nullptr;
    size_t err = 0;

    if (append)
    {
        err = _wfopen_s( &file_handle, file.c_str(), L"a, ccs=UNICODE" );
    }
    else
    {
        err = _wfopen_s( &file_handle, file.c_str(), L"w, ccs=UNICODE" );
    }

    if (err)
    {
        LOG_FATAL(L"Could not write to file %s", file.c_str() );
        return;
    }

    for (auto& line : content)
    {
        fputws( (line + L'\n').c_str(), file_handle );
    }

    fclose( file_handle );
}

std::vector<std::wstring> Toolbox::FileToolbox::Read( std::wstring const & file )
{
    std::vector<std::wstring> result;

    std::wifstream infile(file, std::ios::binary );
    infile.imbue( std::locale( infile.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::consume_header> ) );
    std::wstring line = L"";
    for (wchar_t c; infile.get( c ); )
    {
        if (c == L'\n')
        {
            result.push_back( line );
            line = L"";
        }
        else if (c != L'\r')
        {
            line += c;
        }
    }

    if (line.size() > 0)
    {
        result.push_back( line );
    }

    return result;
}

bool Toolbox::FileToolbox::IsRoot( std::wstring const & path )
{
    wchar_t szLogicalDrives[MAX_PATH];
    auto dwResult = GetLogicalDriveStrings( MAX_PATH, szLogicalDrives );

    if (dwResult > 0 && dwResult <= MAX_PATH)
    {
        auto* szSingleDrive = szLogicalDrives;
        while (*szSingleDrive)
        {
            if (path.compare( szSingleDrive ) == 0)
            {
                return true;
            }

            // get the next drive
            szSingleDrive += wcslen( szSingleDrive ) + 1;
        }
    }

    return false;
}

std::wstring Toolbox::FileToolbox::GetCurrentPath()
{
    wchar_t buffer[MAX_PATH];
    GetModuleFileName( nullptr, buffer, MAX_PATH );
    auto pos = std::wstring( buffer ).find_last_of( L"\\/" );
    return std::wstring( buffer ).substr( 0, pos );
}

std::wstring Toolbox::FileToolbox::GetFileName( std::wstring const& path )
{
    auto result( path );
    replace( result.begin(), result.end(), L'/', L'\\' );

    return StringToolbox::Split( result, L'\\' ).back();
}

std::wstring Toolbox::FileToolbox::GetFolder( std::wstring const & path )
{
    const auto tmp( ToAbsolutePath( path ) );

    return tmp.substr(0, tmp.find_last_of(L"\\/" ));
}

bool Toolbox::FileToolbox::Exists( std::wstring const & path )
{
    return std::experimental::filesystem::exists( ToAbsolutePath(path) );
}
