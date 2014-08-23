#include "framework.h"


namespace windows
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


   bool message_queue::create_message_queue(const char * pszName,::message_queue_listener * plistener)
   {

      m_plistener = plistener;

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


   bool message_queue::message_queue_destroy()
   {

      return DestroyWindow() != NULL;

   }


} // namespace windows





