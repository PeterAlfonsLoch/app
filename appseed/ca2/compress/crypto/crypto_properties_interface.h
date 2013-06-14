#pragma once

namespace crypto
{
   class CLASS_DECL_ca2 properties_interface :
      virtual public ::ca2::object
   {
   public:
     virtual ::ca2::HRes SetKey(const byte *data, uint32_t size) = 0;
     virtual ::ca2::HRes SetInitVector(const byte *data, uint32_t size) = 0;
   };

}