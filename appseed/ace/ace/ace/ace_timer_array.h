#pragma once


namespace ace
{


   class CLASS_DECL_AURA timer_array:
      virtual public ::object,
      virtual public timer_callback
   {
   public:

      typedef map < uint_ptr,uint_ptr,timer *, timer  * > MAP;

      MAP        m_map;

      mutex       m_mutex;

      
      timer_array(::ace::application * papp);
      virtual ~timer_array();



      virtual bool create_timer(uint_ptr nIDEvent,UINT nEllapse,PFN_TIMER pfnTimer, bool bPeriodic = true, void * pvoidData = NULL);
      virtual bool delete_timer(uint_ptr nIDEvent);
      
      virtual void delete_all_timers();

      virtual bool on_timer(timer * ptimer);
      virtual void _001OnTimer(::timer * ptimer);

   };



} // namespace ace


























































