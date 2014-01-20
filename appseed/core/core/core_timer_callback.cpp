#include "framework.h"


timer_callback::timer_callback()
{
   m_bQueueModel = false;
   m_ptimerwnd = NULL;
   Enable();
}

timer_callback::~timer_callback()
{
}

void timer_callback::Enable(bool bEnable)
{
   m_bTimerCallbackEnable = bEnable;
   if(m_ptimerwnd != NULL)
   {
      m_ptimerwnd->EnableTimer(bEnable);
   }
}

bool timer_callback::IsEnabled()
{
   return m_bTimerCallbackEnable;

}

bool timer_callback::SetTimerWindow(timer_window *ptimerwnd)
{
   m_ptimerwnd = ptimerwnd;
   return true;
}


bool timer_callback::WishesQueueModel()
{
   return m_bQueueModel;
}




