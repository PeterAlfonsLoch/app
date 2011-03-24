// WinWindowDC.h: interface for the WinWindowDC class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINWINDOWDC_H__78A6C75D_35A8_4F76_9CBC_2FC6D19A80B5__INCLUDED_)
#define AFX_WINWINDOWDC_H__78A6C75D_35A8_4F76_9CBC_2FC6D19A80B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class WinWindowDC : public ::ca::graphics_sp
{
	

// Constructors
public:
	WinWindowDC(::ca::window * pWnd);

// Attributes
protected:
	HWND m_hWnd;

// ementation
public:
	virtual ~WinWindowDC();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext & dumpcontext) const;
#endif
};

#endif // !defined(AFX_WINWINDOWDC_H__78A6C75D_35A8_4F76_9CBC_2FC6D19A80B5__INCLUDED_)
