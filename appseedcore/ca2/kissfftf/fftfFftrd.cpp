// _vmskissfftKiss.cpp: implementation of the _vmskissfftKiss class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include <math.h>


namespace _vmskissfftf
{

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Fftrd::Fftrd(int iSize)
{
   m_iSize = iSize;
   m_cfg = kiss_fftr_alloc(iSize, 0, NULL, NULL);
   m_freqdata = new kiss_fft_cpx[iSize];
}

Fftrd::~Fftrd()
{
   free(m_cfg);
   delete[] m_freqdata;
}

void Fftrd::Fft(double * pIn, kiss_fft_cpx * pOut)
{
   kiss_fftr(m_cfg, pIn, pOut);
}


} // namespace _vmskissfft


