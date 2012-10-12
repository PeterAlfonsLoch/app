#include "framework.h"

static DWORD m_dwLastError = 0;

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


DWORD
WINAPI
FormatMessage(
              DWORD dwFlags,
              LPCVOID lpSource,
              DWORD dwMessageId,
              DWORD dwLanguageId,
              LPSTR lpBuffer,
              DWORD nSize,
              va_list *Arguments
              )
{
    
    
    return 0;
    
    
}


VOID
WINAPI
OutputDebugStringA(
                   LPCSTR lpOutputString
                   )
{
    
    
    fprintf(stderr, "%s", lpOutputString);
    
    
}



