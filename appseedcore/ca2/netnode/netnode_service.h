#pragma once


namespace netnode
{

   class socket;
   class application;
   class socket_thread;


   class CLASS_DECL_ca service : 
      public plain_service
   {
   public:


      base_array < socket_thread *, socket_thread * > m_threadptra;


      service(::ca::application * papp);
      virtual ~service();

      virtual void ServiceThread();


   };


} // namespace netnode

