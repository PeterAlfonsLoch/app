#pragma once

namespace libcompress
{

   class CLASS_DECL_ca2 progress_info_interface :
      virtual public object
   {
   public:
      virtual ::ca2::HRes SetRatioInfo(const uint64_t *inSize, const uint64_t *outSize) = 0;
   };

} // namespace libcompress

