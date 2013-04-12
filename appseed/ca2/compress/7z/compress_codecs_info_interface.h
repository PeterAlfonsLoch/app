#pragma once

namespace libcompress
{

   class CLASS_DECL_ca codecs_info_interface :
      virtual public ::ca::object
   {
   public:
      virtual ::ca::HRes GetNumberOfMethods(uint32 *numMethods) = 0;
      virtual ::ca::HRes GetProperty(uint32 index, int32_t propID, var * value) = 0;
      virtual ::ca::HRes CreateDecoder(uint32 index, const char * name, void **coder) = 0;
      virtual ::ca::HRes CreateEncoder(uint32 index, const char * name, void **coder) = 0;
   };

} // namespace libcompress
