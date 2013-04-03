#include "framework.h"

namespace ca
{

   message_window_simple_callback::message_window_simple_callback()
   {
   }

   message_window_simple_callback::message_window_simple_callback(::ca::application * papp) :
      ca(papp)
   {
   }

   message_window_simple_callback::~message_window_simple_callback()
   {
   }

   bool message_window_simple_callback::initialize_message_window(::ca::application * papp, const char * pszName)
   {

      set_app(papp);

      return initialize_message_window(pszName);

   }


   bool message_window_simple_callback::initialize_message_window(const char * pszName)
   {

      m_spuiMessage = new user::interaction(get_app());

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


} // namespace ca



