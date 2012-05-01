#pragma once


class CLASS_DECL_ca plain_service :
   public service_base
{
public:


   manual_reset_event m_stopped;
   bool m_stopping;


   plain_service(::ca::application * papp);
   virtual ~plain_service();

   virtual void Start(DWORD);
   virtual void Stop(DWORD);
   void CallServiceThread();
   virtual void ServiceThread() = 0;


};
