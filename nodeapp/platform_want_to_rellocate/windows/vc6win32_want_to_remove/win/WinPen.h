// WinPen.h: interface for the WinPen class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINPEN_H__DA215E1D_C6CF_4DB5_8029_265DCD360866__INCLUDED_)
#define AFX_WINPEN_H__DA215E1D_C6CF_4DB5_8029_265DCD360866__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// ::ca::graphics_object subclasses (drawing tools)

class WinPen : public ::ca::graphics_object
{
	

public:
	static WinPen* PASCAL from_handle(HPEN hPen);

// Constructors
	WinPen();
	WinPen(int nPenStyle, int nWidth, COLORREF crColor);
	WinPen(int nPenStyle, int nWidth, const LOGBRUSH* pLogBrush,
		int nStyleCount = 0, const DWORD* lpStyle = NULL);
	BOOL CreatePen(int nPenStyle, int nWidth, COLORREF crColor);
	BOOL CreatePen(int nPenStyle, int nWidth, const LOGBRUSH* pLogBrush,
		int nStyleCount = 0, const DWORD* lpStyle = NULL);
	BOOL CreatePenIndirect(LPLOGPEN lpLogPen);

// Attributes
	operator HPEN() const;
	int GetLogPen(LOGPEN* pLogPen);
	int GetExtLogPen(EXTLOGPEN* pLogPen);

// ementation
public:
	virtual ~WinPen();
#ifdef _DEBUG
	virtual void Dump(CDumpContext & dumpcontext) const;
#endif
};

#endif // !defined(AFX_WINPEN_H__DA215E1D_C6CF_4DB5_8029_265DCD360866__INCLUDED_)
