#include "StdAfx.h"

// point
point::point() throw()
   { /* random filled */ }
point::point(__int64 initX, __int64 initY) throw()
   { x = (int) initX; y = (int) initY; }
point::point(POINT initPt) throw()
   { *(POINT*)this = initPt; }
point::point(SIZE initSize) throw()
   { *(SIZE*)this = initSize; }
point::point(__point64 pt) throw()
   { x = (int) pt.x; y = (int) pt.y; }
point::point(LPARAM dwPoint) throw()
   {
      x = (short)GET_X_LPARAM(dwPoint);
      y = (short)GET_Y_LPARAM(dwPoint);
   }

point::operator POINT *() throw()
   { return this; }
point::operator const POINT *() const throw()
   { return this; }

void point::Offset(int xOffset, int yOffset) throw()
   { x += xOffset; y += yOffset; }
void point::Offset(POINT point) throw()
   { x += point.x; y += point.y; }
void point::Offset(SIZE size) throw()
   { x += size.cx; y += size.cy; }
void point::SetPoint(int X, int Y) throw()
   { x = X; y = Y; }
BOOL point::operator==(POINT point) const throw()
   { return (x == point.x && y == point.y); }
BOOL point::operator!=(POINT point) const throw()
   { return (x != point.x || y != point.y); }
void point::operator+=(SIZE size) throw()
   { x += size.cx; y += size.cy; }
void point::operator-=(SIZE size) throw()
   { x -= size.cx; y -= size.cy; }
void point::operator+=(POINT point) throw()
   { x += point.x; y += point.y; }
void point::operator-=(POINT point) throw()
   { x -= point.x; y -= point.y; }
point point::operator+(SIZE size) const throw()
   { return point(x + size.cx, y + size.cy); }
point point::operator-(SIZE size) const throw()
   { return point(x - size.cx, y - size.cy); }
point point::operator-() const throw()
   { return point(-x, -y); }
point point::operator+(POINT point) const throw()
   { return class point(x + point.x, y + point.y); }
size point::operator-(POINT point) const throw()
   { return size(x - point.x, y - point.y); }
rect point::operator+(const RECT* lpRect) const throw()
   { return rect(lpRect) + *this; }
rect point::operator-(const RECT* lpRect) const throw()
   { return rect(lpRect) - *this; }

LPARAM point::_001GetLparam()
{
   return MAKELPARAM(x, y);
}









// point64
point64::point64() throw()
   { /* random filled */ }
point64::point64(__int64 initX, __int64 initY) throw()
   { x = initX; y = initY; }
point64::point64(__point64 initPt) throw()
   { *(__point64*)this = initPt; }
point64::point64(POINT initPt) throw()
   { x = initPt.x; y = initPt.y; }
point64::point64(const __point64 * pinitPt) throw()
   { *(__point64*)this = *pinitPt; }
point64::point64(__size64 initSize) throw()
   { *(__size64*)this = initSize; }
point64::point64(unsigned __int64 dwPoint) throw()
   {
      x = (int)GET_X_LPARAM64(dwPoint);
      y = (int)GET_Y_LPARAM64(dwPoint);
   }


point64::operator __point64 *() throw()
   { return this; }
point64::operator const __point64 *() const throw()
   { return this; }


void point64::Offset(__int64 xOffset, __int64 yOffset) throw()
   { x += xOffset; y += yOffset; }
void point64::Offset(__point64 point64) throw()
   { x += point64.x; y += point64.y; }
void point64::Offset(__size64 size64) throw()
   { x += size64.cx; y += size64.cy; }
void point64::SetPoint(__int64 X, __int64 Y) throw()
   { x = X; y = Y; }
BOOL point64::operator==(__point64 point64) const throw()
   { return (x == point64.x && y == point64.y); }
BOOL point64::operator!=(__point64 point64) const throw()
   { return (x != point64.x || y != point64.y); }
void point64::operator+=(__size64 size64) throw()
   { x += size64.cx; y += size64.cy; }
void point64::operator-=(__size64 size64) throw()
   { x -= size64.cx; y -= size64.cy; }
void point64::operator+=(__point64 point64) throw()
   { x += point64.x; y += point64.y; }
void point64::operator-=(__point64 point64) throw()
   { x -= point64.x; y -= point64.y; }
point64 point64::operator+(__size64 size64) const throw()
   { return point64(x + size64.cx, y + size64.cy); }
point64 point64::operator-(__size64 size64) const throw()
   { return point64(x - size64.cx, y - size64.cy); }
point64 point64::operator-() const throw()
   { return point64(-x, -y); }
point64 point64::operator+(__point64 point64) const throw()
   { return class point64(x + point64.x, y + point64.y); }
size64 point64::operator-(__point64 point64) const throw()
   { return size64(x - point64.x, y - point64.y); }
rect64 point64::operator+(const __rect64 * lpRect) const throw()
   { return rect64(lpRect) + *this; }
rect64 point64::operator-(const __rect64 * lpRect) const throw()
   { return rect64(lpRect) - *this; }

unsigned __int64 point64::_001GetLparam()
{
   return MAKELONG64(x, y);
}


