#pragma once

namespace libcompress
{

   class CLASS_DECL_CORE progress_info_interface :
      virtual public ::object
   {
   public:
      virtual HRes SetRatioInfo(const uint64_t *inSize, const uint64_t *outSize) = 0;
   };

} // namespace libcompress

