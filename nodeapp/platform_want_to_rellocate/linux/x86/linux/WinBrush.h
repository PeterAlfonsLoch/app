// WinBrush.h: interface for the WinBrush class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINBRUSH_H__CB959BD8_7F88_4965_B55A_54645A853627__INCLUDED_)
#define AFX_WINBRUSH_H__CB959BD8_7F88_4965_B55A_54645A853627__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class WinBrush : public ::ca::graphics_object
{
	

public:
	static WinBrush* PASCAL from_handle(HBRUSH hBrush);

// Constructors
	WinBrush();
	WinBrush(COLORREF crColor);             // CreateSolidBrush
	WinBrush(int nIndex, COLORREF crColor); // CreateHatchBrush
	WinBrush(::ca::bitmap* pBitmap);          // CreatePatternBrush

	BOOL CreateSolidBrush(COLORREF crColor);
	BOOL CreateHatchBrush(int nIndex, COLORREF crColor);
	BOOL CreateBrushIndirect(const LOGBRUSH* lpLogBrush);
	BOOL CreatePatternBrush(::ca::bitmap* pBitmap);
	BOOL CreateDIBPatternBrush(HGLOBAL hPackedDIB, UINT nUsage);
	BOOL CreateDIBPatternBrush(const void * lpPackedDIB, UINT nUsage);
	BOOL CreateSysColorBrush(int nIndex);

// Attributes
	operator HBRUSH() const;
	int GetLogBrush(LOGBRUSH* pLogBrush);

// ementation
public:
	virtual ~WinBrush();
#ifdef _DEBUG
	virtual void Dump(CDumpContext & dumpcontext) const;
#endif
};

#endif // !defined(AFX_WINBRUSH_H__CB959BD8_7F88_4965_B55A_54645A853627__INCLUDED_)
