#pragma once


namespace radix
{


   class CLASS_DECL_ca thread :
      virtual public ::ca::thread,
      virtual public ::ca::thread_sp
   {
   public:

      static bool    s_bAllocReady;
      mutex          m_mutex;


      thread();
      thread(::ca::application * papp);
      thread(::ca::application * papp, __THREADPROC pfnThreadProc, LPVOID pParam);
      virtual ~thread();


      virtual void * get_os_data() const;
      virtual int_ptr get_os_int() const;

      virtual bool begin(::ca::e_thread_priority epriority = ::get_thread_priority_normal(), uint_ptr nStackSize = 0, uint32_t dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);

      virtual bool create_thread(::ca::e_thread_priority epriority = ::get_thread_priority_normal(), uint32_t dwCreateFlags = 0, uint_ptr nStackSize = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);

      virtual ::ca::e_thread_priority get_thread_priority();
      virtual bool set_thread_priority(::ca::e_thread_priority epriority);

//      virtual uint32_t SuspendThread();
      virtual uint32_t ResumeThread();
      virtual bool post_thread_message(UINT message, WPARAM wParam, LPARAM lParam);
      virtual bool post_message(::user::interaction * pguie, UINT message, WPARAM wParam, LPARAM lParam);

      virtual bool PreInitInstance();

      // called when occurs an standard_exception exception in run
      // return true to call run again
      virtual bool on_run_exception(::ca::exception & e);

      // Overridables
      // thread initialization
      virtual bool initialize_instance();

      virtual ::gen::message::e_prototype GetMessagePrototype(UINT uiMessage, UINT uiCode);

      // running and idle processing
      virtual int32_t run();
      virtual void pre_translate_message(gen::signal_object * pobj);
      virtual bool pump_message();     // low level message pump
      virtual bool on_idle(LONG lCount); // return TRUE if more idle processing
      virtual bool is_idle_message(gen::signal_object * pobj);  // checks for special messages

      // thread termination
      virtual int32_t exit_instance(); // default will 'delete this'

      // Advanced: exception handling
      virtual void ProcessWndProcException(base_exception* e, gen::signal_object * pobj);

      // Advanced: handling messages sent to message filter hook
      virtual void ProcessMessageFilter(int32_t code, gen::signal_object * pobj);

      // Advanced: virtual access to GetMainWnd()
      virtual ::user::interaction* GetMainWnd();

      virtual ::user::interaction * SetMainWnd(::user::interaction * pui);

      virtual void add(::user::interaction * pui);
      virtual void remove(::user::interaction * pui);
      virtual ::count get_ui_count();
      virtual ::user::interaction * get_ui(index iIndex);
      virtual void set_timer(::user::interaction * pui, uint_ptr nIDEvent, UINT nEllapse);
      virtual void unset_timer(::user::interaction * pui, uint_ptr nIDEvent);
      virtual void set_auto_delete(bool bAutoDelete = true);
      virtual void set_run(bool bRun = true);
      virtual event & get_finish_event();
      virtual bool get_run();
      virtual ::ca::thread * get_app_thread();
      virtual ::user::interaction * get_active_ui();
      virtual ::user::interaction * set_active_ui(::user::interaction * pui);
      virtual void step_timer();


      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
      virtual void Delete();
      // 'delete this' only if m_bAutoDelete == TRUE

      virtual void DispatchThreadMessageEx(gen::signal_object * pobj);  // helper

      virtual int32_t main();


      virtual void wait();

#ifdef WINDOWS
      virtual HANDLE item() const;
#else
      virtual int_ptr item() const;
#endif


   };

   CLASS_DECL_ca void thread_alloc_ready(bool bReady);


} // namespace radix
