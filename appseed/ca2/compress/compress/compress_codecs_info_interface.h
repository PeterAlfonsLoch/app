#pragma once

namespace libcompress
{

   class CLASS_DECL_ca2 codecs_info_interface :
      virtual public object
   {
   public:
      virtual ::ca2::HRes GetNumberOfMethods(uint32_t *numMethods) = 0;
      virtual ::ca2::HRes GetProperty(uint32_t index, int32_t propID, var * value) = 0;
      virtual ::ca2::HRes CreateDecoder(uint32_t index, const char * name, void **coder) = 0;
      virtual ::ca2::HRes CreateEncoder(uint32_t index, const char * name, void **coder) = 0;
   };

} // namespace libcompress
