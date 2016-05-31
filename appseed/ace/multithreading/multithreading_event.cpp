#include "framework.h"


#if defined(LINUX) || defined(APPLEOS) || defined(ANDROID)
#include <sys/ipc.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>
#include <sys/time.h>

#if defined(LINUX) || defined(APPLEOS)
#include <sys/sem.h>
#endif


#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif

void clock_getrealtime(struct timespec * pts)
{

#ifdef __MACH__ // OS X does not have clock_gettime, use clock_get_time

    clock_serv_t cclock;
    mach_timespec_t mts;
    host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
    clock_get_time(cclock, &mts);
    mach_port_deallocate(mach_task_self(), cclock);
    pts->tv_sec = mts.tv_sec;
    pts->tv_nsec = mts.tv_nsec;

#else

    clock_gettime(CLOCK_REALTIME, pts);

#endif

}

#endif



event::event(::ace::application * papp, bool bInitiallyOwn, bool bManualReset, const char * pstrName,LPSECURITY_ATTRIBUTES lpsaAttribute) :
   object(papp)
{

   //if(papp == NULL)
      //throw invalid_argument_exception(get_thread_app());

#ifdef WINDOWSEX

   m_object = (int_ptr)::CreateEvent(lpsaAttribute, bManualReset, bInitiallyOwn, pstrName);

   if(m_object == NULL)
      throw resource_exception(papp);

#elif defined(METROWIN)

   uint32_t dwFlags = 0;

   if(bInitiallyOwn)
   {

      dwFlags |= CREATE_EVENT_INITIAL_SET;

   }

   if(bManualReset)
   {

      dwFlags |= CREATE_EVENT_MANUAL_RESET;

   }

   m_object = (int_ptr) ::CreateEventEx(lpsaAttribute, ::str::international::utf8_to_unicode(pstrName), dwFlags, DELETE | EVENT_MODIFY_STATE | SYNCHRONIZE);

   if(m_object == NULL)
      throw resource_exception(papp);

#elif defined(ANDROID)

   m_pcond = new pthread_cond_t;

   pthread_cond_init((pthread_cond_t *) m_pcond, NULL);

   m_bManualEvent = bManualReset;

   if(m_bManualEvent)
   {

      m_bSignaled = bInitiallyOwn;
      pthread_mutexattr_t  attr;
      pthread_mutexattr_init(&attr);
      pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
      int32_t rc;
      m_pmutex = new pthread_mutex_t;
      if((rc = pthread_mutex_init((pthread_mutex_t *) m_pmutex,&attr)))
      {
         throw "RC_OBJECT_NOT_CREATED";
      }


   }
   else
   {
      m_pmutex = NULL;
   }

#else

   m_bManualEvent    = bManualReset;

   if(bManualReset)
   {

      m_pmutex = new pthread_mutex_t;

      m_pcond = new pthread_cond_t;

      pthread_mutex_init((pthread_mutex_t *) m_pmutex, 0);

      pthread_cond_init((pthread_cond_t *) m_pcond, 0);

      m_bSignaled = bInitiallyOwn;

   }
   else
   {

      m_pmutex = NULL;

      m_pcond = NULL;

      if(pstrName != NULL && *pstrName != '\0')
      {

         string strPath = "/core/time/ftok/event/" + string(pstrName);

         m_object = semget(ftok(strPath, 0), 1, 0666 | IPC_CREAT);

      }
      else
      {

         m_object = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);

      }

      semun semctl_arg;

      if(bInitiallyOwn)
      {

         semctl_arg.val = 1;

      }
      else
      {

         semctl_arg.val = 0;

      }

      semctl((int32_t) m_object, 0, SETVAL, semctl_arg);

   }


#endif


}

#ifndef METROWIN
event:: ~event()
{

#if defined(LINUX)

   semun ignored_argument;

   semctl(m_object, 0, IPC_RMID, ignored_argument);

   ::ace::del((pthread_mutex_t * &)m_pmutex);

   ::ace::del((pthread_cond_t * &)m_pcond);

#elif defined(ANDROID)

   if(m_pcond != NULL)
   {
      delete (pthread_cond_t *)m_pcond;
   }
   if(m_pmutex != NULL)
   {
      delete (pthread_mutex_t *)m_pmutex;
   }

#endif

}

#endif

bool event::SetEvent()
{

#ifdef WINDOWS

   ASSERT(m_object != NULL);

   try
   {

      return ::SetEvent((HANDLE)m_object) != FALSE;

   }
   catch(...)
   {
   }

   return false;

#elif defined(ANDROID)

   pthread_mutex_lock((pthread_mutex_t *) m_pmutex);

   if(m_bManualEvent)
   {

      m_bSignaled = true;

      m_iSignalId++;

      pthread_cond_broadcast((pthread_cond_t *) m_pcond);

   }
   else
   {

      pthread_cond_signal((pthread_cond_t *) m_pcond);

   }

   pthread_mutex_unlock((pthread_mutex_t *) m_pmutex);


   return true;


#else

   if(m_bManualEvent)
   {

      pthread_mutex_lock((pthread_mutex_t *) m_pmutex);

      m_bSignaled = true;

      m_iSignalId++;

      pthread_cond_broadcast((pthread_cond_t *) m_pcond);

      pthread_mutex_unlock((pthread_mutex_t *) m_pmutex);

   }
   else
   {
      sembuf sb;

      sb.sem_op   = 1;
      sb.sem_num  = 0;
      sb.sem_flg  = m_bManualEvent ? 0 : SEM_UNDO;

      return semop((int32_t) m_object, &sb, 1) == 0;
   }

   return true;

#endif

}

/*
bool event::PulseEvent()
{

#ifdef WINDOWSEX


   ASSERT(m_object != NULL);

   return ::PulseEvent(m_object) != FALSE;

#else

#else

   sembuf sb;

   sb.sem_op   = 1;
   sb.sem_num  = 0;
   sb.sem_flg  = SEM_UNDO;

   return semop((int32_t) m_object, &sb, 1) == 0;

#endif

}

*/

bool event::ResetEvent()
{

#ifdef WINDOWS

#ifdef DEBUG



   try
   {

      if(m_object == NULL)
      {

         ::OutputDebugStringW(L"error reset event (1)");

      }


      return ::ResetEvent((HANDLE)m_object) != FALSE;


   }
   catch(...)
   {

      ::OutputDebugStringW(L"error reset event (2)");

   }

   return false;

#else

   ASSERT(m_object != NULL);

   return ::ResetEvent((HANDLE)m_object) != FALSE;

#endif

#else

   if(m_bManualEvent)
   {

      pthread_mutex_lock((pthread_mutex_t *) m_pmutex);

      m_bSignaled = false;

      pthread_mutex_unlock((pthread_mutex_t *) m_pmutex);

   }
   else
   {

      throw simple_exception(get_app(), "It does not make sense to Reset a Event that is Automatic. It can be only Pulsed/Broadcasted.");

   }

   return true;

#endif

}


void event::wait ()
{

#ifdef WINDOWS


   if(::WaitForSingleObjectEx((HANDLE)item(),INFINITE,FALSE) != WAIT_OBJECT_0)
		throw runtime_error(get_app(), "::core::pal::Event::wait: failure");

#elif defined(ANDROID)


   pthread_mutex_lock((pthread_mutex_t *) m_pmutex);

   if(m_bManualEvent)
   {

      int32_t iSignal = m_iSignalId;

      while(!m_bSignaled && iSignal == m_iSignalId)
      {

         pthread_cond_wait((pthread_cond_t *) m_pcond, (pthread_mutex_t *) m_pmutex);

      }

   }
   else
   {

      pthread_cond_wait((pthread_cond_t *) m_pcond, (pthread_mutex_t *) m_pmutex);

   }

   pthread_mutex_unlock((pthread_mutex_t *) m_pmutex);

#else

   if(m_bManualEvent)
   {

      pthread_mutex_lock((pthread_mutex_t *) m_pmutex);

      int iSignal = m_iSignalId;

      while(!m_bSignaled && iSignal == m_iSignalId)
      {

         pthread_cond_wait((pthread_cond_t *) m_pcond, (pthread_mutex_t *) m_pmutex);

      }

      pthread_mutex_unlock((pthread_mutex_t *) m_pmutex);

   }
   else
   {

      sembuf sb;

      sb.sem_op   = -1;
      sb.sem_num  = 0;
      sb.sem_flg  = 0;

      semop((int32_t) m_object, &sb, 1);

   }

#endif

}

///  \brief		waits for an event for a specified time
///  \param		duration time period to wait for an event
///  \return	waiting action result as WaitResult
wait_result event::wait (const duration & durationTimeout)
{

#ifdef WINDOWS

   return wait_result((uint32_t) ::WaitForSingleObjectEx((HANDLE)item(),durationTimeout.lock_duration(),FALSE));

#elif defined(ANDROID)

   pthread_mutex_lock((pthread_mutex_t *) m_pmutex);

   timespec end;
   clock_gettime(CLOCK_REALTIME, &end);

   ((duration & ) durationTimeout).normalize();

   end.tv_sec +=durationTimeout.m_iSeconds;
   end.tv_nsec +=durationTimeout.m_iNanoseconds;

   end.tv_sec += end.tv_nsec / (1000 * 1000 * 1000);
   end.tv_nsec %= 1000 * 1000 * 1000;

   if(m_bManualEvent)
   {

      int32_t iSignal = m_iSignalId;

      while(!m_bSignaled && iSignal == m_iSignalId)
      {

         if(pthread_cond_timedwait((pthread_cond_t *) m_pcond, (pthread_mutex_t *) m_pmutex, &end))
            break;

      }

   }
   else
   {

      timespec delay;
      delay.tv_sec = durationTimeout.m_iSeconds;
      delay.tv_nsec = durationTimeout.m_iNanoseconds;
      pthread_cond_timedwait((pthread_cond_t *) m_pcond, (pthread_mutex_t *) m_pmutex, &delay);

   }

   pthread_mutex_unlock((pthread_mutex_t *) m_pmutex);

   return m_bSignaled ? wait_result(wait_result::Event0) : wait_result(wait_result::Timeout);


#else

   if(m_bManualEvent)
   {

      timespec abstime;

      ((duration & ) durationTimeout).normalize();

      pthread_mutex_lock((pthread_mutex_t *) m_pmutex);

      int iSignal = m_iSignalId;

      //clock_gettime(CLOCK_REALTIME, &abstime);

      clock_getrealtime(&abstime);

      abstime.tv_sec += durationTimeout.m_iSeconds;

      abstime.tv_nsec += durationTimeout.m_iNanoseconds;

      while(abstime.tv_nsec > 1000 * 1000 * 1000)
      {

         abstime.tv_nsec -= 1000 * 1000 * 1000;

         abstime.tv_sec++;

      }

      while(!m_bSignaled && iSignal == m_iSignalId)
      {

         int32_t error = pthread_cond_timedwait((pthread_cond_t *) m_pcond, (pthread_mutex_t *) m_pmutex, &abstime);

         if(error == EBUSY || error == ETIMEDOUT)
         {

            pthread_mutex_unlock((pthread_mutex_t *) m_pmutex);

            return wait_result(wait_result::Timeout);

         }

      }

      pthread_mutex_unlock((pthread_mutex_t *) m_pmutex);

      if(m_bSignaled)
         return wait_result(wait_result::Event0);
      else
         return wait_result(wait_result::Failure);

   }
   else
   {

    	timespec delay;

      delay.tv_sec = 0;

      delay.tv_nsec = 1000 * 1000;

      uint32_t timeout = durationTimeout.lock_duration();

      uint32_t start = ::get_tick_count();

      while(durationTimeout.is_pos_infinity() || ::get_tick_count() - start < timeout)
      {


         sembuf sb;

         sb.sem_op   = -1;
         sb.sem_num  = 0;
         sb.sem_flg  = IPC_NOWAIT;

         int32_t ret = semop((int32_t) m_object, &sb, 1);

         if(ret < 0)
         {
            if(ret == EPERM || ret == EBUSY)
            {
               nanosleep(&delay, NULL);
            }
            else
            {
               return wait_result(wait_result::Failure);
            }
         }
         else
         {
            return wait_result(wait_result::Event0);
         }

      }

      return wait_result(wait_result::Timeout);

   }


#endif


}


//*****************************************************************************
//
//      Class:          manual_reset_event
//      Author:         Kenny Kerr
//      Date created:   10 April 2004
//      Description:    Notifies one or more waiting threads that an event has
//                      occurred.
//
//*****************************************************************************
//*****************************************************************************
//
//      Name:           Signaled
//      Description:    Determines whether the event is currently signaled.
//
//*****************************************************************************
bool event::is_signaled() const
{

#ifdef WINDOWS

   return WAIT_OBJECT_0 == ::WaitForSingleObjectEx((HANDLE)m_object,0,FALSE);

#elif defined(ANDROID)

   if(m_bManualEvent)
   {

      return m_bSignaled;

   }
   else
   {

      return ((event *) this)->wait(millis(0)).signaled();

   }


#else

   if(m_bManualEvent)
   {

      return m_bSignaled;

   }
   else
   {

      sembuf sb;

      sb.sem_op   = -1;
      sb.sem_num  = 0;
      sb.sem_flg  = IPC_NOWAIT;

      int32_t ret = semop((int32_t) m_object, &sb, 1);

      if(ret < 0)
      {
         if(ret == EPERM)
         {
            return true;
         }
         else
         {
            return false;
         }
      }
      else
      {
         return false;
      }

   }

#endif

}
//end**************************************************************************
//
//      Class:          manual_reset_event
//      Author:         Kenny Kerr
//      Date created:   10 April 2004
//      Description:    Notifies one or more waiting threads that an event has
//                      occurred.
//
//end**************************************************************************

bool event::lock(const duration & durationTimeout)
{

#ifdef WINDOWS

   uint32_t dwRet = ::WaitForSingleObjectEx((HANDLE)m_object,durationTimeout.lock_duration(),FALSE);

   if (dwRet == WAIT_OBJECT_0 || dwRet == WAIT_ABANDONED)
      return true;
   else
      return false;

#elif defined(ANDROID)

   pthread_mutex_lock((pthread_mutex_t *) m_pmutex);

   ((duration & ) durationTimeout).normalize();


   if(m_bManualEvent)
   {

      int32_t iSignal = m_iSignalId;

      while(!m_bSignaled && iSignal == m_iSignalId)
      {

         timespec delay;
         delay.tv_sec = durationTimeout.m_iSeconds;
         delay.tv_nsec = durationTimeout.m_iNanoseconds;
         if(pthread_cond_timedwait((pthread_cond_t *) m_pcond, (pthread_mutex_t *) m_pmutex, &delay))
            break;

      }

      return m_bSignaled;

   }
   else
   {

      timespec delay;
      delay.tv_sec = durationTimeout.m_iSeconds;
      delay.tv_nsec = durationTimeout.m_iNanoseconds;
      pthread_cond_timedwait((pthread_cond_t *) m_pcond, (pthread_mutex_t *) m_pmutex, &delay);

      return is_locked();

   }

   pthread_mutex_unlock((pthread_mutex_t *) m_pmutex);

#else


   timespec delay;


   if(m_bManualEvent)
   {

      wait(durationTimeout);

      return m_bSignaled;

   }
   else
   {

      uint32_t timeout = durationTimeout.lock_duration();

      uint32_t start = ::get_tick_count();

      while(::get_tick_count() - start < timeout)
      {

         sembuf sb;

         sb.sem_op   = -1;
         sb.sem_num  = 0;
         sb.sem_flg  = IPC_NOWAIT;

         int32_t ret = semop((int32_t) m_object, &sb, 1);

         if(ret < 0)
         {
            if(ret == EPERM)
            {
               nanosleep(&delay, NULL);
            }
            else
            {
               return false;
            }
         }
         else
         {
            return true;
         }

      }

   }

	return false;

#endif

}

bool event::unlock()
{
   return true;
}

void * event::get_os_data() const
{
   return (void *) m_object;
}
