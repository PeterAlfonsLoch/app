#include "StdAfx.h"

namespace winservice_1
{
   message_window::message_window(::ca::application * papp) :
      ca(papp),
   ::ca::message_window_simple_callback(papp)
   {
      m_pthread = NULL;
   }

   message_window::~message_window()
   {
   }

   bool message_window::create()
   {
      string strName = "ca2::fontopus::message_wnd::winservice_1";
      if(!initialize_message_window(strName))
      {
         return false;
      }
      return true;
   }

   void message_window::message_window_message_handler(gen::signal_object * pobj)
   {
      SCAST_PTR(user::win::message::base, pbase, pobj);
      if(pbase->m_uiMessage == WM_APP + 2000)
      {
         m_pthread->_001OnApp2000(pbase);
         pbase->m_bRet = true;
      }
   }

} // namespace winservice_1