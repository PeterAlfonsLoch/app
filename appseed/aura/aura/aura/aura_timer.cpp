
#ifdef WINDOWS
#else
#include <signal.h>
#include <time.h>
#endif


#ifdef METROWIN


namespace aura
{

   class Timer
   {
   public:


      ThreadPoolTimer ^ m_timer;


      Timer()
      {

         m_timer = nullptr;

      }


      ~Timer()
      {

         if (m_timer != nullptr)
         {

            m_timer->Cancel();

            m_timer = nullptr;

         }

      }


   };


} // namespace aura

#elif WINDOWS

namespace aura
{

   class Timer
   {
   public:
      HANDLE               m_hTimerQueue;
      HANDLE               m_hTimer;

   };
}

#elif defined(__APPLE__)

namespace aura
{

   class Timer
   {
   public:
      void *               m_queue;
      void *               m_timer;

   };
}

#else


void aura_timer_handler(sigval sigval);


namespace aura
{


   class Timer
   {
   public:


      timer_t              m_timerid;
      struct sigevent      m_sev;
      struct itimerspec    m_its;


      Timer()
      {

         ZERO(m_sev);

         m_sev.sigev_notify = SIGEV_THREAD;

         m_sev.sigev_signo = 0;

         m_sev.sigev_value.sival_ptr = this;

         m_sev.sigev_notify_function = aura_timer_handler;

         if (timer_create(CLOCK_REALTIME, &m_sev, &m_timerid) == -1)
            throw - 1;

      }


      ~Timer()
      {

         timer_delete(m_timerid);

      }


   };


} // namespace aura


#endif


#ifdef WINDOWSEX

VOID CALLBACK aura_timer_TimerRoutine(PVOID lpParam, BOOLEAN TimerOrWaitFired);

#elif defined(__APPLE__)

void * CreateDispatchQueue();

void CancelDispatchSource(void * p);

void * CreateDispatchTimer(uint64_t interval, uint64_t leeway, void * queue, void(*timer)(void * p), void * p);

void ReleaseDispatch(void * p);

void aura_timer(void * p);

#elif defined(__cplusplus_winrt)


#else


#endif




timer::timer(::aura::application * papp, uint_ptr uiTimer, PFN_TIMER pfnTimer, void * pvoidData, mutex * pmutex) :
   object(papp),
   m_nIDEvent(uiTimer),
   m_pfnTimer(pfnTimer),
   m_pvoidData(pvoidData),
   m_pmutex(pmutex)
{

   m_bDestroying = false;
   m_pcallback = NULL;

   // Create the timer queue.

#if defined(WINDOWSEX)

   hTimerQueue = CreateTimerQueue();

   if (NULL == hTimerQueue)
   {

      throw - 1;

   }

#elif defined(__APPLE__)

   m_queue = NULL;
   m_timer = NULL;

#else

   m_ptimer = new ::aura::Timer;

#endif

   m_bRet = false;
   m_bKill = false;
}

timer::~timer()
{

   stop();

#if defined(WINDOWSEX)

   DeleteTimerQueue(hTimerQueue);

#elif defined(__APPLE__)

   //    dispatch_release(m_queue);

#else

   ::aura::del(m_ptimer);

#endif

}


bool timer::start(int millis, bool bPeriodic)
{

   stop();

   m_bPeriodic = bPeriodic;

   m_dwMillis = millis;

#ifdef METROWIN

   ::Windows::Foundation::TimeSpan span;

   span.Duration = millis * 1000 * 10;

   auto pred = [this](ThreadPoolTimer ^)
   {

      try
      {

         call_on_timer();

      }
      catch (...)
      {

      }

   };

   if (bPeriodic)
   {

      m_ptimer->m_timer = ThreadPoolTimer::CreatePeriodicTimer(ref new TimerElapsedHandler(pred), span); // TimeSpan is 100 nanoseconds

   }
   else
   {

      m_ptimer->m_timer = ThreadPoolTimer::CreateTimer(ref new TimerElapsedHandler(pred), span);

   }



#elif defined(WINDOWS)

   if (!CreateTimerQueueTimer(&hTimer, hTimerQueue, (WAITORTIMERCALLBACK)aura_timer_TimerRoutine, this, m_dwMillis, 0, WT_EXECUTEONLYONCE))
   {

      return false;

   }

#elif defined(__APPLE__)

   m_queue = CreateDispatchQueue();

   if (m_queue == NULL)
      return false;

   m_timer = CreateDispatchTimer(bPeriodic ? millis : 0, millis, m_queue, aura_timer, this);

   if (m_timer == NULL)
      return false;

#else
   /* Start the timer */

   itimerspec & its = m_ptimer->m_its;

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

   if (timer_settime(m_ptimer->m_timerid, 0, &its, NULL) == -1)
      return false;

#endif

   return true;

}

void timer::stop()
{

#ifdef METROWIN

   if (m_ptimer->m_timer != nullptr)
   {

      m_ptimer->m_timer->Cancel();

      m_ptimer->m_timer = nullptr;

   }

#elif defined(WINDOWS)

   if (hTimer != NULL)
   {

      DeleteTimerQueueTimer(hTimerQueue, hTimer, INVALID_HANDLE_VALUE);

      hTimer = NULL;

   }

#elif defined(__APPLE__)

   if (m_timer != NULL)
   {

      CancelDispatchSource(m_timer);

      ReleaseDispatch(m_timer);

      m_timer = NULL;

   }

   if (m_queue != NULL)
   {

      ReleaseDispatch(m_queue);

      m_queue = NULL;

   }


#else

   timer_settime(m_ptimer->m_timerid, 0, NULL, NULL);

#endif

}


bool timer::call_on_timer()
{

   try
   {

      if (::get_thread() == NULL)
      {

         ::set_thread(this);

      }

      synch_lock sl(m_pmutex);

      if (m_bKill || m_bDestroying || m_bDeal)
         return true;

      m_bDeal = true;

      m_bRet = false;

      sl.unlock();

      on_timer();

      sl.lock();

      m_bDeal = false;

      if (m_bKill)
      {

         if (m_bDestroying)
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

#if defined(WINDOWSEX)

      if (m_bPeriodic)
      {

         if (!CreateTimerQueueTimer(&hTimer, hTimerQueue, (WAITORTIMERCALLBACK)aura_timer_TimerRoutine, this, m_dwMillis, 0, WT_EXECUTEONLYONCE))
         {

            return false;

         }

      }


#endif

      return !m_bRet;

   }
   catch (...)
   {

   }

   return false;

}

bool timer::on_timer()
{

   if (m_pfnTimer != NULL)
   {

      if (!m_pfnTimer(this) && m_bPeriodic)
         return false;

   }

   if (m_pcallback != NULL)
   {

      m_pcallback->on_timer(this);

   }

   return !m_bRet;

}




#ifdef WINDOWS

VOID CALLBACK aura_timer_TimerRoutine(PVOID lpParam, BOOLEAN TimerOrWaitFired)
{

   timer * ptimer = (timer *)lpParam;

   try
   {

      ptimer->call_on_timer();

   }
   catch (::exception::base & e)
   {

   }
   catch (...)
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
