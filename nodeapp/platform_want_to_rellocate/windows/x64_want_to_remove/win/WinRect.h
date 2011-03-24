// WinRect.h: interface for the WinRect class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINRECT_H__0915F5E8_88DA_4027_BE14_43EC99A8840F__INCLUDED_)
#define AFX_WINRECT_H__0915F5E8_88DA_4027_BE14_43EC99A8840F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// WinRect - A 2-D rectangle, similar to Windows RECT structure.

typedef const RECT* LPCRECT;    // pointer to read/only RECT

class WinRect : public tagRECT
{
public:

// Constructors

	// uninitialized rectangle
	WinRect();
	// from left, top, right, and bottom
	WinRect(int l, int t, int r, int b);
	// copy constructor
	WinRect(const RECT& srcRect);
	// from a pointer to another rect
	WinRect(LPCRECT lpSrcRect);
	// from a point and size
	WinRect(POINT point, SIZE size);
	// from two points
	WinRect(POINT topLeft, POINT bottomRight);

// Attributes (in addition to RECT members)

	// retrieves the width
	int Width() const;
	// returns the height
	int Height() const;
	// returns the size
	size Size() const;
	// reference to the top-left point
	point& TopLeft();
	// reference to the bottom-right point
	point& BottomRight();
	// const reference to the top-left point
	const point& TopLeft() const;
	// const reference to the bottom-right point
	const point& BottomRight() const;
	// the geometric center point of the rectangle
	point CenterPoint() const;
	// swap the left and right
	void SwapLeftRight();
	static void SwapLeftRight(LPRECT lpRect);

	// convert between WinRect and LPRECT/LPCRECT (no need for &)
	operator LPRECT();
	operator LPCRECT() const;

	// returns TRUE if rectangle has no area
	BOOL IsRectEmpty() const;
	// returns TRUE if rectangle is at (0,0) and has no area
	BOOL IsRectNull() const;
	// returns TRUE if point is within rectangle
	BOOL PtInRect(POINT point) const;

// Operations

	// set rectangle from left, top, right, and bottom
	void SetRect(int x1, int y1, int x2, int y2);
	void SetRect(POINT topLeft, POINT bottomRight);
	// empty the rectangle
	void SetRectEmpty();
	// copy from another rectangle
	void CopyRect(LPCRECT lpSrcRect);
	// TRUE if exactly the same as another rectangle
	BOOL EqualRect(LPCRECT lpRect) const;

	// inflate rectangle's width and height without
	// moving its top or left
	void InflateRect(int x, int y);
	void InflateRect(SIZE size);
	void InflateRect(LPCRECT lpRect);
	void InflateRect(int l, int t, int r, int b);
	// deflate the rectangle's width and height without
	// moving its top or left
	void DeflateRect(int x, int y);
	void DeflateRect(SIZE size);
	void DeflateRect(LPCRECT lpRect);
	void DeflateRect(int l, int t, int r, int b);

	// translate the rectangle by moving its top and left
	void OffsetRect(int x, int y);
	void OffsetRect(SIZE size);
	void OffsetRect(POINT point);
	void NormalizeRect();

	// set this rectangle to intersection of two others
	BOOL IntersectRect(LPCRECT lpRect1, LPCRECT lpRect2);

	// set this rectangle to bounding union of two others
	BOOL UnionRect(LPCRECT lpRect1, LPCRECT lpRect2);

	// set this rectangle to minimum of two others
	BOOL SubtractRect(LPCRECT lpRectSrc1, LPCRECT lpRectSrc2);

// Additional Operations
	void operator=(const RECT& srcRect);
	BOOL operator==(const RECT& rect) const;
	BOOL operator!=(const RECT& rect) const;
	void operator+=(POINT point);
	void operator+=(SIZE size);
	void operator+=(LPCRECT lpRect);
	void operator-=(POINT point);
	void operator-=(SIZE size);
	void operator-=(LPCRECT lpRect);
	void operator&=(const RECT& rect);
	void operator|=(const RECT& rect);

// Operators returning WinRect values
	WinRect operator+(POINT point) const;
	WinRect operator-(POINT point) const;
	WinRect operator+(LPCRECT lpRect) const;
	WinRect operator+(SIZE size) const;
	WinRect operator-(SIZE size) const;
	WinRect operator-(LPCRECT lpRect) const;
	WinRect operator&(const RECT& rect2) const;
	WinRect operator|(const RECT& rect2) const;
	WinRect MulDiv(int nMultiplier, int nDivisor) const;
};

#endif // !defined(AFX_WINRECT_H__0915F5E8_88DA_4027_BE14_43EC99A8840F__INCLUDED_)
