#pragma once


#ifdef __cplusplus

//CLASS_DECL_AXIS string normalize_path(const char * lpcszPath);


//string key_to_char(WPARAM wparam,LPARAM lparam);

#endif

extern CLASS_DECL_AXIS int g_iMouse;

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


//CLASS_DECL_AURA bool __cdecl __is_idle_message(signal_details * pobj);
//CLASS_DECL_AURA bool __cdecl __is_idle_message(MESSAGE * pMsg);




//CLASS_DECL_AXIS int WINAPI GetSystemMetrics(int i);

CLASS_DECL_AXIS oswindow WINAPI GetFocus();
CLASS_DECL_AXIS oswindow WINAPI SetFocus(oswindow oswindow);

CLASS_DECL_AXIS oswindow WINAPI GetCapture();
CLASS_DECL_AXIS oswindow WINAPI SetCapture(oswindow oswindow);
CLASS_DECL_AXIS oswindow WINAPI ReleaseCapture();




CLASS_DECL_AXIS int_bool IsWindow(oswindow oswindow);


#define PostMessage  PostMessageW

CLASS_DECL_AXIS int_bool WINAPI PostMessageW(oswindow oswindow,UINT Msg,WPARAM wParam,LPARAM lParam);

