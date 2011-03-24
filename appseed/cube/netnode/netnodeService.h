#pragma once


class netnodeSocket;
class netnodeApp;
class netnodeSocketThread;


class CLASS_DECL_CA2_CUBE netnodeService : 
   public plain_service
{
public:


   base_array < netnodeSocketThread *, netnodeSocketThread * > m_threadptra;


   netnodeService(::ca::application * papp);
   virtual ~netnodeService();

   virtual void ServiceThread();


};


