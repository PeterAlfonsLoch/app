#include "framework.h"


namespace ca
{


   CLASS_DECL_ca PFN_get_thread g_pfn_get_thread = NULL;
   CLASS_DECL_ca PFN_get_thread_state g_pfn_get_thread_state = NULL;


   thread::thread()
   {

      m_dwAlive                     = ::get_tick_count();
      m_bReady                      = false;
      m_bRun                        = true;
      m_pappDelete                  = NULL;
      m_pbReady                     = NULL;

   }



   thread * get_thread()
   {

      if(g_pfn_get_thread == NULL)
         return NULL;

      return g_pfn_get_thread();

   }


   application * get_thread_app()
   {

      thread * pthread = get_thread();

      if(pthread == NULL)
         return NULL;

      return pthread->get_app();

   }


   thread_state * get_thread_state()
   {
      if(g_pfn_get_thread_state == NULL)
         return NULL;
      return g_pfn_get_thread_state();
   }

   void thread::set_p(::radix::thread * p)
   {
      UNREFERENCED_PARAMETER(p);
      throw interface_only_exception(get_app());
   }

   void thread::construct()
   {
      CommonConstruct();
   }

   void thread::construct(__THREADPROC pfnThreadProc, LPVOID pParam)
   {
      UNREFERENCED_PARAMETER(pfnThreadProc);
      UNREFERENCED_PARAMETER(pParam);
      throw interface_only_exception(get_app());
   }


   void thread::CommonConstruct()
   {
      m_pappDelete      = NULL;
      m_puiMain         = NULL;
      m_pbReady         = NULL;
      m_bReady          = false;
/*      m_ptimera = NULL;
      m_puieptra = NULL;
      GetMainWnd() = NULL;
      m_pActiveWnd = NULL;*/

      // no HTHREAD until it is created
      //      m_hThread = NULL;
      //      m_nThreadID = 0;

      /*      ___THREAD_STATE* pState = __get_thread_state();
      // initialize message pump
      #ifdef DEBUG
      pState->m_nDisablePumpCount = 0;
      #endif
      pState->m_msgCur.message = WM_NULL;
      pState->m_nMsgLast = WM_NULL;
      System.get_cursor_pos(&(pState->m_ptCursorLast));*/

      // most threads are deleted when not needed
/*      m_bAutoDelete = TRUE;
      m_bRun = false;*/

   }

   thread::~thread()
   {
   }


   void * thread::get_os_data() const
   {

      throw interface_only_exception(get_app());

   }


   int_ptr thread::get_os_int() const
   {

      throw interface_only_exception(get_app());

   }


   HTHREAD thread::get_os_handle() const
   {

      return (HTHREAD) get_os_data();

   }


   void thread::start()
   {
      throw interface_only_exception(get_app());
   }


   bool thread::Begin(::ca::e_thread_priority epriority, UINT nStackSize, DWORD dwCreateFlags, LPSECURITY_ATTRIBUTES lpSecurityAttrs)
   {

      UNREFERENCED_PARAMETER(epriority);
      UNREFERENCED_PARAMETER(nStackSize);
      UNREFERENCED_PARAMETER(dwCreateFlags);
      UNREFERENCED_PARAMETER(lpSecurityAttrs);

      throw interface_only_exception(get_app());

   }


   bool thread::create_thread(::ca::e_thread_priority epriority, DWORD dwCreateFlags, UINT nStackSize, LPSECURITY_ATTRIBUTES lpSecurityAttrs)
   {
      UNREFERENCED_PARAMETER(epriority);
      UNREFERENCED_PARAMETER(dwCreateFlags);
      UNREFERENCED_PARAMETER(nStackSize);
      UNREFERENCED_PARAMETER(lpSecurityAttrs);
      throw interface_only_exception(get_app());
   }

   void thread::Delete()
   {
      thread * pthread = this;
      gen::del(pthread);
   }

   /////////////////////////////////////////////////////////////////////////////
   // thread default implementation

   bool thread::PreInitInstance()
   {
      return true;
   }

   bool thread::initialize_instance()
   {
      ASSERT_VALID(this);

      return true;   // by default enter run loop
   }

   bool thread::finalize()
   {
      return true;
   }

   int thread::exit()
   {

      try
      {
         if(!finalize())
         {
            TRACE("There occurred errors durring ::ca::application::finalize virtual member function");
         }
      }
      catch(...)
      {
      }

      return exit_instance();

   }

   // main running routine until thread exits
   int thread::run()
   {
      throw interface_only_exception(get_app());
   }

   bool thread::is_idle_message(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      throw interface_only_exception(get_app());
   }

   int thread::exit_instance()
   {
      throw interface_only_exception(get_app());
   }

   bool thread::on_idle(LONG lCount)
   {
      UNREFERENCED_PARAMETER(lCount);
      throw interface_only_exception(get_app());
   }

   ::gen::message::e_prototype thread::GetMessagePrototype(UINT uiMessage, UINT uiCode)
   {
      UNREFERENCED_PARAMETER(uiMessage);
      UNREFERENCED_PARAMETER(uiCode);
      throw interface_only_exception(get_app());
   }

   void thread::DispatchThreadMessageEx(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      throw interface_only_exception(get_app());
   }

   void thread::pre_translate_message(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void thread::ProcessWndProcException(base_exception* e, gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(e);
      UNREFERENCED_PARAMETER(pobj);
      throw interface_only_exception(get_app());
   }

   void thread::ProcessMessageFilter(int code, gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(code);
      UNREFERENCED_PARAMETER(pobj);
      throw interface_only_exception(get_app());
   }

   /////////////////////////////////////////////////////////////////////////////
   // Access to GetMainWnd() & m_pActiveWnd

   ::user::interaction* thread::GetMainWnd()
   {
      throw interface_only_exception(get_app());
   }

   /////////////////////////////////////////////////////////////////////////////
   // thread implementation helpers

   bool thread::pump_message()
   {
      throw interface_only_exception(get_app());
   }

   /////////////////////////////////////////////////////////////////////////////
   // thread diagnostics

   void thread::assert_valid() const
   {
      throw interface_only_exception(get_app());
   }

   void thread::dump(dump_context & dumpcontext) const
   {
      UNREFERENCED_PARAMETER(dumpcontext);
      throw interface_only_exception(get_app());
   }

   bool thread::post_message(::user::interaction * pguie, UINT uiMessage, WPARAM wparam, LPARAM lparam)
   {
      UNREFERENCED_PARAMETER(pguie);
      UNREFERENCED_PARAMETER(uiMessage);
      UNREFERENCED_PARAMETER(wparam);
      UNREFERENCED_PARAMETER(lparam);
      throw interface_only_exception(get_app());
   }

   bool thread::on_run_exception(::ca::exception & e)
   {

      UNREFERENCED_PARAMETER(e);

      return false;

   }

   ::ca::e_thread_priority thread::get_thread_priority()
   {
      throw interface_only_exception(get_app());
   }

   bool thread::set_thread_priority(::ca::e_thread_priority epriority)
   {
      UNREFERENCED_PARAMETER(epriority);
      throw interface_only_exception(get_app());
   }

   DWORD thread::ResumeThread()
   {
      throw interface_only_exception(get_app());
   }

   DWORD thread::SuspendThread()
   {
      throw interface_only_exception(get_app());
   }

   bool thread::post_thread_message(UINT message, WPARAM wParam, LPARAM lParam)
   {
      UNREFERENCED_PARAMETER(message);
      UNREFERENCED_PARAMETER(wParam);
      UNREFERENCED_PARAMETER(lParam);
      throw interface_only_exception(get_app());
   }

   ::user::interaction * thread::SetMainWnd(::user::interaction * pui)
   {
      UNREFERENCED_PARAMETER(pui);
      throw interface_only_exception(get_app());
   }

   void thread::add(::user::interaction * pui)
   {
      UNREFERENCED_PARAMETER(pui);
      throw interface_only_exception(get_app());
   }

   void thread::remove(::user::interaction * pui)
   {
      UNREFERENCED_PARAMETER(pui);
      throw interface_only_exception(get_app());
   }

   ::count thread::get_ui_count()
   {
      throw interface_only_exception(get_app());
   }

   ::user::interaction * thread::get_ui(index iIndex)
   {
      UNREFERENCED_PARAMETER(iIndex);
      throw interface_only_exception(get_app());
   }

   void thread::set_timer(::user::interaction * pui, uint_ptr nIDEvent, UINT nEllapse)
   {
      UNREFERENCED_PARAMETER(pui);
      UNREFERENCED_PARAMETER(nIDEvent);
      UNREFERENCED_PARAMETER(nEllapse);
      throw interface_only_exception(get_app());
   }

   void thread::unset_timer(::user::interaction * pui, uint_ptr nIDEvent)
   {
      UNREFERENCED_PARAMETER(pui);
      UNREFERENCED_PARAMETER(nIDEvent);
      throw interface_only_exception(get_app());
   }

   void thread::set_auto_delete(bool bAutoDelete)
   {
      UNREFERENCED_PARAMETER(bAutoDelete);
      throw interface_only_exception(get_app());
   }

   void thread::set_run(bool bRun)
   {
      UNREFERENCED_PARAMETER(bRun);
      throw interface_only_exception(get_app());
   }

   event & thread::get_finish_event()
   {
      throw interface_only_exception(get_app());
   }

   bool thread::get_run()
   {
      throw interface_only_exception(get_app());
   }

   ::ca::thread * thread::get_app_thread()
   {
      throw interface_only_exception(get_app());
   }

   ::user::interaction * thread::get_active_ui()
   {
      throw interface_only_exception(get_app());
   }

   ::user::interaction * thread::set_active_ui(::user::interaction * pui)
   {
      UNREFERENCED_PARAMETER(pui);
      throw interface_only_exception(get_app());
   }

   void thread::step_timer()
   {
      throw interface_only_exception(get_app());
   }

   void thread::on_delete(::ca::ca * pui)
   {
      UNREFERENCED_PARAMETER(pui);
   }

   void thread::set_os_data(void * pvoidOsData)
   {
      UNREFERENCED_PARAMETER(pvoidOsData);
      throw interface_only_exception(get_app());
   }

   void thread::set_os_int(int_ptr iData)
   {
      UNREFERENCED_PARAMETER(iData);
      throw interface_only_exception(get_app());
   }


   int thread::main()
   {
      return 0;
   }

   void thread::on_keep_alive()
   {
      m_dwAlive = ::get_tick_count();
   }

   bool thread::is_alive()
   {
      if(!m_bRun)
         return false;
      if((::get_tick_count() - m_dwAlive) > ((1984 + 1977) * 91))
         return false;
      return true;
   }

   bool thread::has_message()
   {
      return false;
   }

   bool thread::verb()
   {
      return true;
   }

   bool thread::is_auto_delete()
   {
      throw not_implemented(get_app());
   }

	void thread::wait()
	{
      throw not_implemented(get_app());
      // on Windows ==>       ::WaitForSingleObject(m_loginthread.get_os_data(), INFINITE);

   }

	///  \brief		waits for signaling the thread for a specified time
	///  \param		duration time period to wait for thread
	///  \return	result of waiting action as defined in wait_result
   wait_result thread::wait(const duration & duration)
	{
      UNREFERENCED_PARAMETER(duration);
		throw not_implemented(get_app());
		return wait_result();
	}

	///  \brief		sets thread priority
	///  \param		new priority
	void thread::set_priority(int priority)
	{
      UNREFERENCED_PARAMETER(priority);
      throw not_implemented(get_app());
   }

	///  \brief		gets thread priority
	///  \param		priority
	int thread::priority()
	{
      throw not_implemented(get_app());
      return 0x80000000;
   }


} // namespace ca


namespace user
{


   LRESULT message::send()
   {
      return m_pguie->send_message(m_uiMessage, m_wparam, m_lparam);
   }

   UINT message::ThreadProcSendMessage(LPVOID lp)
   {
      message * pmessage = (message *) lp;
      pmessage->send();
      delete pmessage;
      return 0;
   }

   void message::post(::user::interaction * puie, UINT uiMessage, WPARAM wparam, LPARAM lparam, ::ca::e_thread_priority epriority)
   {
      message * pmessage = new message;
      pmessage->m_pguie = puie;
      pmessage->m_uiMessage = uiMessage;
      pmessage->m_wparam = wparam;
      pmessage->m_lparam = lparam;
      __begin_thread(puie->get_app(), &ThreadProcSendMessage, pmessage, epriority);
   }


} // namespace win


