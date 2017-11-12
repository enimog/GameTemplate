#include "stdafx.h"
#include "Translator.h"
#include <map>

Translator::Language Translator::m_Language = English;

const wchar_t* translation_list[Translator::TXT_KEY_ENUM_COUNT][Translator::LANGUAGE_COUNT];

#define X(x) L###x,
const wchar_t* key_list[Translator::TXT_KEY_ENUM_COUNT] = {
    TXT_KEY_TABLE
};
#undef X

const wchar_t* Translator::translate( StringKey key )
{
    if (translation_list[key][m_Language] == nullptr)
    {
        if (translation_list[key][English] == nullptr)
        {
            LOG_ERROR(L"No translation key found for enum value %s", key_list[key]);
            return key_list[key];
        }

        return translation_list[key][English];
    }

    return translation_list[key][m_Language];
}

const wchar_t* Translator::translate( StringKey key, Language lang )
{
    if (translation_list[key][lang] == nullptr)
    {
        if (translation_list[key][English] == nullptr)
        {
            LOG_ERROR(L"No translation key found for enum value %s", key_list[key]);
            return key_list[key];
        }

        return translation_list[key][English];
    }

    return translation_list[key][lang];
}

void Translator::setLocale( Language lang )
{
    m_Language = lang;
}

std::vector<std::vector<std::wstring>> Translator::getKeyList()
{
    std::vector<std::vector<std::wstring>> m_TranslationArray( TXT_KEY_ENUM_COUNT, std::vector<std::wstring>( LANGUAGE_COUNT + 1 ) );

    for (size_t index_key = 0; index_key < TXT_KEY_ENUM_COUNT; index_key++)
    {
        m_TranslationArray[index_key][0] = key_list[index_key];

        for (size_t index_language = 0; index_language < LANGUAGE_COUNT; index_language++)
        {
            std::wstring value = translate( static_cast<StringKey>(index_key), static_cast<Language>(index_language));
            if (value != m_TranslationArray[index_key][0])
            {
                m_TranslationArray[index_key][index_language + 1] = value;
            }
        }
    }

    return m_TranslationArray;
}
