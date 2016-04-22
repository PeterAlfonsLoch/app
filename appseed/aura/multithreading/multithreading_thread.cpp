#include "framework.h"



struct send_thread_message :
   virtual public object
{

   MESSAGE     m_message;

   bool        m_bOk;

   send_thread_message();
   virtual ~send_thread_message();

};

send_thread_message::send_thread_message()
{

   ZERO(m_message);

   m_bOk = false;

}


send_thread_message::~send_thread_message()
{


}



bool thread::s_bAllocReady = false;

thread::file_info::file_info()
{
   m_durationFileSharingViolationTimeout = seconds(1984);
}

thread::file_info::~file_info()
{
}


thread::file_info * thread::get_file_info()
{

   if(m_pfileinfo != NULL)
      return m_pfileinfo;

   m_pfileinfo = new file_info();

   return m_pfileinfo;

}

DWORD thread::get_file_sharing_violation_timeout_total_milliseconds()
{

   return (DWORD) get_file_info()->m_durationFileSharingViolationTimeout.get_total_milliseconds();

}

::duration thread::set_file_sharing_violation_timeout(::duration duration)
{

   return get_file_info()->m_durationFileSharingViolationTimeout = duration;

}


thread::thread() :
   ::object(::get_thread_app()),
   m_mutexUiPtra(::get_thread_app())
{

   construct();

   m_puiptra = NULL;



}




thread::thread(::aura::application * papp) :
   object(papp),
   m_mutexUiPtra(papp)
{

   construct();


   if(m_pauraapp != NULL && m_pauraapp->m_paurasession != NULL)
   {

      m_bZipIsDir = m_pauraapp->m_paurasession->m_bZipIsDir;

   }

}


thread::thread(::aura::application * papp, __THREADPROC pfnThreadProc, LPVOID pParam) :
   object(papp),
   m_mutexUiPtra(papp)
{

   //CommonConstruct();

//   m_pthreadimpl.alloc(allocer());
//   m_pthreadimpl->m_pthread = this;
   construct(pfnThreadProc, pParam);

   if(m_pauraapp != NULL && m_pauraapp->m_paurasession != NULL)
   {

      m_bZipIsDir = m_pauraapp->m_paurasession->m_bZipIsDir;

   }

}


void thread::CommonConstruct()
{

   //m_durationRunLock = ::duration::infinite();

   m_dwAlive = ::get_tick_count();

   if (m_pmutex == NULL)
   {
      m_pmutex = new mutex();
   }
   else
   {
      output_debug_string("tst");
   }

   //m_peventEvent = NULL;

   m_bReady = false;
   m_bRun = true;
   m_pevReady = NULL;

   m_puiActive = NULL;
   m_puiMain = NULL;

   m_iReturnCode = 0;

   m_bZipIsDir = true;

   m_pslUser = NULL;

//   m_preplacethread = NULL;

   m_bAutoDelete = true;

   m_pfileinfo = NULL;

#ifndef WINDOWSEX

   m_mq = NULL;

#endif

   m_bDupHandle = false;

   m_hthread = (HTHREAD) NULL;
   m_uiThread = 0;

   m_pThreadParams = NULL;
   m_pfnThreadProc = NULL;

   m_nDisablePumpCount  = 0;

   m_pcommandthread = NULL;

   //m_hthread = NULL;



}



thread::~thread()
{

   //try
   //{

   //   single_lock sl(&m_mutexUiPtra, TRUE);

   //   if (m_spuiptra.is_set())
   //   {

   //      while (m_spuiptra->has_elements())
   //      {

   //         remove(m_spuiptra->element_at(0));

   //      }

   //      m_spuiptra.release();

   //   }

   //}
   //catch (...)
   //{

   //}

   ::aura::del(m_pfileinfo);

}









HTHREAD thread::get_os_handle() const
{

   return (HTHREAD)get_os_data();

}



//void thread::_001OnSendThreadMessage(signal_details * pobj)
//{
//
//   SCAST_PTR(::message::base,pbase,pobj);
//
//   sp(::send_thread_message) pmessage = pbase->m_lparam;
//
//   process_message(&pmessage->m_message);
//
//   pmessage->m_bOk = true;
//
//}








bool thread::finalize()
{

   return true;

}


int32_t thread::exit()
{

   signal_close_dependent_threads();

   wait_close_dependent_threads(minutes(1));


   try
   {

      if (!finalize())
      {

         TRACE("There occurred errors durring application::finalize virtual member function");

      }

   }
   catch (...)
   {

   }

   return exit_instance();

}


bool thread::send_thread_message(UINT message,WPARAM wParam,lparam lParam, ::duration durWaitStep)
{

   sp(::send_thread_message) pmessage =  canew(::send_thread_message);



   pmessage->m_message.message = message;
   pmessage->m_message.wParam = wParam;
   pmessage->m_message.lParam = lParam;
   pmessage->m_bOk = false;

   post_thread_message(message_system,system_message_meta, (LPARAM) (uint_ptr) (object *) pmessage.m_p);

   while(defer_pump_message())
   {

      if(pmessage->m_bOk)
      {

         break;

      }

      Sleep(durWaitStep);

      if(pmessage->m_bOk)
      {

         break;

      }

   }

   return true;

}



void thread::on_keep_alive()
{

   m_dwAlive = ::get_tick_count();

}


bool thread::is_alive()
{

   //if (!m_bRun)
   //   return false;

   //if ((::get_tick_count() - m_dwAlive) > ((5000) * 91))
     // return false;

   return true;

}



bool thread::is_auto_delete()
{

   return m_bAutoDelete;

}




CLASS_DECL_AURA void thread_alloc_ready(bool bReady)
{

   thread::s_bAllocReady = bReady;

}



bool thread::pre_run()
{

   register_at_required_threads();

   return true;

}

int32_t thread::run()
{

   ASSERT_VALID(this);

   //m_bIdle = TRUE;

   //m_lIdleCount = 0;

   //sync_object_ptra soa;

   //if(m_peventEvent == NULL)
   //{

   //   m_peventEvent = new manual_reset_event(get_app());

   //}

   //soa.add(m_peventEvent);

   //defer_add_thread_run_wait(soa);

   //multi_lock ml(soa);

   ::output_debug_string("::thread::run " + string(demangle(typeid(*this).name())) + " m_bRun = "+::str::from((int)m_bRun)+"\n\n");


   while(true)
   {

      //if(m_spuiptra.is_set() && m_spuiptra->get_count() > 0)
      //{

      //      ml.lock(millis(25),false,QS_ALLEVENTS);

      //}
      //else
      //{

      //      ml.lock(m_durationRunLock,false,QS_ALLEVENTS);

      //}

      if(!defer_pump_message())
      {

         break;

      }


   }

   ::output_debug_string("::thread::run Exiting " + string(demangle(typeid(*this).name())) + " m_bRun = "+::str::from((int)m_bRun)+" m_iReturnCode = "+::str::from(m_iReturnCode)+"\n\n");

   return m_iReturnCode;

}



bool thread::pump_message()
{

   try
   {

      MESSAGE msg;

      if(::GetMessage(&msg,NULL,0,0) == 0)
      {

         TRACE(::aura::trace::category_AppMsg,1,"thread::pump_message - Received WM_QUIT.\n");

         ::output_debug_string("thread::pump_message - Received WM_QUIT.\n");

         m_nDisablePumpCount++; // application must die
         // Note: prevents calling message loop things in 'exit_instance'
         // will never be decremented
         return false;

      }

      process_message(&msg);

      return true;

   }
   catch(exit_exception & e)
   {

      throw e;

   }
   catch(const ::exception::exception & e)
   {

      if(on_run_exception((::exception::exception &) e))
         return true;

      // get_app() may be it self, it is ok...
      if(App(get_app()).final_handle_exception((::exception::exception &) e))
         return true;

      return false;

   }
   catch(...)
   {

      return false;

   }

//   if(m_pthreadimpl.is_null())
//   {
//      if(dynamic_cast <::timer *> ((thread *) this) != NULL)
//      {
//         m_pthreadimpl.alloc(allocer());
//         if(m_pthreadimpl.is_null())
//         {
//            return false;
//         }
//         m_pthreadimpl->m_pthread = this;
//      }
//      else
//      {
//         return false;
//      }
//   }
//
//   return m_pthreadimpl->pump_message();

}

bool thread::defer_pump_message()
{

   MESSAGE msg = {};

   //while(::PeekMessage(&msg,NULL,0,0,PM_NOREMOVE) != FALSE)
   {

      // pump message, but quit on WM_QUIT
     // if(!m_bRun || !pump_message())
      if (!pump_message())
      {


         ::output_debug_string("\n\n\nthread::defer_pump_message (1) quitting (WM_QUIT? {PeekMessage->message : "+::str::from(msg.message == WM_QUIT?1:0)+"!}) : " + string(demangle(typeid(*this).name())) + " ("+::str::from((uint64_t)::GetCurrentThreadId())+")\n\n\n");

         return false;

      }

   }

   // reset "no idle" state after pumping "normal" message
   //if (is_idle_message(&m_msgCur))
//   if(is_idle_message(&msg))
//   {
//
//      //m_bIdle = true;
//
//      //m_lIdleCount = 0;
//
//   }

   //if(!on_run_step())
   //{

   //   ::output_debug_string("defer_pump_message (2) quitting : " + string(demangle(typeid(*this).name())) + "\n\n");

   //   return false;

   //}


   //on_idle(0);

   return true;

}


bool thread::on_thread_on_idle(thread *pimpl, LONG lCount)
{
   return true;
}



void thread::set_auto_delete(bool bAutoDelete)
{

   m_bAutoDelete = bAutoDelete;

}


void thread::set_run(bool bRun)
{

   m_bRun = bRun;

}



bool thread::get_run()
{

   return m_bRun;

}




::user::primitive * thread::get_active_ui()
{

   return m_puiActive;

}


::user::primitive * thread::set_active_ui(::user::primitive * pui)
{

   return m_puiActive = pui;

}


//void thread::step_timer()
//{
//
//   if (m_pthreadimpl.is_null())
//      return;
//
//   return m_pthreadimpl->step_timer();
//
//}

//
//bool thread::on_run_step()
//{
//
//
//   //step_timer();
//
//   sp(::aura::application) papp = (this);
//
//   m_dwAlive = ::get_tick_count();
//
//   if (papp != NULL)
//   {
//
//      papp->m_dwAlive = m_dwAlive;
//
//   }
//
//   sp(::aura::application) pappP = (this);
//
//   if (pappP != NULL)
//   {
//
//      pappP->m_dwAlive = m_dwAlive;
//
//   }
//
//   //try
//   //{
//
//   //   if (!verb())
//   //      return false;
//
//   //}
//   //catch (::exit_exception & e)
//   //{
//
//   //   throw e;
//
//   //}
//   //catch (::exception::exception & e)
//   //{
//
//   //   if (!Application.on_run_exception(e))
//   //      throw exit_exception(get_app());
//
//   //}
//   //catch (...)
//   //{
//
//   //}
//
//   return true;
//
//}
//



void thread::Delete()
{


   release();

}

void thread::register_dependent_thread(::thread * pthreadDependent)
{

   //post_thread_message(message_system, 90, (LPARAM) pthreadDependent);
   on_register_dependent_thread(pthreadDependent);

}

void thread::unregister_dependent_thread(::thread * pthreadDependent)
{

   //post_thread_message(message_system, 91, (LPARAM)pthreadDependent);
   on_unregister_dependent_thread(pthreadDependent);

}

void thread::on_register_dependent_thread(::thread * pthreadDependent)
{

   if(pthreadDependent == this)
      return;

   {

      synch_lock slThread(pthreadDependent->m_pmutex);

      pthreadDependent->m_threadptraRequired.add_unique(this);

   }

   {

      synch_lock sl(m_pmutex);

      m_threadptraDependent.add_unique(pthreadDependent);

   }


}


void thread::on_unregister_dependent_thread(::thread * pthreadDependent)
{

   {

      synch_lock sl(m_pmutex);

      m_threadptraDependent.remove(pthreadDependent);

   }

   {

      synch_lock slThread(pthreadDependent->m_pmutex);

      pthreadDependent->m_threadptraRequired.remove(this);

   }
   // the system may do some extra processing (like quitting system in case pthreadDependent is the last thread virgin in America (North, most especifically US) ?!?!), so do a kick
   // (do not apply virgin to your self...)
   post_thread_message(WM_NULL);

}


void thread::signal_close_dependent_threads()
{

   synch_lock sl(m_pmutex);

   thread * pthread;

   for(index i = m_threadptraDependent.get_upper_bound(); i >= 0;)
   {

      pthread = NULL;

      try
      {

         pthread = m_threadptraDependent[i];

      }
      catch (...)
      {

         m_threadptraDependent.remove_at(i);

         continue;

      }

      sl.unlock();

      try
      {

         synch_lock slThread(pthread->m_pmutex);

         pthread->set_end_thread();

         i--;

      }
      catch(...)
      {

      }

      sl.lock();

   }

}


void thread::wait_close_dependent_threads(const duration & duration)
{

   DWORD dwStart = ::get_tick_count();

   while(::get_tick_count() - dwStart < duration.get_total_milliseconds())
   {

      {

         synch_lock sl(m_pmutex);

         if(m_threadptraDependent.get_count() <= 0)
            break;

         for(index i = 0; i < m_threadptraDependent.get_count(); i++)
         {

            ::thread * pthread = m_threadptraDependent[i];
            output_debug_string(string("---"));
            output_debug_string(string("supporter : ") + typeid(*this).name() + string(" (") + ::str::from((int_ptr) this) + ")");
            output_debug_string(string("dependent : ") + typeid(*m_threadptraDependent[i]).name() + string(" (") + ::str::from((int_ptr) m_threadptraDependent[i]) + ")");

         }

      }

      Sleep(284);

   }

}

void thread::register_at_required_threads()
{

   if(is_system())
      return;

   // register default dependencies

   if(&System != NULL)
   {

      System.register_dependent_thread(this);

   }

   if(&Session != NULL)
   {

      Session.register_dependent_thread(this);

   }

   if(&Application != NULL)
   {

      Application.register_dependent_thread(this);

   }



}



void thread::unregister_from_required_threads()
{

   synch_lock sl(m_pmutex);

   for(index i = m_threadptraRequired.get_upper_bound(); i >= 0;)
   {

      try
      {

         ::thread * pthread = m_threadptraRequired[i];

         if (pthread != this)
         {

            synch_lock slThread(pthread->m_pmutex);

            pthread->unregister_dependent_thread(this);

         }

      }
      catch(...)
      {

      }

      i--;

      sl.unlock();

      sl.lock();

   }

}



void thread::do_events(const duration & duration)
{

   DWORD dwEnd = (DWORD) (::get_tick_count() + duration.get_total_milliseconds());

   do
   {

      do_events();

   } while(::get_tick_count() < dwEnd);

}


void thread::set_run_thread(bool bRun)
{

   if(bRun)
   {

      m_bRun = true;

   }
   else
   {

      //m_durationRunLock = millis(7);

      //if(m_peventEvent != NULL)
      //{

      //   m_peventEvent->SetEvent();

      //}

      m_bRun = false;

      post_quit();


   }

}

void thread::set_end_thread()
{

   set_run_thread(false);

}


//void thread::defer_add_thread_run_wait(sync_object_ptra & soa)
//{
//
//    UNREFERENCED_PARAMETER(soa);
//
//}


void thread::message_queue_message_handler(::signal_details * pobj)
{

    UNREFERENCED_PARAMETER(pobj);

}


// if you do not want to allow shutdown, return false
// it is a good practice to prompt for an question related to shutdown or at least a excuse, or even a exception,
// otherwise, shutdown command will be silently ignored
// you can call this function if you will shutdown in other way, for example IDEE (casey) ::ExitProcess for Microsoft (TM) Corporation Windows (TM)
// besides thread(task) base defined, can be overriden, in application/session/system/platform
bool thread::on_before_shutdown()
{

   return true;

}

void thread::shutdown(bool bPrompt)
{

   if(bPrompt)
   {

      if(!on_before_shutdown())
      {

         return;

      }

   }

   post_quit(); // post implies switching to context.


}


void thread::delete_this()
{

   try
   {

      if(get_os_handle() != NULL)
      {

         m_bAutoDelete = true;

         post_quit();

      }
      else
      {

         ::command_target::delete_this();

      }

   }
   catch(...)
   {


   }

}

void thread::post_quit()
{

   try
   {

      set_run(false);

      // post to ensure that quiting is done at the task and for the task and not in this fiber/thread/task
      post_thread_message(WM_QUIT);

   }
   catch(...)
   {


   }

}


bool thread::is_application()
{

   return false;

}


bool thread::is_session()
{

   return false;

}


bool thread::is_system()
{

   return false;

}





uint32_t __thread_entry(void * pparam);

void thread::construct()
{

   CommonConstruct();

}



void thread::construct(__THREADPROC pfnThreadProc, LPVOID pParam)
{

   CommonConstruct();

   m_pfnThreadProc = pfnThreadProc;
   m_pThreadParams = pParam;

}





bool thread::pre_init_instance()
{

   return true;

}


bool thread::initialize_instance()
{

   return true;

}

void thread::dispatch_thread_message(signal_details * pbase)
{


   //LRESULT lresult;

   synch_lock sl(m_pmutex);
   int i = 0;
   Signal * pSignal;
   while((pSignal = m_signala.GetSignal(pbase->m_uiMessage,0,0, i)) != NULL)
   {
      class signal * psignal = pSignal->m_psignal;
      message::e_prototype eprototype = pSignal->m_eprototype;
      if(eprototype == message::PrototypeNone)
      {
         //::message::base aura(get_app());
         pbase->m_psignal = psignal;
         //lresult = 0;
         //aura.set(pmsg->message, pmsg->wParam, pmsg->lParam, lresult);
         psignal->emit(pbase);
         if(pbase->m_bRet)
            return;
      }
      break;
      pbase->m_bRet = true;
   }


}


void thread::wait()
{

#if defined(WINDOWS)

   ::WaitForSingleObject(m_hthread, INFINITE);

#endif

}

wait_result thread::wait(const duration & duration)
{

#if defined(WINDOWS)

   DWORD timeout = duration.is_pos_infinity() ? INFINITE : static_cast<DWORD>(duration.total_milliseconds());
   return wait_result((uint32_t) ::WaitForSingleObject(m_hthread, timeout));

#else

   return wait_result(::wait_result::Failure);

#endif

}


void thread::pre_translate_message(signal_details * pobj)
{

   try
   {
      SCAST_PTR(::message::base,pbase,pobj);

      //   ASSERT_VALID(this);

      // if this is a thread-message, int16_t-circuit this function
      if(pbase->m_pwnd == NULL)
      {
         dispatch_thread_message(pobj);
         if(pobj->m_bRet)
            return;
      }

//      ::user::primitive * puiTopic = pbase->m_pwnd;

      try
      {
         if(m_pauraapp->m_paurasession != NULL)
         {

            m_pauraapp->m_paurasession->frame_pre_translate_message(pobj);
         }
      }
      catch(exit_exception & e)
      {
         throw e;
      }
      catch(...)
      {
      }
   }
   catch(exit_exception & e)
   {
      throw e;
   }
   catch(...)
   {
   }

}







void thread::process_window_procedure_exception(::exception::base*,signal_details * pobj)
{
   SCAST_PTR(::message::base,pbase,pobj);
   if(pbase->m_uiMessage == WM_CREATE)
   {
      pbase->set_lresult(-1);
      return;  // just fail
   }
   else if(pbase->m_uiMessage == WM_PAINT)
   {
      // force validation of interaction_impl to prevent getting WM_PAINT again
      #ifdef WIDOWSEX
      ValidateRect(pbase->m_pwnd->get_safe_handle(),NULL);
      #endif
      pbase->set_lresult(0);
      return;
   }
   return;   // sensible default for rest of commands
}


namespace thread_util
{

   inline bool IsEnterKey(signal_details * pobj)
   {
      SCAST_PTR(::message::base,pbase,pobj);
      return pbase->m_uiMessage == WM_KEYDOWN && pbase->m_wparam == VK_RETURN;
   }

   inline bool IsButtonUp(signal_details * pobj)
   {
      SCAST_PTR(::message::base,pbase,pobj);
      return pbase->m_uiMessage == WM_LBUTTONUP;
   }

}

void thread::process_message_filter(int32_t code,signal_details * pobj)
{

   Application.process_message_filter(code,pobj);

}





thread_startup::thread_startup(::aura::application * papp) :
   object(papp),
   m_event(papp),
   m_event2(papp)
{

   m_iError = 0;
   m_bSynch = false;


}


thread_startup::~thread_startup()
{

}




bool thread::begin_thread(bool bSynch,int32_t * piStartupError,int32_t epriority,uint_ptr nStackSize,uint32_t dwCreateFlagsParam,LPSECURITY_ATTRIBUTES lpSecurityAttrs)
{

   DWORD dwCreateFlags = dwCreateFlagsParam;

   ENSURE(m_hthread == (HTHREAD) NULL);

   sp(::thread_startup) pstartup = canew(::thread_startup(get_app()));

   pstartup->m_bError = FALSE;

   pstartup->m_bSynch = bSynch;

   pstartup->m_pthread = this;

   pstartup->m_dwCreateFlags = dwCreateFlags;

   pstartup->m_event2.ResetEvent();

   m_hthread = (HTHREAD)(uint_ptr) ::create_thread(lpSecurityAttrs,nStackSize,&__thread_entry,pstartup.m_p,dwCreateFlags,&m_uiThread);

   if(m_hthread == (HTHREAD) NULL)
   {
      try
      {

         if(piStartupError != NULL)
            *piStartupError = pstartup->m_iError;
      }
      catch(...)
      {
      }
      return false;
   }


   pstartup->m_event2.SetEvent();

   pstartup->m_event.wait();

   if(pstartup->m_bError)
   {
      try
      {

         if(piStartupError != NULL)
            *piStartupError = pstartup->m_iError;
      }
      catch(...)
      {
      }
      return false;
   }

   pstartup->m_event2.SetEvent();

   set_thread_priority(epriority);

   return true;

}

bool thread::create_thread(int32_t epriority,uint_ptr nStackSize,uint32_t dwCreateFlags,LPSECURITY_ATTRIBUTES lpSecurityAttrs)
{

   return begin_thread(false,NULL,epriority,nStackSize, dwCreateFlags,lpSecurityAttrs);

}

bool thread::create_thread_synch(int32_t * piStartupError,int32_t epriority,uint_ptr nStackSize,uint32_t dwCreateFlags,LPSECURITY_ATTRIBUTES lpSecurityAttrs)
{

   return begin_thread(true,piStartupError,epriority,nStackSize, dwCreateFlags,lpSecurityAttrs);

}


bool thread::begin(int32_t epriority,uint_ptr nStackSize,uint32_t dwCreateFlags,LPSECURITY_ATTRIBUTES lpSecurityAttrs)
{

   if(!create_thread(epriority,nStackSize,dwCreateFlags, lpSecurityAttrs))
   {
      return false;
   }

   return true;

}

bool thread::begin_synch(int32_t * piStartupError,int32_t epriority,uint_ptr nStackSize,uint32_t dwCreateFlags,LPSECURITY_ATTRIBUTES lpSecurityAttrs)
{

   if(!create_thread_synch(piStartupError, epriority,nStackSize, dwCreateFlags,lpSecurityAttrs))
   {
      return false;
   }

   return true;

}

void * thread::get_os_data() const
{

   return (void *)m_hthread;

}


IDTHREAD thread::get_os_int() const
{

   return  m_uiThread;

}


int_ptr thread::item() const
{

   return (int_ptr)m_hthread;

}


uint32_t __thread_entry(void * pparam)
{

   UINT uiRet = 0;

   try
   {

      sp(::thread_startup) pstartup = (::thread_startup *) pparam;

      ASSERT(pstartup != NULL);
      ASSERT(pstartup->m_pthread != NULL);
      //ASSERT(pstartup->m_pthreadimpl != NULL);
      ASSERT(!pstartup->m_bError);

      ::thread * pthread = pstartup->m_pthread;

//      ::thread * pthreadimpl = pstartup->m_pthreadimpl;

      try
      {

         __node_init_thread(pthread);

      }
      catch(...)
      {

         pstartup->m_event2.wait();

         pstartup->m_event2.ResetEvent();

         pstartup->m_bError = TRUE;

         pstartup->m_event.set_event();

         return ::multithreading::__on_thread_finally(pthread);

      }

      pstartup->m_event2.wait();

      pstartup->m_event2.ResetEvent();

      try
      {

         ::multithreading::__node_on_init_thread(pthread);

      }
      catch(...)
      {

         pstartup->m_bError = TRUE;

         pstartup->m_event.set_event();

         return ::multithreading::__on_thread_finally(pthread);

      }

      try
      {

         pthread->thread_startup(pstartup);

      }
      catch(...)
      {

         pstartup->m_bError = true;

      }

      if(pstartup->m_bError)
      {

         pstartup->m_bError = TRUE;

         if(pstartup->m_iError == 0)
         {
            pstartup->m_iError = -1;
         }

         pstartup->m_event.set_event();

         return ::multithreading::__on_thread_finally(pthread);

      }

      bool bSynch = pstartup->m_bSynch;

      if(!bSynch)
      {

         // allow the creating thread to return from thread::create_thread
         pstartup->m_event.set_event();

         // wait for thread to be resumed
         pstartup->m_event2.wait();

         pstartup.release();

      }

      bool bError = false;

      try
      {

         if(!pthread->thread_entry())
         {

            bError = true;

         }

      }
      catch(::exit_exception &)
      {

         bError = true;

      }


      if(bError)
      {

         if(bSynch)
         {

            pstartup->m_iError = pthread->m_iReturnCode;

            pstartup->m_bError = true;

            pstartup->m_event.set_event();

            return ::multithreading::__on_thread_finally(pthread);

         }
         else
         {

            return ::multithreading::__on_thread_finally(pthread);

         }

      }

      if(bSynch)
      {

         // allow the creating thread to return from thread::create_thread
         pstartup->m_event.set_event();

         // wait for thread to be resumed
         pstartup->m_event2.wait();

         pstartup.release();

      }

      //if(pthread->m_preplacethread != NULL && !pthread->m_preplacethread->do_replace(pthread))
      //{

      //   try
      //   {

      //      pthread->m_preplacethread = NULL;

      //   }
      //   catch(...)
      //   {

      //   }

      //   try
      //   {

      //      pthread->exit();

      //   }
      //   catch(...)
      //   {

      //   }

      //   return ::multithreading::__on_thread_finally(pthread);

      //}


      try
      {

                               pthread->main();

      }
      catch(::exit_exception &)
      {

         Sys(pthread->m_pauraapp).post_quit();

         return ::multithreading::__on_thread_finally(pthread);

      }

      return ::multithreading::__on_thread_finally(pthread);

   }
   catch(...)
   {

      ASSERT(FALSE);

      return -1;

   }

   return uiRet;

}


void CLASS_DECL_AURA __end_thread(::aura::application * papp)
{

   __term_thread(papp);

}


void CLASS_DECL_AURA __term_thread(::aura::application * papp)
{

   UNREFERENCED_PARAMETER(papp);

}



bool thread::is_idle_message(signal_details * pobj)
{

   return ::message::is_idle_message(pobj);

}

bool thread::is_idle_message(LPMESSAGE lpmsg)
{

   return ::message::is_idle_message(lpmsg);

}



void thread::post_to_all_threads(UINT message,WPARAM wparam,LPARAM lparam)
{

   //::count ca;

   thread * pthread;

   //ca = ::multithreading::s_pthreadptra->get_size();

   //bool bOk;

   if(message == WM_QUIT)
   {

      single_lock sl(::multithreading::s_pmutex,true);
      ptr_array < thread > threadptra = *::multithreading::s_pthreadptra;

      for(index i = 0; i < threadptra.get_size(); i++)
      {

         try
         {
            pthread = dynamic_cast < thread * >(threadptra[i]);
            pthread->set_end_thread();
         }
         catch(...)
         {
         }


      }
      sl.unlock();

   }


   single_lock sl(::multithreading::s_pmutex);

   for(index i = ::multithreading::s_piaThread->get_size(); i >= 0; i--)
   {

      //bOk = true;

      try
      {

         if(::PostThreadMessage((IDTHREAD) ::multithreading::s_piaThread->element_at(i),message,wparam,lparam))
         {

         }

      }
      catch(...)
      {

         //bOk = false;

      }

      sl.lock();


   }

}


int32_t thread::exit_instance()
{

   ASSERT_VALID(this);

   //try
   //{

   //   single_lock sl(&m_mutexUiPtra,TRUE);

//      if(m_spuiptra.is_set())
//      {
//
//         sp(ptr_array < ::user::primitive >) puiptra = m_spuiptra;
//
//         m_spuiptra.release();
//
//  //       for(int32_t i = 0; i < puiptra->get_size(); i++)
//    //     {
//
////            ::user::primitive * pui = puiptra->element_at(i);
//
//      //   }
//
//         puiptra.release();
//
//         sl.unlock();
//
//      }
//   }
//   catch(...)
//   {
//   }

   //try
   //{

   //   m_sptimera.release();

   //}
   //catch(...)
   //{
   //}


   return m_iReturnCode;

}

//bool thread::on_idle(LONG lCount)
//{
//
//   return on_thread_on_idle(this, lCount);
//
//
//}




bool thread::post_message(::user::primitive * pui,UINT uiMessage,WPARAM wparam,lparam lparam)
{

   return Application.post_user_message(this, pui,uiMessage,wparam,lparam);

}





bool thread::post_thread_message(UINT message,WPARAM wParam,lparam lParam)
{

   if (m_hthread == (HTHREAD)NULL || (!m_bRun && message != WM_QUIT))
   {

      if (message == message_system)
      {

         if (wParam == system_message_command)
         {

            // destruct the object in lparam (thread is either destroyed or quitting : it cannot process the object anymore)
            sp(object) spo((lparam) lParam);

         }

      }

      return false;

   }

   if(message == WM_QUIT)
   {
      m_bRun = false;
      string strName = demangle(typeid(*this).name());
      //::output_debug_string("\n\n\nWM_QUIT posted to thread "+strName+"(" + ::str::from((uint64_t)m_uiThread) + ")\n\n\n");
      if(strName == "::core::system")
      {
         ::output_debug_string("\n\n\nWM_QUIT at ::core::system\n\n\n");
      }
      if(strName == "multimedia::audio_core_audio::wave_out")
      {
         ::output_debug_string("\n\n\nWM_QUIT at multimedia::audio_core_audio::wave_out\n\n\n");
      }
      if(strName == "multimedia::audio::wave_out")
      {
         ::output_debug_string("\n\n\nWM_QUIT at multimedia::audio::wave_out\n\n\n");
      }
      if(strName == "multimedia::audio::wave_player")
      {
         ::output_debug_string("\n\n\nWM_QUIT at multimedia::audio::wave_player\n\n\n");
      }
   }
   return ::PostThreadMessage(m_uiThread,message,wParam,lParam) != FALSE;

}





void thread::set_os_data(void * pvoidOsData)
{
#ifdef WINDOWSEX

   if(m_bDupHandle)
   {
      if(m_hthread != NULL)
      {
         ::CloseHandle(m_hthread);
      }
   }
   m_hthread = NULL;
   if(pvoidOsData != NULL)
   {
      if(::DuplicateHandle(::GetCurrentProcess(),(HANDLE)pvoidOsData,GetCurrentProcess(),&m_hthread,THREAD_ALL_ACCESS,TRUE,0))
      {
         m_bDupHandle = true;
      }
      else
      {
         TRACE("thread::set_os_data failed to duplicate handle");
      }
   }
#else
   m_hthread = (HTHREAD)pvoidOsData;
#endif
}

void thread::set_os_int(IDTHREAD iData)
{
#ifdef WINDOWSEX
   m_uiThread = (DWORD)iData;
#else
   m_uiThread = (IDTHREAD) iData;
#endif
}




int32_t thread::thread_startup(::thread_startup * pstartup)
{

   ASSERT(pstartup != NULL);
   ASSERT(pstartup->m_pthread != NULL);
//   ASSERT(pstartup->m_pthreadimpl != NULL);
   ASSERT(!pstartup->m_bError);
//   ASSERT(pstartup->m_pthreadimpl == pstartup->m_pthreadimpl);
  // ASSERT(pstartup->m_pthread == pstartup->m_pthreadimpl->m_pthread);

   //::thread * pthreadimpl = pstartup->m_pthreadimpl;

   IGUI_WIN_MSG_LINK(WM_APP + 1000, this, this, &::thread::_001OnThreadMessage);

   install_message_handling(this);

   //install_message_handling(pthreadimpl);

   return 0;

}




bool thread::thread_entry()
{

   bool bError = false;

   try
   {


      if(!pre_run())
      {

         bError = true;

      }

   }
   catch(...)
   {

      bError = true;

   }

   if(bError)
   {

      return false;

   }
   else
   {

      return true;

   }

}




int32_t thread::main()
{

   if(!pre_init_instance())
   {
      return 0;
   }



   // first -- check for simple worker thread
   DWORD nResult = 0;
   if(m_pfnThreadProc != NULL)
   {
      m_bRun = true;
      nResult = (*m_pfnThreadProc)(m_pThreadParams);
   }
   // else -- check for thread with message loop
   else if(initialize_instance())
   {
      // will stop after PostQuitMessage called
      ASSERT_VALID(this);
      // let upper framework attach translator
      //         translator::attach();
   run:
      try
      {
         m_bReady = true;
         m_bRun = true;
         nResult = run();
      }
      catch(::exit_exception & e)
      {

         throw e;

      }
      catch(const ::exception::exception & e)
      {

         if(on_run_exception((::exception::exception &) e))
            goto run;

         if(App(get_app()).final_handle_exception((::exception::exception &) e))
            goto run;
      }
      catch(...)
      {
      }
   }


   // let translator run undefinetely
   //translator::detach();
   try
   {
      nResult = exit();
   }
   catch(...)
   {
      nResult = (DWORD)-1;
   }

   return nResult;

}

void thread::assert_valid() const
{

   command_target::assert_valid();

}


void thread::dump(dump_context & dumpcontext) const
{

   command_target::dump(dumpcontext);

}


int32_t thread::thread_term()
{

   int32_t iResult = m_iReturnCode;

   try
   {

//      destroy_message_queue();

   }
   catch(...)
   {

   }

   try
   {

      thread_delete();

   }
   catch(...)
   {

   }

   return iResult;

}


//void thread::add(::user::primitive * pui)
//{
//
//   single_lock sl(&m_mutexUiPtra,TRUE);
//
//   if(m_spuiptra.is_set())
//   {
//
//      m_spuiptra->add(pui);
//
//   }
//
//}
//
//
//void thread::remove(::user::primitive * pui)
//{
//
//   if(pui == NULL)
//      return;
//
//   single_lock sl(&m_mutexUiPtra,TRUE);
//
//   pui->remove_thread(this);
//
//   if(m_spuiptra.is_set())
//   {
//
//      m_spuiptra->remove(pui);
//
//   }
//
//   sl.unlock();
//
//   //if(m_sptimera.is_set())
//   //{
//
//   //   m_sptimera->unset(pui);
//
//   //}
//
//}
//
//
//::count thread::get_ui_count()
//{
//
//   single_lock sl(&m_mutexUiPtra,TRUE);
//   if (m_spuiptra.is_null())
//      return 0;
//
//   return m_spuiptra->get_count();
//
//}
//
//
//::user::primitive * thread::get_ui(index iIndex)
//{
//
//   single_lock sl(&m_mutexUiPtra,TRUE);
//   if (m_spuiptra.is_null())
//      return NULL;
//
//   return m_spuiptra->element_at(iIndex);
//
//}


//void thread::set_timer(::user::primitive * pui,uint_ptr nIDEvent,UINT nEllapse)
//{
//
//   if(m_sptimera.is_null())
//   {
//
//      if(!initialize_message_queue())
//         return;
//
//   }
//
//   m_sptimera->set(pui,nIDEvent,nEllapse);
//
//   Application.add_thread(pui, m_pthread);
//
//}
//

//void thread::unset_timer(::user::primitive * pui,uint_ptr nIDEvent)
//{
//
//   if(m_sptimera.is_null())
//      return;
//
//   m_sptimera->unset(pui,nIDEvent);
//
//}




//void thread::step_timer()
//{
//
//   if(m_sptimera.is_null())
//      return;
//
//   m_sptimera->check();
//
//}


thread::operator HTHREAD() const
{

   return this == NULL ? (HTHREAD) NULL : m_hthread;

}


bool thread::initialize_message_queue()
{

   //if(m_spuiptra.is_null())
   //{

   //   m_spuiptra = canew(ptr_array < ::user::primitive >);

   //}

   //if(m_spqueue.is_null())
   //{

   //   m_spqueue.alloc(allocer());

   //}

   //if(m_spqueue.is_null())
   //{

   //   return false;

   //}

   //if(!m_spqueue->message_queue_is_initialized())
   //{

   //   try
   //   {

   //      if(!m_spqueue->create_message_queue("",this))
   //      {

   //         return false;

   //      }

   //   }
   //   catch(...)
   //   {

   //      return false;

   //   }

   //}


   //single_lock sl(&m_sptimera->m_mutex,TRUE);

   //int32_t iMin = 100;

   //for(int32_t i = 0; i < m_sptimera->m_timera.get_count(); i++)
   //{

   //   if(m_sptimera->m_timera.element_at(i)->m_uiElapse < natural(iMin))
   //   {

   //      iMin = m_sptimera->m_timera.element_at(i)->m_uiElapse;

   //   }

   //}

   //sl.unlock();

   //m_spqueue->message_queue_set_timer((uint_ptr)-2,iMin);

   return true;

}


//// main running routine until thread exits
//int32_t thread::run()
//{
//
//
////stop_run:
//
//   return m_iReturnCode;
//
//}


void thread::message_handler(signal_details * pobj)
{

   Application.message_handler(pobj);

}


//bool thread::defer_pump_message()
//{
//
//   MESSAGE msg;
//
//   while(::PeekMessage(&msg,NULL,0,0,PM_NOREMOVE) != FALSE)
//   {
//
//      // pump message, but quit on WM_QUIT
//      if(!m_bRun || !pump_message())
//      {
//
//
//         ::output_debug_string("\n\n\nthread::defer_pump_message (1) quitting (WM_QUIT? {PeekMessage->message : "+::str::from(msg.message == WM_QUIT?1:0)+"!}) : " + string(demangle(typeid(*m_pthread).name())) + " ("+::str::from((uint64_t)::GetCurrentThreadId())+")\n\n\n");
//
//         return false;
//
//      }
//
//   }
//
//   // reset "no idle" state after pumping "normal" message
//   //if (is_idle_message(&m_msgCur))
//   if(is_idle_message(&msg))
//   {
//
//      //m_bIdle = true;
//
//      //m_lIdleCount = 0;
//
//   }
//
//   if(!on_run_step())
//   {
//
//      ::output_debug_string("defer_pump_message (2) quitting : " + string(demangle(typeid(*m_pthread).name())) + "\n\n");
//
//      return false;
//
//   }
//
//
//   on_idle(0);
//
//   return true;
//
//
//}

//bool thread::pump_message()
//{
//
//   try
//   {
//
//      MESSAGE msg;
//
//      if(!::GetMessage(&msg,NULL,0,0))
//      {
//
//         TRACE(::aura::trace::category_AppMsg,1,"thread::pump_message - Received WM_QUIT.\n");
//
//         ::output_debug_string("thread::pump_message - Received WM_QUIT.\n");
//
//         m_nDisablePumpCount++; // application must die
//         // Note: prevents calling message loop things in 'exit_instance'
//         // will never be decremented
//         return false;
//
//      }
//
//      process_message(&msg);
//
//      return true;
//
//   }
//   catch(exit_exception & e)
//   {
//
//      throw e;
//
//   }
//   catch(const ::exception::exception & e)
//   {
//
//      if(on_run_exception((::exception::exception &) e))
//         return true;
//
//      // get_app() may be it self, it is ok...
//      if(App(get_app()).final_handle_exception((::exception::exception &) e))
//         return true;
//
//      return false;
//
//   }
//   catch(...)
//   {
//
//      return false;
//
//   }
//
//}


bool thread::process_message(LPMESSAGE lpmessage)
{

   if(lpmessage->message == WM_LBUTTONDOWN)
   {

      output_debug_string("WM_LBUTTONDOWN");

   }

   try
   {

      MESSAGE & msg = *lpmessage;

      if (msg.message == message_system)
      {

         if (msg.wParam == system_message_user)
         {

            sp(::object) pobject((lparam) msg.lParam);

            Application.dispatch_user_message_object(pobject);

         }
         else if (msg.wParam == system_message_command)
         {

            sp(::primitive::command) pcommand((lparam)msg.lParam);

            m_pcommandthread->on_command(pcommand);

         }
         else if (msg.wParam == system_message_meta)
         {

            ::send_thread_message * pmessage = dynamic_cast <::send_thread_message *>((object *)(uint_ptr)msg.lParam);

            MESSAGE & message = pmessage->m_message;

            process_message(&message);

            pmessage->m_bOk = true;

         }
         else if (msg.wParam == system_message_register_dependent_thread)
         {

            on_register_dependent_thread((thread*)msg.lParam);

         }
         else if (msg.wParam == system_message_unregister_dependent_thread)
         {

            on_unregister_dependent_thread((thread*)msg.lParam);

         }
         else
         {
         }

         return true;

      }


      //m_message = msg;
      //m_p->m_message = msg;

      if(m_nDisablePumpCount != 0)
      {

         TRACE(::aura::trace::category_AppMsg,0,"Error: thread::pump_message called when not permitted.\n");

//         ASSERT(FALSE);

      }

      //__trace_message("pump_message",&msg);

      if(msg.message != WM_KICKIDLE)
      {

         {

            smart_pointer < ::message::base > spbase;

            spbase = get_base(&msg);

            if(spbase.is_set())
            {

               try
               {

                  pre_translate_message(spbase);

                  if(spbase->m_bRet)
                     return true;

               }
               catch(exit_exception & e)
               {

                  throw e;

               }
               catch(...)
               {

               }

               if(true)
               {

                  try
                  {

                     if(m_pauraapp != NULL)
                     {

                        try
                        {

                           if(m_pauraapp->m_paurasystem != NULL)
                           {

                              m_pauraapp->m_paurasystem->pre_translate_message(spbase);

                              if(spbase->m_bRet)
                                 return true;

                              /*                                 try
                              {
                              if(m_pauraapp->m_paurasystem->m_pcube != NULL)
                              {
                              m_pauraapp->m_paurasystem->m_pcubeInterface->pre_translate_message(spbase);
                              if(spbase->m_bRet)
                              return TRUE;
                              }
                              }
                              catch(...)
                              {
                              }

                              */

                           }

                        }
                        catch(...)
                        {

                        }

                        if(m_pauraapp->m_paurasession != NULL)
                        {

                           try
                           {

                              m_pauraapp->m_paurasession->pre_translate_message(spbase);

                              if(spbase->m_bRet)
                                 return true;

                           }
                           catch(...)
                           {

                           }

                           /*                              try
                           {
                           if(m_pauraapp->m_paurasession->m_pbergedge != NULL)
                           {
                           m_pauraapp->m_paurasession->m_pbergedgeInterface->pre_translate_message(spbase);
                           if(spbase->m_bRet)
                           return TRUE;
                           }
                           }
                           catch(...)
                           {
                           }*/

                        }

                     }

                  }
                  catch(...)
                  {

                  }

                  try
                  {

                     if(!m_pauraapp->is_system() && m_pauraapp->is_session())
                     {

                        m_pauraapp->pre_translate_message(spbase);

                        if(spbase->m_bRet)
                           return true;

                     }

                  }
                  catch(...)
                  {

                  }

               }

               //__pre_translate_message(spbase);
               //if(spbase->m_bRet)
               // return TRUE;

               //     spbase.release();
            }

         }

         ::TranslateMessage(&msg);

         ::DispatchMessage(&msg);

      }

      return true;

   }
   catch(exit_exception & e)
   {

      throw e;

   }
   catch(const ::exception::exception & e)
   {

      if(on_run_exception((::exception::exception &) e))
         return true;

      // get_app() may be it self, it is ok...
      if(App(get_app()).final_handle_exception((::exception::exception &) e))
         return true;

      return false;

   }
   catch(...)
   {

      return false;

   }

}


bool thread::set_thread_priority(int32_t iCa2Priority)
{

   //ASSERT(m_hthread != NULL);

#ifdef WINDOWSEX

   int32_t nPriority = (int)get_os_thread_priority(iCa2Priority);

#else

   int32_t nPriority = (int)iCa2Priority;

#endif

   bool bOk = ::SetThreadPriority(m_hthread, nPriority) != FALSE;

   if (!bOk)
   {
      uint32_t dwLastError = ::GetLastError();
      output_debug_string("thread::SetThreadPriority LastError = " + ::str::from(dwLastError));
   }

   return bOk;

}


int32_t thread::get_thread_priority()
{

   ASSERT(m_hthread != NULL);

   int32_t nPriority = ::GetThreadPriority(m_hthread);

#ifdef WINDOWSEX

   int32_t iCa2Priority = ::get_os_thread_scheduling_priority(nPriority);

#else

   int32_t iCa2Priority = nPriority;

#endif

   return iCa2Priority;
}


void thread::thread_delete()
{

   try
   {

      if(m_pevReady != NULL)
      {

         m_pevReady->SetEvent();

      }

   }
   catch(...)
   {

   }

   set_os_data(NULL);

}


//bool thread::finalize()
//{
//
//   //if(m_spqueue.is_set())
//   //{
//
//   //   //if(m_spqueue->message_queue_is_initialized())
//   //   {
//
//   //      m_spqueue->message_queue_destroy();
//
//   //   }
//
//   //   m_spqueue.release();
//
//   //}
//
//   return true;
//
//}


void thread::start()
{

#if defined (WINDOWSEX)

   ::ResumeThread(m_hthread);

#endif

}


uint32_t thread::ResumeThread()
{

   ASSERT(m_hthread != NULL);

   #if defined (WINODWSEX)

   return ::ResumeThread(m_hthread);

   #else


   return 0;

   #endif

}


bool thread::has_message()
{

   MESSAGE msg;
   return ::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE) != FALSE;

}


void thread::set_priority(int32_t priority)
{

   if (::SetThreadPriority(m_hthread, priority) == 0)
      throw runtime_error(get_app(), "Thread::set_priority: Couldn't set thread priority.");

}


int32_t thread::priority()
{

   return ::GetThreadPriority(m_hthread);

}


bool thread::on_run_exception(::exception::exception &)
{

   return false;

}


message::e_prototype thread::GetMessagePrototype(UINT uiMessage,UINT uiCode)
{

   UNREFERENCED_PARAMETER(uiMessage);
   UNREFERENCED_PARAMETER(uiCode);

   return message::PrototypeNone;


}


int thread::get_x_window_count() const
{

   return 0;

}


void thread::do_events()
{

   MESSAGE msg;

   while(::PeekMessage(&msg,NULL,0,0,PM_NOREMOVE) != FALSE)
   {

      if(msg.message == WM_QUIT) // do not pump, otherwise main loop will not process the message
         break;

      if(!pump_message())
         break;

   }

}






//bool replace_thread::do_replace(::thread * pthread)
//{
//
//   single_lock sl(&m_mutex,true);
//
//   if(m_pthreadNew == NULL)
//      return true;
//
//   if(m_pthreadNew != pthread)
//      return false;
//
//   while(m_spthread.is_set())
//   {
//
//      if(m_pthreadNew != pthread)
//         return false;
//
//      try
//      {
//
//         m_spthread->set_end_thread();
//
//      }
//      catch(...)
//      {
//
//      }
//
//      sl.unlock();
//
//      sl.lock();
//
//      if(m_pthreadNew != pthread)
//         return false;
//
//   }
//
//   if(m_pthreadNew != pthread)
//      return false;
//
//   m_spthread = pthread;
//
//   return true;
//
//}
//
//
//
//

//void thread::message_queue_message_handler(::signal_details * pobj)
//{
//
//    try
//    {
//
//        message_queue_message_handler(pobj);
//
//    }
//    catch(exit_exception & e)
//    {
//
//        throw e;
//
//    }
//    catch(...)
//    {
//
//    }
//
//}



void thread::_001OnThreadMessage(signal_details * pobj)
{

   SCAST_PTR(::message::base, pbase, pobj);



}

::command_thread * thread::command_central()
{
   return m_pcommandthread;
}

::command_thread * thread::command_thread()
{
   return m_pcommandthread;
}

::command_thread * thread::command()
{
   return m_pcommandthread;
}

::command_thread * thread::guideline()
{
   return m_pcommandthread;
}

::command_thread * thread::directrix()
{
   return m_pcommandthread;
}

::command_thread * thread::axiom()
{
   return m_pcommandthread;
}


bool thread::verb()
{

//   m_pcommandthread->run();

   return true;

}



::command_thread * thread::creation()
{
   return m_pcommandthread;
}



void thread::on_command(::primitive::command * pcommand)
{

   sp(::create) pcreate = pcommand;

   if (pcreate.is_set())
   {

      on_create(pcreate);

   }

}


void thread::on_create(::create * pcreate)
{

   try
   {

      request_create(pcreate);

   }
   catch (not_installed & e)
   {

      System.on_run_exception(e);

      throw exit_exception(e.get_app());

   }
   catch (::exit_exception & e)
   {

      throw e;

   }
   catch (::exception::exception & e)
   {

      if (!Application.on_run_exception(e))
         throw exit_exception(get_app());

   }
   catch (...)
   {

   }


}


