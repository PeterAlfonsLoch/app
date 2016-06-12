#pragma once

#define PostMessage  PostMessageW

CLASS_DECL_BASE int_bool PostMessageW(oswindow oswindow,UINT Msg,WPARAM wParam,LPARAM lParam);

CLASS_DECL_BASE WINBOOL GetCursorPos(LPPOINT lpptCursor);
