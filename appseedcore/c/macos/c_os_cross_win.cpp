#include "StdAfx.h"

static DWORD m_dwLastError = 0;

DWORD GetLastError()
{
    return m_dwLastError;
}

void SetLastError(DWORD dwLastError)
{
    m_dwLastError = dwLastError;
}

void Sleep(DWORD dwMillis)
{
    usleep(dwMillis * 1000);
}