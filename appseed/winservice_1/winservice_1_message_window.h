#pragma once

namespace winservice_1
{

   class thread;

   class message_window :
      virtual public ::ca::message_window_simple_callback
   {
   public:

      thread * m_pthread;


      message_window(::ca::application * papp);
      virtual ~message_window();


      virtual void message_window_message_handler(gen::signal_object * pobj);
      bool create();

   };

} // namespace winservice_1
