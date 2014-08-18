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

#pragma once

class CLASS_DECL_AXIS service_base :
   virtual public ::object
{
public:


   static service_base *   s_pservice;

   service_status          m_status;
   string                  m_serviceName;

   manual_reset_event      m_stopped;
   bool                    m_bStopping;

#ifdef WINDOWSEX

   SERVICE_STATUS_HANDLE   m_handle;

#else

   int32_t                 m_iPid;

#endif



#ifdef WINDOWSEX

   service_base(sp(::base::application) papp, uint32_t controlsAccepted = SERVICE_ACCEPT_PAUSE_CONTINUE | SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN);

#else

   service_base(sp(::base::application) papp, uint32_t controlsAccepted = 0);

#endif

   virtual ~service_base();

   virtual void Start(uint32_t control) = 0;

   virtual void Stop(uint32_t control) = 0;

   virtual void UpdateState(uint32_t state, HRESULT errorCode = S_OK);

   virtual string get_service_name() const;

   virtual void SetServiceStatus();

   virtual bool get_run();

   virtual void call_server();

   virtual void serve() = 0;

   static void serve(service_base& service);

#ifdef WINDOWSEX

   static void WINAPI ServiceMain(DWORD argumentCount, PWSTR* arguments);

   static void WINAPI ServiceHandler(DWORD control);

#endif

};


