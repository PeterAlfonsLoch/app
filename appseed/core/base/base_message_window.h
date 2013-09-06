#pragma once


class CLASS_DECL_ca2 message_window_callback :
   virtual public object
{
public:

   virtual void message_window_message_handler(signal_details * pobj) = 0;

};


class CLASS_DECL_ca2 message_window_simple_callback :
   virtual public message_window_callback
{
public:


   sp(::user::interaction)        m_spuiMessage;


   message_window_simple_callback();
   message_window_simple_callback(sp(base_application) papp);
   virtual ~message_window_simple_callback();


   bool initialize_message_window(sp(base_application) papp, const char * pszName);
   bool initialize_message_window(const char * pszName);
   bool finalize_message_window();

};



