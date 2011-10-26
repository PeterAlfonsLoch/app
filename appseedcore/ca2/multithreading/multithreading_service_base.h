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

#ifdef WINDOWS

class CLASS_DECL_ca service_base :
   virtual public ::radix::object
{
public:


   static service_base * m_service;
   SERVICE_STATUS_HANDLE m_handle;
   service_status m_status;
   string m_serviceName;


   service_base(::ca::application * papp, DWORD controlsAccepted = SERVICE_ACCEPT_PAUSE_CONTINUE | SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN);
   virtual ~service_base();

   virtual void Start(DWORD control) = 0;
   virtual void Stop(DWORD control) = 0;

   static void run(service_base& service);


   void UpdateState(DWORD state, HRESULT errorCode = S_OK);

   string get_service_name() const;

   void SetServiceStatus();
   static void WINAPI ServiceMain(DWORD argumentCount, PWSTR* arguments);

   static void WINAPI ServiceHandler(DWORD control);


};

#endif
