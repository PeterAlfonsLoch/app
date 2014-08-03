#include "framework.h"
#include <process.h>    // for _beginthreadex and _endthreadex
#include <ddeml.h>  // for MSGF_DDEMGR

namespace metrowin
{
   class thread;
} // namespace metrowin

bool CLASS_DECL_BASE __internal_pump_message();
LRESULT CLASS_DECL_BASE __internal_process_wnd_proc_exception(::exception::base*, const MSG* pMsg);
bool __internal_pre_translate_message(MSG* pMsg);
bool __internal_is_idle_message(MSG* pMsg);
//__STATIC void CLASS_DECL_BASE __pre_init_dialog(sp(::user::interaction) pWnd, LPRECT lpRectOld, uint32_t* pdwStyleOld);
//__STATIC void CLASS_DECL_BASE __post_init_dialog(sp(::user::interaction) pWnd, const RECT& rectOld, uint32_t dwStyleOld);

namespace core
{

   thread_startup::thread_startup()
   {
   }

   thread_startup::~thread_startup()
   {
   }

} // namespace core





/////////////////////////////////////////////////////////////////////////////
// Thread entry point

#ifdef _MT

struct ___THREAD_STARTUP : ::core::thread_startup
{
   // following are "in" parameters to thread startup
   ___THREAD_STATE* pThreadState;    // thread state of parent thread
   ::metrowin::thread* pThread;    // thread for new thread
   uint32_t dwCreateFlags;    // thread creation flags
   _PNH pfnNewHandler;     // new handler for new thread

   //HANDLE hEvent;          // event triggered after success/non-success
   //HANDLE hEvent2;         // event triggered after thread is resumed

   // strictly "out" -- set after hEvent is triggered
   bool bError;    // TRUE if error during startup
};

uint32_t __thread_entry(void * pParam)
{

   uint32_t uiRet = 0;

   try
   {

      ___THREAD_STARTUP* pStartup = (___THREAD_STARTUP*)pParam;
      ASSERT(pStartup != NULL);
      ASSERT(pStartup->pThreadState != NULL);
      ASSERT(pStartup->pThread != NULL);
      //ASSERT(pStartup->hEvent != NULL);
      ASSERT(!pStartup->bError);


      ::metrowin::thread* pThread = pStartup->pThread;


      //      ::CoInitialize(NULL);


      pThread->::exception::translator::attach();

      try
      {
         // inherit parent's module state
         ___THREAD_STATE* pThreadState = __get_thread_state();

         pThreadState->m_pModuleState = pStartup->pThreadState->m_pModuleState;
         pThreadState->m_pCurrentWinThread = pThread;

         // set current thread pointer for System.GetThread
         __MODULE_STATE* pModuleState = __get_module_state();
         __MODULE_THREAD_STATE* pState = pModuleState->m_thread;
         pState->m_pCurrentWinThread = pThread;
         ::get_current_thread()->m_pthread = pThread->m_p.m_p;

         // forced initialization of the thread
         __init_thread();

         // thread inherits cast's main ::user::interaction_impl if not already set
         //if (papp != NULL && GetMainWnd() == NULL)
         {
            // just attach the oswindow
            // trans         threadWnd.Attach(pApp->GetMainWnd()->get_handle());
            //GetMainWnd() = pApp->GetMainWnd();
         }
      }
      catch(::exception::base *)
      {
         // Note: DELETE_EXCEPTION(e) not required.

         // exception happened during thread initialization!!
         //TRACE(::core::trace::category_AppMsg, 0, "Warning: Error during thread initialization!\n");

         // set error flag and allow the creating thread to notice the error
         //         threadWnd.Detach();
         pStartup->bError = TRUE;
         VERIFY(::SetEvent(pStartup->hEvent));
         __end_thread(dynamic_cast < ::base::application * > (pThread->m_pbaseapp.m_p), (UINT)-1, FALSE);
         ASSERT(FALSE);  // unreachable
      }


      ::metrowin::thread::s_haThread.add(::get_current_thread());
      ::metrowin::thread::s_threadptra.add(pThread);

      pThread->thread_entry(pStartup);

      // pStartup is invlaid after the following
      // SetEvent (but hEvent2 is valid)
      HANDLE hEvent2 = pStartup->hEvent2;

      // allow the creating thread to return from thread::CreateThread
      VERIFY(::SetEvent(pStartup->hEvent));

      // wait for thread to be resumed
      VERIFY(::WaitForSingleObjectEx(hEvent2, INFINITE, FALSE) == WAIT_OBJECT_0);
      ::CloseHandle(hEvent2);


      Sys(pThread->get_app()).get_cursor_pos(&(__get_thread_state()->m_ptCursorLast));


      int n = pThread->m_p->main();

      uiRet =  pThread->thread_term(n);


   }
   catch(...)
   {
      return -1;
   }

   return uiRet;

}

#endif //_MT

CLASS_DECL_BASE ::metrowin::thread * __get_thread()
{
   // check for current thread in module thread state
   //__MODULE_THREAD_STATE* pState = __get_module_thread_state();
   ___THREAD_STATE* pState =  __get_thread_state();
   ::metrowin::thread* pThread = pState->m_pCurrentWinThread;
   return pThread;
}


CLASS_DECL_BASE void __set_thread(::thread * pthread)
{
   // check for current thread in module thread state
   //__MODULE_THREAD_STATE* pState = __get_module_thread_state();
   ___THREAD_STATE* pState =  __get_thread_state();
   pState->m_pCurrentWinThread = dynamic_cast < ::metrowin::thread * > (pthread->::thread::m_p.m_p);
   ::get_current_thread()->m_pthread = pthread;
}



CLASS_DECL_BASE MSG * __get_current_message()
{
   ___THREAD_STATE* pState = __get_thread_state();
   ASSERT(pState);
   return &(pState->m_msgCur);
}



CLASS_DECL_BASE void __internal_process_wnd_proc_exception(::exception::base*, signal_details * pobj)
{
   SCAST_PTR(::message::base, pbase, pobj);
   if (pbase->m_uiMessage == WM_CREATE)
   {
      pbase->set_lresult(-1);
      return;  // just fail
   }
   else if (pbase->m_uiMessage == WM_PAINT)
   {
      // force validation of ::user::interaction_impl to prevent getting WM_PAINT again
      //      ValidateRect(pbase->m_pwnd->get_safe_handle(), NULL);
      pbase->set_lresult(0);
      return;
   }
   return;   // sensible default for rest of commands
}

CLASS_DECL_BASE void __process_window_procedure_exception(::exception::base* e, signal_details * pobj)
{
   ::thread *pThread = App(pobj->get_app()).GetThread();
   if( pThread )
      return pThread->ProcessWndProcException( e, pobj );
   else
      return __internal_process_wnd_proc_exception( e, pobj );
}

void __internal_pre_translate_message(signal_details * pobj)
{
   try
   {
      SCAST_PTR(::message::base, pbase, pobj);

      //   ASSERT_VALID(this);

      ::thread * pthread = ::metrowin::get_thread();
      if(pthread)
      {
         // if this is a thread-message, short-circuit this function
         if (pbase->m_pwnd == NULL)
         {
            pthread->DispatchThreadMessageEx(pobj);
            if(pobj->m_bRet)
               return;
         }
      }

      sp(::user::interaction) puiTopic = pbase->m_pwnd->m_pguie;

      try
      {
         if(pthread->m_pbaseapp->m_pcoreapp->m_psession != NULL)
         {
            try
            {
               for(int i = 0; i < pthread->m_pbaseapp->m_pcoreapp->m_psession->m_pplanesession->frames().get_count(); i++)
               {
                  try
                  {
                     sp(::user::interaction) pui = pthread->m_pbaseapp->m_pcoreapp->m_psession->m_pplanesession->frames()(i);
                     if(pui != NULL)
                     {
                        if(pui->m_pguie != NULL)
                        {
                           pui->m_pguie->pre_translate_message(pobj);
                           if(pobj->m_bRet)
                              return;
                        }
                        else
                        {
                           pui->pre_translate_message(pobj);
                           if(pobj->m_bRet)
                              return;
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
         }
      }
      catch(...)
      {
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
      return __internal_pre_translate_message( pobj );
}

bool __internal_is_idle_message(signal_details * pobj)
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
      // mouse move at same position as last mouse move?
      ___THREAD_STATE *pState = __get_thread_state();
      point ptCursor;
      App(pobj->get_app()).get_cursor_pos(&ptCursor);
      if (pState->m_ptCursorLast == ptCursor && pbase->m_uiMessage == pState->m_nMsgLast)
         return FALSE;

      pState->m_ptCursorLast = ptCursor;  // remember for next time
      pState->m_nMsgLast = pbase->m_uiMessage;
      return TRUE;
   }

   // WM_PAINT and WM_SYSTIMER (caret blink)
   return pbase->m_uiMessage != WM_PAINT && pbase->m_uiMessage != 0x0118;
}



bool __internal_is_idle_message(LPMESSAGE lpmsg)
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
      // mouse move at same position as last mouse move?
      ___THREAD_STATE *pState = __get_thread_state();
      if (pState->m_ptCursorLast == lpmsg->pt && lpmsg->message == pState->m_nMsgLast)
         return FALSE;

      pState->m_ptCursorLast = lpmsg->pt;  // remember for next time
      pState->m_nMsgLast = lpmsg->message;
      return TRUE;
   }

   // WM_PAINT and WM_SYSTIMER (caret blink)
   return lpmsg->message != WM_PAINT && lpmsg->message != 0x0118;
}

bool __cdecl __is_idle_message(signal_details * pobj)
{
   ::thread *pThread = App(pobj->get_app()).GetThread();
   if( pThread )
      return pThread->is_idle_message(pobj);
   else
      return __internal_is_idle_message(pobj);
}

bool __cdecl __is_idle_message(MESSAGE* pMsg)
{
   metrowin::thread * pThread = __get_thread();
   if(pThread)
      return pThread->is_idle_message( pMsg );
   else
      return __internal_is_idle_message( pMsg );
}


/*thread* CLASS_DECL_BASE __begin_thread(::base::application * papp, __THREADPROC pfnThreadProc, LPVOID pParam,
int nPriority, UINT nStackSize, uint32_t dwCreateFlags,
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
VERIFY(pThread->set_thread_priority(nPriority));
if (!(dwCreateFlags & CREATE_SUSPENDED))
VERIFY(pThread->ResumeThread() != (uint32_t)-1);

return pThread;
}*/
void CLASS_DECL_BASE __end_thread(::base::application * papp, UINT nExitCode, bool bDelete)
{
   // remove current thread object from primitive::memory
   __MODULE_THREAD_STATE* pState = __get_module_thread_state();
   ::metrowin::thread* pThread = pState->m_pCurrentWinThread;
   if (pThread != NULL)
   {
      ASSERT_VALID(pThread);
      //ASSERT(pThread != System::smart_pointer < ::base::application *>::m_p);

      if (bDelete)
         pThread->Delete();
      pState->m_pCurrentWinThread = NULL;
   }

   ::metrowin::thread::s_haThread.remove(::get_current_thread());
   ::metrowin::thread::s_threadptra.remove(pThread);

   // allow cleanup of any thread local objects
   __term_thread(papp);

   // allow C-runtime to cleanup, and exit the thread
   try
   {
      //      _endthreadex(nExitCode);
   }
   catch(...)
   {
   }
}

extern thread_local_storage * gen_ThreadData;

void CLASS_DECL_BASE __term_thread(::base::application * papp, HINSTANCE hInstTerm)
{
   UNREFERENCED_PARAMETER(papp);
   try
   {
      // cleanup thread local tooltip window
      if (hInstTerm == NULL)
      {
         //         __MODULE_THREAD_STATE* pModuleThreadState = __get_module_thread_state();
      }
   }
   catch( ::exception::base* e )
   {
      e->Delete();
   }

   try
   {
      // cleanup the rest of the thread local data
      if (gen_ThreadData != NULL)
         gen_ThreadData->delete_data();
   }
   catch( ::exception::base* e )
   {
      e->Delete();
   }
}


/////////////////////////////////////////////////////////////////////////////
// Global functions for thread initialization and thread cleanup

LRESULT CALLBACK __message_filter_hook(int code, WPARAM wParam, LPARAM lParam);

void CLASS_DECL_BASE __init_thread()
{
   if (!afxContextIsDLL)
   {
      // set message filter proc
#ifdef WINDOWSEX
      ___THREAD_STATE* pThreadState = __get_thread_state();
      ASSERT(pThreadState->m_hHookOldMsgFilter == NULL);
      pThreadState->m_hHookOldMsgFilter = ::SetWindowsHookEx(WH_MSGFILTER,
         __message_filter_hook, NULL, ::GetCurrentThreadId());
#endif
   }
}

namespace metrowin
{


   comparable_array < HTHREAD > thread::s_haThread;
   comparable_array < ::thread * > thread::s_threadptra;


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
         m_pAppThread = __get_thread()->m_pAppThread;
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
      //m_evFinish(FALSE, TRUE)
      ::thread(NULL),
      m_evFinish(papp),
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



      m_nDisablePumpCount  = 0;

      // no HTHREAD until it is created
      m_hThread = NULL;
      m_nThreadID = 0;

      ___THREAD_STATE* pState = __get_thread_state();
      // initialize message pump
      m_nDisablePumpCount = 0;
      pState->m_nMsgLast = WM_NULL;

      // most threads are deleted when not needed
      m_bAutoDelete  = TRUE;

      //m_frameList.Construct(offsetof(::user::frame_window, m_pNextFrameWnd));
      m_ptimera = canew(::user::interaction::timer_array(get_app()));
      m_puiptra = canew(::user::interaction_ptr_array(get_app()));

   }


   thread::~thread()
   {
      /*
      if(m_puiptra != NULL)
      {
         single_lock sl(&m_mutexUiPtra, TRUE);
         ::user::interaction_ptr_array * puiptra = m_puiptra;
         m_puiptra = NULL;
         for(int i = 0; i < puiptra->get_size(); i++)
         {
            sp(::user::interaction) pui = puiptra->element_at(i);
            if(pui->m_pthread != NULL)
            {
               try
               {
                  if(WIN_THREAD(pui->m_pthread->m_pthread) == this 
                     || WIN_THREAD(pui->m_pthread->m_pthread->m_p) == WIN_THREAD(m_p->m_pthread)
                     || WIN_THREAD(pui->m_pthread->m_pthread) == WIN_THREAD(m_p->m_pthread))
                  {
                     pui->m_pthread = NULL;
                  }
               }
               catch(...)
               {
               }
               try
               {
                  sp(::user::interaction) puie = pui->m_pguie;
                  if(WIN_THREAD(puie->m_pthread->m_pthread) == this 
                     || WIN_THREAD(puie->m_pthread->m_pthread->m_p) == WIN_THREAD(m_p)
                     || WIN_THREAD(puie->m_pthread->m_pthread) == WIN_THREAD(m_p))
                  {
                     puie->m_pthread = NULL;
                  }
               }
               catch(...)
               {
               }
            }
         }
         sl.unlock();
      }
      */
      __MODULE_THREAD_STATE* pState = __get_module_thread_state();
      /*      // clean up temp objects
      pState->m_pmapHGDIOBJ->delete_temp();
      pState->m_pmapHDC->delete_temp();
      pState->m_pmapHWND->delete_temp();*/

/*      for(int i = 0; i < m_captraDeletePool.get_count(); i++)
      {
         try
         {
            element * pca = m_captraDeletePool[i];            
            if(dynamic_cast < ::base::application * > (pca) == m_papp)
            {
               m_papp = NULL;
            }
         }
         catch(...)
         {
         }
      }
      */
      // free thread object
      if (m_hThread != NULL)
         CloseHandle(m_hThread);

      // cleanup module state
      if (pState->m_pCurrentWinThread == this)
         pState->m_pCurrentWinThread = NULL;

//      window::DeleteTempMap();
      //      graphics::DeleteTempMap();
      //    ::draw2d::object::DeleteTempMap();

      try
      {
         // cleanup temp/permanent maps (just the maps themselves)
         //         delete m_pmapHDC;
         //       delete m_pmapHGDIOBJ;
      }
      catch(...)
      {
      }

   }

   void * thread::get_os_data() const
   {
      return (void *) m_hThread;
   }

   int_ptr thread::get_os_int() const
   {
      return m_nThreadID;
   }

   HANDLE thread::item() const
   {
      return m_hThread == NULL ? NULL : (m_hThread->m_pevent == NULL ? NULL : m_hThread->m_pevent->get_os_data());
   }

   bool thread::begin(int32_t iPriority, UINT nStackSize, uint32_t dwCreateFlags, LPSECURITY_ATTRIBUTES lpSecurityAttrs)
   {

      if (!create_thread(iPriority, dwCreateFlags, nStackSize, lpSecurityAttrs))
      {
         Delete();
         return false;
      }

/*      if (!(dwCreateFlags & CREATE_SUSPENDED))
      {
         ENSURE(ResumeThread() != (uint32_t)-1);
      }*/

      return true;

   }

   void thread::on_delete(element * p)
   {
      UNREFERENCED_PARAMETER(p);
   }



   sp(::user::interaction) thread::SetMainWnd(sp(::user::interaction) pui)
   {
      sp(::user::interaction) puiPrevious = m_puiMain;
      m_puiMain  = pui;
      return puiPrevious;
   }

   void thread::add(sp(::user::interaction) pui)
   {
      single_lock sl(&m_mutexUiPtra, TRUE);
      if(m_puiptra != NULL)
      {
         m_puiptra->add(pui);
      }
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
         m_puiptra->remove(pui->m_pguie);
         m_puiptra->remove(pui->m_pimpl);
      }
      sl.unlock();
      if(m_ptimera != NULL)
      {
         m_ptimera->unset(pui);
         m_ptimera->unset(pui->m_pguie);
         m_ptimera->unset(pui->m_pimpl);
      }

      try
      {
         if(WIN_THREAD(pui->m_pthread.m_p) == this)
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
            if(WIN_THREAD(pui->m_pimpl->m_pthread.m_p) == this)
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
         if(pui->m_pguie != NULL && pui->m_pguie != pui)
         {
            if(WIN_THREAD(pui->m_pguie->m_pthread.m_p) == this)
            {
               pui->m_pguie->m_pthread = NULL;
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

   sp(::user::interaction) thread::get_ui(index iIndex)
   {
      single_lock sl(&m_mutexUiPtra, TRUE);
      return m_puiptra->element_at(iIndex);
   }

   void thread::set_timer(sp(::user::interaction) pui, uint_ptr nIDEvent, UINT nEllapse)
   {
//      if(m_spuiMessage.is_null())
  //    {
    //     return;
      //}
      m_ptimera->set(pui, nIDEvent, nEllapse);
      single_lock sl(&m_ptimera->m_mutex, TRUE);
      int iMin = 100;
      for(int i = 0; i < m_ptimera->m_timera.get_count(); i++)
      {
         if(m_ptimera->m_timera.element_at(i)->m_uiElapse < natural(iMin))
         {
            iMin = m_ptimera->m_timera.element_at(i)->m_uiElapse;
         }
      }
      sl.unlock();
#ifndef METROWIN
      if(m_spwindowMessage->IsWindow())
      {
         m_spwindowMessage->SetTimer((uint_ptr)-2, iMin, NULL);
      }
#endif
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

   bool thread::create_thread(int32_t iPriority, uint32_t dwCreateFlags, UINT nStackSize, LPSECURITY_ATTRIBUTES lpSecurityAttrs)
   {
      ENSURE(m_hThread == NULL);  // already created?

      // setup startup structure for thread initialization
      ___THREAD_STARTUP startup; 
      startup.bError = FALSE;
      startup.pfnNewHandler = NULL;
      //memset(&startup, 0, sizeof(startup));
      startup.pThreadState = __get_thread_state();
      startup.pThread = this;
      startup.m_pthread = NULL;
      startup.hEvent = ::CreateEventEx(NULL, NULL, CREATE_EVENT_MANUAL_RESET, EVENT_ALL_ACCESS);
      startup.hEvent2 = ::CreateEventEx(NULL, NULL, CREATE_EVENT_MANUAL_RESET, EVENT_ALL_ACCESS);
      startup.dwCreateFlags = dwCreateFlags;
      if (startup.hEvent == NULL || startup.hEvent2 == NULL)
      {
         TRACE(::core::trace::category_AppMsg, 0, "Warning: CreateEvent failed in thread::CreateThread.\n");
         if (startup.hEvent != NULL)
            ::CloseHandle(startup.hEvent);
         if (startup.hEvent2 != NULL)
            ::CloseHandle(startup.hEvent2);
         return FALSE;
      }

      //   m_thread = ::CreateThread(NULL, 0, StartThread, this, 0, &m_dwThreadId);
      // create the thread (it may or may not start to run)
      m_hThread = ::create_thread(lpSecurityAttrs, nStackSize, &__thread_entry, &startup, dwCreateFlags | CREATE_SUSPENDED, &m_nThreadID);

      if (m_hThread == NULL)
         return FALSE;

      VERIFY(set_thread_priority(iPriority));

      // start the thread just for ca2 API initialization
      VERIFY(ResumeThread() != (uint32_t)-1);
      VERIFY(::WaitForSingleObjectEx(startup.hEvent, INFINITE, FALSE) == WAIT_OBJECT_0);
      ::CloseHandle(startup.hEvent);

      // if created suspended, suspend it until resume thread wakes it up
      //   if (dwCreateFlags & CREATE_SUSPENDED)
      //    VERIFY(::SuspendThread(m_hThread) != (uint32_t)-1);

      // if error during startup, shut things down
      if (startup.bError)
      {
         VERIFY(::WaitForSingleObjectEx(m_hThread, INFINITE, FALSE) == WAIT_OBJECT_0);
         ::CloseHandle(m_hThread);
         m_hThread = NULL;
         ::CloseHandle(startup.hEvent2);
         return FALSE;
      }

      // allow thread to continue, once resumed (it may already be resumed)
      ::SetEvent(startup.hEvent2);
      return TRUE;

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
      }
      try
      {
         if(m_p != NULL)
         {
            ::thread * pthread = dynamic_cast < ::thread * > (m_p.m_p);
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
         //pthread->smart_pointer < ::thread >::m_p = NULL;
         m_p.release();
         // delete_this();
      }
      else
      {
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
   int thread::run()
   {
      ASSERT_VALID(this);
      //      ___THREAD_STATE* pState = __get_thread_state();

      // for tracking the idle time state
      bool bIdle = TRUE;
      LONG lIdleCount = 0;
      ::base::application * pappThis1 = dynamic_cast < ::base::application * > (this);
      ::base::application * pappThis2 = dynamic_cast < ::base::application * > (m_p.m_p);

      // acquire and dispatch messages until a WM_QUIT message is received.
      MESSAGE msg;
      while(m_bRun)
      {
         // phase1: check to see if we can do idle work
         while (bIdle && !::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE))
         {
            // call on_idle while in bIdle state
            if (!on_idle(lIdleCount++))
               bIdle = FALSE; // assume "no idle" state
            step_timer();
            m_p->m_dwAlive = m_dwAlive = ::get_tick_count();
            if(pappThis1 != NULL)
            {
               pappThis1->m_pcoreapp->m_dwAlive = m_dwAlive;
            }
            if(pappThis2 != NULL)
            {
               pappThis2->m_pcoreapp->m_dwAlive = m_dwAlive;
            }
            try
            {
               if(!m_p->verb())
                  goto stop_run;
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
            //if (is_idle_message(&m_msgCur))
            if (is_idle_message(&msg))
            {
               bIdle = TRUE;
               lIdleCount = 0;
            }

            step_timer();
            m_p->m_dwAlive = m_dwAlive = ::get_tick_count();
            if(pappThis1 != NULL)
            {
               pappThis1->m_pcoreapp->m_dwAlive = m_dwAlive;
            }
            if(pappThis2 != NULL)
            {
               pappThis2->m_pcoreapp->m_dwAlive = m_dwAlive;
            }
         }
         while (::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE) != FALSE);

      }
stop_run:
      return 0;
   }

   bool thread::is_idle_message(signal_details * pobj)
   {
      return __internal_is_idle_message(pobj);
   }

   bool thread::is_idle_message(LPMESSAGE lpmsg)
   {
      return __internal_is_idle_message(lpmsg);
   }

   void thread::delete_temp()
   {

      //      ::draw2d::object::DeleteTempMap();
      //    graphics::DeleteTempMap();
//      window::DeleteTempMap();

   }


   int thread::exit_instance()
   {
      ASSERT_VALID(this);


      try
      {
#ifdef DEBUG
         // Check for missing LockTempMap calls
         if(m_nTempMapLock != 0)
         {
            TRACE(::core::trace::category_AppMsg, 0, "Warning: Temp ::map lock count non-zero (%ld).\n", m_nTempMapLock);
         }
         LockTempMaps();
         UnlockTempMaps(true);
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
            ::user::interaction_ptr_array * puiptra = m_puiptra;
//            m_puiptra = NULL;
            for(int i = 0; i < puiptra->get_size(); i++)
            {
               sp(::user::interaction) pui = puiptra->element_at(i);
               if(pui->m_pthread != NULL)
               {
                  if(WIN_THREAD(pui->m_pthread.m_p) == this 
                     || WIN_THREAD(pui->m_pthread->m_p.m_p) == WIN_THREAD(m_p.m_p)
                     )
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
//         m_ptimera = NULL;
         delete ptimera;
      }
      catch(...)
      {
      }



      int nResult = (int)__get_current_message()->wParam;  // returns the value from PostQuitMessage
      return nResult;
   }

   bool thread::on_idle(LONG lCount)
   {



      ASSERT_VALID(this);

#if defined(DEBUG) && !defined(___NO_DEBUG_CRT)
      // check ca2 API's allocator (before idle)
      if (_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) & _CRTDBG_CHECK_ALWAYS_DF)
         ASSERT(__check_memory());
#endif

      if(lCount <= 0 && m_puiptra != NULL)
      {
         for(int i = 0; i < m_puiptra->get_count(); i++)
         {
            ::user::interaction* pui = m_puiptra->element_at(i);
            try
            {
               if (pui != NULL && pui->IsWindowVisible())
               {
                  /*__call_window_procedure(pMainWnd, pMainWnd->get_handle(),
                  WM_IDLEUPDATECMDUI, (WPARAM)TRUE, 0);*/
                  pui->send_message(WM_IDLEUPDATECMDUI, (WPARAM)TRUE);
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
         /*__call_window_procedure(pMainWnd, pMainWnd->get_handle(),
         WM_IDLEUPDATECMDUI, (WPARAM)TRUE, 0);*/
         /* pMainWnd->SendMessage(WM_IDLEUPDATECMDUI, (WPARAM)TRUE, 0);
         pMainWnd->SendMessageToDescendants(WM_IDLEUPDATECMDUI,
         (WPARAM)TRUE, 0, TRUE, TRUE);
         }
         */
         // send WM_IDLEUPDATECMDUI to all frame windows
         /* linux __MODULE_THREAD_STATE* pState = ___CMDTARGET_GETSTATE()->m_thread;
         frame_window* pFrameWnd = pState->m_frameList;
         while (pFrameWnd != NULL)
         {
         if (pFrameWnd->get_handle() != NULL && pFrameWnd != pMainWnd)
         {
         if (pFrameWnd->m_nShowDelay == SW_HIDE)
         pFrameWnd->ShowWindow(pFrameWnd->m_nShowDelay);
         if (pFrameWnd->IsWindowVisible() ||
         pFrameWnd->m_nShowDelay >= 0)
         {
         __call_window_procedure(pFrameWnd, pFrameWnd->get_handle(),
         WM_IDLEUPDATECMDUI, (WPARAM)TRUE, 0);
         pFrameWnd->SendMessageToDescendants(WM_IDLEUPDATECMDUI,
         (WPARAM)TRUE, 0, TRUE, TRUE);
         }
         if (pFrameWnd->m_nShowDelay > SW_HIDE)
         pFrameWnd->ShowWindow(pFrameWnd->m_nShowDelay);
         pFrameWnd->m_nShowDelay = -1;
         }
         pFrameWnd = pFrameWnd->m_pNextFrameWnd;
         }*/
      }
      else if (lCount >= 0)
      {
         /*         __MODULE_THREAD_STATE* pState = __get_module_thread_state();
         if (pState->m_nTempMapLock == 0)
         {
         // free temp maps, OLE DLLs, etc.
         ::ca2::LockTempMaps(dynamic_cast < ::base::application * > (m_p->m_papp));
         ::ca2::UnlockTempMaps(dynamic_cast < ::base::application * > (m_p->m_papp));
         }*/
      }

#if defined(DEBUG) && !defined(___NO_DEBUG_CRT)
      // check ca2 API's allocator (after idle)
      if (_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) & _CRTDBG_CHECK_ALWAYS_DF)
         ASSERT(__check_memory());
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
      if ((lpEntry = ::ca2::FindMessageEntry(pMessageMap->lpEntries,
      pMsg->message, 0, 0)) != NULL)
      goto LDispatch;
      }
      else
      {
      // registered windows message
      lpEntry = pMessageMap->lpEntries;
      while ((lpEntry = ::ca2::FindMessageEntry(lpEntry, 0xC000, 0, 0)) != NULL)
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
      for(int i = 0; i < signalptra.get_size(); i++)
      {
         Signal & signal = *signalptra[i];
         ::signal * psignal = signal.m_psignal;
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
      return __internal_pre_translate_message(pobj);
   }

   void thread::ProcessWndProcException(::exception::base* e, signal_details * pobj)
   {
      return __internal_process_wnd_proc_exception(e, pobj);
   }

   __STATIC inline bool IsEnterKey(signal_details * pobj)
   { 
      SCAST_PTR(::message::base, pbase, pobj);
      return pbase->m_uiMessage == WM_KEYDOWN && pbase->m_wparam == VK_RETURN; 
   }

   __STATIC inline bool IsButtonUp(signal_details * pobj)
   { 
      SCAST_PTR(::message::base, pbase, pobj);
      return pbase->m_uiMessage == WM_LBUTTONUP; 
   }

   void thread::ProcessMessageFilter(int code, signal_details * pobj)
   {

      if(pobj == NULL)
         return;   // not handled

      SCAST_PTR(::message::base, pbase, pobj);

#ifdef WINDOWSEX
      frame_window* pTopFrameWnd;
      ::user::interaction* pMainWnd;
      ::user::interaction* pMsgWnd;
      switch (code)
      {
      case MSGF_DDEMGR:
         // Unlike other WH_MSGFILTER codes, MSGF_DDEMGR should
         //  never call the next hook.
         // By returning FALSE, the message will be dispatched
         //  instead (the default behavior).
         return;

      case MSGF_MENU:
         pMsgWnd = pbase->m_pwnd;
         if (pMsgWnd != NULL)
         {
            pTopFrameWnd = pMsgWnd->GetTopLevelFrame();
            if (pTopFrameWnd != NULL && pTopFrameWnd->IsTracking() &&
               pTopFrameWnd->m_bHelpMode)
            {
               pMainWnd = __get_main_window();
               if ((GetMainWnd() != NULL) && (IsEnterKey(pbase) || IsButtonUp(pbase)))
               {
                  //                  pMainWnd->SendMessage(WM_COMMAND, ID_HELP);
                  pbase->m_bRet = true;
                  return;
               }
            }
         }
         // fall through...

      case MSGF_DIALOGBOX:    // handles message boxes as well.
         pMainWnd = __get_main_window();
         if (code == MSGF_DIALOGBOX && m_puiActive != NULL &&
            pbase->m_uiMessage >= WM_KEYFIRST && pbase->m_uiMessage <= WM_KEYLAST)
         {
            // need to translate messages for the in-place container
            ___THREAD_STATE* pThreadState = gen_ThreadState.get_data();
            ENSURE(pThreadState);

            if (pThreadState->m_bInMsgFilter)
               return;
            pThreadState->m_bInMsgFilter = TRUE;    // avoid reentering this code
            if (m_puiActive->IsWindowEnabled())
            {
               pre_translate_message(pobj);
               if(pobj->m_bRet)
               {
                  pThreadState->m_bInMsgFilter = FALSE;
                  return;
               }
            }
            pThreadState->m_bInMsgFilter = FALSE;    // ok again
         }
         break;
      }
#endif
      // default to not handled
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

         ZERO(msg);

         if(!::GetMessage(&msg, NULL, NULL, NULL))
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
               smart_pointer < ::message::base > spbase;

               spbase = get_base(&msg);

               try
               {
                  if(m_p != NULL)
                  {
                     m_p->pre_translate_message(spbase);
                     if(spbase->m_bRet)
                        return TRUE;
                  }
               }
               catch(...)
               {
               }

               try
               {
                  if(m_pbaseapp != NULL)
                  {
                     try
                     {
                        if(m_pbaseapp->m_pcoreapp->m_psystem != NULL)
                        {
                           m_pbaseapp->m_pcoreapp->m_psystem->pre_translate_message(spbase);
                           if(spbase->m_bRet)
                              return TRUE;
                        }
                     }
                     catch(...)
                     {
                     }
                     if(m_pbaseapp->m_pcoreapp->m_psession != NULL)
                     {
                        try
                        {
                           m_pbaseapp->m_pcoreapp->m_psession->m_pplanesession->pre_translate_message(spbase);
                           if(spbase->m_bRet)
                              return TRUE;
                        }
                        catch(...)
                        {
                        }
                     }
                  }
               }
               catch(...)
               {
               }
               try
               {
                  if(!m_pbaseapp->m_pcoreapp->is_system())
                  {
                     m_pbaseapp->m_pcoreapp->pre_translate_message(spbase);
                     if(spbase->m_bRet)
                        return TRUE;
                  }
               }
               catch(...)
               {
               }


               __pre_translate_message(spbase);
               if(spbase->m_bRet)
                  return TRUE;

               //spbase.destroy();
            }
            {
//               ::TranslateMessage(&msg);
  //             ::DispatchMessage(&msg);
               msg.oswindow->window()->send_message(msg.message, msg.wParam, msg.lParam);
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
      catch(...)
      {
         return FALSE;
      }

      return true;

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
      ___THREAD_STATE *pState = __get_thread_state();

      dumpcontext << "m_pThreadParams = " << m_pThreadParams;
      dumpcontext << "\nm_pfnThreadProc = " << (void *)m_pfnThreadProc;
      dumpcontext << "\nm_bAutoDelete = " << m_bAutoDelete;
      dumpcontext << "\nm_hThread = " << (void *)m_hThread;
      dumpcontext << "\nm_nThreadID = " << m_nThreadID;
#ifdef DEBUG
      dumpcontext << "\nm_nDisablePumpCount = " << pState->m_nDisablePumpCount;
#endif
      if (__get_thread() == this)
         dumpcontext << "\nm_pMainWnd = " << m_puiMain.m_p;

      dumpcontext << "\nm_msgCur = {";
      dumpcontext << "\n\thwnd = " << (void *)pState->m_msgCur.hwnd;
      dumpcontext << "\n\tmessage = " << (UINT)pState->m_msgCur.message;
      dumpcontext << "\n\twParam = " << (UINT)pState->m_msgCur.wParam;
      dumpcontext << "\n\tlParam = " << (void *)pState->m_msgCur.lParam;
      dumpcontext << "\n\ttime = " << (uint_ptr) pState->m_msgCur.time;
      dumpcontext << "\n\tpt = " << point(pState->m_msgCur.pt);
      dumpcontext << "\n}";

      dumpcontext << "\nm_pThreadParams = " << m_pThreadParams;
      dumpcontext << "\nm_pfnThreadProc = " << (void *)m_pfnThreadProc;
      dumpcontext << "\nm_ptCursorLast = " << pState->m_ptCursorLast;
      dumpcontext << "\nm_nMsgLast = " << pState->m_nMsgLast;

      dumpcontext << "\n";
   }


   bool thread::post_message(sp(::user::interaction) pguie, UINT uiMessage, WPARAM wparam, lparam lparam)
   {
      if(m_hThread == NULL)
         return false;
      ::user::message * pmessage = new ::user::message;
      pmessage->m_pguie       = pguie;
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
      // special message which identifies the window as using __window_procedure
/*      if(pbase->m_uiMessage == WM_QUERYAFXWNDPROC)
      {
         pbase->set_lresult(0);
         return;
      }
*/
      // all other messages route through message ::map
      sp(::user::interaction) pwindow = pbase->m_pwnd->get_wnd();

      ASSERT(pwindow == NULL || pwindow == pbase->m_pwnd->m_pimpl);

      if(pwindow == NULL || pwindow != pbase->m_pwnd->m_pimpl)
      {

         throw todo(get_app());

         //pbase->set_lresult(::DefWindowProc(pbase->m_pwnd->get_safe_handle(), pbase->m_uiMessage, pbase->m_wparam, pbase->m_lparam));
         //return;
      }

      ___THREAD_STATE* pThreadState = gen_ThreadState.get_data();
      MSG oldState = pThreadState->m_lastSentMsg;   // save for nesting
      //      pThreadState->m_lastSentMsg.hwnd       = pbase->m_pwnd->get_safe_handle();
      pThreadState->m_lastSentMsg.message    = pbase->m_uiMessage;
      pThreadState->m_lastSentMsg.wParam     = pbase->m_wparam;
      pThreadState->m_lastSentMsg.lParam     = pbase->m_lparam;

      //      __trace_message("message_handler", pobj);

      // Catch exceptions thrown outside the scope of a callback
      // in debug builds and warn the ::fontopus::user.
      try
      {

         // special case for WM_INITDIALOG
         rect rectOld;
         uint32_t dwStyle = 0;
         //         if(pbase->m_uiMessage == WM_INITDIALOG)
         //          __pre_init_dialog(pwindow, &rectOld, &dwStyle);

         // delegate to object's message_handler
         if(pwindow->m_pguie != NULL && pwindow->m_pguie != pwindow)
         {
            pwindow->m_pguie->message_handler(pobj);
         }
         else
         {
            pwindow->message_handler(pobj);
         }

         // more special case for WM_INITDIALOG
         //         if(pbase->m_uiMessage == WM_INITDIALOG)
         //          __post_init_dialog(pwindow, rectOld, dwStyle);
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
         __process_window_procedure_exception(pe, pbase);
         TRACE(::core::trace::category_AppMsg, 0, "Warning: Uncaught exception in message_handler (returning %ld).\n", pbase->get_lresult());
         pe->Delete();
      }
run:
      pThreadState->m_lastSentMsg = oldState;
   }


   thread::operator HANDLE() const
   { 

      return this == NULL ? NULL : m_hThread; 

   }

   bool thread::set_thread_priority(int nPriority)
   { 
      ASSERT(m_hThread != NULL); 

      return ::SetThreadPriority(m_hThread, nPriority)  != FALSE; 

   }

   int thread::get_thread_priority()
   { 
      
      ASSERT(m_hThread != NULL); 
      
      return ::GetThreadPriority(m_hThread); 
   
   }

   uint32_t thread::ResumeThread()
   {

      ASSERT(m_hThread != NULL); return ::ResumeThread(m_hThread);

   }

   uint32_t thread::SuspendThread()
   {

      throw todo(get_app());

      /*ASSERT(m_hThread != NULL); return ::SuspendThread(m_hThread); 
      */
   }

   bool thread::post_thread_message(UINT message, WPARAM wParam, lparam lParam)
   {

      ASSERT(m_hThread != NULL);
      
      return ::PostThreadMessage(m_nThreadID, message, wParam, lParam) != FALSE;

   }

   void thread::set_os_data(void * pvoidOsData)
   {
      m_hThread = (HTHREAD) pvoidOsData;

   }

   void thread::set_os_int(int_ptr iData)
   {
      m_nThreadID = (uint32_t) iData;
   }

   void thread::message_queue_message_handler(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }


   CLASS_DECL_BASE ::thread * get_thread()
   {
      ::metrowin::thread * pwinthread = __get_thread();
      if(pwinthread == NULL)
         return NULL;
      return pwinthread->m_p;
   }

   CLASS_DECL_BASE ::thread_state * get_thread_state()
   {
      return __get_thread_state();
   }

   void thread::LockTempMaps()
   {
      ++m_nTempMapLock;
   }
   bool thread::UnlockTempMaps(bool bDeleteTemp)
   {
      if (m_nTempMapLock != 0 && --m_nTempMapLock == 0)
      {
         if (bDeleteTemp)
         {
            // clean up temp objects
            //         ::draw2d::object::DeleteTempMap();
            //       graphics::DeleteTempMap();
//            window::DeleteTempMap();
         }



#ifndef ___PORTABLE
         ::base::application * papp = dynamic_cast < ::base::application * > (get_app());
         ___THREAD_STATE* pThreadState = gen_ThreadState.GetDataNA();
         if( pThreadState != NULL )
         {
            // restore safety pool after temp objects destroyed
            if(papp != NULL &&
               (pThreadState->m_pSafetyPoolBuffer == NULL ||
               _msize(pThreadState->m_pSafetyPoolBuffer) < papp->m_pcoreapp->m_pcoreapp->m_nSafetyPoolSize) &&
               papp->m_pcoreapp->m_pcoreapp->m_nSafetyPoolSize != 0)
            {
               // attempt to restore the safety pool to its max size
               size_t nOldSize = 0;
               if (pThreadState->m_pSafetyPoolBuffer != NULL)
               {
                  nOldSize = _msize(pThreadState->m_pSafetyPoolBuffer);
                  free(pThreadState->m_pSafetyPoolBuffer);
               }

               // undo handler trap for the following allocation
               //bool bEnable = __enable_memory_tracking(FALSE);
               try
               {
                  pThreadState->m_pSafetyPoolBuffer = malloc(papp->m_pcoreapp->m_pcoreapp->m_nSafetyPoolSize);
                  if (pThreadState->m_pSafetyPoolBuffer == NULL)
                  {
                     //                  TRACE(::core::trace::category_AppMsg, 0, "Warning: failed to reclaim %d bytes for primitive::memory safety pool.\n",
                     //                   pApp->m_nSafetyPoolSize);
                     // at least get the old buffer back
                     if (nOldSize != 0)
                     {
                        //get it back
                        pThreadState->m_pSafetyPoolBuffer = malloc(nOldSize);
                        ASSERT(pThreadState->m_pSafetyPoolBuffer != NULL);
                     }
                  }
               }
               catch( ::exception::base * )
               {
                  //__enable_memory_tracking(bEnable);
                  throw;
               }
               //__enable_memory_tracking(bEnable);
            }
         }
#endif  // !___PORTABLE
      }
      // return TRUE if temp maps still locked
      return m_nTempMapLock != 0;
   }

   int thread::thread_entry(::core::thread_startup * pstartup)
   {

      ___THREAD_STARTUP* pStartup = (___THREAD_STARTUP*)pstartup;
      ASSERT(pStartup != NULL);
      ASSERT(pStartup->pThreadState != NULL);
      ASSERT(pStartup->pThread != NULL);
      ASSERT(!pStartup->bError);

      ::metrowin::thread* pThread = pStartup->pThread;

      //      ::application* papp = dynamic_cast < ::base::application * > (get_app());
      m_evFinish.ResetEvent();
      install_message_handling(pThread);
      m_p->install_message_handling(pThread);

//      ::user::interaction_impl threadWnd;

//      m_ptimera            = new ::user::interaction::timer_array(get_app());
  //    m_puiptra            = new user::interaction_ptr_array(get_app());

      //m_ptimera->m_papp    = m_papp;
      //m_puiptra->m_papp    = m_papp;



      //if(!create_message_queue(get_app(), ""))
        // return -1;


      return 0;   // not reached

   }

   int thread::main()
   {

      /*      ___THREAD_STARTUP* pStartup = (___THREAD_STARTUP*)pstartup;
      ASSERT(pStartup != NULL);
      ASSERT(pStartup->pThreadState != NULL);
      ASSERT(pStartup->pThread != NULL);
      ASSERT(!pStartup->bError);*/

      if(!m_p->PreInitInstance())
      {
         return 0;
      }

      // first -- check for simple worker thread
      uint32_t nResult = 0;
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
            nResult = (uint32_t) -1;
         }
      }
      else
      {
         // will stop after PostQuitMessage called
         ASSERT_VALID(this);
         translator::attach();
run:
         try
         {
            try
            {
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
                  nResult = (uint32_t) -1;
               }
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

   int thread::thread_term(int nResult)
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
         __end_thread(dynamic_cast < ::base::application * > (m_pbaseapp.m_p), nResult);
      }
      catch(...)
      {
      }
      return nResult;
   }


   /**
   * \file		src/lib/pal/windows/thread_windows.hpp
   * \brief	Platform independent threads and synchronization objects (windows version)
   * \author	Thomas Nass
   */

   ///  \brief		starts thread on first call
   void thread::start()
   {
      ::ResumeThread(m_hThread);
   }


   void thread::wait()
   {
      ::WaitForSingleObjectEx(item(),INFINITE, FALSE);
   }

   ///  \brief		waits for signaling the thread for a specified time
   ///  \param		duration time period to wait for thread
   ///  \return	result of waiting action as defined in wait_result
   wait_result thread::wait(const duration & duration)
   {
      uint32_t timeout = duration.is_pos_infinity() ? INFINITE : static_cast<uint32_t>(duration.total_milliseconds());
      return wait_result((uint32_t) ::WaitForSingleObjectEx(item(),timeout, FALSE));
   }

   ///  \brief		sets thread priority
   ///  \param		new priority
   void thread::set_priority(int priority)
   {
      if ( ::SetThreadPriority(m_hThread, priority) == 0)
         throw runtime_error(get_app(), "Thread::set_priority: Couldn't set thread priority.");
   }

   ///  \brief		gets thread priority
   ///  \param		priority
   int thread::priority()
   { 
      return ::GetThreadPriority(m_hThread);
   }


   bool thread::has_message()
   {
      ASSERT(GetCurrentThreadId() == m_nThreadID);
      MESSAGE msg;
      return ::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE) != FALSE;
   }


} // namespace metrowin




bool CLASS_DECL_BASE __internal_pump_message();
LRESULT CLASS_DECL_BASE __internal_process_wnd_proc_exception(::exception::base*, const MSG* pMsg);
void __internal_pre_translate_message(signal_details * pobj);
bool __internal_is_idle_message(signal_details * pobj);
bool __internal_is_idle_message(LPMSG lpmsg);


/*thread* CLASS_DECL_BASE System.GetThread()
{
// check for current thread in module thread state
__MODULE_THREAD_STATE* pState = __get_module_thread_state();
//thread* pThread = pState->m_pCurrentWinThread;
return pThread;
}

MSG* CLASS_DECL_BASE __get_current_message()
{
___THREAD_STATE* pState = __get_thread_state();
ASSERT(pState);
return &(pState->m_msgCur);
}

bool CLASS_DECL_BASE __internal_pump_message()
{
___THREAD_STATE *pState = __get_thread_state();

if (!::GetMessage(&(pState->m_msgCur), NULL, NULL, NULL))
{
#ifdef DEBUG
TRACE(::core::trace::category_AppMsg, 1, "thread::pump_message - Received WM_QUIT.\n");
pState->m_nDisablePumpCount++; // application must die
#endif
// Note: prevents calling message loop things in 'exit_instance'
// will never be decremented
return FALSE;
}

#ifdef DEBUG
if (pState->m_nDisablePumpCount != 0)
{
TRACE(::core::trace::category_AppMsg, 0, "Error: thread::pump_message called when not permitted.\n");
ASSERT(FALSE);
}
#endif

#ifdef DEBUG
__trace_message("pump_message", &(pState->m_msgCur));
#endif

// process this message

if (pState->m_msgCur.message != WM_KICKIDLE && !__pre_translate_message(&(pState->m_msgCur)))
{
::TranslateMessage(&(pState->m_msgCur));
::DispatchMessage(&(pState->m_msgCur));
}
return TRUE;
}

bool CLASS_DECL_BASE ::ca2::PumpMessage()
{
thread *pThread = System.GetThread();
if( pThread )
return pThread->pump_message();
else
return __internal_pump_message();
}

LRESULT CLASS_DECL_BASE __internal_process_wnd_proc_exception(::exception::base*, const MSG* pMsg)
{
if (pMsg->message == WM_CREATE)
{
return -1;  // just fail
}
else if (pMsg->message == WM_PAINT)
{
// force validation of ::user::interaction_impl to prevent getting WM_PAINT again
ValidateRect(pMsg->hwnd, NULL);
return 0;
}
return 0;   // sensible default for rest of commands
}

LRESULT CLASS_DECL_BASE __process_window_procedure_exception(::exception::base* e, const MSG* pMsg)
{
thread *pThread = System.GetThread();
if( pThread )
return pThread->ProcessWndProcException( e, pMsg );
else
return __internal_process_wnd_proc_exception( e, pMsg );
}
bool __internal_pre_translate_message(MSG* pMsg)
{
//   ASSERT_VALID(this);

thread *pThread = System.GetThread();
if( pThread )
{
// if this is a thread-message, short-circuit this function
if (pMsg->hwnd == NULL && pThread->DispatchThreadMessageEx(pMsg))
return TRUE;
}

// walk from target to main ::user::interaction_impl
::user::interaction* pMainWnd = System.GetMainWnd();
/* trans   if (::user::interaction_impl::WalkPreTranslateTree(pMainWnd->GetSafeHwnd(), pMsg))
return TRUE; */

// in case of modeless dialogs, last chance route through main
//   ::user::interaction_impl's accelerator table
/*   if (pMainWnd != NULL)
{
::user::interaction_impl * pWnd = ::metrowin::window::from_handle(pMsg->hwnd);
if (pWnd != NULL && WIN_WINDOW(pWnd)->GetTopLevelParent() != pMainWnd)
return pMainWnd->pre_translate_message(pMsg);
}

return FALSE;   // no special processing
}

bool __cdecl __pre_translate_message(MSG* pMsg)
{
thread *pThread = System.GetThread();
if( pThread )
return pThread->pre_translate_message( pMsg );
else
return __internal_pre_translate_message( pMsg );
}

bool __internal_is_idle_message(MSG* pMsg)
{
// Return FALSE if the message just dispatched should _not_
// cause on_idle to be run.  Messages which do not usually
// affect the state of the ::fontopus::user interface and happen very
// often are checked for.

// redundant WM_MOUSEMOVE and WM_NCMOUSEMOVE
if (pMsg->message == WM_MOUSEMOVE || pMsg->message == WM_NCMOUSEMOVE)
{
// mouse move at same position as last mouse move?
___THREAD_STATE *pState = __get_thread_state();
if (pState->m_ptCursorLast == pMsg->pt && pMsg->message == pState->m_nMsgLast)
return FALSE;

pState->m_ptCursorLast = pMsg->pt;  // remember for next time
pState->m_nMsgLast = pMsg->message;
return TRUE;
}

// WM_PAINT and WM_SYSTIMER (caret blink)
return pMsg->message != WM_PAINT && pMsg->message != 0x0118;
}

bool __cdecl __is_idle_message(MSG* pMsg)
{
thread *pThread = System.GetThread();
if( pThread )
return pThread->is_idle_message( pMsg );
else
return __internal_is_idle_message( pMsg );
}

/*
thread* CLASS_DECL_BASE __begin_thread(::ca2::type_info pThreadClass,
int nPriority, UINT nStackSize, uint32_t dwCreateFlags,
LPSECURITY_ATTRIBUTES lpSecurityAttrs)
{
#ifndef _MT
pThreadClass;
nPriority;
nStackSize;
dwCreateFlags;
lpSecurityAttrs;

return NULL;
#else
ASSERT(pThreadClass != NULL);
ASSERT(pThreadClass->IsDerivedFrom(System.template type_info < thread > ()));

thread* pThread = dynamic_cast < thread * > (App(get_app()).alloc(pThreadClass));
if (pThread == NULL)
throw memory_exception();
ASSERT_VALID(pThread);

pThread->m_pThreadParams = NULL;
if(pThread->begin(
nPriority, 
nStackSize, 
dwCreateFlags, 
lpSecurityAttrs))
return pThread;
else
return NULL;
#endif //!_MT
}*/

/*
void CLASS_DECL_BASE __end_thread(UINT nExitCode, bool bDelete)
{
#ifndef _MT
nExitCode;
bDelete;
#else
// remove current thread object from primitive::memory
__MODULE_THREAD_STATE* pState = __get_module_thread_state();
// thread* pThread = pState->m_pCurrentWinThread;
if (pThread != NULL)
{
ASSERT_VALID(pThread);
ASSERT(pThread != &System);

if (bDelete)
pThread->Delete();
// pState->m_pCurrentWinThread = NULL;
}

// allow cleanup of any thread local objects
__term_thread();

// allow C-runtime to cleanup, and exit the thread
_endthreadex(nExitCode);
#endif //!_MT
}

/////////////////////////////////////////////////////////////////////////////
// Global functions for thread initialization and thread cleanup

LRESULT CALLBACK __message_filter_hook(int code, WPARAM wParam, LPARAM lParam);

void CLASS_DECL_BASE __init_thread()
{
if (!afxContextIsDLL)
{
// set message filter proc
___THREAD_STATE* pThreadState = __get_thread_state();
ASSERT(pThreadState->m_hHookOldMsgFilter == NULL);
pThreadState->m_hHookOldMsgFilter = ::SetWindowsHookEx(WH_MSGFILTER,
__message_filter_hook, NULL, ::GetCurrentThreadId());
}
}





bool thread::CreateThread(uint32_t dwCreateFlags, UINT nStackSize,
LPSECURITY_ATTRIBUTES lpSecurityAttrs)
{
#ifndef _MT
dwCreateFlags;
nStackSize;
lpSecurityAttrs;

return FALSE;
#else
ENSURE(m_hThread == NULL);  // already created?

// setup startup structure for thread initialization
___THREAD_STARTUP startup; memset(&startup, 0, sizeof(startup));
startup.pThreadState = __get_thread_state();
startup.pThread = this;
startup.hEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);
startup.hEvent2 = ::CreateEvent(NULL, TRUE, FALSE, NULL);
startup.dwCreateFlags = dwCreateFlags;
if (startup.hEvent == NULL || startup.hEvent2 == NULL)
{
TRACE(::core::trace::category_AppMsg, 0, "Warning: CreateEvent failed in thread::CreateThread.\n");
if (startup.hEvent != NULL)
::CloseHandle(startup.hEvent);
if (startup.hEvent2 != NULL)
::CloseHandle(startup.hEvent2);
return FALSE;
}

#ifdef _WIN32
//   m_thread = ::CreateThread(NULL, 0, StartThread, this, 0, &m_dwThreadId);
// create the thread (it may or may not start to run)
m_hThread = (HANDLE)(ulong_ptr)_beginthreadex(lpSecurityAttrs, nStackSize,  
&__thread_entry, &startup, dwCreateFlags | CREATE_SUSPENDED, (UINT*)&m_nThreadID);
#else
pthread_attr_t attr;

pthread_attr_init(&attr);
pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
if (pthread_create(&m_thread,&attr, StartThread,this) == -1)
{
perror("Thread: create failed");
SetRunning(false);
}
//   pthread_attr_destroy(&attr);
#endif

if (m_hThread == NULL)
return FALSE;

// start the thread just for ca2 API initialization
VERIFY(ResumeThread() != (uint32_t)-1);
VERIFY(::WaitForSingleObject(startup.hEvent, INFINITE) == WAIT_OBJECT_0);
::CloseHandle(startup.hEvent);

// if created suspended, suspend it until resume thread wakes it up
if (dwCreateFlags & CREATE_SUSPENDED)
VERIFY(::SuspendThread(m_hThread) != (uint32_t)-1);

// if error during startup, shut things down
if (startup.bError)
{
VERIFY(::WaitForSingleObject(m_hThread, INFINITE) == WAIT_OBJECT_0);
::CloseHandle(m_hThread);
m_hThread = NULL;
::CloseHandle(startup.hEvent2);
return FALSE;
}

// allow thread to continue, once resumed (it may already be resumed)
::SetEvent(startup.hEvent2);
return TRUE;
#endif //!_MT
}

void thread::Delete()
{

// delete thread if it is auto-deleting
if(m_bAutoDelete)
{
m_evFinish.SetEvent();
delete this;
}
else
{
m_hThread = NULL;
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
int thread::run()
{
ASSERT_VALID(this);
___THREAD_STATE* pState = __get_thread_state();

// for tracking the idle time state
bool bIdle = TRUE;
LONG lIdleCount = 0;

// acquire and dispatch messages until a WM_QUIT message is received.
while(m_bRun)
{
// phase1: check to see if we can do idle work
while (bIdle &&
!::PeekMessage(&(pState->m_msgCur), NULL, NULL, NULL, PM_NOREMOVE))
{
// call on_idle while in bIdle state
if (!on_idle(lIdleCount++))
bIdle = FALSE; // assume "no idle" state
}

// phase2: pump messages while available
do
{
// pump message, but quit on WM_QUIT
if (!pump_message())
return exit_instance();

// reset "no idle" state after pumping "normal" message
//if (is_idle_message(&m_msgCur))
if (is_idle_message(&(pState->m_msgCur)))
{
bIdle = TRUE;
lIdleCount = 0;
}


} while (::PeekMessage(&(pState->m_msgCur), NULL, NULL, NULL, PM_NOREMOVE));

m_ptimera->check();
}
}

bool thread::is_idle_message(MSG* pMsg)
{
return __internal_is_idle_message(pMsg);
}

int thread::exit_instance()
{
ASSERT_VALID(this);
ASSERT(&System != this);

for(int i = 0; i < m_puieptra->get_count(); i++)
{
m_puieptra->element_at(i)->m_pthread = NULL;
}

delete m_ptimera;
delete m_puieptra;

int nResult = (int)__get_current_message()->wParam;  // returns the value from PostQuitMessage
return nResult;
}

bool thread::on_idle(LONG lCount)
{
ASSERT_VALID(this);

#if defined(DEBUG) && !defined(___NO_DEBUG_CRT)
// check ca2 API's allocator (before idle)
if (_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) & _CRTDBG_CHECK_ALWAYS_DF)
ASSERT(__check_memory());
#endif

if (lCount <= 0)
{
// send WM_IDLEUPDATECMDUI to the main ::user::interaction_impl
::user::interaction* pMainWnd = GetMainWnd();
if (pMainWnd != NULL && pMainWnd->IsWindowVisible())
{
/*__call_window_procedure(pMainWnd, pMainWnd->get_handle(),
WM_IDLEUPDATECMDUI, (WPARAM)TRUE, 0);*/
/*       pMainWnd->SendMessage(WM_IDLEUPDATECMDUI, (WPARAM)TRUE, 0);
pMainWnd->SendMessageToDescendants(WM_IDLEUPDATECMDUI,
(WPARAM)TRUE, 0, TRUE, TRUE);
}
// send WM_IDLEUPDATECMDUI to all frame windows
/* linux __MODULE_THREAD_STATE* pState = ___CMDTARGET_GETSTATE()->m_thread;
frame_window* pFrameWnd = pState->m_frameList;
while (pFrameWnd != NULL)
{
if (pFrameWnd->get_handle() != NULL && pFrameWnd != pMainWnd)
{
if (pFrameWnd->m_nShowDelay == SW_HIDE)
pFrameWnd->ShowWindow(pFrameWnd->m_nShowDelay);
if (pFrameWnd->IsWindowVisible() ||
pFrameWnd->m_nShowDelay >= 0)
{
__call_window_procedure(pFrameWnd, pFrameWnd->get_handle(),
WM_IDLEUPDATECMDUI, (WPARAM)TRUE, 0);
pFrameWnd->SendMessageToDescendants(WM_IDLEUPDATECMDUI,
(WPARAM)TRUE, 0, TRUE, TRUE);
}
if (pFrameWnd->m_nShowDelay > SW_HIDE)
pFrameWnd->ShowWindow(pFrameWnd->m_nShowDelay);
pFrameWnd->m_nShowDelay = -1;
}
pFrameWnd = pFrameWnd->m_pNextFrameWnd;
}*/
/*}
else if (lCount >= 0)
{
__MODULE_THREAD_STATE* pState = __get_module_thread_state();
if (pState->m_nTempMapLock == 0)
{
// free temp maps, OLE DLLs, etc.
::ca2::LockTempMaps();
::ca2::UnlockTempMaps();
}
}

#if defined(DEBUG) && !defined(___NO_DEBUG_CRT)
// check ca2 API's allocator (after idle)
if (_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) & _CRTDBG_CHECK_ALWAYS_DF)
ASSERT(__check_memory());
#endif

return lCount < 0;  // nothing more to do if lCount >= 0
}

::message::e_prototype thread::GetMessagePrototype(UINT uiMessage, UINT uiCode)
{
return ::message::PrototypeNone;
}


bool thread::DispatchThreadMessageEx(MSG* pmsg)
{
if(pmsg->message == WM_APP + 1984 && pmsg->wParam == 77)
{
::ca2::scoped_ptr < metrowin::message > spmessage(pmsg->lParam);
spmessage->send();
return TRUE;
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
// constant ::user::interaction_impl message
if ((lpEntry = ::ca2::FindMessageEntry(pMessageMap->lpEntries,
pMsg->message, 0, 0)) != NULL)
goto LDispatch;
}
else
{
// registered windows message
lpEntry = pMessageMap->lpEntries;
while ((lpEntry = ::ca2::FindMessageEntry(lpEntry, 0xC000, 0, 0)) != NULL)
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

/*LRESULT lresult;
SignalPtrArray signalptra;
m_signala.GetSignalsByMessage(signalptra, pmsg->message, 0, 0);
for(int i = 0; i < signalptra.get_size(); i++)
{
Signal & signal = *signalptra[i];
::signal * psignal = signal.m_psignal;
::message::e_prototype eprototype = signal.m_eprototype;
if(eprototype == ::message::PrototypeNone)
{
::message::base base;
base.m_psignal = psignal;
lresult = 0;
base.set(pmsg->message, pmsg->wParam, pmsg->lParam, lresult);
psignal->emit(&base);
if(base.m_bRet)
return true;
}
break;
}
return true;
}

bool thread::pre_translate_message(signal_details * pobj)
{
ASSERT_VALID(this);
return __internal_pre_translate_message( pMsg );
}

LRESULT thread::ProcessWndProcException(::exception::base* e, const MSG* pMsg)
{
return __internal_process_wnd_proc_exception( e, pMsg );
}
*/

/////////////////////////////////////////////////////////////////////////////
// Message Filter processing (WH_MSGFILTER)

#ifdef WINDOWSEX

LRESULT CALLBACK __message_filter_hook(int code, WPARAM wParam, LPARAM lParam)
{
   ::thread* pthread;
   if (afxContextIsDLL || (code < 0 && code != MSGF_DDEMGR) || (pthread = dynamic_cast < ::thread * > (::metrowin::get_thread())) == NULL)
   {
      return ::CallNextHookEx(gen_ThreadState->m_hHookOldMsgFilter, code, wParam, lParam);
   }
   ASSERT(pthread != NULL);
   smart_pointer < ::message::base > spbase;
   spbase(pthread->get_base((LPMSG)lParam));
   pthread->ProcessMessageFilter(code, spbase);
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

#endif

__STATIC inline bool IsEnterKey(LPMSG lpMsg)
{ return lpMsg->message == WM_KEYDOWN && lpMsg->wParam == VK_RETURN; }

__STATIC inline bool IsButtonUp(LPMSG lpMsg)
{ return lpMsg->message == WM_LBUTTONUP; }

/*&bool thread::ProcessMessageFilter(int code, LPMSG lpMsg)
{
if (lpMsg == NULL)
return FALSE;   // not handled

frame_window* pTopFrameWnd;
::user::interaction* pMainWnd;
::user::interaction* pMsgWnd;
switch (code)
{
case MSGF_DDEMGR:
// Unlike other WH_MSGFILTER codes, MSGF_DDEMGR should
//  never call the next hook.
// By returning FALSE, the message will be dispatched
//  instead (the default behavior).
return FALSE;

case MSGF_MENU:
pMsgWnd = ::metrowin::window::from_handle(lpMsg->hwnd);
if (pMsgWnd != NULL)
{
pTopFrameWnd = pMsgWnd->GetTopLevelFrame();
if (pTopFrameWnd != NULL && pTopFrameWnd->IsTracking() &&
pTopFrameWnd->m_bHelpMode)
{
pMainWnd = System.GetMainWnd();
if ((GetMainWnd() != NULL) && (IsEnterKey(lpMsg) || IsButtonUp(lpMsg)))
{
pMainWnd->SendMessage(WM_COMMAND, ID_HELP);
return TRUE;
}
}
}
// fall through...

case MSGF_DIALOGBOX:    // handles message boxes as well.
pMainWnd = System.GetMainWnd();
if (code == MSGF_DIALOGBOX && m_pActiveWnd != NULL &&
lpMsg->message >= WM_KEYFIRST && lpMsg->message <= WM_KEYLAST)
{
// need to translate messages for the in-place container
___THREAD_STATE* pThreadState = gen_ThreadState.get_data();
ENSURE(pThreadState);

if (pThreadState->m_bInMsgFilter)
return FALSE;
pThreadState->m_bInMsgFilter = TRUE;    // avoid reentering this code
MSG msg = *lpMsg;
if (m_pActiveWnd->IsWindowEnabled() && pre_translate_message(&msg))
{
pThreadState->m_bInMsgFilter = FALSE;
return TRUE;
}
pThreadState->m_bInMsgFilter = FALSE;    // ok again
}
break;
}

return FALSE;   // default to not handled
}*/

/*
/////////////////////////////////////////////////////////////////////////////
// Access to GetMainWnd() & m_pActiveWnd

::user::interaction* thread::GetMainWnd()
{
if (m_pActiveWnd != NULL)
return m_pActiveWnd;    // probably in-place active

// when not inplace active, just return main ::user::interaction_impl
if (GetMainWnd() != NULL)
return GetMainWnd();

return System.get_active_guie();
}

/////////////////////////////////////////////////////////////////////////////
// thread implementation helpers

bool thread::pump_message()
{
try
{
return __internal_pump_message();
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


void thread::assert_valid() const
{
command_target::assert_valid();
}

void thread::dump(dump_context & dumpcontext) const
{
command_target::dump(dumpcontext);
___THREAD_STATE *pState = __get_thread_state();

dumpcontext << "m_pThreadParams = " << m_pThreadParams;
dumpcontext << "\nm_pfnThreadProc = " << (void *)m_pfnThreadProc;
dumpcontext << "\nm_bAutoDelete = " << m_bAutoDelete;
dumpcontext << "\nm_hThread = " << (void *)m_hThread;
dumpcontext << "\nm_nThreadID = " << m_nThreadID;
dumpcontext << "\nm_nDisablePumpCount = " << pState->m_nDisablePumpCount;
if (System.GetThread() == this)
dumpcontext << "\nm_pMainWnd = " << GetMainWnd();

dumpcontext << "\nm_msgCur = {";
dumpcontext << "\n\thwnd = " << (void *)pState->m_msgCur.hwnd;
dumpcontext << "\n\tmessage = " << (UINT)pState->m_msgCur.message;
dumpcontext << "\n\twParam = " << (UINT)pState->m_msgCur.wParam;
dumpcontext << "\n\tlParam = " << (void *)pState->m_msgCur.lParam;
dumpcontext << "\n\ttime = " << pState->m_msgCur.time;
dumpcontext << "\n\tpt = " << point(pState->m_msgCur.pt);
dumpcontext << "\n}";

dumpcontext << "\nm_pThreadParams = " << m_pThreadParams;
dumpcontext << "\nm_pfnThreadProc = " << (void *)m_pfnThreadProc;
dumpcontext << "\nm_ptCursorLast = " << pState->m_ptCursorLast;
dumpcontext << "\nm_nMsgLast = " << pState->m_nMsgLast;

dumpcontext << "\n";
}


bool thread::post_message(sp(::user::interaction) pguie, UINT uiMessage, WPARAM wparam, LPARAM lparam)
{
metrowin::message * pmessage = new metrowin::message;
pmessage->m_pguie       = pguie;
pmessage->m_uiMessage   = uiMessage;
pmessage->m_wparam      = wparam;
pmessage->m_lparam      = lparam;
return PostThreadMessage(WM_APP + 1984, 77, (LPARAM) pmessage);
}


bool thread::on_run_exception(::exception::exception & e)
{
return false;
}


namespace metrowin
{
LRESULT message::send()
{
return m_pguie->SendMessage(m_uiMessage, m_wparam, m_lparam);
}

UINT message::ThreadProcSendMessage(LPVOID lp)
{
message * pmessage = (message *) lp;
pmessage->send();
delete pmessage;
return 0;
}

void message::post(sp(::user::interaction) puie, UINT uiMessage, WPARAM wparam, LPARAM lparam, int nPriority)
{
message * pmessage = new message;
pmessage->m_pguie = puie;
pmessage->m_uiMessage = uiMessage;
pmessage->m_wparam = wparam;
pmessage->m_lparam = lparam;
__begin_thread(puie->get_app(), &ThreadProcSendMessage, pmessage, nPriority);
}*/

// thread

