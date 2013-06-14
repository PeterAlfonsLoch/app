#pragma once


namespace ca2
{


   class CLASS_DECL_ca2 request_signal : 
      public ::ca2::signal_object
   {
   public:


      var         m_varFile;
      var         m_varQuery;


      request_signal(sp(::ca2::application) papp, ::ca2::signal * psignal = NULL);


   }; 



} // namespace ca2



