//
//  multithreading_thread_impl.h
//  aura
//
//
//
#pragma once


class thread_startup :
   virtual public object
{
public:


   ::thread *              m_pthread;
   ::thread_impl *         m_pthreadimpl;
   manual_reset_event      m_event;
   manual_reset_event      m_event2;
   DWORD                   m_dwCreateFlags;
   bool                    m_bError;
   int32_t                 m_iError;
   bool                    m_bSynch;


   thread_startup(sp(::aura::application) papp);
   ~thread_startup();

};



class CLASS_DECL_AURA thread_impl :
   virtual public command_target,
   virtual public ::aura::message_queue_listener
{
public:


   thread *                                  m_pthread;

   sp(ptr_array < ::user::interaction >)     m_spuiptra;
   sp(::user::timer_array)                   m_sptimera;
   
   bool                                      m_bDupHandle;
   HTHREAD                                   m_hthread;
   uint32_t                                  m_uiThread;

   list < ::user::frame_window * >           m_frameList;

   LPVOID                                    m_pThreadParams;
   __THREADPROC                              m_pfnThreadProc;

   manual_reset_event                        m_evFinish;
   UINT                                      m_nDisablePumpCount;
   mutex                                     m_mutexUiPtra;

   UINT                                      m_dwFinishTimeout;
   ::aura::message_queue_sp                 m_spqueue;


   thread_impl(sp(::aura::application) papp);
   virtual ~thread_impl();
   
   
   void construct();
   
   void construct(__THREADPROC pfnthread_implProc, LPVOID pParam);

   void CommonConstruct();

   virtual bool pre_init_instance();

   virtual bool initialize_instance();

   virtual bool finalize();

   virtual void pre_translate_message(signal_details * pobj);

   virtual void process_window_procedure_exception(::exception::base*,signal_details * pobj);

   virtual void process_message_filter(int32_t code,signal_details * pobj);

   virtual int32_t thread_startup(::thread_startup * pstartup);
   virtual bool thread_entry();
   virtual int32_t main();
   virtual int32_t thread_term();


   virtual int32_t exit_instance();
   virtual bool on_idle(LONG lCount);


   virtual void * get_os_data() const;
   virtual int_ptr get_os_int() const;

   operator HTHREAD() const;

   virtual int_ptr item() const;

   virtual void add(::user::interaction * pui);
   virtual void remove(::user::interaction * pui);

   virtual bool is_idle_message(signal_details * pobj);
   virtual bool is_idle_message(LPMESSAGE lpmsg);

   virtual void post_to_all_threads(UINT message,WPARAM wparam,LPARAM lparam);
   virtual bool post_thread_message(UINT message,WPARAM wParam = 0,lparam lParam = 0);
   virtual bool post_message(::user::interaction * pui,UINT message,WPARAM wParam = 0,lparam lParam = 0);

   virtual ::count get_ui_count();
   virtual ::user::interaction * get_ui(::index iIndex);
   virtual void set_timer(::user::interaction * pui,uint_ptr nIDEvent,UINT nEllapse);
   virtual void unset_timer(::user::interaction * pui,uint_ptr nIDEvent);
   virtual event & get_finish_event();
   virtual void step_timer();


   virtual void set_os_data(void * pvoidOsData);
   virtual void set_os_int(int_ptr iData);

   virtual bool initialize_message_queue();


   virtual int32_t run();

   virtual void message_handler(signal_details * pobj);


   virtual bool pump_message();




   virtual bool begin(int32_t epriority,uint_ptr nStackSize,uint32_t dwCreateFlags,LPSECURITY_ATTRIBUTES lpSecurityAttrs);
   virtual bool create_thread(int32_t epriority,uint_ptr nStackSize,uint32_t dwCreateFlagsParam,LPSECURITY_ATTRIBUTES lpSecurityAttrs);
   virtual bool begin_synch(int32_t *piStartupError,int32_t epriority,uint_ptr nStackSize,uint32_t dwCreateFlags,LPSECURITY_ATTRIBUTES lpSecurityAttrs);
   virtual bool create_thread_synch(int32_t *piStartupError,int32_t epriority,uint_ptr nStackSize,uint32_t dwCreateFlags,LPSECURITY_ATTRIBUTES lpSecurityAttrs);
   virtual bool begin_thread(bool bSynchStartup,int32_t *piStartupError,int32_t epriority,uint_ptr nStackSize,uint32_t dwCreateFlagsParam,LPSECURITY_ATTRIBUTES lpSecurityAttrs);

   virtual void thread_impl_delete();

   virtual void dispatch_thread_message(signal_details * pobj);

   virtual void start();
   virtual uint32_t ResumeThread();
   virtual bool has_message();
   
   virtual void set_priority(int32_t priority);
   virtual int32_t priority();

   virtual bool set_thread_priority(int32_t priority);
   virtual int32_t get_thread_priority();

   virtual bool on_run_exception(::exception::exception &);


   virtual message::e_prototype GetMessagePrototype(UINT uiMessage,UINT uiCode);

   virtual int get_x_window_count() const;

   virtual void do_events();

};





