//#include "framework.h" // previously aura/user/user.h


namespace aura
{


   timer_array::timer_array(::aura::application * papp):
      object(papp),
      m_mutex(papp)
   {

   }


   timer_array::~timer_array()
   {

      MAP::pair * ppair = m_map.PGetFirstAssoc();

      while(ppair != NULL)
      {

         delete ppair->m_element2;

         ppair = m_map.PGetNextAssoc(ppair);

      }

   }

   bool timer_array::create_timer(uint_ptr nIDEvent,UINT nEllapse, PFN_TIMER pfnTimer, bool bPeriodic, void * pvoidData)
   {

      delete_timer(nIDEvent);

      synch_lock sl(&m_mutex);

      timer * ptimer = new timer(get_app(),nIDEvent,pfnTimer,pvoidData, &m_mutex);

      ptimer->m_pcallback = this;

      m_map.set_at(nIDEvent, ptimer);

      sl.unlock();

      if(!ptimer->start(nEllapse,bPeriodic))
      {

         sl.lock();

         m_map.remove_key(nIDEvent);

         return false;

      }

      return true;

   }

   bool timer_array::delete_timer(uint_ptr nIDEvent)
   {

      synch_lock sl(&m_mutex);

      MAP::pair * ppair = m_map.PLookup(nIDEvent);

      if(ppair == NULL)
         return true;

      timer * ptimer = ppair->m_element2;

      m_map.remove_key(nIDEvent);

      sl.unlock();

      if(ptimer->m_bDeal)
      {

         ptimer->m_bKill = true;

      }
      else
      {

         ptimer->m_bKill = true;

         delete ptimer;

      }

      return true;

   }


   bool timer_array::on_timer(timer * ptimer)
   {

      if(ptimer->m_pcallback == this)
      {

         _001OnTimer(ptimer);

      }

      if(!ptimer->m_bPeriodic)
      {

         delete_timer(ptimer->m_nIDEvent);

      }


      return true;

   }


   void timer_array::_001OnTimer(timer * ptimer)
   {

   }


} // namespace user






