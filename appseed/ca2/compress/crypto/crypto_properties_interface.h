#pragma once

namespace crypto
{
   class CLASS_DECL_ca2 properties_interface :
      virtual public object
   {
   public:
     virtual HRes SetKey(const byte *data, uint32_t size) = 0;
     virtual HRes SetInitVector(const byte *data, uint32_t size) = 0;
   };

}