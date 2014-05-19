#pragma once


namespace linux
{


   class CLASS_DECL_LINUX thread :
      virtual public ::thread_impl
   {
   public:


      manual_reset_event m_evFinish;


      thread(sp(::base::application) papp);
      virtual ~thread();


      void CommonConstruct();
      virtual void Delete();


      virtual void construct(__THREADPROC pfnThreadProc, LPVOID pParam);




      virtual void add(sp(::user::interaction) pui);
      virtual void remove(::user::interaction * pui);
      virtual ::count get_ui_count();
      virtual sp(::user::interaction) get_ui(int32_t iIndex);
      virtual void set_timer(sp(::user::interaction) pui, uint_ptr nIDEvent, UINT nEllapse);
      virtual void unset_timer(sp(::user::interaction) pui, uint_ptr nIDEvent);
      virtual void set_auto_delete(bool bAutoDelete = true);
      virtual void set_run(bool bRun = true);
      virtual event & get_finish_event();
      virtual bool get_run();
      virtual sp(::user::interaction) get_active_ui();
      virtual sp(::user::interaction) set_active_ui(sp(::user::interaction) pui);
      virtual void step_timer();


      virtual void defer_process_windows_messages();



      virtual int32_t get_x_window_count() const;




      operator pthread_t() const;


      virtual bool on_run_step();


   };



} // namespace linux




