#include "framework.h"


message_queue::message_queue()
{
}

message_queue::message_queue(sp(::base::application) papp) :
   element(papp)
{
}

message_queue::~message_queue()
{
}

bool message_queue::create_message_queue(sp(::base::application) papp, const char * pszName)
{

   set_app(papp);

   return create_message_queue(pszName);

}


bool message_queue::create_message_queue(const char * pszName)
{

   m_spuiMessage = canew(user::interaction(get_app()));

   return m_spuiMessage->create_message_queue(pszName, this);

}


bool message_queue::destroy_message_queue()
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


