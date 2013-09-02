#pragma once


#ifdef WINDOWSEX

typedef HANDLE HTHREAD;

#else

typedef hthread * HTHREAD;

#endif


class CLASS_DECL_c thread_base :
   virtual public object
{
public:


   thread *          m_pthread;


   thread_base();
   virtual ~thread_base();


   virtual HTHREAD get_os_handle() const;
   virtual int get_x_window_count() const;
   virtual void step_timer();
   virtual bool get_run();

   virtual bool verb();


};


namespace user
{


   class interaction;


    class CLASS_DECL_c interaction_base :
        virtual public ::ca::ca
   {
   public:


      ::thread_base *         m_pthread;
      ::user::interaction *   m_pui;


      virtual LRESULT message_handler(LPMESSAGE lpmessage) = 0;
      virtual sp(interaction_base) get_parent_base() const = 0;
      virtual sp(interaction_base) set_parent_base(sp(interaction_base) pguieParent) = 0;
      virtual oswindow get_parent_handle() const = 0;
      virtual bool is_message_only_window() const = 0;
#ifdef METROWIN
      virtual Platform::Agile<Windows::UI::Core::CoreWindow> get_os_window() = 0;
#endif

   };


} // namespace user




