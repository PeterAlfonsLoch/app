#include "StdAfx.h"

namespace ca
{

   message_window_simple_callback::message_window_simple_callback()
   { 
   }

   message_window_simple_callback::message_window_simple_callback(::ca::application * papp) :
      m_spwindowMessage(papp)
   { 
   }

   message_window_simple_callback::~message_window_simple_callback()
   {
   }

   bool message_window_simple_callback::initialize_message_window(::ca::application * papp, const char * pszName)
   {
      if(m_spwindowMessage.m_p == NULL)
         m_spwindowMessage.create(papp);
      return m_spwindowMessage->create_message_window(pszName, this);
   }

   bool message_window_simple_callback::initialize_message_window(const char * pszName)
   {
      return m_spwindowMessage->create_message_window(pszName, this);
   }

   bool message_window_simple_callback::finalize_message_window()
   {
      bool bOk = true;
      if(m_spwindowMessage.is_set())
      {
         if(m_spwindowMessage->IsWindow())
         {
            bOk = m_spwindowMessage->DestroyWindow() != FALSE;
         }
         try
         {
            m_spwindowMessage.destroy();
         }
         catch(...)
         {
            bOk = false;
         }
      }
      return bOk;
   }

} // namespace ca