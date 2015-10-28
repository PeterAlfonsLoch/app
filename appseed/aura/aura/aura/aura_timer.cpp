
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


      ThreadPoolTimer ^    m_timer;
      timer *              m_ptimer;


      Timer()
      {

         m_timer     = nullptr;
         m_ptimer    = NULL;

      }


      ~Timer()
      {

         if (m_timer != nullptr)
         {

            m_timer->Cancel();

            m_timer = nullptr;

         }

      }


      void stop()
      {

         if (m_timer != nullptr)
         {

            m_timer->Cancel();

            m_timer = nullptr;

         }

      }


   };


} // namespace aura

#elif defined(WINDOWSEX)

VOID CALLBACK aura_timer_TimerRoutine(PVOID lpParam, BOOLEAN TimerOrWaitFired);

namespace aura
{

   class Timer
   {
   public:


      HANDLE               m_hTimerQueue;
      HANDLE               m_hTimer;
      timer *              m_ptimer;


      Timer()
      {

         m_hTimer = NULL;

         m_ptimer = NULL;

         m_hTimerQueue = CreateTimerQueue();

         if(NULL == m_hTimerQueue)
         {

            throw - 1;

         }

      }

      ~Timer()
      {

#if defined(WINDOWSEX)

         if(m_hTimerQueue != NULL && m_hTimerQueue != INVALID_HANDLE_VALUE)
         {

            DeleteTimerQueue(m_hTimerQueue);

         }

#endif

      }


      void stop()
      {

         if(m_hTimerQueue != NULL && m_hTimer != NULL)
         {

            DeleteTimerQueueTimer(m_hTimerQueue,m_hTimer,INVALID_HANDLE_VALUE);

            m_hTimer = NULL;

         }

      }

   };

}

#elif defined(__APPLE__)


void * CreateDispatchQueue();

void CancelDispatchSource(void * p);

void * CreateDispatchTimer(uint64_t interval, uint64_t leeway, void * queue, void(*timer)(void * p), void * p);

void ReleaseDispatch(void * p);

void aura_timer(void * p);

namespace aura
{

   class Timer
   {
   public:
      void *               m_queue;
      void *               m_timer;
      timer *              m_ptimer;
      bool                 m_bFirst;

      Timer()
      {

         m_queue = NULL;
         m_timer = NULL;
         m_ptimer = NULL;


      }

      void stop()
      {

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

      }

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
      timer *              m_ptimer;


      Timer()
      {

         m_ptimer = NULL;

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

      void stop()
      {

         timer_settime(m_timerid, 0, NULL, NULL);

      }

   };


} // namespace aura


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

   m_ptimer = new ::aura::Timer;

   m_ptimer->m_ptimer = this;

   m_bRet = false;
   m_bKill = false;
   m_bDeal = false;
}

timer::~timer()
{

   stop();

   ::aura::del(m_ptimer);

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

   //if (bPeriodic)
   //{

   //   m_ptimer->m_timer = ThreadPoolTimer::CreatePeriodicTimer(ref new TimerElapsedHandler(pred), span); // TimeSpan is 100 nanoseconds

   //}
//   else
   {

      m_ptimer->m_timer = ThreadPoolTimer::CreateTimer(ref new TimerElapsedHandler(pred), span);

   }



#elif defined(WINDOWS)

   if(!CreateTimerQueueTimer(&m_ptimer->m_hTimer,m_ptimer->m_hTimerQueue,(WAITORTIMERCALLBACK)aura_timer_TimerRoutine,m_ptimer,m_dwMillis,0,WT_EXECUTEONLYONCE | WT_EXECUTELONGFUNCTION))
   {

      return false;

   }

#elif defined(__APPLE__)

   m_ptimer->m_queue = CreateDispatchQueue();

   if (m_ptimer->m_queue == NULL)
      return false;

   m_ptimer->m_bFirst = true;

   m_ptimer->m_timer = CreateDispatchTimer(millis, MAX(1, millis / 20), m_ptimer->m_queue, aura_timer, m_ptimer);

   if (m_ptimer->m_timer == NULL)
      return false;

#else
   /* Start the timer */

   itimerspec & its = m_ptimer->m_its;

   its.it_value.tv_sec = millis / 1000; // expiration

   its.it_value.tv_nsec = (millis * 1000 * 1000) % (1000 * 1000 * 1000); // expiration

//   if (bPeriodic)
  // {

      its.it_interval.tv_sec = 0; // no freq

      its.it_interval.tv_nsec = 0; // no freq

   //}
   //else
//   {
//
//      its.it_value.tv_sec = millis / 1000; // freq period
//
//      its.it_value.tv_nsec = (millis * 1000 * 1000) % (1000 * 1000 * 1000); // freq period
//
//   }

   if (timer_settime(m_ptimer->m_timerid, 0, &its, NULL) == -1)
      return false;

#endif

   return true;

}

void timer::stop()
{

   try
   {

      m_ptimer->stop();

   }
   catch(...)
   {

   }



}


bool timer::call_on_timer()
{
   if(!g_bAura)
   {
      output_debug_string("there is timer on (timer::call_on_timer) and aura has gone (!g_bAura)\n");
      return  false;
   }

   try
   {

      //if (::get_thread() == NULL)
      {

         ::set_thread(this);

         m_bRun = true;

      }

      mutex m(*m_pmutex);

      synch_lock sl(&m);

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

//#ifndef METROWIN
//
//         sl.m_pobjectSync = NULL;
//
//#endif

         if (!m_bDestroying)
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

         if(!CreateTimerQueueTimer(&m_ptimer->m_hTimer,m_ptimer->m_hTimerQueue,(WAITORTIMERCALLBACK)aura_timer_TimerRoutine,m_ptimer,m_dwMillis,0,WT_EXECUTEONLYONCE | WT_EXECUTELONGFUNCTION))
         {

            return false;

         }

      }

#elif defined(__APPLE__)

      if (!m_bPeriodic)
      {

         stop();

         return false;

      }


#elif defined(METROWIN)

      if(m_bPeriodic)
      {

         m_ptimer->m_timer->Cancel();

         m_ptimer->m_timer = nullptr;

         ::Windows::Foundation::TimeSpan span;

         span.Duration = m_dwMillis * 1000 * 10;

         auto pred = [this](ThreadPoolTimer ^)
         {

            try
            {

               call_on_timer();

            }
            catch(...)
            {

            }

         };


         m_ptimer->m_timer = ThreadPoolTimer::CreateTimer(ref new TimerElapsedHandler(pred),span);

      }
#else

      if (m_bPeriodic)
      {

         if (timer_settime(m_ptimer->m_timerid, 0, &m_ptimer->m_its, NULL) == -1)
            return false;

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

   if(!g_bAura)
   {
      output_debug_string("there is timer on (aura_timer_TimerRoutine) and aura is going away (!g_bAura)\n");
      return;
   }

   ::aura::Timer * ptimer = (::aura::Timer *)lpParam;

   try
   {

      ptimer->m_ptimer->call_on_timer();

      return;

   }
   catch (::exception::base &)
   {

   }
   catch (...)
   {

   }

   ::aura::del(ptimer);

}
#elif defined(__APPLE__)

void aura_timer(void * p)
{

   ::aura::Timer * ptimer = (::aura::Timer *)p;

   if(ptimer->m_bFirst)
   {

      ptimer->m_bFirst = false;

      return;

   }

   ptimer->m_ptimer->call_on_timer();

}

#else

void aura_timer_handler(sigval sigval)
{

   ::aura::Timer * ptimer = (::aura::Timer *)sigval.sival_ptr;

   ptimer->m_ptimer->call_on_timer();

}

#endif
