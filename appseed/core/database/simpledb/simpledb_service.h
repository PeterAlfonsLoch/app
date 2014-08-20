#pragma once


namespace simpledb
{


   class socket_thread;


   class CLASS_DECL_CORE service :
      public plain_service
   {
   public:


      manager *            m_pmanager;
      array < socket_thread *, socket_thread * > m_threadptra;


      service(sp(::axis::application) papp);
      virtual ~service();


      virtual void serve();


   };



} // namespace simpledb



