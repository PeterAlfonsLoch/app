#include "StdAfx.h"
#include <math.h>


audWaveBuffer::audWaveBuffer(::ca::application * papp) :
   ca(papp)
{
   m_lpbData = NULL;
   m_lpbBuffer = NULL;
//   m_rfftwplan = NULL;
   m_pfft = NULL;
   m_pcpx = NULL;
//   unsigned int uiBufferSizeLog2 = 9;
//   m_uiBufferSize = 8 * 1 << uiBufferSizeLog2;
//   m_uiAnalysisSize = 4 * 1 << uiBufferSizeLog2;
//   m_uiAllocationSize = 8 * m_uiAnalysisSize;
//   m_uiInterestSize = 200;
   m_uiBufferSize = 0;
   m_uiAnalysisSize = 0;
    m_uiAnalysisSizeOrder = 0;
   m_uiAllocationSize = 0;
   m_uiInterestSize = 0;
   //const double audWaveBuffer::m_uiMaxLevel = 8.0;
//   m_uiMaxLevel = 10.0;
//   m_dMidLevel = 0.3;
//   m_dHighLevel = 0.8;
   m_uiSkippedSamplesCount = 2;

   m_pucData         = NULL;
   m_pucBuffer       = NULL;
//   m_pdProcRealA      = NULL;
//   m_pdProcRealB      = NULL;
//   m_pdProcImagA      = NULL;
//   m_pdProcImagB      = NULL;

   m_pdSetA         = NULL;
   m_pdSetB         = NULL;


   m_pdModuleSet   = NULL;
   m_pdResultSet   = NULL;

//    m_daMaxLevel.set_size(300);
  //  for(int i = 0; i < m_daMaxLevel.get_size(); i++)
    ///{
       // m_daMaxLevel.set_at(i, 0.0);
//    }
  //  m_iMaxLevel = 0;


}

#define ___DELETE(p) if(p != NULL) \
                        delete p; \
                        p = NULL;

audWaveBuffer::~audWaveBuffer()
{
   //if(m_rfftwplan != NULL)
     // rfftw_destroy_plan((rfftw_plan) m_rfftwplan);
   CSingleLock slProcLevel2(&m_csProcLevel2, TRUE);
   CSingleLock slProcLevel1(&m_csProcLevel1, TRUE);
   delete m_pucData;
//   delete m_pdProcRealA;
//   delete m_pdProcRealB;
//   delete m_pdProcImagA;
//   delete m_pdProcImagB;
    
   ___DELETE(m_pdSetA);
   ___DELETE(m_pdSetB);


   ___DELETE(m_pcpx);

   delete m_pdModuleSet;
   CSingleLock slProcResult(&m_csResult, TRUE);
   delete m_pdResultSet;
   m_buffera.remove_all();


   if(m_pfft != NULL)
      delete m_pfft;
}

void audWaveBuffer::FFTDoubleSetADoubleSetB(
    bool   bInverseTransform)
{

   ASSERT(FALSE);
//    ASSERT(m_pdProcRealA != NULL);
  //  ASSERT(m_pdProcRealB != NULL);
    //ASSERT(m_pdProcImagA != NULL);
   //ASSERT(m_pdProcImagB != NULL);
    ASSERT(m_pdSetA != NULL);
    ASSERT(m_pdSetB != NULL);

//   DWORD dwTimeIn = timeGetTime();
//   TRACE("FFT time In: %d ", dwTimeIn);
   CSingleLock sl(&m_csProcLevel1, TRUE);
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
//   DWORD dwTimeIn = timeGetTime();
//   TRACE("data to real A In: %d ", dwTimeIn);
//   TRACE("*********************");
   CSingleLock sl(&m_csProcLevel1, TRUE);
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
//      m_pdProcRealA[j] = (double) (m_pucData[i]);
        m_pdSetA[j] = (double) (m_pucData[i]);
//      TRACE("IN(%d) = %f\n",j, m_pdProcRealA[j]);
      j++;
   }
   for(i = iMinB; i < iMaxB; i += m_uiSkippedSamplesCount)
   {
      //m_pdProcRealA[j] = (double) (m_pucData[i]);
        m_pdSetA[j] = (double) (m_pucData[i]);
//      TRACE("IN(%d) = %f\n",j, m_pdProcRealA[j]);
      j++;
   }
   for(i = iMinC; i < iMaxC; i += m_uiSkippedSamplesCount)
   {
      //m_pdProcRealA[j] = (double) (m_pucData[i]);
        m_pdSetA[j] = (double) (m_pucData[i]);
//      TRACE("IN(%d) = %f\n",j, m_pdProcRealA[j]);
      j++;
   }
//   DWORD dwTimeOut = timeGetTime();
//   TRACE(" data to real a Out: %d ", dwTimeOut);
//   TRACE(" data to real a delta: %d \n", dwTimeOut - dwTimeIn);
}


void audWaveBuffer::CopyDataToSetA(int iIndex)
{
//   DWORD dwTimeIn = timeGetTime();
//   TRACE("data to real A In: %d ", dwTimeIn);
//   TRACE("*********************");
   CSingleLock sl(&m_csProcLevel1, TRUE);
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
//      m_pdProcRealA[j] = (double) (m_pucData[i]);
        m_pdSetA[j] = (double) (m_pucData[i]);
//      TRACE("IN(%d) = %f\n",j, m_pdProcRealA[j]);
      j++;
   }
   for(i = iMinB; i < iMaxB; i += m_uiSkippedSamplesCount)
   {
      //m_pdProcRealA[j] = (double) (m_pucData[i]);
        m_pdSetA[j] = (double) (m_pucData[i]);
//      TRACE("IN(%d) = %f\n",j, m_pdProcRealA[j]);
      j++;
   }
   for(i = iMinC; i < iMaxC; i += m_uiSkippedSamplesCount)
   {
      //m_pdProcRealA[j] = (double) (m_pucData[i]);
        m_pdSetA[j] = (double) (m_pucData[i]);
//      TRACE("IN(%d) = %f\n",j, m_pdProcRealA[j]);
      j++;
   }
//   DWORD dwTimeOut = timeGetTime();
//   TRACE(" data to real a Out: %d ", dwTimeOut);
//   TRACE(" data to real a delta: %d \n", dwTimeOut - dwTimeIn);
   //TRACE("Sample Peak Value: %f - -", dPeakValue);
}

void audWaveBuffer::ZeroDoubleSetAImaginary()
{
    return;
   DWORD dwTimeIn = timeGetTime();
   TRACE("zeroproc a In: %d ", dwTimeIn);
   UINT user;
   CSingleLock sl(&m_csProcLevel1, TRUE);
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
   CSingleLock sl(&m_csProcLevel2, TRUE);

   if(m_uiAllocationSize != uiAllocationSize)
   {
      if(m_pucData != NULL)
         delete[] m_pucData;
      m_uiAllocationSize = uiAllocationSize;
      m_pucData         = new WAVEBUFFERDATA[m_uiAllocationSize];
   }
   if(m_uiAnalysisSize != uiAnalysisSize)
   {
//      if(m_pdProcRealA != NULL)
//         delete[] m_pdProcRealA;
//      if(m_pdProcRealB != NULL)
//         delete[] m_pdProcRealB;
//      if(m_pdProcImagA != NULL)
//         delete[] m_pdProcImagA;
//      if(m_pdProcImagB != NULL)
//         delete[] m_pdProcImagB;

      if(m_pdSetA != NULL)
         delete[] m_pdSetA;
      if(m_pdSetB != NULL)
         delete[] m_pdSetB;


      m_uiAnalysisSize = uiAnalysisSize;
        // soma-se 0.5 para ter certeza que o arredondamento
        // aconteça correatamente
        m_uiAnalysisSizeOrder = (UINT) (log((double) m_uiAnalysisSize) / log(2.0) + 0.5);


      m_pdSetA      = new double[m_uiAnalysisSize];
      m_pdSetB      = new double[m_uiAnalysisSize + 2];


      m_pcpx = new kiss_fft_cpx[m_uiAnalysisSize];

       m_dNominalMaxLevel = 1 << (sizeof(WAVEBUFFERDATA) * 8 - 3); //1024.0;
      m_dNominalMaxLevel = 1.0;
      //m_dNominalMaxLevel = 255.0;
      //m_dNominalMaxLevel *= sqrt(m_uiAnalysisSize);
        //m_uiMaxLevel = sqrt(m_uiMaxLevel);

//      m_pdProcRealA      = new double[m_uiAnalysisSize];
//      m_pdProcRealB      = new double[m_uiAnalysisSize];
//      m_pdProcImagA      = new double[m_uiAnalysisSize];
//      m_pdProcImagB      = new double[m_uiAnalysisSize];
   }
   if(m_uiInterestSize != uiInterestSize)
   {
      if(m_pdModuleSet != NULL)
         delete[] m_pdModuleSet;
      if(m_pdResultSet != NULL)
         delete[] m_pdResultSet;
      m_uiInterestSize = uiInterestSize;
      m_pdModuleSet   = new double[m_uiInterestSize];
      m_pdResultSet      = new double[m_uiInterestSize];
   }

   //ASSERT((m_uiBufferSize % m_uiAnalysisSize) == 0);
   m_uiSkippedSamplesCount = uiSkippedSamplesCount;
   m_uiBufferSize = uiBufferSize;


   UINT user;
   for(user = 0; user < m_uiInterestSize; user++)
   {
      m_pdResultSet[user] = 0.0f;
   }
   DWORD_PTR iSize;
   LPWAVEHDR pWaveHdr;
   DWORD_PTR i;
   iSize = GetBufferCount();
   m_buffera.set_size(iSize);
   for(i = 0; i < iSize; i++)
   {
      buffer & buffer = m_buffera.element_at(i);
      buffer.m_pData = &m_pucData[i * m_uiBufferSize / sizeof(WAVEBUFFERDATA)];
      buffer.m_iIndex = i;
      pWaveHdr = &buffer.m_wavehdr;
      pWaveHdr->lpData = (char *) get_data(i);
      pWaveHdr->dwBufferLength = m_uiBufferSize;
      pWaveHdr->dwBytesRecorded = 0;
      pWaveHdr->dwUser = i;
      pWaveHdr->dwFlags = 0;
   }

   ZeroDoubleSetAImaginary();

   /*if(m_rfftwplan != NULL)
      rfftw_destroy_plan((rfftw_plan) m_rfftwplan);
   int iPlanSize = 1 << m_uiAnalysisSizeOrder;
   m_rfftwplan = rfftw_create_plan(iPlanSize, FFTW_REAL_TO_COMPLEX, FFTW_ESTIMATE);;*/

   if(m_pfft != NULL)
      delete m_pfft;
   int iPlanSize = 1 << m_uiAnalysisSizeOrder;
   m_pfft = new _vmskissfftf::Fftrd(iPlanSize);
}

void audWaveBuffer::InterestCalcDoubleSetBModule()
{
//   DWORD dwTimeIn = timeGetTime();
//   TRACE("proc b module In: %d ", dwTimeIn);
   
   UINT user;
    UINT uj;
    UINT uk;
   CSingleLock sl(&m_csProcLevel1, TRUE);
   int iPlanSize = 1 << m_uiAnalysisSizeOrder;
   for(user = 0, uj = 0, uk = iPlanSize -1; user < m_uiInterestSize; user++)
   {
//      m_pdModuleSet[user] =
//         sqrt(
//         m_pdProcRealB[user] * m_pdProcRealB[user] +
//         m_pdProcImagB[user] * m_pdProcImagB[user]);
      m_pdModuleSet[user] =
         sqrt(
         m_pdSetB[uj] * m_pdSetB[uj] +
         m_pdSetB[uk] * m_pdSetB[uk]);
        uj += 1;
        uk -= 1;
   }
//   DWORD dwTimeOut = timeGetTime();
//   TRACE(" proc b module Out: %d ", dwTimeOut);
//   TRACE(" proc b module delta: %d \n", dwTimeOut - dwTimeIn);

}

void audWaveBuffer::InterestCalcSetBModule()
{
   
   UINT user;
   CSingleLock sl(&m_csProcLevel1, TRUE);
   //int iPlanSize = 1 << m_uiAnalysisSizeOrder;
   for(user = 0; user < m_uiInterestSize; user++)
   {
      m_pdModuleSet[user] = m_pdSetB[user];
   }

}


void audWaveBuffer::InterestCopyModuleToResult(double * lpdMax)
{
   CSingleLock slResult(&m_csResult, TRUE);
   CSingleLock slProcLevel1(&m_csProcLevel1, TRUE);
   UINT user;
    if(lpdMax == NULL)
    {
       for(user = 0; user < m_uiInterestSize; user++)
       {
          m_pdResultSet[user] = m_pdModuleSet[user];
          //TRACE("Result(%05d) = %f\n", i, m_pfResult[i]);
       }
    }
    else
    {
        double d;
        double dMax = 0.0;
       for(user = 0; user < m_uiInterestSize; user++)
       {
          d = m_pdResultSet[user] = m_pdModuleSet[user];
            if(d > dMax)
                dMax = d;

          //TRACE("Result(%05d) = %f\n", i, m_pfResult[i]);
       }
        *lpdMax = dMax;
    }

}

void audWaveBuffer::PCMOutOpen(
   unsigned int uiBufferSize,
   unsigned int uiBufferCount,
   LPWAVEFORMATEX lpwfexIn,
   LPWAVEFORMATEX lpwfexOut)
{
   m_waveformatexIn     = *lpwfexIn;
   m_waveformatexOut    = *lpwfexOut;

   CSingleLock sl(&m_csProcLevel2, TRUE);

   m_uiAllocationSize = uiBufferSize * uiBufferCount;
   m_uiBufferSize = uiBufferSize;
   if(m_lpbData != NULL)
      delete[] m_lpbData;
   m_lpbData         = new BYTE[m_uiAllocationSize];
   memset(m_lpbData, 0, m_uiAllocationSize);
   if(m_lpbBuffer != NULL)
      delete[] m_lpbBuffer;
   m_lpbBuffer         = new BYTE[m_uiBufferSize];
   memset(m_lpbBuffer, 0, m_uiBufferSize);

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
   CSingleLock sl(&m_csProcLevel2, TRUE);
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

   CSingleLock sl(&m_csProcLevel2, TRUE);

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
   CSingleLock sl(&m_csProcLevel1, TRUE);
   wbdLast = 0;
   for(user = 0; user < m_uiBufferSize; user++)
   {
//      m_pfProcRealA[i] = (double) (m_pucData[i] - m_wbdMidLevel);
      wbdNew = m_pucData[user];
      m_pucData[user] -= wbdLast;
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
      if(m_pdResultSet[user] > dMaxAmplitude)
      {
         dPeakValue = user;
         dMaxAmplitude = m_pdResultSet[user];
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
      if(m_pdResultSet[user] > dMaxAmplitude)
      {
         dPeakValue = user;
         dMaxAmplitude = m_pdResultSet[user];
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
      if(m_pdResultSet[user] > dMaxAmplitude)
      {
         dPeakValue = user;
         dMaxAmplitude = m_pdResultSet[user];
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
         if(m_pdResultSet[user] > dMaxAmplitude && daFreq.find_first(user) < 0)
         {
            dPeakValue = user;
            dMaxAmplitude = m_pdResultSet[user];
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
   return &m_pucData[dwIndex * m_uiBufferSize];
};

LPBYTE audWaveBuffer::PCMOutGetBuffer(DWORD_PTR dwIndex)
{
   ASSERT(dwIndex >= 0);
   ASSERT((dwIndex * m_uiBufferSize) < m_uiAllocationSize);
   return &m_lpbData[dwIndex * m_uiBufferSize];
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
   CSingleLock sl(&m_csProcLevel1, TRUE);
   double dr = 32767.0 / log(32767.0);
   for(user = 0; user < m_uiInterestSize; user++)
   {
      m_pdModuleSet[user] = log(m_pdModuleSet[user]) * dr;
   }
   DWORD dwTimeOut = timeGetTime();
   TRACE(" compress module Out: %d ", dwTimeOut);
   TRACE(" compress module delta: %d \n", dwTimeOut - dwTimeIn);

}

double audWaveBuffer::GetMaxLevel()
{
//    return m_dMaxLevel;
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
   ASSERT(m_pdSetA != NULL);
   ASSERT(m_pdSetB != NULL);

   CSingleLock sl(&m_csProcLevel1, TRUE);

   m_pfft->Fft(m_pdSetA, m_pcpx); 

   //double dLog = log(sizeof(m_pucData[0]) * 8.0) / log(2.0);
   double dLog = 1.0;
   double dDiv = pow(2.0, sizeof(m_pucData[0]) * 8.0 / 2.0) * m_uiAnalysisSize * dLog;
   double dPeakValue = 0.0;
   int iCount = m_uiAnalysisSize / 2 + 1;
   for(int i = 0; i < iCount; i++)
   {
      m_pdSetB[i] = (sqrt(m_pcpx[i].r * m_pcpx[i].r + m_pcpx[i].i * m_pcpx[i].i)) / (double) dDiv;
      if(m_pdSetB[i] > dPeakValue)
      {
         dPeakValue = m_pdSetB[i]; 
      }
   }


   TRACE("FFT Peak Value: %f\n", dPeakValue);

}



double * audWaveBuffer::FFTGetResult()
{
   return m_pdResultSet;
};

LPVOID audWaveBuffer::PCMOutGetInBuffer()
{
   return m_lpbBuffer;
}

UINT audWaveBuffer::PCMOutGetInBufferSize()
{
   return m_uiBufferSize;
}

audWaveBuffer::buffer & audWaveBuffer::GetBuffer(DWORD_PTR dwIndex)
{
   return m_buffera.element_at(dwIndex);
}
