#pragma once


namespace ca
{


   class CLASS_DECL_ca2 request_signal : 
      public ::ca::signal_object
   {
   public:


      var         m_varFile;
      var         m_varQuery;


      request_signal(sp(::ca::application) papp, ::ca::signal * psignal = NULL);


   }; 



} // namespace ca



