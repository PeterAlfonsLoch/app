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

#ifdef METROWIN

   Threading::ThreadPoolTimer ^     m_timer;

#elif WINDOWS

   HANDLE                           m_hTimerQueue;
   HANDLE                           m_hTimer;

#elif defined(__APPLE__)            
    
   void *                           m_queue;
   void *                           m_timer;

#else

   timer_t                          m_timerid;
   struct sigevent                  m_sev;
   struct itimerspec                m_its;


#endif

   
   timer(::aura::application * papp,uint_ptr uiTimer = 0,PFN_TIMER pfnTimer = NULL,void * pvoidData = NULL, mutex * pmutex = NULL);
   virtual ~timer();

   virtual bool start(int millis, bool bPeriodic);

   virtual void stop();

   virtual bool call_on_timer();

   virtual bool on_timer();


};


