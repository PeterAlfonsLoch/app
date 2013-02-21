#pragma once

namespace libcompress
{

   class CLASS_DECL_ca progress_info_interface :
      virtual public ::gen::object
   {
   public:
      virtual gen::HRes SetRatioInfo(const uint64_t *inSize, const uint64_t *outSize) = 0;
   };

} // namespace libcompress

