// from ICoder.h from 7-zip on 2010-12-20
#pragma once


namespace crypto
{

   class CLASS_DECL_CORE reset_init_vector_interface :
      virtual public ::object
   {
   public:
      virtual HRes ResetInitVector() = 0;
   };

} /// namespace crypto
