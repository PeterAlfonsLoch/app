#include "StdAfx.h"

namespace _vmskissfftf
{

   Fftri::Fftri(int iSize)
   {
      m_iSize = iSize;
      m_cfg = kiss_fftr_alloc(iSize, 1, NULL, NULL);
      m_freqdata = new kiss_fft_cpx[iSize];
   }

   Fftri::~Fftri()
   {
      free(m_cfg);
      delete[] m_freqdata;
   }

   void Fftri::Fft(kiss_fft_cpx * pIn, double * pOut)
   {
      kiss_fftri(m_cfg, pIn, pOut);
   }


} // namespace _vmskissfft