#pragma once


#include "ca/visual/visual.h"


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


#include "user_document_interface.h"
#include "user_document.h"



#include "user_view.h"
#include "user_control.h"

#include "user_place_holder.h"
#include "user_place_holder_container.h"



/////////////////////////////////////////////////////////////////////////////
// frame_window - base class for SDI and other frame windows

// Frame ::ca::window styles
#define FWS_ADDTOTITLE  0x00008000L // modify title based on content
#define FWS_PREFIXTITLE 0x00004000L // show document name before cast name
#define FWS_SNAPTOBARS  0x00002000L // snap size to size of contained bars

struct CPrintPreviewState;  // forward reference (see afxext.h)
namespace userbase
{
   class control_bar;          // forward reference (see afxext.h)
}
class CReBar;               // forward reference (see afxext.h)
class simple_frame_window;
class CDockBar;             // forward reference (see afxpriv.h)
class mini_dock_frame_window;    // forward reference (see afxpriv.h)
class CDockState;           // forward reference (see afxpriv.h)


#include "user_frame_window_interface.h"
#include "user_frame_window.h"



/*


/////////////////////////////////////////////////////////////////////////////
// CMiniFrameWnd

// MiniFrame ::ca::window styles
#define MFS_SYNCACTIVE      0x00000100L // syncronize activation w/ parent
#define MFS_4THICKFRAME     0x00000200L // thick frame all around (no tiles)
#define MFS_THICKFRAME      0x00000400L // use instead of WS_THICKFRAME
#define MFS_MOVEFRAME       0x00000800L // no sizing, just moving
#define MFS_BLOCKSYSMENU    0x00001000L // block hit testing on system menu

#pragma warning( disable: 4263 )
#pragma warning( disable: 4264 )
class CLASS_DECL_ca CMiniFrameWnd : public frame_window
{
public:


   CMiniFrameWnd();
   ~CMiniFrameWnd();


   virtual bool create(const char * lpClassName, const char * lpWindowName,
      uint32_t dwStyle, const RECT& rect,
      virtual_user_interface* pParentWnd = NULL, UINT nID = 0);
   virtual bool CreateEx(uint32_t dwExStyle, const char * lpClassName, const char * lpWindowName,
      uint32_t dwStyle, const RECT& rect,
      virtual_user_interface* pParentWnd = NULL, UINT nID = 0);


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
   virtual bool pre_create_window(CREATESTRUCT& cs);

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




namespace user
{


   class CLASS_DECL_ca message
   {
   public:
      ::user::interaction *  m_pguie;
      UINT              m_uiMessage;
      WPARAM            m_wparam;
      LPARAM            m_lparam;
      LRESULT send();
      static UINT ThreadProcSendMessage(LPVOID lp);
      static void post(::user::interaction * puie, UINT uiMessage, WPARAM wparam, LPARAM lparam, ::ca::e_thread_priority epriority = ::ca::thread_priority_normal);
   };


   CLASS_DECL_ca ::user::interaction * get_parent_owner(::user::interaction * pui);
   CLASS_DECL_ca bool is_descendant(::user::interaction * puiParent, ::user::interaction * puiChild);


} // namespace user


#include "user_window_util.h"


#include "user_wait_message_dialog.h"
#include "user_message_box.h"
#include "user_network_configuration.h"
#include "user_shell.h"
#include "user_keyboard_layout.h"
#include "user_keyboard.h"
#include "user_keyboard_layout_cfg.h"


#include "user_document_template_interface.h"
#include "user_document_template.h"
#include "user_single_document_template.h"
#include "user_multiple_document_template.h"


#include "user_document_manager.h"


#include "user_data_exchange.h"
#include "user_form.h"
#include "user_form_callback.h"


#include "user_view_container.h"
#include "user_view_creator.h"

#include "user_job.h"


#include "user_user.h"



