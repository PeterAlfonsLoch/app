#include "framework.h" // from ""axis/user/user.h"


namespace linux
{


   message_queue::message_queue(sp(::aura::application) papp):
      element(papp),
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

      return ::user::interaction::create_message_queue(pszName);

   }


   void message_queue::message_handler(signal_details * pobj)
   {

      message_queue_message_handler(pobj);

      if(pobj->m_bRet)
         return;

      return ::user::interaction::message_handler(pobj);

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

      return IsWindow();

   }


   bool message_queue::message_queue_set_timer(uint_ptr uiId,DWORD dwMillis)
   {

      return SetTimer(uiId,dwMillis,NULL) != FALSE;

   }

   bool message_queue::message_queue_del_timer(uint_ptr uiId)
   {

      return KillTimer(uiId) != FALSE;

   }

   bool message_queue::message_queue_post_message(uint32_t uiMessage,WPARAM wparam,lparam lparam)
   {

      return post_message(uiMessage,wparam,lparam);

   }

   LRESULT message_queue::message_queue_send_message(uint32_t uiMessage,WPARAM wparam,lparam lparam)
   {

      return send_message(uiMessage,wparam,lparam);

   }

   bool message_queue::message_queue_destroy()
   {

      return DestroyWindow() != NULL;

   }


   void * message_queue::message_queue_get_os_handle()
   {

      return get_os_data();

   }


} // namespace linux




































