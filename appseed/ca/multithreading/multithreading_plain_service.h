#pragma once


class CLASS_DECL_ca plain_service :
   public service_base
{
public:


   plain_service(::ca::applicationsp papp);
   virtual ~plain_service();


   virtual void Start(uint32_t);
   virtual void Stop(uint32_t);


   void CallServiceThread();



};
