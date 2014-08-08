#pragma once


#include "core/graphics/visual/visual.h"



namespace html
{


   class data;


} // namespace html


namespace user
{

   enum e_mouse
   {

      mouse_left_button,
      mouse_right_button,
      mouse_middle_button

   };


} // namespace user


enum e_position
{
   position_none           = 0,
   position_top            = 1,
   position_left           = 2,
   position_top_left       = 3,
   position_right          = 4,
   position_top_right      = 5,
   position_hcenter        = 6,
   position_top_center     = 7,
   position_bottom         = 8,
   position_vcenter        = 9,
   position_bottom_left    = 10,
   position_left_center    = 11,
   position_bottom_right   = 12,
   position_right_center   = 13,
   position_bottom_center  = 14,
   position_center         = 15,
};


namespace user
{
   enum e_line_hit
   {
      line_hit_none,
      line_hit_normal,
      line_hit_link,
   };
}




#include "user_front_end_schema.h"
#include "user_front_end.h"


#include "user_list_header.h"


#include "user_combo_box.h"
#include "user_combo_list.h"


#include "user_button.h"
#include "user_check_box.h"


//#include "user_document_interface.h"
//#include "user_document.h"



#include "user_list.h"
#include "user_list_cache_interface.h"
#include "user_list_cache.h"
#include "user_list_data.h"
#include "user_simple_list_data.h"

#include "user_tree_data.h"

#include "user_tree.h"

#include "user_form.h"
#include "user_form_list.h"
#include "user_form_callback.h"


//#include "user_place_holder.h"
//#include "user_place_holder_container.h"


#include "user_tab_callback.h"
#include "user_tab.h"




struct CPrintPreviewState;  // forward reference (see afxext.h)
namespace user
{
   class control_bar;          // forward reference (see afxext.h)
}
class CReBar;               // forward reference (see afxext.h)
class simple_frame_window;
class CDockBar;             // forward reference (see afxpriv.h)
class mini_dock_frame_window;    // forward reference (see afxpriv.h)
class CDockState;           // forward reference (see afxpriv.h)


#include "core/user/uinteraction/uinteraction.h"



/*


/////////////////////////////////////////////////////////////////////////////
// CMiniFrameWnd

// MiniFrame window styles
#define MFS_SYNCACTIVE      0x00000100L // syncronize activation w/ parent
#define MFS_4THICKFRAME     0x00000200L // thick frame all around (no tiles)
#define MFS_THICKFRAME      0x00000400L // use instead of WS_THICKFRAME
#define MFS_MOVEFRAME       0x00000800L // no sizing, just moving
#define MFS_BLOCKSYSMENU    0x00001000L // block hit testing on system menu

#pragma warning( disable: 4263 )
#pragma warning( disable: 4264 )
class CLASS_DECL_CORE CMiniFrameWnd : public frame_window
{
public:


   CMiniFrameWnd();
   ~CMiniFrameWnd();


   virtual bool create(const char * lpClassName, const char * lpWindowName,
      uint32_t dwStyle, const RECT& rect,
      ::user::interaction_child* pParentWnd = NULL, UINT nID = 0);
   virtual bool create_window_ex(uint32_t dwExStyle, const char * lpClassName, const char * lpWindowName,
      uint32_t dwStyle, const RECT& rect,
      ::user::interaction_child* pParentWnd = NULL, UINT nID = 0);


   bool OnNcActivate(bool bActive);
   LRESULT OnNcHitTest(point point);
   void OnSysCommand(UINT nID, LPARAM lParam);
   void OnGetMinMaxInfo(MINMAXINFO* pMMI);
   LRESULT OnFloatStatus(WPARAM wParam, LPARAM lParam);
   LRESULT OnQueryCenterWnd(WPARAM wParam, LPARAM lParam);
   bool OnNcCreate(LPCREATESTRUCT lpcs);

public:
   static void CalcBorders(LPRECT lpClientRect, uint32_t dwStyle = 0, uint32_t dwExStyle = 0);

protected:
   virtual bool pre_create_window(::user::create_struct& cs);

protected:
   bool m_bSysTracking;
   bool m_bInSys;
   bool m_bActive;
   string m_strCaption;
};
#pragma warning( default: 4263 )
#pragma warning( default: 4264 )


typedef uint32_t DROPEFFECT;
class COleDataObject;   // forward reference (see afxole.h)

*/






#include "user_network_configuration.h"
#include "user_shell.h"
#include "user_keyboard_layout_cfg.h"


//#include "user_document_template_interface.h"
//#include "user_document_template.h"
#include "user_single_document_template.h"
#include "user_multiple_document_template.h"


#include "user_document_manager.h"


#include "user_data_exchange.h"


//#include "user_view_container.h"
//#include "user_view_creator.h"

//#include "user_job.h"


#include "core/user/menu/user_menu_central.h"


#include "user_xfplayer_view_line.h"
#include "user_xfplayer_view_lines.h"

#include "user_tool_tip_tool.h"
#include "user_tool_tip_window.h"











struct __SIZEPARENTPARAMS;


namespace user
{


   class user;


} // namespace user



#include "user_button.h"
#include "user_meta_button.h"
#include "user_bitmap_button.h"
#include "user_combo_box.h"
#include "user_combo_list.h"
#include "user_static_control.h"

#include "user_button_control.h"

//#include "user_mdi_frame_window.h"
//#include "user_mdi_child_window.h"


#include "user_tool_cmd_ui.h"


#include "user_toolbar_control.h"

//#include "user_control_bar.h"
#include "user_toolbar.h"
#include "user_statusbar.h"

//#include "user_view.h"
//#include "user_document.h"
//#include "user_document_template.h"

#include "user_split_bar.h"
#include "user_split_layout.h"

#include "user_form_list.h"
#include "user_split_bar.h"
#include "user_split_window.h"
#include "user_split_view.h"


#include "user_edit_plain_text_view.h"


#include "user_form.h"
#include "user_tab_view.h"

#include "user_tab_view_update_hint.h"

#include "user_document_manager.h"


#include "user_notification_area.h"
#include "user_notify_icon.h"
#include "user_notify_icon_listener.h"

#include "user_single_document_template.h"
#include "user_multiple_document_template.h"

#include "core/user/menu/user_menu_button.h"
#include "core/user/menu/user_menu_item.h"
#include "core/user/menu/user_menu.h"
#include "core/user/menu/user_menu_list_window.h"
#include "core/user/menu/user_menu_list_view.h"

#include "user_step_slider.h"
#include "user_elastic_slider.h"


// user simple
#include "core/user/simple/simple.h"


// user after simple
#include "user_main_frame.h"

#include "user_image_manager.h"

#include "user_core.h"







