#pragma once



namespace metrowin
{


   class CLASS_DECL_BASE thread :
      virtual public ::thread_impl//,
      //virtual public ::message_queue
   {
   public:

      /*
      // only valid while running
      HTHREAD                                       m_hThread;       // this thread's HANDLE
      uint32_t                                     m_nThreadID;      // this thread's ID

      static comparable_array < HTHREAD >          s_haThread;
      static comparable_array < ::thread * >   s_threadptra;
      // list of frame_window objects for thread
      // temporary/permanent ::map state
      uint32_t                                     m_nTempMapLock;           // if not 0, temp maps locked
      LPVOID                                       m_pThreadParams; // generic parameters passed to starting function
      __THREADPROC                                 m_pfnThreadProc;
      event                                        m_evFinish;
      UINT                                         m_nDisablePumpCount;
      mutex                                        m_mutexUiPtra;
      ::thread *                               m_pAppThread;
      UINT                                         m_dwFinishTimeout;

      */

      thread(::base::application * papp);


      //operator HANDLE() const;

      //virtual void * get_os_data() const;
      //virtual int_ptr get_os_int() const;

      //void set_os_data(void * pvoidOsData);
      //void set_os_int(int_ptr iData);



      //virtual void construct(__THREADPROC pfnThreadProc, LPVOID pParam);

      //virtual bool begin(int32_t epriority = ::get_scheduling_priority_normal(), uint_ptr nStackSize = 0, uint32_t uiCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL) override;

      //virtual bool create_thread(int32_t epriority = ::get_scheduling_priority_normal(), uint32_t uiCreateFlags = 0, uint_ptr nStackSize = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL) override;


      //virtual sp(::user::interaction) SetMainWnd(sp(::user::interaction) pui);

      //virtual int thread_entry(::core::thread_startup * pstartup);
      //virtual int main();
      //virtual int thread_term(int nResult);

      /*
      virtual void add(sp(::user::interaction) pui);
      virtual void remove(::user::interaction * pui);
      virtual ::count get_ui_count();
      virtual ::user::interaction * get_ui(::index iIndex);
      virtual void set_timer(sp(::user::interaction) pui, uint_ptr nIDEvent, UINT nEllapse);
      virtual void unset_timer(sp(::user::interaction) pui, uint_ptr nIDEvent);
      virtual void set_auto_delete(bool bAutoDelete = true);
      virtual void set_run(bool bRun = true);
      virtual event & get_finish_event();
      virtual bool get_run();
      virtual ::thread * get_app_thread();
      virtual sp(::user::interaction) get_active_ui();
      virtual sp(::user::interaction) set_active_ui(sp(::user::interaction) pui);
      virtual void step_timer();


/**
* \file		src/lib/pal/linux/thread_linux.hpp
* \brief	Platform independent threads and synchronization objects (linux version)
* \author	Thomas Nass
*/

      /*

      virtual void on_delete(element * poc);


      virtual void start();

      int get_thread_priority();
      bool set_thread_priority(int nPriority);

   // Operations
      uint32_t SuspendThread();
      uint32_t ResumeThread();
      bool post_thread_message(UINT message, WPARAM wParam = 0, lparam lParam = NULL) override;
      bool post_message(sp(::user::interaction) pguie, UINT message, WPARAM wParam = 0, lparam lParam = NULL);

      virtual bool PreInitInstance();

      // called when occurs an standard_exception exception in run
      // return true to call run again
      virtual bool on_run_exception(::exception::exception & e);

   // Overridables
      // thread initialization
      virtual bool initialize_instance();

      virtual ::message::e_prototype thread::GetMessagePrototype(UINT uiMessage, UINT uiCode); 

      // running and idle processing
      virtual int run();
      virtual void pre_translate_message(signal_details * pobj);
      virtual bool pump_message();     // low level message pump
      virtual bool on_idle(LONG lCount); // return TRUE if more idle processing
      virtual bool is_idle_message(signal_details * pobj);  // checks for special messages
      virtual bool is_idle_message(LPMESSAGE lpmsg);  // checks for special messages
      virtual void message_handler(signal_details * pobj);

      // thread termination
      virtual int exit_instance(); // default will 'delete this'

      // Advanced: exception handling
      virtual void ProcessWndProcException(::exception::base * e, signal_details * pMsg);

      // Advanced: handling messages sent to message filter hook
      virtual void ProcessMessageFilter(int code, signal_details * pobj);

      // Advanced: virtual access to GetMainWnd()
      virtual sp(::user::interaction) GetMainWnd();

   // Implementation
   public:
      virtual ~thread();
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
      void CommonConstruct();
      virtual void Delete();
         // 'delete this' only if m_bAutoDelete == TRUE



      virtual void DispatchThreadMessageEx(signal_details * pobj);  // helper
      virtual void message_queue_message_handler(signal_details * pobj);

      virtual void delete_temp();


      virtual void LockTempMaps();
      virtual bool UnlockTempMaps(bool bDeleteTemp);


		///  \brief		waits for signaling the thread forever
		virtual void wait();

		///  \brief		waits for signaling the thread for a specified time
		///  \param		duration time period to wait for thread
		///  \return	result of waiting action as defined in wait_result
		virtual wait_result wait(const duration & duration);

		///  \brief		sets thread priority
		///  \param		new priority
		void set_priority(int priority);

		///  \brief		gets thread priority
		///  \param		priority
		int priority();


      virtual bool has_message();


      virtual int_ptr item() const;
      */

   };


   //CLASS_DECL_BASE ::thread * get_thread();
//   CLASS_DECL_BASE ::thread_state * get_thread_state();


} // namespace metrowin



