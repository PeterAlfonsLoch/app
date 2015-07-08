#pragma once


class timer_callback;


class CLASS_DECL_AURA timer :
   virtual public thread
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
   bool                 m_bDeal;
   bool                 m_bKill;
   mutex *              m_pmutex;
   DWORD                m_dwMillis;
   bool                 m_bDestroying;

#ifdef WINDOWS

   HANDLE hTimerQueue;
   HANDLE hTimer;
#elif defined(__APPLE__)
    void *              m_queue;
    void *              m_timer;
#else

   timer_t timerid;
   struct sigevent sev;
   struct itimerspec its;
#endif

   
   timer(::aura::application * papp,uint_ptr uiTimer = 0,PFN_TIMER pfnTimer = NULL,void * pvoidData = NULL, mutex * pmutex = NULL);
   virtual ~timer();

   virtual bool start(int millis, bool bPeriodic);

   virtual void stop();

   virtual bool call_on_timer();

   virtual bool on_timer();


};


