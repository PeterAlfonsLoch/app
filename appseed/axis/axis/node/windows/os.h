#pragma once

//#include <shlobj.h>
//#include <Security.h>
//#include <shlobj.h>

//#include "windows_exception.h"





string get_error_message(DWORD dwError);




namespace windows
{
   

   class interaction_impl;


} // namespace windows




#include "win1.h"
#include "windows_implementation.h"
#include "windows_message_queue.h"
#include "windows_factory_exchange.h"
#include "windows_window_draw.h"
#include "windows_interaction_impl.h"

CLASS_DECL_AXIS WNDPROC __get_window_procedure();
#define __window_procedure (*__get_window_procedure())

#define NODE_WINDOW(pwnd) ((sp(::windows::interaction_impl))(pwnd))






#include "windows_print_job.h"








#include "windows_copydesk.h"





#define __set_dialog_control_id(oswindow, nID)     SetWindowLong(oswindow, GWL_ID, nID)
#define __set_dialog_control_id_(oswindow, nID)     oswindow->SetWindowLong(GWL_ID, nID)
#define __get_dialog_control_id(oswindow)         ((UINT)(WORD)::GetDlgCtrlID(oswindow))
#define __get_dialog_control_id_(oswindow)         ((UINT)(WORD)oswindow->GetDlgCtrlId())
