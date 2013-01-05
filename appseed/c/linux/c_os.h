#pragma once



#include <wchar.h>

#include "c_os_graphics.h"
#include "c_os_http_lib.h"
#include "c_os_http.h"
#include "c_os_process.h"
#include "c_os_cross_win_gdi.h"
#include "c_os_cross_win_file.h"
#include "c_os_file.h"
#include "c_os_file_watcher.h"



#define ENABLE_BINRELOC
//#include "c_os_binreloc.h"



DWORD GetTickCount();




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

   int32_t val;
   struct semid_ds * buf;
   USHORT * array;

};



CLASS_DECL_c DWORD GetLastError();
CLASS_DECL_c DWORD SetLastError(DWORD dw);


CLASS_DECL_c bool _istlead(int32_t ch);
