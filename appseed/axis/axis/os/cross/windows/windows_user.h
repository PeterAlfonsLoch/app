#pragma once


CLASS_DECL_BASE WINBOOL GetCursorPos(LPPOINT lpptCursor);

#ifndef HWND_MESSAGE

#define HWND_MESSAGE     ((oswindow)-3)

#endif

#define PostMessage  PostMessageW

CLASS_DECL_BASE int_bool WINAPI PostMessageW(oswindow oswindow,UINT Msg,WPARAM wParam,LPARAM lParam);
