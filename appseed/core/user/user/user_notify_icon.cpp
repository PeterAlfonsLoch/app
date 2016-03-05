//#include "framework.h"


static ::user::notify_icon * g_pnotifyiconLast = NULL;
#ifdef LINUX
#include <dlfcn.h>
BEGIN_EXTERN_C
typedef void * BASECORE_APP_INDICATOR_NEW(const char *, const char *, const char *, i_close_quit *);
typedef void BASECORE_APP_INDICATOR_TERM(void *);
END_EXTERN_C
extern void * g_pbasecore;
#endif

namespace user
{

   notify_icon::notify_icon(::aura::application * papp) :
      object(papp)
   {

      g_pnotifyiconLast = this;

#ifdef WINDOWSEX

      m_nid.cbSize = sizeof(m_nid);

#elif defined(LINUX)

      m_pindicator = NULL;

#endif

      m_bCreated = false;

   }


   notify_icon::~notify_icon()
   {

      Destroy();

      if(g_pnotifyiconLast== this)
      {

         g_pnotifyiconLast = NULL;

      }

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
      m_nid.hIcon                = *hicon;
      m_nid.uFlags               = NIF_ICON | NIF_MESSAGE;
      m_nid.uCallbackMessage     = MessageNotifyIcon;
#elif defined(LINUX)
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
#elif defined(LINUX)
{
         BASECORE_APP_INDICATOR_NEW* f = (BASECORE_APP_INDICATOR_NEW *) dlsym(g_pbasecore, "basecore_app_indicator_new");

         string strFolder("/ca2/");
         string str = hicon->m_strAppTrayIcon;
         str.replace("-", "_");
         str.replace("/", "_");
         str.replace("\\", "_");
         if(::str::begins_eat_ci(str, "app_veriwell_"))
         {
            strFolder+="app-veriwell";
         }
         else if(::str::begins_eat_ci(str, "app_core_"))
         {
            strFolder+="app-core";
         }
         else
         {
            strFolder+="app";
         }

         strFolder+= "/appmatter/" + str;

         strFolder += "/_std/_std/main/";

      m_pindicator = (*f)(strNotifyIcon,"icon128", strFolder, this);
   }
   if(m_pindicator == NULL)
      {
         DestroyWindow();
         return false;
      }
#else
#endif

      m_bCreated = true;

      return true;

   }

   bool notify_icon::ModifyIcon(sp(::visual::icon) hicon)
   {

      if(!m_bCreated)
         return false;

#ifdef WINDOWSEX
      m_nid.hIcon       = (HICON) *hicon;
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
#elif defined(LINUX)
{
         BASECORE_APP_INDICATOR_TERM * f =  (BASECORE_APP_INDICATOR_TERM *) dlsym(g_pbasecore, "basecore_app_indicator_term");

      (*f)(m_pindicator);
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


   void notify_icon::__close()
   {

      m_plistener->OnNotifyIconMessage(m_uiId, WM_CLOSE);

   }


   void notify_icon::__quit()
   {

      m_plistener->OnNotifyIconMessage(m_uiId, WM_QUIT);

   }


   bool notify_icon::__close_is_closed()
   {


      return m_plistener->__close_is_closed();

   }


} // namespace user


