// WinPaintDC.h: interface for the WinPaintDC class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINPAINTDC_H__1DF108EA_DA9C_4905_AA50_8B023AF36009__INCLUDED_)
#define AFX_WINPAINTDC_H__1DF108EA_DA9C_4905_AA50_8B023AF36009__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// WinDC Helpers

class WinPaintDC : public WinDC
{
	

// Constructors
public:
	WinPaintDC(::ca::window * pWnd);   // BeginPaint

// Attributes
protected:
	HWND m_hWnd;
public:
	PAINTSTRUCT m_ps;       // actual paint struct!

// ementation
public:
	virtual ~WinPaintDC();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext & dumpcontext) const;
#endif
};

#endif // !defined(AFX_WINPAINTDC_H__1DF108EA_DA9C_4905_AA50_8B023AF36009__INCLUDED_)
