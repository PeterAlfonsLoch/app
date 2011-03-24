// WinSize.h: interface for the WinSize class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINSIZE_H__C0205FA8_76D6_4F48_BEE9_F478E3801406__INCLUDED_)
#define AFX_WINSIZE_H__C0205FA8_76D6_4F48_BEE9_F478E3801406__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// WinSize - An extent, similar to Windows SIZE structure.

class WinSize : public tagSIZE
{
public:

// Constructors
	// construct an uninitialized size
	WinSize();
	// create from two integers
	WinSize(int initCX, int initCY);
	// create from another size
	WinSize(SIZE initSize);
	// create from a point
	WinSize(POINT initPt);
	// create from a DWORD: cx = LOWORD(dw) cy = HIWORD(dw)
	WinSize(DWORD dwSize);

// Operations
	BOOL operator==(SIZE size) const;
	BOOL operator!=(SIZE size) const;
	void operator+=(SIZE size);
	void operator-=(SIZE size);

// Operators returning WinSize values
	WinSize operator+(SIZE size) const;
	WinSize operator-(SIZE size) const;
	WinSize operator-() const;

// Operators returning point values
	point operator+(POINT point) const;
	point operator-(POINT point) const;

// Operators returning rect values
	rect operator+(const RECT* lpRect) const;
	rect operator-(const RECT* lpRect) const;
};

#endif // !defined(AFX_WINSIZE_H__C0205FA8_76D6_4F48_BEE9_F478E3801406__INCLUDED_)
