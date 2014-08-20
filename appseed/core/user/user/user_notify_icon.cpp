#include "framework.h"


namespace user
{

   notify_icon::notify_icon(sp(::axis::application) papp) :
      element(papp)
   {
#ifdef WINDOWSEX
      m_nid.cbSize = sizeof(m_nid);
#endif
      m_bCreated = false;

   }

   notify_icon::~notify_icon()
   {
      Destroy();
   }

   void notify_icon::install_message_handling(::message::dispatch * pinterface)
   {
      IGUI_WIN_MSG_LINK(MessageNotifyIcon, pinterface, this, &notify_icon::_001OnNotifyIconMessage);
   }

   bool notify_icon::create(UINT uiId, notify_icon_listener * plistener, sp(::visual::icon) hicon)
   {

      if(m_bCreated)
         return false;

      string strNotifyIcon;

      strNotifyIcon.Format("user::notify_icon - %d", uiId);

      if(!create_message_queue(strNotifyIcon))
         return false;

      m_uiId                     = uiId;
#ifdef WINDOWSEX
      m_nid.hWnd                 = get_safe_handle();
      m_nid.uID                  = uiId;
      m_nid.hIcon                = (HICON)hicon->get_os_data();
      m_nid.uFlags               = NIF_ICON | NIF_MESSAGE;
      m_nid.uCallbackMessage     = MessageNotifyIcon;
#else
      throw todo(get_app());
#endif
      m_plistener                = plistener;

#ifdef WINDOWSEX
      if(!Shell_NotifyIcon(NIM_ADD, &m_nid))
      {
         DestroyWindow();
         return false;
      }
#else
      throw todo(get_app());
#endif

      m_bCreated = true;

      return true;

   }

   bool notify_icon::ModifyIcon(sp(::visual::icon) hicon)
   {

      if(!m_bCreated)
         return false;

#ifdef WINDOWSEX
      m_nid.hIcon       = (HICON) hicon->get_os_data();
      m_nid.uFlags      = NIF_ICON;


      if(!Shell_NotifyIcon(NIM_MODIFY, &m_nid))
      {
         return false;
      }

#else
      throw todo(get_app());
#endif

      return true;

   }


   bool notify_icon::Destroy()
   {

      if(!m_bCreated)
         return false;

#ifdef WINDOWSEX
      m_nid.uFlags = 0;

      if(!Shell_NotifyIcon(NIM_DELETE, &m_nid))
      {
         return false;
      }
#else
      throw todo(get_app());
#endif

      m_bCreated = false;

      DestroyWindow();

      return true;

   }

   void notify_icon::_001OnNotifyIconMessage(signal_details * pobj)
   {

      SCAST_PTR(::message::base, pbase, pobj);

      m_plistener->OnNotifyIconMessage(m_uiId, (UINT) pbase->m_lparam);

   }


} // namespace user

