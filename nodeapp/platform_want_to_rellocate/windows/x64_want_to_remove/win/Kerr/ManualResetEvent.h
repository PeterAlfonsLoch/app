//*****************************************************************************
//
//      Class:          ManualResetEvent
//      Author:         Kenny Kerr
//      Date created:   10 April 2004
//      Description:    Notifies one or more waiting threads that an event has 
//                      occurred.
//
//*****************************************************************************

#pragma once

namespace Kerr
{
    class CLASS_DECL_VMSWIN ManualResetEvent
    {
    public:

        enum EventState
        {
            NonsignaledState,
            SignaledState
        };

        explicit ManualResetEvent(EventState initialState = NonsignaledState);

        bool Signaled() const;

        void Signal();
        void Reset();
        bool Wait(DWORD timeout = INFINITE);

    private:

       ::CEvent m_event;
    };
}
