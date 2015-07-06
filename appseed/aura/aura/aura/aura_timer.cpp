
#ifdef WINDOWS
#else
#include <signal.h>
#include <time.h>
#endif

#ifdef WINDOWS

VOID CALLBACK aura_timer_TimerRoutine(PVOID lpParam,BOOLEAN TimerOrWaitFired);

#else

void aura_timer_handler(sigval sigval);

#endif





timer::timer(::aura::application * papp,uint_ptr uiTimer ,PFN_TIMER pfnTimer ,void * pvoidData, mutex * pmutex):
object(papp),
m_nIDEvent(uiTimer),
m_pfnTimer(pfnTimer),
m_pvoidData(pvoidData),
m_pmutex(pmutex)
{
   m_pcallback = NULL;
   // Create the timer queue.

#ifdef WINDOWS
   hTimerQueue = CreateTimerQueue();
   if (NULL == hTimerQueue)
   {
      throw - 1;
   }


#else
   /*           sigset_t mask;
   struct sigaction sa;


   /* Establish handler for timer signal */


   ZERO(sev);

   sev.sigev_notify = SIGEV_THREAD;
   sev.sigev_signo = 0;
   sev.sigev_value.sival_ptr = this;
   sev.sigev_notify_function = aura_timer_handler;
   if (timer_create(CLOCK_REALTIME, &sev, &timerid) == -1)
      throw - 1;
#endif

   m_bRet = false;
   m_bKill = false;
}

timer::~timer()
{

   stop();

#ifdef WINDOWS

   DeleteTimerQueue(hTimerQueue);

#else

   timer_delete(timerid);

#endif

}


bool timer::start(int millis,bool bPeriodic)
{

   stop();

   m_bPeriodic = bPeriodic;

#ifdef LINUX
   if (!CreateTimerQueueTimer(&hTimer, hTimerQueue, (WAITORTIMERCALLBACK)aura_timer_TimerRoutine, this, millis, bPeriodic ? millis : 0, 0))
   {

      return false;

   }

#else
   /* Start the timer */

   its.it_value.tv_sec = millis / 1000; // expiration
   its.it_value.tv_nsec = (millis * 1000 * 1000) % (1000 * 1000 * 1000); // expiration
   if (bPeriodic)
   {
      its.it_interval.tv_sec = 0; // no freq
      its.it_interval.tv_nsec = 0; // no freq
   }
   else
   {
      its.it_value.tv_sec = millis / 1000; // freq period
      its.it_value.tv_nsec = (millis * 1000 * 1000) % (1000 * 1000 * 1000); // freq period
   }

   if (timer_settime(timerid, 0, &its, NULL) == -1)
      return false;


#endif

   return true;

}

void timer::stop()
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


bool timer::call_on_timer()
{
   
   synch_lock sl(m_pmutex);

   if(m_bKill)
      return true;

   m_bDeal = true;

   m_bRet = false;

   sl.unlock();

   on_timer();

   sl.lock();

   if(m_bKill)
   {

      sl.unlock();

      delete this;

      return false;

   }

   m_bDeal = false;

   return !m_bRet;

}

bool timer::on_timer()
{
   
   if(m_pfnTimer != NULL)
   {

      if(!m_pfnTimer(this) && m_bPeriodic)
         return false;

   }

   if(m_pcallback != NULL)
   {

      m_pcallback->on_timer(this);

   }

   return !m_bRet;

}




#ifdef WINDOWS

VOID CALLBACK aura_timer_TimerRoutine(PVOID lpParam,BOOLEAN TimerOrWaitFired)
{

   timer * ptimer = (timer *)lpParam;

   ptimer->call_on_timer();

}

#else

void aura_timer_handler(sigval sigval)
{

   timer * ptimer = (timer *)sigval.sival_ptr;

   ptimer->call_on_timer();

}

#endif
