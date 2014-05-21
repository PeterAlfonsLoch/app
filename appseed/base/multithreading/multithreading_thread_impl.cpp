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

   m_evFinish.SetEvent();
   m_pThreadParams = NULL;
   m_pfnThreadProc = NULL;
   
   
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
   m_evFinish.SetEvent();
   m_pfnThreadProc = pfnThreadProc;
   m_pThreadParams = pParam;
   
   CommonConstruct();
}


void thread_impl::CommonConstruct()
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

      sp(::user::interaction) puiTopic = pbase->m_pwnd.is_null() ? NULL : pbase->m_pwnd->m_pui;

      try
      {
         if(m_pbaseapp->m_pbasesession != NULL)
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
            //if((m_puiMain != NULL) && (IsEnterKey(pbase) || IsButtonUp(pbase)))
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
   element(papp),
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

   ENSURE(m_hthread == NULL);

   sp(thread_startup) pstartup = canew(thread_startup(get_app()));

   pstartup->m_bError = FALSE;

   pstartup->m_pthreadimpl = this;

   pstartup->m_pthread = m_puser;

   pstartup->m_dwCreateFlags = dwCreateFlags;

   m_hthread = (HTHREAD)(uint_ptr) ::create_thread(lpSecurityAttrs,nStackSize,&__thread_entry,pstartup.m_p,dwCreateFlags | CREATE_SUSPENDED,&m_uiThread);

   if(m_hthread == NULL)
      return false;

   VERIFY(::ResumeThread(m_hthread) != (DWORD)-1);

   pstartup->m_event.wait();

   pstartup->m_event2.SetEvent();

   VERIFY(set_thread_priority(epriority));

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
      #ifdef WINDOWSEX

      ::CoInitializeEx(NULL,COINIT_MULTITHREADED);

      pthreadimpl->::exception::translator::attach();
      #endif

      try
      {

         ::multithreading::__node_on_init_thread(::GetCurrentThread(),pthread);

      }
      catch(::exception::base *)
      {

         pstartup->m_bError = TRUE;

         pstartup->m_event.set_event();

         ::multithreading::__node_on_term_thread(::GetCurrentThread(),pthread,-1);

         ASSERT(FALSE);  // unreachable

      }




      pthreadimpl->thread_entry(pstartup);


      // allow the creating thread to return from thread::create_thread
      pstartup->m_event.set_event();

      // wait for thread to be resumed
      pstartup->m_event2.wait();

      pstartup.release();

      int32_t n;

      try
      {

         n = pthreadimpl->m_puser->main();

      }
      catch(::exit_exception &)
      {

         pthreadimpl->m_puser->post_to_all_threads(WM_QUIT,0,0);

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

         if(::PostThreadMessage(::GetThreadId(::multithreading::s_phaThread->element_at(i)),message,wparam,lparam))
         {

            if(message == WM_QUIT)
            {

               if(::multithreading::s_phaThread->element_at(i) != ::GetCurrentThread())
               {
DWORD dwRet = 0;
                  sl.unlock();
#ifdef WINDOWSEX
                  dwRet = ::WaitForSingleObject(::multithreading::s_phaThread->element_at(i),(1984 + 1977) * 2);
#endif
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

               if(pui->m_pthread->m_pimpl == this)
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

#if defined(WINDOWS) && defined(DEBUG) && !defined(___NO_DEBUG_CRT)
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

#if defined(WINDOWS) && defined(DEBUG) && !defined(___NO_DEBUG_CRT)
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

   return ::PostThreadMessage(m_uiThread,message,wParam,lParam) != FALSE;

}





void thread_impl::set_os_data(void * pvoidOsData)
{
   m_hthread = (HTHREAD)pvoidOsData;
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

   ::thread_impl * pthreadimpl = pstartup->m_pthreadimpl;

   m_evFinish.ResetEvent();

   install_message_handling(pthreadimpl);

   m_puser->install_message_handling(pthreadimpl);

   IGUI_WIN_MSG_LINK(WM_USER + 123,pthreadimpl,pthreadimpl,&thread_impl::_001OnCreateMessageWindow);

   return 0;

}


int32_t thread_impl::main()
{

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
      ::multithreading::__node_on_term_thread(GetCurrentThread(), m_puser,nResult);
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
      if(pui->m_pthread->m_pimpl == this)
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
         if(pui->m_pimpl->m_pthread->m_pimpl == this)
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
         if(pui->m_pui->m_pthread->m_pimpl == this)
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





// main running routine until thread exits
int32_t thread_impl::run()
{

   ASSERT_VALID(this);

   // for tracking the idle time state
   bool bIdle = TRUE;
   LONG lIdleCount = 0;

   // acquire and dispatch messages until a WM_QUIT message is received.
   MESSAGE msg;
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




void thread_impl::message_handler(signal_details * pobj)
{

   SCAST_PTR(::message::base,pbase,pobj);

   ::window_sp pwindow = pbase->m_pwnd->get_wnd();

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

      TRACE(::core::trace::category_AppMsg,0,"Warning: Uncaught exception in message_handler (returning %ld).\n",pbase->get_lresult());

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
                  if(m_puser != NULL)
                  {
                     m_puser->pre_translate_message(spbase);
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



               //__pre_translate_message(spbase);
               //if(spbase->m_bRet)
                 // return TRUE;

          //     spbase.release();
            }
         }
         #ifdef WINDOWSEX
         {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
         }
         #endif
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


bool thread_impl::set_thread_priority(int32_t priority)
{

   return ::SetThreadPriority(m_hthread, priority) != 0;

}


int32_t thread_impl::get_thread_priority()
{

   return ::GetThreadPriority(m_hthread);

}




bool thread_impl::begin(int32_t epriority,uint_ptr nStackSize,uint32_t dwCreateFlags,LPSECURITY_ATTRIBUTES lpSecurityAttrs)
{

   if(!create_thread(epriority,dwCreateFlags,nStackSize,lpSecurityAttrs))
   {
      Delete();
      return false;
   }

   return true;

}


void thread_impl::Delete()
{
   if(m_bAutoDelete)
   {
      try
      {
         if(m_pappDelete != NULL)
            m_pappDelete.release();
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






