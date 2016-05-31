#include "framework.h"


#if defined(LINUX) || defined(APPLEOS)

#include <sys/ipc.h>
#include <sys/sem.h>
#include <time.h>

#endif


condition::condition(::ace::application * papp) :
object(papp),
sync_object(NULL)
{


   if(papp == NULL)
      throw invalid_argument_exception(get_thread_app());

#ifdef WINDOWS

//    ::InitializeCriticalSection(&m_sect);

   ::InitializeCriticalSectionEx(&m_sect, 4000, 0);

   ::InitializeConditionVariable(&m_var);
#elif defined(ANDROID)

   pthread_mutex_init(&m_mutex,NULL);

   pthread_cond_init(&m_cond,NULL);

   m_iHold = 0;

   m_bSignaled = false;

#else

/*
   if(pstrName != NULL && *pstrName != '\0')
   {

      string strPath = "/core/time/ftok/condition/" + string(pstrName);

      m_object = semget(ftok(strPath, 0), 1, 0666 | IPC_CREAT);

   }
   else
*/
   {

      m_object = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);

   }

/*

   semun semctl_arg;

   if(bSet)
   {

      semctl_arg.val = 1;

   }
   else
   {

      semctl_arg.val = 0;

   }

   semctl((int32_t) m_object, 0, SETVAL, semctl_arg);

*/

#endif


}

condition::~condition()
{

#ifdef WINDOWS

   ::DeleteCriticalSection(&m_sect);

#endif

}


bool condition::SetEvent()
{

#ifdef WINDOWS


   WakeAllConditionVariable(&m_var);

   return true;

#elif defined(ANDROID)

   pthread_mutex_lock(&m_mutex);

   if(!m_bSignaled)
   {

      m_bSignaled = true;

      pthread_mutex_unlock(&m_mutex);

      pthread_cond_signal(&m_cond);

   }
   else
   {

      pthread_mutex_unlock(&m_mutex);

   }


   return true;

#else

   sembuf sb;

   sb.sem_op   = 1;
   sb.sem_num  = 0;
   sb.sem_flg  = SEM_UNDO;

   return semop((int32_t)m_object,&sb,1) == 0;

#endif

}


bool condition::pulse()
{

#ifdef WINDOWS


   WakeAllConditionVariable(&m_var);

   return true;

#elif defined(ANDROID)

   pthread_mutex_lock(&m_mutex);

   if(m_iHold > 0)
   {

      m_bSignaled = true;

      pthread_mutex_unlock(&m_mutex);

      pthread_cond_signal(&m_cond);

      pthread_mutex_lock(&m_mutex);

      while(m_iHold > 0)
      {

         Sleep(1);

      }

      m_bSignaled = false;

      pthread_mutex_unlock(&m_mutex);

   }
   else
   {

      pthread_mutex_unlock(&m_mutex);

   }


   return true;


#else

   sembuf sb;

   sb.sem_op   = 1;
   sb.sem_num  = 0;
   sb.sem_flg  = SEM_UNDO;

   return semop((int32_t) m_object, &sb, 1) == 0;

#endif

}




void condition::wait ()
{

#ifdef WINDOWS

	SleepConditionVariableCS(&m_var, &m_sect, INFINITE);

#elif defined(ANDROID)

   pthread_mutex_lock(&m_mutex);

   m_iHold++;

   while(!m_bSignaled)
   {

      pthread_cond_wait(&m_cond, &m_mutex);

   }

   pthread_mutex_unlock(&m_mutex);

   pthread_mutex_lock(&m_mutex);

   m_iHold--;

   pthread_mutex_unlock(&m_mutex);


#else

   sembuf sb;

   sb.sem_op   = -1;
   sb.sem_num  = 0;
   sb.sem_flg  = 0;

   semop((int32_t) m_object, &sb, 1);

#endif

}

///  \brief		waits for an condition for a specified time
///  \param		duration time period to wait for an condition
///  \return	waiting action result as WaitResult
wait_result condition::wait (const duration & duration)
{

	uint32_t timeout = duration.lock_duration();

#ifdef WINDOWS

   return wait_result(SleepConditionVariableCS(&m_var, &m_sect, timeout));

#elif defined(ANDROID)


   pthread_mutex_lock(&m_mutex);

   m_iHold++;

   uint32_t start = ::get_tick_count();

   while(!m_bSignaled)
   {

      pthread_cond_wait(&m_cond, &m_mutex);

      if(get_tick_count() - start > duration.get_total_milliseconds())
      {

         m_iHold--;

         return ::wait_result(::wait_result::Timeout);

      }


   }

   m_iHold--;

   pthread_mutex_unlock(&m_mutex);

   return ::wait_result(::wait_result::Event0);

#else

	uint32_t start = ::get_tick_count();

	timespec delay;

	delay.tv_sec = 0;
	delay.tv_nsec = 1000000;

	while(duration.is_pos_infinity() || ::get_tick_count() - start < timeout)
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

#endif
}


//*****************************************************************************
//
//      Class:          manual_reset_event
//      Author:         Kenny Kerr
//      Date created:   10 April 2004
//      Description:    Notifies one or more waiting threads that an condition has
//                      occurred.
//
//*****************************************************************************
//*****************************************************************************
//
//      Name:           Signaled
//      Description:    Determines whether the condition is currently signaled.
//
//*****************************************************************************
bool condition::is_signaled() const
{

#ifdef ANDROID

   return m_bSignaled;

#endif


    throw not_supported_exception(get_app());

}


//end**************************************************************************
//
//      Class:          manual_reset_event
//      Author:         Kenny Kerr
//      Date created:   10 April 2004
//      Description:    Notifies one or more waiting threads that an condition has
//                      occurred.
//
//end**************************************************************************

bool condition::lock(const duration & durationTimeout)
{
#ifdef WINDOWS

   if(SleepConditionVariableCS(&m_var, &m_sect, durationTimeout.lock_duration()) != FALSE)
      return true;
   else
      return false;

#elif defined(ANDROID)

   return wait(durationTimeout).succeeded();

#else

   uint32_t timeout = durationTimeout.lock_duration();

	uint32_t start = ::get_tick_count();

	timespec delay;

	delay.tv_sec = 0;
	delay.tv_nsec = 1000000;

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

	return false;

#endif

}

bool condition::ResetEvent()
{
#ifdef ANDROID

   pthread_mutex_lock(&m_mutex);

   m_iHold = 0;

   m_bSignaled = false;

   pthread_mutex_unlock(&m_mutex);

   pthread_cond_signal(&m_cond);


#endif

   return true;

}

bool condition::unlock()
{

   return ResetEvent();

}

void * condition::get_os_data() const
{

   throw not_supported_exception(get_app());

}
