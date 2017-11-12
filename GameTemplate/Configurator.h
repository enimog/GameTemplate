#pragma once
#include "INIFile.h"
#include <unordered_map>

class CConfigurator
{
public:
    CConfigurator();
    ~CConfigurator();

    enum ConfigOption
    {
        // User
        USER_Username,

        // Video
        VIDEO_ResolutionX,
        VIDEO_ResolutionY,
        VIDEO_VideoMode,
        VIDEO_VSync,

        // Audio
        AUDIO_Master,
        AUDIO_Sound,
        AUDIO_Music,
        AUDIO_Environmental,

    };

    void UseDefaultConfiguration() const;

    std::wstring operator[]( ConfigOption key ) const;

private:
    File::CINIFile Config;

    static const std::unordered_map<ConfigOption, std::wstring> OptionToString;
};

