#include "framework.h"
#include <stdlib.h>
#include <string.h>


DWORD
WINAPI
GetTempPathA(
    DWORD nBufferLength,
    LPSTR lpBuffer
    )
{

    const char * ptmpdir = getenv("TMPDIR");

    if(ptmpdir != NULL && *ptmpdir != '\0')
    {
        strncpy(lpBuffer, ptmpdir, MIN(nBufferLength, strlen(ptmpdir) + 1));
        return (DWORD) strlen(ptmpdir);
    }

    ptmpdir = P_tmpdir;

    if(ptmpdir != NULL && *ptmpdir != '\0')
    {
        strncpy(lpBuffer, ptmpdir, MIN(nBufferLength, strlen(ptmpdir) + 1));
        return (DWORD) strlen(ptmpdir);
    }

    strncpy(lpBuffer, "/tmp", MIN(nBufferLength, 5));
    return 5;


}

