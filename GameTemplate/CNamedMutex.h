#pragma once


class CNamedMutex
{
public:
    /*
     * Wrapper class for mutex objects
     * mutex objects are OS specific, so this class
     * is a container for that logic.
     */
    explicit CNamedMutex(const std::wstring& name);
    ~CNamedMutex();

    /*
     * Acquire the mutex. Will wait until the mutex is released
     */
    volatile void acquire() const;

    /*
     * Release the mutex.
     */
    volatile void release() const;

private:
    /*
     * Mutex handle. Is nullptr if not defined
     */
    HANDLE m_Handle;
};

