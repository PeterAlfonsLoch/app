//
//  multithreading_thread_impl.cpp
//  base
//
//  Created by Carlos Gustavo Cecyn Lundgren on 16/05/14.
//
//

#include "framework.h"

uint32_t __thread_entry(void * pparam);

thread_impl::thread_impl(sp(::base::application) papp):
element(papp),
m_evFinish(papp),
m_mutexUiPtra(papp)

{

   m_hthread = NULL;
   m_uiThread = 0;

}


thread_impl::~thread_impl()
{


}



bool thread_impl::pre_init_instance()
{
   
   return true;
   
}


bool thread_impl::initialize_instance()
{
   
   return true;
   
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
         dispatch_thread_message(pobj);
         if(pobj->m_bRet)
            return;
      }

      sp(::user::interaction) puiTopic = pbase->m_pwnd->m_pui;

      try
      {
         if(m_pbaseapp->m_pbasesession != NULL &&
            &m_pbaseapp->m_pbasesession->frames() != NULL)
         {
            try
            {
               for(int32_t i = 0; i < m_pbaseapp->m_pbasesession->frames().get_count(); i++)
               {
                  try
                  {
                     sp(::user::interaction) pui = m_pbaseapp->m_pbasesession->frames()(i);
                     if(pui != NULL)
                     {
                        if(pui->m_pui != NULL)
                        {
                           pui->m_pui->pre_translate_message(pobj);
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
                  catch(exit_exception & e)
                  {
                     throw e;
                  }
                  catch(...)
                  {
                  }
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
      // force validation of window to prevent getting WM_PAINT again
      ValidateRect(pbase->m_pwnd->get_safe_handle(),NULL);
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

   if(pobj == NULL)
      return;   // not handled

   SCAST_PTR(::message::base,pbase,pobj);

   sp(::user::frame_window) pTopFrameWnd;
   sp(::user::interaction) pMainWnd;
   sp(::user::interaction) pMsgWnd;
   switch(code)
   {
   //case MSGF_DDEMGR:
      // Unlike other WH_MSGFILTER codes, MSGF_DDEMGR should
      //  never call the next hook.
      // By returning FALSE, the message will be dispatched
      //  instead (the default behavior).
      //return;

   case MSGF_MENU:
      pMsgWnd = pbase->m_pwnd;
      if(pMsgWnd != NULL)
      {
         pTopFrameWnd = pMsgWnd->GetTopLevelFrame();
         if(pTopFrameWnd != NULL && pTopFrameWnd->IsTracking() &&
            pTopFrameWnd->m_bHelpMode)
         {
            //pMainWnd = __get_main_window();
            //if((GetMainWnd() != NULL) && (IsEnterKey(pbase) || IsButtonUp(pbase)))
            //{
            //   //                  pMainWnd->SendMessage(WM_COMMAND, ID_HELP);
            //   pbase->m_bRet = true;
            //   return;
            //}
         }
      }
      // fall through...

   case MSGF_DIALOGBOX:    // handles message boxes as well.
      //pMainWnd = __get_main_window();
      if(code == MSGF_DIALOGBOX && m_puiActive != NULL &&
         pbase->m_uiMessage >= WM_KEYFIRST && pbase->m_uiMessage <= WM_KEYLAST)
      {
         //// need to translate messages for the in-place container
         //___THREAD_STATE* pThreadState = __get_thread_state();
         //ENSURE(pThreadState);

         //if (pThreadState->m_bInMsgFilter)
         //   return;
         //pThreadState->m_bInMsgFilter = TRUE;    // avoid reentering this code
         //if (m_puiActive->is_window_enabled())
         //{
         //   pre_translate_message(pobj);
         //   if(pobj->m_bRet)
         //   {
         //      pThreadState->m_bInMsgFilter = FALSE;
         //      return;
         //   }
         //}
         //pThreadState->m_bInMsgFilter = FALSE;    // ok again
      }
      break;
   }
   // default to not handled
}





thread_startup::thread_startup(sp(::base::application) papp) :
   m_event(papp),
   m_event2(papp)
{

}


thread_startup::~thread_startup()
{

}




bool thread_impl::create_thread(int32_t epriority,uint32_t dwCreateFlagsParam,uint_ptr nStackSize,LPSECURITY_ATTRIBUTES lpSecurityAttrs)
{

   DWORD dwCreateFlags = dwCreateFlagsParam;

   if(epriority != ::core::scheduling_priority_normal)
   {
      dwCreateFlags |= CREATE_SUSPENDED;
   }

   ENSURE(m_hthread == NULL);  // already created?

   // setup startup structure for thread initialization
   thread_startup startup(get_app());

   startup.m_bError = FALSE;
   startup.m_pthreadimpl = this;
   startup.m_pthread = m_puser;
   startup.m_dwCreateFlags = dwCreateFlags;

   m_hthread = (HANDLE)(uint_ptr) ::create_thread(lpSecurityAttrs,nStackSize,&__thread_entry,&startup,dwCreateFlags | CREATE_SUSPENDED,&m_uiThread);

   if(m_hthread == NULL)
      return FALSE;

   // start the thread just for core API initialization
   VERIFY(::ResumeThread(m_hthread) != (DWORD)-1);
   startup.m_event.wait();

   // if created suspended, suspend it until resume thread wakes it up
   if(dwCreateFlags & CREATE_SUSPENDED)
      VERIFY(::SuspendThread(m_hthread) != (DWORD)-1);

   // if error during startup, shut things down
   if(startup.m_bError)
   {
      VERIFY(::WaitForSingleObject(m_hthread,INFINITE) == WAIT_OBJECT_0);
      ::CloseHandle(m_hthread);
      m_hthread = NULL;
      return FALSE;
   }

   // allow thread to continue, once resumed (it may already be resumed)
   startup.m_event2.wait();

   if(epriority != ::core::scheduling_priority_normal)
   {

      VERIFY(set_thread_priority(epriority));

      if(!(dwCreateFlagsParam & CREATE_SUSPENDED))
      {
         ENSURE(ResumeThread() != (DWORD)-1);
      }

   }

   return TRUE;

}



void * thread_impl::get_os_data() const
{

   return (void *)m_hthread;

}


int_ptr thread_impl::get_os_int() const
{

   return m_uiThread;

}


HTHREAD thread_impl::item() const
{

   return m_hthread;

}


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



bool thread_impl::is_idle_message(signal_details * pobj)
{

   return ::message::is_idle_message(pobj);

}

bool thread_impl::is_idle_message(LPMSG lpmsg)
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
            pthread->m_pimpl->m_bRun = false;
         }
         catch(...)
         {
         }


      }
      sl.unlock();

   }


   single_lock sl(::multithreading::s_pmutex);

   for(index i = 0; i < ::multithreading::s_phaThread->get_size();)
   {

      bOk = true;

      try
      {

      repeat:

         if(::PostThreadMessageA(::GetThreadId(::multithreading::s_phaThread->element_at(i)),message,wparam,lparam))
         {

            if(message == WM_QUIT)
            {

               if(::multithreading::s_phaThread->element_at(i) != ::GetCurrentThread())
               {

                  sl.unlock();

                  DWORD dwRet = ::WaitForSingleObject(::multithreading::s_phaThread->element_at(i),(1984 + 1977) * 2);

                  sl.lock();

                  if((dwRet != WAIT_OBJECT_0) && (dwRet != WAIT_FAILED) && i < ::multithreading::s_phaThread->get_size())
                     goto repeat;



               }

            }

         }

      }
      catch(...)
      {

         bOk = false;

      }

      sl.lock();

      try
      {
         if(bOk)
         {

            if(ca == ::multithreading::s_phaThread->get_size())
               i++;
            else
               ca = ::multithreading::s_phaThread->get_size();

         }
         else
         {

            ca = ::multithreading::s_phaThread->get_size();

         }

      }
      catch(...)
      {
         break;
      }

   }

}


int32_t thread_impl::exit_instance()
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

               if(NODE_THREAD(pui->m_pthread.m_p) == this || NODE_THREAD(pui->m_pthread->m_pimpl.m_p) == this)
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


   return m_iReturnCode;

} 

bool thread_impl::on_idle(LONG lCount)
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




bool thread_impl::post_message(sp(::user::interaction) pui,UINT uiMessage,WPARAM wparam,lparam lparam)
{
   
   if(m_hthread == NULL)
      return false;

   ::user::message * pmessage = new ::user::message;
   pmessage->m_pui       = pui;
   pmessage->m_uiMessage   = uiMessage;
   pmessage->m_wparam      = wparam;
   pmessage->m_lparam      = lparam;

   return post_thread_message(WM_APP + 1984,77,(LPARAM)pmessage) != FALSE;

}





bool thread_impl::post_thread_message(UINT message,WPARAM wParam,lparam lParam)
{

   if(m_hthread == NULL)
      return false;

   return ::PostThreadMessageA(m_uiThread,message,wParam,lParam) != FALSE;

}





void thread_impl::set_os_data(void * pvoidOsData)
{
   m_hthread = (HANDLE)pvoidOsData;
}

void thread_impl::set_os_int(int_ptr iData)
{
   m_uiThread = (DWORD)iData;
}

void thread_impl::message_queue_message_handler(signal_details * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
}






int32_t thread_impl::thread_entry(::thread_startup * pstartup)
{

   ASSERT(pstartup != NULL);
   ASSERT(pstartup->m_pthread != NULL);
   ASSERT(pstartup->m_pthreadimpl != NULL);
   ASSERT(!pstartup->m_bError);
   ASSERT(pstartup->m_pthreadimpl == pstartup->m_pthread->m_pimpl);
   ASSERT(pstartup->m_pthread == pstartup->m_pthreadimpl->m_puser);
   ASSERT(pstartup->m_pthreadimpl->m_pimpl.is_null());
   ASSERT(pstartup->m_pthread->m_puser.is_null());

   ::thread * pthread = pstartup->m_pthread;

   ::thread_impl * pthreadimpl = pstartup->m_pthreadimpl;

   //      sp(::base::application) papp = (get_app());
   m_evFinish.ResetEvent();
   install_message_handling(pthreadimpl);
   m_puser->install_message_handling(pthreadimpl);

   IGUI_WIN_MSG_LINK(WM_USER + 123,pthreadimpl,pthreadimpl,&thread_impl::_001OnCreateMessageWindow);

   return 0;   // not reached

}


int32_t thread_impl::main()
{

   /*      ___THREAD_STARTUP* pStartup = (___THREAD_STARTUP*)pstartup;
   ASSERT(pStartup != NULL);
   ASSERT(pStartup->pThreadState != NULL);
   ASSERT(pStartup->pThread != NULL);
   ASSERT(!pStartup->bError);*/

   if(!m_puser->pre_init_instance())
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
   else if(!m_puser->initialize_instance())
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
         m_puser->m_bReady = true;
         m_bRun = true;
         m_puser->m_bRun = true;
         nResult = m_puser->run();
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

int32_t thread_impl::thread_term(int32_t nResult)
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






void thread_impl::add(sp(::user::interaction) pui)
{
   single_lock sl(&m_mutexUiPtra,TRUE);
   if(m_puiptra != NULL)
   {
      m_puiptra->add(pui);
   }
}

void thread_impl::remove(::user::interaction * pui)
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


::count thread_impl::get_ui_count()
{

   single_lock sl(&m_mutexUiPtra,TRUE);

   return m_puiptra->get_count();

}


::user::interaction * thread_impl::get_ui(index iIndex)
{

   single_lock sl(&m_mutexUiPtra,TRUE);

   return m_puiptra->element_at(iIndex);

}




void thread_impl::set_timer(sp(::user::interaction) pui,uint_ptr nIDEvent,UINT nEllapse)
{

   m_ptimera->set(pui,nIDEvent,nEllapse);

   if(!m_bCreatingMessageWindow && m_spuiMessage.is_null())
   {
      _001PostCreateMessageWindow();
   }

}

void thread_impl::unset_timer(sp(::user::interaction) pui,uint_ptr nIDEvent)
{
   m_ptimera->unset(pui,nIDEvent);
}

void thread_impl::set_auto_delete(bool bAutoDelete)
{
   m_bAutoDelete = bAutoDelete;
}

void thread_impl::set_run(bool bRun)
{
   m_bRun = bRun;
}

event & thread_impl::get_finish_event()
{
   return m_evFinish;
}

bool thread_impl::get_run()
{
   return m_bRun;
}

sp(::user::interaction) thread_impl::get_active_ui()
{
   return m_puiActive;
}

sp(::user::interaction) thread_impl::set_active_ui(sp(::user::interaction) pui)
{
   sp(::user::interaction) puiPrevious = m_puiActive;
   m_puiActive = pui;
   return puiPrevious;
}

void thread_impl::step_timer()
{
   if(m_ptimera == NULL)
      return;
   m_ptimera->check();
}





thread_impl::operator HTHREAD() const
{

   return this == NULL ? NULL : m_hthread;

}



void thread_impl::_001PostCreateMessageWindow()
{

   post_thread_message(WM_USER + 123);

}


void thread_impl::_001OnCreateMessageWindow(signal_details * pobj)
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


