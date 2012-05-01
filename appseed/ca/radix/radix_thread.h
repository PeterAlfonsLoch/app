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
      thread(::ca::application * papp, AFX_THREADPROC pfnThreadProc, LPVOID pParam);
      virtual ~thread();


      virtual INT_PTR get_os_data() const;
      virtual INT_PTR get_os_int() const;

      virtual bool Begin(int nPriority = ::get_thread_priority_normal(), UINT nStackSize = 0, DWORD dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);

      virtual BOOL CreateThread(DWORD dwCreateFlags = 0, UINT nStackSize = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);

      virtual int GetThreadPriority();
      virtual BOOL SetThreadPriority(int nPriority);

      virtual DWORD SuspendThread();
      virtual DWORD ResumeThread();
      virtual BOOL PostThreadMessage(UINT message, WPARAM wParam, LPARAM lParam);
      virtual bool post_message(::user::interaction * pguie, UINT message, WPARAM wParam, LPARAM lParam);

      virtual bool PreInitInstance();

      // called when occurs an se_exception exception in run
      // return true to call run again
      virtual bool on_run_exception(::ca::exception & e);

      // Overridables
      // thread initialization
      virtual bool initialize_instance();

      virtual ::gen::message::e_prototype GetMessagePrototype(UINT uiMessage, UINT uiCode);

      // running and idle processing
      virtual int run();
      virtual void pre_translate_message(gen::signal_object * pobj);
      virtual BOOL pump_message();     // low level message pump
      virtual BOOL on_idle(LONG lCount); // return TRUE if more idle processing
      virtual BOOL is_idle_message(gen::signal_object * pobj);  // checks for special messages

      // thread termination
      virtual int exit_instance(); // default will 'delete this'

      // Advanced: exception handling
      virtual void ProcessWndProcException(base_exception* e, gen::signal_object * pobj);

      // Advanced: handling messages sent to message filter hook
      virtual void ProcessMessageFilter(int code, gen::signal_object * pobj);

      // Advanced: virtual access to GetMainWnd()
      virtual ::user::interaction* GetMainWnd();

      virtual ::user::interaction * SetMainWnd(::user::interaction * pui);

      virtual void add(::user::interaction * pui);
      virtual void remove(::user::interaction * pui);
      virtual ::count get_ui_count();
      virtual ::user::interaction * get_ui(index iIndex);
      virtual void set_timer(::user::interaction * pui, UINT_PTR nIDEvent, UINT nEllapse);
      virtual void unset_timer(::user::interaction * pui, UINT_PTR nIDEvent);
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

      virtual int main();


      virtual void wait();


   };

   CLASS_DECL_ca void thread_alloc_ready(bool bReady);


} // namespace radix
