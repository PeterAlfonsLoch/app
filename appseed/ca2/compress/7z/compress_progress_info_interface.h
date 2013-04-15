#pragma once

namespace libcompress
{

   class CLASS_DECL_ca2 progress_info_interface :
      virtual public ::ca::object
   {
   public:
      virtual ::ca::HRes SetRatioInfo(const uint64 *inSize, const uint64 *outSize) = 0;
   };

} // namespace libcompress

