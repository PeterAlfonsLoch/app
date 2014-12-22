#pragma once

CLASS_DECL_BASE string get_user_interaction_window_class(::user::interaction * pui);




extern CLASS_DECL_BASE const char gen_Wnd[];           // simple child windows/controls
extern CLASS_DECL_BASE const char gen_WndControlBar[]; // controls with gray backgrounds
extern CLASS_DECL_BASE const char gen_WndMDIFrame[];
extern CLASS_DECL_BASE const char gen_WndFrameOrView[];
extern CLASS_DECL_BASE const char gen_WndOleControl[];


CLASS_DECL_BASE void __cancel_modes(oswindow oswindow_Rcvr);
CLASS_DECL_BASE bool __help_enabled();  // determine if ID_HELP handler exists
CLASS_DECL_BASE bool __custom_log_font(UINT nIDS, LOGFONTW* pLogFont);
CLASS_DECL_BASE bool __get_prop_sheet_font(string & strFace, WORD& wSize, bool bWizard);

CLASS_DECL_BASE bool __is_combo_box_control(oswindow oswindow, UINT nStyle);
CLASS_DECL_BASE bool __check_center_dialog(const char * lpszResource);
CLASS_DECL_BASE bool __compare_class_name(oswindow oswindow, const char * lpszClassName);
CLASS_DECL_BASE oswindow __child_window_from_point(oswindow, POINT);

