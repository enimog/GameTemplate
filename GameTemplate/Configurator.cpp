#include "stdafx.h"
#include "Configurator.h"
#include "SFML/Window/WindowStyle.hpp"
#include "FileToolbox.h"

const std::unordered_map<CConfigurator::ConfigOption, std::wstring> CConfigurator::OptionToString = {
    { USER_Username , L"User" },
    { VIDEO_ResolutionX, L"ResolutionX" },
    { VIDEO_ResolutionY ,  L"ResolutionY" },
    { VIDEO_VideoMode , L"VideoMode" },
    { VIDEO_VSync , L"VSync" }
};

CConfigurator::CConfigurator() : Config( L"config.ini" )
{
    if (Toolbox::FileToolbox::Exists( L"config.ini" ))
    {
        LOG_INFO( "Using the loaded configuration" );
    }
    else
    {
        LOG_INFO( "Using the default configuration" );
        UseDefaultConfiguration();
    }
}


CConfigurator::~CConfigurator()
{
}

void CConfigurator::UseDefaultConfiguration() const
{
    LOG_TRACE("Begin creating the default configuration");

    // Clear the configuration if it existed
    Config.clear();

    // Set here user specific configuration
    Config.AppendSection( L"User" );
    Config.AppendKeyValue( L"Username", L"Mog" );

    Config.AppendEmptyLine();

    // Set here graphical options
    Config.AppendSection( L"Video" );
    Config.AppendKeyValue(L"ResolutionX", 800);
    Config.AppendKeyValue( L"ResolutionY", 600 );
    Config.AppendKeyValue( L"VideoMode", sf::Style::Default );
    Config.AppendKeyValue( L"VSync", 1 );
    Config.AppendKeyValue( L"Quality", 3 );

    Config.AppendEmptyLine();

    // Set here audio options
    Config.AppendSection( L"Audio" );
    Config.AppendKeyValue( L"Master", 100.F );
    Config.AppendKeyValue( L"SoundEffect", 100.F );
    Config.AppendKeyValue( L"Music", 100.F );
    Config.AppendKeyValue( L"Environmental", 100.F );

    Config.AppendEmptyLine();

    // Set here input mapping
    Config.AppendSection( L"Input" );
    Config.AppendKeyValue( L"A", L"A" );
    Config.AppendKeyValue( L"B", L"B" );
    Config.AppendKeyValue( L"C", L"C" );
    // ...

    LOG_TRACE( "End creating the default configuration" );
}

std::wstring CConfigurator::operator[]( ConfigOption key ) const
{
    auto iter = OptionToString.find( key );
    if (iter != OptionToString.end())
    {
        return Config[iter->second];
    }

    return std::wstring();
}
