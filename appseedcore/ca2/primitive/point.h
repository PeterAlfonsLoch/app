#pragma once


/////////////////////////////////////////////////////////////////////////////
// point - A 2-D point, similar to Windows POINT structure.

class CLASS_DECL_ca point : public tagPOINT
{
public:
// Constructors

   // create an uninitialized point
   point() throw();
   // create from two integers
   point(__int64 initX, __int64 initY) throw();
   // create from another point
   point(POINT initPt) throw();
   point(const POINT * pinitPt) throw();
   point(__point64 initPt) throw();
   point(const __point64 * pinitPt) throw();
   // create from a size
   point(SIZE initSize) throw();
   // create from an LPARAM: x = LOWORD(dw) y = HIWORD(dw)
   point(LPARAM dwPoint) throw();


   operator POINT *();
   operator const POINT *() const;

// Operations

// translate the point
   void Offset(int xOffset, int yOffset) throw();
   void Offset(POINT point) throw();
   void Offset(SIZE size) throw();
   void SetPoint(int X, int Y) throw();

   BOOL operator==(POINT point) const throw();
   BOOL operator!=(POINT point) const throw();
   void operator+=(SIZE size) throw();
   void operator-=(SIZE size) throw();
   void operator+=(POINT point) throw();
   void operator-=(POINT point) throw();

// Operators returning point values
   point operator+(SIZE size) const throw();
   point operator-(SIZE size) const throw();
   point operator-() const throw();
   point operator+(POINT point) const throw();

// Operators returning size values
   size operator-(POINT point) const throw();

// Operators returning rect values
   rect operator+(const RECT* lpRect) const throw();
   rect operator-(const RECT* lpRect) const throw();

   LPARAM _001GetLparam();
};


__inline point null_point() { return point(0, 0); }

/////////////////////////////////////////////////////////////////////////////
// point64 - A 2-D point64, similar to Windows __point64 structure.

class CLASS_DECL_ca point64 : public __point64
{
public:
// Constructors

   // create an uninitialized point64
   point64() throw();
   // create from two integers
   point64(__int64 initX, __int64 initY) throw();
   // create from another point64
   point64(__point64 initPt) throw();
   point64(POINT pt) throw();
   point64(const __point64 * pinitPt) throw();
   // create from a size
   point64(__size64 initSize) throw();
   // create from an UINT64: x = LODWORD(dw) y = HIDWORD(dw)
   point64(unsigned __int64 dwPoint) throw();

   operator __point64 *() throw();
   operator const __point64 *() const throw();

// Operations

// translate the point64
   void Offset(__int64 xOffset, __int64 yOffset) throw();
   void Offset(__point64 point64) throw();
   void Offset(__size64 size) throw();
   void SetPoint(__int64 X, __int64 Y) throw();

   BOOL operator==(__point64 point64) const throw();
   BOOL operator!=(__point64 point64) const throw();
   void operator+=(__size64 size) throw();
   void operator-=(__size64 size) throw();
   void operator+=(__point64 point64) throw();
   void operator-=(__point64 point64) throw();

// Operators returning point64 values
   point64 operator+(__size64 size) const throw();
   point64 operator-(__size64 size) const throw();
   point64 operator-() const throw();
   point64 operator+(__point64 point64) const throw();

// Operators returning size values
   size64 operator-(__point64 point64) const throw();

// Operators returning rect values
   rect64 operator+(const __rect64 * lpRect) const throw();
   rect64 operator-(const __rect64 * lpRect) const throw();

   unsigned __int64 _001GetLparam();
};
