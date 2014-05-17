#include "framework.h"
#include <fcntl.h>




struct ___THREAD_STARTUP : ::mac::thread_startup

{
   ::mac::thread* pThread;    // thread for new thread
   DWORD dwCreateFlags;    // thread creation flags
   bool bError;    // TRUE if error during startup
};


namespace mac
{
   
   thread_startup::thread_startup() :
   hEvent(get_thread_app(), false, true),
   hEvent2(get_thread_app(), false, true)
   {
   }
   
   thread_startup::~thread_startup()
   {
   }
   
} // namespace ca2





/////////////////////////////////////////////////////////////////////////////
// thread entry point

struct _AFX_THREAD_STARTUP : ::mac::thread_startup
{
   ::mac::thread* pThread;    // thread for new thread
   DWORD dwCreateFlags;    // thread creation flags
   WINBOOL bError;    // TRUE if error during startup
};

UINT APIENTRY __thread_entry(void * pParam)
{
   _AFX_THREAD_STARTUP* pStartup = (_AFX_THREAD_STARTUP*)pParam;
   ASSERT(pStartup != NULL);
   ASSERT(pStartup->pThread != NULL);
   ASSERT(!pStartup->bError);
   
   ::mac::thread * pnodethread = pStartup->pThread;
   
   try
   {
      
      __init_thread();

   }
   catch(::exception::base *)
   {
      pStartup->bError = TRUE;
      pStartup->hEvent.set_event();
      __end_thread(pnodethread->m_pbaseapp, (UINT)-1, FALSE);
      ASSERT(FALSE);  // unreachable
   }
   
   pStartup->m_pthread = pStartup->pThread;
   
   pnodethread->thread_entry(pStartup);
   
   
   pStartup->hEvent.set_event();
   
   // wait for thread to be resumed
   pStartup->hEvent2.wait();
   
   delete pStartup;
   
   pStartup = NULL;
   
   
   int32_t n = pnodethread->m_puser->main();
   
   return pnodethread->thread_term(n);
}





void CLASS_DECL_mac __end_thread(::base::application * papp, UINT nExitCode, bool bDelete)
{
   
   ::thread * pthread = ::get_thread();
   
   if(pthread != NULL)
   {
      
      if(pthread->m_pimpl.is_set())
      {

         ::mac::thread* pmacthread = pthread->m_pimpl.cast < ::mac::thread >();
   
         if (pmacthread != NULL)
         {
            
            ASSERT_VALID(pmacthread);
      
            if (bDelete)
               pmacthread->Delete();
            
         }
         
      }
      
   }
   
   __term_thread(papp);
   
   // allow C-runtime to cleanup, and exit the thread
   // _endthreadex(nExitCode);
      
}

void CLASS_DECL_mac __term_thread(::base::application * papp, HINSTANCE hInstTerm)
{
   
   
}



namespace mac
{
   

   
   
   thread::thread(::base::application * papp) :
   element(papp),
   message_queue(papp),//,
   m_evFinish(papp, FALSE, TRUE),
   ::thread(NULL),
   m_mutexUiPtra(papp)
   {
      m_evFinish.SetEvent();
      m_pThreadParams = NULL;
      m_pfnThreadProc = NULL;
      
      
      CommonConstruct();
      
      
   }
   
   
   
   
   void thread::construct(__THREADPROC pfnThreadProc, LPVOID pParam)
   {
      m_evFinish.SetEvent();
      m_pfnThreadProc = pfnThreadProc;
      m_pThreadParams = pParam;
      
      CommonConstruct();
   }
   
   
   void thread::CommonConstruct()
   {
      m_ptimera      = NULL;
      m_puiptra      = NULL;
      m_puiMain      = NULL;
      m_puiActive    = NULL;
      
      //      m_peventReady  = NULL;
      
      //      m_pmapHDC      = NULL;
      //    m_pmapHGDIOBJ  = NULL;
      
      m_nDisablePumpCount  = 0;
      
      m_bAutoDelete = TRUE;
      m_bRun = false;
      
      //      m_pmapHDC = new hdc_map;
      //    m_pmapHGDIOBJ = new hgdiobj_map;
      //      m_frameList.Construct(offsetof(frame_window, m_pNextFrameWnd));
      m_ptimera = canew(::user::interaction::timer_array(get_app()));
      m_puiptra = canew(::user::interaction_ptr_array(get_app()));
      
      m_hThread = NULL;
      
   }
   
   
   thread::~thread()
   {

     
   }
   
   
   void * thread::get_os_data() const
   {
      
      return m_hThread;
      
   }
   
   
   int_ptr thread::get_os_int() const
   {
      
      return m_nID;
      
   }
   
   
   sp(::user::interaction) thread::SetMainWnd(sp(::user::interaction) pui)
   {
      ::user::interaction * puiPrevious = m_puiMain;
      m_puiMain  = pui;
      return puiPrevious;
   }
   
   void thread::add(sp(::user::interaction) pui)
   {
      single_lock sl(&m_mutexUiPtra, TRUE);
      m_puiptra->add(pui);
   }
   
   void thread::remove(::user::interaction * pui)
   {
      if(pui == NULL)
         return;
      if(GetMainWnd() == pui)
      {
         SetMainWnd(NULL);
      }
      single_lock sl(&m_mutexUiPtra, TRUE);
      if(m_puiptra != NULL)
      {
         m_puiptra->remove(pui);
         m_puiptra->remove(pui->m_pui);
         m_puiptra->remove(pui->m_pimpl);
      }
      sl.unlock();
      if(m_ptimera != NULL)
      {
         m_ptimera->unset(pui);
         m_ptimera->unset(pui->m_pui);
         m_ptimera->unset(pui->m_pimpl);
      }
      
      try
      {
         if(MAC_THREAD(pui->m_pthread.m_p) == this)
         {
            pui->m_pthread = NULL;
         }
      }
      catch(...)
      {
      }
      try
      {
         if(pui->m_pimpl != NULL && pui->m_pimpl != pui)
         {
            if(MAC_THREAD(pui->m_pimpl->m_pthread.m_p) == this)
            {
               pui->m_pimpl->m_pthread = NULL;
            }
         }
      }
      catch(...)
      {
      }
      try
      {
         if(pui->m_pui != NULL && pui->m_pui != pui)
         {
            if(MAC_THREAD(pui->m_pui->m_pthread.m_p) == this)
            {
               pui->m_pui->m_pthread = NULL;
            }
         }
      }
      catch(...)
      {
      }
   }
   
   ::count thread::get_ui_count()
   {
      single_lock sl(&m_mutexUiPtra, TRUE);
      return m_puiptra->get_count();
   }
   
   sp(::user::interaction) thread::get_ui(int32_t iIndex)
   {
      single_lock sl(&m_mutexUiPtra, TRUE);
      return m_puiptra->element_at(iIndex);
   }
   
   void thread::set_timer(sp(::user::interaction) pui, uint_ptr nIDEvent, UINT nEllapse)
   {
      if(m_spuiMessage.is_null())
      {
         return;
      }
      m_ptimera->set(pui, nIDEvent, nEllapse);
      single_lock sl(&m_ptimera->m_mutex, TRUE);
      int32_t iMin = 100;
      for(int32_t i = 0; i < m_ptimera->m_timera.get_count(); i++)
      {
         if(m_ptimera->m_timera.element_at(i)->m_uiElapse < natural(iMin))
         {
            iMin = m_ptimera->m_timera.element_at(i)->m_uiElapse;
         }
      }
      sl.unlock();
      if(m_spuiMessage->IsWindow())
      {
         m_spuiMessage->SetTimer((uint_ptr)-2, iMin, NULL);
      }
   }
   
   void thread::unset_timer(sp(::user::interaction) pui, uint_ptr nIDEvent)
   {
      m_ptimera->unset(pui, nIDEvent);
   }
   
   void thread::set_auto_delete(bool bAutoDelete)
   {
      m_bAutoDelete = bAutoDelete;
   }
   
   void thread::set_run(bool bRun)
   {
      m_bRun = bRun;
   }
   
   event & thread::get_finish_event()
   {
      return m_evFinish;
   }
   
   bool thread::get_run()
   {
      return m_bRun;
   }
   
   sp(::user::interaction) thread::get_active_ui()
   {
      return m_puiActive;
   }
   
   sp(::user::interaction) thread::set_active_ui(sp(::user::interaction) pui)
   {
      ::user::interaction * puiPrevious = m_puiActive;
      m_puiActive = pui;
      return puiPrevious;
   }
   
   void thread::step_timer()
   {
   
      if(m_ptimera == NULL)
         return;
      
      m_ptimera->check();
      
   }
   
   bool thread::on_run_step()
   {
   
      step_timer();
     
      
      ::base::application * pappThis1 = dynamic_cast < ::base::application * > (this);

      ::base::application * pappThis2 = dynamic_cast < ::base::application * > (m_pimpl.m_p);
      
      m_pimpl->m_dwAlive = m_dwAlive = ::get_tick_count();
      
      if(pappThis1 != NULL)
      {

         pappThis1->m_dwAlive = m_dwAlive;
         
      }
      
      if(pappThis2 != NULL)
      {
      
         pappThis2->m_dwAlive = m_dwAlive;
         
      }
       
       return true;
      
   }
   
   
   bool thread::begin(int32_t epriority, uint_ptr nStackSize, uint32_t dwCreateFlags, LPSECURITY_ATTRIBUTES lpSecurityAttrs)
   {
      if(!create_thread(epriority, dwCreateFlags, nStackSize, lpSecurityAttrs))
      {
         Delete();
         return false;
      }
      //VERIFY(SetThreadPriority(epriority));
      //if (!(dwCreateFlags & CREATE_SUSPENDED))
      //{
      // ENSURE(ResumeThread() != (DWORD)-1);
      //}
      return true;
   }
   
   
   bool thread::create_thread(int32_t epriority, uint32_t dwCreateFlagsParam, uint_ptr nStackSize, LPSECURITY_ATTRIBUTES lpSecurityAttrs)
   {
      
      uint32_t dwCreateFlags = dwCreateFlagsParam;
      
      if(epriority != ::core::scheduling_priority_normal)
      {
   dwCreateFlags |= CREATE_SUSPENDED;
      }
      
      ENSURE(m_hThread == NULL);  // already created?
      
      // setup startup structure for thread initialization
      ___THREAD_STARTUP * pstartup = new ___THREAD_STARTUP;
      pstartup->bError = FALSE;
      pstartup->pThread = this;
      pstartup->m_pthread = NULL;
      //      startup.hEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);
      //    startup.hEvent2 = ::CreateEvent(NULL, TRUE, FALSE, NULL);
      pstartup->dwCreateFlags = dwCreateFlags;
      /*      if (startup.hEvent == NULL || startup.hEvent2 == NULL)
       {
       TRACE(::ca2::trace::category_AppMsg, 0, "Warning: CreateEvent failed in thread::create_thread.\n");
       if (startup.hEvent != NULL)
       ::CloseHandle(startup.hEvent);
       if (startup.hEvent2 != NULL)
       ::CloseHandle(startup.hEvent2);
       return FALSE;
       }*/
      
      m_hThread = ::create_thread(lpSecurityAttrs, nStackSize, (DWORD (__stdcall *)(LPVOID)) &::__thread_entry, pstartup, dwCreateFlags | CREATE_SUSPENDED, &m_nID);
      
      if (m_hThread == NULL)
         return FALSE;
      
      // start the thread just for ca2 API initialization
      VERIFY(ResumeThread() != (DWORD)-1);
      pstartup->hEvent.wait();
      
      // if created suspended, suspend it until resume thread wakes it up
      //if (dwCreateFlags & CREATE_SUSPENDED)
      //VERIFY(::SuspendThread(m_hThread) != (DWORD)-1);
      
      // if error during startup, shut things down
      if (pstartup->bError)
      {
         m_hThread->wait();
         m_hThread = NULL;
         return FALSE;
      }
      
      // allow thread to continue, once resumed (it may already be resumed)
      pstartup->hEvent2.set_event();
      
      if(epriority != ::core::scheduling_priority_normal)
      {
         
         //VERIFY(set_thread_priority(epriority));
         
         if (!(dwCreateFlagsParam & CREATE_SUSPENDED))
         {
            //ENSURE(ResumeThread() != (DWORD)-1);
         }
         
      }
      
      return TRUE;
   }
   
   void thread::Delete()
   {
      
      // delete thread if it is auto-deleting
      if(m_bAutoDelete)
      {
         
         if(m_pappDelete != NULL)
            m_pappDelete.release();
         
         m_evFinish.SetEvent();
         
         m_pimpl.release();
         
      }
      else
      {
         m_hThread = 0;
         
         m_evFinish.SetEvent();
         
      }
      
   }
   
   
   bool thread::PreInitInstance()
   {
      
      return true;
      
   }
   
   
   bool thread::initialize_instance()
   {
      
      ASSERT_VALID(this);
      
      return true;   // by default enter run loop
   }
   
   // main running routine until thread exits
   int32_t thread::run()
   {
      
      ASSERT_VALID(this);
      
      // for tracking the idle time state
      WINBOOL bIdle = TRUE;
      LONG lIdleCount = 0;
      
      // acquire and dispatch messages until a WM_QUIT message is received.
      MESSAGE msg;
      

      
      while(m_bRun)
      {
         
         
         // phase1: check to see if we can do idle work
         while (bIdle && !::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
         {

            
            // call on_idle while in bIdle state
            if (!on_idle(lIdleCount++))
               bIdle = FALSE; // assume "no idle" state
            
            m_pimpl->on_run_step();
            
            try
            {
               if(!m_pimpl->verb())
                  goto stop_run;
            }
            catch(::exit_exception & e)
            {
               
               throw e;
               
            }
            catch(::exception::exception & e)
            {
               
               if(!Application.on_run_exception(e))
                  throw exit_exception(get_app());
               
            }
            catch(...)
            {
            }
            
         }
         
         // phase2: pump messages while available
         do
         {
            
            
            // pump message, but quit on WM_QUIT
            if (!pump_message())
            {
               try
               {
                  return exit();
               }
               catch(...)
               {
                  return -1;
               }
            }
            
            // reset "no idle" state after pumping "normal" message
            if (is_idle_message(&msg))
            {
               bIdle = TRUE;
               lIdleCount = 0;
            }
            
            m_puser->on_run_step();
            
         }
         while (::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE) != FALSE);

         
      }
   stop_run:
      
      return 0;
   }
   
   void thread::delete_temp()
   {
      
      //      m_pmapHGDIOBJ->delete_temp();
      //    m_pmapHDC->delete_temp();
      //window::DeleteTempMap();
      
   }
   
   
   int32_t thread::exit_instance()
   {
      ASSERT_VALID(this);
      
      
      try
      {
         if(m_puiptra != NULL)
         {
            single_lock sl(&m_mutexUiPtra, TRUE);
            sp(::user::interaction_ptr_array) puiptra = m_puiptra;
            m_puiptra = NULL;
            for(int32_t i = 0; i < puiptra->get_size(); i++)
            {
               ::user::interaction * pui = puiptra->element_at(i);
               if(pui->m_pthread != NULL)
               {
                  if(MAC_THREAD(pui->m_pthread.m_p) == this || MAC_THREAD(pui->m_pthread->m_pimpl.m_p) == MAC_THREAD(m_pimpl.m_p))
                  {
                     pui->m_pthread = NULL;
                  }
               }
            }
            sl.unlock();
         }
      }
      catch(...)
      {
      }
      
      try
      {
         ::user::interaction::timer_array * ptimera = m_ptimera;
         m_ptimera = NULL;
         delete ptimera;
      }
      catch(...)
      {
      }
      
      
      
      int32_t nResult = (int32_t)window::GetCurrentMessage()->wParam;  // returns the value from PostQuitMessage
      return nResult;
   }
   
   bool thread::on_idle(LONG lCount)
   {
      ASSERT_VALID(this);
      
#if defined(DEBUG) && !defined(_AFX_NO_DEBUG_CRT)
      // check ca2 API's allocator (before idle)
//      if (_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) & _CRTDBG_CHECK_ALWAYS_DF)
  //       ASSERT(__check_memory());
#endif
      
      if(lCount <= 0 && m_puiptra != NULL)
      {
         for(int32_t i = 0; i < m_puiptra->get_count(); i++)
         {
            sp(::user::interaction) pui = m_puiptra->element_at(i);
            try
            {
               if (pui != NULL && pui->IsWindowVisible())
               {
                  /*AfxCallWndProc(pMainWnd, pMainWnd->get_handle(),
                   WM_IDLEUPDATECMDUI, (WPARAM)TRUE, 0);*/
                  pui->send_message(WM_IDLEUPDATECMDUI, (WPARAM)TRUE, 0);
                  /*   pui->SendMessageToDescendants(WM_IDLEUPDATECMDUI,
                   (WPARAM)TRUE, 0, TRUE, TRUE);*/
               }
            }
            catch(...)
            {
            }
         }
         
         
         // send WM_IDLEUPDATECMDUI to the main window
         /*
          ::user::interaction* pMainWnd = GetMainWnd();
          if (pMainWnd != NULL && pMainWnd->IsWindowVisible())
          {
          AfxCallWndProc(pMainWnd, pMainWnd->get_handle(),
          WM_IDLEUPDATECMDUI, (WPARAM)TRUE, 0);*/
         /* pMainWnd->SendMessage(WM_IDLEUPDATECMDUI, (WPARAM)TRUE, 0);
          pMainWnd->SendMessageToDescendants(WM_IDLEUPDATECMDUI,
          (WPARAM)TRUE, 0, TRUE, TRUE);
          }
          */
         // send WM_IDLEUPDATECMDUI to all frame windows
         /* linux
          
          
          if (pFrameWnd->m_nShowDelay > SW_HIDE)
          pFrameWnd->ShowWindow(pFrameWnd->m_nShowDelay);
          pFrameWnd->m_nShowDelay = -1;
          }
          pFrameWnd = pFrameWnd->m_pNextFrameWnd;
          }*/
      }
      else if (lCount >= 0)
      {
      }
      
#if defined(DEBUG) && !defined(_AFX_NO_DEBUG_CRT)
      // check ca2 API's allocator (after idle)
//      if (_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) & _CRTDBG_CHECK_ALWAYS_DF)
  //       ASSERT(__check_memory());
#endif
      
      return lCount < 0;  // nothing more to do if lCount >= 0
   }
   
   ::message::e_prototype thread::GetMessagePrototype(UINT uiMessage, UINT uiCode)
   {
      UNREFERENCED_PARAMETER(uiMessage);
      UNREFERENCED_PARAMETER(uiCode);
      return ::message::PrototypeNone;
   }
   
   
   void thread::DispatchThreadMessageEx(signal_details * pobj)
   {
      SCAST_PTR(::message::base, pbase, pobj);
      if(pbase->m_uiMessage == WM_APP + 1984 && pbase->m_wparam == 77)
      {
         ::smart_pointer < ::user::message > spmessage(pbase->m_lparam);
         spmessage->send();
         pbase->m_bRet = true;
         return;
      }
      /*   const __MSGMAP* pMessageMap; pMessageMap = GetMessageMap();
       const __MSGMAP_ENTRY* lpEntry;
       
       for ( pMessageMap already init'ed *//*; pMessageMap->pfnGetBaseMap != NULL;
                                              pMessageMap = (*pMessageMap->pfnGetBaseMap)())
                                              {
                                              // Note: catch not so common but fatal mistake!!
                                              //       // BEGIN_MESSAGE_MAP(CMyThread, CMyThread)
                                              
                                              ASSERT(pMessageMap != (*pMessageMap->pfnGetBaseMap)());
                                              if (pMsg->message < 0xC000)
                                              {
                                              // constant window message
                                              if ((lpEntry = AfxFindMessageEntry(pMessageMap->lpEntries,
                                              pMsg->message, 0, 0)) != NULL)
                                              goto LDispatch;
                                              }
                                              else
                                              {
                                              // registered windows message
                                              lpEntry = pMessageMap->lpEntries;
                                              while ((lpEntry = AfxFindMessageEntry(lpEntry, 0xC000, 0, 0)) != NULL)
                                              {
                                              UINT* pnID = (UINT*)(lpEntry->nSig);
                                              ASSERT(*pnID >= 0xC000);
                                              // must be successfully registered
                                              if (*pnID == pMsg->message)
                                              goto LDispatch;
                                              lpEntry++;      // keep looking past this one
                                              }
                                              }
                                              }
                                              return FALSE;
                                              
                                              LDispatch:
                                              union MessageMapFunctions mmf;
                                              mmf.pfn = lpEntry->pfn;
                                              
                                              // always posted, so return value is meaningless
                                              
                                              (this->*mmf.pfn_THREAD)(pMsg->wParam, pMsg->lParam);*/
      
      LRESULT lresult;
      SignalPtrArray signalptra;
      m_signala.GetSignalsByMessage(signalptra, pbase->m_uiMessage, 0, 0);
      for(int32_t i = 0; i < signalptra.get_size(); i++)
      {
         Signal & signal = *signalptra[i];
         class ::signal * psignal = signal.m_psignal;
         ::message::e_prototype eprototype = signal.m_eprototype;
         if(eprototype == ::message::PrototypeNone)
         {
            //::message::base base(get_app());
            pbase->m_psignal = psignal;
            lresult = 0;
            //base.set(pmsg->message, pmsg->wParam, pmsg->lParam, lresult);
            psignal->emit(pbase);
            if(pbase->m_bRet)
               return;
         }
         break;
      }
      pbase->m_bRet = true;
   }
   
   void thread::pre_translate_message(signal_details * pobj)
   {
      ASSERT_VALID(this);
      return AfxInternalPreTranslateMessage(pobj);
   }
   
   void thread::ProcessWndProcException(::exception::base* e, signal_details * pobj)
   {
      return AfxInternalProcessWndProcException(e, pobj);
   }
   
   __STATIC inline WINBOOL IsEnterKey(signal_details * pobj)
   {
      SCAST_PTR(::message::base, pbase, pobj);
      return pbase->m_uiMessage == WM_KEYDOWN && pbase->m_wparam == VK_RETURN;
   }
   
   __STATIC inline WINBOOL IsButtonUp(signal_details * pobj)
   {
      SCAST_PTR(::message::base, pbase, pobj);
      return pbase->m_uiMessage == WM_LBUTTONUP;
   }
   
   void thread::ProcessMessageFilter(int32_t code, signal_details * pobj)
   {
      
      if(pobj == NULL)
         return;   // not handled
      
   }
   
   /////////////////////////////////////////////////////////////////////////////
   // Access to GetMainWnd() & m_pActiveWnd
   
   sp(::user::interaction) thread::GetMainWnd()
   {
      if (m_puiActive != NULL)
         return m_puiActive;    // probably in-place active
      
      // when not inplace active, just return main window
      if (m_puiMain != NULL)
         return m_puiMain;
      
      return System.get_active_guie();
   }
   
   /////////////////////////////////////////////////////////////////////////////
   // thread implementation helpers
   
   bool thread::pump_message()
   {
      try
      {
         MESSAGE msg;
         if(!::GetMessage(&msg, NULL, 0, 0))
         {
            TRACE(::core::trace::category_AppMsg, 1, "thread::pump_message - Received WM_QUIT.\n");
            m_nDisablePumpCount++; // application must die
            // Note: prevents calling message loop things in 'exit_instance'
            // will never be decremented
            return FALSE;
         }
         
         if(m_nDisablePumpCount != 0)
         {
            TRACE(::core::trace::category_AppMsg, 0, "Error: thread::pump_message called when not permitted.\n");
            ASSERT(FALSE);
         }
         
         __trace_message("pump_message", &msg);
         
         if(msg.message != WM_KICKIDLE)
         {
            {
               ::smart_pointer < ::message::base > spbase;
               
               spbase = get_base(&msg);
               
               if(m_puser != NULL)
               {
                  m_puser->pre_translate_message(spbase);
                  if(spbase->m_bRet)
                     return TRUE;
               }
               
               System.pre_translate_message(spbase);
               if(spbase->m_bRet)
                  return TRUE;
               
               if(!Application.is_system())
               {
                  Application.pre_translate_message(spbase);
                  if(spbase->m_bRet)
                     return TRUE;
               }
               
               __pre_translate_message(spbase);
               if(spbase->m_bRet)
                  return TRUE;
               
            }
            {
               //             ::TranslateMessage(&msg);
               //             ::DispatchMessage(&msg);
            }
         }
         return TRUE;
      }
      catch(const ::exception::exception & e)
      {
         if(on_run_exception((::exception::exception &) e))
            return TRUE;
         // get_app() may be it self, it is ok...
         if(App(get_app()).final_handle_exception((::exception::exception & ) e))
            return TRUE;
         return FALSE;
      }
   }
   
   
   /////////////////////////////////////////////////////////////////////////////
   // thread diagnostics
   
#ifdef DEBUG
   void thread::assert_valid() const
   {
      command_target::assert_valid();
   }
   void thread::dump(dump_context & dumpcontext) const
   {
      command_target::dump(dumpcontext);
   }
#endif
   
   bool thread::post_message(sp(::user::interaction) pguie, UINT uiMessage, WPARAM wparam, lparam lparam)
   {
      //      if(m_hThread == NULL)
      //       return false;
      ::user::message * pmessage = new ::user::message;
      pmessage->m_pui       = pguie;
      pmessage->m_uiMessage   = uiMessage;
      pmessage->m_wparam      = wparam;
      pmessage->m_lparam      = lparam;
      return post_thread_message(WM_APP + 1984, 77, (LPARAM) pmessage) != FALSE;
   }
   
   
   bool thread::on_run_exception(::exception::exception & e)
   {
      UNREFERENCED_PARAMETER(e);
      return false;
   }
   
   
   void thread::message_handler(signal_details * pobj)
   {
      SCAST_PTR(::message::base, pbase, pobj);
      // special message which identifies the window as using AfxWndProc
//      if(pbase->m_uiMessage == WM_QUERYAFXWNDPROC)
  //    {
    //     pbase->set_lresult(0);
      //   return;
      //}
      
      // all other messages route through message ::collection::map
      ::window * pwindow = pbase->m_pwnd->get_wnd();
      
      /*      ASSERT(pwindow == NULL || MAC_WINDOW(pwindow)->get_handle() == pbase->m_hwnd);
       
       if(pwindow == NULL || MAC_WINDOW(pwindow)->get_handle() != pbase->m_hwnd)
       {
       pbase->set_lresult(::DefWindowProc(pbase->m_hwnd, pbase->m_uiMessage, pbase->m_wparam, pbase->m_lparam));
       return;
       }*/
      
      __trace_message("message_handler", pobj);
      
      // Catch exceptions thrown outside the scope of a callback
      // in debug builds and warn the ::fontopus::user.
      try
      {
         
         // special case for WM_INITDIALOG
         rect rectOld;
         DWORD dwStyle = 0;
         if(pbase->m_uiMessage == WM_INITDIALOG)
            __pre_init_dialog(pwindow, &rectOld, &dwStyle);
         
         // delegate to object's message_handler
         if(pwindow->m_pui != NULL && pwindow->m_pui != pwindow)
         {
            pwindow->m_pui->message_handler(pobj);
         }
         else
         {
            pwindow->message_handler(pobj);
         }
         
         // more special case for WM_INITDIALOG
         if(pbase->m_uiMessage == WM_INITDIALOG)
            __post_init_dialog(pwindow, rectOld, dwStyle);
      }
      catch(const ::exception::exception & e)
      {
         
         if(App(get_app()).on_run_exception((::exception::exception &) e))
            return;
         
         if(App(get_app()).final_handle_exception((::exception::exception &) e))
            return;
         
         __post_quit_message(-1);
         
         pbase->set_lresult(-1);
         
         return;
         
      }
      catch(::exception::base * pe)
      {
         
         AfxProcessWndProcException(pe, pbase);
         
         TRACE(::core::trace::category_AppMsg, 0, "Warning: Uncaught exception in message_handler (returning %ld).\n", pbase->get_lresult());
         
         pe->Delete();
         
      }
      
   }
   
   
   bool thread::set_thread_priority(int32_t epriority)
   {

      return ::SetThreadPriority(m_hThread, ::get_scheduling_priority_normal()) != FALSE;
      
   }
   
   
   int32_t thread::get_thread_priority()
   {
      ::GetThreadPriority(m_hThread);
      return ::get_scheduling_priority_normal();
      
   }
   
   
   DWORD thread::ResumeThread()
   {
      //throw not_implemented(get_app());
      ASSERT(m_hThread != NULL);
      return ::ResumeThread(m_hThread);
   }
   DWORD thread::SuspendThread()
   {
      throw not_implemented(get_app());
      //   ASSERT(m_hThread != NULL);
      // return ::SuspendThread(m_hThread);
      
   }
   
   
   bool thread::post_thread_message(UINT message, WPARAM wParam, lparam lParam)
   {
      
      return ::PostThreadMessage(m_nID, message, wParam, lParam);
      
   }
   
   
   void thread::set_os_data(void * pvoidOsData)
   {
      
      m_hThread = (HTHREAD) pvoidOsData;
      
   }
   
   
   void thread::set_os_int(int_ptr iData)
   {
      throw not_implemented(get_app());
      //m_nThreadID = (dword_ptr) iData;
   }
   
   void thread::message_queue_message_handler(signal_details * pobj)
   {
   }
   
   
   
   
   int32_t thread::thread_entry(::mac::thread_startup * pstartup)
   {
      
      ASSERT(pstartup != NULL);
      //      ASSERT(pstartup->pThreadState != NULL);
      ASSERT(pstartup->m_pthread != NULL);
      //ASSERT(!pstartup->bError);

      ::mac::thread* pThread = dynamic_cast < ::mac::thread * > (pstartup->m_pthread);
      
//      ::application* papp = dynamic_cast < ::application * > (get_app());
      m_evFinish.ResetEvent();
      install_message_handling(pThread);
      m_puser->install_message_handling(pThread);
      
//      ::window threadWnd;
      
//      m_ptimera            = new ::user::interaction::timer_array(get_app());
//      m_puiptra            = new user::interaction_ptr_array;
      m_bRun               = true;
      
      m_ptimera->m_pbaseapp    = m_pbaseapp;
      m_puiptra->m_pbaseapp    = m_pbaseapp;
      
      
      if(!create_message_queue(get_app(), ""))
         return -1;
      
      
      
      
      return 0;   // not reached
   }
   
   int32_t thread::main()
   {
      
      if(!m_puser->PreInitInstance())
      {
         return 0;
      }
      
      // first -- check for simple worker thread
      DWORD nResult = 0;
      if (m_pfnThreadProc != NULL)
      {
         nResult = (*m_pfnThreadProc)(m_pThreadParams);
      }
      // else -- check for thread with message loop
      else if (!m_puser->initialize_instance())
      {
         try
         {
            nResult = exit();
         }
         catch(...)
         {
            nResult = (DWORD) -1;
         }
      }
      else
      {
         // will stop after PostQuitMessage called
         ASSERT_VALID(this);
         //         se_translator::attach();
      run:
         try
         {
            try
            {
               m_bReady = true;
               m_puser->m_bReady = true;
               m_bRun = true;
               m_puser->m_bRun = true;
               nResult = m_puser->run();
            }
            catch(const ::exception::exception & e)
            {
               if(on_run_exception((::exception::exception &) e))
                  goto run;
               if(App(get_app()).final_handle_exception((::exception::exception & ) e))
                  goto run;
               try
               {
                  nResult = exit();
               }
               catch(...)
               {
                  nResult = (DWORD) -1;
               }
            }
         }
         catch(...)
         {
         }
         // let se_translator run undefinetely
         //se_translator::detach();
      }
      
      
      
      return 0;   // not reached
   }
   
   int32_t thread::thread_term(int32_t nResult)
   {
      try
      {
         destroy_message_queue();
      }
      catch(...)
      {
      }
      
      try
      {
         // cleanup and shutdown the thread
         //         threadWnd.Detach();
         __end_thread(m_pbaseapp, nResult);
      }
      catch(...)
      {
      }
      return nResult;
   }
   
 
   
	unsigned long MillisecondCounter ()
	{
		timeval tv;
		gettimeofday(&tv, 0);
		return tv.tv_sec * 1000 + tv.tv_usec / 1000;
	}

   
} // namespace mac




WINBOOL CLASS_DECL_mac AfxInternalPumpMessage();
LRESULT CLASS_DECL_mac AfxInternalProcessWndProcException(::exception::base*, const MESSAGE* pMsg);
void AfxInternalPreTranslateMessage(signal_details * pobj);

void CLASS_DECL_mac __init_thread()
{
   
   
}









