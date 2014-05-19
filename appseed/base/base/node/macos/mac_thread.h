#pragma once


WINBOOL AfxInternalPreTranslateMessage(MESSAGE* pMsg);


namespace mac
{

   
   struct thread_startup
   {
      
      
      ::thread *           m_pthread;    // thread for new thread
      event                hEvent;          // event triggered after success/non-success
      event                hEvent2;         // event triggered after thread is resumed
      
      
      thread_startup();
      ~thread_startup();
      
      
   };
   
   
   class CLASS_DECL_mac thread :
      virtual public ::thread_impl
   {
   public:
      
      ::event                              m_evFinish;
      
      
      thread(::base::application * papp);
      virtual ~thread();
      
      
      void CommonConstruct();
      virtual void Delete();
      
      
      virtual void construct(__THREADPROC pfnThreadProc, LPVOID pParam);
      
      
#ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
#endif
      
      
      virtual void add(sp(::user::interaction)  pui);
      virtual void remove(::user::interaction *  pui);
      virtual ::count get_ui_count();
      virtual sp(::user::interaction)  get_ui(int32_t iIndex);
      virtual void set_timer(sp(::user::interaction)  pui, uint_ptr nIDEvent, UINT nEllapse);
      virtual void unset_timer(sp(::user::interaction)  pui, uint_ptr nIDEvent);
      virtual void set_auto_delete(bool bAutoDelete = true);
      virtual void set_run(bool bRun = true);
      virtual event & get_finish_event();
      virtual bool get_run();
      virtual sp(::user::interaction) get_active_ui();
      virtual sp(::user::interaction) set_active_ui(sp(::user::interaction) pui);
      virtual void step_timer();
      virtual bool on_run_step();
      
      
      int32_t get_thread_priority();
      bool set_thread_priority(int32_t epriority);
      
      DWORD SuspendThread();
      DWORD ResumeThread();
      
      
      operator pthread_t() const;
      
      
   };
   
   
   CLASS_DECL_mac ::thread * get_thread();
   
   
} // namespace mac



