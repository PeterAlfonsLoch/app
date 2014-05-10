#include "framework.h"



timer_window::timer_window() :
   m_evFree(NULL, FALSE, TRUE)
{
   EnableTimer();
}

timer_window::~timer_window()
{

   //    if(m_pTimerCallbackFinal != NULL)
   //  {
   //    m_pTimerCallbackFinal->m_evTimerWndDeleted.SetEvent();
   //  m_pTimerCallbackFinal = NULL;
   //}
}


// // BEGIN_MESSAGE_MAP(timer_window, window)
//{{__MSG_MAP(timer_window)
/* xxx   ON_WM_TIMER()
ON_WM_DESTROY()
ON_WM_CLOSE()
//}}__MSG_MAP
ON_MESSAGE(WM_USER, OnUserMessage) */
// // END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// timer_window message handlers

bool timer_window::create(timer_callback *pCallback)

{
   m_pTimerCallback = pCallback;
   ///    m_pTimerCallbackFinal = m_pTimerCallback;
   rect rect(0, 0, 0, 0);

   return window::CreateEx(0,NULL, "timer Window", 0, rect, NULL, id());
}

void timer_window::OnTimer(UINT nIDEvent)
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

#ifdef WINDOWSEX

   long lElapsed = get_tick_count() - GetMessageTime();
   //TRACE("Elapsed %d /n", lElapsed);
   if(lElapsed > 1000)
   {
      //        ASSERT(FALSE);
      return;
   }

#else

   throw todo(get_app());

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
#if !defined(DEBUG) || defined(WINDOWS)
            try
            {
#endif
               m_pTimerCallback->TimerProc(nIDEvent);
#if !defined(DEBUG) || defined(WINDOWS)
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
      //       System.simple_message_box("timer_window::OnTimer Exception");
      //    }
      //}
      //    catch(...)
      //  {
      //    ASSERT(FALSE);
      //}

      //window::OnTimer(nIDEvent);
}

void timer_window::OnDestroy()
{
   m_pTimerCallback = NULL;
   //   window::OnDestroy();

   //m_pTimerCallbackFinal = m_pTimerCallback;

   //MESSAGE msg;

   //    while(PeekMessage(&msg, m_oswindow_, WM_TIMER, WM_TIMER, PM_REMOVE))
   //  {
   //    KillTimer(msg.wParam);
   //    }


   // TODO: add your message handler code here

}

void timer_window::OnClose()
{
   // TODO: add your message handler code here and/or call default

   //   window::OnClose();
   DestroyWindow();
}

bool timer_window::DestroyWindow()
{
   // TODO: add your specialized code here and/or call the base class

   if(window::DestroyWindow())
   {
      delete this;
      return TRUE;
   }
   else
   {
      return FALSE;
   }
}

bool timer_window::EnableTimer(bool bEnable)
{
   bool b = m_bEnable;
   m_bEnable = bEnable;
   return b;
}

bool timer_window::IsEnabled()
{
   return m_bEnable;
}

// Purpose:
// Handle Queue Model Message Posts
//
LRESULT timer_window::OnUserMessage(WPARAM wparam, LPARAM lparam)
{
   UNREFERENCED_PARAMETER(lparam);

   // processor saving remark but should not be a remark
   // ASSERT(m_pTimerCallback->WishesQueueModel());
   // END processor saving remark but should not be a remark

#if !defined(DEBUG) || defined(WINDOWS)
   try
   {
#endif
      m_pTimerCallback->TimerProc(wparam); // ASSERT(wparam == nIDEvent)
#if !defined(DEBUG) || defined(WINDOWS)
   }
   catch(...)
   {
   }
#endif
   return 0;
}

