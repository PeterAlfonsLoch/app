#pragma once

namespace radix
{
   class thread;

} // namespace radix


namespace ca
{

   class thread;


   class CLASS_DECL_ca thread :
      virtual public command_target,
      virtual public se_translator,
      virtual public pha(::user::interaction)
   {
   public:


      bool                                m_bRun;
      user::LPWndArray *                  m_puiptra;
      ::user::interaction::timer_array *  m_ptimera;
      comparable_array < ::ca::ca * >     m_captraDeletePool;
      bool                                m_bAutoDelete;     // enables 'delete this' after thread termination


      virtual void * get_os_data();
      virtual INT_PTR get_os_int();

      virtual void set_p(::radix::thread * p);


      virtual void set_os_data(void * pvoidOsData);
      virtual void set_os_int(INT_PTR iData);


      friend BOOL AfxInternalPreTranslateMessage(MSG* pMsg);

      virtual void construct();
      virtual void construct(AFX_THREADPROC pfnThreadProc, LPVOID pParam);

      virtual int main();

      virtual void CommonConstruct();

      virtual bool Begin(int nPriority = THREAD_PRIORITY_NORMAL, UINT nStackSize = 0,
         DWORD dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);

      virtual BOOL CreateThread(DWORD dwCreateFlags = 0, UINT nStackSize = 0,
         LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);

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

      virtual bool finalize();

      virtual int exit();

      virtual ::user::win::message::e_prototype thread::GetMessagePrototype(UINT uiMessage, UINT uiCode); 

      // running and idle processing
      virtual int run();
      virtual void pre_translate_message(gen::signal_object * pobj);
      virtual BOOL pump_message();     // low level message pump
      virtual BOOL on_idle(LONG lCount); // return TRUE if more idle processing
      virtual BOOL is_idle_message(gen::signal_object * pobj);  // checks for special messages

      // thread termination
      virtual int exit_instance(); // default will 'delete this'

      // Advanced: exception handling
      virtual void ProcessWndProcException(base_exception * e, gen::signal_object * pobj);

      // Advanced: handling messages sent to message filter hook
      virtual void ProcessMessageFilter(int code, gen::signal_object * pobj);

      // Advanced: virtual access to GetMainWnd()
      virtual ::user::interaction * GetMainWnd();
      virtual ::user::interaction * SetMainWnd(::user::interaction * pui);

      using pha(::user::interaction)::add;
      virtual void add(::user::interaction * pui);

      using pha(::user::interaction)::remove;
      virtual void remove(::user::interaction * pui);

      virtual int get_ui_count();
      virtual ::user::interaction * get_ui(int iIndex);
      virtual void set_timer(::user::interaction * pui, UINT_PTR nIDEvent, UINT nEllapse);
      virtual void unset_timer(::user::interaction * pui, UINT_PTR nIDEvent);
      virtual void set_auto_delete(bool bAutoDelete = true);
      virtual void set_run(bool bRun = true);
      virtual CEvent & get_finish_event();
      virtual bool get_run();
      virtual ::ca::thread * get_app_thread();
      virtual ::user::interaction * get_active_ui();
      virtual ::user::interaction * set_active_ui(::user::interaction * pui);
      virtual void step_timer();

      virtual void on_delete(::ca::ca * p);

   public:
      virtual ~thread();
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif
      virtual void Delete();
         // 'delete this' only if m_bAutoDelete == TRUE

      virtual void DispatchThreadMessageEx(gen::signal_object * pobj);  // helper
   };

   typedef smart_pointer < thread > thread_sp;

   CLASS_DECL_ca thread * get_thread();


   typedef thread * (* PFN_get_thread)();

   extern CLASS_DECL_ca PFN_get_thread g_pfn_get_thread;



} // namespace ca



