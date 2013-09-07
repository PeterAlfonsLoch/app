// ProgressUtils.h
#include "framework.h"

//#include "ProgressUtils.h"

namespace libcompress
{

   local_progress::local_progress()
   {
     ProgressOffset = InSize = OutSize = 0;
     SendRatio = SendProgress = true;
   }

   void local_progress::Init(::core::progress_interface *progress, bool inSizeIsMain)
   {
     _ratioProgress = NULL;
     _progress = progress;
     _ratioProgress = dynamic_cast < ::libcompress::progress_info_interface * > (progress);
     _inSizeIsMain = inSizeIsMain;
   }

   HRes local_progress::SetRatioInfo(const uint64_t *inSize, const uint64_t *outSize)
   {
     uint64_t inSizeNew = InSize, outSizeNew = OutSize;
     if (inSize)
       inSizeNew += (*inSize);
     if (outSize)
       outSizeNew += (*outSize);
     if (SendRatio && _ratioProgress)
     {
       RINOK(_ratioProgress->SetRatioInfo(&inSizeNew, &outSizeNew));
     }
     inSizeNew += ProgressOffset;
     outSizeNew += ProgressOffset;
     if (SendProgress)
       return _progress->SetCompleted(_inSizeIsMain ? &inSizeNew : &outSizeNew);
     return S_OK;
   }

   HRESULT local_progress::SetCur()
   {
     return SetRatioInfo(NULL, NULL);
   }

} // namespace libcompress
