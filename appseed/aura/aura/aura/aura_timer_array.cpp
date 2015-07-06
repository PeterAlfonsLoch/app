//#include "framework.h" // previously aura/user/user.h


namespace aura
{

   timer_array::timer_array() :
      timer_array(get_app())
   {
   }


   timer_array::timer_array(::aura::application * papp):
      object(papp),
      m_mutex(papp)
   {

   }


   timer_array::~timer_array()
   {

   }

   bool timer_array::create_timer(uint_ptr nIDEvent,UINT nEllapse, PFN_TIMER pfnTimer, bool bPeriodic, void * pvoidData)
   {

      synch_lock sl(&m_mutex);

      MAP::pair * ppair = m_map.PLookup(nIDEvent);

      if(ppair == NULL)
      {

         m_map.set_at(nIDEvent,new timer(get_app(),nIDEvent,pfnTimer, pvoidData));

         ppair = m_map.PLookup(nIDEvent);

      }

      ppair->m_element2->m_pcallback = this;

      ppair->m_element2->start(nEllapse,bPeriodic);

      return ppair->m_element2;

   }

   bool timer_array::delete_timer(uint_ptr nIDEvent)
   {

      synch_lock sl(&m_mutex);

      MAP::pair * ppair = m_map.PLookup(nIDEvent);

      if(ppair == NULL)
         return true;

      delete ppair->m_element2;

      m_map.remove_key(nIDEvent);

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






