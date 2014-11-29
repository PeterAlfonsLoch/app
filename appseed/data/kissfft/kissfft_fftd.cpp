#include "framework.h"


namespace kissfft
{


   fftd::fftd(int32_t iSize)
   {
      m_iSize = iSize;
      m_cfg = kiss_fftr_alloc(iSize, 0, NULL, NULL);
   }

   fftd::~fftd()
   {
      free(m_cfg);
   }

   void fftd::fft(double * pIn, kiss_fft_cpx * pOut)
   {
      kiss_fftr(m_cfg, pIn, pOut);
   }


} // namespace kissfft


