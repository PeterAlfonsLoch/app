
#ifdef WINDOWS
#else
#include <signal.h>
#include <time.h>
#endif

#ifdef WINDOWS

VOID CALLBACK aura_timer_TimerRoutine(PVOID lpParam,BOOLEAN TimerOrWaitFired);

#elif defined(__APPLE__)

void * CreateDispatchTimer(uint64_t interval, uint64_t leeway, void * queue, void (*timer)(void * p), void * p);

void aura_timer(void * p);

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
   m_bDestroying = false;
   m_pcallback = NULL;
   // Create the timer queue.

#ifdef WINDOWS
   hTimerQueue = CreateTimerQueue();
   if (NULL == hTimerQueue)
   {
      throw - 1;
   }

#elif defined(__APPLE__)
    
    m_queue =  NULL;
    m_timer = NULL;
    
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
    
#elif defined(__APPLE__)

//    dispatch_release(m_queue);
    
#else

   timer_delete(timerid);

#endif

}


bool timer::start(int millis,bool bPeriodic)
{

   stop();

   m_bPeriodic = bPeriodic;

   m_dwMillis = millis;

#ifdef WINDOWS
   if(!CreateTimerQueueTimer(&hTimer,hTimerQueue,(WAITORTIMERCALLBACK)aura_timer_TimerRoutine,this,m_dwMillis,0,WT_EXECUTEONLYONCE))
   {

      return false;

   }
    
#elif defined(__APPLE__)
    
    m_queue =  dispatch_queue_create (NULL, NULL);
    
    if(m_queue == NULL)
        return false;
    
    m_timer = CreateDispatchTimer(bPeriodic ? millis : 0, millis, m_queue, aura_timer, this);
    
    if(m_timer == NULL)
        return false;

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
    
#elif defined(__APPLE__)
    
   if(m_timer != NULL)
   {
        
      dispatch_source_cancel((dispatch_source_t) m_timer);
        
      dispatch_release((dispatch_source_t) m_timer);
       
      m_timer = NULL;
        
   }
    
   if(m_queue != NULL)
   {
        
      dispatch_release(m_queue);
      
      m_queue = NULL;
        
   }
    

#else

   timer_settime(timerid,0,NULL,NULL);


#endif
}


bool timer::call_on_timer()
{

   if(::get_thread() == NULL)
   {
    
      ::set_thread(this);

   }
   
   synch_lock sl(m_pmutex);

   if(m_bKill || m_bDestroying || m_bDeal)
      return true;

   m_bDeal = true;

   m_bRet = false;

   sl.unlock();
   
   on_timer();

   sl.lock();

   m_bDeal = false;
   
   if(m_bKill)
   {
      
      if(m_bDestroying)
      {

         sl.unlock();
         
      }
      else
      {
         
         m_bDestroying = true;
         
         sl.unlock();
         
         delete this;
         
      }

      return false;

   }

#ifdef WINDOWS

   if(m_bPeriodic)
   {

      if(!CreateTimerQueueTimer(&hTimer,hTimerQueue,(WAITORTIMERCALLBACK)aura_timer_TimerRoutine,this,m_dwMillis,0,WT_EXECUTEONLYONCE))
      {

         return false;

      }

   }


#endif

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

   try
   {

      ptimer->call_on_timer();

   }
   catch(::exception::base & e)
   {

   }
   catch(...)
   {
      
      delete ptimer;

   }

}
#elif defined(__APPLE__)

void aura_timer(void * p)
{
    
    timer * ptimer = (timer *)p;
    
    ptimer->call_on_timer();
    
}

#else

void aura_timer_handler(sigval sigval)
{

   timer * ptimer = (timer *)sigval.sival_ptr;

   ptimer->call_on_timer();

}

#endif
