#pragma once

#include "kiss_fftr.h"

namespace _vmskissfftf
{

   class CLASS_DECL_ca Fftrd  
   {
   public:
      Fftrd(int iSize);
      virtual ~Fftrd();

      void Fft(double * pIn, kiss_fft_cpx * pOut);

   protected:
      int               m_iSize;
      kiss_fftr_cfg     m_cfg;
      kiss_fft_cpx *    m_freqdata;

   };

} // namespace _vmskissfft

