#pragma once

namespace crypto
{
   class CLASS_DECL_ca properties_interface :
      virtual public ::gen::object
   {
   public:
     virtual gen::HRes SetKey(const byte *data, uint32_t size) = 0;
     virtual gen::HRes SetInitVector(const byte *data, uint32_t size) = 0;
   };

}