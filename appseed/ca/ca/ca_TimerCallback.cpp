#include "framework.h"

namespace ca
{

   TimerCallback::TimerCallback()
   {
      m_bQueueModel = false;
      m_ptimerwnd = ::null();
       Enable();
   }

   TimerCallback::~TimerCallback()
   {
   }

   void TimerCallback::Enable(bool bEnable)
   {
      m_bTimerCallbackEnable = bEnable;
      if(m_ptimerwnd != ::null())
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

} // namespace ca



