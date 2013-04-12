#pragma once

namespace crypto
{
   class CLASS_DECL_ca2 properties_interface :
      virtual public ::ca::object
   {
   public:
     virtual ::ca::HRes SetKey(const byte *data, uint32_t size) = 0;
     virtual ::ca::HRes SetInitVector(const byte *data, uint32_t size) = 0;
   };

}