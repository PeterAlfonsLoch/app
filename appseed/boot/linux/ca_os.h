#pragma once



#include <wchar.h>

#include "ca_os_graphics.h"
#include "ca_os_process.h"
#include "ca_os_cross_win_gdi.h"
#include "ca_os_cross_win_file.h"
#include "ca_os_file.h"
#include "ca_os_file_watcher.h"
#include "ca_os_cairo_keep.h"
#include "ca_os_window_cairo.h"



#define ENABLE_BINRELOC
//#include "c_os_binreloc.h"



DWORD get_tick_count();




#define _fileno   fileno
#define _unlink   unlink





CLASS_DECL_c DWORD GetLastError();
CLASS_DECL_c DWORD SetLastError(DWORD dw);


CLASS_DECL_c bool _istlead(int32_t ch);




bool c_xstart();

extern oswindow g_oswindowDesktop;



CLASS_DECL_c bool main_initialize();
CLASS_DECL_c bool main_finalize();
