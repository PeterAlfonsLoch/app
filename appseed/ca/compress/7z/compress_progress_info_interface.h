#pragma once

namespace libcompress
{

   class CLASS_DECL_ca progress_info_interface :
      virtual public ::radix::object
   {
   public:
      virtual ex1::HRes SetRatioInfo(const uint64 *inSize, const uint64 *outSize) = 0;
   };

} // namespace libcompress

