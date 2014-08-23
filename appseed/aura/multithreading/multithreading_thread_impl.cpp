//
//  multithreading_thread_impl.cpp
//  aura
//
//
//

#include "framework.h"

uint32_t __thread_entry(void * pparam);

thread_impl::thread_impl(sp(::aura::application) papp):
element(papp),
m_evFinish(papp),
m_mutexUiPtra(papp),
m_queue(papp)
{

   
   
   CommonConstruct();

}


thread_impl::~thread_impl()
{


}



void thread_impl::construct()
{
   
   CommonConstruct();
   
}



void thread_impl::construct(__THREADPROC pfnThreadProc, LPVOID pParam)
{

   CommonConstruct();

   m_pfnThreadProc = pfnThreadProc;
   m_pThreadParams = pParam;
   
}


void thread_impl::CommonConstruct()
{

   m_bDupHandle = false;

   m_hthread = NULL;
   m_uiThread = 0;

   m_evFinish.SetEvent();
   m_pThreadParams = NULL;
   m_pfnThreadProc = NULL;

   m_nDisablePumpCount  = 0;
   
   
   m_hthread = NULL;

}




bool thread_impl::pre_init_instance()
{

   return true;

}


bool thread_impl::initialize_instance()
{

   return true;

}

void thread_impl::dispatch_thread_message(signal_details * pobj)
{

   SCAST_PTR(::message::base,pbase,pobj);
   if(!pbase->m_bRet && pbase->m_uiMessage == WM_APP + 1984 && pbase->m_wparam == 77)
   {
      Application.dispatch_user_message(pbase);
   }
   LRESULT lresult;
   SignalPtrArray signalptra;
   m_signala.GetSignalsByMessage(signalptra,pbase->m_uiMessage,0,0);
   for(int32_t i = 0; i < signalptra.get_size(); i++)
   {
      Signal & signal = *signalptra[i];
      class signal * psignal = signal.m_psignal;
      message::e_prototype eprototype = signal.m_eprototype;
      if(eprototype == message::PrototypeNone)
      {
         //::message::base aura(get_app());
         pbase->m_psignal = psignal;
         lresult = 0;
         //aura.set(pmsg->message, pmsg->wParam, pmsg->lParam, lresult);
         psignal->emit(pbase);
         if(pbase->m_bRet)
            return;
      }
      break;
   }
   pbase->m_bRet = true;

}


void thread_impl::pre_translate_message(signal_details * pobj)
{

   try
   {
      SCAST_PTR(::message::base,pbase,pobj);

      //   ASSERT_VALID(this);

      // if this is a thread-message, int16_t-circuit this function
      if(pbase->m_pwnd == NULL)
      {
         m_pthread->dispatch_thread_message(pobj);
         if(pobj->m_bRet)
            return;
      }

//      ::user::interaction * puiTopic = pbase->m_pwnd;

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







void thread_impl::process_window_procedure_exception(::exception::base*,signal_details * pobj)
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


namespace thread_impl_util
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

void thread_impl::process_message_filter(int32_t code,signal_details * pobj)
{

   Application.process_message_filter(code,pobj);
   //if(pobj == NULL)
   //   return;   // not handled

   //SCAST_PTR(::message::base,pbase,pobj);

   //sp(::user::frame_window) pTopFrameWnd;
   //::user::interaction * pMainWnd;
   //::user::interaction * pMsgWnd;
   //switch(code)
   //{
   ////case MSGF_DDEMGR:
   //   // Unlike other WH_MSGFILTER codes, MSGF_DDEMGR should
   //   //  never call the next hook.
   //   // By returning FALSE, the message will be dispatched
   //   //  instead (the default behavior).
   //   //return;

   //case MSGF_MENU:
   //   pMsgWnd = pbase->m_pwnd;
   //   if(pMsgWnd != NULL)
   //   {
   //      pTopFrameWnd = pMsgWnd->GetTopLevelFrame();
   //      if(pTopFrameWnd != NULL && pTopFrameWnd->IsTracking() &&
   //         pTopFrameWnd->m_bHelpMode)
   //      {
   //         //pMainWnd = __get_main_window();
   //         //if((m_puiMain != NULL) && (IsEnterKey(pbase) || IsButtonUp(pbase)))
   //         //{
   //         //   //                  pMainWnd->SendMessage(WM_COMMAND, ID_HELP);
   //         //   pbase->m_bRet = true;
   //         //   return;
   //         //}
   //      }
   //   }
   //   // fall through...

   //case MSGF_DIALOGBOX:    // handles message boxes as well.
   //   //pMainWnd = __get_main_window();
   //   if(code == MSGF_DIALOGBOX && m_pthread->m_puiActive != NULL &&
   //      pbase->m_uiMessage >= WM_KEYFIRST && pbase->m_uiMessage <= WM_KEYLAST)
   //   {
   //      //// need to translate messages for the in-place container
   //      //___THREAD_STATE* pThreadState = __get_thread_state();
   //      //ENSURE(pThreadState);

   //      //if (pThreadState->m_bInMsgFilter)
   //      //   return;
   //      //pThreadState->m_bInMsgFilter = TRUE;    // avoid reentering this code
   //      //if (m_puiActive->is_window_enabled())
   //      //{
   //      //   pre_translate_message(pobj);
   //      //   if(pobj->m_bRet)
   //      //   {
   //      //      pThreadState->m_bInMsgFilter = FALSE;
   //      //      return;
   //      //   }
   //      //}
   //      //pThreadState->m_bInMsgFilter = FALSE;    // ok again
   //   }
   //   break;
   //}
   //// default to not handled
}





thread_startup::thread_startup(sp(::aura::application) papp) :
   element(papp),
   m_event(papp),
   m_event2(papp)
{

   m_iError = 0;
   m_bSynch = false;


}


thread_startup::~thread_startup()
{

}




bool thread_impl::begin_thread(bool bSynch,int32_t * piStartupError,int32_t epriority,uint_ptr nStackSize,uint32_t dwCreateFlagsParam,LPSECURITY_ATTRIBUTES lpSecurityAttrs)
{

   DWORD dwCreateFlags = dwCreateFlagsParam;

   ENSURE(m_hthread == NULL);

   sp(::thread_startup) pstartup = canew(::thread_startup(get_app()));

   pstartup->m_bError = FALSE;

   pstartup->m_bSynch = bSynch;

   pstartup->m_pthreadimpl = this;

   pstartup->m_pthread = m_pthread;

   pstartup->m_dwCreateFlags = dwCreateFlags;

   pstartup->m_event2.ResetEvent();

   m_hthread = (HTHREAD)(uint_ptr) ::create_thread(lpSecurityAttrs,nStackSize,&__thread_entry,pstartup.m_p,dwCreateFlags,&m_uiThread);

   if(m_hthread == NULL)
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

bool thread_impl::create_thread(int32_t epriority,uint_ptr nStackSize,uint32_t dwCreateFlags,LPSECURITY_ATTRIBUTES lpSecurityAttrs)
{

   return begin_thread(false,NULL,epriority,nStackSize, dwCreateFlags,lpSecurityAttrs);

}

bool thread_impl::create_thread_synch(int32_t * piStartupError,int32_t epriority,uint_ptr nStackSize,uint32_t dwCreateFlags,LPSECURITY_ATTRIBUTES lpSecurityAttrs)
{

   return begin_thread(true,piStartupError,epriority,nStackSize, dwCreateFlags,lpSecurityAttrs);

}


bool thread_impl::begin(int32_t epriority,uint_ptr nStackSize,uint32_t dwCreateFlags,LPSECURITY_ATTRIBUTES lpSecurityAttrs)
{

   if(!create_thread(epriority,nStackSize,dwCreateFlags, lpSecurityAttrs))
   {
      return false;
   }

   return true;

}

bool thread_impl::begin_synch(int32_t * piStartupError,int32_t epriority,uint_ptr nStackSize,uint32_t dwCreateFlags,LPSECURITY_ATTRIBUTES lpSecurityAttrs)
{

   if(!create_thread_synch(piStartupError, epriority,nStackSize, dwCreateFlags,lpSecurityAttrs))
   {
      return false;
   }

   return true;

}

void * thread_impl::get_os_data() const
{

   return (void *)m_hthread;

}


int_ptr thread_impl::get_os_int() const
{

   return m_uiThread;

}


int_ptr thread_impl::item() const
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
      ASSERT(pstartup->m_pthreadimpl != NULL);
      ASSERT(!pstartup->m_bError);


      ::thread * pthread = pstartup->m_pthread;

      ::thread_impl * pthreadimpl = pstartup->m_pthreadimpl;


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

         pthreadimpl->thread_startup(pstartup);

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

         if(!pthreadimpl->thread_entry())
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

      if(pthread->m_preplacethread != NULL && !pthread->m_preplacethread->do_replace(pthread))
      {

         try
         {

            pthread->m_preplacethread = NULL;

         }
         catch(...)
         {

         }

         try
         {

            pthread->exit();

         }
         catch(...)
         {

         }

         return ::multithreading::__on_thread_finally(pthread);

      }


      try
      {

         pthreadimpl->m_pthread->main();

      }
      catch(::exit_exception &)
      {

         Sys(pthreadimpl->m_pauraapp).post_thread_message(WM_QUIT,0,0);

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


void CLASS_DECL_AURA __end_thread(sp(::aura::application) papp)
{

   __term_thread(papp);

}


void CLASS_DECL_AURA __term_thread(sp(::aura::application) papp)
{

   UNREFERENCED_PARAMETER(papp);

}



bool thread_impl::is_idle_message(signal_details * pobj)
{

   return ::message::is_idle_message(pobj);

}

bool thread_impl::is_idle_message(LPMESSAGE lpmsg)
{

   return ::message::is_idle_message(lpmsg);

}



void thread_impl::post_to_all_threads(UINT message,WPARAM wparam,LPARAM lparam)
{

   ::count ca;

   thread * pthread;

   ca = ::multithreading::s_pthreadptra->get_size();

   bool bOk;

   if(message == WM_QUIT)
   {

      single_lock sl(::multithreading::s_pmutex,true);
      comparable_array < thread * > threadptra = *::multithreading::s_pthreadptra;

      for(index i = 0; i < threadptra.get_size(); i++)
      {

         try
         {
            pthread = dynamic_cast < thread * >(threadptra[i]);
            pthread->m_bRun = false;
         }
         catch(...)
         {
         }


      }
      sl.unlock();

   }


   single_lock sl(::multithreading::s_pmutex);

   for(index i = ::multithreading::s_phaThread->get_size(); i >= 0; i--)
   {

      bOk = true;

      try
      {

         if(::PostThreadMessage(::GetThreadId(::multithreading::s_phaThread->element_at(i)),message,wparam,lparam))
         {

         }

      }
      catch(...)
      {

         bOk = false;

      }

      sl.lock();


   }

}


int32_t thread_impl::exit_instance()
{

   ASSERT_VALID(this);

   try
   {

      single_lock sl(&m_mutexUiPtra,TRUE);
      
      if(m_spuiptra.is_set())
      {

         sp(ptr_array < ::user::interaction >) puiptra = m_spuiptra;

         m_spuiptra.release();

         for(int32_t i = 0; i < puiptra->get_size(); i++)
         {

            ::user::interaction * pui = puiptra->element_at(i);

         }

         puiptra.release();

         sl.unlock();

      }
   }
   catch(...)
   {
   }

   try
   {
      
      m_sptimera.release();

   }
   catch(...)
   {
   }


   return m_pthread->m_iReturnCode;

}

bool thread_impl::on_idle(LONG lCount)
{
   
   
   return Application.on_thread_on_idle(this, lCount);


}




bool thread_impl::post_message(::user::interaction * pui,UINT uiMessage,WPARAM wparam,lparam lparam)
{

   return Application.post_user_message(this, pui,uiMessage,wparam,lparam);

}





bool thread_impl::post_thread_message(UINT message,WPARAM wParam,lparam lParam)
{

   if(m_hthread == NULL)
      return false;

   return ::PostThreadMessage(m_uiThread,message,wParam,lParam) != FALSE;

}





void thread_impl::set_os_data(void * pvoidOsData)
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
         TRACE("thread_impl::set_os_data failed to duplicate handle");
      }
   }
#else
   m_hthread = (HTHREAD)pvoidOsData;
#endif
}

void thread_impl::set_os_int(int_ptr iData)
{
#ifdef WINDOWSEX
   m_uiThread = (DWORD)iData;
#else
   m_uiThread = (DWORD)iData;
#endif
}




int32_t thread_impl::thread_startup(::thread_startup * pstartup)
{

   ASSERT(pstartup != NULL);
   ASSERT(pstartup->m_pthread != NULL);
   ASSERT(pstartup->m_pthreadimpl != NULL);
   ASSERT(!pstartup->m_bError);
   ASSERT(pstartup->m_pthreadimpl == pstartup->m_pthread->m_pthreadimpl);
   ASSERT(pstartup->m_pthread == pstartup->m_pthreadimpl->m_pthread);

   ::thread_impl * pthreadimpl = pstartup->m_pthreadimpl;

   m_evFinish.ResetEvent();

   install_message_handling(pthreadimpl);

   m_pthread->install_message_handling(pthreadimpl);

   return 0;

}




bool thread_impl::thread_entry()
{

   bool bError = false;

   try
   {


      if(!m_pthread->pre_run())
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


int32_t thread_impl::main()
{

   if(!m_pthread->pre_init_instance())
   {
      return 0;
   }

   // first -- check for simple worker thread
   DWORD nResult = 0;
   if(m_pfnThreadProc != NULL)
   {
      nResult = (*m_pfnThreadProc)(m_pThreadParams);
   }
   // else -- check for thread with message loop
   else if(m_pthread->initialize_instance())
   {
      // will stop after PostQuitMessage called
      ASSERT_VALID(this);
      // let upper framework attach translator
      //         translator::attach();
   run:
      try
      {
         m_pthread->m_bReady = true;
         m_pthread->m_bRun = true;
         nResult = m_pthread->run();
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
      nResult = m_pthread->exit();
   }
   catch(...)
   {
      nResult = (DWORD)-1;
   }

   return nResult;

}


int32_t thread_impl::thread_term()
{

   int32_t iResult = m_pthread->m_iReturnCode;

   try
   {
      
//      destroy_message_queue();

   }
   catch(...)
   {

   }

   try
   {

      thread_impl_delete();

   }
   catch(...)
   {

   }

   return iResult;

}


void thread_impl::add(::user::interaction * pui)
{

   single_lock sl(&m_mutexUiPtra,TRUE);

   if(m_spuiptra.is_set())
   {

      m_spuiptra->add(pui);

   }

}


void thread_impl::remove(::user::interaction * pui)
{

   if(pui == NULL)
      return;

   single_lock sl(&m_mutexUiPtra,TRUE);

   if(Application.get_thread(pui) == m_pthread)
   {

      Application.set_thread(pui, NULL);

   }

   if(m_spuiptra.is_set())
   {

      m_spuiptra->remove(pui);

   }

   sl.unlock();

   if(m_sptimera.is_set())
   {

      m_sptimera->unset(pui);

   }

}


::count thread_impl::get_ui_count()
{

   single_lock sl(&m_mutexUiPtra,TRUE);

   return m_spuiptra->get_count();

}


::user::interaction * thread_impl::get_ui(index iIndex)
{

   single_lock sl(&m_mutexUiPtra,TRUE);

   return m_spuiptra->element_at(iIndex);

}


void thread_impl::set_timer(::user::interaction * pui,uint_ptr nIDEvent,UINT nEllapse)
{

   if(m_sptimera.is_null())
   {

      if(!initialize_message_queue())
         return;

   }

   m_sptimera->set(pui,nIDEvent,nEllapse);

}


void thread_impl::unset_timer(::user::interaction * pui,uint_ptr nIDEvent)
{
   
   if(m_sptimera.is_null())
      return;

   m_sptimera->unset(pui,nIDEvent);

}


event & thread_impl::get_finish_event()
{

   return m_evFinish;

}


void thread_impl::step_timer()
{
   
   if(m_sptimera.is_null())
      return;

   m_sptimera->check();

}


thread_impl::operator HTHREAD() const
{

   return this == NULL ? NULL : m_hthread;

}


bool thread_impl::initialize_message_queue()
{

   if(m_sptimera.is_null())
   {

      m_sptimera = canew(::user::timer_array(get_app()));

   }

   if(m_spuiptra.is_null())
   {

      m_spuiptra = canew(ptr_array < ::user::interaction >);

   }

   if(!m_queue.is_initialized())
   {

      try
      {

         if(!m_queue.create_message_queue("",this))
            return false;

      }
      catch(...)
      {

         return false;

      }

   }


   single_lock sl(&m_sptimera->m_mutex,TRUE);

   int32_t iMin = 100;

   for(int32_t i = 0; i < m_sptimera->m_timera.get_count(); i++)
   {

      if(m_sptimera->m_timera.element_at(i)->m_uiElapse < natural(iMin))
      {

         iMin = m_sptimera->m_timera.element_at(i)->m_uiElapse;

      }

   }

   sl.unlock();

   m_queue.message_queue_set_timer((uint_ptr)-2,iMin);

   return true;

}


// main running routine until thread exits
int32_t thread_impl::run()
{

   ASSERT_VALID(this);

   // for tracking the idle time state
   bool bIdle = TRUE;
   LONG lIdleCount = 0;

   // acquire and dispatch messages until a WM_QUIT message is received.
   MESSAGE msg;

   while(m_pthread->m_bRun)
   {

      // phase1: check to see if we can do idle work
      while(bIdle && !::PeekMessage(&msg,NULL,0,0,PM_NOREMOVE))
      {

         // call on_idle while in bIdle state
         if(!on_idle(lIdleCount++))
         {

            lIdleCount = 0;

            bIdle = FALSE; // assume "no idle" state

         }

         if(!m_pthread->on_run_step())
            goto stop_run;

      }

      // phase2: pump messages while available
      while(::PeekMessage(&msg,NULL,0,0,PM_NOREMOVE) != FALSE)
      {

         // pump message, but quit on WM_QUIT
         if(!m_pthread->m_bRun || !pump_message())
         {

            goto stop_run;

         }

         // reset "no idle" state after pumping "normal" message
         //if (is_idle_message(&m_msgCur))
         if(is_idle_message(&msg))
         {

            bIdle = TRUE;

            lIdleCount = 0;

         }

         if(!m_pthread->on_run_step())
            goto stop_run;

      }

      bIdle = true;

   }

stop_run:

   return 0;

}


void thread_impl::message_handler(signal_details * pobj)
{

   SCAST_PTR(::message::base,pbase,pobj);

   ::window_sp pwindow = pbase->m_pwnd->GetWindow();

   ASSERT(pwindow == NULL || pwindow == pbase->m_pwnd->m_pimpl);

   if(pwindow == NULL || pwindow != pbase->m_pwnd->m_pimpl)
   {

   #ifdef WINDOWSEX

      pbase->set_lresult(::DefWindowProc(pbase->m_pwnd->get_safe_handle(),pbase->m_uiMessage,pbase->m_wparam,pbase->m_lparam));

   #else

      pbase->set_lresult(0);

   #endif

      return;

   }

   __trace_message("message_handler",pobj);

   try
   {

      if(pwindow->m_pui != NULL && pwindow->m_pui != pwindow)
      {

         pwindow->m_pui->message_handler(pobj);

      }
      else
      {

         pwindow->message_handler(pobj);

      }

   }
   catch(const ::exception::exception & e)
   {

      if(App(get_app()).on_run_exception((::exception::exception &) e))
         goto run;

      if(App(get_app()).final_handle_exception((::exception::exception &) e))
         goto run;

      __post_quit_message(-1);

      pbase->set_lresult(-1);

      return;

   }
   catch(::exception::base * pe)
   {

      process_window_procedure_exception(pe,pbase);

      TRACE(::aura::trace::category_AppMsg,0,"Warning: Uncaught exception in message_handler (returning %ld).\n",(int_ptr)pbase->get_lresult());

      pe->Delete();

   }

run:;

}


bool thread_impl::pump_message()
{

   try
   {

      MESSAGE msg;

      if(!::GetMessage(&msg,NULL,0,0))
      {

         TRACE(::aura::trace::category_AppMsg,1,"thread::pump_message - Received WM_QUIT.\n");

         m_nDisablePumpCount++; // application must die
         // Note: prevents calling message loop things in 'exit_instance'
         // will never be decremented
         return false;

      }

      //m_message = msg;
      //m_p->m_message = msg;

      if(m_nDisablePumpCount != 0)
      {

         TRACE(::aura::trace::category_AppMsg,0,"Error: thread::pump_message called when not permitted.\n");

         ASSERT(FALSE);

      }

      __trace_message("pump_message",&msg);

      if(msg.message != WM_KICKIDLE)
      {

         {

            smart_pointer < ::message::base > spbase;

            spbase = get_base(&msg);

            if(spbase.is_set())
            {

               try
               {

                  if(m_pthread != NULL)
                  {

                     m_pthread->pre_translate_message(spbase);

                     if(spbase->m_bRet)
                        return true;

                  }

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


bool thread_impl::set_thread_priority(int32_t priority)
{

   return ::SetThreadPriority(m_hthread, priority) != 0;

}


int32_t thread_impl::get_thread_priority()
{

   return ::GetThreadPriority(m_hthread);

}


void thread_impl::thread_impl_delete()
{

   try
   {

      if(m_pthread->m_pbReady != NULL)
      {

         *m_pthread->m_pbReady = true;

      }

   }
   catch(...)
   {

   }

   try
   {

      m_evFinish.SetEvent();

   }
   catch(...)
   {

   }

   try
   {

      m_pthread->m_bRun = false;

   }
   catch(...)
   {

   }

   if(m_pthread->m_preplacethread != NULL)
   {

      single_lock sl(&m_pthread->m_preplacethread->m_mutex,true);

      m_pthread->m_preplacethread->m_spthread.release();
   
   }
   else if(m_pthread->m_bAutoDelete)
   {

       m_pthread->release();

   }
   else
   {
      
      m_pthread->set_os_data(NULL);

   }

}


bool thread_impl::finalize()
{
   
   m_queue.DestroyWindow();

//   destroy_message_queue();

   return true;

}


void thread_impl::start()
{

}


uint32_t thread_impl::ResumeThread()
{

   return 0;

}


bool thread_impl::has_message()
{

   return false;

}


void thread_impl::set_priority(int32_t priority)
{

   UNREFERENCED_PARAMETER(priority);

}


int32_t thread_impl::priority()
{

   return ::aura::scheduling_priority_normal;

}


bool thread_impl::on_run_exception(::exception::exception &)
{

   return true;

}


message::e_prototype thread_impl::GetMessagePrototype(UINT uiMessage,UINT uiCode)
{

   UNREFERENCED_PARAMETER(uiMessage);
   UNREFERENCED_PARAMETER(uiCode);

   return message::PrototypeNone;


}


int thread_impl::get_x_window_count() const
{

   return 0;

}


void thread_impl::do_events()
{

   MESSAGE msg;

   while(m_pthread->m_bRun && ::PeekMessage(&msg,NULL,0,0,PM_NOREMOVE) != FALSE)
   {
      
      if(msg.message == WM_QUIT) // do not pump, otherwise main loop will not process the message
         break;

      if(!m_pthread->pump_message())
         break;

   }

}






bool replace_thread::do_replace(::thread * pthread)
{

   single_lock sl(&m_mutex,true);

   if(m_pthreadNew == NULL)
      return true;

   if(m_pthreadNew != pthread)
      return false;

   while(m_spthread.is_set())
   {

      if(m_pthreadNew != pthread)
         return false;

      try
      {

         m_spthread->m_bRun = false;

      }
      catch(...)
      {

      }

      sl.unlock();

      sl.lock();

      if(m_pthreadNew != pthread)
         return false;

   }

   if(m_pthreadNew != pthread)
      return false;

   m_spthread = pthread;

   return true;

}



