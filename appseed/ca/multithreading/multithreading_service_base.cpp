//*****************************************************************************
//
//      Class:          service_base
//      Author:         Kenny Kerr
//      Date created:   10 April 2004
//      Description:    Provides a base class for a service that will exist as
//                      part of a service application. service_base must be
//                      derived when creating a new service class.
//
//*****************************************************************************

#include "StdAfx.h"


//
// The single, static service instance pointer.
//
service_base* service_base::m_service = 0;

//*****************************************************************************
//
//      Name:           service_base
//      Description:    The constructor - initializes a new instance of the
//                      service_base class.
//
//*****************************************************************************
service_base::service_base(::ca::application * papp, DWORD controlsAccepted) :
   ca(papp)
#ifdef WINDOWS
   , m_handle(0)
#else
   , m_waitableptra(0)
#endif
{
    m_status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    m_status.dwCurrentState = SERVICE_START_PENDING;
    m_status.dwControlsAccepted = controlsAccepted;
}

//*****************************************************************************
//
//      Name:           service_base
//      Description:    The virtual destructor.
//
//*****************************************************************************
service_base::~service_base()
{
    // Do nothing
}

//*****************************************************************************
//
//      Name:           run
//      Description:    Provides the main entry point for an executable that
//                      contains a single service. Loads the service into
//                      primitive::memory so it can be started. This method blocks until
//                      the service has stopped.
//
//*****************************************************************************
void service_base::run(service_base& service)
{
   ATLASSERT(0 == m_service);
   m_service = &service;

   SERVICE_TABLE_ENTRYW serviceTable[] =
   {
      // Even though the service name is ignored for own process services,
      // it must be a valid string and cannot be 0.
      { L"", ServiceMain },

      // Designates the end of table.
      { 0, 0 }
   };

   if (!::StartServiceCtrlDispatcherW(serviceTable))
   {
      _template::AtlThrowLastWin32();
   }
}

DWORD Win32FromHResult(HRESULT value)
{
    ATLASSERT(FACILITY_WIN32 == HRESULT_FACILITY(value));
    return value & ~0x80070000;
}


//*****************************************************************************
//
//      Name:           UpdateState
//      Description:    Updates the current state and exit code of the service
//                      and notifies the service control manager of the change.
//
//*****************************************************************************
void service_base::UpdateState(DWORD state,
                                    HRESULT errorCode)
{
    m_status.dwCurrentState = state;

    ATLASSERT(0 == m_status.dwWin32ExitCode);
    ATLASSERT(0 == m_status.dwServiceSpecificExitCode);

    if (FAILED(errorCode))
    {
        if (FACILITY_WIN32 == HRESULT_FACILITY(errorCode))
        {
            m_status.dwWin32ExitCode = Win32FromHResult(errorCode);
        }
        else
        {
            m_status.dwWin32ExitCode = ERROR_SERVICE_SPECIFIC_ERROR;
            m_status.dwServiceSpecificExitCode = errorCode;
        }
    }

    SetServiceStatus();
}

//*****************************************************************************
//
//      Name:           SetServiceStatus
//      Description:    Wrapper for the SetServiceStatus SCM function.
//
//*****************************************************************************
void service_base::SetServiceStatus()
{
    // If m_service is zero it means we're not running as a service but
    // rather from the console. This is possible in debug mode.

#ifdef DEBUG
    if (0 != m_service)
    {
#endif
        ATLASSERT(0 != m_service);

        if (!::SetServiceStatus(m_handle,
                                &m_status))
        {
           _template::AtlThrowLastWin32();
        }
#ifdef DEBUG
    }
#endif
}

//*****************************************************************************
//
//      Name:           ServiceName
//      Description:    Gets the service name of the service (as apposed to the
//                      display name). This is the name reported by the service
//                      control manager.
//
//*****************************************************************************
string service_base::get_service_name() const
{
    return m_serviceName;
}

//*****************************************************************************
//
//      Name:           ServiceMain
//      Description:    The starting point for the service.
//
//*****************************************************************************
void WINAPI service_base::ServiceMain(DWORD argumentCount,
                                           PWSTR* arguments)
{
    //
    // Since there's no way to inform the SCM of failure before a successful
    // call to RegisterServiceCtrlHandler, if an error occurs before we have
    // a service status handle we don't catch any exceptions and let the
    // process terminate. The SCM will diligently log this event.
    //

    ATLASSERT(0 != m_service);

    if (1 != argumentCount || 0 == arguments || 0 == arguments[0])
    {
        AtlThrow(E_INVALIDARG);
    }

    m_service->m_serviceName = arguments[0];

    m_service->m_handle = ::RegisterServiceCtrlHandler("",
                                                       ServiceHandler);

    if (0 == m_service->m_handle)
    {
       _template::AtlThrowLastWin32();
    }

    m_service->SetServiceStatus();

    try
    {
        m_service->Start(0);
        m_service->UpdateState(SERVICE_RUNNING);
    }
    catch (const _template::atl_exception& e)
    {
        //
        // If the service can't start it should throw an exception from the
        // Start method. If this happens, we catch it here and notify the
        // SCM so that it can log the error code.
        //

        m_service->UpdateState(SERVICE_STOPPED, e);
    }
}

//*****************************************************************************
//
//      Name:           Handler
//      Description:    The handler function called by the control dispatcher
//                      when an event occurs.
//
//*****************************************************************************
void WINAPI service_base::ServiceHandler(DWORD control)
{
    try
    {
        switch (control)
        {
            case SERVICE_CONTROL_CONTINUE :
            {
                m_service->UpdateState(SERVICE_CONTINUE_PENDING);
                m_service->Start(control);
                m_service->UpdateState(SERVICE_RUNNING);
                break;
            }
            case SERVICE_CONTROL_PAUSE :
            {
                m_service->UpdateState(SERVICE_PAUSE_PENDING);
                m_service->Stop(control);
                m_service->UpdateState(SERVICE_PAUSED);
                break;
            }
            case SERVICE_CONTROL_SHUTDOWN :
            case SERVICE_CONTROL_STOP :
            {
                m_service->UpdateState(SERVICE_STOP_PENDING);
                m_service->Stop(control);
                m_service->UpdateState(SERVICE_STOPPED);
                break;
            }
        }
    }
    catch (const _template::atl_exception& e)
    {
        m_service->UpdateState(SERVICE_STOPPED, e);
    }
}


