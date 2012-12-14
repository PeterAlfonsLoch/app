#pragma once


#ifdef WINDOWS

   #define HTHREAD HANDLE

#else

   class simple_event;

   #define HTHREAD simple_event *

#endif



namespace radix
{

   class thread;

}

namespace ca
{

   class CLASS_DECL_c thread_base
   {
   public:


      ::radix::thread      * m_pthread;


      virtual HTHREAD get_os_handle() const = 0;

   };

};


namespace user
{


   class interaction;


   class CLASS_DECL_c interaction_base
   {
   public:


      ::ca::thread_base *     m_pthread;
      ::user::interaction *   m_pui;


      virtual LRESULT message_handler(LPMESSAGE lpmessage) = 0;


   };


} // namespace user




