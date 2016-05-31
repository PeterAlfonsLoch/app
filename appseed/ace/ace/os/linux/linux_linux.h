#pragma once


#include <wchar.h>


#include "linux_graphics.h"
#include "linux_process.h"
#include "linux_cross_win_gdi.h"
#include "linux_cross_win_file.h"
#include "linux_file.h"
#include "linux_file_watcher.h"
#include "linux_cross_win_gdi_internal.h"


#define ENABLE_BINRELOC



DWORD get_tick_count();




#define _fileno   fileno
#define _unlink   unlink





CLASS_DECL_ACE DWORD GetLastError();
CLASS_DECL_ACE DWORD SetLastError(DWORD dw);


CLASS_DECL_ACE bool _istlead(int32_t ch);




bool c_xstart();

extern oswindow g_oswindowDesktop;



CLASS_DECL_ACE bool main_initialize();
CLASS_DECL_ACE bool main_finalize();





#include "linux.inl"



