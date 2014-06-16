//
//  multithreading_thread_impl.h
//  base
//
//  Created by Carlos Gustavo Cecyn Lundgren on 16/05/14.
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


   thread_startup(sp(::base::application) papp);
   ~thread_startup();

};



class CLASS_DECL_BASE thread_impl :
   virtual public thread,
   virtual public message_queue
{
public:


   sp(::user::interaction_ptr_array)      m_puiptra;
   sp(::user::interaction::timer_array)   m_ptimera;
   
   HTHREAD                                   m_hthread;
   uint32_t                                  m_uiThread;

   list < sp(::user::frame_window) >         m_frameList;

   bool                                      m_bCreatingMessageWindow;

   LPVOID                                    m_pThreadParams;
   __THREADPROC                              m_pfnThreadProc;

   manual_reset_event                        m_evFinish;
   UINT                                      m_nDisablePumpCount;
   mutex                                     m_mutexUiPtra;

   UINT                                      m_dwFinishTimeout;


   thread_impl(sp(::base::application) papp);
   virtual ~thread_impl();
   
   
   void construct();
   
   void construct(__THREADPROC pfnthread_implProc, LPVOID pParam);

   void CommonConstruct();

   virtual bool pre_init_instance();

   virtual bool initialize_instance();

   virtual void pre_translate_message(signal_details * pobj);

   virtual void process_window_procedure_exception(::exception::base*,signal_details * pobj);

   virtual void process_message_filter(int32_t code,signal_details * pobj);

   virtual int32_t thread_startup(::thread_startup * pstartup);
   virtual bool thread_entry(int32_t * piReturnCode);
   virtual int32_t main();
   virtual int32_t thread_term(int32_t nResult);


   virtual int32_t exit_instance();
   virtual bool on_idle(LONG lCount);


   virtual void * get_os_data() const;
   virtual int_ptr get_os_int() const;

   operator HTHREAD() const;

   virtual int_ptr item() const;

   virtual void add(sp(::user::interaction) pui);
   virtual void remove(::user::interaction * pui);

   virtual bool is_idle_message(signal_details * pobj);
   virtual bool is_idle_message(LPMESSAGE lpmsg);

   virtual void post_to_all_threads(UINT message,WPARAM wparam,LPARAM lparam);
   virtual bool post_thread_message(UINT message,WPARAM wParam = 0,lparam lParam = 0);
   virtual bool post_message(sp(::user::interaction) pui,UINT message,WPARAM wParam = 0,lparam lParam = 0);

   virtual ::count get_ui_count();
   virtual ::user::interaction * get_ui(::index iIndex);
   virtual void set_timer(sp(::user::interaction) pui,uint_ptr nIDEvent,UINT nEllapse);
   virtual void unset_timer(sp(::user::interaction) pui,uint_ptr nIDEvent);
   virtual void set_auto_delete(bool bAutoDelete = true);
   virtual void set_run(bool bRun = true);
   virtual event & get_finish_event();
   virtual bool get_run();
   virtual sp(::user::interaction) get_active_ui();
   virtual sp(::user::interaction) set_active_ui(sp(::user::interaction) pui);
   virtual void step_timer();


   virtual void set_os_data(void * pvoidOsData);
   virtual void set_os_int(int_ptr iData);
   virtual void message_queue_message_handler(signal_details * pobj);

   void _001PostCreateMessageWindow();
   DECL_GEN_SIGNAL(_001OnCreateMessageWindow);


   virtual int32_t run();

   void message_handler(signal_details * pobj);


   virtual bool pump_message();

   bool set_thread_priority(int32_t priority);
   int32_t get_thread_priority();



   virtual bool begin(int32_t epriority,uint_ptr nStackSize,uint32_t dwCreateFlags,LPSECURITY_ATTRIBUTES lpSecurityAttrs);
   virtual bool create_thread(int32_t epriority,uint_ptr nStackSize,uint32_t dwCreateFlagsParam,LPSECURITY_ATTRIBUTES lpSecurityAttrs);
   virtual bool begin_synch(int32_t *piStartupError,int32_t epriority,uint_ptr nStackSize,uint32_t dwCreateFlags,LPSECURITY_ATTRIBUTES lpSecurityAttrs);
   virtual bool create_thread_synch(int32_t *piStartupError,int32_t epriority,uint_ptr nStackSize,uint32_t dwCreateFlags,LPSECURITY_ATTRIBUTES lpSecurityAttrs);
   virtual bool begin_thread(bool bSynchStartup,int32_t *piStartupError,int32_t epriority,uint_ptr nStackSize,uint32_t dwCreateFlagsParam,LPSECURITY_ATTRIBUTES lpSecurityAttrs);

   void Delete();

   virtual void dispatch_thread_message(signal_details * pobj);

};





