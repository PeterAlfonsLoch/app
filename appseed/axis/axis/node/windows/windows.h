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








CLASS_DECL_AXIS void __cancel_modes(oswindow oswindow_Rcvr);
CLASS_DECL_AXIS bool __help_enabled();  // determine if ID_HELP handler exists
CLASS_DECL_AXIS bool __custom_log_font(UINT nIDS,LOGFONTW* pLogFont);
CLASS_DECL_AXIS bool __get_prop_sheet_font(string & strFace,WORD& wSize,bool bWizard);



//#include "windows_message_queue.h"
#include "windows_factory_exchange.h"

#define NODE_WINDOW(pwnd) ((sp(::windows::interaction_impl))(pwnd))

#include "windows_print_job.h"
#include "windows_copydesk.h"






#define __set_dialog_control_id(oswindow, nID)     SetWindowLong(oswindow, GWL_ID, nID)
#define __set_dialog_control_id_(oswindow, nID)     oswindow->SetWindowLong(GWL_ID, nID)
#define __get_dialog_control_id(oswindow)         ((UINT)(WORD)::GetDlgCtrlID(oswindow))
#define __get_dialog_control_id_(oswindow)         ((UINT)(WORD)oswindow->GetDlgCtrlId())



string get_error_message(DWORD dwError);





