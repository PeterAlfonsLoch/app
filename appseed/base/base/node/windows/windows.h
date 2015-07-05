#pragma once


CLASS_DECL_BASE const char * __register_window_class(::aura::application * papp,UINT nClassStyle,HCURSOR hCursor = 0,HBRUSH hbrBackground = 0,HICON hIcon = 0);

CLASS_DECL_BASE bool __register_class(WNDCLASS* lpWndClass);

CLASS_DECL_BASE LRESULT CALLBACK __window_procedure(oswindow oswindow,UINT nMsg,WPARAM wParam,LPARAM lParam);
CLASS_DECL_BASE WNDPROC __get_window_procedure();
#define __window_procedure (*__get_window_procedure())
typedef void (__MSG_CALL ::user::interaction_impl::*__PMSGW)();
typedef void (__MSG_CALL thread::*__PMSGT)();


#include "axis/node/windows/windows.h"

#include "windows_interaction_impl.h"

#include "windows_factory_exchange.h"


#include "windows_implementation.h"




