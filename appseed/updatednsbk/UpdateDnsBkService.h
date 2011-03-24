#pragma once


class UpdateDnsBkService : 
   public plain_service
{
public:

   UpdateDnsBkService(::ca::application * papp);
   virtual ~UpdateDnsBkService(void);

   virtual void ServiceThread();

};
