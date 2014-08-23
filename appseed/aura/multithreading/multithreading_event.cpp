#include "framework.h"


#if defined(LINUX) || defined(APPLEOS)
#include <sys/ipc.h>
#include <sys/sem.h>
#endif


event::event(sp(::aura::application) papp, bool bInitiallyOwn, bool bManualReset, const char * pstrName,LPSECURITY_ATTRIBUTES lpsaAttribute) :
   element(papp)
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

   m_object = ::CreateEventEx(lpsaAttribute, ::str::international::utf8_to_unicode(pstrName), dwFlags, DELETE | EVENT_MODIFY_STATE | SYNCHRONIZE);

   if(m_object == NULL)
      throw resource_exception(papp);

#elif defined(ANDROID)

   pthread_cond_init(&m_cond, NULL);

   m_bManualEvent = bManualReset;

   if(m_bManualEvent)
   {

      m_bSignaled = bInitiallyOwn;
      pthread_mutexattr_t  attr;
      pthread_mutexattr_init(&attr);
      pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
      int32_t rc;
      if((rc = pthread_mutex_init(&m_mutex, &attr)))
      {
         throw "RC_OBJECT_NOT_CREATED";
      }


   }

#else

   m_bManualEvent    = bManualReset;

   if(bManualReset)
   {

      pthread_mutex_init(&m_mutex, 0);

      pthread_cond_init(&m_cond, 0);

      m_bSignaled = bInitiallyOwn;

   }
   else
   {

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

   pthread_mutex_lock(&m_mutex);

   if(m_bManualEvent)
   {

      m_bSignaled = true;

      m_iSignalId++;

      pthread_cond_broadcast(&m_cond);

   }
   else
   {

      pthread_cond_signal(&m_cond);

   }

   pthread_mutex_unlock(&m_mutex);


#else

   if(m_bManualEvent)
   {

      pthread_mutex_lock(&m_mutex);

      m_bSignaled = true;

      m_iSignalId++;

      pthread_cond_broadcast(&m_cond);

      pthread_mutex_unlock(&m_mutex);

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

   ASSERT(m_object != NULL);

   return ::ResetEvent((HANDLE)m_object) != FALSE;

#else

   if(m_bManualEvent)
   {

      pthread_mutex_lock(&m_mutex);

      m_bSignaled = false;

      pthread_mutex_unlock(&m_mutex);

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


   pthread_mutex_lock(&m_mutex);

   if(m_bManualEvent)
   {

      int32_t iSignal = m_iSignalId;

      while(!m_bSignaled && iSignal == m_iSignalId)
      {

         pthread_cond_wait(&m_cond, &m_mutex);

      }

   }
   else
   {

      pthread_cond_wait(&m_cond, &m_mutex);

   }

   pthread_mutex_unlock(&m_mutex);

#else

   if(m_bManualEvent)
   {

      pthread_mutex_lock(&m_mutex);

      int iSignal = m_iSignalId;

      while(!m_bSignaled && iSignal == m_iSignalId)
      {

         pthread_cond_wait(&m_cond, &m_mutex);

      }

      pthread_mutex_unlock(&m_mutex);

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

   return wait_result((uint32_t) ::WaitForSingleObjectEx((HANDLE)item(),durationTimeout.os_lock_duration(),FALSE));

#elif defined(ANDROID)

   pthread_mutex_lock(&m_mutex);

   ((duration & ) durationTimeout).normalize();


   if(m_bManualEvent)
   {

      int32_t iSignal = m_iSignalId;

      while(!m_bSignaled && iSignal == m_iSignalId)
      {

         timespec delay;
         delay.tv_sec = durationTimeout.m_iSeconds;
         delay.tv_nsec = durationTimeout.m_iNanoseconds;
         if(pthread_cond_timedwait(&m_cond, &m_mutex, &delay))
            break;

      }

   }
   else
   {

      timespec delay;
      delay.tv_sec = durationTimeout.m_iSeconds;
      delay.tv_nsec = durationTimeout.m_iNanoseconds;
      pthread_cond_timedwait(&m_cond, &m_mutex, &delay);

   }

   pthread_mutex_unlock(&m_mutex);

   return m_bSignaled ? wait_result(wait_result::Event0) : wait_result(wait_result::Timeout);


#else

	timespec delay;

   if(m_bManualEvent)
   {
      
      ((duration & ) durationTimeout).normalize();

      pthread_mutex_lock(&m_mutex);

      int iSignal = m_iSignalId;
      
      timeval ts1, ts2;
      
      gettimeofday(&ts1, 0);
      
      int error;

      int64_t sec = durationTimeout.m_iSeconds;
      
      int64_t nsec = durationTimeout.m_iNanoseconds;

      while(!m_bSignaled && iSignal == m_iSignalId)
      {
      
         delay.tv_sec = sec;

         delay.tv_nsec = nsec;

         error = pthread_cond_timedwait(&m_cond, &m_mutex, &delay);
         
         pthread_mutex_unlock(&m_mutex);
         
         gettimeofday(&ts2,0);
               
         sec -= ts2.tv_sec - ts1.tv_sec;
         
         nsec -= (ts2.tv_usec - ts1.tv_usec) * 1000;
         
         if(nsec < 0)
         {
            nsec  += 1000000000;
            sec   -= 1;
         }
         
         if(sec < 0 || nsec < 0)
         {
               
            return wait_result(wait_result::Timeout);
                  
         }
         
         ts1 = ts2;

      }

      pthread_mutex_unlock(&m_mutex);

      if(m_bSignaled)
         return wait_result(wait_result::Event0);
      else
         return wait_result(wait_result::Failure);

   }
   else
   {

      uint32_t timeout = durationTimeout.os_lock_duration();

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
            if(ret == EPERM)
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

   uint32_t dwRet = ::WaitForSingleObjectEx((HANDLE)m_object,durationTimeout.os_lock_duration(),FALSE);

   if (dwRet == WAIT_OBJECT_0 || dwRet == WAIT_ABANDONED)
      return true;
   else
      return false;

#elif defined(ANDROID)

   pthread_mutex_lock(&m_mutex);

   ((duration & ) durationTimeout).normalize();


   if(m_bManualEvent)
   {

      int32_t iSignal = m_iSignalId;

      while(!m_bSignaled && iSignal == m_iSignalId)
      {

         timespec delay;
         delay.tv_sec = durationTimeout.m_iSeconds;
         delay.tv_nsec = durationTimeout.m_iNanoseconds;
         if(pthread_cond_timedwait(&m_cond, &m_mutex, &delay))
            break;

      }

      return m_bSignaled;

   }
   else
   {

      timespec delay;
      delay.tv_sec = durationTimeout.m_iSeconds;
      delay.tv_nsec = durationTimeout.m_iNanoseconds;
      pthread_cond_timedwait(&m_cond, &m_mutex, &delay);

      return is_locked();

   }

   pthread_mutex_unlock(&m_mutex);

#else


   timespec delay;


   if(m_bManualEvent)
   {
      
      wait(durationTimeout);

      return m_bSignaled;

   }
   else
   {

      uint32_t timeout = durationTimeout.os_lock_duration();

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
