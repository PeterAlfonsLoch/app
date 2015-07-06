#pragma once

#ifdef WINDOWS
#else
#include <signal.h>
#include <time.h>
#endif

class timer;

typedef void FN_TIMER(timer * ptimer);
typedef FN_TIMER * PFN_TIMER;

class CLASS_DECL_AURA timer_callback
{

public:

   virtual void on_timer(timer * ptimer) {}

};



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

#ifdef WINDOWS

   HANDLE hTimerQueue;
   HANDLE hTimer;
#else

   timer_t timerid;
   struct sigevent sev;
   struct itimerspec its;
#endif

   timer(::aura::application * papp,uint_ptr uiTimer = 0, PFN_TIMER pfnTimer = NULL, void * pvoidData = NULL) :
      object(papp),
      m_nIDEvent(uiTimer),
      m_pfnTimer(pfnTimer),
      m_pvoidData(pvoidData)
   {
      m_pcallback = NULL;
      // Create the timer queue.

#ifdef LINUX

      /*           sigset_t mask;
      struct sigaction sa;


      /* Establish handler for timer signal */


      ZERO(sev);

      sev.sigev_notify = SIGEV_THREAD;
      sev.sigev_signo = 0;
      sev.sigev_value.sival_ptr = this;
      sev.sigev_notify_function = handler;
      if(timer_create(CLOCK_REALTIME,&sev,&timerid) == -1)
         throw - 1;

#else
      hTimerQueue = CreateTimerQueue();
      if(NULL == hTimerQueue)
      {
         throw - 1;
      }
#endif
   }

   ~timer()
   {

      stop();

#ifdef WINDOWS

      DeleteTimerQueue(hTimerQueue);

#else

      timer_delete(timerid);

#endif

   }

#ifdef WINDOWS
      
   static VOID CALLBACK TimerRoutine(PVOID lpParam,BOOLEAN TimerOrWaitFired)
   {
         
      timer * ptimer = (timer *)lpParam;

      ptimer->on_timer();

   }

#else

   static void handler(sigval sigval)
   {

      millis_timer * ptimer = (millis_timer *)sigval.sival_ptr;

      ptimer->on_timer();

   }

#endif

   bool start(int millis, bool bPeriodic)
   {

      stop();

      m_bPeriodic = bPeriodic;

#ifdef LINUX
      /* Start the timer */

      its.it_value.tv_sec = millis / 1000; // expiration
      its.it_value.tv_nsec = (millis * 1000 * 1000) % (1000 * 1000 * 1000); // expiration
      if(bPeriodic)
      {
         its.it_interval.tv_sec = 0; // no freq
         its.it_interval.tv_nsec = 0; // no freq
      }
      else
      {
         its.it_value.tv_sec = millis / 1000; // freq period
         its.it_value.tv_nsec = (millis * 1000 * 1000) % (1000 * 1000 * 1000); // freq period
      }

      if(timer_settime(timerid,0,&its,NULL) == -1)
         return false;

#else
         
      if(!CreateTimerQueueTimer(&hTimer,hTimerQueue,(WAITORTIMERCALLBACK)TimerRoutine,this,millis,bPeriodic ? millis : 0,0))
      {
            
         return false;

      }

#endif

      return true;

   }

   virtual void stop()
   {
#ifdef WINDOWS
         
      if(hTimer != NULL)
      {
            
         DeleteTimerQueueTimer(hTimerQueue,hTimer,INVALID_HANDLE_VALUE);

         hTimer = NULL;

      }

#else

      timer_settime(timerid,0,NULL,NULL);
            

#endif
   }


   virtual void on_timer()
   {

      if(m_pcallback != NULL)
      {

         m_pcallback->on_timer(this);

      }

      if(m_pfnTimer != NULL)
      {

         m_pfnTimer(this);

      }

   }


};


class timer_event :
   virtual public timer,
   virtual public manual_reset_event
{
public:


   timer_event(::aura::application * papp,int iTimer):
      object(papp),
      timer(papp, iTimer),
      manual_reset_event(papp)
   {

   }

   virtual ~timer_event()
   {


   }

   bool wait(int millis)
   {

      start(millis, false);

      manual_reset_event::wait();

      return true;
}




};

