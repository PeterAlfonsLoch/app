#pragma once


class CLASS_DECL_ACE timer_event:
   virtual public timer
{
public:

   
   manual_reset_event   m_ev;


   timer_event(::ace::application * papp,int iTimer);
   virtual ~timer_event();


   virtual bool wait(int millis);


   virtual bool on_timer();


};






