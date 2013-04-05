#pragma once


namespace ca
{


   class CLASS_DECL_ca request_signal : 
      public ::ca::signal_object
   {
   public:


      var         m_varFile;
      var         m_varQuery;


      request_signal(::ca::applicationsp papp, ::ca::signal * psignal = ::null());


   }; 



} // namespace ca



