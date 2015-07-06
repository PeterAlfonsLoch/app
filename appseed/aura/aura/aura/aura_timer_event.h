#pragma once


class CLASS_DECL_AURA timer_event:
   virtual public timer,
   virtual public manual_reset_event
{
public:


   timer_event(::aura::application * papp,int iTimer);
   virtual ~timer_event();


   bool wait(int millis);


};






