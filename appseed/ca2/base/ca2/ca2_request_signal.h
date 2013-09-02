#pragma once


namespace ca2
{


   class CLASS_DECL_ca2 request_signal : 
      public signal_details
   {
   public:


      var         m_varFile;
      var         m_varQuery;


      request_signal(sp(::application) papp, ::signal * psignal = NULL);


   }; 



} // namespace ca2



