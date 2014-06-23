#include "framework.h"


namespace core
{


   timer_callback::timer_callback()
   {
      m_bQueueModel = false;
      m_ptimer = NULL;
      Enable();
   }

   timer_callback::~timer_callback()
   {
   }

   void timer_callback::Enable(bool bEnable)
   {
      m_bTimerCallbackEnable = bEnable;
      if(m_ptimer != NULL)
      {
         m_ptimer->EnableTimer(bEnable);
      }
   }

   bool timer_callback::IsEnabled()
   {
      return m_bTimerCallbackEnable;

   }

   bool timer_callback::set_timer(timer *ptimerwnd)
   {
      m_ptimer = ptimerwnd;
      return true;
   }


   bool timer_callback::WishesQueueModel()
   {
      return m_bQueueModel;
   }


} // namespace core





