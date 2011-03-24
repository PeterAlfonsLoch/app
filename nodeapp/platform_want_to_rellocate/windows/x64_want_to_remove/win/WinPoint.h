// WinPoint.h: interface for the WinPoint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINPOINT_H__26B2FC08_9ADF_485B_ABAF_428AB12789EB__INCLUDED_)
#define AFX_WINPOINT_H__26B2FC08_9ADF_485B_ABAF_428AB12789EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// WinPoint - A 2-D point, similar to Windows POINT structure.

class WinPoint : public tagPOINT
{
public:
// Constructors

	// create an uninitialized point
	WinPoint();
	// create from two integers
	WinPoint(int initX, int initY);
	// create from another point
	WinPoint(POINT initPt);
	// create from a size
	WinPoint(SIZE initSize);
	// create from a dword: x = LOWORD(dw) y = HIWORD(dw)
	WinPoint(DWORD dwPoint);

// Operations

// translate the point
	void Offset(int xOffset, int yOffset);
	void Offset(POINT point);
	void Offset(SIZE size);

	BOOL operator==(POINT point) const;
	BOOL operator!=(POINT point) const;
	void operator+=(SIZE size);
	void operator-=(SIZE size);
	void operator+=(POINT point);
	void operator-=(POINT point);

// Operators returning WinPoint values
	WinPoint operator+(SIZE size) const;
	WinPoint operator-(SIZE size) const;
	WinPoint operator-() const;
	WinPoint operator+(POINT point) const;

// Operators returning size values
	size operator-(POINT point) const;

// Operators returning rect values
	rect operator+(const RECT* lpRect) const;
	rect operator-(const RECT* lpRect) const;
};


#endif // !defined(AFX_WINPOINT_H__26B2FC08_9ADF_485B_ABAF_428AB12789EB__INCLUDED_)
