#pragma once



#include <stdarg.h>
#include <wchar.h>


#include "c_os_http_lib.h"
#include "c_os_http.h"
#include "c_os_process.h"
#include "c_os_cross_win_gdi.h"
#include "c_os_cross_win_file.h"



#define ENABLE_BINRELOC
//#include "c_os_binreloc.h"



DWORD GetTickCount();


#define GetAValue(rgb)      (LOBYTE((rgb)>>24))
#define ARGB(a, r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)|(((DWORD)(BYTE)(a))<<24)))


#define _fileno   fileno
#define _unlink   unlink


/*
#define STATUS_WAIT_0            ((DWORD   ) 0x00000000L)
#define STATUS_ABANDONED_WAIT_0  ((DWORD   ) 0x00000080L)
#define STATUS_USER_APC          ((DWORD   ) 0x000000C0L)
#define STATUS_TIMEOUT           ((DWORD   ) 0x00000102L)
*/

#define WAIT_FAILED              ((DWORD   ) 0xFFFFFFFFL)
#define WAIT_OBJECT_0            ((DWORD   ) STATUS_WAIT_0 + 0)

#define WAIT_ABANDONED           ((DWORD   ) STATUS_ABANDONED_WAIT_0 + 0)
#define WAIT_ABANDONED_0         ((DWORD   ) STATUS_ABANDONED_WAIT_0 + 0)

#define WAIT_IO_COMPLETION                   STATUS_USER_APC

// based on Windows implementation and also a good limit for iterations with nanosleep and multiple locks in objects up to MAXIMUM_WAIT_OBJECTS in a single call
#define MAXIMUM_WAIT_OBJECTS      64




union semun
{

   int val;
   struct semid_ds * buf;
   USHORT * array;

};


void fd_ensure_file_size(int fd, int iSize);
int64_t fd_get_file_size(int fd);



CLASS_DECL_c DWORD GetLastError();
CLASS_DECL_c DWORD SetLastError(DWORD dw);
