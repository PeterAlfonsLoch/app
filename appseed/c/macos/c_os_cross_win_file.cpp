#include "framework.h"


HANDLE
WINAPI
CreateFileA(
            LPCSTR lpFileName,
            DWORD dwDesiredAccess,
            DWORD dwShareMode,
            LPSECURITY_ATTRIBUTES lpSecurityAttributes,
            DWORD dwCreationDisposition,
            DWORD dwFlagsAndAttributes,
            HANDLE hTemplateFile
            )
{
    
    FILE * pfile = fopen(lpFileName, "rw");
    
    if(pfile == NULL)
        return INVALID_HANDLE_VALUE;
    
    HANDLE handle = new win_handle;
    
    handle->m_etype = win_handle::type_file;
    handle->m_data.m_pfile = pfile;

    
    return handle;
    
    
}

DWORD
WINAPI
SetFilePointer(
               HANDLE hFile,
               LONG lDistanceToMove,
               PLONG lpDistanceToMoveHigh,
               DWORD dwMoveMethod
               )
{
    if(hFile == INVALID_HANDLE_VALUE)
        return -1;
    if(hFile->m_etype != win_handle::type_file)
        return -1;
    return fseek(hFile->m_data.m_pfile, lDistanceToMove, dwMoveMethod);
}


WINBOOL
WINAPI
WriteFile(
          HANDLE hFile,
          LPCVOID lpBuffer,
          DWORD nNumberOfBytesToWrite,
          LPDWORD lpNumberOfBytesWritten,
          LPOVERLAPPED lpOverlapped
          )
{    
    if(hFile == INVALID_HANDLE_VALUE)
        return FALSE;
    if(hFile->m_etype != win_handle::type_file)
        return FALSE;
    size_t sizeWritten = fwrite(lpBuffer, nNumberOfBytesToWrite, 1, hFile->m_data.m_pfile);
    if(lpNumberOfBytesWritten != NULL)
        *lpNumberOfBytesWritten = sizeWritten;
    return TRUE;
}

WINBOOL
WINAPI
ReadFile(
         HANDLE hFile,
         LPVOID lpBuffer,
         DWORD nNumberOfBytesToRead,
         LPDWORD lpNumberOfBytesRead,
         LPOVERLAPPED lpOverlapped
         )
{
    if(hFile == INVALID_HANDLE_VALUE)
        return FALSE;
    if(hFile->m_etype != win_handle::type_file)
        return FALSE;
    size_t sizeRead = fwrite(lpBuffer, nNumberOfBytesToRead, 1, hFile->m_data.m_pfile);
    if(lpNumberOfBytesRead != NULL)
        *lpNumberOfBytesRead = sizeRead;
    return TRUE;
}

WINBOOL
WINAPI
FlushFileBuffers(
                 HANDLE hFile
                 )
{    if(hFile == INVALID_HANDLE_VALUE)
    return FALSE;
    if(hFile->m_etype != win_handle::type_file)
        return FALSE;
    return fflush(hFile->m_data.m_pfile) == 0;    
}


WINBOOL
WINAPI
__win_CloseFile(
            HANDLE hFile
            )
{
    if(hFile == INVALID_HANDLE_VALUE)
        return FALSE;
    if(hFile->m_etype != win_handle::type_file)
        return FALSE;
    return fclose(hFile->m_data.m_pfile) != FALSE;
}

WINBOOL
WINAPI
CloseHandle(
            HANDLE hObject
            )
{
    if(hObject == INVALID_HANDLE_VALUE)
        return FALSE;
    switch(hObject->m_etype)
    {
        case win_handle::type_file:
            return __win_CloseFile(hObject);
        default:
            return FALSE;
    };
 
}



