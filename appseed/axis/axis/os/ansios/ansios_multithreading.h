#pragma once


#if defined(LINUX) // || defined(ANDROID)

bool axis_defer_process_x_message(HTHREAD hthread,LPMESSAGE lpMsg,oswindow oswindow,bool bPeek);

#endif



#define PostMessage  PostMessageW

CLASS_DECL_AXIS int_bool WINAPI PostMessageW(oswindow oswindow,UINT Msg,WPARAM wParam,LPARAM lParam);



