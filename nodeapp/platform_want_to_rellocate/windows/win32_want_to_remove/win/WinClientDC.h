// WinClientDC.h: interface for the WinClientDC class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINCLIENTDC_H__D255A7EF_9E67_470A_96F9_44CD21E19DE7__INCLUDED_)
#define AFX_WINCLIENTDC_H__D255A7EF_9E67_470A_96F9_44CD21E19DE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WinDC.h"

class WinClientDC : public WinDC
{
	

// Constructors
public:
	WinClientDC(::ca::window * pWnd);

// Attributes
protected:
	HWND m_hWnd;

// ementation
public:
	virtual ~WinClientDC();
#ifdef _DEBUG
	virtual void assert_valid() const;
	virtual void dump(dump_context & dumpcontext) const;
#endif
};

#endif // !defined(AFX_WINCLIENTDC_H__D255A7EF_9E67_470A_96F9_44CD21E19DE7__INCLUDED_)
