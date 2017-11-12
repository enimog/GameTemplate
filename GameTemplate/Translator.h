#pragma once

#define TRANSLATE(x) Translator::translate(Translator::x)

#define TXT_KEY_TABLE \
X( TXT_KEY_SYSTEM_MESSAGEBOX_TITLE_ERROR ) \
X( TXT_KEY_SYSTEM_MESSAGEBOX_ALREADY_EXISTS )

class Translator
{
public:
    Translator() = delete;
    ~Translator() = delete;

#define X(x) x,
    enum StringKey : unsigned short
    {
        TXT_KEY_TABLE

        // This enum should always be the last
        TXT_KEY_ENUM_COUNT
    };
#undef X

    /*
    * Language
    *
    */
    enum Language : unsigned char
    {
        English,
        French,

        // This enum should always be the last
        LANGUAGE_COUNT
    };

    /*
     * Translate a string using it's key and the locale language
     * If the input key is not found for a language, will default to english
     * If the english key is not found, will return the string key
     * @param key to translate
     * @return translated string
     */
    static const wchar_t* translate( StringKey key );

    /*
    * Translate a string using it's key and a specific language
    * If the input key is not found for the language, will default to english
    * If the english key is not found, will return the string key
    * @param key to translate
    * @param language to translate
    * @return translated string
    */
    static const wchar_t* translate( StringKey key, Language lang );

    /*
     * Set the language used for translating
     * Default language set to English
     * @param lang : Language to translate
     */
    static void setLocale( Language lang);

    /*
     * Get the full list of all string key used to translate
     * This is a utilitary function to be used with a dump
     * @return vector of [line][translations]
     * Format is :
     *  key - language - language - language - ...
     *  key - language - language - language - ...
     *  key - language - language - language - ...
     *  ... - ...      - ...      - ...      - ...
     */
    static std::vector<std::vector<std::wstring>> getKeyList();

private:
    static Language m_Language;
};