// WinRgn.h: interface for the WinRgn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINRGN_H__1F592BE4_12ED_45A4_B9D8_C07074E66DC1__INCLUDED_)
#define AFX_WINRGN_H__1F592BE4_12ED_45A4_B9D8_C07074E66DC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class WinRgn : public ::ca::graphics_object
{
	

public:
	static WinRgn* PASCAL from_handle(HRGN hRgn);
	operator HRGN() const;

// Constructors
	WinRgn();
	BOOL CreateRectRgn(int x1, int y1, int x2, int y2);
	BOOL CreateRectRgnIndirect(LPCRECT lpRect);
	BOOL CreateEllipticRgn(int x1, int y1, int x2, int y2);
	BOOL CreateEllipticRgnIndirect(LPCRECT lpRect);
	BOOL CreatePolygonRgn(LPPOINT lpPoints, int nCount, int nMode);
	BOOL CreatePolyPolygonRgn(LPPOINT lpPoints, LPINT lpPolyCounts,
			int nCount, int nPolyFillMode);
	BOOL CreateRoundRectRgn(int x1, int y1, int x2, int y2, int x3, int y3);
	BOOL CreateFromPath(::ca::graphics * pgraphics);
	BOOL CreateFromData(const XFORM* lpXForm, int nCount,
		const RGNDATA* pRgnData);

// Operations
	void SetRectRgn(int x1, int y1, int x2, int y2);
	void SetRectRgn(LPCRECT lpRect);
	int CombineRgn(WinRgn* pRgn1, WinRgn* pRgn2, int nCombineMode);
	int CopyRgn(WinRgn* pRgnSrc);
	BOOL EqualRgn(WinRgn* pRgn) const;
	int OffsetRgn(int x, int y);
	int OffsetRgn(POINT point);
	int GetRgnBox(LPRECT lpRect) const;
	BOOL PtInRegion(int x, int y) const;
	BOOL PtInRegion(POINT point) const;
	BOOL RectInRegion(LPCRECT lpRect) const;
	int GetRegionData(LPRGNDATA lpRgnData, int nCount) const;

// ementation
	virtual ~WinRgn();
};

#endif // !defined(AFX_WINRGN_H__1F592BE4_12ED_45A4_B9D8_C07074E66DC1__INCLUDED_)
