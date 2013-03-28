#include "framework.h"

namespace ca
{

   message_window_simple_callback::message_window_simple_callback()
   { 
   }

   message_window_simple_callback::message_window_simple_callback(::ca::application * papp) :
      m_uiMessage(papp)
   { 
   }

   message_window_simple_callback::~message_window_simple_callback()
   {
   }

   bool message_window_simple_callback::initialize_message_window(::ca::application * papp, const char * pszName)
   {
      
      set_app(papp);

      m_uiMessage.set_app(papp);

      return m_uiMessage.create_message_window(pszName, this);

   }


   bool message_window_simple_callback::initialize_message_window(const char * pszName)
   {

      return m_uiMessage.create_message_window(pszName, this);

   }


   bool message_window_simple_callback::finalize_message_window()
   {

      bool bOk = true;

      if(m_uiMessage.IsWindow())
      {
         bOk = m_uiMessage.DestroyWindow();
      }

      return bOk;

   }


} // namespace ca



