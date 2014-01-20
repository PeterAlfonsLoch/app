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
    usleep(dwMillis * 1000);
}



