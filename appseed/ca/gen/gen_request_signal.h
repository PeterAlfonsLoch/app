#pragma once


#include "ca/primitive/primitive_var.h"


namespace gen
{

   class CLASS_DECL_ca request_signal : 
      public gen::signal_object
   {
   public:

      request_signal(::ca::application * papp, gen::signal * psignal = NULL);

      var         m_varFile;
      var         m_varQuery;

   }; 

} // namespace gen