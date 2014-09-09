#pragma once



typedef void (__MSG_CALL ::user::interaction_impl::*__PMSGW)();
typedef void (__MSG_CALL thread::*__PMSGT)();



string get_error_message(DWORD dwError);




namespace windows
{


   class interaction_impl;


} // namespace windows



// interaction_impl creation hooking
CLASS_DECL_AXIS bool hook_window_create(::windows::interaction_impl * pwindow);
CLASS_DECL_AXIS bool unhook_window_create();
CLASS_DECL_AXIS void reset_message_cache();




#include "windows_implementation.h"
#include "windows_message_queue.h"
#include "windows_factory_exchange.h"
#include "windows_window_draw.h"
#include "windows_interaction_impl.h"

CLASS_DECL_AXIS WNDPROC __get_window_procedure();

#define NODE_WINDOW(pwnd) ((sp(::windows::interaction_impl))(pwnd))






#include "windows_print_job.h"








#include "windows_copydesk.h"





#define __set_dialog_control_id(oswindow, nID)     SetWindowLong(oswindow, GWL_ID, nID)
#define __set_dialog_control_id_(oswindow, nID)     oswindow->SetWindowLong(GWL_ID, nID)
#define __get_dialog_control_id(oswindow)         ((UINT)(WORD)::GetDlgCtrlID(oswindow))
#define __get_dialog_control_id_(oswindow)         ((UINT)(WORD)oswindow->GetDlgCtrlId())




CLASS_DECL_AXIS const char * __register_window_class(sp(::aura::application) papp,UINT nClassStyle,HCURSOR hCursor = 0,HBRUSH hbrBackground = 0,HICON hIcon = 0);

CLASS_DECL_AXIS bool __register_class(WNDCLASS* lpWndClass);


CLASS_DECL_AXIS LRESULT CALLBACK __window_procedure(oswindow oswindow,UINT nMsg,WPARAM wParam,LPARAM lParam);
CLASS_DECL_AXIS WNDPROC __get_window_procedure();
#define __window_procedure (*__get_window_procedure())
