#pragma once

namespace libcompress
{

   class CLASS_DECL_ca codecs_info_interface :
      virtual public ::gen::object
   {
   public:
      virtual gen::HRes GetNumberOfMethods(uint32_t *numMethods) = 0;
      virtual gen::HRes GetProperty(uint32_t index, int32_t propID, var * value) = 0;
      virtual gen::HRes CreateDecoder(uint32_t index, const char * name, void **coder) = 0;
      virtual gen::HRes CreateEncoder(uint32_t index, const char * name, void **coder) = 0;
   };

} // namespace libcompress
