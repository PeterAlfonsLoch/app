#include "framework.h"
#include <ddeml.h>  // for MSGF_DDEMGR


__declspec(thread) HHOOK t_hHookOldMsgFilter = NULL;

LRESULT CALLBACK __message_filter_hook(int32_t code,WPARAM wParam,LPARAM lParam);

void CLASS_DECL_BASE __init_thread()
{

   ASSERT(t_hHookOldMsgFilter == NULL);

   t_hHookOldMsgFilter = ::SetWindowsHookEx(WH_MSGFILTER,__message_filter_hook,NULL,::GetCurrentThreadId());


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





   bool thread::pre_init_instance()
   {
      return true;
   }

   bool thread::initialize_instance()
   {
      ASSERT_VALID(this);

      return true;   // by default enter run loop
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
      if(get_thread() == m_puser)
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
      ::ResumeThread(m_hthread);
   }


   void thread::wait()
   {
      ::WaitForSingleObject(m_hthread,INFINITE);
   }

   ///  \brief		waits for signaling the thread for a specified time
   ///  \param		duration time period to wait for thread
   ///  \return	result of waiting action as defined in wait_result
   wait_result thread::wait(const duration & duration)
   {
      DWORD timeout = duration.is_pos_infinity() ? INFINITE : static_cast<DWORD>(duration.total_milliseconds());
      return wait_result((uint32_t) ::WaitForSingleObject(m_hthread,timeout));
   }

   ///  \brief		sets thread priority
   ///  \param		new priority
   void thread::set_priority(int32_t priority)
   {
      if(::SetThreadPriority(m_hthread,priority) == 0)
         throw runtime_error(get_app(),"Thread::set_priority: Couldn't set thread priority.");
   }

   ///  \brief		gets thread priority
   ///  \param		priority
   int32_t thread::priority()
   {
      return ::GetThreadPriority(m_hthread);
   }


   bool thread::has_message()
   {
      MSG msg;
      return ::PeekMessage(&msg,NULL,0,0,PM_NOREMOVE) != FALSE;
   }


} // namespace windows





LRESULT CALLBACK __message_filter_hook(int32_t code,WPARAM wParam,LPARAM lParam)
{
   ::thread * pthread;
   if((code < 0 && code != MSGF_DDEMGR) || ((pthread = ::get_thread()) == NULL))
   {
      return ::CallNextHookEx(t_hHookOldMsgFilter,code,wParam,lParam);
   }
   ASSERT(pthread != NULL);
   smart_pointer < message::base > spbase;
   spbase = pthread->get_base((LPMSG)lParam);
   if(spbase.is_null())
      return ::CallNextHookEx(t_hHookOldMsgFilter,code,wParam,lParam);
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



void __term_threading()
{

   if(t_hHookOldMsgFilter != NULL)
   {
      ::UnhookWindowsHookEx(t_hHookOldMsgFilter);
      t_hHookOldMsgFilter = NULL;
   }

}
