#pragma once


namespace ca
{


   class thread_base;


} // namespace ca


class hthread
{
public:


   simple_event             * m_pevent;
   ::ca::thread_base        * m_pthread;


   hthread();
   ~hthread();


};



#ifdef WINDOWS

   #define HTHREAD HANDLE

#else

   class simple_event;

   #define HTHREAD hthread *

#endif


namespace ca
{


   class thread;


   class CLASS_DECL_c thread_base
   {
   public:


      ::ca::thread      * m_pthread;


      thread_base();
      virtual ~thread_base();


      virtual HTHREAD get_os_handle() const = 0;
      virtual int get_x_window_count() const = 0;


   };


} // namespace ca




namespace user
{


   class interaction;


   class CLASS_DECL_c interaction_base
   {
   public:


      ::ca::thread_base *     m_pthread;
      ::user::interaction *   m_pui;


      virtual LRESULT message_handler(LPMESSAGE lpmessage) = 0;
      //virtual sp(interaction) get_parent() const = 0;
      //virtual sp(interaction) set_parent(sp(interaction) pguieParent) = 0;
#ifdef METROWIN
      virtual Platform::Agile<Windows::UI::Core::CoreWindow> get_os_window() = 0;
#endif

   };


} // namespace user


CLASS_DECL_c simple_mutex & user_mutex();

