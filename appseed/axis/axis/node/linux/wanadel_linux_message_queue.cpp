#include "framework.h" // from ""axis/user/user.h"
#include "linux.h"


namespace linux
{


   message_queue::message_queue(sp(::aura::application) papp):
      ::object(papp),
      ::user::message_queue(papp)
   {

      m_plistener          = NULL;

   }


   message_queue::~message_queue()
   {

   }


   bool message_queue::create_message_queue(const char * pszName,::user::message_queue_listener * plistener)
   {

      if(!::user::message_queue::create_message_queue(pszName,plistener))
         return true;

//      return ::user::interaction::create_message_queue(pszName);
      return true;

   }


   void message_queue::message_handler(signal_details * pobj)
   {

      message_queue_message_handler(pobj);

      if(pobj->m_bRet)
         return;

      //return ::user::interaction::message_handler(pobj);
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

      return IsWindow(m_oswindow);

   }


   bool message_queue::message_queue_set_timer(uint_ptr uiId,DWORD dwMillis)
   {

      //return SetTimer(m_oswindow, uiId,dwMillis,NULL) != FALSE;
      return true;

   }

   bool message_queue::message_queue_del_timer(uint_ptr uiId)
   {

      //return KillTimer(m_oswindow, uiId) != FALSE;
      return true;

   }

   bool message_queue::message_queue_post_message(uint32_t uiMessage,WPARAM wparam,lparam lparam)
   {

      //return post_message(uiMessage,wparam,lparam);
      return true;

   }

   LRESULT message_queue::message_queue_send_message(uint32_t uiMessage,WPARAM wparam,lparam lparam)
   {

      //return send_message(uiMessage,wparam,lparam);
      return false;

   }

   bool message_queue::message_queue_destroy()
   {

      return DestroyWindow(m_oswindow) != NULL;

   }


   void * message_queue::message_queue_get_os_handle()
   {

      return m_oswindow;

   }


} // namespace linux




































