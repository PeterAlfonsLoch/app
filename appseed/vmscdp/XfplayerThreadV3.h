#if !defined(AFX_XFPLAYERTHREADV3_H__9259267D_851F_4005_8470_0167AC0C3B3D__INCLUDED_)
#define AFX_XFPLAYERTHREADV3_H__9259267D_851F_4005_8470_0167AC0C3B3D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XfplayerThreadV3.h : header file
//

typedef struct tagScoreUpdateMessage
 SCOREUPDATEMESSAGE, * LPSCOREUPDATEMESSAGE;


#include "ImageLoaderEventContainer.h"
#include "VMSException.h"	// Added by ClassView
//#import ".\vmsidle\debug\vmsidle.tlb"
//class CXfplayerThreadV1;
class CXfplayerView;

/////////////////////////////////////////////////////////////////////////////
// CXfplayerThreadV3 thread
class CXfplayerThreadV3 : public CWinThread
{
	DECLARE_DYNCREATE(CXfplayerThreadV3)
protected:
	CXfplayerThreadV3();           // protected constructor used by dynamic creation

// Attributes
protected:
	CWinThread *			m_pthreadV1;
	//FIBITMAP *					m_pfiBitmap;
    CBitmap                     m_bitmap;
	CCriticalSection			m_csBitmap;
    

public:
    //CComPtr <VMSIdleLib::IVMSIdle> m_spIdle;
    CEvent                         m_evInitialized;
	bool							m_bBkImageEnable;
protected:
    CDC m_dcDisplay;                          
    //CEvent                         m_evGotIdleStream;
    LPSTREAM                       m_lpstreamIdle;

public:

// Operations
public:
	void OnLyricViewSize(int iType);
	inline void SetThreadV1(CWinThread * pthreadV1);
//	void LoadImageAsync(LPLOADIMAGESTRUCTURE lpLi);
//	void StretchImageAsync(LPSTRETCHIMAGESTRUCTURE lpSi, bool bBitmapLocked);
    void PreTransitionImageAsync(CXfplayerView * pview);
	BOOL TranslateUserMessage(MSG *pMsg);

protected:
    static DWORD WINAPI ThreadProcStretchImage(LPVOID lpParameter);
    static DWORD WINAPI ThreadProcLoadImage(LPVOID lpParameter);
    static DWORD WINAPI ThreadProcPreTransitionImage(LPVOID lpParameter);

    long OnImageLoaded(HBITMAP hBitmap);
	long OnImageStretched(
		HBITMAP hBitmap,
		int iUserData,
		long cx,
		long cy);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXfplayerThreadV3)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
protected:
public:
//	VMSRESULT ReleaseIdleObject();
//	VMSRESULT CreateIdleObject();
//    VMSRESULT  GetIdle(VMSIdleLib::IVMSIdle ** pIdle);
	CBitmap * GetBitmap();
	virtual ~CXfplayerThreadV3();

	// Generated message map functions
	//{{AFX_MSG(CXfplayerThreadV3)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
    // Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CXfplayerThreadV3)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
    DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

inline void CXfplayerThreadV3::SetThreadV1(CWinThread * pthreadV1)
{
	m_pthreadV1 = pthreadV1;
}
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XFPLAYERTHREADV3_H__9259267D_851F_4005_8470_0167AC0C3B3D__INCLUDED_)
