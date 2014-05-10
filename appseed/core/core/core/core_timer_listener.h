#pragma once


class timer_listener  
{
public:


   timer_listener();
   virtual ~timer_listener();


   virtual void TimerProc(UINT nID) = 0;


};




