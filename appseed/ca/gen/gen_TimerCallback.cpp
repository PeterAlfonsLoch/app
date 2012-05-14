#include "framework.h"

namespace gen
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

   /*bool TimerCallback::InstallTimerCallbackHook()
   {
      C000WndInterface * pwndinterface = dynamic_cast < C000WndInterface * > (this);
      
      if(pwndinterface != NULL)
      {
         pwndinterface->_000HookBeforeWndProc(this);
         return true;
      }

      return false;

   }*/

   /*bool TimerCallback::_000BeforeWndProc(UINT message, WPARAM wparam, LPARAM lparam, LRESULT & lresult)
   {
      switch(message)
      {
      case WM_DESTROY:
         m_ptimerwnd->EnableTimer(false);
         break;
      }

      return false;
   }*/
   bool TimerCallback::WishesQueueModel()
   {
      return m_bQueueModel;
   }

} // namespace gen



