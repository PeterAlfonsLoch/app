#include "framework.h"

#if defined(LINUX)
// Ubuntu apt-get install libx11-dev
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#endif

#undef new

struct myfx_CTLCOLOR
{
   ::oswindow oswindow;
   HDC hDC;
   UINT nCtlType;
};


namespace message
{


   void create::set(sp(::user::interaction) pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult)
   {
      base::set(pwnd,uiMessage,wparam,lparam,lresult);
      m_lpcreatestruct = reinterpret_cast<::user::create_struct *>(lparam);
   }

   void create::set_lresult(LRESULT lresult)
   {
      base::set_lresult(lresult);
      if(get_lresult() == -1)
         m_bRet = true;
      else
         m_bRet = false;
   }

   void create::failed(const char * lpcszErrorMessage)
   {
      error(lpcszErrorMessage);
   }

   void create::error(const char * lpcszErrorMessage)
   {
      set_lresult(-1);
      TRACE0(lpcszErrorMessage);
      System.log().print(lpcszErrorMessage);
   }

   void timer::set(sp(::user::interaction) pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult)
   {
      base::set(pwnd,uiMessage,wparam,lparam,lresult);
      m_nIDEvent = static_cast<UINT>(wparam);
   }

   activate::activate(sp(::base::application) papp):
      element(papp),
      message::base(papp)
   {
      }

   void activate::set(sp(::user::interaction) pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult)
   {
      base::set(pwnd,uiMessage,wparam,lparam,lresult);
      m_nState = (UINT)(LOWORD(wparam));
      m_pWndOther = System.window_from_os_data((void *)lparam);
      m_bMinimized = HIWORD(wparam) != FALSE;
   }



   erase_bkgnd::erase_bkgnd(sp(::base::application) papp):
      element(papp),
      message::base(papp)
   {
      }

   void erase_bkgnd::set_result(bool bResult)
   {
      set_lresult(bResult);
   }

   key::key(sp(::base::application) papp):
      element(papp),
      message::base(papp)
   {
      }

   void key::set(sp(::user::interaction) pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult)
   {

      base::set(pwnd,uiMessage,wparam,lparam,lresult);

      m_nChar = static_cast<UINT>(wparam);

      m_nRepCnt = LOWORD(lparam);

      m_nFlags = HIWORD(lparam);



   }

   nc_activate::nc_activate(sp(::base::application) papp):
      element(papp),
      message::base(papp)
   {
      }

   void nc_activate::set(sp(::user::interaction) pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult)
   {
      base::set(pwnd,uiMessage,wparam,lparam,lresult);
      m_bActive = wparam != FALSE;
   }

   void size::set(sp(::user::interaction) pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult)
   {
      base::set(pwnd,uiMessage,wparam,lparam,lresult);
      m_nType     = static_cast < UINT > (wparam);
      m_size      = ::size(LOWORD(lparam),HIWORD(lparam));
   }

   mouse::mouse(sp(::base::application) papp):
      element(papp),
      base(papp),
      m_ecursor(::visual::cursor_unmodified)
   {
   }

   mouse::~mouse()
   {

      try
      {

         if(m_ecursor != ::visual::cursor_unmodified && m_pbaseapp != NULL && m_pbaseapp->m_pbasesession != NULL)
         {

            session().set_cursor(m_ecursor);

         }

      }
      catch(...)
      {
      }
   }

   void mouse::set(sp(::user::interaction) pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult)
   {
      base::set(pwnd,uiMessage,wparam,lparam,lresult);
      m_nFlags    = wparam;
      m_pt        = point(lparam);
#ifdef LINUX
      m_bTranslated = true;  // in root coordinates
#elif defined(WINDOWS)
      m_bTranslated = false; // not in root coordinates
#else
      m_bTranslated = false; // not in root coordinates
#endif
   }

   void mouse_wheel::set(sp(::user::interaction) pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult)
   {
      base::set(pwnd,uiMessage,wparam,lparam,lresult);
      m_nFlags    = wparam;
      m_pt        = point(lparam);
      m_bTranslated = true;
   }

   sp(::user::interaction) mouse_activate::GetDesktopWindow()
   {
      throw not_implemented(get_app());
      //      return interaction_impl::from_handle_dup(reinterpret_cast<oswindow>(m_wparam));
      return NULL;
   }

   UINT mouse_activate::GetHitTest()
   {
      return LOWORD(m_lparam);
   }

   UINT mouse_activate::get_message()
   {
      return HIWORD(m_lparam);
   }

   ::window_sp context_menu::GetWindow()
   {
      throw not_implemented(get_app());
      return NULL;
      //            return interaction_impl::from_handle_dup(reinterpret_cast<oswindow>(m_wparam));
   }

   point context_menu::GetPoint()
   {
      return point(m_lparam);
   }


   void scroll::set(sp(::user::interaction) pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult)
   {
      base::set(pwnd,uiMessage,wparam,lparam,lresult);
      m_nSBCode = (int16_t)LOWORD(wparam);
      m_nPos = (int16_t)HIWORD(wparam);
      m_pScrollBar = (sp(::user::interaction)) lparam;
   }

   void show_window::set(sp(::user::interaction) pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult)
   {
      base::set(pwnd,uiMessage,wparam,lparam,lresult);
      m_bShow = wparam != FALSE;
      m_nStatus = static_cast<UINT>(lparam);
   }

   void set_focus::set(sp(::user::interaction) pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult)
   {
      base::set(pwnd,uiMessage,wparam,lparam,lresult);
      //m_pwnd = System.window_from_os_data(reinterpret_cast<oswindow>(wparam));
      m_pwnd = NULL;
   }

   void window_pos::set(sp(::user::interaction) pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult)
   {
      base::set(pwnd,uiMessage,wparam,lparam,lresult);
      m_pwindowpos = reinterpret_cast<WINDOWPOS*>(lparam);
   }

   void nc_calc_size::set(sp(::user::interaction) pwnd,UINT uiMessage,WPARAM wparam,LPARAM lparam,LRESULT & lresult)
   {
      base::set(pwnd,uiMessage,wparam,lparam,lresult);
      m_pparams = reinterpret_cast<NCCALCSIZE_PARAMS*>(lparam);
   }

   bool nc_calc_size::GetCalcValidRects()
   {
      return m_wparam != FALSE;
   }


   bool enable::get_enable()
   {
      return m_wparam != 0;
   }





   UINT mouse_wheel::GetFlags()
   {
      return LOWORD(m_wparam);
   }

   int16_t mouse_wheel::GetDelta()
   {
      return (int16_t)HIWORD(m_wparam);
   }

   point mouse_wheel::GetPoint()
   {
      return point(GET_X_LPARAM(m_lparam),GET_Y_LPARAM(m_lparam));
   }

   UINT command::GetNotifyCode()
   {
      return HIWORD(m_wparam);
   }

   UINT command::GetId()
   {
      return LOWORD(m_wparam);
   }

#ifdef WINDOWS

   oswindow command::get_oswindow()
   {
      return (oswindow)m_lparam.m_lparam;
   }

#endif

#ifdef WINDOWSEX

   LPNMHDR notify::get_lpnmhdr()
   {
      return (LPNMHDR)m_lparam.m_lparam;
   }

   int32_t notify::get_ctrl_id()
   {
      return (int32_t)m_wparam;
   }

#endif




} // namespace message







