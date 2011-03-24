#if !defined(AFX_AUDIOGEN1_H__469AB582_E004_47B3_8F59_95A9880BBAED__INCLUDED_)
#define AFX_AUDIOGEN1_H__469AB582_E004_47B3_8F59_95A9880BBAED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AudioGen1.h : header file
//
namespace _vmsaudio
{
   class WaveOut;
}


/////////////////////////////////////////////////////////////////////////////
// AudioGen thread

class AudioGen : public CWinThread
{
	DECLARE_DYNCREATE(AudioGen)
protected:
	AudioGen();           // protected constructor used by dynamic creation

// Attributes
public:
   _vmsaudio::WaveOut * m_pwaveout;
   int         m_iBufferSize;
   int         m_i;
   LPBYTE      m_lpb;
      
   double m_dTime;
   double m_dFreq;
// Operations
public:
	void Gen(LPBYTE lpdata, DWORD dwLen);
   void Gen();
   void Buf(LPBYTE lpdata, DWORD dwLen);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AudioGen)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~AudioGen();

	// Generated message map functions
	//{{AFX_MSG(AudioGen)
	afx_msg void OnExecutePlay();
	afx_msg void OnExecuteStop();
	//}}AFX_MSG
   afx_msg void OnWaveOutBufferRequest(WPARAM wparam, LPARAM lparam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUDIOGEN1_H__469AB582_E004_47B3_8F59_95A9880BBAED__INCLUDED_)
