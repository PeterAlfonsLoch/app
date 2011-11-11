#include "StdAfx.h"
#include <math.h>


audWaveBuffer::audWaveBuffer(::ca::application * papp) :
ca(papp)
{

   m_pfft                     = NULL;
   m_uiBufferSize             = 0;
   m_uiAnalysisSize           = 0;
   m_uiAnalysisSizeOrder      = 0;
   m_uiAllocationSize         = 0;
   m_uiInterestSize           = 0;
   m_uiSkippedSamplesCount    = 2;

}

audWaveBuffer::~audWaveBuffer()
{

   single_lock slProcLevel2(&m_csProcLevel2, TRUE);
   single_lock slProcLevel1(&m_csProcLevel1, TRUE);

   single_lock slProcResult(&m_csResult, TRUE);
   m_buffera.remove_all();

   if(m_pfft != NULL)
      delete m_pfft;

}

void audWaveBuffer::FFTDoubleSetADoubleSetB(bool   bInverseTransform)
{


   //   DWORD dwTimeIn = timeGetTime();
   //   TRACE("FFT time In: %d ", dwTimeIn);
   single_lock sl(&m_csProcLevel1, TRUE);
   /*   m_fft.fft_double(
   m_uiAnalysisSize,
   bInverseTransform,
   m_pdProcRealA,
   m_pdProcImagA,
   m_pdProcRealB,
   m_pdProcImagB);*/
   //nspsRealFftNip(const float * inSamps, SCplx *outSamps, int order, int flags);
   //   rfftw_one((rfftw_plan) m_rfftwplan, m_pdSetA, m_pdSetB);


   //   DWORD dwTimeOut = timeGetTime();
   //   TRACE(" FFT time Out: %d ", dwTimeOut);
   //   TRACE(" FFT time delta: %d \n", dwTimeOut - dwTimeIn);
   return;

   //   unsigned int uiNumBits;    /* Number of bits needed to store indices */
   unsigned int i, j, k, n;
   unsigned int uiBlockSize, uiBlockEnd;

   double dAngleNumerator = 2.0 * System.math().GetPi();
   //   double dTr, dTi;    /* temp real, temp imaginary */

   ASSERT(gen::math::math::IsPowerOfTwo(m_uiBufferSize));

   if (bInverseTransform)
      dAngleNumerator = -dAngleNumerator;

   //    ASSERT(m_pdProcRealA != NULL);
   //  ASSERT(m_pdProcRealB != NULL);
   //ASSERT(m_pdProcImagA != NULL);
   //ASSERT(m_pdProcImagB != NULL);


   /*
   **    Do simultaneous data copy and bit-reversal ordering into outputs...
   */
   //   DWORD dwTimeIn = timeGetTime();
   for (i = 0; i < m_uiBufferSize; i++)
   {
      //      j = math::ReverseBits (i, m_uiBufferSizeLog2);
      //      m_pdProcRealB[j] = m_pdProcRealA[i];
      //      m_pdProcImagB[j] = m_pdProcImagA[i];
   }
   return;
   /*
   **    Do the FFT itself...
   */

   uiBlockEnd = 1;
   for (uiBlockSize = 2; uiBlockSize <= m_uiBufferSize; uiBlockSize <<= 1 )
   {
      double dDeltaAngle = dAngleNumerator / (double) uiBlockSize;
      double dSinM1 = sin(-dDeltaAngle);
      double dCosM1 = cos(-dDeltaAngle);
      //      double dCosM2 = sqrt(1 - dSinM1 * dSinM1);
      //      double dSinM2 = 2 * dSinM1 * dCosM1;
      //      double cm2 = cos ( -2 * delta_angle );
      double dSinM2 = sin(-2 * dDeltaAngle);
      double dCosM2 = cos(-2 * dDeltaAngle);

      double dW = 2 * dCosM1;
      double ar[3], ai[3];
      //      double dAr0, dAr1, dAr2;
      //      double dAi0, dAi1, dAi2;
      //      double dTemp;

      for ( i=0; i < m_uiBufferSize; i += uiBlockSize)
      {
         ar[2] = dCosM2;
         ar[1] = dCosM1;

         //         dAr2 = dCosM2;
         //         dAr1 = dCosM1;

         ai[2] = dSinM2;
         ai[1] = dSinM1;

         //         dAi2 = dSinM2;
         //         dAi1 = dSinM1;

         for (j = i, n = 0; n < uiBlockEnd; j++, n++ )
         {
            ar[0] = dW*ar[1] - ar[2];
            ar[2] = ar[1];
            ar[1] = ar[0];

            //            dAr0 = dW*dAr1 - dAr2;
            //            dAr2 = dAr1;
            //            dAr1 = dAr0;

            ai[0] = dW*ai[1] - ai[2];
            ai[2] = ai[1];
            ai[1] = ai[0];

            //            dAi0 = dW*dAi1 - dAi2;
            //            dAi2 = dAi1;
            //            dAi1 = dAi0;

            k = j + uiBlockEnd;
            //            dTr = ar[0] * m_pdProcRealB[k] - ai[0] * m_pdProcImagB[k];
            //            dTi = ar[0] * m_pdProcImagB[k] + ai[0] * m_pdProcRealB[k];

            //            m_pdProcRealB[k] = m_pdProcRealB[j] - dTr;
            //            m_pdProcImagB[k] = m_pdProcImagB[j] - dTi;

            //            m_pdProcRealB[j] += dTr;
            //            m_pdProcImagB[j] += dTi;
         }
      }

      uiBlockEnd = uiBlockSize;
   }

   /*
   **    Need to normalize if inverse transform...
   */

   //   if (bInverseTransform)
   {
      //      double denom = (double)m_uiBufferSize;

      for ( i=0; i < m_uiBufferSize; i++ )
      {
         //         m_pdProcRealB[i] /= denom;
         //         m_pdProcRealB[i] /= denom;
      }
   }
   //   DWORD dwTimeOut = timeGetTime();
   //   TRACE(" FFT time Out: %d ", dwTimeOut);
   //   TRACE(" FFT time delta: %d \n", dwTimeOut - dwTimeIn);
}

void audWaveBuffer::CopyDataToDoubleSetA(int iIndex)
{
   single_lock sl(&m_csProcLevel1, TRUE);
   int iMinA = 0;
   int iMaxA = 0;
   int iMinC = 0;
   int iMaxC = 0;
   int iMaxB = iIndex * m_uiBufferSize + m_uiBufferSize;
   int iMinB = iMaxB - (m_uiSkippedSamplesCount * m_uiAnalysisSize);
   if(iMinB < 0)
   {
      iMinA = m_uiAllocationSize + iMinB;
      iMaxA = m_uiAllocationSize;
   }
   if(natural(iMaxB) > m_uiAllocationSize)
   {
      iMinC = 0;
      iMaxC = iMaxB - m_uiAllocationSize;
   }
   int i;
   int j = 0;
   for(i = iMinA; i < iMaxA; i += m_uiSkippedSamplesCount)
   {
      m_daSetA[j] = (double) (m_bdaData[i]);
      j++;
   }
   for(i = iMinB; i < iMaxB; i += m_uiSkippedSamplesCount)
   {
      m_daSetA[j] = (double) (m_bdaData[i]);
      j++;
   }
   for(i = iMinC; i < iMaxC; i += m_uiSkippedSamplesCount)
   {
      m_daSetA[j] = (double) (m_bdaData[i]);
      j++;
   }
}


void audWaveBuffer::CopyDataToSetA(int iIndex)
{
   single_lock sl(&m_csProcLevel1, TRUE);
   int iMinA = 0;
   int iMaxA = 0;
   int iMinC = 0;
   int iMaxC = 0;
   int iMaxB = iIndex * m_uiBufferSize + m_uiBufferSize;
   int iMinB = iMaxB - (m_uiSkippedSamplesCount * m_uiAnalysisSize);
   if(iMinB < 0)
   {
      iMinA = m_uiAllocationSize + iMinB;
      iMaxA = m_uiAllocationSize;
      iMinB = 0;
   }
   if(natural(iMaxB) > m_uiAllocationSize)
   {
      iMaxB = m_uiAllocationSize;
      iMinC = 0;
      iMaxC = iMaxB - m_uiAllocationSize;
   }
   int i;
   int j = 0;
   for(i = iMinA; i < iMaxA; i += m_uiSkippedSamplesCount)
   {
      m_daSetA[j] = (double) (m_bdaData[i]);
      j++;
   }
   for(i = iMinB; i < iMaxB; i += m_uiSkippedSamplesCount)
   {
      m_daSetA[j] = (double) (m_bdaData[i]);
      j++;
   }
   for(i = iMinC; i < iMaxC; i += m_uiSkippedSamplesCount)
   {
      m_daSetA[j] = (double) (m_bdaData[i]);
      j++;
   }
}

void audWaveBuffer::ZeroDoubleSetAImaginary()
{
   return;
   DWORD dwTimeIn = timeGetTime();
   TRACE("zeroproc a In: %d ", dwTimeIn);
   UINT user;
   single_lock sl(&m_csProcLevel1, TRUE);
   for(user = 0; user < m_uiAnalysisSize; user++)
   {
      //      m_pdProcImagA[user] = 0.0;
   }
   DWORD dwTimeOut = timeGetTime();
   TRACE(" zeroproc a Out: %d ", dwTimeOut);
   TRACE(" zeroproc atime delta: %d \n", dwTimeOut - dwTimeIn);

}


void audWaveBuffer::FFTOpen(
   unsigned int uiAllocationSize,
   unsigned int uiBufferSize,
   unsigned int uiAnalysisSize,
   unsigned int uiInterestSize,
   unsigned int uiSkippedSamplesCount)
{
   single_lock sl(&m_csProcLevel2, TRUE);

   if(m_uiAllocationSize != uiAllocationSize)
   {
      m_uiAllocationSize = uiAllocationSize;
      m_bdaData.set_size(uiAllocationSize);
   }
   if(m_uiAnalysisSize != uiAnalysisSize)
   {

      m_uiAnalysisSize = uiAnalysisSize;
      // soma-se 0.5 para ter certeza que o arredondamento
      // aconteça correatamente
      m_uiAnalysisSizeOrder = (UINT) (log((double) m_uiAnalysisSize) / log(2.0) + 0.5);


      m_daSetA.set_size(m_uiAnalysisSize);
      m_daSetB.set_size(m_uiAnalysisSize + 2);
      m_pcpxa.set_size(m_uiAnalysisSize);

      m_dNominalMaxLevel = 1 << (sizeof(WAVEBUFFERDATA) * 8 - 3); //1024.0;
      m_dNominalMaxLevel = 1.0;

   }
   if(m_uiInterestSize != uiInterestSize)
   {
      m_uiInterestSize = uiInterestSize;
      m_daModuleSet.set_size(m_uiInterestSize);
      m_daResultSet.set_size(m_uiInterestSize);
   }

   m_uiSkippedSamplesCount = uiSkippedSamplesCount;
   m_uiBufferSize = uiBufferSize;


   UINT user;
   for(user = 0; user < m_uiInterestSize; user++)
   {
      m_daResultSet[user] = 0.0f;
   }
   DWORD_PTR iSize;
   LPWAVEHDR pWaveHdr;
   DWORD_PTR i;
   iSize = GetBufferCount();
   m_buffera.set_size(iSize);
   for(i = 0; i < iSize; i++)
   {
      buffer & buffer = m_buffera.element_at(i);
      buffer.m_pData = &m_bdaData[i * m_uiBufferSize / sizeof(WAVEBUFFERDATA)];
      buffer.m_iIndex = i;
      pWaveHdr = &buffer.m_wavehdr;
      pWaveHdr->lpData = (char *) get_data(i);
      pWaveHdr->dwBufferLength = m_uiBufferSize;
      pWaveHdr->dwBytesRecorded = 0;
      pWaveHdr->dwUser = i;
      pWaveHdr->dwFlags = 0;
   }

   ZeroDoubleSetAImaginary();

   if(m_pfft != NULL)
   {
      delete m_pfft;
      m_pfft = NULL;
   }
   int iPlanSize = 1 << m_uiAnalysisSizeOrder;
   m_pfft = new kissfft::fftd(iPlanSize);
}

void audWaveBuffer::InterestCalcDoubleSetBModule()
{

   UINT user;
   UINT uj;
   UINT uk;
   single_lock sl(&m_csProcLevel1, TRUE);
   int iPlanSize = 1 << m_uiAnalysisSizeOrder;
   for(user = 0, uj = 0, uk = iPlanSize -1; user < m_uiInterestSize; user++)
   {
      m_daModuleSet[user] = sqrt(m_daSetB[uj] * m_daSetB[uj] + m_daSetB[uk] * m_daSetB[uk]);
      uj += 1;
      uk -= 1;
   }

}

void audWaveBuffer::InterestCalcSetBModule()
{

   UINT user;
   single_lock sl(&m_csProcLevel1, TRUE);
   for(user = 0; user < m_uiInterestSize; user++)
   {
      m_daModuleSet[user] = m_daSetB[user];
   }

}


void audWaveBuffer::InterestCopyModuleToResult(double * lpdMax)
{
   single_lock slResult(&m_csResult, TRUE);
   single_lock slProcLevel1(&m_csProcLevel1, TRUE);
   UINT user;
   if(lpdMax == NULL)
   {
      for(user = 0; user < m_uiInterestSize; user++)
      {
         m_daResultSet[user] = m_daModuleSet[user];
      }
   }
   else
   {
      double d;
      double dMax = 0.0;
      for(user = 0; user < m_uiInterestSize; user++)
      {
         d = m_daResultSet[user] = m_daModuleSet[user];
         if(d > dMax)
            dMax = d;
      }
      *lpdMax = dMax;
   }

}

void audWaveBuffer::PCMOutOpen(unsigned int uiBufferSize, unsigned int uiBufferCount, LPWAVEFORMATEX lpwfexIn, LPWAVEFORMATEX lpwfexOut)
{
   m_waveformatexIn     = *lpwfexIn;
   m_waveformatexOut    = *lpwfexOut;

   single_lock sl(&m_csProcLevel2, TRUE);

   m_uiAllocationSize = uiBufferSize * uiBufferCount;
   m_uiBufferSize = uiBufferSize;
   m_baData.set_size(m_uiAllocationSize);
   m_baBuffer.set_size(m_uiBufferSize);
   memset(m_baBuffer.get_data(), 0, m_uiBufferSize);

   //ASSERT((m_uiBufferSize % m_uiAnalysisSize) == 0);

   DWORD_PTR iSize;
   LPWAVEHDR pWaveHdr;
   DWORD_PTR i;
   iSize = GetBufferCount();
   m_buffera.set_size(iSize);
   for(i = 0; i < iSize; i++)
   {
      //      buffer & buffer = GetBuffer(i);
      pWaveHdr = GetHdr(i);
      pWaveHdr->lpData = (char *) PCMOutGetBuffer(i);
      pWaveHdr->dwBufferLength = m_uiBufferSize;
      pWaveHdr->dwBytesRecorded = 0;
      pWaveHdr->dwUser = i;
      pWaveHdr->dwFlags = 0;
   }

}

void audWaveBuffer::PCMOutProcessWAVEHDR(LPWAVEHDR lpwavehdr)
{
   PCMOutProcess(lpwavehdr->dwUser);
}

void audWaveBuffer::PCMOutProcess(DWORD_PTR dwBuffer)
{
   m_dwCurrentBuffer = dwBuffer;
   single_lock sl(&m_csProcLevel2, TRUE);
   memcpy(PCMOutGetBuffer(dwBuffer), PCMOutGetInBuffer(), PCMOutGetInBufferSize());
}

void audWaveBuffer::FFTProcess(LPWAVEHDR lpwavehdr)
{
   FFTProcess(lpwavehdr->dwUser);
}

void audWaveBuffer::FFTProcess(DWORD_PTR dwBuffer)
{
   buffer & buffer = GetBuffer(dwBuffer);
   if(buffer.FFTProcessed())
      return;
   m_dwCurrentBuffer = dwBuffer;

   single_lock sl(&m_csProcLevel2, TRUE);

   //HighPassFilterData(); // Needed in 16 bits data samples
   //CopyDataToDoubleSetA(iBuffer);
   CopyDataToSetA(dwBuffer);
   //    TRACE("audWaveBuffer::Process FFT In %d\n", timeGetTime());
   //FFTDoubleSetADoubleSetB(FALSE);
   FFTSetASetB();
   //   TRACE("audWaveBuffer::Process FFT Out %d\n", timeGetTime());
   //InterestCalcDoubleSetBModule();
   InterestCalcSetBModule();
   //InterestCompressModuleSet();
   double dMax = 0.0;
   InterestCopyModuleToResult(&dMax);

   buffer.m_bFFT = true;
}

void audWaveBuffer::HighPassFilterData()
{

   DWORD dwTimeIn = timeGetTime();
   WAVEBUFFERDATA wbdLast, wbdNew;
   TRACE("data to real A In: %d ", dwTimeIn);
   UINT user;
   single_lock sl(&m_csProcLevel1, TRUE);
   wbdLast = 0;
   for(user = 0; user < m_uiBufferSize; user++)
   {
      wbdNew = m_bdaData[user];
      m_bdaData[user] -= wbdLast;
      wbdLast = wbdNew;
   }
   DWORD dwTimeOut = timeGetTime();
   TRACE(" data to real a Out: %d ", dwTimeOut);
   TRACE(" data to real a delta: %d \n", dwTimeOut - dwTimeIn);

}

double audWaveBuffer::PeakValueFrequency(double dSampleFrequency, double * dAmplitude)
{
   UINT user;
   double dMaxAmplitude = 0.0;
   double dPeakValue = 0.0;
   for(user = m_uiInterestSize / 20; user < m_uiInterestSize; user++)
   {
      if(m_daResultSet[user] > dMaxAmplitude)
      {
         dPeakValue = user;
         dMaxAmplitude = m_daResultSet[user];
      }
   }
   *dAmplitude = dMaxAmplitude;
   return dPeakValue * dSampleFrequency / m_uiAnalysisSize;
}


double audWaveBuffer::PeakValueFrequency(double dMin, double dMax, double dSampleFrequency, double * dAmplitude)
{
   UINT user;
   double dMaxAmplitude = 0.0;
   double dPeakValue = 0.0;
   UINT uiMax = (UINT) (dMax * m_uiAnalysisSize / dSampleFrequency);
   UINT uiMin = (UINT) (dMin * m_uiAnalysisSize / dSampleFrequency);
   for(user = uiMin; user <= uiMax; user++)
   {
      if(m_daResultSet[user] > dMaxAmplitude)
      {
         dPeakValue = user;
         dMaxAmplitude = m_daResultSet[user];
      }
   }
   *dAmplitude = dMaxAmplitude;
   return dPeakValue * dSampleFrequency / m_uiAnalysisSize;
}


double audWaveBuffer::PeakValueFrequency(double * dAmplitude)
{
   UINT user;
   double dMaxAmplitude = 0.0;
   double dPeakValue = 0.0;
   for(user = 0; user < m_uiInterestSize; user++)
   {
      if(m_daResultSet[user] > dMaxAmplitude)
      {
         dPeakValue = user;
         dMaxAmplitude = m_daResultSet[user];
      }
   }
   *dAmplitude = dMaxAmplitude;
   return dPeakValue;
}

void audWaveBuffer::PeakValueFrequencies(double_array & daFreq, double_array & daAmp, int iCount)
{

   UNREFERENCED_PARAMETER(daAmp);

   UINT user;
   double dLimitAmplitude = 0.0;
   double dMaxAmplitude;
   double dPeakValue;
   for(int i = 0; i < iCount; i++)
   {
      dMaxAmplitude = 0.0;
      dPeakValue = 0.0;
      for(user = 0; user < m_uiInterestSize; user++)
      {
         if(m_daResultSet[user] > dMaxAmplitude && daFreq.find_first(user) < 0)
         {
            dPeakValue = user;
            dMaxAmplitude = m_daResultSet[user];
         }
      }
      if(dMaxAmplitude < 0.5)
         break;
      daFreq.add(dPeakValue);
      daFreq.add(dMaxAmplitude);
      dLimitAmplitude = dMaxAmplitude;
   }
}

void * audWaveBuffer::get_data(DWORD_PTR dwIndex)
{
   ASSERT(dwIndex >= 0);
   ASSERT((dwIndex * m_uiBufferSize) < m_uiAllocationSize);
   return &m_bdaData[dwIndex * m_uiBufferSize];
};

LPBYTE audWaveBuffer::PCMOutGetBuffer(DWORD_PTR dwIndex)
{
   ASSERT(dwIndex >= 0);
   ASSERT((dwIndex * m_uiBufferSize) < m_uiAllocationSize);
   return &m_baData[dwIndex * m_uiBufferSize];
};

DWORD_PTR audWaveBuffer::GetBufferCount()
{
   return m_uiAllocationSize / m_uiBufferSize;
}

LPWAVEHDR audWaveBuffer::GetHdr(DWORD_PTR dwIndex)
{
   ASSERT(dwIndex >= 0);
   ASSERT(dwIndex < GetBufferCount());
   return &GetBuffer(dwIndex).m_wavehdr;
};

audWaveBuffer::buffer * audWaveBuffer::get_item(DWORD_PTR dwIndex)
{
   ASSERT(dwIndex >= 0);
   ASSERT(dwIndex < GetBufferCount());
   return &GetBuffer(dwIndex);
};

void audWaveBuffer::InterestCompressModuleSet()
{
   DWORD dwTimeIn = timeGetTime();
   TRACE("compress module In: %d ", dwTimeIn);

   UINT user;
   single_lock sl(&m_csProcLevel1, TRUE);
   double dr = 32767.0 / log(32767.0);
   for(user = 0; user < m_uiInterestSize; user++)
   {
      m_daModuleSet[user] = log(m_daModuleSet[user]) * dr;
   }
   DWORD dwTimeOut = timeGetTime();
   TRACE(" compress module Out: %d ", dwTimeOut);
   TRACE(" compress module delta: %d \n", dwTimeOut - dwTimeIn);

}

double audWaveBuffer::GetMaxLevel()
{
   return m_dNominalMaxLevel;
}

bool audWaveBuffer::buffer::OnMultimediaDone()
{
   m_bFFT = false;
   return true;
}

bool audWaveBuffer::buffer::FFTProcessed()
{
   return m_bFFT;
}

void audWaveBuffer::FFTSetASetB()
{

   single_lock sl(&m_csProcLevel1, TRUE);

   m_pfft->fft(m_daSetA.get_data(), m_pcpxa.get_data());

   //double dLog = log(sizeof(m_pucData[0]) * 8.0) / log(2.0);
   double dLog = 1.0;
   double dDiv = pow(2.0, sizeof(m_baData[0]) * 8.0 / 2.0) * m_uiAnalysisSize * dLog;
   double dPeakValue = 0.0;
   int iCount = m_uiAnalysisSize / 2 + 1;
   for(int i = 0; i < iCount; i++)
   {
      m_daSetB[i] = (sqrt(m_pcpxa[i].r * m_pcpxa[i].r + m_pcpxa[i].i * m_pcpxa[i].i)) / (double) dDiv;
      if(m_daSetB[i] > dPeakValue)
      {
         dPeakValue = m_daSetB[i];
      }
   }


   TRACE("FFT Peak Value: %f\n", dPeakValue);

}



double * audWaveBuffer::FFTGetResult()
{
   return m_daResultSet.get_data();
};

LPVOID audWaveBuffer::PCMOutGetInBuffer()
{
   return m_baBuffer.get_data();
}

UINT audWaveBuffer::PCMOutGetInBufferSize()
{
   return m_uiBufferSize;
}

audWaveBuffer::buffer & audWaveBuffer::GetBuffer(DWORD_PTR dwIndex)
{
   return m_buffera.element_at(dwIndex);
}
