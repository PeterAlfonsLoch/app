//*****************************************************************************
//
//      Class:          manual_reset_event
//      Author:         Kenny Kerr
//      Date created:   10 April 2004
//      Description:    Notifies one or more waiting threads that an event has 
//                      occurred.
//
//*****************************************************************************

#include "framework.h"

//*****************************************************************************
//
//      Name:           manual_reset_event
//      Description:    The constructor - initializes a new instance of the 
//                      manual_reset_event class with an initial state.
//
//*****************************************************************************
manual_reset_event::manual_reset_event(sp(::base::application) papp, bool bInitiallyOwn) :
   element(papp),
    ::event(papp, bInitiallyOwn, true)
{
}


//*****************************************************************************
//
//      Name:           Signal
//      Description:    Sets the state of the event to signaled.
//
//*****************************************************************************
/*void manual_reset_event::Signal()
{
    if (!m_event.SetEvent())
    {
       throw last_error_exception();
    }
}*/

//*****************************************************************************
//
//      Name:           Reset
//      Description:    Sets the state of the event to nonsignaled.
//
//*****************************************************************************
/*void manual_reset_event::Reset()
{
    if (!m_event.ResetEvent())
    {
       throw last_error_exception();
    }
}*/

//*****************************************************************************
//
//      Name:           Wait
//      Description:    Waits for the event to become signaled.
//
//*****************************************************************************
/*bool manual_reset_event::Wait(uint32_t timeout)
{
    return (WAIT_OBJECT_0 == ::WaitForSingleObject(m_event,
                                                   timeout));
}*/
