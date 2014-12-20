#pragma once


WINBOOL GetCursorPos(LPPOINT lpptCursor);

#define HWND_MESSAGE ((::oswindow_data *) (int_ptr) 1)

#define PostMessage  PostMessageW

CLASS_DECL_AXIS int_bool WINAPI PostMessageW(oswindow oswindow,UINT Msg,WPARAM wParam,LPARAM lParam);
