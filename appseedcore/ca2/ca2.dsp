# Microsoft Developer Studio Project File - Name="ca2" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ca2 - Win32 basis
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ca2.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ca2.mak" CFG="ca2 - Win32 basis"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ca2 - Win32 basis" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe
# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "basis"
# PROP BASE Intermediate_Dir "basis"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../../stage/vc6/"
# PROP Intermediate_Dir "../../../time/intermediate/vc6/ca2"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CA2_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /GR /GX /Zi /Od /I "." /D "VC6" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_AFXDLL" /D "_CA_DLL" /D "_AFX_CORE_IMPL" /D "_AFX_OLE_IMPL" /D "_AFX_DB_IMPL" /D "_AFX_NET_IMPL" /D "_AFX_NOFORCE_LIBS" /D "_AFX_ENABLE_INLINES" /D "_CRT_SECURE_NO_WARNINGS" /FD /GZ /Zm1024 /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x416 /d "_DEBUG"
# ADD RSC /l 0x416 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /debug /machine:I386 /pdbtype:sept
# Begin Target

# Name "ca2 - Win32 basis"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "radix Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\radix\afxcrit.cpp
# End Source File
# Begin Source File

SOURCE=.\radix\afxdbcs.cpp
# End Source File
# Begin Source File

SOURCE=.\radix\allocation.cpp
# End Source File
# Begin Source File

SOURCE=.\radix\allocator.cpp
# End Source File
# Begin Source File

SOURCE=.\radix\application.cpp
# End Source File
# Begin Source File

SOURCE=.\radix\assert.cpp
# End Source File
# Begin Source File

SOURCE=.\radix\auxdata.cpp
# End Source File
# Begin Source File

SOURCE=.\radix\base_object.cpp
# End Source File
# Begin Source File

SOURCE=.\radix\bergedge_application.cpp
# End Source File
# Begin Source File

SOURCE=.\radix\bergedge_object.cpp
# End Source File
# Begin Source File

SOURCE=.\radix\BSTR.CPP
# End Source File
# Begin Source File

SOURCE=.\radix\cmdtarg.cpp
# End Source File
# Begin Source File

SOURCE=.\radix\command_target.cpp
# End Source File
# Begin Source File

SOURCE=.\radix\composite.cpp
# End Source File
# Begin Source File

SOURCE=.\radix\Constraint.cpp
# End Source File
# Begin Source File

SOURCE=.\radix\contact_list.cpp
# End Source File
# Begin Source File

SOURCE=.\radix\datetime_value.cpp
# End Source File
# Begin Source File

SOURCE=.\radix\DispatchPtrArray.cpp
# End Source File
# Begin Source File

SOURCE=.\radix\dllinit.cpp
# End Source File
# Begin Source File

SOURCE=.\radix\Externs.cpp
# End Source File
# Begin Source File

SOURCE=.\radix\factory.cpp
# End Source File
# Begin Source File

SOURCE=.\radix\fixed_alloc.cpp
# End Source File
# Begin Source File

SOURCE=.\radix\Flags.cpp
# End Source File
# Begin Source File

SOURCE=.\radix\id.cpp
# End Source File
# Begin Source File

SOURCE=.\radix\install.cpp
# End Source File
# Begin Source File

SOURCE=.\radix\language_string.cpp
# End Source File
# Begin Source File

SOURCE=.\radix\LoadNSave.cpp
# End Source File
# Begin Source File

SOURCE=.\radix\machine_event_central.cpp
# End Source File
# Begin Source File

SOURCE=.\radix\PcreUtil.cpp
# End Source File
# Begin Source File

SOURCE=.\radix\pipe.cpp
# End Source File
# Begin Source File

SOURCE=.\radix\plex.cpp
# End Source File
# Begin Source File

SOURCE=.\radix\PushingRoutingFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\radix\radix_html_file.cpp
# End Source File
# Begin Source File

SOURCE=.\radix\rawdllmainproxy.c
# End Source File
# Begin Source File

SOURCE=.\radix\service.cpp
# End Source File
# Begin Source File

SOURCE=.\radix\strcore.cpp
# End Source File
# Begin Source File

SOURCE=.\radix\StringUtil.cpp
# End Source File
# Begin Source File

SOURCE=.\radix\system.cpp
# End Source File
# Begin Source File

SOURCE=.\radix\thread.cpp
# End Source File
# Begin Source File

SOURCE=.\radix\timecore.cpp
# End Source File
# Begin Source File

SOURCE=.\radix\user.cpp
# End Source File
# Begin Source File

SOURCE=.\radix\userset.cpp
# End Source File
# Begin Source File

SOURCE=.\radix\util.cpp
# End Source File
# Begin Source File

SOURCE=.\radix\Util1.cpp
# End Source File
# Begin Source File

SOURCE=.\radix\validadd.cpp
# End Source File
# Begin Source File

SOURCE=.\radix\win2.cpp
# End Source File
# Begin Source File

SOURCE=.\radix\win_registry.cpp
# End Source File
# Begin Source File

SOURCE=.\radix\winstr.cpp
# End Source File
# End Group
# Begin Group "ca Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ca\ca_application.cpp
# End Source File
# Begin Source File

SOURCE=.\ca\ca_application_interface.cpp
# End Source File
# Begin Source File

SOURCE=.\ca\ca_bitmap.cpp
# End Source File
# Begin Source File

SOURCE=.\ca\ca_brush.cpp
# End Source File
# Begin Source File

SOURCE=.\ca\ca_ca.cpp
# End Source File
# Begin Source File

SOURCE=.\ca\ca_dib.cpp
# End Source File
# Begin Source File

SOURCE=.\ca\ca_dir.cpp
# End Source File
# Begin Source File

SOURCE=.\ca\ca_draw_dib.cpp
# End Source File
# Begin Source File

SOURCE=.\ca\ca_exception.cpp
# End Source File
# Begin Source File

SOURCE=.\ca\ca_font.cpp
# End Source File
# Begin Source File

SOURCE=.\ca\ca_graphics.cpp
# End Source File
# Begin Source File

SOURCE=.\ca\ca_graphics_object.cpp
# End Source File
# Begin Source File

SOURCE=.\ca\ca_lock.cpp
# End Source File
# Begin Source File

SOURCE=.\ca\ca_log.cpp
# End Source File
# Begin Source File

SOURCE=.\ca\ca_message_window.cpp
# End Source File
# Begin Source File

SOURCE=.\ca\ca_object.cpp
# End Source File
# Begin Source File

SOURCE=.\ca\ca_osi.cpp
# End Source File
# Begin Source File

SOURCE=.\ca\ca_palette.cpp
# End Source File
# Begin Source File

SOURCE=.\ca\ca_pen.cpp
# End Source File
# Begin Source File

SOURCE=.\ca\ca_profiler.cpp
# End Source File
# Begin Source File

SOURCE=.\ca\ca_rgn.cpp
# End Source File
# Begin Source File

SOURCE=.\ca\ca_thread.cpp
# End Source File
# Begin Source File

SOURCE=.\ca\ca_window.cpp
# End Source File
# Begin Source File

SOURCE=.\ca\ca_window_draw.cpp
# End Source File
# Begin Source File

SOURCE=.\ca\type_info.cpp
# End Source File
# End Group
# Begin Group "ca2 Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ca2\ca2_application.cpp
# End Source File
# Begin Source File

SOURCE=.\ca2\ca2_datetime.cpp
# End Source File
# Begin Source File

SOURCE=.\ca2\ca2_file.cpp
# End Source File
# Begin Source File

SOURCE=.\ca2\ca2_file_system.cpp
# End Source File
# Begin Source File

SOURCE=.\ca2\ca2_html.cpp
# End Source File
# Begin Source File

SOURCE=.\ca2\ca2_log.cpp
# End Source File
# Begin Source File

SOURCE=.\ca2\ca2_net.cpp
# End Source File
# Begin Source File

SOURCE=.\ca2\ca2_process.cpp
# End Source File
# Begin Source File

SOURCE=.\ca2\ca2_stra.cpp
# End Source File
# Begin Source File

SOURCE=.\ca2\ca2_url.cpp
# End Source File
# Begin Source File

SOURCE=.\ca2\ca2_url_domain.cpp
# End Source File
# Begin Source File

SOURCE=.\ca2\socket_address.cpp
# End Source File
# End Group
# Begin Group "template Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\template\allocate.cpp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\template\template_base.cpp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\template\template_debug.cpp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\template\template_memory.cpp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\template\template_time.cpp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\template\template_trace.cpp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\template\template_trace_module_manager.cpp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "collection Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\collection\2DArray.cpp
# End Source File
# Begin Source File

SOURCE=.\collection\array.cpp
# End Source File
# Begin Source File

SOURCE=.\collection\array_app_copy.cpp
# End Source File
# Begin Source File

SOURCE=.\collection\array_ptr.cpp
# End Source File
# Begin Source File

SOURCE=.\collection\array_ptr_alloc.cpp
# End Source File
# Begin Source File

SOURCE=.\collection\array_ptr_copy.cpp
# End Source File
# Begin Source File

SOURCE=.\collection\bit_array.cpp
# End Source File
# Begin Source File

SOURCE=.\collection\class_sort_array.cpp
# End Source File
# Begin Source File

SOURCE=.\collection\collection_numeric_array.cpp
# End Source File
# Begin Source File

SOURCE=.\collection\comparable_array.cpp
# End Source File
# Begin Source File

SOURCE=.\collection\key_sort_array.cpp
# End Source File
# Begin Source File

SOURCE=.\collection\list_o.cpp
# End Source File
# Begin Source File

SOURCE=.\collection\list_p.cpp
# End Source File
# Begin Source File

SOURCE=.\collection\list_s.cpp
# End Source File
# Begin Source File

SOURCE=.\collection\map_pp.cpp
# End Source File
# Begin Source File

SOURCE=.\collection\map_pw.cpp
# End Source File
# Begin Source File

SOURCE=.\collection\map_so.cpp
# End Source File
# Begin Source File

SOURCE=.\collection\map_sp.cpp
# End Source File
# Begin Source File

SOURCE=.\collection\map_ss.cpp
# End Source File
# Begin Source File

SOURCE=.\collection\map_wo.cpp
# End Source File
# Begin Source File

SOURCE=.\collection\map_wp.cpp
# End Source File
# Begin Source File

SOURCE=.\collection\point_array.cpp
# End Source File
# Begin Source File

SOURCE=.\collection\rect_array.cpp
# End Source File
# Begin Source File

SOURCE=.\collection\simple_list.cpp
# End Source File
# Begin Source File

SOURCE=.\collection\sort.cpp
# End Source File
# Begin Source File

SOURCE=.\collection\string_array.cpp
# End Source File
# Begin Source File

SOURCE=.\collection\string_to_string_map.cpp
# End Source File
# Begin Source File

SOURCE=.\template\templ.cpp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "gen Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\gen\AStrArray.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\AStringArray.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\AStrSortArray.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\AStrTokenizer.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\base_enum.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\base_rect.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\base_rect_array.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\gen_application.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\gen_base64.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\gen_bit.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\gen_ch.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\gen_ch_class.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\gen_command_line.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\gen_Debug.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\gen_file_sssociation.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\gen_frame_wnd_interface.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\gen_geometry.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\gen_international.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\gen_keeper.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\gen_logic.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\gen_math.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\gen_math_rng.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\gen_object.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\gen_parse.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\gen_pointer_holder.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\gen_pointer_interface.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\gen_pointer_keeper.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\gen_pointer_listener.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\gen_pointer_manager.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\gen_process.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\gen_property.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\gen_ptri.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\gen_savings.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\gen_signal.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\gen_str.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\gen_system.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\gen_Timer.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\gen_TimerCallback.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\gen_TimerListener.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\gen_TimerWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\gen_var.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\gen_var_array.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\gen_variable_strict_compare.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\go_thread.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\MessageWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\MessageWindowListener.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\muldiv64.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\simple_thread.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\WStrArray.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\WString.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\WStringArray.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\WStringToPointer.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\WStringToWString.cpp
# End Source File
# Begin Source File

SOURCE=.\gen\WStrTokenizer.cpp
# End Source File
# End Group
# Begin Group "multithreading Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\multithreading\multithreading_core.cpp
# End Source File
# Begin Source File

SOURCE=.\multithreading\multithreading_event.cpp
# End Source File
# Begin Source File

SOURCE=.\multithreading\multithreading_manual_reset_event.cpp
# End Source File
# Begin Source File

SOURCE=.\multithreading\multithreading_mutex.cpp
# End Source File
# Begin Source File

SOURCE=.\multithreading\multithreading_plain_service.cpp
# End Source File
# Begin Source File

SOURCE=.\multithreading\multithreading_service_base.cpp
# End Source File
# Begin Source File

SOURCE=.\multithreading\multithreading_sync_object.cpp
# End Source File
# End Group
# Begin Group "user Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\user\user_application.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_buffer.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_button.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_check_box.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_check_interface.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_combo_box.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_control.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_control_event.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_control_property.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_create_view.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_document.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_document_interface.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_document_manager.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_document_template.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_document_template_tnterface.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_draw_context.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_edit_plain_text.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_element_2d.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_elemental.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_form.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_form_callback.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_form_list.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_frame_window.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_frame_wnd_interface.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_front_end.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_front_end_schema.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_get_view.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_interaction.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_interface.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_keyboard.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_keyboard_focus.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_keyboard_layout.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_list.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_list_cache.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_list_cache_interface.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_list_data.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_list_data_interface.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_list_header.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_mouse_focus.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_multiple_document_template.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_on_draw_interface.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_scroll_bar.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_scroll_view.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_single_document_template.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_str.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_tab.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_tab_callback.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_text_interface.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_tool_tip_tool.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_tool_tip_window.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_tree.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_win_message.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_window_draw_client_tool.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_window_draw_interface.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_window_map.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_window_message.cpp
# End Source File
# Begin Source File

SOURCE=.\user\user_window_util.cpp
# End Source File
# Begin Source File

SOURCE=.\user\viewcore.cpp
# End Source File
# Begin Source File

SOURCE=.\user\virtual_user_interface.cpp
# End Source File
# Begin Source File

SOURCE=.\user\window_interface.cpp
# End Source File
# Begin Source File

SOURCE=.\user\winfrmx.cpp
# End Source File
# Begin Source File

SOURCE=.\user\winmdi.cpp
# End Source File
# Begin Source File

SOURCE=.\user\winmini.cpp
# End Source File
# Begin Source File

SOURCE=.\user\XfplayerViewLine.cpp
# End Source File
# Begin Source File

SOURCE=.\user\XfplayerViewLines.cpp
# End Source File
# Begin Source File

SOURCE=.\user\XfplayerViewLineSelection.cpp
# End Source File
# End Group
# Begin Group "userbase Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\userbase\simple_button.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\simple_child_frame.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\simple_combo_box.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\simple_edit.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\simple_edit_plain_text.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\simple_form_list_edit.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\simple_form_list_view.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\simple_frame_window.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\simple_list_ctrl.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\simple_list_header_ctrl.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\simple_list_view.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\simple_mdi_child_window.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\simple_mdi_frame_window.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\simple_menu_bar.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\simple_push_button.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\simple_scroll_bar.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\simple_static.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\simple_status_bar.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\simple_tab_ctrl.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\simple_tab_view.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\simple_toolbar.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_application.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_base_bitmap_buttonex.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_button.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_button_control.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_combo_box.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_control_bar.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_document.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_document_manager.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_document_template.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_edit_plain_text.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_edit_plain_text_view.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_elastic_slider.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_form_list.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_form_view.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_frame_window.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_frame_window_interface.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_image_manager.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_mdi_child_window.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_mdi_frame_window.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_menu.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_menu_base.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_menu_button.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_menu_central.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_menu_item.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_menu_list_view.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_menu_list_window.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_meta_button.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_multiple_document_template.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_notification_area.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_notify_icon.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_notify_icon_listener.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_scroll_view.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_single_document_template.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_split_bar.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_split_layout.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_split_view.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_split_window.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_static.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_status_bar.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_step_slider.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_tab_control.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_tab_view.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_tab_view_update_hint.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_toolbar.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_toolbar_ctrl.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_tree_window.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_util.cpp
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_view.cpp
# End Source File
# End Group
# Begin Group "userex Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\userex\userbase_mini_dock_frame_window.cpp
# End Source File
# Begin Source File

SOURCE=.\userex\userex_calendar.cpp
# End Source File
# Begin Source File

SOURCE=.\userex\userex_calendar_interface.cpp
# End Source File
# Begin Source File

SOURCE=.\userex\userex_clock.cpp
# End Source File
# Begin Source File

SOURCE=.\userex\userex_clock_interface.cpp
# End Source File
# Begin Source File

SOURCE=.\userex\userex_form_child_frame.cpp
# End Source File
# Begin Source File

SOURCE=.\userex\userex_form_document.cpp
# End Source File
# Begin Source File

SOURCE=.\userex\userex_form_frame.cpp
# End Source File
# Begin Source File

SOURCE=.\userex\userex_form_update_hint.cpp
# End Source File
# Begin Source File

SOURCE=.\userex\userex_form_view.cpp
# End Source File
# Begin Source File

SOURCE=.\userex\userex_menu_document.cpp
# End Source File
# Begin Source File

SOURCE=.\userex\userex_menu_frame.cpp
# End Source File
# Begin Source File

SOURCE=.\userex\userex_menu_view.cpp
# End Source File
# Begin Source File

SOURCE=.\userex\userex_pane_split_view.cpp
# End Source File
# Begin Source File

SOURCE=.\userex\userex_pane_tab_view.cpp
# End Source File
# Begin Source File

SOURCE=.\userex\userex_pane_view.cpp
# End Source File
# Begin Source File

SOURCE=.\userex\userex_split_view.cpp
# End Source File
# End Group
# Begin Group "html Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\html\_html_child_frame.cpp
# End Source File
# Begin Source File

SOURCE=.\html\_html_document.cpp
# End Source File
# Begin Source File

SOURCE=.\html\_html_form.cpp
# End Source File
# Begin Source File

SOURCE=.\html\_html_form_view.cpp
# End Source File
# Begin Source File

SOURCE=.\html\_html_view.cpp
# End Source File
# Begin Source File

SOURCE=.\html\cell.cpp
# End Source File
# Begin Source File

SOURCE=.\html\document.cpp
# End Source File
# Begin Source File

SOURCE=.\html\document_container.cpp
# End Source File
# Begin Source File

SOURCE=.\html\elemental.cpp
# End Source File
# Begin Source File

SOURCE=.\html\EntryPoint.cpp
# End Source File
# Begin Source File

SOURCE=.\html\file.cpp
# End Source File
# Begin Source File

SOURCE=.\html\font.cpp
# End Source File
# Begin Source File

SOURCE=.\html\form.cpp
# End Source File
# Begin Source File

SOURCE=.\html\html_application.cpp
# End Source File
# Begin Source File

SOURCE=.\html\html_attribute.cpp
# End Source File
# Begin Source File

SOURCE=.\html\html_base.cpp
# End Source File
# Begin Source File

SOURCE=.\html\html_cell.cpp
# End Source File
# Begin Source File

SOURCE=.\html\html_child_frame.cpp
# End Source File
# Begin Source File

SOURCE=.\html\html_document.cpp
# End Source File
# Begin Source File

SOURCE=.\html\html_document_container.cpp
# End Source File
# Begin Source File

SOURCE=.\html\html_elemental.cpp
# End Source File
# Begin Source File

SOURCE=.\html\html_ex.cpp
# End Source File
# Begin Source File

SOURCE=.\html\html_file.cpp
# End Source File
# Begin Source File

SOURCE=.\html\html_font.cpp
# End Source File
# Begin Source File

SOURCE=.\html\html_form.cpp
# End Source File
# Begin Source File

SOURCE=.\html\html_form_view.cpp
# End Source File
# Begin Source File

SOURCE=.\html\html_form_window.cpp
# End Source File
# Begin Source File

SOURCE=.\html\html_frame.cpp
# End Source File
# Begin Source File

SOURCE=.\html\html_image.cpp
# End Source File
# Begin Source File

SOURCE=.\html\html_input_button.cpp
# End Source File
# Begin Source File

SOURCE=.\html\html_input_checkbox.cpp
# End Source File
# Begin Source File

SOURCE=.\html\html_input_text.cpp
# End Source File
# Begin Source File

SOURCE=.\html\html_LiteHTMLAttributes.cpp
# End Source File
# Begin Source File

SOURCE=.\html\html_LiteHTMLEntityResolver.cpp
# End Source File
# Begin Source File

SOURCE=.\html\html_LiteHTMLReader.cpp
# End Source File
# Begin Source File

SOURCE=.\html\html_LiteHTMLTag.cpp
# End Source File
# Begin Source File

SOURCE=.\html\html_reader.cpp
# End Source File
# Begin Source File

SOURCE=.\html\html_signal.cpp
# End Source File
# Begin Source File

SOURCE=.\html\html_style.cpp
# End Source File
# Begin Source File

SOURCE=.\html\html_style_sheet.cpp
# End Source File
# Begin Source File

SOURCE=.\html\html_style_sheet_array.cpp
# End Source File
# Begin Source File

SOURCE=.\html\html_table.cpp
# End Source File
# Begin Source File

SOURCE=.\html\html_table_elemental.cpp
# End Source File
# Begin Source File

SOURCE=.\html\html_table_row.cpp
# End Source File
# Begin Source File

SOURCE=.\html\html_tag.cpp
# End Source File
# Begin Source File

SOURCE=.\html\html_text.cpp
# End Source File
# Begin Source File

SOURCE=.\html\html_value.cpp
# End Source File
# Begin Source File

SOURCE=.\html\html_view.cpp
# End Source File
# Begin Source File

SOURCE=.\html\html_view_update_hint.cpp
# End Source File
# Begin Source File

SOURCE=.\html\image.cpp
# End Source File
# Begin Source File

SOURCE=.\html\input_button.cpp
# End Source File
# Begin Source File

SOURCE=.\html\input_checkbox.cpp
# End Source File
# Begin Source File

SOURCE=.\html\input_text.cpp
# End Source File
# Begin Source File

SOURCE=.\html\LiteHTMLAttributes.cpp
# End Source File
# Begin Source File

SOURCE=.\html\LiteHTMLEntityResolver.cpp
# End Source File
# Begin Source File

SOURCE=.\html\LiteHTMLReader.cpp
# End Source File
# Begin Source File

SOURCE=.\html\signal.cpp
# End Source File
# Begin Source File

SOURCE=.\html\style.cpp
# End Source File
# Begin Source File

SOURCE=.\html\table.cpp
# End Source File
# Begin Source File

SOURCE=.\html\table_elemental.cpp
# End Source File
# Begin Source File

SOURCE=.\html\table_row.cpp
# End Source File
# Begin Source File

SOURCE=.\html\text.cpp
# End Source File
# End Group
# Begin Group "primitive Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\primitive\color.cpp
# End Source File
# Begin Source File

SOURCE=.\primitive\comparable.cpp
# End Source File
# Begin Source File

SOURCE=.\primitive\count.cpp
# End Source File
# Begin Source File

SOURCE=.\primitive\index.cpp
# End Source File
# Begin Source File

SOURCE=.\primitive\int_biunique.cpp
# End Source File
# Begin Source File

SOURCE=.\primitive\logic.cpp
# End Source File
# Begin Source File

SOURCE=.\primitive\memory.cpp
# End Source File
# Begin Source File

SOURCE=.\primitive\memory_container.cpp
# End Source File
# Begin Source File

SOURCE=.\primitive\memory_file.cpp
# End Source File
# Begin Source File

SOURCE=.\primitive\natural.cpp
# End Source File
# Begin Source File

SOURCE=.\primitive\point.cpp
# End Source File
# Begin Source File

SOURCE=.\primitive\primitive_scalar.cpp
# End Source File
# Begin Source File

SOURCE=.\primitive\rectangle.cpp
# End Source File
# Begin Source File

SOURCE=.\primitive\shared_file.cpp
# End Source File
# Begin Source File

SOURCE=.\primitive\shared_memory.cpp
# End Source File
# Begin Source File

SOURCE=.\primitive\simple_string.cpp
# End Source File
# Begin Source File

SOURCE=.\primitive\size.cpp
# End Source File
# Begin Source File

SOURCE=.\primitive\string.cpp
# End Source File
# Begin Source File

SOURCE=.\primitive\types.cpp
# End Source File
# End Group
# Begin Group "colorertake5 Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\colorertake5\base_editor.cpp
# End Source File
# Begin Source File

SOURCE=.\colorertake5\colorertake5_application.cpp
# End Source File
# Begin Source File

SOURCE=.\colorertake5\colorertake5_base_editor.cpp
# End Source File
# Begin Source File

SOURCE=.\colorertake5\colorertake5_cregexp.cpp
# End Source File
# Begin Source File

SOURCE=.\colorertake5\colorertake5_default_error_handler.cpp
# End Source File
# Begin Source File

SOURCE=.\colorertake5\colorertake5_error_handler_writer.cpp
# End Source File
# Begin Source File

SOURCE=.\colorertake5\colorertake5_exception.cpp
# End Source File
# Begin Source File

SOURCE=.\colorertake5\colorertake5_hrc_parser_helpers.cpp
# End Source File
# Begin Source File

SOURCE=.\colorertake5\colorertake5_hrc_parser_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\colorertake5\colorertake5_line_regions_compact_support.cpp
# End Source File
# Begin Source File

SOURCE=.\colorertake5\colorertake5_line_regions_support.cpp
# End Source File
# Begin Source File

SOURCE=.\colorertake5\colorertake5_line_source.cpp
# End Source File
# Begin Source File

SOURCE=.\colorertake5\colorertake5_logging.cpp
# End Source File
# Begin Source File

SOURCE=.\colorertake5\colorertake5_outliner.cpp
# End Source File
# Begin Source File

SOURCE=.\colorertake5\colorertake5_parsed_line_writer.cpp
# End Source File
# Begin Source File

SOURCE=.\colorertake5\colorertake5_parser_factory.cpp
# End Source File
# Begin Source File

SOURCE=.\colorertake5\colorertake5_region_handler.cpp
# End Source File
# Begin Source File

SOURCE=.\colorertake5\colorertake5_region_mapper_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\colorertake5\colorertake5_styled_hrd_mapper.cpp
# End Source File
# Begin Source File

SOURCE=.\colorertake5\colorertake5_text_hrd_mapper.cpp
# End Source File
# Begin Source File

SOURCE=.\colorertake5\colorertake5_text_lines.cpp
# End Source File
# Begin Source File

SOURCE=.\colorertake5\colorertake5_text_parser_helpers.cpp
# End Source File
# Begin Source File

SOURCE=.\colorertake5\colorertake5_text_parser_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\colorertake5\cregexp.cpp
# End Source File
# Begin Source File

SOURCE=.\colorertake5\default_error_handler.cpp
# End Source File
# Begin Source File

SOURCE=.\colorertake5\error_handler_writer.cpp
# End Source File
# Begin Source File

SOURCE=.\colorertake5\hrc_parser_helpers.cpp
# End Source File
# Begin Source File

SOURCE=.\colorertake5\hrc_parser_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\colorertake5\line_regions_compact_support.cpp
# End Source File
# Begin Source File

SOURCE=.\colorertake5\line_regions_support.cpp
# End Source File
# Begin Source File

SOURCE=.\colorertake5\logging.cpp
# End Source File
# Begin Source File

SOURCE=.\colorertake5\memory_chunks.cpp
# End Source File
# Begin Source File

SOURCE=.\colorertake5\outliner.cpp
# End Source File
# Begin Source File

SOURCE=.\colorertake5\parser_factory.cpp
# End Source File
# Begin Source File

SOURCE=.\colorertake5\region_mapper_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\colorertake5\styled_hrd_mapper.cpp
# End Source File
# Begin Source File

SOURCE=.\colorertake5\text_hrd_mapper.cpp
# End Source File
# Begin Source File

SOURCE=.\colorertake5\text_lines.cpp
# End Source File
# Begin Source File

SOURCE=.\colorertake5\text_parser_helpers.cpp
# End Source File
# Begin Source File

SOURCE=.\colorertake5\text_parser_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\colorertake5\TextConsoleViewer.cpp
# End Source File
# Begin Source File

SOURCE=.\colorertake5\xmldom.cpp
# End Source File
# End Group
# Begin Group "ca2api002_00002 Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ca2api002_00002\ca04_bzip.cpp
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\ca04_compress.cpp
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\ca04_gzip.cpp
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\ca04_patch.cpp
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\ca05_crypt.cpp
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\ca08_application.cpp
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\ca27_email.cpp
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\ca27_http.cpp
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\ca27_http_get_socket.cpp
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\ca27_user.cpp
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\ca2api002_00002.cpp
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\ca36_file.cpp
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\compress.cpp
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\copydesk.cpp
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\CRC.cpp
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\CRCFast.cpp
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\crypt.cpp
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\email.cpp
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\http.cpp
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\http_get_socket.cpp
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\ip_enum.cpp
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\patch.cpp
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\whirlpool.cpp
# End Source File
# End Group
# Begin Group "sockets Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sockets\Ajp13Socket.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\AjpBaseSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\application_interface.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\Base64.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\dllmain.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\Event.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\EventHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\EventTime.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\http_base_socket.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\http_cookie.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\http_file.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\http_form.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\http_memory_file.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\http_request.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\http_response.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\http_socket.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\http_transaction.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\http_tunnel.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\HttpClientSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\httpd_socket.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\HttpDebugSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\HttpGetSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\HttpPostSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\HttpPutSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\IEventOwner.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\Ipv4Address.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\Ipv6Address.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\Lock.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\Mutex.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\Parse.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\ResolvServer.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\ResolvSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\SctpSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\Semaphore.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sip_base.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sip_callback.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sip_client.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sip_event.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sip_server.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sip_socket.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\smtp_socket.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\SmtpdSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\Socket.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\socket_include.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\SocketHandler.cpp
# End Source File
# Begin Source File

SOURCE=".\sockets\Sockets-config.cpp"
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_Ajp13Socket.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_AjpBaseSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_application_interface.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_Event.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_EventHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_EventTime.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_exception.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_http_base_socket.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_http_cookie.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_http_form.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_http_request.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_http_response.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_http_socket.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_http_transaction.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_http_tunnel.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_HttpClientSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_httpd_socket.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_HttpDebugSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_HttpGetSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_HttpPostSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_HttpPutSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_IEventOwner.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_Ipv4Address.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_Ipv6Address.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_resolv_server.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_resolv_socket.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_SctpSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_sip_base.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_sip_base_client_socket.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_sip_callback.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_sip_client.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_sip_event.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_sip_request.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_sip_response.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_sip_server.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_sip_socket.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_sip_tcp_client_socket.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_sip_transaction.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_sip_udp_client_socket.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_smtp_socket.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_smtpd_socket.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_Socket.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_SocketHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_SSLInitializer.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_StreamSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_TcpSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_trace_log.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets_UdpSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\SSLInitializer.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\StdoutLog.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\StreamSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\TcpSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\sockets\UdpSocket.cpp
# End Source File
# End Group
# Begin Group "ex2 Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ex2\ex2_application.cpp
# End Source File
# Begin Source File

SOURCE=.\ex2\ex2_file_set.cpp
# End Source File
# Begin Source File

SOURCE=.\ex2\ex2_folder_watch.cpp
# End Source File
# End Group
# Begin Group "icube Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\icube\icube_application.cpp
# End Source File
# End Group
# Begin Group "ex1 Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ex1\ex1_application.cpp
# End Source File
# Begin Source File

SOURCE=.\ex1\ex1_buffered_file.cpp
# End Source File
# Begin Source File

SOURCE=.\ex1\ex1_edit_file.cpp
# End Source File
# Begin Source File

SOURCE=.\ex1\ex1_exception.cpp
# End Source File
# Begin Source File

SOURCE=.\ex1\ex1_file.cpp
# End Source File
# Begin Source File

SOURCE=.\ex1\ex1_file_set.cpp
# End Source File
# Begin Source File

SOURCE=.\ex1\ex1_file_system.cpp
# End Source File
# Begin Source File

SOURCE=.\ex1\ex1_resource.cpp
# End Source File
# Begin Source File

SOURCE=.\ex1\ex1_serializable.cpp
# End Source File
# Begin Source File

SOURCE=.\ex1\ex1_str_stream.cpp
# End Source File
# Begin Source File

SOURCE=.\ex1\ex1_stream.cpp
# End Source File
# Begin Source File

SOURCE=.\ex1\ex1_stream2.cpp
# End Source File
# Begin Source File

SOURCE=.\ex1\ex1_text_file.cpp
# End Source File
# Begin Source File

SOURCE=.\ex1\ex1_tree_data.cpp
# End Source File
# End Group
# Begin Group "mus Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\mus\_stdmidifile.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\Attributes.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\KaraokeUtil.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\LyricTrack.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\LyricTracks.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\LyricType1Events.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\Microke1.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\Midi.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\MidiCentral.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\MidiCentralContainer.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\MidiCentralListener.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\MidiDocHelper.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\MidiEventBase.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\MidiEventsV1.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\MidiEventV001.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\MidiEventV007.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\MidiEventV008.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\MidiEventV016.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\MidiEventV507.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\MidiEventV508.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\MidiException.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\MidiFile.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\MidiPlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\MidiPlayerCallback.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\MidiPlayerCallbackInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\MidiPlayerHighPriorityThread.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\MidiPlayerInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\MidiPlayerWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\MidiSequence.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\MidiSequenceThread.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\MidiTrack.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\MidiTrackBase.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\MidiTracks.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\MidiTrackV008.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\midiutil.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\MidiViewHelper.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\MidiWorkEventV3A.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\MidiWorkTrackV3.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\MultimediaFile.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\mus_dll.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\SoftKaraokeInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\Star350EventBase.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\Star350EventTrack.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\Star350EventV001.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\Star350EventV008.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\Star350EventV016.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\Star350File.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\Star350InfoHeader.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\Star350LyricTrack.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\Star350LyricTracks.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\Star350TrackBase.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\Star350Tracks.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\Star350TrackV008.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\Tune1000Info.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\Uiutils.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\vmsmus.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\XF.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\XFInfoHeader.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\XFInfoHeaderLS.cpp
# End Source File
# Begin Source File

SOURCE=.\mus\XFInfoHeaders.cpp
# End Source File
# End Group
# Begin Group "mediaplay Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\mediaplay\mediaplay.cpp
# End Source File
# Begin Source File

SOURCE=.\mediaplay\mediaplay_data.cpp
# End Source File
# Begin Source File

SOURCE=.\mediaplay\mediaplay_document.cpp
# End Source File
# Begin Source File

SOURCE=.\mediaplay\mediaplay_karaoke.cpp
# End Source File
# Begin Source File

SOURCE=.\mediaplay\mediaplay_playlist_callback.cpp
# End Source File
# Begin Source File

SOURCE=.\mediaplay\mediaplay_record_notify_view.cpp
# End Source File
# Begin Source File

SOURCE=.\mediaplay\mediaplay_view.cpp
# End Source File
# Begin Source File

SOURCE=.\mediaplay\mediaplay_view_interface.cpp
# End Source File
# Begin Source File

SOURCE=.\mediaplay\mediaplay_view_update_hint.cpp
# End Source File
# End Group
# Begin Group "mediaplaylist Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\mediaplaylist\PlaylistAppInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\mediaplaylist\PlaylistCallback.cpp
# End Source File
# Begin Source File

SOURCE=.\mediaplaylist\PlaylistCallbackContainer.cpp
# End Source File
# Begin Source File

SOURCE=.\mediaplaylist\PlaylistCallbackContainerInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\mediaplaylist\PlaylistCallbackInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\mediaplaylist\PlaylistCentral.cpp
# End Source File
# Begin Source File

SOURCE=.\mediaplaylist\PlaylistCentralCallbackInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\mediaplaylist\PlaylistCentralContainer.cpp
# End Source File
# Begin Source File

SOURCE=.\mediaplaylist\PlaylistDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\mediaplaylist\PlaylistFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\mediaplaylist\PlaylistListView.cpp
# End Source File
# Begin Source File

SOURCE=.\mediaplaylist\PlaylistView.cpp
# End Source File
# Begin Source File

SOURCE=.\mediaplaylist\PlaylistViewUpdateHint.cpp
# End Source File
# End Group
# Begin Group "mediamanager Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\mediamanager\AlbumBuild.cpp
# End Source File
# Begin Source File

SOURCE=.\mediamanager\AlbumBuildThread.cpp
# End Source File
# Begin Source File

SOURCE=.\mediamanager\AlbumBuildWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\mediamanager\mediamanager.cpp
# End Source File
# Begin Source File

SOURCE=.\mediamanager\MediaManagerImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\mediamanager\playlist_callback.cpp
# End Source File
# End Group
# Begin Group "mail Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\mail\mail_account.cpp
# End Source File
# Begin Source File

SOURCE=.\mail\mail_application.cpp
# End Source File
# Begin Source File

SOURCE=.\mail\mail_child_frame.cpp
# End Source File
# Begin Source File

SOURCE=.\mail\mail_configuration.cpp
# End Source File
# Begin Source File

SOURCE=.\mail\mail_db_pop3.cpp
# End Source File
# Begin Source File

SOURCE=.\mail\mail_document.cpp
# End Source File
# Begin Source File

SOURCE=.\mail\mail_folder_list.cpp
# End Source File
# Begin Source File

SOURCE=.\mail\mail_folder_list_interface.cpp
# End Source File
# Begin Source File

SOURCE=.\mail\mail_frame.cpp
# End Source File
# Begin Source File

SOURCE=.\mail\mail_list.cpp
# End Source File
# Begin Source File

SOURCE=.\mail\mail_list_interface.cpp
# End Source File
# Begin Source File

SOURCE=.\mail\mail_pop3.cpp
# End Source File
# Begin Source File

SOURCE=.\mail\mail_pop3_socket.cpp
# End Source File
# Begin Source File

SOURCE=.\mail\mail_right_pane_view.cpp
# End Source File
# Begin Source File

SOURCE=.\mail\mail_simple_pop3.cpp
# End Source File
# Begin Source File

SOURCE=.\mail\mail_view.cpp
# End Source File
# Begin Source File

SOURCE=.\mail\mail_views.cpp
# End Source File
# Begin Source File

SOURCE=.\mail\main_document.cpp
# End Source File
# Begin Source File

SOURCE=.\mail\main_frame.cpp
# End Source File
# Begin Source File

SOURCE=.\mail\pop3.cpp
# End Source File
# Begin Source File

SOURCE=.\mail\pop3_format.cpp
# End Source File
# Begin Source File

SOURCE=.\mail\pop3_objects.cpp
# End Source File
# Begin Source File

SOURCE=.\mail\pop3_parsing.cpp
# End Source File
# Begin Source File

SOURCE=.\mail\pop3_queries.cpp
# End Source File
# Begin Source File

SOURCE=.\mail\pop3_session.cpp
# End Source File
# Begin Source File

SOURCE=.\mail\pop3_socket.cpp
# End Source File
# Begin Source File

SOURCE=.\mail\right_pane_view.cpp
# End Source File
# End Group
# Begin Group "bergedge Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\bergedge\bergedge_bergedge_application.cpp
# End Source File
# Begin Source File

SOURCE=.\bergedge\bergedge_document.cpp
# End Source File
# Begin Source File

SOURCE=.\bergedge\bergedge_EntryPoint.cpp
# End Source File
# Begin Source File

SOURCE=.\bergedge\bergedge_form_callback.cpp
# End Source File
# Begin Source File

SOURCE=.\bergedge\bergedge_frame.cpp
# End Source File
# Begin Source File

SOURCE=.\bergedge\bergedge_pane_view.cpp
# End Source File
# Begin Source File

SOURCE=.\bergedge\bergedge_pane_view_update_hint.cpp
# End Source File
# Begin Source File

SOURCE=.\bergedge\bergedge_system.cpp
# End Source File
# Begin Source File

SOURCE=.\bergedge\bergedge_system_map.cpp
# End Source File
# Begin Source File

SOURCE=.\bergedge\bergedge_view.cpp
# End Source File
# End Group
# Begin Group "platform Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\platform\platform_application.cpp
# End Source File
# Begin Source File

SOURCE=.\platform\platform_document.cpp
# End Source File
# Begin Source File

SOURCE=.\platform\platform_frame.cpp
# End Source File
# Begin Source File

SOURCE=.\platform\platform_pane_view.cpp
# End Source File
# Begin Source File

SOURCE=.\platform\platform_pane_view_update_hint.cpp
# End Source File
# Begin Source File

SOURCE=.\platform\platform_view.cpp
# End Source File
# End Group
# Begin Group "nature Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\nature\nature_appearance_view.cpp
# End Source File
# Begin Source File

SOURCE=.\nature\nature_application.cpp
# End Source File
# Begin Source File

SOURCE=.\nature\nature_database.cpp
# End Source File
# Begin Source File

SOURCE=.\nature\nature_document.cpp
# End Source File
# Begin Source File

SOURCE=.\nature\nature_frame.cpp
# End Source File
# Begin Source File

SOURCE=.\nature\nature_pane_view.cpp
# End Source File
# Begin Source File

SOURCE=.\nature\nature_pane_view_update_hint.cpp
# End Source File
# Begin Source File

SOURCE=.\nature\nature_view.cpp
# End Source File
# End Group
# Begin Group "fontopus Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\fontopus\fontopus_application.cpp
# End Source File
# End Group
# Begin Group "ca2_cgcly24_84 Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ca2_cgcly24_84\ca84_application.cpp
# End Source File
# End Group
# Begin Group "ca2_cstx23_77 Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ca2_cstx23_77\ca77_application.cpp
# End Source File
# End Group
# Begin Group "filemanager Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\filemanager\ContextMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\file_manager_form_child_frame.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\file_manager_form_document.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\file_manager_form_update_hint.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\file_manager_form_view.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\file_manager_operation_child_frame.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\file_manager_operation_document.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\file_manager_operation_info_view.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\file_manager_operation_list_view.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\file_manager_operation_thread.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\file_manager_operation_view.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\file_operation.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\FileManager.2.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\filemanager.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\filemanager_application.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\filemanager_folder_list_view.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\filemanager_folder_selection_list_view.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\filemanager_form_child_frame.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\filemanager_form_document.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\filemanager_form_update_hint.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\filemanager_form_view.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\filemanager_icon.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\filemanager_item_action.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\filemanager_operation_child_frame.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\filemanager_operation_document.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\filemanager_operation_info_view.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\filemanager_operation_list_view.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\filemanager_operation_thread.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\filemanager_operation_view.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\FileManagerCallbackInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\FileManagerChildFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\FileManagerDDX.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\FileManagerDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\FileManagerFileListCallback.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\FileManagerFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\FileManagerInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\FileManagerLeftView.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\FileManagerMainFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\FileManagerPathView.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\FileManagerTabView.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\FileManagerTemplate.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\FileManagerView.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\FileManagerViewInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\FileManagerViewUpdateHint.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\folder_list_view.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\folder_selection_list_view.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\icon.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\item_action.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\SimpleFileListInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\SimpleFileListView.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\SimpleFilePropertiesForm.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\SimpleFolderListInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\SimpleFolderListView.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\SimpleFolderTreeInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\SimpleFolderTreeView.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\SimplePreview.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\SimplePreviewInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\filemanager\XfplayerDialogBar.cpp
# End Source File
# End Group
# Begin Group "calculator Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\calculator\calculator_application.cpp
# End Source File
# Begin Source File

SOURCE=.\calculator\calculator_class.cpp
# End Source File
# Begin Source File

SOURCE=.\calculator\calculator_document.cpp
# End Source File
# Begin Source File

SOURCE=.\calculator\calculator_frame.cpp
# End Source File
# Begin Source File

SOURCE=.\calculator\calculator_view.cpp
# End Source File
# Begin Source File

SOURCE=.\calculator\datetime_element.cpp
# End Source File
# Begin Source File

SOURCE=.\calculator\datetime_parser.cpp
# End Source File
# Begin Source File

SOURCE=.\calculator\datetime_scanner.cpp
# End Source File
# Begin Source File

SOURCE=.\calculator\datetime_token.cpp
# End Source File
# Begin Source File

SOURCE=.\calculator\numeric_element.cpp
# End Source File
# Begin Source File

SOURCE=.\calculator\numeric_parser.cpp
# End Source File
# Begin Source File

SOURCE=.\calculator\numeric_scanner.cpp
# End Source File
# Begin Source File

SOURCE=.\calculator\numeric_value.cpp
# End Source File
# End Group
# Begin Group "ca2_devian Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ca2_devian\ca67_application.cpp
# End Source File
# End Group
# Begin Group "ca2api015_00045 Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ca2api015_00045\ca2api015_00045.cpp
# End Source File
# Begin Source File

SOURCE=.\ca2api015_00045\ca45_application.cpp
# End Source File
# Begin Source File

SOURCE=.\ca2api015_00045\ca45_keyboard_layout.cpp
# End Source File
# Begin Source File

SOURCE=.\ca2api015_00045\ca45_validate.cpp
# End Source File
# Begin Source File

SOURCE=.\ca2api015_00045\dialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ca2api015_00045\message_box.cpp
# End Source File
# Begin Source File

SOURCE=.\ca2api015_00045\network_configuration.cpp
# End Source File
# Begin Source File

SOURCE=.\ca2api015_00045\Shell.cpp
# End Source File
# Begin Source File

SOURCE=.\ca2api015_00045\wait_message_dialog.cpp
# End Source File
# End Group
# Begin Group "ca2api014_00042 Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ca2api014_00042\ca2api014_00042.cpp
# End Source File
# Begin Source File

SOURCE=.\ca2api014_00042\ca42_application.cpp
# End Source File
# End Group
# Begin Group "ca2api013_00039 Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ca2api013_00039\ca39_application.cpp
# End Source File
# Begin Source File

SOURCE=.\ca2api013_00039\ca39_user.cpp
# End Source File
# End Group
# Begin Group "simpledb Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\simpledb\db_long_set.cpp
# End Source File
# Begin Source File

SOURCE=.\simpledb\db_server.cpp
# End Source File
# Begin Source File

SOURCE=.\simpledb\db_set.cpp
# End Source File
# Begin Source File

SOURCE=.\simpledb\db_str_set.cpp
# End Source File
# Begin Source File

SOURCE=.\simpledb\db_stra_set.cpp
# End Source File
# Begin Source File

SOURCE=.\simpledb\DBFileSystemSize.cpp
# End Source File
# Begin Source File

SOURCE=.\simpledb\file_set.cpp
# End Source File
# Begin Source File

SOURCE=.\simpledb\im_post.cpp
# End Source File
# Begin Source File

SOURCE=.\simpledb\mysql_database.cpp
# End Source File
# Begin Source File

SOURCE=.\simpledb\mysql_result.cpp
# End Source File
# Begin Source File

SOURCE=.\simpledb\simpledb.cpp
# End Source File
# Begin Source File

SOURCE=.\simpledb\simpledb_application.cpp
# End Source File
# Begin Source File

SOURCE=.\simpledb\simpledb_database.cpp
# End Source File
# Begin Source File

SOURCE=.\simpledb\simpledb_dataset.cpp
# End Source File
# Begin Source File

SOURCE=.\simpledb\simpledb_table.cpp
# End Source File
# Begin Source File

SOURCE=.\simpledb\sqlite_database.cpp
# End Source File
# Begin Source File

SOURCE=.\simpledb\sqlite_dataset.cpp
# End Source File
# End Group
# Begin Group "database Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\database\BaseDatabase.cpp
# End Source File
# Begin Source File

SOURCE=.\database\BaseDataset.cpp
# End Source File
# Begin Source File

SOURCE=.\database\data_server.cpp
# End Source File
# Begin Source File

SOURCE=.\database\data_update_hint.cpp
# End Source File
# Begin Source File

SOURCE=.\database\database_application.cpp
# End Source File
# Begin Source File

SOURCE=.\database\database_base.cpp
# End Source File
# Begin Source File

SOURCE=.\database\database_client.cpp
# End Source File
# Begin Source File

SOURCE=.\database\database_definition.cpp
# End Source File
# Begin Source File

SOURCE=.\database\database_event_change.cpp
# End Source File
# Begin Source File

SOURCE=.\database\database_field_definition.cpp
# End Source File
# Begin Source File

SOURCE=.\database\database_id.cpp
# End Source File
# Begin Source File

SOURCE=.\database\database_key.cpp
# End Source File
# Begin Source File

SOURCE=.\database\database_selection.cpp
# End Source File
# Begin Source File

SOURCE=.\database\database_selection_item.cpp
# End Source File
# Begin Source File

SOURCE=.\database\database_server.cpp
# End Source File
# Begin Source File

SOURCE=.\database\database_set.cpp
# End Source File
# Begin Source File

SOURCE=.\database\database_stringhelper.cpp
# End Source File
# Begin Source File

SOURCE=.\database\database_update_hint.cpp
# End Source File
# Begin Source File

SOURCE=.\database\database_user_interaction.cpp
# End Source File
# End Group
# Begin Group "audio Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\audio\audio_WaveBuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\audio\audio_WaveCentral.cpp
# End Source File
# Begin Source File

SOURCE=.\audio\audio_WaveCentralContainer.cpp
# End Source File
# Begin Source File

SOURCE=.\audio\audio_WaveEffectCrescendo.cpp
# End Source File
# Begin Source File

SOURCE=.\audio\audio_WaveEffectDevocalizer.cpp
# End Source File
# Begin Source File

SOURCE=.\audio\audio_WaveFile.cpp
# End Source File
# Begin Source File

SOURCE=.\audio\audio_WaveIn.cpp
# End Source File
# Begin Source File

SOURCE=.\audio\audio_WaveInListener.cpp
# End Source File
# Begin Source File

SOURCE=.\audio\audio_WaveInListenerSet.cpp
# End Source File
# Begin Source File

SOURCE=.\audio\audio_WaveOut.cpp
# End Source File
# Begin Source File

SOURCE=.\audio\audio_WavePlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\audio\audio_WavePlayerInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\audio\audio_WavePreBuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\audio\audio_WavePreBufferCallback.cpp
# End Source File
# Begin Source File

SOURCE=.\audio\audio_WaveRecorder.cpp
# End Source File
# Begin Source File

SOURCE=.\audio\audio_WaveRecorderInterface.cpp
# End Source File
# End Group
# Begin Group "audio_decode Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\audio_decode\audio_decode.cpp
# End Source File
# Begin Source File

SOURCE=.\audio_decode\audio_decode_Decoder.cpp
# End Source File
# Begin Source File

SOURCE=.\audio_decode\audio_decode_DecoderPlugin.cpp
# End Source File
# Begin Source File

SOURCE=.\audio_decode\audio_decode_DecoderPluginSet.cpp
# End Source File
# Begin Source File

SOURCE=.\audio_decode\audio_decode_DecoderPluginSetEx1.cpp
# End Source File
# Begin Source File

SOURCE=.\audio_decode\audio_decode_Encoder.cpp
# End Source File
# Begin Source File

SOURCE=.\audio_decode\audio_decode_EncoderPlugin.cpp
# End Source File
# Begin Source File

SOURCE=.\audio_decode\audio_decode_EncoderPluginSet.cpp
# End Source File
# Begin Source File

SOURCE=.\audio_decode\audio_decode_EncoderPluginSetEx1.cpp
# End Source File
# End Group
# Begin Group "video Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\video\video_player.cpp
# End Source File
# Begin Source File

SOURCE=.\video\video_player_command.cpp
# End Source File
# End Group
# Begin Group "video_decode Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\video_decode\video_decode_Decoder.cpp
# End Source File
# Begin Source File

SOURCE=.\video_decode\video_decode_DecoderPlugin.cpp
# End Source File
# Begin Source File

SOURCE=.\video_decode\video_decode_DecoderPluginSet.cpp
# End Source File
# Begin Source File

SOURCE=.\video_decode\video_decode_DecoderPluginSetEx1.cpp
# End Source File
# End Group
# Begin Group "exception Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\exception\debug.cpp
# End Source File
# Begin Source File

SOURCE=.\exception\dump.cpp
# End Source File
# Begin Source File

SOURCE=.\exception\dump_context.cpp
# End Source File
# Begin Source File

SOURCE=.\exception\dump_floating_point.cpp
# End Source File
# Begin Source File

SOURCE=.\exception\dump_output.cpp
# End Source File
# Begin Source File

SOURCE=.\exception\except.cpp
# End Source File
# Begin Source File

SOURCE=.\exception\exception.cpp
# End Source File
# Begin Source File

SOURCE=.\exception\se_translator.cpp
# End Source File
# Begin Source File

SOURCE=.\exception\SymEngine.cpp
# End Source File
# Begin Source File

SOURCE=.\exception\VMSException.cpp
# End Source File
# End Group
# Begin Group "upnp Source"

# PROP Default_Filter ""
# End Group
# Begin Group "visual Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\visual\font_central.cpp
# End Source File
# Begin Source File

SOURCE=.\visual\FreeImageFileProc.cpp
# End Source File
# Begin Source File

SOURCE=.\visual\image_list.cpp
# End Source File
# Begin Source File

SOURCE=.\visual\Imaging.cpp
# End Source File
# Begin Source File

SOURCE=.\visual\rgb_quad_array.cpp
# End Source File
# Begin Source File

SOURCE=.\visual\Visual.cpp
# End Source File
# Begin Source File

SOURCE=.\visual\visual_api.cpp
# End Source File
# Begin Source File

SOURCE=.\visual\visual_application.cpp
# End Source File
# Begin Source File

SOURCE=.\visual\visual_buffered_graphics.cpp
# End Source File
# Begin Source File

SOURCE=.\visual\visual_clip.cpp
# End Source File
# Begin Source File

SOURCE=.\visual\visual_cursor.cpp
# End Source File
# Begin Source File

SOURCE=.\visual\visual_dib.cpp
# End Source File
# Begin Source File

SOURCE=.\visual\visual_font.cpp
# End Source File
# Begin Source File

SOURCE=.\visual\visual_glyph.cpp
# End Source File
# Begin Source File

SOURCE=.\visual\visual_glyph_set.cpp
# End Source File
# Begin Source File

SOURCE=.\visual\visual_graphics_extension.cpp
# End Source File
# Begin Source File

SOURCE=.\visual\visual_icon.cpp
# End Source File
# Begin Source File

SOURCE=.\visual\visual_image_list.cpp
# End Source File
# Begin Source File

SOURCE=.\visual\visual_visual.cpp
# End Source File
# Begin Source File

SOURCE=.\visual\visual_water_routine.cpp
# End Source File
# End Group
# Begin Group "xml Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\xml\xml_attr.cpp
# End Source File
# Begin Source File

SOURCE=.\xml\xml_base_array.cpp
# End Source File
# Begin Source File

SOURCE=.\xml\xml_disp_option.cpp
# End Source File
# Begin Source File

SOURCE=.\xml\xml_document.cpp
# End Source File
# Begin Source File

SOURCE=.\xml\xml_entity.cpp
# End Source File
# Begin Source File

SOURCE=.\xml\xml_exportable.cpp
# End Source File
# Begin Source File

SOURCE=.\xml\xml_importable.cpp
# End Source File
# Begin Source File

SOURCE=.\xml\xml_input_tree.cpp
# End Source File
# Begin Source File

SOURCE=.\xml\xml_node.cpp
# End Source File
# Begin Source File

SOURCE=.\xml\xml_output_tree.cpp
# End Source File
# Begin Source File

SOURCE=.\xml\xml_parse_info.cpp
# End Source File
# Begin Source File

SOURCE=.\xml\xml_property_exchange.cpp
# End Source File
# Begin Source File

SOURCE=.\xml\xml_tree_base.cpp
# End Source File
# Begin Source File

SOURCE=.\xml\xml_tree_schema.cpp
# End Source File
# Begin Source File

SOURCE=.\xml\xml_var_exchange.cpp
# End Source File
# Begin Source File

SOURCE=.\xml\xml_XMLite.cpp
# End Source File
# End Group
# Begin Group "imedia Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\imedia\imedia_position.cpp
# End Source File
# Begin Source File

SOURCE=.\imedia\imedia_position_array.cpp
# End Source File
# Begin Source File

SOURCE=.\imedia\imedia_time.cpp
# End Source File
# Begin Source File

SOURCE=.\imedia\imedia_time_array.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\StdAfx.cpp
# SUBTRACT CPP /YX /Yc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "ca Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ca\application.h
# End Source File
# Begin Source File

SOURCE=.\ca\application_interface.h
# End Source File
# Begin Source File

SOURCE=.\ca\bitmap.h
# End Source File
# Begin Source File

SOURCE=.\ca\brush.h
# End Source File
# Begin Source File

SOURCE=.\ca\ca.h
# End Source File
# Begin Source File

SOURCE=.\ca\ca_2.h
# End Source File
# Begin Source File

SOURCE=.\ca\ca_base.h
# End Source File
# Begin Source File

SOURCE=.\ca\ca_graphics.h
# End Source File
# Begin Source File

SOURCE=.\ca\dib.h
# End Source File
# Begin Source File

SOURCE=.\ca\dir.h
# End Source File
# Begin Source File

SOURCE=.\ca\draw_dib.h
# End Source File
# Begin Source File

SOURCE=.\ca\exception.h
# End Source File
# Begin Source File

SOURCE=.\ca\font.h
# End Source File
# Begin Source File

SOURCE=.\ca\graphics.h
# End Source File
# Begin Source File

SOURCE=.\ca\graphics_object.h
# End Source File
# Begin Source File

SOURCE=.\ca\igui.h
# End Source File
# Begin Source File

SOURCE=.\ca\lock.h
# End Source File
# Begin Source File

SOURCE=.\ca\log.h
# End Source File
# Begin Source File

SOURCE=.\ca\message_window.h
# End Source File
# Begin Source File

SOURCE=.\ca\object.h
# End Source File
# Begin Source File

SOURCE=.\ca\osi.h
# End Source File
# Begin Source File

SOURCE=.\ca\palette.h
# End Source File
# Begin Source File

SOURCE=.\ca\pen.h
# End Source File
# Begin Source File

SOURCE=.\ca\profiler.h
# End Source File
# Begin Source File

SOURCE=.\ca\rgn.h
# End Source File
# Begin Source File

SOURCE=.\ca\se_translator.h
# End Source File
# Begin Source File

SOURCE=.\ca\smart_pointer.h
# End Source File
# Begin Source File

SOURCE=.\ca\system.h
# End Source File
# Begin Source File

SOURCE=.\ca\thread.h
# End Source File
# Begin Source File

SOURCE=.\ca\type_info.h
# End Source File
# Begin Source File

SOURCE=.\ca\window.h
# End Source File
# Begin Source File

SOURCE=.\ca\window_draw.h
# End Source File
# End Group
# Begin Group "radix Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\radix\allocate.h
# End Source File
# Begin Source File

SOURCE=.\radix\application.h
# End Source File
# Begin Source File

SOURCE=.\radix\base.h
# End Source File
# Begin Source File

SOURCE=.\radix\base_object.h
# End Source File
# Begin Source File

SOURCE=.\radix\bergedge_application.h
# End Source File
# Begin Source File

SOURCE=.\radix\bergedge_object.h
# End Source File
# Begin Source File

SOURCE=.\radix\BSTR.H
# End Source File
# Begin Source File

SOURCE=.\radix\ca2api000_00001_res.h
# End Source File
# Begin Source File

SOURCE=.\radix\cafx.inl
# End Source File
# Begin Source File

SOURCE=.\radix\cafxdllx.h
# End Source File
# Begin Source File

SOURCE=.\radix\command.h
# End Source File
# Begin Source File

SOURCE=.\radix\command_target.h
# End Source File
# Begin Source File

SOURCE=.\radix\Common.h
# End Source File
# Begin Source File

SOURCE=.\radix\comparable.h
# End Source File
# Begin Source File

SOURCE=.\radix\composite.h
# End Source File
# Begin Source File

SOURCE=.\radix\Constraint.h
# End Source File
# Begin Source File

SOURCE=.\radix\contact_list.h
# End Source File
# Begin Source File

SOURCE=.\radix\conv.h
# End Source File
# Begin Source File

SOURCE=.\radix\conversion.h
# End Source File
# Begin Source File

SOURCE=.\radix\core.h
# End Source File
# Begin Source File

SOURCE=.\radix\creutil.h
# End Source File
# Begin Source File

SOURCE=.\radix\data_exchange.h
# End Source File
# Begin Source File

SOURCE=.\radix\datetime_value.h
# End Source File
# Begin Source File

SOURCE=.\radix\dbimpl.h
# End Source File
# Begin Source File

SOURCE=.\radix\dd_.h
# End Source File
# Begin Source File

SOURCE=.\radix\DispatchPtrArray.h
# End Source File
# Begin Source File

SOURCE=.\radix\dispimpl.h
# End Source File
# Begin Source File

SOURCE=.\radix\dll_.h
# End Source File
# Begin Source File

SOURCE=.\radix\elements.h
# End Source File
# Begin Source File

SOURCE=.\radix\factory.h
# End Source File
# Begin Source File

SOURCE=.\radix\field_definition.h
# End Source File
# Begin Source File

SOURCE=.\radix\fixed_alloc.h
# End Source File
# Begin Source File

SOURCE=.\radix\Flags.h
# End Source File
# Begin Source File

SOURCE=.\radix\fspath.h
# End Source File
# Begin Source File

SOURCE=.\radix\hh.h
# End Source File
# Begin Source File

SOURCE=.\radix\html_file.h
# End Source File
# Begin Source File

SOURCE=.\radix\implementation.h
# End Source File
# Begin Source File

SOURCE=.\radix\inline.h
# End Source File
# Begin Source File

SOURCE=.\radix\install.h
# End Source File
# Begin Source File

SOURCE=.\radix\kbase.h
# End Source File
# Begin Source File

SOURCE=.\radix\keep_ptr.h
# End Source File
# Begin Source File

SOURCE=.\radix\language_string.h
# End Source File
# Begin Source File

SOURCE=.\radix\legacy_vms.h
# End Source File
# Begin Source File

SOURCE=.\radix\machine_event_central.h
# End Source File
# Begin Source File

SOURCE=.\radix\optr.h
# End Source File
# Begin Source File

SOURCE=.\radix\packset.h
# End Source File
# Begin Source File

SOURCE=.\radix\pipe.h
# End Source File
# Begin Source File

SOURCE=.\radix\plex.h
# End Source File
# Begin Source File

SOURCE=.\radix\preview_dc.h
# End Source File
# Begin Source File

SOURCE=.\radix\priv.h
# End Source File
# Begin Source File

SOURCE=.\radix\priv2.h
# End Source File
# Begin Source File

SOURCE=.\radix\process_data.h
# End Source File
# Begin Source File

SOURCE=.\radix\PushingRoutingFrame.h
# End Source File
# Begin Source File

SOURCE=.\radix\radix.h
# End Source File
# Begin Source File

SOURCE=.\radix\radix.inl
# End Source File
# Begin Source File

SOURCE=.\radix\radix_1.h
# End Source File
# Begin Source File

SOURCE=.\radix\radix_2.h
# End Source File
# Begin Source File

SOURCE=.\radix\radix_5.h
# End Source File
# Begin Source File

SOURCE=.\radix\Resource.h
# End Source File
# Begin Source File

SOURCE=.\radix\sensitive_ptr.h
# End Source File
# Begin Source File

SOURCE=.\radix\service.h
# End Source File
# Begin Source File

SOURCE=.\radix\simple_list.h
# End Source File
# Begin Source File

SOURCE=.\radix\sockets.h
# End Source File
# Begin Source File

SOURCE=.\radix\specialty.h
# End Source File
# Begin Source File

SOURCE=.\radix\spreadset.h
# End Source File
# Begin Source File

SOURCE=.\radix\StringUtil.h
# End Source File
# Begin Source File

SOURCE=.\radix\system.h
# End Source File
# Begin Source File

SOURCE=.\radix\this_build_number.h
# End Source File
# Begin Source File

SOURCE=.\radix\thread.h
# End Source File
# Begin Source File

SOURCE=.\radix\ui_str.h
# End Source File
# Begin Source File

SOURCE=.\radix\unhandled_report.h
# End Source File
# Begin Source File

SOURCE=.\radix\user.h
# End Source File
# Begin Source File

SOURCE=.\radix\userset.h
# End Source File
# Begin Source File

SOURCE=.\radix\util.h
# End Source File
# Begin Source File

SOURCE=.\radix\veriwell_musical_studio.h
# End Source File
# Begin Source File

SOURCE=.\radix\vms.h
# End Source File
# Begin Source File

SOURCE=.\radix\wait_cursor.h
# End Source File
# Begin Source File

SOURCE=.\radix\win_registry.h
# End Source File
# End Group
# Begin Group "ca2 Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ca2\application.h
# End Source File
# Begin Source File

SOURCE=.\ca2\ca2.h
# End Source File
# Begin Source File

SOURCE=.\ca2\ca2_2.h
# End Source File
# Begin Source File

SOURCE=.\ca2\datetime.h
# End Source File
# Begin Source File

SOURCE=.\ca2\file.h
# End Source File
# Begin Source File

SOURCE=.\ca2\file_system.h
# End Source File
# Begin Source File

SOURCE=.\ca2\html.h
# End Source File
# Begin Source File

SOURCE=.\ca2\inline.h
# End Source File
# Begin Source File

SOURCE=.\ca2\log.h
# End Source File
# Begin Source File

SOURCE=.\ca2\net.h
# End Source File
# Begin Source File

SOURCE=.\ca2\process.h
# End Source File
# Begin Source File

SOURCE=.\ca2\seed.h
# End Source File
# Begin Source File

SOURCE=.\ca2\socket_address.h
# End Source File
# Begin Source File

SOURCE=.\ca2\stra.h
# End Source File
# Begin Source File

SOURCE=.\ca2\url.h
# End Source File
# Begin Source File

SOURCE=.\ca2\url_domain.h
# End Source File
# End Group
# Begin Group "template Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\template\allocate.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\template\base.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\template\checked.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\template\core.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\template\debug.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\template\definition.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\template\exception.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\template\resource.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\template\simple_collection.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\template\string.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\template\templ.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\template\template.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\template\time.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\template\trace.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\template\trace_module_manager.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "collection Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\collection\array.h
# End Source File
# Begin Source File

SOURCE=.\collection\array_app_alloc.h
# End Source File
# Begin Source File

SOURCE=.\collection\array_parent_alloc.h
# End Source File
# Begin Source File

SOURCE=.\collection\array_ptr.h
# End Source File
# Begin Source File

SOURCE=.\collection\array_ptr_alloc.h
# End Source File
# Begin Source File

SOURCE=.\collection\array_ptr_copy.h
# End Source File
# Begin Source File

SOURCE=.\collection\array_smart_ptr.h
# End Source File
# Begin Source File

SOURCE=.\collection\base_array.h
# End Source File
# Begin Source File

SOURCE=.\collection\bit_array.h
# End Source File
# Begin Source File

SOURCE=.\collection\class_sort_array.h
# End Source File
# Begin Source File

SOURCE=.\collection\collection.h
# End Source File
# Begin Source File

SOURCE=.\collection\collection.inl
# End Source File
# Begin Source File

SOURCE=.\collection\comparable_array.h
# End Source File
# Begin Source File

SOURCE=.\collection\comparable_eq_array.h
# End Source File
# Begin Source File

SOURCE=.\collection\comparable_eq_list.h
# End Source File
# Begin Source File

SOURCE=.\collection\comparable_list.h
# End Source File
# Begin Source File

SOURCE=.\collection\comparable_primitive_array.h
# End Source File
# Begin Source File

SOURCE=.\collection\comparable_raw_array.h
# End Source File
# Begin Source File

SOURCE=.\collection\elements.h
# End Source File
# Begin Source File

SOURCE=.\collection\key_sort_array.h
# End Source File
# Begin Source File

SOURCE=.\collection\list.h
# End Source File
# Begin Source File

SOURCE=.\collection\map.h
# End Source File
# Begin Source File

SOURCE=.\collection\numeric_array.h
# End Source File
# Begin Source File

SOURCE=.\collection\point_array.h
# End Source File
# Begin Source File

SOURCE=.\collection\primitive_array.h
# End Source File
# Begin Source File

SOURCE=.\collection\raw_array.h
# End Source File
# Begin Source File

SOURCE=.\collection\rect_array.h
# End Source File
# Begin Source File

SOURCE=.\collection\sort.h
# End Source File
# Begin Source File

SOURCE=.\collection\sort_array.h
# End Source File
# Begin Source File

SOURCE=.\collection\string_to_string_map.h
# End Source File
# End Group
# Begin Group "gen Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\gen\application.h
# End Source File
# Begin Source File

SOURCE=.\gen\AStrArray.h
# End Source File
# Begin Source File

SOURCE=.\gen\AStringArray.h
# End Source File
# Begin Source File

SOURCE=.\gen\AStrSortArray.h
# End Source File
# Begin Source File

SOURCE=.\gen\AStrTokenizer.h
# End Source File
# Begin Source File

SOURCE=.\gen\Base2DArray.h
# End Source File
# Begin Source File

SOURCE=.\gen\base64.h
# End Source File
# Begin Source File

SOURCE=.\gen\base_enum.h
# End Source File
# Begin Source File

SOURCE=.\gen\base_rect.h
# End Source File
# Begin Source File

SOURCE=.\gen\base_rect_array.h
# End Source File
# Begin Source File

SOURCE=.\gen\bit.h
# End Source File
# Begin Source File

SOURCE=.\gen\ch.h
# End Source File
# Begin Source File

SOURCE=.\gen\ch_class.h
# End Source File
# Begin Source File

SOURCE=.\gen\command_line.h
# End Source File
# Begin Source File

SOURCE=.\gen\Debug.h
# End Source File
# Begin Source File

SOURCE=.\gen\file_association.h
# End Source File
# Begin Source File

SOURCE=.\gen\frame_window_interface.h
# End Source File
# Begin Source File

SOURCE=.\gen\full_pointer.h
# End Source File
# Begin Source File

SOURCE=.\gen\gen.h
# End Source File
# Begin Source File

SOURCE=.\gen\gen_0.h
# End Source File
# Begin Source File

SOURCE=.\gen\gen_1.h
# End Source File
# Begin Source File

SOURCE=.\gen\gen_2.h
# End Source File
# Begin Source File

SOURCE=.\gen\geometry.h
# End Source File
# Begin Source File

SOURCE=.\gen\go_thread.h
# End Source File
# Begin Source File

SOURCE=.\gen\international.h
# End Source File
# Begin Source File

SOURCE=.\gen\international2.h
# End Source File
# Begin Source File

SOURCE=.\gen\Keeper.h
# End Source File
# Begin Source File

SOURCE=.\gen\Logic.h
# End Source File
# Begin Source File

SOURCE=.\gen\math.h
# End Source File
# Begin Source File

SOURCE=.\gen\math_rng.h
# End Source File
# Begin Source File

SOURCE=.\gen\memory_file.h
# End Source File
# Begin Source File

SOURCE=.\gen\MessageWindow.h
# End Source File
# Begin Source File

SOURCE=.\gen\MessageWindowListener.h
# End Source File
# Begin Source File

SOURCE=.\gen\Muldiv32.h
# End Source File
# Begin Source File

SOURCE=.\gen\MulDiv64.h
# End Source File
# Begin Source File

SOURCE=.\gen\object.h
# End Source File
# Begin Source File

SOURCE=.\gen\parse.h
# End Source File
# Begin Source File

SOURCE=.\gen\pointer.h
# End Source File
# Begin Source File

SOURCE=.\gen\PointerManager.h
# End Source File
# Begin Source File

SOURCE=.\gen\process.h
# End Source File
# Begin Source File

SOURCE=.\gen\property.h
# End Source File
# Begin Source File

SOURCE=.\gen\ptri.h
# End Source File
# Begin Source File

SOURCE=.\gen\raw_pointer.h
# End Source File
# Begin Source File

SOURCE=.\gen\reference.h
# End Source File
# Begin Source File

SOURCE=.\gen\Savings.h
# End Source File
# Begin Source File

SOURCE=.\gen\se_exception.h
# End Source File
# Begin Source File

SOURCE=.\gen\signal.h
# End Source File
# Begin Source File

SOURCE=.\gen\simple_thread.h
# End Source File
# Begin Source File

SOURCE=.\gen\str.h
# End Source File
# Begin Source File

SOURCE=.\gen\system.h
# End Source File
# Begin Source File

SOURCE=.\gen\Timer.h
# End Source File
# Begin Source File

SOURCE=.\gen\TimerCallback.h
# End Source File
# Begin Source File

SOURCE=.\gen\TimerListener.h
# End Source File
# Begin Source File

SOURCE=.\gen\TimerWnd.h
# End Source File
# Begin Source File

SOURCE=.\gen\Util1.h
# End Source File
# Begin Source File

SOURCE=.\gen\var.h
# End Source File
# Begin Source File

SOURCE=.\gen\var_array.h
# End Source File
# Begin Source File

SOURCE=.\gen\variable_strict_compare.h
# End Source File
# Begin Source File

SOURCE=.\gen\WStrArray.h
# End Source File
# Begin Source File

SOURCE=.\gen\WString.h
# End Source File
# Begin Source File

SOURCE=.\gen\WStringArray.h
# End Source File
# Begin Source File

SOURCE=.\gen\WStringToPointer.h
# End Source File
# Begin Source File

SOURCE=.\gen\WStringToWString.h
# End Source File
# Begin Source File

SOURCE=.\gen\WStrTokenizer.h
# End Source File
# End Group
# Begin Group "multithreading Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\multithreading\event.h
# End Source File
# Begin Source File

SOURCE=.\multithreading\manual_reset_event.h
# End Source File
# Begin Source File

SOURCE=.\multithreading\multithreading.h
# End Source File
# Begin Source File

SOURCE=.\multithreading\multithreading.inl
# End Source File
# Begin Source File

SOURCE=.\multithreading\mutex.h
# End Source File
# Begin Source File

SOURCE=.\multithreading\plain_service.h
# End Source File
# Begin Source File

SOURCE=.\multithreading\service_base.h
# End Source File
# Begin Source File

SOURCE=.\multithreading\service_status.h
# End Source File
# Begin Source File

SOURCE=.\multithreading\sync_object.h
# End Source File
# Begin Source File

SOURCE=.\multithreading\thread_pool.h
# End Source File
# End Group
# Begin Group "user Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\user\application.h
# End Source File
# Begin Source File

SOURCE=.\user\buffer.h
# End Source File
# Begin Source File

SOURCE=.\user\button.h
# End Source File
# Begin Source File

SOURCE=.\user\check_box.h
# End Source File
# Begin Source File

SOURCE=.\user\check_interface.h
# End Source File
# Begin Source File

SOURCE=.\user\combo_box.h
# End Source File
# Begin Source File

SOURCE=.\user\control.h
# End Source File
# Begin Source File

SOURCE=.\user\control_event.h
# End Source File
# Begin Source File

SOURCE=.\user\control_property.h
# End Source File
# Begin Source File

SOURCE=.\user\create_context.h
# End Source File
# Begin Source File

SOURCE=.\user\create_view.h
# End Source File
# Begin Source File

SOURCE=.\user\document.h
# End Source File
# Begin Source File

SOURCE=.\user\document_interface.h
# End Source File
# Begin Source File

SOURCE=.\user\document_template.h
# End Source File
# Begin Source File

SOURCE=.\user\document_template_interface.h
# End Source File
# Begin Source File

SOURCE=.\user\draw_context.h
# End Source File
# Begin Source File

SOURCE=.\user\edit_plain_text.h
# End Source File
# Begin Source File

SOURCE=.\user\element_2d.h
# End Source File
# Begin Source File

SOURCE=.\user\elemental.h
# End Source File
# Begin Source File

SOURCE=.\user\form.h
# End Source File
# Begin Source File

SOURCE=.\user\form_callback.h
# End Source File
# Begin Source File

SOURCE=.\user\form_list.h
# End Source File
# Begin Source File

SOURCE=.\user\frame_window.h
# End Source File
# Begin Source File

SOURCE=.\user\frame_window_interface.h
# End Source File
# Begin Source File

SOURCE=.\user\front_end.h
# End Source File
# Begin Source File

SOURCE=.\user\front_end_schema.h
# End Source File
# Begin Source File

SOURCE=.\user\get_view.h
# End Source File
# Begin Source File

SOURCE=.\user\inline.h
# End Source File
# Begin Source File

SOURCE=.\user\interaction.inl
# End Source File
# Begin Source File

SOURCE=.\user\keyboard.h
# End Source File
# Begin Source File

SOURCE=.\user\keyboard_focus.h
# End Source File
# Begin Source File

SOURCE=.\user\list_cache.h
# End Source File
# Begin Source File

SOURCE=.\user\list_cache_interface.h
# End Source File
# Begin Source File

SOURCE=.\user\list_data.h
# End Source File
# Begin Source File

SOURCE=.\user\list_data_interface.h
# End Source File
# Begin Source File

SOURCE=.\user\list_header.h
# End Source File
# Begin Source File

SOURCE=.\user\mouse_focus.h
# End Source File
# Begin Source File

SOURCE=.\user\multiple_document_template.h
# End Source File
# Begin Source File

SOURCE=.\user\on_draw_interface.h
# End Source File
# Begin Source File

SOURCE=.\user\scroll_bar.h
# End Source File
# Begin Source File

SOURCE=.\user\scroll_view.h
# End Source File
# Begin Source File

SOURCE=.\user\simple_list_data.h
# End Source File
# Begin Source File

SOURCE=.\user\tool_tip_tool.h
# End Source File
# Begin Source File

SOURCE=.\user\tool_tip_window.h
# End Source File
# Begin Source File

SOURCE=.\user\tree.h
# End Source File
# Begin Source File

SOURCE=.\user\user.h
# End Source File
# Begin Source File

SOURCE=.\user\user_0.h
# End Source File
# Begin Source File

SOURCE=.\user\user_00.h
# End Source File
# Begin Source File

SOURCE=.\user\user_01.h
# End Source File
# Begin Source File

SOURCE=.\user\user_application.h
# End Source File
# Begin Source File

SOURCE=.\user\user_buffer.h
# End Source File
# Begin Source File

SOURCE=.\user\user_button.h
# End Source File
# Begin Source File

SOURCE=.\user\user_check_box.h
# End Source File
# Begin Source File

SOURCE=.\user\user_check_interface.h
# End Source File
# Begin Source File

SOURCE=.\user\user_combo_box.h
# End Source File
# Begin Source File

SOURCE=.\user\user_control.h
# End Source File
# Begin Source File

SOURCE=.\user\user_control_event.h
# End Source File
# Begin Source File

SOURCE=.\user\user_control_property.h
# End Source File
# Begin Source File

SOURCE=.\user\user_create_context.h
# End Source File
# Begin Source File

SOURCE=.\user\user_create_view.h
# End Source File
# Begin Source File

SOURCE=.\user\user_document.h
# End Source File
# Begin Source File

SOURCE=.\user\user_document_interface.h
# End Source File
# Begin Source File

SOURCE=.\user\user_document_template.h
# End Source File
# Begin Source File

SOURCE=.\user\user_document_template_interface.h
# End Source File
# Begin Source File

SOURCE=.\user\user_draw_context.h
# End Source File
# Begin Source File

SOURCE=.\user\user_edit_plain_text.h
# End Source File
# Begin Source File

SOURCE=.\user\user_element_2d.h
# End Source File
# Begin Source File

SOURCE=.\user\user_elemental.h
# End Source File
# Begin Source File

SOURCE=.\user\user_form.h
# End Source File
# Begin Source File

SOURCE=.\user\user_form_callback.h
# End Source File
# Begin Source File

SOURCE=.\user\user_form_list.h
# End Source File
# Begin Source File

SOURCE=.\user\user_frame_window.h
# End Source File
# Begin Source File

SOURCE=.\user\user_frame_window_interface.h
# End Source File
# Begin Source File

SOURCE=.\user\user_front_end.h
# End Source File
# Begin Source File

SOURCE=.\user\user_front_end_schema.h
# End Source File
# Begin Source File

SOURCE=.\user\user_get_view.h
# End Source File
# Begin Source File

SOURCE=.\user\user_inline.h
# End Source File
# Begin Source File

SOURCE=.\user\user_interaction.h
# End Source File
# Begin Source File

SOURCE=.\user\user_interaction.inl
# End Source File
# Begin Source File

SOURCE=.\user\user_keyboard.h
# End Source File
# Begin Source File

SOURCE=.\user\user_keyboard_focus.h
# End Source File
# Begin Source File

SOURCE=.\user\user_keyboard_layout.h
# End Source File
# Begin Source File

SOURCE=.\user\user_list.h
# End Source File
# Begin Source File

SOURCE=.\user\user_list_cache.h
# End Source File
# Begin Source File

SOURCE=.\user\user_list_cache_interface.h
# End Source File
# Begin Source File

SOURCE=.\user\user_list_data.h
# End Source File
# Begin Source File

SOURCE=.\user\user_list_data_interface.h
# End Source File
# Begin Source File

SOURCE=.\user\user_list_header.h
# End Source File
# Begin Source File

SOURCE=.\user\user_mouse_focus.h
# End Source File
# Begin Source File

SOURCE=.\user\user_multiple_document_template.h
# End Source File
# Begin Source File

SOURCE=.\user\user_on_draw_interface.h
# End Source File
# Begin Source File

SOURCE=.\user\user_place_holder.h
# End Source File
# Begin Source File

SOURCE=.\user\user_place_holder_container.h
# End Source File
# Begin Source File

SOURCE=.\user\user_plain_text_data.h
# End Source File
# Begin Source File

SOURCE=.\user\user_scroll_bar.h
# End Source File
# Begin Source File

SOURCE=.\user\user_scroll_view.h
# End Source File
# Begin Source File

SOURCE=.\user\user_simple_list_data.h
# End Source File
# Begin Source File

SOURCE=.\user\user_single_document_template.h
# End Source File
# Begin Source File

SOURCE=.\user\user_str.h
# End Source File
# Begin Source File

SOURCE=.\user\user_tab.h
# End Source File
# Begin Source File

SOURCE=.\user\user_tab_callback.h
# End Source File
# Begin Source File

SOURCE=.\user\user_text_interface.h
# End Source File
# Begin Source File

SOURCE=.\user\user_tool_tip_tool.h
# End Source File
# Begin Source File

SOURCE=.\user\user_tool_tip_window.h
# End Source File
# Begin Source File

SOURCE=.\user\user_tree.h
# End Source File
# Begin Source File

SOURCE=.\user\user_view.h
# End Source File
# Begin Source File

SOURCE=.\user\user_virtual_user_interface.h
# End Source File
# Begin Source File

SOURCE=.\user\user_window_draw_client_tool.h
# End Source File
# Begin Source File

SOURCE=.\user\user_window_draw_interface.h
# End Source File
# Begin Source File

SOURCE=.\user\user_window_id.h
# End Source File
# Begin Source File

SOURCE=.\user\user_window_interface.h
# End Source File
# Begin Source File

SOURCE=.\user\user_window_map.h
# End Source File
# Begin Source File

SOURCE=.\user\user_window_message.h
# End Source File
# Begin Source File

SOURCE=.\user\user_window_redraw_interface.h
# End Source File
# Begin Source File

SOURCE=.\user\user_window_util.h
# End Source File
# Begin Source File

SOURCE=.\user\user_xfplayer_view_line.h
# End Source File
# Begin Source File

SOURCE=.\user\user_xfplayer_view_line_selection.h
# End Source File
# Begin Source File

SOURCE=.\user\user_xfplayer_view_lines.h
# End Source File
# Begin Source File

SOURCE=.\user\view.h
# End Source File
# Begin Source File

SOURCE=.\user\virtual_user_interface.h
# End Source File
# Begin Source File

SOURCE=.\user\window_draw_client_tool.h
# End Source File
# Begin Source File

SOURCE=.\user\window_draw_interface.h
# End Source File
# Begin Source File

SOURCE=.\user\window_id.h
# End Source File
# Begin Source File

SOURCE=.\user\window_interface.h
# End Source File
# Begin Source File

SOURCE=.\user\window_map.h
# End Source File
# Begin Source File

SOURCE=.\user\window_message.h
# End Source File
# Begin Source File

SOURCE=.\user\window_redraw_interface.h
# End Source File
# Begin Source File

SOURCE=.\user\window_util.h
# End Source File
# Begin Source File

SOURCE=.\user\XfplayerViewLine.h
# End Source File
# Begin Source File

SOURCE=.\user\XfplayerViewLines.h
# End Source File
# Begin Source File

SOURCE=.\user\XfplayerViewLineSelection.h
# End Source File
# End Group
# Begin Group "userbase Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\userbase\simple_button.h
# End Source File
# Begin Source File

SOURCE=.\userbase\simple_child_frame.h
# End Source File
# Begin Source File

SOURCE=.\userbase\simple_combo_box.h
# End Source File
# Begin Source File

SOURCE=.\userbase\simple_edit.h
# End Source File
# Begin Source File

SOURCE=.\userbase\simple_edit_plain_text.h
# End Source File
# Begin Source File

SOURCE=.\userbase\simple_form_list_edit.h
# End Source File
# Begin Source File

SOURCE=.\userbase\simple_form_list_view.h
# End Source File
# Begin Source File

SOURCE=.\userbase\simple_frame_window.h
# End Source File
# Begin Source File

SOURCE=.\userbase\simple_list_control.h
# End Source File
# Begin Source File

SOURCE=.\userbase\simple_list_header_control.h
# End Source File
# Begin Source File

SOURCE=.\userbase\simple_list_view.h
# End Source File
# Begin Source File

SOURCE=.\userbase\simple_mdi_child_window.h
# End Source File
# Begin Source File

SOURCE=.\userbase\simple_mdi_frame_window.h
# End Source File
# Begin Source File

SOURCE=.\userbase\simple_menu_bar.h
# End Source File
# Begin Source File

SOURCE=.\userbase\simple_push_button.h
# End Source File
# Begin Source File

SOURCE=.\userbase\simple_scroll_bar.h
# End Source File
# Begin Source File

SOURCE=.\userbase\simple_static.h
# End Source File
# Begin Source File

SOURCE=.\userbase\simple_status_bar.h
# End Source File
# Begin Source File

SOURCE=.\userbase\simple_tab_control.h
# End Source File
# Begin Source File

SOURCE=.\userbase\simple_tab_view.h
# End Source File
# Begin Source File

SOURCE=.\userbase\simple_tool_bar.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_application.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_bitmap_button.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_button.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_button_control.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_combo_box.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_control_bar.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_dock_context.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_dock_state.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_document.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_document_manager.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_document_template.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_edit_plain_text.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_edit_plain_text_view.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_elastic_slider.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_form_list.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_form_view.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_frame_window.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_frame_window_interface.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_image_manager.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_impl.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_mdi_child_window.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_mdi_frame_window.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_menu.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_menu_base.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_menu_button.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_menu_central.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_menu_item.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_menu_list_view.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_menu_list_window.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_meta_button.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_multiple_document_template.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_notification_area.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_notify_icon.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_notify_icon_listener.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_scroll_view.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_simple.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_single_document_template.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_split_bar.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_split_layout.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_split_view.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_split_window.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_static.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_status_bar.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_step_slider.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_tab_control.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_tab_view.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_tab_view_update_hint.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_tool_bar.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_tool_bar_control.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_tree_window.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_view.h
# End Source File
# Begin Source File

SOURCE=.\userbase\userbase_window_map.h
# End Source File
# End Group
# Begin Group "userex Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\userex\calendar.h
# End Source File
# Begin Source File

SOURCE=.\userex\calendar_interface.h
# End Source File
# Begin Source File

SOURCE=.\userex\clock.h
# End Source File
# Begin Source File

SOURCE=.\userex\clock_interface.h
# End Source File
# Begin Source File

SOURCE=.\userex\dialog.h
# End Source File
# Begin Source File

SOURCE=.\userex\form_child_frame.h
# End Source File
# Begin Source File

SOURCE=.\userex\form_document.h
# End Source File
# Begin Source File

SOURCE=.\userex\form_frame.h
# End Source File
# Begin Source File

SOURCE=.\userex\form_update_hint.h
# End Source File
# Begin Source File

SOURCE=.\userex\form_view.h
# End Source File
# Begin Source File

SOURCE=.\userex\menu_document.h
# End Source File
# Begin Source File

SOURCE=.\userex\menu_frame.h
# End Source File
# Begin Source File

SOURCE=.\userex\menu_view.h
# End Source File
# Begin Source File

SOURCE=.\userex\mini_dock_frame_window.h
# End Source File
# Begin Source File

SOURCE=.\userex\pane_split_view.h
# End Source File
# Begin Source File

SOURCE=.\userex\pane_tab_view.h
# End Source File
# Begin Source File

SOURCE=.\userex\pane_view.h
# End Source File
# Begin Source File

SOURCE=.\userex\split_view.h
# End Source File
# Begin Source File

SOURCE=.\userex\userex.h
# End Source File
# End Group
# Begin Group "html Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\html\application.h
# End Source File
# Begin Source File

SOURCE=.\html\cell.h
# End Source File
# Begin Source File

SOURCE=.\html\document.h
# End Source File
# Begin Source File

SOURCE=.\html\document_container.h
# End Source File
# Begin Source File

SOURCE=.\html\elemental.h
# End Source File
# Begin Source File

SOURCE=.\html\file.h
# End Source File
# Begin Source File

SOURCE=.\html\font.h
# End Source File
# Begin Source File

SOURCE=.\html\form.h
# End Source File
# Begin Source File

SOURCE=.\html\html.h
# End Source File
# Begin Source File

SOURCE=.\html\html_attribute.h
# End Source File
# Begin Source File

SOURCE=.\html\html_base.h
# End Source File
# Begin Source File

SOURCE=.\html\html_child_frame.h
# End Source File
# Begin Source File

SOURCE=.\html\html_document.h
# End Source File
# Begin Source File

SOURCE=.\html\html_ex.h
# End Source File
# Begin Source File

SOURCE=.\html\html_form.h
# End Source File
# Begin Source File

SOURCE=.\html\html_form_view.h
# End Source File
# Begin Source File

SOURCE=.\html\html_frame.h
# End Source File
# Begin Source File

SOURCE=.\html\html_reader.h
# End Source File
# Begin Source File

SOURCE=.\html\html_tag.h
# End Source File
# Begin Source File

SOURCE=.\html\html_value.h
# End Source File
# Begin Source File

SOURCE=.\html\html_view.h
# End Source File
# Begin Source File

SOURCE=.\html\html_view_update_hint.h
# End Source File
# Begin Source File

SOURCE=.\html\image.h
# End Source File
# Begin Source File

SOURCE=.\html\input_button.h
# End Source File
# Begin Source File

SOURCE=.\html\input_check_box.h
# End Source File
# Begin Source File

SOURCE=.\html\input_text.h
# End Source File
# Begin Source File

SOURCE=.\html\LiteHTMLAttributes.h
# End Source File
# Begin Source File

SOURCE=.\html\LiteHTMLCommon.h
# End Source File
# Begin Source File

SOURCE=.\html\LiteHTMLEntityResolver.h
# End Source File
# Begin Source File

SOURCE=.\html\LiteHTMLReader.h
# End Source File
# Begin Source File

SOURCE=.\html\LiteHTMLTag.h
# End Source File
# Begin Source File

SOURCE=.\html\signal.h
# End Source File
# Begin Source File

SOURCE=.\html\style.h
# End Source File
# Begin Source File

SOURCE=.\html\style_sheet.h
# End Source File
# Begin Source File

SOURCE=.\html\style_sheet_array.h
# End Source File
# Begin Source File

SOURCE=.\html\table.h
# End Source File
# Begin Source File

SOURCE=.\html\table_elemental.h
# End Source File
# Begin Source File

SOURCE=.\html\table_row.h
# End Source File
# Begin Source File

SOURCE=.\html\text.h
# End Source File
# End Group
# Begin Group "primitive Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\primitive\align.h
# End Source File
# Begin Source File

SOURCE=.\primitive\check.h
# End Source File
# Begin Source File

SOURCE=.\primitive\color.h
# End Source File
# Begin Source File

SOURCE=.\primitive\count.h
# End Source File
# Begin Source File

SOURCE=.\primitive\id.h
# End Source File
# Begin Source File

SOURCE=.\primitive\id_space.h
# End Source File
# Begin Source File

SOURCE=.\primitive\img.h
# End Source File
# Begin Source File

SOURCE=.\primitive\index.h
# End Source File
# Begin Source File

SOURCE=.\primitive\int_biunique.h
# End Source File
# Begin Source File

SOURCE=.\primitive\logic.h
# End Source File
# Begin Source File

SOURCE=.\primitive\memory.h
# End Source File
# Begin Source File

SOURCE=.\primitive\memory_container.h
# End Source File
# Begin Source File

SOURCE=.\primitive\memory_file.h
# End Source File
# Begin Source File

SOURCE=.\primitive\memory_operator.h
# End Source File
# Begin Source File

SOURCE=.\primitive\natural.h
# End Source File
# Begin Source File

SOURCE=.\primitive\numeric_info.h
# End Source File
# Begin Source File

SOURCE=.\primitive\point.h
# End Source File
# Begin Source File

SOURCE=.\primitive\primitive.h
# End Source File
# Begin Source File

SOURCE=.\primitive\rectangle.h
# End Source File
# Begin Source File

SOURCE=.\primitive\scalar.h
# End Source File
# Begin Source File

SOURCE=.\primitive\shared_file.h
# End Source File
# Begin Source File

SOURCE=.\primitive\shared_memory.h
# End Source File
# Begin Source File

SOURCE=.\primitive\simple_string.h
# End Source File
# Begin Source File

SOURCE=.\primitive\size.h
# End Source File
# Begin Source File

SOURCE=.\primitive\string.h
# End Source File
# Begin Source File

SOURCE=.\primitive\types.h
# End Source File
# End Group
# Begin Group "colorertake5 Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\colorertake5\application.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\base_editor.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\colorertake5.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\cregexp.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\default_error_handler.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\editor_listener.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\error_handler.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\error_handler_writer.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\exception.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\features.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\file_input_source.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\file_type.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\file_type_impl.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\file_writer.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\hrc_parser.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\hrc_parser_helpers.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\hrc_parser_impl.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\line_region.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\line_regions_compact_support.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\line_regions_support.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\line_source.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\logging.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\memory_chunks.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\memory_file.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\memory_operator.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\outline_item.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\outliner.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\pair_match.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\parsed_line_writer.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\parser_factory.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\parser_factory_exception.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\region.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\region_define.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\region_handler.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\region_mapper.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\region_mapper_impl.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\scheme.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\shared_input_source.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\string_buffer.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\styled_hrd_mapper.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\styled_region.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\text_console_viewer.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\text_hrd_mapper.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\text_lines.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\text_parser.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\text_parser_helpers.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\text_parser_impl.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\text_region.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\Writer.h
# End Source File
# Begin Source File

SOURCE=.\colorertake5\xmldom.h
# End Source File
# End Group
# Begin Group "ca2api002_00002 Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ca2api002_00002\application.h
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\BZipHelper.h
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\ca04_compress.h
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\ca04_patch.h
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\ca05_crypt.h
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\ca08_application.h
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\ca27_email.h
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\ca27_http.h
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\ca27_http_get_socket.h
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\ca27_user.h
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\ca2api002_00002.h
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\ca36_file.h
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\compress.h
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\copydesk.h
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\CRC.h
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\CRCFast.h
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\crypt.h
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\email.h
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\file.h
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\GZipHelper.h
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\http.h
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\http_get_socket.h
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\ip_enum.h
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\nessie.h
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\patch.h
# End Source File
# Begin Source File

SOURCE=.\ca2api002_00002\user.h
# End Source File
# End Group
# Begin Group "sockets Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sockets\ajp13.h
# End Source File
# Begin Source File

SOURCE=.\sockets\Ajp13Socket.h
# End Source File
# Begin Source File

SOURCE=.\sockets\AjpBaseSocket.h
# End Source File
# Begin Source File

SOURCE=.\sockets\application_interface.h
# End Source File
# Begin Source File

SOURCE=.\sockets\config.h
# End Source File
# Begin Source File

SOURCE=.\sockets\Event.h
# End Source File
# Begin Source File

SOURCE=.\sockets\EventHandler.h
# End Source File
# Begin Source File

SOURCE=.\sockets\EventTime.h
# End Source File
# Begin Source File

SOURCE=.\sockets\Exception.h
# End Source File
# Begin Source File

SOURCE=.\sockets\http_base_socket.h
# End Source File
# Begin Source File

SOURCE=.\sockets\http_client_socket.h
# End Source File
# Begin Source File

SOURCE=.\sockets\http_cookie.h
# End Source File
# Begin Source File

SOURCE=.\sockets\http_debug_socket.h
# End Source File
# Begin Source File

SOURCE=.\sockets\http_file.h
# End Source File
# Begin Source File

SOURCE=.\sockets\http_form.h
# End Source File
# Begin Source File

SOURCE=.\sockets\http_get_socket.h
# End Source File
# Begin Source File

SOURCE=.\sockets\http_memory_file.h
# End Source File
# Begin Source File

SOURCE=.\sockets\http_post_socket.h
# End Source File
# Begin Source File

SOURCE=.\sockets\http_put_socket.h
# End Source File
# Begin Source File

SOURCE=.\sockets\http_request.h
# End Source File
# Begin Source File

SOURCE=.\sockets\http_response.h
# End Source File
# Begin Source File

SOURCE=.\sockets\http_socket.h
# End Source File
# Begin Source File

SOURCE=.\sockets\http_transaction.h
# End Source File
# Begin Source File

SOURCE=.\sockets\http_tunnel.h
# End Source File
# Begin Source File

SOURCE=.\sockets\httpd_socket.h
# End Source File
# Begin Source File

SOURCE=.\sockets\IBase.h
# End Source File
# Begin Source File

SOURCE=.\sockets\IEventHandler.h
# End Source File
# Begin Source File

SOURCE=.\sockets\IEventOwner.h
# End Source File
# Begin Source File

SOURCE=.\sockets\ipv4_address.h
# End Source File
# Begin Source File

SOURCE=.\sockets\ipv6_address.h
# End Source File
# Begin Source File

SOURCE=.\sockets\listen_socket.h
# End Source File
# Begin Source File

SOURCE=.\sockets\resolv_server.h
# End Source File
# Begin Source File

SOURCE=.\sockets\resolv_socket.h
# End Source File
# Begin Source File

SOURCE=.\sockets\sctp_socket.h
# End Source File
# Begin Source File

SOURCE=.\sockets\Semaphore.h
# End Source File
# Begin Source File

SOURCE=.\sockets\sip_base.h
# End Source File
# Begin Source File

SOURCE=.\sockets\sip_base_client_socket.h
# End Source File
# Begin Source File

SOURCE=.\sockets\sip_callback.h
# End Source File
# Begin Source File

SOURCE=.\sockets\sip_client.h
# End Source File
# Begin Source File

SOURCE=.\sockets\sip_event.h
# End Source File
# Begin Source File

SOURCE=.\sockets\sip_request.h
# End Source File
# Begin Source File

SOURCE=.\sockets\sip_response.h
# End Source File
# Begin Source File

SOURCE=.\sockets\sip_server.h
# End Source File
# Begin Source File

SOURCE=.\sockets\sip_socket.h
# End Source File
# Begin Source File

SOURCE=.\sockets\sip_tcp_client_socket.h
# End Source File
# Begin Source File

SOURCE=.\sockets\sip_transaction.h
# End Source File
# Begin Source File

SOURCE=.\sockets\sip_udp_client_socket.h
# End Source File
# Begin Source File

SOURCE=.\sockets\smtp_socket.h
# End Source File
# Begin Source File

SOURCE=.\sockets\smtpd_socket.h
# End Source File
# Begin Source File

SOURCE=.\sockets\Socket.h
# End Source File
# Begin Source File

SOURCE=.\sockets\socket_handler.h
# End Source File
# Begin Source File

SOURCE=.\sockets\socket_handler_base.h
# End Source File
# Begin Source File

SOURCE=.\sockets\sockets.h
# End Source File
# Begin Source File

SOURCE=.\sockets\SSLInitializer.h
# End Source File
# Begin Source File

SOURCE=.\sockets\StdLog.h
# End Source File
# Begin Source File

SOURCE=.\sockets\stream_socket.h
# End Source File
# Begin Source File

SOURCE=.\sockets\tcp_socket.h
# End Source File
# Begin Source File

SOURCE=.\sockets\trace_log.h
# End Source File
# Begin Source File

SOURCE=.\sockets\udp_socket.h
# End Source File
# End Group
# Begin Group "ex2 Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ex2\Ex17MemoryFile.h
# End Source File
# Begin Source File

SOURCE=.\ex2\Ex2.h
# End Source File
# Begin Source File

SOURCE=.\ex2\ex2_application.h
# End Source File
# Begin Source File

SOURCE=.\ex2\ex2_file_set.h
# End Source File
# Begin Source File

SOURCE=.\ex2\ex2_folder_watch.h
# End Source File
# End Group
# Begin Group "icube Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\icube\application.h
# End Source File
# Begin Source File

SOURCE=.\icube\icube.h
# End Source File
# End Group
# Begin Group "ex1 Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ex1\Ex1.h
# End Source File
# Begin Source File

SOURCE=.\ex1\ex1_0.h
# End Source File
# Begin Source File

SOURCE=.\ex1\ex1_1.h
# End Source File
# Begin Source File

SOURCE=.\ex1\ex1_application.h
# End Source File
# Begin Source File

SOURCE=.\ex1\ex1_buffered_file.h
# End Source File
# Begin Source File

SOURCE=.\ex1\ex1_edit_file.h
# End Source File
# Begin Source File

SOURCE=.\ex1\ex1_exception.h
# End Source File
# Begin Source File

SOURCE=.\ex1\ex1_file.h
# End Source File
# Begin Source File

SOURCE=.\ex1\ex1_file_set.h
# End Source File
# Begin Source File

SOURCE=.\ex1\ex1_file_system.h
# End Source File
# Begin Source File

SOURCE=.\ex1\ex1_resource.h
# End Source File
# Begin Source File

SOURCE=.\ex1\ex1_serializable.h
# End Source File
# Begin Source File

SOURCE=.\ex1\ex1_str_stream.h
# End Source File
# Begin Source File

SOURCE=.\ex1\ex1_stream.h
# End Source File
# Begin Source File

SOURCE=.\ex1\ex1_stream2.h
# End Source File
# Begin Source File

SOURCE=.\ex1\ex1_text_file.h
# End Source File
# Begin Source File

SOURCE=.\ex1\ex1_tree_data.h
# End Source File
# End Group
# Begin Group "mus Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\mus\Attributes.h
# End Source File
# Begin Source File

SOURCE=.\mus\Intrisics.h
# End Source File
# Begin Source File

SOURCE=.\mus\KaraokeUtil.h
# End Source File
# Begin Source File

SOURCE=.\mus\LyricTrack.h
# End Source File
# Begin Source File

SOURCE=.\mus\LyricTracks.h
# End Source File
# Begin Source File

SOURCE=.\mus\LyricType1Events.h
# End Source File
# Begin Source File

SOURCE=.\mus\Microke1.h
# End Source File
# Begin Source File

SOURCE=.\mus\Midi.h
# End Source File
# Begin Source File

SOURCE=.\mus\MidiCentral.h
# End Source File
# Begin Source File

SOURCE=.\mus\MidiCentralContainer.h
# End Source File
# Begin Source File

SOURCE=.\mus\MidiCentralListener.h
# End Source File
# Begin Source File

SOURCE=.\mus\MidiDocHelper.h
# End Source File
# Begin Source File

SOURCE=.\mus\MidiEventBase.h
# End Source File
# Begin Source File

SOURCE=.\mus\MidiEventsV1.h
# End Source File
# Begin Source File

SOURCE=.\mus\MidiEventV001.h
# End Source File
# Begin Source File

SOURCE=.\mus\MidiEventV007.h
# End Source File
# Begin Source File

SOURCE=.\mus\MidiEventV008.h
# End Source File
# Begin Source File

SOURCE=.\mus\MidiEventV016.h
# End Source File
# Begin Source File

SOURCE=.\mus\MidiEventV507.h
# End Source File
# Begin Source File

SOURCE=.\mus\MidiEventV508.h
# End Source File
# Begin Source File

SOURCE=.\mus\MidiException.h
# End Source File
# Begin Source File

SOURCE=.\mus\MidiFile.h
# End Source File
# Begin Source File

SOURCE=.\mus\MidiPlayer.h
# End Source File
# Begin Source File

SOURCE=.\mus\MidiPlayerCallback.h
# End Source File
# Begin Source File

SOURCE=.\mus\midiplayercallbackinterface.h
# End Source File
# Begin Source File

SOURCE=.\mus\MidiPlayerInterface.h
# End Source File
# Begin Source File

SOURCE=.\mus\MidiPlayerWnd.h
# End Source File
# Begin Source File

SOURCE=.\mus\Midiplyr.h
# End Source File
# Begin Source File

SOURCE=.\mus\MidiSequence.h
# End Source File
# Begin Source File

SOURCE=.\mus\MidiSequenceThread.h
# End Source File
# Begin Source File

SOURCE=.\mus\MidiTrack.h
# End Source File
# Begin Source File

SOURCE=.\mus\MidiTrackBase.h
# End Source File
# Begin Source File

SOURCE=.\mus\MidiTracks.h
# End Source File
# Begin Source File

SOURCE=.\mus\MidiTrackV008.h
# End Source File
# Begin Source File

SOURCE=.\mus\MidiUtil.h
# End Source File
# Begin Source File

SOURCE=.\mus\MidiViewHelper.h
# End Source File
# Begin Source File

SOURCE=.\mus\MidiWorkEventV3A.h
# End Source File
# Begin Source File

SOURCE=.\mus\MidiWorkTrackV3.h
# End Source File
# Begin Source File

SOURCE=.\mus\MultimediaFile.h
# End Source File
# Begin Source File

SOURCE=.\mus\mus.h
# End Source File
# Begin Source File

SOURCE=.\mus\mus_intrisics.h
# End Source File
# Begin Source File

SOURCE=.\mus\SoftKaraokeInfo.h
# End Source File
# Begin Source File

SOURCE=.\mus\Star350.h
# End Source File
# Begin Source File

SOURCE=.\mus\Star350EventBase.h
# End Source File
# Begin Source File

SOURCE=.\mus\Star350EventTrack.h
# End Source File
# Begin Source File

SOURCE=.\mus\Star350EventV001.h
# End Source File
# Begin Source File

SOURCE=.\mus\Star350EventV008.h
# End Source File
# Begin Source File

SOURCE=.\mus\Star350EventV016.h
# End Source File
# Begin Source File

SOURCE=.\mus\Star350File.h
# End Source File
# Begin Source File

SOURCE=.\mus\Star350InfoHeader.h
# End Source File
# Begin Source File

SOURCE=.\mus\Star350LyricTrack.h
# End Source File
# Begin Source File

SOURCE=.\mus\Star350LyricTracks.h
# End Source File
# Begin Source File

SOURCE=.\mus\Star350TrackBase.h
# End Source File
# Begin Source File

SOURCE=.\mus\Star350Tracks.h
# End Source File
# Begin Source File

SOURCE=.\mus\Star350TrackV008.h
# End Source File
# Begin Source File

SOURCE=.\mus\StdMidiFile.h
# End Source File
# Begin Source File

SOURCE=.\mus\Tune1000Info.h
# End Source File
# Begin Source File

SOURCE=.\mus\Uiutils.h
# End Source File
# Begin Source File

SOURCE=.\mus\vmsgentempl.h
# End Source File
# Begin Source File

SOURCE=.\mus\VmsMusDll.h
# End Source File
# Begin Source File

SOURCE=.\mus\vmsmusresource.h
# End Source File
# Begin Source File

SOURCE=.\mus\Xf.h
# End Source File
# Begin Source File

SOURCE=.\mus\XFInfoHeader.h
# End Source File
# Begin Source File

SOURCE=.\mus\XFInfoHeaderLS.h
# End Source File
# Begin Source File

SOURCE=.\mus\XFInfoHeaders.h
# End Source File
# End Group
# Begin Group "mediaplay"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\mediaplay\data.h
# End Source File
# Begin Source File

SOURCE=.\mediaplay\document.h
# End Source File
# Begin Source File

SOURCE=.\mediaplay\karaoke.h
# End Source File
# Begin Source File

SOURCE=.\mediaplay\mediaplay.h
# End Source File
# Begin Source File

SOURCE=.\mediaplay\playlist_callback.h
# End Source File
# Begin Source File

SOURCE=.\mediaplay\record_notify_view.h
# End Source File
# Begin Source File

SOURCE=.\mediaplay\view.h
# End Source File
# Begin Source File

SOURCE=.\mediaplay\view_interface.h
# End Source File
# Begin Source File

SOURCE=.\mediaplay\view_update_hint.h
# End Source File
# End Group
# Begin Group "mediaplaylist Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\mediaplaylist\Enum.h
# End Source File
# Begin Source File

SOURCE=.\mediaplaylist\mediaplaylist.h
# End Source File
# Begin Source File

SOURCE=.\mediaplaylist\PlaylistAppInterface.h
# End Source File
# Begin Source File

SOURCE=.\mediaplaylist\PlaylistCallback.h
# End Source File
# Begin Source File

SOURCE=.\mediaplaylist\PlaylistCallbackContainer.h
# End Source File
# Begin Source File

SOURCE=.\mediaplaylist\PlaylistCallbackContainerInterface.h
# End Source File
# Begin Source File

SOURCE=.\mediaplaylist\PlaylistCallbackInterface.h
# End Source File
# Begin Source File

SOURCE=.\mediaplaylist\PlaylistCentral.h
# End Source File
# Begin Source File

SOURCE=.\mediaplaylist\PlaylistCentralCallbackInterface.h
# End Source File
# Begin Source File

SOURCE=.\mediaplaylist\PlaylistCentralContainer.h
# End Source File
# Begin Source File

SOURCE=.\mediaplaylist\PlaylistDoc.h
# End Source File
# Begin Source File

SOURCE=.\mediaplaylist\PlaylistFrame.h
# End Source File
# Begin Source File

SOURCE=.\mediaplaylist\PlaylistListView.h
# End Source File
# Begin Source File

SOURCE=.\mediaplaylist\PlaylistView.h
# End Source File
# Begin Source File

SOURCE=.\mediaplaylist\PlaylistViewUpdateHint.h
# End Source File
# End Group
# Begin Group "mediamanager Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\mediamanager\AlbumBuild.h
# End Source File
# Begin Source File

SOURCE=.\mediamanager\AlbumBuildThread.h
# End Source File
# Begin Source File

SOURCE=.\mediamanager\AlbumBuildWnd.h
# End Source File
# Begin Source File

SOURCE=.\mediamanager\mediamanager.h
# End Source File
# Begin Source File

SOURCE=.\mediamanager\MediaManagerImpl.h
# End Source File
# Begin Source File

SOURCE=.\mediamanager\playlist_callback.h
# End Source File
# End Group
# Begin Group "mail Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\mail\application_interface.h
# End Source File
# Begin Source File

SOURCE=.\mail\child_frame.h
# End Source File
# Begin Source File

SOURCE=.\mail\configuration.h
# End Source File
# Begin Source File

SOURCE=.\mail\db_pop3.h
# End Source File
# Begin Source File

SOURCE=.\mail\document.h
# End Source File
# Begin Source File

SOURCE=.\mail\folder_list.h
# End Source File
# Begin Source File

SOURCE=.\mail\folder_list_interface.h
# End Source File
# Begin Source File

SOURCE=.\mail\frame.h
# End Source File
# Begin Source File

SOURCE=.\mail\mail.h
# End Source File
# Begin Source File

SOURCE=.\mail\mail_account.h
# End Source File
# Begin Source File

SOURCE=.\mail\mail_child_frame.h
# End Source File
# Begin Source File

SOURCE=.\mail\mail_document.h
# End Source File
# Begin Source File

SOURCE=.\mail\mail_frame.h
# End Source File
# Begin Source File

SOURCE=.\mail\mail_list.h
# End Source File
# Begin Source File

SOURCE=.\mail\mail_list_interface.h
# End Source File
# Begin Source File

SOURCE=.\mail\mail_view.h
# End Source File
# Begin Source File

SOURCE=.\mail\main_document.h
# End Source File
# Begin Source File

SOURCE=.\mail\main_frame.h
# End Source File
# Begin Source File

SOURCE=.\mail\pop3.h
# End Source File
# Begin Source File

SOURCE=.\mail\pop3_socket.h
# End Source File
# Begin Source File

SOURCE=.\mail\right_pane_view.h
# End Source File
# Begin Source File

SOURCE=.\mail\simple_pop3.h
# End Source File
# Begin Source File

SOURCE=.\mail\view.h
# End Source File
# Begin Source File

SOURCE=.\mail\views.h
# End Source File
# End Group
# Begin Group "bergedge Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\bergedge\application.h
# End Source File
# Begin Source File

SOURCE=.\bergedge\bergedge.h
# End Source File
# Begin Source File

SOURCE=.\bergedge\document.h
# End Source File
# Begin Source File

SOURCE=.\bergedge\form_callback.h
# End Source File
# Begin Source File

SOURCE=.\bergedge\frame.h
# End Source File
# Begin Source File

SOURCE=.\bergedge\pane_view.h
# End Source File
# Begin Source File

SOURCE=.\bergedge\pane_view_update_hint.h
# End Source File
# Begin Source File

SOURCE=.\bergedge\system.h
# End Source File
# Begin Source File

SOURCE=.\bergedge\system_map.h
# End Source File
# Begin Source File

SOURCE=.\bergedge\view.h
# End Source File
# End Group
# Begin Group "platform Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\platform\application.h
# End Source File
# Begin Source File

SOURCE=.\platform\document.h
# End Source File
# Begin Source File

SOURCE=.\platform\frame.h
# End Source File
# Begin Source File

SOURCE=.\platform\pane_view.h
# End Source File
# Begin Source File

SOURCE=.\platform\pane_view_update_hint.h
# End Source File
# Begin Source File

SOURCE=.\platform\platform.h
# End Source File
# Begin Source File

SOURCE=.\platform\Resource.h
# End Source File
# Begin Source File

SOURCE=.\platform\view.h
# End Source File
# End Group
# Begin Group "nature Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\nature\appearance_view.h
# End Source File
# Begin Source File

SOURCE=.\nature\application.h
# End Source File
# Begin Source File

SOURCE=.\nature\database.h
# End Source File
# Begin Source File

SOURCE=.\nature\document.h
# End Source File
# Begin Source File

SOURCE=.\nature\frame.h
# End Source File
# Begin Source File

SOURCE=.\nature\nature.h
# End Source File
# Begin Source File

SOURCE=.\nature\pane_view.h
# End Source File
# Begin Source File

SOURCE=.\nature\pane_view_update_hint.h
# End Source File
# Begin Source File

SOURCE=.\nature\view.h
# End Source File
# End Group
# Begin Group "fontopus Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\fontopus\application.h
# End Source File
# Begin Source File

SOURCE=.\fontopus\fontopus.h
# End Source File
# End Group
# Begin Group "ca2_cgcly24_84 Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ca2_cgcly24_84\application.h
# End Source File
# Begin Source File

SOURCE=.\ca2_cgcly24_84\ca2_cgcly24_84.h
# End Source File
# End Group
# Begin Group "ca2_cstx23_77 Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ca2_cstx23_77\application.h
# End Source File
# Begin Source File

SOURCE=.\ca2_cstx23_77\ca2_cstx23_77.h
# End Source File
# End Group
# Begin Group "filemanager Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\filemanager\Application.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\application2.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\ContextMenu.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\file_manager_form_child_frame.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\file_manager_form_document.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\file_manager_form_update_hint.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\file_manager_form_view.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\file_manager_operation_child_frame.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\file_manager_operation_document.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\file_manager_operation_info_view.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\file_manager_operation_list_view.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\file_manager_operation_thread.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\file_manager_operation_view.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\file_operation.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\FileManager.2.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\filemanager.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\filemanager_application.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\filemanager_folder_list_view.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\filemanager_folder_selection_list_view.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\filemanager_form_child_frame.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\filemanager_form_document.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\filemanager_form_update_hint.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\filemanager_form_view.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\filemanager_icon.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\filemanager_item_action.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\filemanager_operation_child_frame.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\filemanager_operation_document.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\filemanager_operation_info_view.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\filemanager_operation_list_view.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\filemanager_operation_thread.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\filemanager_operation_view.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\FileManagerCallbackInterface.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\FileManagerChildFrame.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\FileManagerDDX.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\FileManagerDoc.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\FileManagerFileListCallback.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\FileManagerFrame.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\FileManagerInterface.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\FileManagerLeftView.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\FileManagerMainFrame.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\FileManagerPathView.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\FileManagerTabView.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\FileManagerTemplate.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\FileManagerView.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\FileManagerViewInterface.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\FileManagerViewUpdateHint.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\folder_list_view.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\folder_selection_list_view.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\icon.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\item_action.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\SimpleFileListInterface.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\SimpleFileListView.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\SimpleFilePropertiesForm.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\SimpleFolderListInterface.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\SimpleFolderListView.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\SimpleFolderTreeInterface.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\SimpleFolderTreeView.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\SimplePreview.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\SimplePreviewInterface.h
# End Source File
# Begin Source File

SOURCE=.\filemanager\XfplayerDialogBar.h
# End Source File
# End Group
# Begin Group "calculator Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\calculator\application.h
# End Source File
# Begin Source File

SOURCE=.\calculator\calculator.h
# End Source File
# Begin Source File

SOURCE=.\calculator\calculator_class.h
# End Source File
# Begin Source File

SOURCE=.\calculator\datetime_element.h
# End Source File
# Begin Source File

SOURCE=.\calculator\datetime_parser.h
# End Source File
# Begin Source File

SOURCE=.\calculator\datetime_scanner.h
# End Source File
# Begin Source File

SOURCE=.\calculator\datetime_token.h
# End Source File
# Begin Source File

SOURCE=.\calculator\document.h
# End Source File
# Begin Source File

SOURCE=.\calculator\element.h
# End Source File
# Begin Source File

SOURCE=.\calculator\frame.h
# End Source File
# Begin Source File

SOURCE=.\calculator\numeric_element.h
# End Source File
# Begin Source File

SOURCE=.\calculator\numeric_parser.h
# End Source File
# Begin Source File

SOURCE=.\calculator\numeric_scanner.h
# End Source File
# Begin Source File

SOURCE=.\calculator\numeric_token.h
# End Source File
# Begin Source File

SOURCE=.\calculator\numeric_value.h
# End Source File
# Begin Source File

SOURCE=.\calculator\parser.h
# End Source File
# Begin Source File

SOURCE=.\calculator\scanner.h
# End Source File
# Begin Source File

SOURCE=.\calculator\view.h
# End Source File
# End Group
# Begin Group "ca2_devian Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ca2_devian\application.h
# End Source File
# Begin Source File

SOURCE=.\ca2_devian\ca2_devian.h
# End Source File
# End Group
# Begin Group "ca2api015_00045 Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ca2api015_00045\application.h
# End Source File
# Begin Source File

SOURCE=.\ca2api015_00045\ca2api015_00045.h
# End Source File
# Begin Source File

SOURCE=.\ca2api015_00045\dialog.h
# End Source File
# Begin Source File

SOURCE=.\ca2api015_00045\keyboard_layout.h
# End Source File
# Begin Source File

SOURCE=.\ca2api015_00045\message_box.h
# End Source File
# Begin Source File

SOURCE=.\ca2api015_00045\network_configuration.h
# End Source File
# Begin Source File

SOURCE=.\ca2api015_00045\Shell.h
# End Source File
# Begin Source File

SOURCE=.\ca2api015_00045\validate.h
# End Source File
# Begin Source File

SOURCE=.\ca2api015_00045\wait_message_dialog.h
# End Source File
# End Group
# Begin Group "ca2api014_00042 Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ca2api014_00042\application.h
# End Source File
# Begin Source File

SOURCE=.\ca2api014_00042\ca2api014_00042.h
# End Source File
# End Group
# Begin Group "ca2api013_00039 Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ca2api013_00039\application.h
# End Source File
# Begin Source File

SOURCE=.\ca2api013_00039\ca2api013_00039.h
# End Source File
# Begin Source File

SOURCE=.\ca2api013_00039\user.h
# End Source File
# End Group
# Begin Group "simpledb Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\simpledb\application.h
# End Source File
# Begin Source File

SOURCE=.\simpledb\db_long_set.h
# End Source File
# Begin Source File

SOURCE=.\simpledb\db_server.h
# End Source File
# Begin Source File

SOURCE=.\simpledb\db_set.h
# End Source File
# Begin Source File

SOURCE=.\simpledb\db_str_set.h
# End Source File
# Begin Source File

SOURCE=.\simpledb\db_stra_set.h
# End Source File
# Begin Source File

SOURCE=.\simpledb\DBFileSystemSize.h
# End Source File
# Begin Source File

SOURCE=.\simpledb\file_set.h
# End Source File
# Begin Source File

SOURCE=.\simpledb\im_post.h
# End Source File
# Begin Source File

SOURCE=.\simpledb\mysql_database.h
# End Source File
# Begin Source File

SOURCE=.\simpledb\mysql_result.h
# End Source File
# Begin Source File

SOURCE=.\simpledb\simpledb.h
# End Source File
# Begin Source File

SOURCE=.\simpledb\simpledb_base.h
# End Source File
# Begin Source File

SOURCE=.\simpledb\simpledb_set.h
# End Source File
# Begin Source File

SOURCE=.\simpledb\simpledb_table.h
# End Source File
# Begin Source File

SOURCE=.\simpledb\sqlite_base.h
# End Source File
# Begin Source File

SOURCE=.\simpledb\sqlite_set.h
# End Source File
# End Group
# Begin Group "database Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\database\database.h
# End Source File
# Begin Source File

SOURCE=.\database\database_01.h
# End Source File
# Begin Source File

SOURCE=.\database\database_application.h
# End Source File
# Begin Source File

SOURCE=.\database\database_base.h
# End Source File
# Begin Source File

SOURCE=.\database\database_change_event.h
# End Source File
# Begin Source File

SOURCE=.\database\database_client.h
# End Source File
# Begin Source File

SOURCE=.\database\database_definition.h
# End Source File
# Begin Source File

SOURCE=.\database\database_field_definition.h
# End Source File
# Begin Source File

SOURCE=.\database\database_id.h
# End Source File
# Begin Source File

SOURCE=.\database\database_key.h
# End Source File
# Begin Source File

SOURCE=.\database\database_selection.h
# End Source File
# Begin Source File

SOURCE=.\database\database_selection_item.h
# End Source File
# Begin Source File

SOURCE=.\database\database_server.h
# End Source File
# Begin Source File

SOURCE=.\database\database_set.h
# End Source File
# Begin Source File

SOURCE=.\database\database_stringhelper.h
# End Source File
# Begin Source File

SOURCE=.\database\database_update_hint.h
# End Source File
# Begin Source File

SOURCE=.\database\database_user_interaction.h
# End Source File
# End Group
# Begin Group "audio Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\audio\audio.h
# End Source File
# Begin Source File

SOURCE=.\audio\audio_global.h
# End Source File
# Begin Source File

SOURCE=.\audio\Command.h
# End Source File
# Begin Source File

SOURCE=.\audio\Resource.h
# End Source File
# Begin Source File

SOURCE=.\audio\WaveBuffer.h
# End Source File
# Begin Source File

SOURCE=.\audio\WaveCentral.h
# End Source File
# Begin Source File

SOURCE=.\audio\WaveCentralContainer.h
# End Source File
# Begin Source File

SOURCE=.\audio\WaveEffectCrescendo.h
# End Source File
# Begin Source File

SOURCE=.\audio\WaveEffectDevocalizer.h
# End Source File
# Begin Source File

SOURCE=.\audio\WaveFile.h
# End Source File
# Begin Source File

SOURCE=.\audio\WaveIn.h
# End Source File
# Begin Source File

SOURCE=.\audio\WaveInListener.h
# End Source File
# Begin Source File

SOURCE=.\audio\WaveInListenerSet.h
# End Source File
# Begin Source File

SOURCE=.\audio\WaveOut.h
# End Source File
# Begin Source File

SOURCE=.\audio\WavePlayer.h
# End Source File
# Begin Source File

SOURCE=.\audio\WavePlayerCommand.h
# End Source File
# Begin Source File

SOURCE=.\audio\WavePlayerInterface.h
# End Source File
# Begin Source File

SOURCE=.\audio\WavePreBuffer.h
# End Source File
# Begin Source File

SOURCE=.\audio\WaveRecorder.h
# End Source File
# Begin Source File

SOURCE=.\audio\WaveRecorderCommand.h
# End Source File
# Begin Source File

SOURCE=.\audio\WaveRecorderInterface.h
# End Source File
# End Group
# Begin Group "audio_decode Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\audio_decode\audio_decode.h
# End Source File
# Begin Source File

SOURCE=.\audio_decode\Decoder.h
# End Source File
# Begin Source File

SOURCE=.\audio_decode\DecoderPlugin.h
# End Source File
# Begin Source File

SOURCE=.\audio_decode\DecoderPluginSet.h
# End Source File
# Begin Source File

SOURCE=.\audio_decode\DecoderPluginSetEx1.h
# End Source File
# Begin Source File

SOURCE=.\audio_decode\Encoder.h
# End Source File
# Begin Source File

SOURCE=.\audio_decode\EncoderPlugin.h
# End Source File
# Begin Source File

SOURCE=.\audio_decode\EncoderPluginSet.h
# End Source File
# Begin Source File

SOURCE=.\audio_decode\EncoderPluginSetEx1.h
# End Source File
# Begin Source File

SOURCE=.\audio_decode\Resource.h
# End Source File
# End Group
# Begin Group "video Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\video\video.h
# End Source File
# Begin Source File

SOURCE=.\video\video_command.h
# End Source File
# Begin Source File

SOURCE=.\video\video_global.h
# End Source File
# Begin Source File

SOURCE=.\video\video_player.h
# End Source File
# Begin Source File

SOURCE=.\video\video_player_command.h
# End Source File
# End Group
# Begin Group "video_decode Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\video_decode\Decoder.h
# End Source File
# Begin Source File

SOURCE=.\video_decode\DecoderPlugin.h
# End Source File
# Begin Source File

SOURCE=.\video_decode\DecoderPluginSet.h
# End Source File
# Begin Source File

SOURCE=.\video_decode\DecoderPluginSetEx1.h
# End Source File
# Begin Source File

SOURCE=.\video_decode\video_decode.h
# End Source File
# End Group
# Begin Group "exception Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\exception\assert.h
# End Source File
# Begin Source File

SOURCE=.\exception\base_exception.h
# End Source File
# Begin Source File

SOURCE=.\exception\class.h
# End Source File
# Begin Source File

SOURCE=.\exception\debug.h
# End Source File
# Begin Source File

SOURCE=.\exception\debug_stream.h
# End Source File
# Begin Source File

SOURCE=.\exception\dump_context.h
# End Source File
# Begin Source File

SOURCE=.\exception\exception.h
# End Source File
# Begin Source File

SOURCE=.\exception\exception2.h
# End Source File
# Begin Source File

SOURCE=.\exception\exception_0.h
# End Source File
# Begin Source File

SOURCE=.\exception\exception_trap.h
# End Source File
# Begin Source File

SOURCE=.\exception\interface_only.h
# End Source File
# Begin Source File

SOURCE=.\exception\invalid_argument.h
# End Source File
# Begin Source File

SOURCE=.\exception\memory.h
# End Source File
# Begin Source File

SOURCE=.\exception\memory_state.h
# End Source File
# Begin Source File

SOURCE=.\exception\misc.h
# End Source File
# Begin Source File

SOURCE=.\exception\not_implemented.h
# End Source File
# Begin Source File

SOURCE=.\exception\not_supported.h
# End Source File
# Begin Source File

SOURCE=.\exception\resource.h
# End Source File
# Begin Source File

SOURCE=.\exception\se_exception.h
# End Source File
# Begin Source File

SOURCE=.\exception\se_translator.h
# End Source File
# Begin Source File

SOURCE=.\exception\simple.h
# End Source File
# Begin Source File

SOURCE=.\exception\SymEngine.h
# End Source File
# Begin Source File

SOURCE=.\exception\unhandled_report.h
# End Source File
# Begin Source File

SOURCE=.\exception\user.h
# End Source File
# Begin Source File

SOURCE=.\exception\VMSException.h
# End Source File
# End Group
# Begin Group "id3lib Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\id3lib\acconfig.h
# End Source File
# Begin Source File

SOURCE=.\id3lib\config.h
# End Source File
# Begin Source File

SOURCE=.\id3lib\field.h
# End Source File
# Begin Source File

SOURCE=.\id3lib\field_def.h
# End Source File
# Begin Source File

SOURCE=.\id3lib\field_impl.h
# End Source File
# Begin Source File

SOURCE=.\id3lib\flags.h
# End Source File
# Begin Source File

SOURCE=.\id3lib\frame_def.h
# End Source File
# Begin Source File

SOURCE=.\id3lib\frame_impl.h
# End Source File
# Begin Source File

SOURCE=.\id3lib\globals.h
# End Source File
# Begin Source File

SOURCE=.\id3lib\header.h
# End Source File
# Begin Source File

SOURCE=.\id3lib\header_frame.h
# End Source File
# Begin Source File

SOURCE=.\id3lib\header_tag.h
# End Source File
# Begin Source File

SOURCE=.\id3lib\helpers.h
# End Source File
# Begin Source File

SOURCE=.\id3lib\id3.h
# End Source File
# Begin Source File

SOURCE=.\id3lib\id3lib_frame.h
# End Source File
# Begin Source File

SOURCE=.\id3lib\id3lib_streams.h
# End Source File
# Begin Source File

SOURCE=.\id3lib\id3lib_strings.h
# End Source File
# Begin Source File

SOURCE=.\id3lib\io_decorators.h
# End Source File
# Begin Source File

SOURCE=.\id3lib\io_helpers.h
# End Source File
# Begin Source File

SOURCE=.\id3lib\io_strings.h
# End Source File
# Begin Source File

SOURCE=.\id3lib\mp3_header.h
# End Source File
# Begin Source File

SOURCE=.\id3lib\reader.h
# End Source File
# Begin Source File

SOURCE=.\id3lib\readers.h
# End Source File
# Begin Source File

SOURCE=.\id3lib\sized_types.h
# End Source File
# Begin Source File

SOURCE=.\id3lib\spec.h
# End Source File
# Begin Source File

SOURCE=.\id3lib\tag.h
# End Source File
# Begin Source File

SOURCE=.\id3lib\tag_impl.h
# End Source File
# Begin Source File

SOURCE=.\id3lib\utils.h
# End Source File
# Begin Source File

SOURCE=.\id3lib\writer.h
# End Source File
# Begin Source File

SOURCE=.\id3lib\writers.h
# End Source File
# End Group
# Begin Group "upnp Header"

# PROP Default_Filter ""
# End Group
# Begin Group "visual Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\visual\Api.h
# End Source File
# Begin Source File

SOURCE=.\visual\application.h
# End Source File
# Begin Source File

SOURCE=.\visual\buffered_graphics.h
# End Source File
# Begin Source File

SOURCE=.\visual\Clip.h
# End Source File
# Begin Source File

SOURCE=.\visual\Dib.h
# End Source File
# Begin Source File

SOURCE=.\visual\dib_pal.h
# End Source File
# Begin Source File

SOURCE=.\visual\font_central.h
# End Source File
# Begin Source File

SOURCE=.\visual\FreeImageFileProc.h
# End Source File
# Begin Source File

SOURCE=.\visual\Glyph.h
# End Source File
# Begin Source File

SOURCE=.\visual\glyph_set.h
# End Source File
# Begin Source File

SOURCE=.\visual\graphics_extension.h
# End Source File
# Begin Source File

SOURCE=.\visual\Icon.h
# End Source File
# Begin Source File

SOURCE=.\visual\image_list.h
# End Source File
# Begin Source File

SOURCE=.\visual\Imaging.h
# End Source File
# Begin Source File

SOURCE=.\visual\rgb_quad_array.h
# End Source File
# Begin Source File

SOURCE=.\visual\Visual.h
# End Source File
# Begin Source File

SOURCE=.\visual\visual_0.h
# End Source File
# Begin Source File

SOURCE=.\visual\visual_application.h
# End Source File
# Begin Source File

SOURCE=.\visual\visual_cursor.h
# End Source File
# Begin Source File

SOURCE=.\visual\visual_dib.h
# End Source File
# Begin Source File

SOURCE=.\visual\visual_font.h
# End Source File
# Begin Source File

SOURCE=.\visual\visual_visual.h
# End Source File
# Begin Source File

SOURCE=.\visual\water_routine.h
# End Source File
# End Group
# Begin Group "xml Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\xml\attr.h
# End Source File
# Begin Source File

SOURCE=.\xml\base_array.h
# End Source File
# Begin Source File

SOURCE=.\xml\disp_option.h
# End Source File
# Begin Source File

SOURCE=.\xml\document.h
# End Source File
# Begin Source File

SOURCE=.\xml\entity.h
# End Source File
# Begin Source File

SOURCE=.\xml\enum.h
# End Source File
# Begin Source File

SOURCE=.\xml\exportable.h
# End Source File
# Begin Source File

SOURCE=.\xml\importable.h
# End Source File
# Begin Source File

SOURCE=.\xml\input_tree.h
# End Source File
# Begin Source File

SOURCE=.\xml\node.h
# End Source File
# Begin Source File

SOURCE=.\xml\output_tree.h
# End Source File
# Begin Source File

SOURCE=.\xml\parse_info.h
# End Source File
# Begin Source File

SOURCE=.\xml\property_exchange.h
# End Source File
# Begin Source File

SOURCE=.\xml\tree_base.h
# End Source File
# Begin Source File

SOURCE=.\xml\tree_schema.h
# End Source File
# Begin Source File

SOURCE=.\xml\var_exchange.h
# End Source File
# Begin Source File

SOURCE=.\xml\xml.h
# End Source File
# Begin Source File

SOURCE=.\xml\XMLite.h
# End Source File
# End Group
# Begin Group "imedia Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\imedia\imedia.h
# End Source File
# Begin Source File

SOURCE=.\imedia\Position.h
# End Source File
# Begin Source File

SOURCE=.\imedia\position_array.h
# End Source File
# Begin Source File

SOURCE=.\imedia\Time.h
# End Source File
# Begin Source File

SOURCE=.\imedia\time_array.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ca2.h
# End Source File
# Begin Source File

SOURCE=.\ca2_res.h
# End Source File
# Begin Source File

SOURCE=.\cafxres.h
# End Source File
# Begin Source File

SOURCE=.\cawinres.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\this_version_info.h
# End Source File
# Begin Source File

SOURCE=.\winres.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
