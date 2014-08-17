#include "framework.h"


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
    fflush(stderr);
    //printf("%s", lpOutputString);


}




VOID
WINAPI
OutputDebugStringW(
                   LPCWSTR lpOutputString
                   )
{


    OutputDebugStringA(string(lpOutputString));


}



