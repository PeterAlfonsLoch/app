#pragma once

#include "kiss_fftr.h"

namespace _vmskissfftf
{

   class CLASS_DECL_ca Fftri
   {
   public:
      Fftri(int iSize);
      virtual ~Fftri();

      void Fft(kiss_fft_cpx * pIn, double * pOut);

   protected:
      int               m_iSize;
      kiss_fftr_cfg     m_cfg;
      kiss_fft_cpx *    m_freqdata;

   };

} // namespace _vmskissfft

