#pragma once


namespace gen
{


   class CLASS_DECL_ca request_signal : 
      public gen::signal_object
   {
   public:


      var         m_varFile;
      var         m_varQuery;


      request_signal(::ca::application * papp, gen::signal * psignal = NULL);


   }; 



} // namespace gen



