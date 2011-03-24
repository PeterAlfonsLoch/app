#pragma once

namespace crypto
{
   class CLASS_DECL_ca properties_interface :
      virtual public ::radix::object
   {
   public:
     virtual ex1::HRes SetKey(const byte *data, uint32 size) = 0;
     virtual ex1::HRes SetInitVector(const byte *data, uint32 size) = 0;
   };

}