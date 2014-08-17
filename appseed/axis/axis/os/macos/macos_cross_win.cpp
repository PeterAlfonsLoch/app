#include "framework.h"

__thread DWORD m_dwLastError = 0;

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



