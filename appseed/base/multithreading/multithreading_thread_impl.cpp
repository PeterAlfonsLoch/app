//
//  multithreading_thread_impl.cpp
//  base
//
//  Created by Carlos Gustavo Cecyn Lundgren on 16/05/14.
//
//

#include "framework.h"


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


int32_t thread_impl::thread_entry(::thread_startup * pstartup)
{

   UNREFERENCED_PARAMETER(pstartup);

   return -1;

}


int32_t thread_impl::main()
{

   return -1;

}


int32_t thread_impl::thread_term(int32_t nResult)
{

   UNREFERENCED_PARAMETER(nResult);

   return -1;

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

   ENSURE(m_hThread == NULL);  // already created?

   // setup startup structure for thread initialization
   thread_startup startup;
   startup.bError = FALSE;
   startup.pfnNewHandler = NULL;
   //memset(&startup, 0, sizeof(startup));
   //      startup.pThreadState = __get_thread_state();
   startup.pThread = this;
   startup.m_pthread = NULL;
   startup.hEvent = ::CreateEvent(NULL,TRUE,FALSE,NULL);
   startup.hEvent2 = ::CreateEvent(NULL,TRUE,FALSE,NULL);
   startup.dwCreateFlags = dwCreateFlags;
   if(startup.hEvent == NULL || startup.hEvent2 == NULL)
   {
      TRACE(::core::trace::category_AppMsg,0,"Warning: CreateEvent failed in thread::create_thread.\n");
      if(startup.hEvent != NULL)
         ::CloseHandle(startup.hEvent);
      if(startup.hEvent2 != NULL)
         ::CloseHandle(startup.hEvent2);
      return FALSE;
   }

   m_hThread = (HANDLE)(uint_ptr) ::create_thread(lpSecurityAttrs,nStackSize,&__thread_entry,&startup,dwCreateFlags | CREATE_SUSPENDED,&m_nThreadID);

   if(m_hThread == NULL)
      return FALSE;

   // start the thread just for core API initialization
   VERIFY(::ResumeThread(m_hThread) != (DWORD)-1);
   VERIFY(::WaitForSingleObject(startup.hEvent,INFINITE) == WAIT_OBJECT_0);
   ::CloseHandle(startup.hEvent);

   // if created suspended, suspend it until resume thread wakes it up
   if(dwCreateFlags & CREATE_SUSPENDED)
      VERIFY(::SuspendThread(m_hThread) != (DWORD)-1);

   // if error during startup, shut things down
   if(startup.bError)
   {
      VERIFY(::WaitForSingleObject(m_hThread,INFINITE) == WAIT_OBJECT_0);
      ::CloseHandle(m_hThread);
      m_hThread = NULL;
      ::CloseHandle(startup.hEvent2);
      return FALSE;
   }

   // allow thread to continue, once resumed (it may already be resumed)
   ::SetEvent(startup.hEvent2);

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
