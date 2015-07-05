#include "framework.h"

thread_int_ptr < DWORD > m_dwLastError;

DWORD GetLastError()
{
    return m_dwLastError;
}

DWORD SetLastError(DWORD dwLastError)
{
    m_dwLastError = dwLastError;
   return m_dwLastError;
}

void Sleep(DWORD dwMillis)
{
    timespec ts;
    ts.tv_sec = dwMillis / 1000;
    ts.tv_nsec = (dwMillis % 1000) * 1000 * 1000;
    timespec tsRem;
    nanosleep(&ts, &tsRem);
}



