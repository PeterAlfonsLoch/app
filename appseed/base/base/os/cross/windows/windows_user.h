#pragma once


CLASS_DECL_BASE WINBOOL GetCursorPos(LPPOINT lpptCursor);

#define HWND_MESSAGE     ((HWND)-3)

#define PostMessage  PostMessageW

CLASS_DECL_BASE int_bool WINAPI PostMessageW(oswindow oswindow,UINT Msg,WPARAM wParam,LPARAM lParam);
