#pragma once


#include "aura/node/windows/windows.h"





#include "windows_crypto.h"
#include "windows_axis_dir.h"
#include "windows_file_set.h"
#include "windows_axis_file_system.h"
#include "windows_ip_enum.h"
#include "windows_port_forward.h"





#include "windows_factory_exchange.h"


















namespace windows
{


   class interaction_impl;


} // namespace windows


// interaction_impl creation hooking
CLASS_DECL_AXIS bool hook_window_create(::windows::interaction_impl * pwindow);
CLASS_DECL_AXIS bool unhook_window_create();
CLASS_DECL_AXIS void reset_message_cache();


CLASS_DECL_AXIS string get_user_interaction_window_class(::user::interaction * pui);




extern CLASS_DECL_AXIS const char gen_Wnd[];           // simple child windows/controls
extern CLASS_DECL_AXIS const char gen_WndControlBar[]; // controls with gray backgrounds
extern CLASS_DECL_AXIS const char gen_WndMDIFrame[];
extern CLASS_DECL_AXIS const char gen_WndFrameOrView[];
extern CLASS_DECL_AXIS const char gen_WndOleControl[];


CLASS_DECL_AXIS void __cancel_modes(oswindow oswindow_Rcvr);
CLASS_DECL_AXIS bool __help_enabled();  // determine if ID_HELP handler exists
CLASS_DECL_AXIS bool __custom_log_font(UINT nIDS,LOGFONTW* pLogFont);
CLASS_DECL_AXIS bool __get_prop_sheet_font(string & strFace,WORD& wSize,bool bWizard);

CLASS_DECL_AXIS bool __is_combo_box_control(oswindow oswindow,UINT nStyle);
CLASS_DECL_AXIS bool __check_center_dialog(const char * lpszResource);
CLASS_DECL_AXIS bool __compare_class_name(oswindow oswindow,const char * lpszClassName);
CLASS_DECL_AXIS oswindow __child_window_from_point(oswindow,POINT);


#include "windows_message_queue.h"
#include "windows_factory_exchange.h"
CLASS_DECL_AXIS WNDPROC __get_window_procedure();

#define NODE_WINDOW(pwnd) ((sp(::windows::interaction_impl))(pwnd))

#include "windows_print_job.h"
#include "windows_copydesk.h"






#define __set_dialog_control_id(oswindow, nID)     SetWindowLong(oswindow, GWL_ID, nID)
#define __set_dialog_control_id_(oswindow, nID)     oswindow->SetWindowLong(GWL_ID, nID)
#define __get_dialog_control_id(oswindow)         ((UINT)(WORD)::GetDlgCtrlID(oswindow))
#define __get_dialog_control_id_(oswindow)         ((UINT)(WORD)oswindow->GetDlgCtrlId())



string get_error_message(DWORD dwError);





