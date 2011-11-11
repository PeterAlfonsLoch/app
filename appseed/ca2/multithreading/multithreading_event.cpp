#include "StdAfx.h"


event::event(BOOL bInitiallyOwn, BOOL bManualReset, const char * pstrName,LPSECURITY_ATTRIBUTES lpsaAttribute)
{
   m_object = ::CreateEvent(lpsaAttribute, bManualReset, bInitiallyOwn, pstrName);
   if(m_object == NULL)
      AfxThrowResourceException();
}

event::~event()
{
}

BOOL event::SetEvent()
{
   ASSERT(m_object != NULL); 
   return ::SetEvent(m_object); 
}

BOOL event::PulseEvent()
{
   ASSERT(m_object != NULL); 
   return ::PulseEvent(m_object); 
}

BOOL event::ResetEvent()
{
   ASSERT(m_object != NULL);
   return ::ResetEvent(m_object); 
}


void event::wait ()
{
	if ( ::WaitForSingleObject(item(), INFINITE) != WAIT_OBJECT_0 )
		throw runtime_error("gen::pal::Event::wait: failure");
}

///  \brief		waits for an event for a specified time
///  \param		duration time period to wait for an event
///  \return	waiting action result as WaitResult
wait_result event::wait (const duration & duration)
{
	DWORD timeout = duration.is_pos_infinity() ? INFINITE : static_cast<DWORD>(duration.total_milliseconds());
	return wait_result(::WaitForSingleObject(item(), timeout));
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
    return WAIT_OBJECT_0 == ::WaitForSingleObject(m_object, 0);
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
   DWORD dwRet = ::WaitForSingleObject(m_object, durationTimeout.os_lock_duration());
   if (dwRet == WAIT_OBJECT_0 || dwRet == WAIT_ABANDONED)
      return true;
   else
      return false;
}

bool event::unlock()
{
   return true;
}

HANDLE event::get_os_data() const
{
   return m_object;
}
