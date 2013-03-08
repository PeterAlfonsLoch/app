#pragma once


#ifdef WINDOWS

   #define HTHREAD HANDLE

#else

   class simple_event;

   #define HTHREAD simple_event *

#endif



namespace ca
{

   class thread;

   class CLASS_DECL_c thread_base
   {
   public:


      ::ca::thread      * m_pthread;


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
      virtual interaction * get_parent() const = 0;
      virtual interaction * set_parent(interaction * pguieParent) = 0;
#ifdef METROWIN
      virtual Platform::Agile<Windows::UI::Core::CoreWindow> get_os_window() = 0;
#endif

   };


} // namespace user


CLASS_DECL_c simple_mutex & user_mutex();

