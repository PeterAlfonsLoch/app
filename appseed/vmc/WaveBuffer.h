// WaveBuffer.h: interface for the CWaveBuffer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WAVEBUFFER_H__AB614F35_5AF3_47AF_803F_23A4B7DE47AC__INCLUDED_)
#define AFX_WAVEBUFFER_H__AB614F35_5AF3_47AF_803F_23A4B7DE47AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "aflibFFT.h"

#define WAVEBUFFERDATA signed short
#define LPWAVEBUFFERDATA signed short *

class CWaveBuffer  
{
//	aflibFFT	m_fft;
	LPWAVEBUFFERDATA	m_pucData;
//	double * m_pdProcRealA;
//	double * m_pdProcRealB;
//	double * m_pdProcImagA;
//	double * m_pdProcImagB;
    double * m_pdFftIn;
    double * m_pdFftOut;
	double * m_pdProcModule;
	double * m_pdResult;
	CCriticalSection m_csResult;
	CCriticalSection m_csProcLevel1;
	CCriticalSection m_csProcLevel2;
	CTypedPtrArray <CPtrArray, WAVEHDR *> m_whArray;
    double m_dNominalMaxLevel; // Divisor que faz o nível máximo ser um.
//    int                         m_iMaxLevel;
//    double                      m_dMaxLevel;
//    CBaseArray<double, double>  m_daMaxLevel;
public:
	double GetMaxLevel();
	void CompressInterestModule();
	int GetBufferCount();
	double PeakValueFrequency(double dSampleFrequency, double * dAmplitude);
	double PeakValueFrequency(double * dAmplitude);
	void HighPassFilterData();
	//unsigned int m_uiBufferSizeLog2;
	unsigned int m_uiBufferSize;
	unsigned int m_uiAnalysisSize;
	unsigned int m_uiAnalysisSizeOrder;
	unsigned int m_uiAllocationSize;
	unsigned int m_uiInterestSize;
	unsigned int m_uiSkippedSamplesCount;
	
//	double m_dMidLevel;
//	double m_dHighLevel;

	void Process(int iIndex);
	void CopyInterestModuleToResult(double * lpdMax);
	void CalcInterestProcBModule();
	void Initialize(
		unsigned int uiAllocationSize,
		unsigned int uiBufferSize,
		unsigned int uiAnalisysSize,
		unsigned int uiInterestSize,
		unsigned int uiSkippedSamplesCount);
	void ZeroProcImagA();
	void CopyDataToProcRealA(int iIndex);
	void ProcAFFTProcB(BOOL bInverseTransform);
	LPWAVEBUFFERDATA GetBuffer(int iIndex);
	LPWAVEHDR GetHdr(int iIndex);
	double * GetResult()
	{
		return m_pdResult;
	};

	CWaveBuffer();
	virtual ~CWaveBuffer();

};

#endif // !defined(AFX_WAVEBUFFER_H__AB614F35_5AF3_47AF_803F_23A4B7DE47AC__INCLUDED_)
