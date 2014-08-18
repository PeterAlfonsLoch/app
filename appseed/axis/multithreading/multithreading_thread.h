#pragma once


class replace_thread;



class CLASS_DECL_AXIS thread :
   virtual public command_target,
#ifdef WINDOWS
   virtual public ::exception::translator,
#endif
   virtual public ptr_array < ::user::interaction >,
   virtual public ::axis::live_object,
   virtual public event_base
{
public:

   single_lock *                          m_pslUser;
   static bool                            s_bAllocReady;
   mutex *                                m_pmutex;
   bool                                   m_bRun;

   thread_impl_sp                         m_pthreadimpl;

   bool                                   m_bAutoDelete;       // enables 'delete this' after thread termination
   uint_ptr                               m_dwAlive;
   bool                                   m_bReady;
   int32_t                                m_iReturnCode;
   ::user::interaction *                  m_puiMain;           // main interaction_impl (usually same System.m_puiMain)
   ::user::interaction *                  m_puiActive;         // active main interaction_impl (may not be m_puiMain)
   bool *                                 m_pbReady;
   property_set                           m_set;
   string                                 m_strWorkUrl;
   ptr_array < thread >                   m_threadptraDependent;
   ptr_array < thread >                   m_threadptraRequired;


   bool                                   m_bZipIsDir;

   replace_thread *                       m_preplacethread;


   thread();
   thread(sp(::axis::application) papp);
   thread(sp(::axis::application) papp, __THREADPROC pfnThreadProc, LPVOID pParam);
   virtual ~thread();

   ///  \brief		starts thread on first call
   virtual void start();

   virtual void * get_os_data() const;
   virtual int_ptr get_os_int() const;


   virtual HTHREAD get_os_handle() const;


   virtual void set_os_data(void * pvoidOsData);
   virtual void set_os_int(int_ptr iData);


   friend bool __internal_pre_translate_message(MESSAGE * pMsg);


   void CommonConstruct();


   virtual bool pre_run();


   virtual bool finalize();

   virtual int32_t exit();


   virtual void on_keep_alive();
   virtual bool is_alive();


   virtual bool has_message();

   virtual int get_x_window_count() const;

   virtual wait_result wait(const duration & duration);

   void set_priority(int32_t priority);

   int32_t priority();


   virtual bool is_auto_delete();

   virtual bool begin(int32_t epriority = ::get_scheduling_priority_normal(), uint_ptr nStackSize = 0, uint32_t dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);

   virtual bool create_thread(int32_t epriority = ::get_scheduling_priority_normal(),uint_ptr nStackSize = 0,uint32_t dwCreateFlags = 0,LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);

   virtual bool begin_synch(int32_t *piStartupError, int32_t epriority = ::get_scheduling_priority_normal(),uint_ptr nStackSize = 0,uint32_t dwCreateFlags = 0,LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);

   virtual bool create_thread_synch(int32_t *piStartupError,int32_t epriority = ::get_scheduling_priority_normal(),uint_ptr nStackSize = 0,uint32_t dwCreateFlags = 0,LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);


   virtual int32_t get_thread_priority();
   virtual bool set_thread_priority(int32_t epriority);

   virtual uint32_t ResumeThread();
   virtual bool post_thread_message(UINT message, WPARAM wParam = 0, lparam lParam = 0);
   virtual bool post_message(sp(::user::interaction) pui, UINT message, WPARAM wParam = 0, lparam lParam = 0);

   virtual bool pre_init_instance();

   virtual bool on_run_exception(::exception::exception &);

   virtual bool initialize_instance();

   virtual message::e_prototype GetMessagePrototype(UINT uiMessage, UINT uiCode);

   // running and idle processing
   virtual int32_t run();
   virtual void pre_translate_message(signal_details * pobj);
   virtual bool pump_message();     // low level message pump
   virtual bool on_idle(LONG lCount); // return TRUE if more idle processing
   virtual bool is_idle_message(signal_details * pobj);  // checks for special messages
   virtual bool is_idle_message(LPMESSAGE lpmessage);  // checks for special messages

   virtual int32_t exit_instance();

   virtual void process_window_procedure_exception(::exception::axis*,signal_details * pobj);

   virtual void process_message_filter(int32_t code, signal_details * pobj);

   virtual void add(sp(::user::interaction) pui);
   virtual void remove(::user::interaction * pui);
   virtual ::count get_ui_count();
   virtual ::user::interaction * get_ui(index iIndex);
   virtual void set_timer(sp(::user::interaction) pui, uint_ptr nIDEvent, UINT nEllapse);
   virtual void unset_timer(sp(::user::interaction) pui, uint_ptr nIDEvent);
   virtual void set_auto_delete(bool bAutoDelete = true);
   virtual void set_run(bool bRun = true);
   virtual event & get_finish_event();
   virtual bool get_run();
   virtual sp(::user::interaction) get_active_ui();
   virtual sp(::user::interaction) set_active_ui(sp(::user::interaction) pui);
   virtual void step_timer();
   virtual bool on_run_step();


   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
   virtual void Delete();
   // 'delete this' only if m_bAutoDelete == TRUE

   virtual void dispatch_thread_message(signal_details * pobj);  // helper

   virtual int32_t main();





   virtual void wait();


   virtual int_ptr item() const;



   virtual bool verb();


   virtual void post_to_all_threads(UINT message,WPARAM wparam,LPARAM lparam);


   virtual void register_dependent_thread(::thread * pthread);
   virtual void unregister_dependent_thread(::thread * pthread);
   virtual void signal_close_dependent_threads();
   virtual void wait_close_dependent_threads(const duration & duration);
   virtual void register_at_required_threads();
   virtual void unregister_from_required_threads();

   virtual void do_events();
   virtual void do_events(const duration & duration);

};



class CLASS_DECL_AXIS replace_thread
{
public:

   smart_pointer < ::thread >    m_spthread;
   ::thread *                    m_pthreadNew;
   mutex &                       m_mutex;

   replace_thread(mutex & m): m_mutex(m) {  }

   void replace(::thread * pcanew);

   bool do_replace(::thread * pthread);

};
