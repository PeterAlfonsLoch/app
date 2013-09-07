#include "framework.h"


message_window_simple_callback::message_window_simple_callback()
{
}

message_window_simple_callback::message_window_simple_callback(sp(base_application) papp) :
   element(papp)
{
}

message_window_simple_callback::~message_window_simple_callback()
{
}

bool message_window_simple_callback::initialize_message_window(sp(base_application) papp, const char * pszName)
{

   set_app(papp);

   return initialize_message_window(pszName);

}


bool message_window_simple_callback::initialize_message_window(const char * pszName)
{

   m_spuiMessage = canew(user::interaction(get_app()));

   return m_spuiMessage->create_message_window(pszName, this);

}


bool message_window_simple_callback::finalize_message_window()
{

   bool bOk = true;

   if(m_spuiMessage.is_set())
   {

      try
      {

         if(m_spuiMessage->IsWindow())
         {

            bOk = m_spuiMessage->DestroyWindow();

         }

      }
      catch(...)
      {

         bOk = false;

      }

      m_spuiMessage.release();

   }

   return bOk;

}


