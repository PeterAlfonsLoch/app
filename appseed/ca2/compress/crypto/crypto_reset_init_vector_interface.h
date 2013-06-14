// from ICoder.h from 7-zip on 2010-12-20
#pragma once


namespace crypto
{

   class CLASS_DECL_ca2 reset_init_vector_interface :
      virtual public ::ca2::object
   {
   public:
      virtual ::ca2::HRes ResetInitVector() = 0;
   };

} /// namespace crypto
