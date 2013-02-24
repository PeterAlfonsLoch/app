// from ICoder.h from 7-zip on 2010-12-20
#pragma once


namespace crypto
{

   class CLASS_DECL_ca reset_init_vector_interface :
      virtual public ::ca::object
   {
   public:
      virtual ca::HRes ResetInitVector() = 0;
   };

} /// namespace crypto
