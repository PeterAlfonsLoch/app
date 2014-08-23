#pragma once


#include <wchar.h>


#include "android_graphics.h"


#include "android_process.h"
#include "android_cross_win_gdi.h"
#include "android_cross_win_file.h"
#include "android_file.h"
#include "android_file_watcher.h"
#include "android_window_android.h"
#include "android_window_impl.h"



#define ENABLE_BINRELOC
//#include "c_os_binreloc.h"



DWORD get_tick_count();




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


#ifndef ANDROID

union semun
{

   int32_t val;
   struct semid_ds * buf;
   USHORT * array;

};

#endif

CLASS_DECL_AURA DWORD GetLastError();
CLASS_DECL_AURA DWORD SetLastError(DWORD dw);


CLASS_DECL_AURA bool _istlead(int32_t ch);


oswindow GetCapture();
oswindow SetCapture(oswindow interaction_impl);
int_bool ReleaseCapture();
oswindow SetFocus(oswindow interaction_impl);
oswindow GetFocus();
oswindow GetWindow(oswindow interaction_impl, int iParentHood);
oswindow GetActiveWindow();
oswindow SetActiveWindow(oswindow interaction_impl);
int_bool DestroyWindow(oswindow interaction_impl);
oswindow GetDesktopWindow();







bool c_xstart();

extern oswindow g_oswindowDesktop;

