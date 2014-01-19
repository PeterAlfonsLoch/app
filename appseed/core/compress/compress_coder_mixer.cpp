// CoderMixer.cpp
// from 7-zip on dawn of 13/01/2001 - Thursday

#include "framework.h"

//#include "CoderMixer.h"

namespace libcompress
{

   namespace coder_mixer
   {

      void coder_info::SetCoderInfo(const uint64_t *inSize, const uint64_t *outSize)
      {
        InSizeAssigned = (inSize != 0);
        if (InSizeAssigned)
          InSizeValue = *inSize;
        OutSizeAssigned = (outSize != 0);
        if (OutSizeAssigned)
          OutSizeValue = *outSize;
      }

   }
} // namespace libcompress
