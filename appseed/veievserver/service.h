#pragma once


namespace veievserver
{

   class socket_thread;

   class CLASS_DECL_VEIEVSERVER service : 
      public plain_service
   {
   public:

      base_array < socket_thread *, socket_thread * >    m_threadptra;
      application *                                      m_papp;
      rgb_quad_array                                     m_rgbquada;



      service(::ca::application * papp);
      virtual ~service();

      virtual void ServiceThread();

   };


} // namespace veievserver
