// ProgressUtils.h
// from 7-zip on 2010-12-21 - dia do Churrasco de Confraternizacao Setorial de 2010 - preparando o programa de Karaoke e indiretamente muitas outras infinitas coisas pela fe
#pragma once

/*#include "../../Common/MyCom.h"

#include "../ICoder.h"
#include "../IProgress.h"*/

namespace libcompress
{

   class local_progress:
      public progress_info_interface
   {
   public:


      ::ca::progress_interface * _progress;
      progress_info_interface * _ratioProgress;

      bool _inSizeIsMain;
      uint64 ProgressOffset;
      uint64 InSize;
      uint64 OutSize;
      bool SendRatio;
      bool SendProgress;

      local_progress();
      void Init(::ca::progress_interface *progress, bool inSizeIsMain);
      HRESULT SetCur();

      //MY_UNKNOWN_IMP

      ::ca::HRes SetRatioInfo(const uint64 *inSize, const uint64 *outSize);
   };

} // namespace libcompress
