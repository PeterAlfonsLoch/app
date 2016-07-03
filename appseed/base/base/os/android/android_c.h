#pragma once


#include "axis/os/android/android.h"






struct hthread;






struct oswindow_data;






bool IsChild(oswindow oswindowParent, ::oswindow oswindowcandidateChildOrDescendant);
oswindow GetParent(::oswindow oswindow);
oswindow SetParent(::oswindow oswindow, ::oswindow oswindowNewParent);
bool ShowWindow(::oswindow oswindow, int32_t nCmdShow);
LONG GetWindowLongA(::oswindow oswindow, int32_t nIndex);
LONG SetWindowLongA(::oswindow oswindow, int32_t nIndex, LONG l);
bool ClientToScreen(::oswindow oswindow, LPPOINT lppoint);
bool ScreenToClient(::oswindow oswindow, LPPOINT lppoint);
int32_t IsIconic(::oswindow oswindow);
int32_t IsWindowVisible(::oswindow oswindow);
void on_post_nc_destroy(::oswindow oswindow);
bool is_message_only_window(::oswindow oswindow);

#define GetWindowLong GetWindowLongA
#define SetWindowLong SetWindowLongA



CLASS_DECL_AURA bool IsWindow(oswindow oswindow);






