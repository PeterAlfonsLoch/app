#include "framework.h"
#include <ddeml.h>  // for MSGF_DDEMGR




uint32_t __thread_entry(void * pparam)
{
   UINT uiRet = 0;

   try
   {

      ::thread_startup * pstartup = (::thread_startup *) pparam;
      
      ASSERT(pstartup != NULL);
      ASSERT(pstartup->m_pthread != NULL);
      ASSERT(pstartup->m_pthreadimpl != NULL);
      ASSERT(!pstartup->m_bError);

      ::thread_impl * pthreadimpl = pstartup->m_pthreadimpl;

      ::CoInitializeEx(NULL,COINIT_MULTITHREADED);

      pthreadimpl->::exception::translator::attach();

      try
      {

         __init_thread();

      }
      catch(::exception::base *)
      {

         pstartup->m_bError = TRUE;

         pstartup->m_event.set_event();

         __end_thread(pthreadimpl->m_pbaseapp,(UINT)-1,FALSE);

         ASSERT(FALSE);  // unreachable

      }


      ::multithreading::__node_on_init_thread(::GetCurrentThread(),pthreadimpl->m_puser);


      pthreadimpl->thread_entry(pstartup);

      HANDLE hEvent2 = pstartup->m_event2.get_os_data();

      // allow the creating thread to return from thread::create_thread
      pstartup->m_event.set_event();

      // wait for thread to be resumed
      VERIFY(::WaitForSingleObject(hEvent2,INFINITE) == WAIT_OBJECT_0);

      ::CloseHandle(hEvent2);

      int32_t n;

      try
      {

         n = pthreadimpl->m_puser->main();

      }
      catch(::exit_exception &)
      {

         Sys(pthreadimpl->get_app()).os().post_to_all_threads(WM_QUIT,0,0);

         return -1;

      }

      uiRet =  pthreadimpl->thread_term(n);


   }
   catch(...)
   {
      return -1;
   }

   return uiRet;

}


void CLASS_DECL_BASE __end_thread(sp(::base::application) papp,UINT nExitCode,bool bDelete)
{

   ::thread * pthread = ::get_thread();

   if(pthread != NULL)
   {

      ::thread_impl * pthreadimpl = pthread->m_pimpl;

      if(pthreadimpl != NULL)
      {

         ::multithreading::__node_on_term_thread(::GetCurrentThread(),pthread);

         ASSERT_VALID(pthreadimpl);

         if(bDelete)
            pthreadimpl->Delete();
         
      }

   }

   __term_thread(papp);

}


void CLASS_DECL_BASE __term_thread(sp(::base::application) papp,HINSTANCE hInstTerm)
{

   UNREFERENCED_PARAMETER(papp);

}

LRESULT CALLBACK __message_filter_hook(int32_t code,WPARAM wParam,LPARAM lParam);

__declspec(thread) HHOOK t_hHookOldMsgFilter = NULL;

void CLASS_DECL_BASE __init_thread()
{
   {
      ASSERT(t_hHookOldMsgFilter == NULL);
      t_hHookOldMsgFilter = ::SetWindowsHookEx(WH_MSGFILTER,__message_filter_hook,NULL,::GetCurrentThreadId());
   }
}

namespace windows
{


   thread::thread(sp(::base::application) papp):
      element(papp),
      message_queue(papp),//,
      //m_evFinish(FALSE, TRUE)
      ::thread(NULL),
      m_evFinish(papp),
      m_mutexUiPtra(papp)

   {
         m_evFinish.SetEvent();
         m_pThreadParams = NULL;
         m_pfnThreadProc = NULL;

         CommonConstruct();
      }

   void thread::construct(__THREADPROC pfnThreadProc,LPVOID pParam)
   {
      m_evFinish.SetEvent();
      m_pfnThreadProc = pfnThreadProc;
      m_pThreadParams = pParam;

      CommonConstruct();
   }

   void thread::CommonConstruct()
   {
      m_bCreatingMessageWindow = false;
      m_ptimera      = NULL;
      m_puiptra      = NULL;
      m_puiMain      = NULL;
      m_puiActive    = NULL;


      m_nDisablePumpCount  = 0;

      // no HTHREAD until it is created
      m_hThread = NULL;
      m_nThreadID = 0;

      m_nDisablePumpCount = 0;
      m_bAutoDelete  = TRUE;

      m_ptimera = canew(::user::interaction::timer_array(get_app()));
      m_puiptra = canew(::user::interaction_ptr_array(get_app()));

   }


   thread::~thread()
   {

   }


   void * thread::get_os_data() const
   {

      return (void *)m_hThread;

   }


   int_ptr thread::get_os_int() const
   {

      return m_nThreadID;

   }


   HANDLE thread::item() const
   {
      return m_hThread;
   }

   bool thread::begin(int32_t epriority,uint_ptr nStackSize,uint32_t dwCreateFlags,LPSECURITY_ATTRIBUTES lpSecurityAttrs)
   {

      if(!create_thread(epriority,dwCreateFlags,nStackSize,lpSecurityAttrs))
      {
         Delete();
         return false;
      }

      return true;

   }

   sp(::user::interaction) thread::SetMainWnd(sp(::user::interaction) pui)
   {
      sp(::user::interaction) puiPrevious = m_puiMain;
      m_puiMain  = pui;
      return puiPrevious;
   }

   void thread::add(sp(::user::interaction) pui)
   {
      single_lock sl(&m_mutexUiPtra,TRUE);
      if(m_puiptra != NULL)
      {
         m_puiptra->add(pui);
      }
   }

   void thread::remove(::user::interaction * pui)
   {

      if(pui == NULL)
         return;

      single_lock sl(&m_mutexUiPtra,TRUE);

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
         if(NODE_THREAD(pui->m_pthread.m_p) == this)
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
            if(NODE_THREAD(pui->m_pimpl->m_pthread.m_p) == this)
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
            if(NODE_THREAD(pui->m_pui->m_pthread.m_p) == this)
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

      single_lock sl(&m_mutexUiPtra,TRUE);

      return m_puiptra->get_count();

   }


   ::user::interaction * thread::get_ui(index iIndex)
   {

      single_lock sl(&m_mutexUiPtra,TRUE);

      return m_puiptra->element_at(iIndex);

   }


   void thread::_001PostCreateMessageWindow()
   {

      post_thread_message(WM_USER + 123);

   }


   void thread::_001OnCreateMessageWindow(signal_details * pobj)
   {

      if(m_bCreatingMessageWindow)
         return;

      if(m_spuiMessage.is_set() && m_spuiMessage->IsWindow())
         return;

      keeper < bool > keepCreating(&m_bCreatingMessageWindow,true,false,true);

      try
      {

         if(!create_message_queue(get_app(),""))
            return;

      }
      catch(...)
      {
         return;
      }

      if(m_spuiMessage->IsWindow())
      {
         single_lock sl(&m_ptimera->m_mutex,TRUE);
         int32_t iMin = 100;
         for(int32_t i = 0; i < m_ptimera->m_timera.get_count(); i++)
         {
            if(m_ptimera->m_timera.element_at(i)->m_uiElapse < natural(iMin))
            {
               iMin = m_ptimera->m_timera.element_at(i)->m_uiElapse;
            }
         }
         sl.unlock();
         m_spuiMessage->SetTimer((uint_ptr)-2,iMin,NULL);
      }

   }


   void thread::set_timer(sp(::user::interaction) pui,uint_ptr nIDEvent,UINT nEllapse)
   {

      m_ptimera->set(pui,nIDEvent,nEllapse);

      if(!m_bCreatingMessageWindow && m_spuiMessage.is_null())
      {
         _001PostCreateMessageWindow();
      }

   }

   void thread::unset_timer(sp(::user::interaction) pui,uint_ptr nIDEvent)
   {
      m_ptimera->unset(pui,nIDEvent);
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
      sp(::user::interaction) puiPrevious = m_puiActive;
      m_puiActive = pui;
      return puiPrevious;
   }

   void thread::step_timer()
   {
      if(m_ptimera == NULL)
         return;
      m_ptimera->check();
   }


   void thread::Delete()
   {
      if(m_bAutoDelete)
      {
         try
         {
            if(m_pappDelete != NULL)
               delete m_pappDelete;
         }
         catch(...)
         {
         }
      }
      else
      {
         try
         {
            m_hThread = NULL;
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
            m_bRun = false;
         }
         catch(...)
         {
         }
      }
      try
      {
         if(m_p != NULL)
         {
            ::thread * pthread = thread::m_p;
            if(pthread != NULL && pthread->m_pbReady != NULL)
            {
               *pthread->m_pbReady = true;
            }
         }
      }
      catch(...)
      {
      }
      try
      {
         if(m_pbReady != NULL)
         {
            *m_pbReady = true;
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

      if(m_bAutoDelete)
      {
         // delete thread if it is auto-deleting
         //pthread->smart_pointer < thread >::m_p = NULL;
         m_p.release();
         // delete_this();
      }
      else
      {
         try
         {
            m_p->m_bRun = false;
         }
         catch(...)
         {
         }
      }
   }

   /////////////////////////////////////////////////////////////////////////////
   // thread default implementation

   bool thread::pre_init_instance()
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
      bool bIdle = TRUE;
      LONG lIdleCount = 0;

      // acquire and dispatch messages until a WM_QUIT message is received.
      MSG msg;
      while(m_bRun)
      {
         // phase1: check to see if we can do idle work
         while(bIdle && !::PeekMessage(&msg,NULL,0,0,PM_NOREMOVE))
         {
            // call on_idle while in bIdle state
            if(!on_idle(lIdleCount++))
            {
               Sleep(10);
               lIdleCount = 0;
               bIdle = FALSE; // assume "no idle" state
            }



            if(!m_p->on_run_step())
               goto stop_run;

         }

         // phase2: pump messages while available
         while(::PeekMessage(&msg,NULL,0,0,PM_NOREMOVE) != FALSE)
         {

            // pump message, but quit on WM_QUIT
            if(!m_bRun || !pump_message())
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
            //if (is_idle_message(&m_msgCur))
            if(is_idle_message(&msg))
            {
               bIdle = TRUE;
               lIdleCount = 0;
            }

            if(!m_p->on_run_step())
               goto stop_run;

         }

         bIdle = true;

      }
   stop_run:

      return 0;
   }

   bool thread::is_idle_message(signal_details * pobj)
   {
      return __internal_is_idle_message(pobj);
   }

   bool thread::is_idle_message(LPMSG lpmsg)
   {
      return __internal_is_idle_message(lpmsg);
   }


   int32_t thread::exit_instance()
   {


      ASSERT_VALID(this);


      try
      {
         if(m_puiptra != NULL)
         {
            single_lock sl(&m_mutexUiPtra,TRUE);
            ::user::interaction_ptr_array * puiptra = m_puiptra;
            m_puiptra = NULL;
            for(int32_t i = 0; i < puiptra->get_size(); i++)
            {
               sp(::user::interaction) pui = puiptra->element_at(i);
               if(pui->m_pthread != NULL)
               {
                  if(NODE_THREAD(pui->m_pthread.m_p) == this
                     || NODE_THREAD(pui->m_pthread->m_p.m_p) == NODE_THREAD(m_p.m_p)
                     || NODE_THREAD(pui->m_pthread.m_p) == NODE_THREAD(m_p.m_p))
                  {
                     pui->m_pthread = NULL;
                  }
               }
            }
            delete puiptra;
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



      //int32_t nResult = (int32_t)__get_current_message()->wParam;  // returns the value from PostQuitMessage
      return m_iReturnCode;
   }

   bool thread::on_idle(LONG lCount)
   {



      ASSERT_VALID(this);

#if defined(DEBUG) && !defined(___NO_DEBUG_CRT)
      // check core API's allocator (before idle)
      if(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) & _CRTDBG_CHECK_ALWAYS_DF)
         ASSERT(__check_memory());
#endif

      if(lCount <= 0 && m_puiptra != NULL)
      {
         for(int32_t i = 0; i < m_puiptra->get_count();)
         {
            sp(::user::interaction) pui = m_puiptra->element_at(i);
            bool bOk = false;
            try
            {

               bOk = pui != NULL && pui->IsWindowVisible();
            }
            catch(...)
            {
            }
            if(!bOk)
            {
               m_puiptra->remove_at(i);
            }
            else
            {
               try
               {
                  pui->send_message(WM_IDLEUPDATECMDUI,(WPARAM)TRUE);
               }
               catch(...)
               {

               }
               i++;
            }
         }


      }
      else if(lCount >= 0)
      {
      }

#if defined(DEBUG) && !defined(___NO_DEBUG_CRT)
      // check core API's allocator (after idle)
      if(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) & _CRTDBG_CHECK_ALWAYS_DF)
         ASSERT(__check_memory());
#endif



      return lCount < 0;  // nothing more to do if lCount >= 0
   }

   message::e_prototype thread::GetMessagePrototype(UINT uiMessage,UINT uiCode)
   {
      UNREFERENCED_PARAMETER(uiMessage);
      UNREFERENCED_PARAMETER(uiCode);
      return message::PrototypeNone;
   }


   void thread::dispatch_thread_message(signal_details * pobj)
   {
      SCAST_PTR(::message::base,pbase,pobj);
      if(!pbase->m_bRet && pbase->m_uiMessage == WM_APP + 1984 && pbase->m_wparam == 77)
      {
         smart_pointer < ::user::message > spmessage(pbase->m_lparam);
         spmessage->send();
         pbase->m_uiMessage   = 0;    // ssshhhh.... - self-healing - sh...
         pbase->m_wparam      = 0;    // ssshhhh.... - self-healing - sh...
         pbase->m_bRet        = true;
         return;
      }
      /*   const __MSGMAP* pMessageMap; pMessageMap = GetMessageMap();
      const __MSGMAP_ENTRY* lpEntry;

      for (/* pMessageMap already init'ed *//*; pMessageMap->pfnGetBaseMap != NULL;
      pMessageMap = (*pMessageMap->pfnGetBaseMap)())
      {
      // Note: catch not so common but fatal mistake!!
      //       // BEGIN_MESSAGE_MAP(CMyThread, CMyThread)

      ASSERT(pMessageMap != (*pMessageMap->pfnGetBaseMap)());
      if (pMsg->message < 0xC000)
      {
      // constant window message
      if ((lpEntry = ::core::FindMessageEntry(pMessageMap->lpEntries,
      pMsg->message, 0, 0)) != NULL)
      goto LDispatch;
      }
      else
      {
      // registered windows message
      lpEntry = pMessageMap->lpEntries;
      while ((lpEntry = ::core::FindMessageEntry(lpEntry, 0xC000, 0, 0)) != NULL)
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
      m_signala.GetSignalsByMessage(signalptra,pbase->m_uiMessage,0,0);
      for(int32_t i = 0; i < signalptra.get_size(); i++)
      {
         Signal & signal = *signalptra[i];
         ::signal * psignal = signal.m_psignal;
         message::e_prototype eprototype = signal.m_eprototype;
         if(eprototype == message::PrototypeNone)
         {
            //message::base base(get_app());
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
      return __internal_pre_translate_message(pobj);
   }

   void thread::ProcessWndProcException(::exception::base* e,signal_details * pobj)
   {
      return __internal_process_wnd_proc_exception(e,pobj);
   }

   __STATIC inline bool IsEnterKey(signal_details * pobj)
   {
      SCAST_PTR(::message::base,pbase,pobj);
      return pbase->m_uiMessage == WM_KEYDOWN && pbase->m_wparam == VK_RETURN;
   }

   __STATIC inline bool IsButtonUp(signal_details * pobj)
   {
      SCAST_PTR(::message::base,pbase,pobj);
      return pbase->m_uiMessage == WM_LBUTTONUP;
   }

   void thread::process_message_filter(int32_t code,signal_details * pobj)
   {

      if(pobj == NULL)
         return;   // not handled

      SCAST_PTR(::message::base,pbase,pobj);

      sp(::user::frame_window) pTopFrameWnd;
      sp(::user::interaction) pMainWnd;
      sp(::user::interaction) pMsgWnd;
      switch(code)
      {
      case MSGF_DDEMGR:
         // Unlike other WH_MSGFILTER codes, MSGF_DDEMGR should
         //  never call the next hook.
         // By returning FALSE, the message will be dispatched
         //  instead (the default behavior).
         return;

      case MSGF_MENU:
         pMsgWnd = pbase->m_pwnd;
         if(pMsgWnd != NULL)
         {
            pTopFrameWnd = pMsgWnd->GetTopLevelFrame();
            if(pTopFrameWnd != NULL && pTopFrameWnd->IsTracking() &&
               pTopFrameWnd->m_bHelpMode)
            {
               //pMainWnd = __get_main_window();
               if((GetMainWnd() != NULL) && (IsEnterKey(pbase) || IsButtonUp(pbase)))
               {
                  //                  pMainWnd->SendMessage(WM_COMMAND, ID_HELP);
                  pbase->m_bRet = true;
                  return;
               }
            }
         }
         // fall through...

      case MSGF_DIALOGBOX:    // handles message boxes as well.
         //pMainWnd = __get_main_window();
         if(code == MSGF_DIALOGBOX && m_puiActive != NULL &&
            pbase->m_uiMessage >= WM_KEYFIRST && pbase->m_uiMessage <= WM_KEYLAST)
         {
         }
         break;
      }
      // default to not handled
   }

   /////////////////////////////////////////////////////////////////////////////
   // Access to GetMainWnd() & m_pActiveWnd

   sp(::user::interaction) thread::GetMainWnd()
   {
      if(m_puiActive != NULL)
         return m_puiActive;    // probably in-place active

      // when not inplace active, just return main window
      if(m_puiMain != NULL)
         return m_puiMain;

      return System.get_active_guie();
   }

   /////////////////////////////////////////////////////////////////////////////
   // thread implementation helpers

   bool thread::pump_message()
   {
      try
      {
         MSG msg;
         if(!::GetMessage(&msg,NULL,0,0))
         {
            TRACE(::core::trace::category_AppMsg,1,"thread::pump_message - Received WM_QUIT.\n");
            m_nDisablePumpCount++; // application must die
            // Note: prevents calling message loop things in 'exit_instance'
            // will never be decremented
            return FALSE;
         }
         //m_message = msg;
         //m_p->m_message = msg;

         if(m_nDisablePumpCount != 0)
         {
            TRACE(::core::trace::category_AppMsg,0,"Error: thread::pump_message called when not permitted.\n");
            ASSERT(FALSE);
         }

         __trace_message("pump_message",&msg);

         if(msg.message != WM_KICKIDLE)
         {

            {

               smart_pointer < message::base > spbase;

               spbase = get_base(&msg);

               if(spbase.is_set())
               {

                  try
                  {
                     if(m_p != NULL)
                     {
                        m_p->pre_translate_message(spbase);
                        if(spbase->m_bRet)
                           return TRUE;
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
                        if(m_pbaseapp != NULL)
                        {
                           try
                           {
                              if(m_pbaseapp->m_pbasesystem != NULL)
                              {
                                 m_pbaseapp->m_pbasesystem->pre_translate_message(spbase);
                                 if(spbase->m_bRet)
                                    return TRUE;
                                 /*                                 try
                                 {
                                 if(m_pbaseapp->m_pbasesystem->m_pcube != NULL)
                                 {
                                 m_pbaseapp->m_pbasesystem->m_pcubeInterface->pre_translate_message(spbase);
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
                           if(m_pbaseapp->m_pbasesession != NULL)
                           {
                              try
                              {
                                 m_pbaseapp->m_pbasesession->pre_translate_message(spbase);
                                 if(spbase->m_bRet)
                                    return TRUE;
                              }
                              catch(...)
                              {
                              }
                              /*                              try
                              {
                              if(m_pbaseapp->m_pbasesession->m_pbergedge != NULL)
                              {
                              m_pbaseapp->m_pbasesession->m_pbergedgeInterface->pre_translate_message(spbase);
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
                        if(!m_pbaseapp->is_system() && m_pbaseapp->is_session())
                        {
                           m_pbaseapp->pre_translate_message(spbase);
                           if(spbase->m_bRet)
                              return TRUE;
                        }
                     }
                     catch(...)
                     {
                     }

                  }



                  __pre_translate_message(spbase);
                  if(spbase->m_bRet)
                     return TRUE;

                  spbase.release();
               }
            }
            {
               ::TranslateMessage(&msg);
               ::DispatchMessage(&msg);
            }
         }
         return TRUE;
      }
      catch(exit_exception & e)
      {
         throw e;
      }
      catch(const ::exception::exception & e)
      {
         if(on_run_exception((::exception::exception &) e))
            return TRUE;
         // get_app() may be it self, it is ok...
         if(App(get_app()).final_handle_exception((::exception::exception &) e))
            return TRUE;
         return FALSE;
      }
      catch(...)
      {
         return FALSE;
      }
   }


   /////////////////////////////////////////////////////////////////////////////
   // thread diagnostics


   void thread::assert_valid() const
   {
      command_target::assert_valid();
   }
   void thread::dump(dump_context & dumpcontext) const
   {
      command_target::dump(dumpcontext);

      dumpcontext << "m_pThreadParams = " << m_pThreadParams;
      dumpcontext << "\nm_pfnThreadProc = " << (void *)m_pfnThreadProc;
      dumpcontext << "\nm_bAutoDelete = " << m_bAutoDelete;
      dumpcontext << "\nm_hThread = " << (void *)m_hThread;
      dumpcontext << "\nm_nThreadID = " << m_nThreadID;
#ifdef DEBUG
      //    dumpcontext << "\nm_nDisablePumpCount = " << pState->m_nDisablePumpCount;
#endif
      if(__get_thread() == this)
         dumpcontext << "\nm_pMainWnd = " << m_puiMain.m_p;

      dumpcontext << "\nm_msgCur = {";
      /*      dumpcontext << "\n\toswindow = " << (void *)pState->m_msgCur.hwnd;
      dumpcontext << "\n\tmessage = " << (UINT)pState->m_msgCur.message;
      dumpcontext << "\n\twParam = " << (UINT)pState->m_msgCur.wParam;
      dumpcontext << "\n\tlParam = " << (void *)pState->m_msgCur.lParam;
      dumpcontext << "\n\ttime = " << (uint_ptr) pState->m_msgCur.time;
      dumpcontext << "\n\tpt = " << point(pState->m_msgCur.pt);*/
      dumpcontext << "\n}";

      dumpcontext << "\nm_pThreadParams = " << m_pThreadParams;
      dumpcontext << "\nm_pfnThreadProc = " << (void *)m_pfnThreadProc;
      //dumpcontext << "\nm_ptCursorLast = " << pState->m_ptCursorLast;
      //dumpcontext << "\nm_nMsgLast = " << pState->m_nMsgLast;

      dumpcontext << "\n";
   }


   bool thread::post_message(sp(::user::interaction) pui,UINT uiMessage,WPARAM wparam,lparam lparam)
   {
      if(m_hThread == NULL)
         return false;
      ::user::message * pmessage = new ::user::message;
      pmessage->m_pui       = pui;
      pmessage->m_uiMessage   = uiMessage;
      pmessage->m_wparam      = wparam;
      pmessage->m_lparam      = lparam;
      return post_thread_message(WM_APP + 1984,77,(LPARAM)pmessage) != FALSE;
   }


   bool thread::on_run_exception(::exception::exception & e)
   {
      UNREFERENCED_PARAMETER(e);
      return false;
   }


   void thread::message_handler(signal_details * pobj)
   {
      SCAST_PTR(::message::base,pbase,pobj);
      // special message which identifies the window as using __window_procedure
      //      if(pbase->m_uiMessage == WM_QUERYAFXWNDPROC)
      //    {
      //     pbase->set_lresult(0);
      //   return;
      // }

      // all other messages route through message map
      ::window_sp pwindow = pbase->m_pwnd->get_wnd();

      ASSERT(pwindow == NULL || pwindow == pbase->m_pwnd->m_pimpl);

      if(pwindow == NULL || pwindow != pbase->m_pwnd->m_pimpl)
      {
         pbase->set_lresult(::DefWindowProc(pbase->m_pwnd->get_safe_handle(),pbase->m_uiMessage,pbase->m_wparam,pbase->m_lparam));
         return;
      }

      __trace_message("message_handler",pobj);

      // Catch exceptions thrown outside the scope of a callback
      // in debug builds and warn the ::fontopus::user.
      try
      {

         // special case for WM_INITDIALOG
         rect rectOld;
         uint32_t dwStyle = 0;
         if(pbase->m_uiMessage == WM_INITDIALOG)
            __pre_init_dialog(pwindow,&rectOld,&dwStyle);

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
            __post_init_dialog(pwindow,rectOld,dwStyle);
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
         __process_window_procedure_exception(pe,pbase);
         TRACE(::core::trace::category_AppMsg,0,"Warning: Uncaught exception in message_handler (returning %ld).\n",pbase->get_lresult());
         pe->Delete();
      }
   run:;
      //      pThreadState->m_lastSentMsg = oldState;
   }


   thread::operator HANDLE() const
   {

      return this == NULL ? NULL : m_hThread;

   }

   bool thread::set_thread_priority(int32_t iCa2Priority)
   {

      ASSERT(m_hThread != NULL);

      int32_t nPriority = (int)get_os_thread_priority(iCa2Priority);


      bool bOk = ::SetThreadPriority(m_hThread,get_os_thread_priority(iCa2Priority)) != FALSE;

      if(!bOk)
      {
         uint32_t dwLastError = ::GetLastError();
         ::OutputDebugString("thread::SetThreadPriority LastError = " + ::str::from(dwLastError));
      }

      return bOk;

   }


   int32_t thread::get_thread_priority()
   {

      ASSERT(m_hThread != NULL);

      int32_t nPriority = ::GetThreadPriority(m_hThread);

      int32_t iCa2Priority = ::get_os_thread_scheduling_priority(nPriority);

      return iCa2Priority;

   }


   uint32_t thread::ResumeThread()
   {

      ASSERT(m_hThread != NULL);

      return ::ResumeThread(m_hThread);

   }


   /*

   DWORD thread::SuspendThread()
   {

   ASSERT(m_hThread != NULL);

   return ::SuspendThread(m_hThread);

   }

   */


   bool thread::post_thread_message(UINT message,WPARAM wParam,lparam lParam)
   {

      if(m_hThread == NULL)
         return false;

      return ::PostThreadMessageA(m_nThreadID,message,wParam,lParam) != FALSE;

   }


   void thread::set_os_data(void * pvoidOsData)
   {
      m_hThread = (HANDLE)pvoidOsData;
   }

   void thread::set_os_int(int_ptr iData)
   {
      m_nThreadID = (DWORD)iData;
   }

   void thread::message_queue_message_handler(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }


   CLASS_DECL_BASE ::thread * get_thread()
   {
      ::windows::thread * pwinthread = __get_thread();
      if(pwinthread == NULL)
         return NULL;
      return pwinthread->m_p;
   }



   int32_t thread::thread_entry(::core::thread_startup * pstartup)
   {

      ___THREAD_STARTUP* pStartup = (___THREAD_STARTUP*)pstartup;
      ASSERT(pStartup != NULL);
      //      ASSERT(pStartup->pThreadState != NULL);
      ASSERT(pStartup->pThread != NULL);
      ASSERT(!pStartup->bError);

      ::windows::thread* pThread = pStartup->pThread;

      //      sp(::base::application) papp = (get_app());
      m_evFinish.ResetEvent();
      install_message_handling(pThread);
      m_p->install_message_handling(pThread);

      IGUI_WIN_MSG_LINK(WM_USER + 123,pThread,pThread,&thread::_001OnCreateMessageWindow);

      return 0;   // not reached

   }

   int32_t thread::main()
   {

      /*      ___THREAD_STARTUP* pStartup = (___THREAD_STARTUP*)pstartup;
      ASSERT(pStartup != NULL);
      ASSERT(pStartup->pThreadState != NULL);
      ASSERT(pStartup->pThread != NULL);
      ASSERT(!pStartup->bError);*/

      if(!m_p->pre_init_instance())
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
      else if(!m_p->initialize_instance())
      {
         try
         {
            nResult = exit();
         }
         catch(...)
         {
            nResult = (DWORD)-1;
         }
      }
      else
      {
         // will stop after PostQuitMessage called
         ASSERT_VALID(this);
         // let upper framework attach translator    
         //         translator::attach();
      run:
         try
         {
            m_bReady = true;
            m_p->m_bReady = true;
            m_bRun = true;
            m_p->m_bRun = true;
            nResult = m_p->run();
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
            try
            {
               nResult = exit();
            }
            catch(...)
            {
               nResult = (DWORD)-1;
            }
         }
         catch(...)
         {
         }
         // let translator run undefinetely
         //translator::detach();
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
         //         threadWnd.detach();
         __end_thread((m_pbaseapp),nResult);
      }
      catch(...)
      {
      }


      return nResult;
   }


   /**
   * \file		src/lib/pal/windows/thread_windows.hpp
   * \brief	Platform independent threads and synchronization objects (windows version)
   */

   ///  \brief		starts thread on first call
   void thread::start()
   {
      ::ResumeThread(item());
   }


   void thread::wait()
   {
      ::WaitForSingleObject(item(),INFINITE);
   }

   ///  \brief		waits for signaling the thread for a specified time
   ///  \param		duration time period to wait for thread
   ///  \return	result of waiting action as defined in wait_result
   wait_result thread::wait(const duration & duration)
   {
      DWORD timeout = duration.is_pos_infinity() ? INFINITE : static_cast<DWORD>(duration.total_milliseconds());
      return wait_result((uint32_t) ::WaitForSingleObject(item(),timeout));
   }

   ///  \brief		sets thread priority
   ///  \param		new priority
   void thread::set_priority(int32_t priority)
   {
      if(::SetThreadPriority(item(),priority) == 0)
         throw runtime_error(get_app(),"Thread::set_priority: Couldn't set thread priority.");
   }

   ///  \brief		gets thread priority
   ///  \param		priority
   int32_t thread::priority()
   {
      return ::GetThreadPriority(item());
   }


   bool thread::has_message()
   {
      ASSERT(GetCurrentThreadId() == m_nThreadID);
      MSG msg;
      return ::PeekMessage(&msg,NULL,0,0,PM_NOREMOVE) != FALSE;
   }


} // namespace windows





LRESULT CALLBACK __message_filter_hook(int32_t code,WPARAM wParam,LPARAM lParam)
{
   thread* pthread;
   //   if (afxContextIsDLL || (code < 0 && code != MSGF_DDEMGR) || (pthread = dynamic_cast < thread * > (::windows::get_thread())) == NULL)
   if((code < 0 && code != MSGF_DDEMGR) || (pthread = dynamic_cast < thread * > (::windows::get_thread())) == NULL)
   {
      return ::CallNextHookEx(t_hHookOldMsgFilter,code,wParam,lParam);
   }
   ASSERT(pthread != NULL);
   smart_pointer < message::base > spbase;
   spbase = pthread->get_base((LPMSG)lParam);
   pthread->process_message_filter(code,spbase);
   LRESULT lresult = spbase->m_bRet ? 1 : 0;
   return lresult;
}

__STATIC bool CLASS_DECL_BASE IsHelpKey(LPMSG lpMsg)
// return TRUE only for non-repeat F1 keydowns.
{
   return lpMsg->message == WM_KEYDOWN &&
      lpMsg->wParam == VK_F1 &&
      !(HIWORD(lpMsg->lParam) & KF_REPEAT) &&
      GetKeyState(VK_SHIFT) >= 0 &&
      GetKeyState(VK_CONTROL) >= 0 &&
      GetKeyState(VK_MENU) >= 0;
}

__STATIC inline bool IsEnterKey(LPMSG lpMsg)
{
   return lpMsg->message == WM_KEYDOWN && lpMsg->wParam == VK_RETURN;
}

__STATIC inline bool IsButtonUp(LPMSG lpMsg)
{
   return lpMsg->message == WM_LBUTTONUP;
}


