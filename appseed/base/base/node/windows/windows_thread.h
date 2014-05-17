#pragma once


namespace windows
{


   class CLASS_DECL_BASE thread :
      virtual public ::thread_impl
   {
   public:



      thread(sp(::base::application) papp);
      virtual ~thread();


      virtual void construct(__THREADPROC pfnThreadProc, LPVOID pParam);






      virtual bool begin(int32_t epriority = get_scheduling_priority_normal(), uint_ptr nStackSize = 0, uint32_t dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);







      virtual void start();

      int32_t get_thread_priority();
      bool set_thread_priority(int32_t epriority);

      uint32_t ResumeThread();

      virtual bool pre_init_instance();

      virtual bool on_run_exception(::exception::exception &);

      virtual bool initialize_instance();

      virtual message::e_prototype thread::GetMessagePrototype(UINT uiMessage, UINT uiCode); 

      virtual int32_t run();
      virtual bool pump_message(); 
      virtual bool on_idle(LONG lCount);
      virtual void message_handler(signal_details * pobj);

      virtual int32_t exit_instance(); 

      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
      void CommonConstruct();
      virtual void Delete();



      virtual void dispatch_thread_message(signal_details * pobj); 
      virtual void message_queue_message_handler(signal_details * pobj);



		virtual void wait();

		virtual wait_result wait(const duration & duration);

		void set_priority(int32_t priority);

		int32_t priority();


      virtual bool has_message();


      virtual HANDLE item() const;


   };


   CLASS_DECL_BASE ::thread * get_thread();


} // namespace windows




