#pragma once


bool __internal_pre_translate_message(MSG* pMsg);




namespace windows
{


   class CLASS_DECL_BASE thread :
      virtual public ::thread,
      virtual public message_queue
   {
   public:



      static comparable_array < HANDLE > * s_phaThread;
      static comparable_array < thread * > * s_pthreadptra;
      static mutex * s_pmutex;


      // list of frame_window objects for thread
      list < sp(::user::frame_window) >   m_frameList;



      bool                                   m_bCreatingMessageWindow;
      LPVOID                              m_pThreadParams; // generic parameters passed to starting function
      __THREADPROC                      m_pfnThreadProc;

      event                              m_evFinish;
      UINT                                m_nDisablePumpCount;
      mutex                               m_mutexUiPtra;
      
      UINT                                m_dwFinishTimeout;


      thread(sp(::base::application) papp);
      virtual ~thread();


      virtual void construct(__THREADPROC pfnThreadProc, LPVOID pParam);



      virtual void * get_os_data() const;
      virtual int_ptr get_os_int() const;


      operator HANDLE() const;


      void set_os_data(void * pvoidOsData);
      void set_os_int(int_ptr iData);

      virtual bool begin(int32_t epriority = get_scheduling_priority_normal(), uint_ptr nStackSize = 0, uint32_t dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);

      bool create_thread(int32_t epriority = get_scheduling_priority_normal(), uint32_t dwCreateFlags = 0, uint_ptr nStackSize = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL) override;


      virtual sp(::user::interaction) SetMainWnd(sp(::user::interaction) pui);

      virtual int32_t thread_entry(::thread_startup * pstartup);
      virtual int32_t main();
      virtual int32_t thread_term(int32_t nResult);


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
      virtual sp(::user::interaction) get_active_ui();
      virtual sp(::user::interaction) set_active_ui(sp(::user::interaction) pui);
      virtual void step_timer();


/**
* \file		src/lib/pal/linux/thread_linux.hpp
* \brief	Platform independent threads and synchronization objects (linux version)
*/

      virtual void start();

      int32_t get_thread_priority();
      bool set_thread_priority(int32_t epriority);

   // Operations
      //DWORD SuspendThread();
      uint32_t ResumeThread();
      bool post_thread_message(UINT message, WPARAM wParam = 0, lparam lParam = NULL);
      bool post_message(sp(::user::interaction) pui, UINT message, WPARAM wParam = 0, lparam lParam = NULL);

      virtual bool pre_init_instance();

      // called when occurs an standard_exception exception in run
      // return true to call run again
      virtual bool on_run_exception(::exception::exception &);

   // Overridables
      // thread initialization
      virtual bool initialize_instance();

      virtual message::e_prototype thread::GetMessagePrototype(UINT uiMessage, UINT uiCode); 

      // running and idle processing
      virtual int32_t run();
      virtual bool pump_message(); 
      virtual bool on_idle(LONG lCount);
      virtual void message_handler(signal_details * pobj);

      // thread termination
      virtual int32_t exit_instance(); // default will 'delete this'

      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
      void CommonConstruct();
      virtual void Delete();



      virtual void dispatch_thread_message(signal_details * pobj);  // helper
      virtual void message_queue_message_handler(signal_details * pobj);



		///  \brief		waits for signaling the thread forever
		virtual void wait();

		///  \brief		waits for signaling the thread for a specified time
		///  \param		duration time period to wait for thread
		///  \return	result of waiting action as defined in wait_result
		virtual wait_result wait(const duration & duration);

		///  \brief		sets thread priority
		///  \param		new priority
		void set_priority(int32_t priority);

		///  \brief		gets thread priority
		///  \param		priority
		int32_t priority();


      virtual bool has_message();


      virtual HANDLE item() const;

      void _001PostCreateMessageWindow();
      DECL_GEN_SIGNAL(_001OnCreateMessageWindow);

   };


   CLASS_DECL_BASE ::thread * get_thread();


} // namespace windows




