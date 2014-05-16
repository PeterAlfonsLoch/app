#include "framework.h"
//#include <process.h>    // for _beginthreadex and _endthreadex
//#include <ddeml.h>  // for MESSAGEF_DDEMGR

/**
 * \file		src/lib/pal/src/linux/thread_linux.cpp
 * \brief	Platform independent threads and synchronization objects (linux version)
 * \author	Thomas Nass
 */

//#include "internal_linux.hpp"

#include <fcntl.h>

//namespace gen { namespace pal {

//namespace internal
//{


struct ___THREAD_STARTUP : ::mac::thread_startup
{
   ::mac::thread* pThread;    // thread for new thread
   DWORD dwCreateFlags;    // thread creation flags
   bool bError;    // TRUE if error during startup
};

/*
 WINBOOL PeekMessage(
 LPMESSAGE lpMsg,
 oswindow hWnd,
 UINT wMsgFilterMin,
 UINT wMsgFilterMax,
 UINT wRemoveMsg)
 {
 
 return TRUE;
 }
 
 WINBOOL GetMessage(
 LPMESSAGE lpMsg,
 oswindow hWnd,
 UINT wMsgFilterMin,
 UINT wMsgFilterMax)
 {
 
 return TRUE;
 }
 */
namespace mac
{
   class thread;
} // namespace mac

WINBOOL CLASS_DECL_mac AfxInternalPumpMessage();
LRESULT CLASS_DECL_mac AfxInternalProcessWndProcException(::exception::base*, const MESSAGE* pMsg);
WINBOOL AfxInternalPreTranslateMessage(MESSAGE* pMsg);
WINBOOL AfxInternalIsIdleMessage(MESSAGE* pMsg);
__STATIC void CLASS_DECL_mac __pre_init_dialog(::user::interaction * pWnd, LPRECT lpRectOld, DWORD* pdwStyleOld);
__STATIC void CLASS_DECL_mac __post_init_dialog(::user::interaction * pWnd, const RECT& rectOld, DWORD dwStyleOld);

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


namespace mac
{
   
   thread_pointer < ::thread > t_pthread;

   
   CLASS_DECL_mac ::thread * __get_thread()
   {
      
      return t_pthread;
      
   }
   
   
   CLASS_DECL_mac void __set_thread(::thread * pthread)
   {

      t_pthread = pthread;
      
   }
   
   
} // namespace mac







CLASS_DECL_mac void AfxInternalProcessWndProcException(::exception::base*, signal_details * pobj)
{
   SCAST_PTR(::message::base, pbase, pobj);
   if (pbase->m_uiMessage == WM_CREATE)
   {
      pbase->set_lresult(-1);
      return;  // just fail
   }
   else if (pbase->m_uiMessage == WM_PAINT)
   {
      // force validation of ::window to prevent getting WM_PAINT again
      //      ValidateRect(pbase->m_hwnd, NULL);
      pbase->set_lresult(0);
      return;
   }
   return;   // sensible default for rest of commands
}

CLASS_DECL_mac void AfxProcessWndProcException(::exception::base* e, signal_details * pobj)
{
   ::thread *pThread = App(pobj->get_app()).GetThread();
   if( pThread )
      return pThread->ProcessWndProcException( e, pobj );
   else
      return AfxInternalProcessWndProcException( e, pobj );
}

void AfxInternalPreTranslateMessage(signal_details * pobj)
{
   try
   {
      SCAST_PTR(::message::base, pbase, pobj);
      
      //   ASSERT_VALID(this);
      
      ::thread *pThread = dynamic_cast < ::thread * > (::mac::get_thread());
      if( pThread )
      {
         // if this is a thread-message, short-circuit this function
         if (pbase->m_pwnd == NULL)
         {
            pThread->DispatchThreadMessageEx(pobj);
            if(pobj->m_bRet)
               return;
         }
      }
      
      // walk from target to main ::window
      ::user::interaction* pMainWnd = pThread->GetMainWnd();
      if(pMainWnd != NULL && pMainWnd->IsWindow())
      {
         pMainWnd->WalkPreTranslateTree(pobj);
         if(pobj->m_bRet)
            return;
      }
      
      // in case of modeless dialogs, last chance route through main
      //   ::ca2::window's accelerator table
      ::window * pWnd = pbase->m_pwnd->get_wnd();
      if (pMainWnd != NULL)
      {
         if (pWnd != NULL && MAC_WINDOW(pWnd)->GetTopLevelParent() != pMainWnd)
         {
            pMainWnd->pre_translate_message(pobj);
            if(pobj->m_bRet)
               return;
         }
      }
      user::interaction_ptr_array wnda = Sys(pThread->get_app()).frames();
      for(int32_t i = 0; i < wnda.get_count(); i++)
      {
         ::user::interaction * pui = &wnda[i];
         try
         {
            if(pui != NULL)
            {
               if(pui->m_pui != NULL)
               {
                  if(pui->m_pui != pMainWnd
                     && pui != pMainWnd)
                  {
                     pui->m_pui->pre_translate_message(pobj);
                     if(pobj->m_bRet)
                        return;
                  }
               }
               else
               {
                  if(pui != pMainWnd)
                  {
                     pui->pre_translate_message(pobj);
                     if(pobj->m_bRet)
                        return;
                  }
               }
            }
         }
         catch(...)
         {
         }
      }
   }
   catch(...)
   {
   }
   
   // no special processing
}

void __cdecl __pre_translate_message(signal_details * pobj)
{
   ::thread *pThread = App(pobj->get_app()).GetThread();
   if( pThread )
      return pThread->pre_translate_message( pobj );
   else
      return AfxInternalPreTranslateMessage( pobj );
}

WINBOOL AfxInternalIsIdleMessage(signal_details * pobj)
{
   SCAST_PTR(::message::base, pbase, pobj);
   // Return FALSE if the message just dispatched should _not_
   // cause on_idle to be run.  Messages which do not usually
   // affect the state of the ::fontopus::user interface and happen very
   // often are checked for.
   
   if(pbase == NULL)
      return FALSE;
   
   // redundant WM_MOUSEMOVE and WM_NCMOUSEMOVE
   if (pbase->m_uiMessage == WM_MOUSEMOVE || pbase->m_uiMessage == WM_NCMOUSEMOVE)
   {
      
      return TRUE;
      
   }
   
   // WM_PAINT and WM_SYSTIMER (caret blink)
   return pbase->m_uiMessage != WM_PAINT && pbase->m_uiMessage != 0x0118;
}



WINBOOL AfxInternalIsIdleMessage(LPMESSAGE lpmsg)
{
   // Return FALSE if the message just dispatched should _not_
   // cause on_idle to be run.  Messages which do not usually
   // affect the state of the ::fontopus::user interface and happen very
   // often are checked for.
   
   if(lpmsg == NULL)
      return FALSE;
   
   // redundant WM_MOUSEMOVE and WM_NCMOUSEMOVE
   if (lpmsg->message == WM_MOUSEMOVE || lpmsg->message == WM_NCMOUSEMOVE)
   {
      
      return TRUE;
      
   }
   
   // WM_PAINT and WM_SYSTIMER (caret blink)
   return lpmsg->message != WM_PAINT && lpmsg->message != 0x0118;
}




/*thread* CLASS_DECL_mac AfxBeginThread(::base::application * papp, __THREADPROC pfnThreadProc, LPVOID pParam,
 int32_t nPriority, UINT nStackSize, DWORD dwCreateFlags,
 LPSECURITY_ATTRIBUTES lpSecurityAttrs)
 {
 ASSERT(pfnThreadProc != NULL);
 
 thread* pThread = BASE_NEW thread(papp, pfnThreadProc, pParam);
 ASSERT_VALID(pThread);
 
 if (!pThread->CreateThread(dwCreateFlags|CREATE_SUSPENDED, nStackSize,
 lpSecurityAttrs))
 {
 pThread->Delete();
 return NULL;
 }
 VERIFY(pThread->SetThreadPriority(nPriority));
 if (!(dwCreateFlags & CREATE_SUSPENDED))
 VERIFY(pThread->ResumeThread() != (DWORD)-1);
 
 return pThread;
 }*/
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
   
   void thread::set_p(::thread * p)
   {
      m_p = p;
   }
   
   /////////////////////////////////////////////////////////////////////////////
   // thread construction
   
   
   void thread::construct(__THREADPROC pfnThreadProc, LPVOID pParam)
   {
      m_evFinish.SetEvent();
      if(System.GetThread() != NULL)
      {
         m_pAppThread = MAC_THREAD(::get_thread()->m_p.m_p)->m_pAppThread;
      }
      else
      {
         m_pAppThread = NULL;
      }
      m_pfnThreadProc = pfnThreadProc;
      m_pThreadParams = pParam;
      
      CommonConstruct();
   }
   
   thread::thread(::base::application * papp) :
   element(papp),
   message_queue(papp),//,
   m_evFinish(papp, FALSE, TRUE),
   ::thread(NULL),
   m_mutexUiPtra(papp)
   {
      m_evFinish.SetEvent();
      m_pAppThread = dynamic_cast < ::thread * > (papp);
      m_pThreadParams = NULL;
      m_pfnThreadProc = NULL;
      
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
/*      if(m_puiptra != NULL)
      {
         single_lock sl(&m_mutexUiPtra, TRUE);
         ::user::interaction_ptr_array * puiptra = m_puiptra;
         m_puiptra = NULL;
         for(int32_t i = 0; i < puiptra->get_size(); i++)
         {
            ::user::interaction * pui = puiptra->element_at(i);
            if(pui->m_pthread != NULL)
            {
               try
               {
                  if(MAC_THREAD(pui->m_pthread->m_pthread) == this
                     || MAC_THREAD(pui->m_pthread->m_pthread->m_p.m_p) == MAC_THREAD(m_p.m_p)
                     || MAC_THREAD(pui->m_pthread->m_pthread) == MAC_THREAD(m_p.m_p))
                  {
                     pui->m_pthread = NULL;
                  }
               }
               catch(...)
               {
               }
            }
         }
         sl.unlock();
      }*/
      
      /*      // clean up temp objects
       pState->m_pmapHGDIOBJ->delete_temp();
       pState->m_pmapHDC->delete_temp();
       pState->m_pmapHWND->delete_temp();*/
      
/*      for(int32_t i = 0; i < m_captraDeletePool.get_count(); i++)
      {
         try
         {
            ::ca2::ca2 * pca = m_captraDeletePool[i];
            if(dynamic_cast < ::application * > (pca) == m_papp)
            {
               m_papp = NULL;
            }
         }
         catch(...)
         {
         }
      } */
      
      // free thread object
      //      if (m_hThread != NULL)
      //       CloseHandle(m_hThread);
      
     
   }
   
   
   void * thread::get_os_data() const
   {
      
      return m_hThread;
      
   }
   
   
   int_ptr thread::get_os_int() const
   {
      
      return m_nID;
      
   }
   
   
/*
 void thread::on_delete(::ca2::ca2 * p)
   {
   }
 */
   
   
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
   
   ::thread * thread::get_app_thread()
   {
      return m_pAppThread;
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

      ::base::application * pappThis2 = dynamic_cast < ::base::application * > (m_p.m_p);
      
      m_p->m_dwAlive = m_dwAlive = ::get_tick_count();
      
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
//         ::thread * pthread = dynamic_cast < ::thread * > (m_p);
         //      if(pthread->m_peventReady != NULL)
         //    {
         //     ::SetEvent((HANDLE) pthread->m_peventReady);
         // }
         //      if(m_peventReady != NULL)
         //    {
         //     ::SetEvent((HANDLE) m_peventReady);
         //}
         //pthread->::ca2::smart_pointer < ::thread >::m_p = NULL;
         m_p.release();
         //      delete_this();
      }
      else
      {
         m_hThread = 0;
         m_evFinish.SetEvent();
      }
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
            
            m_p->on_run_step();
            
            try
            {
               if(!m_p->verb())
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
            
            m_p->on_run_step();
            
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
#ifdef DEBUG
         // Check for missing LockTempMap calls
         if(m_nTempMapLock != 0)
         {
            TRACE(::core::trace::category_AppMsg, 0, "Warning: Temp ::collection::map lock count non-zero (%ld).\n", m_nTempMapLock);
         }
         LockTempMaps();
         UnlockTempMaps(-1);
#endif
      }
      catch(...)
      {
      }
      
      
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
                  if(MAC_THREAD(pui->m_pthread.m_p) == this
                     || MAC_THREAD(pui->m_pthread->m_p.m_p) == MAC_THREAD(m_p.m_p)
                     || MAC_THREAD(pui->m_pthread.m_p) == MAC_THREAD(m_p.m_p))
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
               
               if(m_p != NULL)
               {
                  m_p->pre_translate_message(spbase);
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
   
   
   CLASS_DECL_mac ::thread * get_thread()
   {
      ::thread * pthread = ::get_thread();
      if(pthread == NULL)
         return NULL;
      return MAC_THREAD(pthread->m_p.m_p);
   }
   
   
   void thread::LockTempMaps()
   {
      ++m_nTempMapLock;
   }
   WINBOOL thread::UnlockTempMaps(WINBOOL bDeleteTemp)
   {
      if (m_nTempMapLock != 0 && --m_nTempMapLock == 0)
      {
         if (bDeleteTemp)
         {
            // clean up temp objects
            //         m_pmapHGDIOBJ->delete_temp();
            //       m_pmapHDC->delete_temp();
            //  window::DeleteTempMap();
         }
         
         
         
      }
      // return TRUE if temp maps still locked
      return m_nTempMapLock != 0;
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
      m_p->install_message_handling(pThread);
      
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
      
      /*      _AFX_THREAD_STARTUP* pStartup = (_AFX_THREAD_STARTUP*)pstartup;
       ASSERT(pStartup != NULL);
       ASSERT(pStartup->pThreadState != NULL);
       ASSERT(pStartup->pThread != NULL);
       ASSERT(!pStartup->bError);*/
      
      if(!m_p->PreInitInstance())
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
      else if (!m_p->initialize_instance())
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
               m_p->m_bReady = true;
               m_bRun = true;
               m_p->m_bRun = true;
               nResult = m_p->run();
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
   
   //  \brief		starts thread on first call
   //		void thread::start ()
	//	{
   //   pthread_mutex_unlock(&startMutex_);
   //}
   //
   //		Globals g_globals;
   //
   //		inline const char *b2s(bool b) { return b ? "true" : "false"; }
   //
   //		-----------------------------------------------------------------------------------------
   //	/*	thread * ThisThread ()	// returns a pointer to the thread class of the calling thread
   //		{
   //			pthread_t myId = pthread_self();
   //			g_globals.mutex_.lock();
   //			thread * thisThread = g_globals.threadMap_[myId];
   //			if (!thisThread)
   //			{
   //				 thread must be an "external" pthread (e.g. created by a linked SIP-stack)
   //				 => get instance of ExternalThread-class from pool and add it temporarily to the global thread map
   //				if (!g_globals.externalThreadPool_.is_empty())
   //				{
   //					ExternalThread *extThread = g_globals.externalThreadPool_.front();
   //					g_globals.externalThreadPool_.pop_front();
   //					extThread->SetId(myId);
   //					g_globals.threadMap_[myId] = thisThread = extThread;
   //				}
   //				else
   //					thisThread = new ExternalThread;	// this will also set the thread ID and add it to the global thread map
   //			}
   //			g_globals.mutex_.unlock();
   //			return thisThread;
   //		}*/
   //
   //		-----------------------------------------------------------------------------------------
   ///*		FileDescWaiterThread::FileDescWaiterThread()
   //		{
   //			if ( pipe(fileDescs_) )
   //				;	// TO DO: throw
   //			int32_t flags = fcntl( fileDescs_[1],F_GETFL );
   //			fcntl( fileDescs_[1], F_SETFL, flags|O_NONBLOCK );
   //			FD_ZERO(&fdRead);
   //			FD_ZERO(&fdWrite);
   //			FD_SET(fileDescs_[0], &fdRead);
   //written_=read_=0;
   //			start();
   //		}
   //
   //		-----------------------------------------------------------------------------------------
   //		FileDescWaiterThread::~FileDescWaiterThread()
   //		{
   //			FileDescWaiterThreadCommand command(FileDescWaiterThreadCommand::terminate);
   //			write(fileDescs_[1], &command, sizeof command);
   //			pal::wait(*this);
   //			close(fileDescs_[0]);
   //			close(fileDescs_[1]);
   //						raise( SIGSEGV );
   //		}
   //
   //		-----------------------------------------------------------------------------------------
   //		unsigned FileDescWaiterThread::operator() ()
   //		{
   //			fd_evmap_t Map;
   //
   //			for ( ;; ) {	// loop can only be stopped by "terminate" command
   //				mutex_.lock();
   //				fd_set actRead	= fdRead;
   //				fd_set actWrite = fdWrite;
   //				Map 			= evSetMap;
   //				mutex_.unlock();
   //
   //				int32_t	fdHigh 	= Map.is_empty() ? fileDescs_[0] : Map.rbegin()->first;
   //				int32_t nSelect = select(fdHigh + 1, &actRead, &actWrite, 0, 0);
   //				if ( nSelect <= 0 )	// timeout: 0, error: -1
   //					continue;
   //				if ( FD_ISSET(fileDescs_[0], &actRead) ) {
   //					 read command from pipe
   //					FileDescWaiterThreadCommand command[ 5 ];
   //					int32_t rc = 0;
   //					if ( ( rc = read(fileDescs_[0], &command, 5 * sizeof( FileDescWaiterThreadCommand ) ) ) == -1 )
   //						continue;
   //					read_++;
   //					for ( uint32_t i = 0; i < ( rc/sizeof( FileDescWaiterThreadCommand ) ); i++ )
   //						if ( command[i]() == FileDescWaiterThreadCommand::terminate )
   //							return 0;
   //					if ( !--nSelect )
   //						continue;
   //				}
   //				g_globals.mutex_.lock();
   //				for ( itMap_t it=Map.begin(), ie=Map.end(); nSelect && it!=ie;  ) {
   //					int32_t fd 		= it->first;
   //					bool bRead  = FD_ISSET(fd,&actRead);
   //					bool bWrite = FD_ISSET(fd,&actWrite);
   //					if ( bRead || bWrite ) {
   //						fd_evset_t& evSet = it->second;
   //						for ( itEv_t itE=evSet.begin(), itEnd=evSet.end(); itE != itEnd; ) {
   //							FileDescEvent *ev = *itE++;
   //							if ( !(ev->read_ ^ bRead) ) {	//	both true or both false
   //								ev->set();
   //								ev->set_active(false);	// prevent call to RemoveEvent for event already erased here
   //								evSet.erase(ev);
   //							}
   //						}
   //						mutex_.lock();
   //						if ( bRead ) {
   //							FD_CLR(fd, &fdRead);
   //							--nSelect;
   //						}
   //						if ( bWrite ) {
   //							FD_CLR(fd, &fdWrite);
   //							--nSelect;
   //						}
   //						++it;	// must increment before erase
   //						if ( evSet.is_empty() )
   //							evSetMap.erase(fd);
   //						mutex_.unlock();
   //					} else
   //						++it;
   //				}
   //				g_globals.mutex_.unlock();
   //			}
   //		}
   //
   //		-----------------------------------------------------------------------------------------
   //		void FileDescWaiterThread::ModifyEvent_(FileDescEvent *event, bool add /*= true*/ /*)
   //		{
   //			int32_t	fd = event->fileDesc_;
   //
   //			mutex_.lock();
   //			if ( add ) {
   //				evSetMap[fd].insert(event);
   //				FD_SET(fd, event->read_ ? &fdRead : &fdWrite);
   //			} else {
   //				itMap_t it = evSetMap.find(fd);
   //				if ( it != evSetMap.end() ) {
   //					fd_evset_t& evSet = it->second;
   //					evSet.erase(event);
   //					unsigned nRead = 0;
   //					for ( itEv_t itE=evSet.begin(); itE!=evSet.end(); ++itE )
   //						nRead += (*itE)->read_;
   //					if ( !nRead )
   //						FD_CLR(fd, &fdRead);
   //					if ( evSet.size() == nRead )
   //						FD_CLR(fd, &fdWrite);
   //					if ( evSet.is_empty() )
   //						evSetMap.erase(fd);
   //				}
   //			}
   //			mutex_.unlock();
   //
   //			 trigger thread
   //			FileDescWaiterThreadCommand command(FileDescWaiterThreadCommand::events_changed);
   //			int32_t tries=30;
   //			while ( tries > 0 ) {
   //				if ( ::write(fileDescs_[1], &command, sizeof command) < 0 )
   //				{
   //					tries--;
   //					usleep(100);
   //					if ( errno == EAGAIN && tries == 0 )  {
   //						void *mythis = this;
   //						char buffer[1000];
   //						int32_t rc = read(fileDescs_[0],buffer,1000);
   //						strcpy(0,"coredump");;
   //					}
   //				}
   //				else
   //					tries = 0;
   //			}
   //			written_++;
   //			if ( written_ - read_ > 200 )
   //				strcpy(0,"coredump");
   //		}
   //
   //	} // namespace internal*/
   //
   ///*	wait_result wait (WaitableItem & waitableItem, const boost::posix_time::time_duration& duration/*=InfiniteTime*//*)
   //	{
   //		return internal::ThisThread()->wait(waitableItem, duration);
   //	}
   //
   //	wait_result wait (size_t numberOfItems, WaitableItem * waitableItems[], const boost::posix_time::time_duration& duration/*=InfiniteTime*//*, bool waitForAll /*= false*/ /*)
   //	{
   //		return internal::ThisThread()->wait(numberOfItems, waitableItems, duration, waitForAll);
   //	}
   //
   //	void ExternalThread::endWait()
   //	{
   //		internal::g_globals.threadMap_.erase(thread_);
   //		internal::g_globals.externalThreadPool_.push_back(this);
   //	}
   //
   //	thread::thread()
   //		: WaitableItem(false, false), isMainThread_(false), isExternalThread_(false)
   //	{
   //		pthread_attr_t Attributes;
   //
   //		if (   pthread_attr_init(&Attributes)
   //			|| pthread_attr_setdetachstate(&Attributes, PTHREAD_CREATE_DETACHED)
   //			|| pthread_cond_init(&wakeUpCondition_, 0)
   //			|| pthread_mutex_init(&startMutex_, 0)
   //			|| pthread_mutex_lock(&startMutex_)
   //			|| pthread_create(&thread_, &Attributes, reinterpret_cast<void * (*)(void *)>(thread::startExecution_), this))
   //			; // throw ...
   //
   //		 Scheduling policy is set to round robin and priority to normal
   //		struct sched_param param = {0};
   //		param.sched_priority = pal::scheduling_priority_normal;
   //		pthread_setschedparam( thread_, SCHED_RR, &param );
   //
   //		internal::g_globals.mutex_.lock();
   //		internal::g_globals.threadMap_[thread_] = this;
   //		internal::g_globals.mutex_.unlock();
   //	}
   //
   //	thread::thread(bool isMainThread, bool isExternalThread)
   //		: WaitableItem(false, false), isMainThread_(isMainThread), isExternalThread_(isExternalThread)
   //	{
   //		if (pthread_cond_init(&wakeUpCondition_, 0))
   //			; // throw ...
   //
   //		thread_ = pthread_self();
   //		internal::g_globals.mutex_.lock();
   //		internal::g_globals.threadMap_[thread_] = this;
   //		internal::g_globals.mutex_.unlock();
   //	}
   //
   //	wait_result thread::wait (WaitableItem & item, const boost::posix_time::time_duration& duration/*=InfiniteTime*/ /*)
   ///*	{
   //		WaitableItem * itemPtr = &item;
   //		return /*thread::*/ /*wait (1, &itemPtr, duration);
   //	}
   //
   //	wait_result thread::wait (size_t numberOfItems, WaitableItem * items[], const boost::posix_time::time_duration& duration/*=InfiniteTime*//*, bool waitForAll /*= false*/ /*)
   //	{
   //		if (pthread_self() != thread_)
   //			 do not call endWait() here
   //			return wait_result(wait_result::BadThread);
   //
   //		internal::g_globals.mutex_.lock();
   //
   //		if (!numberOfItems)
   //		{
   //			endWait();
   //			internal::g_globals.mutex_.unlock();
   //			return wait_result(wait_result::Failure);
   //		}
   //
   //		waitForAllItems_ = waitForAll;
   //
   //		if (!waitForAllItems_)
   //		{
   //			for (size_t i=0; i < numberOfItems; ++i)
   //				if (*items[i])
   //				{
   //					items[i]->threadTriggered_();
   //					endWait();
   //					internal::g_globals.mutex_.unlock();
   //					return wait_result(wait_result::Event0 + i);
   //				}
   //
   //
   //			if (duration.total_nanoseconds() == 0)
   //			{
   //				endWait();
   //				internal::g_globals.mutex_.unlock();
   //				return wait_result(wait_result::Timeout);
   //			}
   //		}
   //
   //		 add all events we wait for to itemsToWaitFor_ and the thread to WaitingThreads_ of every event we wait for
   //		for (size_t i=0; i < numberOfItems; ++i)
   //		{
   //			itemsToWaitFor_.push_back(items[i]);
   //			items[i]->addThread_(*this);
   //		}
   //
   //		if (waitForAllItems_ && checkAllItems_())
   //		{
   //			cleanUpItems_();
   //			endWait();
   //			internal::g_globals.mutex_.unlock();
   //			return wait_result(wait_result::Event0);
   //		}
   //		else if (!duration.total_nanoseconds())
   //		{
   //			cleanUpItems_();
   //			endWait();
   //			internal::g_globals.mutex_.unlock();
   //			return wait_result(wait_result::Timeout);
   //		}
   //
   //		waitResult_ = wait_result::Timeout;
   //
   //		 activate all events
   //		std::list<WaitableItem *>::iterator it(itemsToWaitFor_.begin()), end(itemsToWaitFor_.end());
   //		for (; it != end; ++it)
   //			(*it)->init_wait();	// activate event
   //
   //		 The cleanUpItems_-member-function of the thread-class will set waitResult_ before setting the wakeUpCondition_
   //		if (duration.is_pos_infinity())
   //			while (pthread_cond_wait(&wakeUpCondition_, &internal::g_globals.mutex_()) == EINTR)
   //				;	// nothing to do
   //		else
   //		{
   //			timeval tv;
   //			gettimeofday(&tv, 0);
   //			struct timespec Timeout = {tv.tv_sec + duration.total_seconds(), tv.tv_usec * 1000 + duration.total_nanoseconds() % 1000000000};
   //			if (Timeout.tv_nsec >= 1000000000)
   //			{
   //				Timeout.tv_nsec -= 1000000000;
   //				++Timeout.tv_sec;
   //			}
   //			while (pthread_cond_timedwait(&wakeUpCondition_, &internal::g_globals.mutex_(), &Timeout) == EINTR)
   //				;	// nothing to do
   //		}
   //
   //		if (waitResult_ == wait_result::Timeout)
   //			cleanUpItems_();
   //
   //		endWait();
   //		internal::g_globals.mutex_.unlock();
   //		return wait_result(waitResult_);
   //	}
   //
   //	void thread::cleanUpItems_ (WaitableItem * signallingItem /* = 0 */ /*)	// must be called with g_globals locked !!!
   //	{
   //		 remove thread from WaitingThreads_ of all events in itemsToWaitFor_
   //		 except the signalling event (because it is iterating over the list and will remove it itself) !!!
   //		std::list<WaitableItem *>::iterator it(itemsToWaitFor_.begin()), end(itemsToWaitFor_.end());
   //
   //		for (int32_t i=0 ; it != end; ++it, ++i)
   //		{
   //			if (*it != signallingItem)
   //				(*it)->removeThread_(*this);
   //
   //			if (**it && waitResult_ == wait_result::Timeout)
   //				waitResult_ = wait_result::Event0 + i;
   //		}
   //
   //		itemsToWaitFor_.clear();
   //
   //		if (signallingItem) {
   //			pthread_cond_signal(&wakeUpCondition_);
   //        }
   //	}
   //
   //	bool thread::checkAllItems_ (WaitableItem * signallingItem /* = 0 *//*)	// must be called with g_globals locked !!!
   //	{
   //		 remove thread from WaitingThreads_ of all events in itemsToWaitFor_
   //		 except the signalling event (because it is iterating over the list and will remove it itself) !!!
   //		std::list<WaitableItem *>::iterator it(itemsToWaitFor_.begin()), end(itemsToWaitFor_.end());
   //
   //		for ( ; it != end; ++it )
   //			if ( !**it ) {
   //				(*it)->init_wait();	// reactivate event
   //				return false;
   //			}
   //
   //		 all events signaled => inform all events except signalling event
   //		for (it = itemsToWaitFor_.begin(); it != end; ++it)
   //			if (*it != signallingItem)
   //				(*it)->threadTriggered_();
   //
   //		return true;
   //	}
   //
   //	void thread::set_priority(int32_t priority)
   //	{
   //		struct sched_param param = {0};
   //
   //		 Test routine
   //		/*int32_t policy;
   //		memset( &param, 0, sizeof( param ) );
   //		pthread_getschedparam( thread_, &policy, &param );
   //		std::cout << "thread::set_priority: thread has policy " << policy << " and priority " << param.sched_priority << '\n';
   //		std::cout << "thread::set_priority: Priority to set " << priority << '\n';*/
   //
   //		/*param.sched_priority = priority;
   //		/*int32_t result = *//*pthread_setschedparam( thread_, SCHED_RR, &param );
   //
   //		 TODO: We would need superuser privileges to change priority
   //		/*if ( result )
   //		{
   //			switch ( result )
   //			{
   //			case EPERM:
   //				std::cout << "thread::set_priority: You do not have superuser privileges\n";
   //				break;
   //			case ESRCH:
   //				std::cout << "thread::set_priority: thread does not exist\n";
   //				break;
   //			case EFAULT:
   //				std::cout << "thread::set_priority: Illegal parameter address\n";
   //				break;
   //			case EINVAL:
   //				std::cout << "thread::set_priority: Priority inconsistent with policy\n";
   //				break;
   //			default:
   //				std::cout << "thread::set_priority: Unknown error\n";
   //			}
   //		}*/
   //	}
   //
   //	/*int32_t thread::priority()
   //	{
   //		struct sched_param param = {0};
   //		int32_t policy;
   //
   //		/*int32_t result = *//*pthread_getschedparam( thread_, &policy, &param );
   //
   //		 TODO: We have to decide how to react on errors
   //		/*if ( result )
   //		{
   //			switch ( result )
   //			{
   //			case ESRCH:
   //				std::cout << "thread::priority: thread does not exist\n";
   //				break;
   //			case EFAULT:
   //				std::cout << "thread::priority: Illegal parameter address\n";
   //				break;
   //			case EINVAL:
   //				std::cout << "thread::priority: Priority inconsistent with policy\n";
   //				break;
   //			default:
   //				std::cout << "thread::priority: Unknown error\n";
   //			}
   //		}*/
   //
   //		/return param.sched_priority;
   //	}
   //
   //	thread::~thread()
   //	{
   ///*		internal::g_globals.mutex_.lock();
   //		cleanUpItems_();
   //		internal::g_globals.threadMap_.erase(thread_);
   //		internal::g_globals.mutex_.unlock();
   //
   //		if (!isMainThread_)
   //			pthread_mutex_destroy(&startMutex_);
   //		pthread_cond_destroy(&wakeUpCondition_);*/
   //	}
   
	unsigned long MillisecondCounter ()
	{
		timeval tv;
		gettimeofday(&tv, 0);
		return tv.tv_sec * 1000 + tv.tv_usec / 1000;
	}
   
   //	void thread::wait()
   //	{
   //
   //	   event_base::wait();
   //	}
   
   
   //	bool thread::has_message()
   //	{
   
   //	   throw "how to know?";
   
   //	}
   
   //} } // namespace gen { namespace pal {
   //
   //
   // EoF
   ///////
   
   
} // namespace mac




WINBOOL CLASS_DECL_mac AfxInternalPumpMessage();
LRESULT CLASS_DECL_mac AfxInternalProcessWndProcException(::exception::base*, const MESSAGE* pMsg);
void AfxInternalPreTranslateMessage(signal_details * pobj);
WINBOOL AfxInternalIsIdleMessage(signal_details * pobj);
WINBOOL AfxInternalIsIdleMessage(LPMESSAGE lpmsg);




/////////////////////////////////////////////////////////////////////////////
// Global functions for thread initialization and thread cleanup

//LRESULT CALLBACK _AfxMsgFilterHook(int32_t code, WPARAM wParam, LPARAM lParam);

void CLASS_DECL_mac __init_thread()
{
   
   
}

namespace mac
{
   
   

void __node_init_app_thread(::thread * pthread)
{
   
   UNREFERENCED_PARAMETER(pthread);
   
}



void __node_init_thread_state()
{
   
}




void __node_term_thread_state()
{
   
}





