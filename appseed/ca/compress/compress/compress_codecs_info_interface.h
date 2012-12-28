#pragma once

namespace compress
{

   class CLASS_DECL_ca codecs_info_interface :
      virtual public ::radix::object
   {
   public:
      virtual ex1::HRes GetNumberOfMethods(uint32 *numMethods) = 0;
      virtual ex1::HRes GetProperty(uint32 index, int32_t propID, var * value) = 0;
      virtual ex1::HRes CreateDecoder(uint32 index, const char * name, void **coder) = 0;
      virtual ex1::HRes CreateEncoder(uint32 index, const char * name, void **coder) = 0;
   };

} // namespace compress