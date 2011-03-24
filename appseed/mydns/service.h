#pragma once

namespace mydns
{

   class application;

   class service : 
      virtual public plain_service
   {
   public:

      application *        m_papp;

      service(::ca::application * papp);
      virtual ~service();

      void ServiceThread();


   };


} // namespace mydns
