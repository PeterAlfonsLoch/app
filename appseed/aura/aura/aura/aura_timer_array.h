#pragma once


namespace aura
{


   class CLASS_DECL_AURA timer_array:
      virtual public ::object,
      virtual public timer_callback
   {
   public:

      

      typedef map < uint_ptr,uint_ptr,timer *, timer  * > MAP;

      MAP        m_map;

      mutex       m_mutex;

      timer_array();
      timer_array(::aura::application * papp);
      virtual ~timer_array();



      virtual bool SetTimer(uint_ptr nIDEvent,UINT nEllapse);
      virtual bool KillTimer(uint_ptr nIDEvent);

      virtual void on_timer(timer * ptimer);
      virtual void _001OnTimer(timer * ptimer);

   };



} // namespace aura


























































