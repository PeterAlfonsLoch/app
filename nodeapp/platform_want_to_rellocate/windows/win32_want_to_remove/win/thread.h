#pragma once

BOOL AfxInternalPreTranslateMessage(MSG* pMsg);

namespace win
{

   class CLASS_DECL_VMSWIN thread :
      virtual public ::ca::thread
   {
   public:

   #ifdef _WIN32
	   // only valid while running
	   HANDLE m_hThread;       // this thread's HANDLE
	   operator HANDLE() const;
	   DWORD m_nThreadID;      // this thread's ID
   #else
	   operator pthread_t() const;
	   pthread_t m_thread;
   #endif


	   LPVOID                              m_pThreadParams; // generic parameters passed to starting function
	   AFX_THREADPROC                      m_pfnThreadProc;

      CEvent                              m_evFinish;
      UINT                                m_nDisablePumpCount;
      mutex                               m_mutexUiPtra;
	   ::user::interaction *               m_pMainWnd;       // main ::ca::window (usually same Application.GetMainWnd())
      ::user::interaction *               m_pActiveWnd;     // active main ::ca::window (may not be GetMainWnd())
	   BOOL                                m_bAutoDelete;     // enables 'delete this' after thread termination
      ::ca::thread *                      m_pAppThread;

      UINT                                m_dwFinishTimeout;

      ::thread *                          m_p;

      virtual void * get_os_data();
      virtual INT_PTR get_os_int();

      void set_os_data(void * pvoidOsData);
      void set_os_int(int iData);

      virtual void set_p(::thread * p);

      thread(::ca::application * papp);

      virtual void construct(AFX_THREADPROC pfnThreadProc, LPVOID pParam);

      virtual bool Begin(int nPriority = THREAD_PRIORITY_NORMAL, UINT nStackSize = 0,
	      DWORD dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);

	   BOOL CreateThread(DWORD dwCreateFlags = 0, UINT nStackSize = 0,
		   LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);


      virtual ::user::interaction * SetMainWnd(::user::interaction * pui);

      virtual void add(::user::interaction * pui);
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


      void OnPointerClear(::user::interaction * p);

	   int GetThreadPriority();
	   BOOL SetThreadPriority(int nPriority);

   // Operations
	   DWORD SuspendThread();
	   DWORD ResumeThread();
	   BOOL PostThreadMessage(UINT message, WPARAM wParam, LPARAM lParam);
      bool post_message(::user::interaction * pguie, UINT message, WPARAM wParam, LPARAM lParam);

      virtual bool PreInitInstance();

      // called when occurs an se_exception exception in run
      // return true to call run again
      virtual bool on_run_exception(::ca::exception & e);

   // Overridables
	   // thread initialization
	   virtual bool initialize_instance();

      virtual ::user::win::message::e_prototype thread::GetMessagePrototype(UINT uiMessage, UINT uiCode); 

	   // running and idle processing
	   virtual int run();
	   virtual void pre_translate_message(gen::signal_object * pobj);
	   virtual BOOL pump_message();     // low level message pump
	   virtual BOOL on_idle(LONG lCount); // return TRUE if more idle processing
	   virtual BOOL is_idle_message(gen::signal_object * pobj);  // checks for special messages
      virtual BOOL is_idle_message(LPMSG lpmsg);  // checks for special messages
      virtual void message_handler(gen::signal_object * pobj);

	   // thread termination
	   virtual int exit_instance(); // default will 'delete this'

	   // Advanced: exception handling
	   virtual void ProcessWndProcException(base_exception * e, gen::signal_object * pMsg);

	   // Advanced: handling messages sent to message filter hook
	   virtual void ProcessMessageFilter(int code, gen::signal_object * pobj);

	   // Advanced: virtual access to GetMainWnd()
	   virtual ::user::interaction* GetMainWnd();

   // Implementation
   public:
	   virtual ~thread();
   #ifdef _DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   #endif
	   void CommonConstruct();
	   virtual void Delete();
		   // 'delete this' only if m_bAutoDelete == TRUE



	   virtual void DispatchThreadMessageEx(gen::signal_object * pobj);  // helper
   };

} // namespace win



