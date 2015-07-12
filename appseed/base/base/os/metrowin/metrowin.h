#pragma once


#ifdef __cplusplus

//CLASS_DECL_BASE string normalize_path(const char * lpcszPath);


//string key_to_char(WPARAM wparam,LPARAM lparam);

#endif

extern CLASS_DECL_BASE int g_iMouse;

#define GW_HWNDFIRST        0
#define GW_HWNDLAST         1
#define GW_HWNDNEXT         2
#define GW_HWNDPREV         3
#define GW_OWNER            4
#define GW_CHILD            5
#if(WINVER <= 0x0400)
#define GW_MAX              5
#else
#define GW_ENABLEDPOPUP     6
#define GW_MAX              6
#endif


//CLASS_DECL_BASE bool __cdecl __is_idle_message(signal_details * pobj);
//CLASS_DECL_BASE bool __cdecl __is_idle_message(MESSAGE * pMsg);


CLASS_DECL_BASE oswindow WINAPI GetFocus();
CLASS_DECL_BASE oswindow WINAPI SetFocus(oswindow oswindow);

CLASS_DECL_BASE oswindow WINAPI GetCapture();
CLASS_DECL_BASE oswindow WINAPI SetCapture(oswindow oswindow);
CLASS_DECL_BASE oswindow WINAPI ReleaseCapture();

CLASS_DECL_BASE oswindow WINAPI GetActiveWindow();
CLASS_DECL_BASE oswindow WINAPI SetActiveWindow(oswindow oswindow);



CLASS_DECL_BASE int_bool IsWindow(oswindow oswindow);


//CLASS_DECL_BASE int WINAPI GetSystemMetrics(int i);



#include "base/graphics/graphics_window_graphics.h"
//#include "metrowin_gdi_winrt.h"

#include "metrowin_window_impl.h"