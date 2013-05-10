#include "framework.h"


#if defined(LINUX)
#include <sys/ipc.h>
#include <sys/sem.h>
#endif


event::event(sp(::ca::application) papp, bool bInitiallyOwn, bool bManualReset, const char * pstrName,LPSECURITY_ATTRIBUTES lpsaAttribute) :
   ca(papp)
{

   //if(papp == ::null())
      //throw invalid_argument_exception(::ca::get_thread_app());

#ifdef WINDOWSEX

   m_object = ::CreateEvent(lpsaAttribute, bManualReset, bInitiallyOwn, pstrName);

   if(m_object == ::null())
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

   m_object = ::CreateEventEx(lpsaAttribute, ::ca::international::utf8_to_unicode(pstrName), dwFlags, DELETE | EVENT_MODIFY_STATE | SYNCHRONIZE);

   if(m_object == ::null())
      throw resource_exception(papp);

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

      if(pstrName != ::null() && *pstrName != '\0')
      {

         string strPath = "/ca2/time/ftok/event/" + string(pstrName);

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


bool event::SetEvent()
{

#ifdef WINDOWS

   ASSERT(m_object != ::null());

   try
   {

      return ::SetEvent(m_object) != FALSE;

   }
   catch(...)
   {
   }

   return false;

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


   ASSERT(m_object != ::null());

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

   ASSERT(m_object != ::null());

   return ::ResetEvent(m_object) != FALSE;

#else

   if(m_bManualEvent)
   {

      pthread_mutex_lock(&m_mutex);

      m_bSignaled = false;

      pthread_mutex_unlock(&m_mutex);

   }
   else
   {

      throw "simple_exception";

   }

   return true;

#endif

}


void event::wait ()
{

#ifdef WINDOWS


	if ( ::WaitForSingleObjectEx(item(), INFINITE, FALSE) != WAIT_OBJECT_0 )
		throw runtime_error(get_app(), "::ca::pal::Event::wait: failure");

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

	return wait_result((uint32_t) ::WaitForSingleObjectEx(item(), durationTimeout.os_lock_duration(), FALSE));

#else

	timespec delay;

   if(m_bManualEvent)
   {

      ((duration & ) durationTimeout).normalize();

      delay.tv_sec = durationTimeout.m_iSeconds;

      delay.tv_nsec = durationTimeout.m_iNanoseconds;

      pthread_mutex_lock(&m_mutex);

      int iSignal = m_iSignalId;

      while(!m_bSignaled && iSignal == m_iSignalId)
      {

         if(pthread_cond_timedwait(&m_cond, &m_mutex, &delay) != 0)
        {


         if(errno == ETIMEDOUT)
         {

            pthread_mutex_unlock(&m_mutex);

            return wait_result(wait_result::Timeout);

         }

         }

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
               nanosleep(&delay, ::null());
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

    return WAIT_OBJECT_0 == ::WaitForSingleObjectEx(m_object, 0, FALSE);

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

   uint32_t dwRet = ::WaitForSingleObjectEx(m_object, durationTimeout.os_lock_duration(), FALSE);

   if (dwRet == WAIT_OBJECT_0 || dwRet == WAIT_ABANDONED)
      return true;
   else
      return false;

#else


   timespec delay;


   if(m_bManualEvent)
   {

      ((duration & ) durationTimeout).normalize();

      DWORD dwStart = get_tick_count();

      DWORD dwTimeout = (DWORD) durationTimeout.get_total_milliseconds();
      DWORD dwSleep = min(84, max(1, dwTimeout / 20));

//      delay.tv_sec = durationTimeout.m_iSeconds;

  //    delay.tv_nsec = ;

      pthread_mutex_lock(&m_mutex);

      int iSignal = m_iSignalId;

//int iError = 0;
//int iError2 = 0;
    while(!m_bSignaled && iSignal == m_iSignalId && get_tick_count() - dwStart < dwTimeout)
    {
      pthread_mutex_unlock(&m_mutex);

//iError = pthread_cond_timedwait(&m_cond, &m_mutex, &delay);
  //  if(iError != 0)
    //     {

      //       iError = errno;

            //if(errno == ETIMEDOUT)
            {

              // pthread_mutex_unlock(&m_mutex);

               //return false;

            }
            Sleep(dwSleep);
      pthread_mutex_lock(&m_mutex);

         }

      //}

      pthread_mutex_unlock(&m_mutex);

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
               nanosleep(&delay, ::null());
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
