#include "framework.h"
#include <ddeml.h>  // for MSGF_DDEMGR





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
      message_queue(papp),
      ::thread_impl(papp)
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


      m_nDisablePumpCount = 0;
      m_bAutoDelete  = TRUE;

      m_ptimera = canew(::user::interaction::timer_array(get_app()));
      m_puiptra = canew(::user::interaction_ptr_array(get_app()));

   }


   thread::~thread()
   {

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
            m_hthread = NULL;
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
         if(m_puser != NULL)
         {
            ::thread * pthread = thread::m_puser;
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
         m_puser.release();
         // delete_this();
      }
      else
      {
         try
         {
            m_puser->m_bRun = false;
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



            if(!m_puser->on_run_step())
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

            if(!m_puser->on_run_step())
               goto stop_run;

         }

         bIdle = true;

      }
   stop_run:

      return 0;
   }


   int32_t thread::exit_instance()
   {


      m_iReturnCode = thread_impl::exit_instance();


      return m_iReturnCode;

   }


   bool thread::on_idle(LONG lCount)
   {

      return ::thread_impl::on_idle(lCount);

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
      dumpcontext << "\nm_hThread = " << (void *)m_hthread;
      dumpcontext << "\nm_nThreadID = " << m_uiThread;
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




   bool thread::on_run_exception(::exception::exception & e)
   {
      UNREFERENCED_PARAMETER(e);
      return false;
   }


   void thread::message_handler(signal_details * pobj)
   {

      SCAST_PTR(::message::base,pbase,pobj);

      ::window_sp pwindow = pbase->m_pwnd->get_wnd();

      ASSERT(pwindow == NULL || pwindow == pbase->m_pwnd->m_pimpl);

      if(pwindow == NULL || pwindow != pbase->m_pwnd->m_pimpl)
      {
         pbase->set_lresult(::DefWindowProc(pbase->m_pwnd->get_safe_handle(),pbase->m_uiMessage,pbase->m_wparam,pbase->m_lparam));
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

         __process_window_procedure_exception(pe,pbase);

         TRACE(::core::trace::category_AppMsg,0,"Warning: Uncaught exception in message_handler (returning %ld).\n",pbase->get_lresult());

         pe->Delete();

      }

   run:;
      
   }


   bool thread::set_thread_priority(int32_t iCa2Priority)
   {

      ASSERT(m_hthread != NULL);

      int32_t nPriority = (int)get_os_thread_priority(iCa2Priority);


      bool bOk = ::SetThreadPriority(m_hthread,get_os_thread_priority(iCa2Priority)) != FALSE;

      if(!bOk)
      {
         uint32_t dwLastError = ::GetLastError();
         ::OutputDebugString("thread::SetThreadPriority LastError = " + ::str::from(dwLastError));
      }

      return bOk;

   }


   int32_t thread::get_thread_priority()
   {

      ASSERT(m_hthread != NULL);

      int32_t nPriority = ::GetThreadPriority(m_hthread);

      int32_t iCa2Priority = ::get_os_thread_scheduling_priority(nPriority);

      return iCa2Priority;

   }


   uint32_t thread::ResumeThread()
   {

      ASSERT(m_hthread != NULL);

      return ::ResumeThread(m_hthread);

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
      ASSERT(GetCurrentThreadId() == m_uiThread);
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


