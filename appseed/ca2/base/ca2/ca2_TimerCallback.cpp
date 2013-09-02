#include "framework.h"

namespace ca2
{

   TimerCallback::TimerCallback()
   {
      m_bQueueModel = false;
      m_ptimerwnd = NULL;
       Enable();
   }

   TimerCallback::~TimerCallback()
   {
   }

   void TimerCallback::Enable(bool bEnable)
   {
      m_bTimerCallbackEnable = bEnable;
      if(m_ptimerwnd != NULL)
      {
         m_ptimerwnd->EnableTimer(bEnable);
      }
   }

   bool TimerCallback::IsEnabled()
   {
       return m_bTimerCallbackEnable;

   }

   bool TimerCallback::SetTimerWindow(TimerWnd *ptimerwnd)
   {
      m_ptimerwnd = ptimerwnd;
      return true;
   }


   bool TimerCallback::WishesQueueModel()
   {
      return m_bQueueModel;
   }

} // namespace ca2



