#include "framework.h"

namespace gen
{


   TimerWnd::TimerWnd() :
      m_evFree(FALSE, TRUE)
   {
      EnableTimer();
   }

   TimerWnd::~TimerWnd()
   {

   //    if(m_pTimerCallbackFinal != NULL)
     //  {
       //    m_pTimerCallbackFinal->m_evTimerWndDeleted.SetEvent();
         //  m_pTimerCallbackFinal = NULL;
       //}
   }


   // // BEGIN_MESSAGE_MAP(TimerWnd, ::ca::window)
      //{{__MSG_MAP(TimerWnd)
   /* xxx   ON_WM_TIMER()
      ON_WM_DESTROY()
      ON_WM_CLOSE()
      //}}__MSG_MAP
      ON_MESSAGE(WM_USER, OnUserMessage) */
   // // END_MESSAGE_MAP()


   /////////////////////////////////////////////////////////////////////////////
   // TimerWnd message handlers

   bool TimerWnd::create(TimerCallback *pCallback)

   {
       m_pTimerCallback = pCallback;
   ///    m_pTimerCallbackFinal = m_pTimerCallback;
       rect rect(0, 0, 0, 0);
       const char * lpcStr = System.RegisterWndClass(0);
       return ::ca::window::CreateEx(0,lpcStr, "Timer Window", 0, rect, NULL, id());
   }

   void TimerWnd::OnTimer(UINT nIDEvent)
   {
      // TODO: add your message handler code here and/or call default
   //    try
   //    {
   //    try
   //    {
   //    single_lock sl(&m_mutexSkipConcurrency, false);
   //    if(m_bSkipConcurrency)
   //    {
   //        if(!sl.lock(0))
   //            return;
   //    }

#ifdef WINDOWS

       long lElapsed = GetTickCount() - GetMessageTime();
       //TRACE("Elapsed %d /n", lElapsed);
       if(lElapsed > 1000)
       {
   //        ASSERT(FALSE);
           return;
       }

#endif

       if(m_bEnable && m_pTimerCallback != NULL)
           if(m_pTimerCallback->IsEnabled())
           {
   //         if(m_pTimerCallback->WishesQueueModel())
   //         {
   //            PostMessage(WM_USER, nIDEvent);
   //         }
   //         else
            {
   //            m_evFree.ResetEvent();
   #ifndef DEBUG
               try
               {
   #endif
               m_pTimerCallback->TimerProc(nIDEvent);
   #ifndef DEBUG
               }
               catch(...)
               {
               }
   #endif
            }
   //            m_evFree.SetEvent();
           }
   //    }
   //    catch(...)
   //    {
   //       System.simple_message_box("TimerWnd::OnTimer Exception");
   //    }
       //}
   //    catch(...)
     //  {
       //    ASSERT(FALSE);
       //}

      //::ca::window::OnTimer(nIDEvent);
   }

   void TimerWnd::OnDestroy()
   {
       m_pTimerCallback = NULL;
   //   ::ca::window::OnDestroy();

       //m_pTimerCallbackFinal = m_pTimerCallback;

       //MSG msg;

   //    while(PeekMessage(&msg, m_hWnd, WM_TIMER, WM_TIMER, PM_REMOVE))
     //  {
       //    KillTimer(msg.wParam);
   //    }


      // TODO: add your message handler code here

   }

   void TimerWnd::OnClose()
   {
      // TODO: add your message handler code here and/or call default

   //   ::ca::window::OnClose();
       DestroyWindow();
   }

   bool TimerWnd::DestroyWindow()
   {
      // TODO: add your specialized code here and/or call the base class

      if(::ca::window::DestroyWindow())
       {
           delete this;
           return TRUE;
       }
       else
       {
           return FALSE;
       }
   }

   bool TimerWnd::EnableTimer(bool bEnable)
   {
      bool b = m_bEnable;
      m_bEnable = bEnable;
      return b;
   }

   bool TimerWnd::IsEnabled()
   {
      return m_bEnable;
   }

   // Purpose:
   // Handle Queue Model Message Posts
   //
   LRESULT TimerWnd::OnUserMessage(WPARAM wparam, LPARAM lparam)
   {
      UNREFERENCED_PARAMETER(lparam);

      // processor saving remark but should not be a remark
      // ASSERT(m_pTimerCallback->WishesQueueModel());
      // END processor saving remark but should not be a remark

   #ifndef DEBUG
               try
               {
   #endif
               m_pTimerCallback->TimerProc(wparam); // ASSERT(wparam == nIDEvent)
   #ifndef DEBUG
               }
               catch(...)
               {
               }
   #endif
      return 0;
   }

} // namespace gen


