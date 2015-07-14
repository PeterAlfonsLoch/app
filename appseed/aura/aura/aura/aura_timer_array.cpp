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

      delete_all_timers(); // besides virtual
      

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

      if(ptimer->m_bDeal)
      {

         ptimer->m_bKill = true;

      }
      else
      {

         if(ptimer->m_bDestroying)
         {
            
          
            sl.unlock();
            
         }
         else
         {
            
            ptimer->m_bDestroying = true;

            sl.unlock();
         
            delete ptimer;
            
         }

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

   void timer_array::delete_all_timers()
   {
   
      MAP::pair * ppair = NULL;
      
   restart:
      
      ppair = m_map.PGetFirstAssoc();
   
      if(ppair != NULL)
      {
      
         delete_timer(ppair->m_element1);
         
         goto restart;
      
      }
      
   }


} // namespace user






