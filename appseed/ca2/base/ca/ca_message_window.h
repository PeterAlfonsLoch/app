#pragma once


#include "ca_window.h"


namespace ca
{

   class CLASS_DECL_ca2 window_callback :
      virtual public ::ca::object
   {
   public:
      virtual void message_window_message_handler(::ca::signal_object * pobj) = 0;
   };

   class CLASS_DECL_ca2 message_window_simple_callback :
      virtual public window_callback
   {
   public:


      sp(::user::interaction)        m_spuiMessage;


      message_window_simple_callback();
      message_window_simple_callback(sp(::ca::application) papp);
      virtual ~message_window_simple_callback();


      bool initialize_message_window(sp(::ca::application) papp, const char * pszName);
      bool initialize_message_window(const char * pszName);
      bool finalize_message_window();

   };

} // namespace ca
