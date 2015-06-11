#include "framework.h"
#include "user/user.h"


#include "core/user/simple/simple.h"
#include "core/user/userex/userex.h"

#include "core/user/menu/menu.h"



#include "core/filesystem/filemanager/filemanager.h"
#include <math.h>
#ifdef WINDOWS
#include <dde.h>
#include <winspool.h>
#include <Shellapi.h>
#include <CommonControls.h>
#endif


// O volume na unidade Z ‚ eco
// O N£mero de S‚rie do Volume ‚ 4A91-94E4
//
// Pasta de Z:\nordroid\app\appseed\core\user
//
//2014-12-24  20:51                 0 _user.cpp"
//               1 arquivo(s)              0 bytes
//
// Pasta de Z:\nordroid\app\appseed\core\user\menu

#include "menu/user_menu.cpp"
#include "menu/user_menu_button.cpp"
#include "menu/user_menu_central.cpp"
#include "menu/user_menu_item.cpp"
#include "menu/user_menu_list_window.cpp"
 //              5 arquivo(s)         44.883 bytes

 //Pasta de Z:\nordroid\app\appseed\core\user\simple

#include "simple/simple_child_frame.cpp"
#include "simple/simple_form_list_view.cpp"
#include "simple/simple_frame_window.cpp"
#include "simple/simple_list_ctrl.cpp"
#include "simple/simple_list_header_ctrl.cpp"
#include "simple/simple_list_view.cpp"
#include "simple/simple_main_frame.cpp"
#include "simple/simple_menu_bar.cpp"
#include "simple/simple_printer_list_view.cpp"
#include "simple/simple_static.cpp"
#include "simple/simple_status_bar.cpp"
#include "simple/simple_tab_ctrl.cpp"
#include "simple/simple_tab_view.cpp"
#include "simple/simple_toolbar.cpp"
#include "simple/simple_tree_view.cpp"
#include "simple/simple_form_view.cpp"
 //             15 arquivo(s)        148.378 bytes

 //Pasta de Z:\nordroid\app\appseed\core\user\user

#include "user/user.cpp"
#include "user/user_button.cpp"
#include "user/user_check_box.cpp"
#include "user/user_combo_box.cpp"
#include "user/user_combo_list.cpp"
#include "user/user_control_property.cpp"
//#include "user/user_core.cpp"
#include "user/user_data_exchange.cpp"
#include "user/user_document_manager.cpp"
#include "user/user_edit_plain_text_view.cpp"
#include "user/user_elastic_slider.cpp"
//#include "user/user_form.cpp"
//#include "user/user_form_callback.cpp"
#include "user/user_form.cpp"
#include "user/user_form_view.cpp"
#include "user/user_form_mesh.cpp"
#include "user/user_form_list.cpp"
#include "user/user_form_list_view.cpp"
#include "user/user_front_end.cpp"
#include "user/user_front_end_schema.cpp"
#include "user/user_image_manager.cpp"
#include "user/user_keyboard_layout_cfg.cpp"
#include "user/user_mesh.cpp"
#include "user/user_list.cpp"
#include "user/user_list_view.cpp"
#include "user/user_list_cache.cpp"
#include "user/user_mesh_cache.cpp"
#include "user/user_mesh_cache_interface.cpp"
#include "simple/simple_mesh_data.cpp"
#include "simple/simple_list_data.cpp"
#include "user/user_list_data.cpp"
#include "user/user_mesh_data.cpp"
#include "user/user_list_header.cpp"
#include "user/user_menu_list_view.cpp"
#include "user/user_meta_button.cpp"
#include "user/user_meta_control_box.cpp"
#include "user/user_multiple_document_template.cpp"
#include "user/user_network_configuration.cpp"
#include "user/user_notification_area.cpp"
#include "user/user_notify_icon.cpp"
#include "user/user_notify_icon_listener.cpp"
#include "user/user_orto_button.cpp"
#include "user/user_shell.cpp"
#include "user/user_single_document_template.cpp"
#include "user/user_slider.cpp"
#include "user/user_split_bar.cpp"
#include "user/user_split_layout.cpp"
#include "user/user_split_view.cpp"
#include "user/user_split_window.cpp"
#include "user/user_static_control.cpp"
#include "user/user_statusbar.cpp"
#include "user/user_step_slider.cpp"
#include "user/user_tab.cpp"
#include "user/user_tab_callback.cpp"
#include "user/user_tab_view.cpp"
#include "user/user_tab_view_update_hint.cpp"
#include "user/user_toolbar.cpp"
#include "user/user_toolbar_ctrl.cpp"
#include "user/user_tool_cmd_ui.cpp"
#include "user/user_tool_tip_tool.cpp"
#include "user/user_tool_tip_window.cpp"
#include "user/user_tree.cpp"
#include "user/user_tree_data.cpp"
#include "user/user_tree_window.cpp"
#include "user/user_xfplayer_view_line.cpp"
#include "user/user_xfplayer_view_lines.cpp"
#include "user/user_xfplayer_view_line_selection.cpp"
 //             58 arquivo(s)        808.857 bytes

 //Pasta de Z:\nordroid\app\appseed\core\user\userex

#include "userex/userex_dialog.cpp"
#include "userex/userex_form_child_frame.cpp"
//#include "userex/userex_form_document.cpp"
#include "userex/userex_form_frame.cpp"
#include "userex/userex_form_update_hint.cpp"
#include "userex/userex_form_view.cpp"
#include "userex/userex_keyboard_layout.cpp"
#include "userex/userex_menu_document.cpp"
#include "userex/userex_menu_frame.cpp"
#include "userex/userex_menu_view.cpp"
#include "userex/userex_message_box.cpp"
#include "userex/userex_mini_dock_frame_window.cpp"
#include "userex/userex_pane_split_view.cpp"
#include "userex/userex_pane_tab_view.cpp"
#include "userex/userex_pane_view.cpp"
#include "userex/userex_property_page.cpp"
#include "userex/userex_property_sheet.cpp"
#include "userex/userex_split_view.cpp"
#include "userex/userex_userex.cpp"
#include "userex/userex_wait_message_dialog.cpp"
 //             20 arquivo(s)         52.000 bytes

 //Pasta de Z:\nordroid\app\appseed\core\user\wndfrm

#include "wndfrm/wndfrm_interaction.cpp"
#include "wndfrm/wndfrm_wndfrm.cpp"
 //              2 arquivo(s)          3.486 bytes

 //Pasta de Z:\nordroid\app\appseed\core\user\wndfrm\frame

#include "wndfrm/frame/aaa_want_to_remove_wndfrm_frame_up_down_target.cpp"
#include "wndfrm/frame/aaa_want_to_remove_wndfrm_frame_work_set_down_up_interface.cpp"
#include "wndfrm/frame/wndfrm_frame_appearance.cpp"
#include "wndfrm/frame/wndfrm_frame_constants.cpp"
#include "wndfrm/frame/wndfrm_frame_control_box.cpp"
#include "wndfrm/frame/wndfrm_frame_control_box_button.cpp"
#include "wndfrm/frame/wndfrm_frame_dock_manager.cpp"
#include "wndfrm/frame/wndfrm_frame_frame.cpp"
#include "wndfrm/frame/wndfrm_frame_move_manager.cpp"
#include "wndfrm/frame/wndfrm_frame_size_manager.cpp"
#include "wndfrm/frame/wndfrm_frame_sys_menu_manager.cpp"
#include "wndfrm/frame/wndfrm_frame_work_set.cpp"
#include "wndfrm/frame/wndfrm_frame_work_set_client_interface.cpp"
#include "wndfrm/frame/wndfrm_frame_work_set_listener.cpp"
#include "wndfrm/frame/wndfrm_frame_work_set_listener_array.cpp"
     //         15 arquivo(s)        198.852 bytes

     //Total de Arquivos na Lista:
     //        116 arquivo(s)      1.256.456 bytes
     //          0 pasta(s)   65.377.120.256 bytes dispon¡veis


#include "app/appseed/core/net/usernet/usernet_network_configuration.cpp"



#include "user/user_margin.cpp"