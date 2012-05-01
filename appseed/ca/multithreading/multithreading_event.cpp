#include "StdAfx.h"


#if defined(LINUX)
#include <sys/ipc.h>
#include <sys/sem.h>
#endif


event::event(BOOL bInitiallyOwn, BOOL bManualReset, const char * pstrName,LPSECURITY_ATTRIBUTES lpsaAttribute)
{
#ifdef WINDOWS

   m_object = ::CreateEvent(lpsaAttribute, bManualReset, bInitiallyOwn, pstrName);

   if(m_object == NULL)
      AfxThrowResourceException();

#else

   m_bManualReset    = bManualReset;

   bool bSet;

   if(m_bManualReset)
   {
      bSet         = bInitiallyOwn != FALSE;
   }
   else
   {
      bSet         = false;
   }

   if(pstrName != NULL && *pstrName != '\0')
   {

      string strPath = "/ca2/time/ftok/event/" + string(pstrName);

      m_object = (HANDLE) semget(ftok(strPath, 0), 1, 0666 | IPC_CREAT);

   }
   else
   {

      m_object = (HANDLE) semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);

   }

   semun semctl_arg;

   if(bSet)
   {

      semctl_arg.val = 1;

   }
   else
   {

      semctl_arg.val = 0;

   }

   semctl(static_cast < int > (m_object), 0, SETVAL, semctl_arg);


#endif


}

event::~event()
{

#if defined(LINUX)
   
   semun ignored_argument;

   semctl(static_cast < int > (m_object), 0, IPC_RMID, ignored_argument);

#endif

}

BOOL event::SetEvent()
{
#ifdef WINDOWS
   ASSERT(m_object != NULL);
   return ::SetEvent(m_object);
#else

   sembuf sb;

   sb.sem_op   = 1;
   sb.sem_num  = 0;
   sb.sem_flg  = m_bManualReset ? 0 : SEM_UNDO;

   sempop(static_cast < int > (m_object), &sb, 1);

#endif
}

BOOL event::PulseEvent()
{
#ifdef WINDOWS
   ASSERT(m_object != NULL);
   return ::PulseEvent(m_object);
#else

   sembuf sb;

   sb.sem_op   = 1;
   sb.sem_num  = 0;
   sb.sem_flg  = SEM_UNDO;

   sempop(static_cast < int > (m_object), &sb, 1);

#endif
}

BOOL event::ResetEvent()
{
#ifdef WINDOWS
   ASSERT(m_object != NULL);
   return ::ResetEvent(m_object);
#else

   sembuf sb;

   sb.sem_op   = 0;
   sb.sem_num  = 0;
   sb.sem_flg  = bManualReset ? 0 : SEM_UNDO;

   sempop(static_cast < int > (m_object), &sb, 1);

#endif
}


void event::wait ()
{
#ifdef WINDOWS
	if ( ::WaitForSingleObject(item(), INFINITE) != WAIT_OBJECT_0 )
		throw runtime_error("gen::pal::Event::wait: failure");
#else

   sembuf sb;

   sb.sem_op   = -1;
   sb.sem_num  = 0;
   sb.sem_flg  = 0;

   sempop(static_cast < int > (m_object), &sb, 1);

   return wait_result(wait_result::Success);

#endif
}

///  \brief		waits for an event for a specified time
///  \param		duration time period to wait for an event
///  \return	waiting action result as WaitResult
wait_result event::wait (const duration & duration)
{
	DWORD timeout = duration.is_pos_infinity() ? INFINITE : static_cast<DWORD>(duration.total_milliseconds());

#ifdef WINDOWS
	return wait_result(::WaitForSingleObject(item(), timeout));
#else

	DWORD start = ::GetTickCount();

	timespec delay;

	delay.tv_sec = 0;
	defay.tv_nsec = 1000000;

	while(::GetTickCount() - start < timeout)
	{

      sembuf sb;

      sb.sem_op   = -1;
      sb.sem_num  = 0;
      sb.sem_flg  = IPC_NOWAIT;

      int ret = sempop(static_cast < int > (m_object), &sb, 1);

      if(ret < 0)
      {
         if(ret == EPERM)
         {
            nanosleep(&delay, NULL);
         }
         else
         {
            return wait_result(wait_result::Error);
         }
      }
      else
      {
         return wait_result(wait_result::Success);
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

    return WAIT_OBJECT_0 == ::WaitForSingleObject(m_object, 0);

#else

   sembuf sb;

   sb.sem_op   = -1;
   sb.sem_num  = 0;
   sb.sem_flg  = IPC_NOWAIT;

   int ret = sempop(static_cast < int > (m_object), &sb, 1);

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
   DWORD dwRet = ::WaitForSingleObject(m_object, durationTimeout.os_lock_duration());
   if (dwRet == WAIT_OBJECT_0 || dwRet == WAIT_ABANDONED)
      return true;
   else
      return false;

#else

	DWORD start = ::GetTickCount();

	timespec delay;

	delay.tv_sec = 0;
	defay.tv_nsec = 1000000;

	while(::GetTickCount() - start < timeout)
	{

      sembuf sb;

      sb.sem_op   = -1;
      sb.sem_num  = 0;
      sb.sem_flg  = IPC_NOWAIT;

      int ret = sempop(static_cast < int > (m_object), &sb, 1);

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

bool event::unlock()
{
   return true;
}

INT_PTR event::get_os_data() const
{
   return (INT_PTR) m_object;
}
