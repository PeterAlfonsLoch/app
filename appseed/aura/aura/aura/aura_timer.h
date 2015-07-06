#pragma once


class CLASS_DECL_AURA timer :
   virtual public object
{
public:


   enum e
   {
      e_start = 1000000,
      hover = e_start,
      e_end

   };



   uint_ptr             m_nIDEvent;
   PFN_TIMER            m_pfnTimer;
   timer_callback *     m_pcallback;
   bool                 m_bPeriodic;
   void *               m_pvoidData;
   bool                 m_bRet;

#ifdef WINDOWS

   HANDLE hTimerQueue;
   HANDLE hTimer;
#else

   timer_t timerid;
   struct sigevent sev;
   struct itimerspec its;
#endif

   
   timer(::aura::application * papp,uint_ptr uiTimer = 0,PFN_TIMER pfnTimer = NULL,void * pvoidData = NULL);
   virtual ~timer();

   virtual bool start(int millis, bool bPeriodic);

   virtual void stop();

   virtual bool on_timer();


};


