#pragma once

#include "kissfftf/kiss_fftr.h"


namespace _vmskissfftf
{
   class Fftrd;
   class Fftri;
}


//#include "aflibFFT.h"

#define WAVEBUFFERDATA signed short
#define LPWAVEBUFFERDATA signed short *

class CLASS_DECL_ca audWaveBuffer :
   virtual public ::radix::object
{
public:
   class buffer
   {
   protected:
      bool        m_bShortCompress;
   public:
      bool        m_bFFT;
      bool FFTProcessed();
      bool OnMultimediaDone();
      int         m_iIndex;
      WAVEHDR     m_wavehdr;
      void *      m_pData;
      
   };

   class BufferArray :
      public base_array <buffer, buffer>
   {
   };
         
   unsigned int         m_uiBufferSize;
   unsigned int         m_uiAnalysisSize;
   unsigned int         m_uiAnalysisSizeOrder;
   unsigned int         m_uiAllocationSize;
   unsigned int         m_uiInterestSize;
   unsigned int         m_uiSkippedSamplesCount;

   DWORD_PTR            m_dwCurrentBuffer;
   LPWAVEBUFFERDATA      m_pucData;
   LPWAVEBUFFERDATA      m_pucBuffer;
   LPBYTE               m_lpbData;
   LPBYTE               m_lpbBuffer;
   
   double *             m_pdSetA;
   double *             m_pdSetB;


   double *             m_pdModuleSet;
   double *             m_pdResultSet;
   critical_section     m_csResult;
   critical_section     m_csProcLevel1;
   critical_section     m_csProcLevel2;
   BufferArray          m_buffera;
   _vmskissfftf::Fftrd *  m_pfft;
   kiss_fft_cpx * m_pcpx;

    double m_dNominalMaxLevel; // Divisor que faz o nível máximo ser um.
   //void * m_rfftwplan;
//    int                         m_iMaxLevel;
//    double                      m_dMaxLevel;
//    Carray<double, double>  m_daMaxLevel;


   audWaveBuffer(::ca::application * papp);
   virtual ~audWaveBuffer();

   WAVEFORMATEX         m_waveformatexIn;
   WAVEFORMATEX         m_waveformatexOut;
   double GetMaxLevel();
   void InterestCompressModuleSet();
   DWORD_PTR GetBufferCount();
   double PeakValueFrequency(double dMin, double dMax, double dSampleFrequency, double * dAmplitude);
   double PeakValueFrequency(double dSampleFrequency, double * dAmplitude);
   double PeakValueFrequency(double * dAmplitude);
   void HighPassFilterData();
   void PeakValueFrequencies(double_array & daFreq, double_array & daAmp, int iCount);
   void FFTProcess(LPWAVEHDR lpwavehdr);
   void FFTProcess(DWORD_PTR iBuffer);
   void PCMOutProcessWAVEHDR(LPWAVEHDR lpwavehdr);
   void PCMOutProcess(DWORD_PTR iBuffer);
   LPBYTE PCMOutGetBuffer(DWORD_PTR iIndex);
   void InterestCopyModuleToResult(double * lpdMax);
   void InterestCalcDoubleSetBModule();
   void InterestCalcSetBModule();
   void FFTOpen(unsigned int uiAllocationSize, unsigned int uiBufferSize, unsigned int uiAnalisysSize, unsigned int uiInterestSize, unsigned int uiSkippedSamplesCount);
   void PCMOutOpen(UINT uiBufferSize, UINT uiBufferCount, LPWAVEFORMATEX lpwfexIn, LPWAVEFORMATEX lpwfexOut);
   void ZeroDoubleSetAImaginary();
   void CopyDataToDoubleSetA(int iIndex);
   void CopyDataToSetA(int iIndex);
   void FFTDoubleSetADoubleSetB(bool bInverseTransform);
   void FFTSetASetB();
   buffer & GetBuffer(DWORD_PTR iIndex);
   void * get_data(DWORD_PTR iIndex);
   buffer * get_item(DWORD_PTR iIndex);
   LPWAVEHDR GetHdr(DWORD_PTR iIndex);
   double * FFTGetResult();
   LPVOID   PCMOutGetInBuffer();
   UINT     PCMOutGetInBufferSize();
   
};
