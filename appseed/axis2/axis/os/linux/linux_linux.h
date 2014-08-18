#pragma once


#include <wchar.h>


#include "linux_graphics.h"
#include "linux_process.h"
#include "linux_cross_win_gdi.h"
#include "linux_cross_win_file.h"
#include "linux_file.h"
#include "linux_file_watcher.h"
#include "linux_window_xlib.h"
#include "linux_cross_win_gdi_internal.h"
#include "linux_windowing.h"


#define ENABLE_BINRELOC
//#include "c_os_binreloc.h"



DWORD get_tick_count();




#define _fileno   fileno
#define _unlink   unlink





CLASS_DECL_AXIS DWORD GetLastError();
CLASS_DECL_AXIS DWORD SetLastError(DWORD dw);


CLASS_DECL_AXIS bool _istlead(int32_t ch);




bool c_xstart();

extern oswindow g_oswindowDesktop;



CLASS_DECL_AXIS bool main_initialize();
CLASS_DECL_AXIS bool main_finalize();



