//#include "framework.h"
//#include "base/user/user.h"
#ifdef METROWIN
//#include "base/base/node/metrowin/metrowin.h"
#else
//#include "windows.h"
#endif


namespace windows
{


   message_queue::message_queue(::aura::application * papp):
      ::object(papp),
      ::aura::message_queue(papp)
   {

      m_plistener          = NULL;

   }


   message_queue::~message_queue()
   {

   }


   bool message_queue::create_message_queue(const char * pszName,::aura::message_queue_listener * plistener)
   {

      if(!::aura::message_queue::create_message_queue(pszName,plistener))
         return true;

      //return ::user::interaction::create_message_queue(pszName);
      return false;

   }


   void message_queue::message_handler(signal_details * pobj)
   {

      message_queue_message_handler(pobj);

      if(pobj->m_bRet)
         return;

//      return ::user::interaction::message_handler(pobj);
      return;

   }


   void message_queue::message_queue_message_handler(signal_details * pobj)
   {

      if(m_plistener != NULL)
      {

         m_plistener->message_queue_message_handler(pobj);

      }

   }


   bool message_queue::message_queue_is_initialized()
   {

      return ::IsWindow(m_hwnd);

   }


   bool message_queue::message_queue_set_timer(uint_ptr uiId,DWORD dwMillis)
   {

      return ::SetTimer(m_hwnd, uiId,dwMillis,NULL) != FALSE;

   }

   bool message_queue::message_queue_del_timer(uint_ptr uiId)
   {

      return KillTimer(m_hwnd, uiId) != FALSE;

   }

   bool message_queue::message_queue_post_message(uint32_t uiMessage,WPARAM wparam,lparam lparam)
   {

      return ::PostMessage(m_hwnd, uiMessage,wparam,lparam);

   }

   LRESULT message_queue::message_queue_send_message(uint32_t uiMessage,WPARAM wparam,lparam lparam)
   {

      return ::SendMessage(m_hwnd, uiMessage,wparam,lparam);

   }

   bool message_queue::message_queue_destroy()
   {

      return DestroyWindow(m_hwnd) != NULL;

   }


   void * message_queue::message_queue_get_os_handle()
   {

      return get_os_data();

   }


} // namespace windows




































