#include "framework.h"

// point
point::point() throw()
   { /* random filled */ }
point::point(int64_t initX, int64_t initY) throw()
   { x = (int32_t) initX; y = (int32_t) initY; }
point::point(POINT initPt) throw()
   { *(POINT*)this = initPt; }
point::point(SIZE initSize) throw()
   { *(SIZE*)this = initSize; }
point::point(__point64 pt) throw()
   { x = (int32_t) pt.x; y = (int32_t) pt.y; }
point::point(const ::lparam & dwPoint) throw()
   {
      x = (int16_t)GET_X_LPARAM(dwPoint.m_lparam);
      y = (int16_t)GET_Y_LPARAM(dwPoint.m_lparam);
   }

point::operator POINT *() throw()
   { return this; }
point::operator const POINT *() const throw()
   { return this; }

void point::offset(int32_t xOffset, int32_t yOffset) throw()
   { x += xOffset; y += yOffset; }
void point::offset(POINT point) throw()
   { x += point.x; y += point.y; }
void point::offset(SIZE size) throw()
   { x += size.cx; y += size.cy; }
void point::SetPoint(int32_t X, int32_t Y) throw()
   { x = X; y = Y; }
bool point::operator==(POINT point) const throw()
   { return (x == point.x && y == point.y); }
bool point::operator!=(POINT point) const throw()
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
point point::operator+(POINT pt) const throw()
   { return point(x +  pt.x, y +  pt.y); }
size point::operator-(POINT  pt) const throw()
   { return size(x -  pt.x, y -  pt.y); }
rect point::operator+(LPCRECT lpRect) const throw()
   { return rect(lpRect) + *this; }
rect point::operator-(LPCRECT lpRect) const throw()
   { return rect(lpRect) - *this; }

uint32_t point::ui32() const throw()
{
   return MAKELONG(x, y);
}

uint64_t point::ui64() const throw()
{
   return MAKELONG64(x, y);
}

LPARAM point::lparam() const throw()
{
   return MAKELPARAM(x, y);
}







// point64
point64::point64() throw()
   { /* random filled */ }
point64::point64(int64_t initX, int64_t initY) throw()
   { x = initX; y = initY; }
point64::point64(__point64 initPt) throw()
   { *(__point64*)this = initPt; }
point64::point64(POINT initPt) throw()
   { x = initPt.x; y = initPt.y; }
point64::point64(const __point64 * pinitPt) throw()
   { *(__point64*)this = *pinitPt; }
point64::point64(__size64 initSize) throw()
   { *(__size64*)this = initSize; }
point64::point64(uint64_t dwPoint) throw()
   {
      x = (int32_t)GET_X_LPARAM64(dwPoint);
      y = (int32_t)GET_Y_LPARAM64(dwPoint);
   }


point64::operator __point64 *() throw()
   { return this; }
point64::operator const __point64 *() const throw()
   { return this; }


void point64::offset(int64_t xOffset, int64_t yOffset) throw()
   { x += xOffset; y += yOffset; }
void point64::offset(__point64 point64) throw()
   { x += point64.x; y += point64.y; }
void point64::offset(__size64 size64) throw()
   { x += size64.cx; y += size64.cy; }
void point64::SetPoint(int64_t X, int64_t Y) throw()
   { x = X; y = Y; }
bool point64::operator==(__point64 point64) const throw()
   { return (x == point64.x && y == point64.y); }
bool point64::operator!=(__point64 point64) const throw()
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
point64 point64::operator+(__point64 pt) const throw()
   { return point64(x + pt.x, y + pt.y); }
size64 point64::operator-(__point64 pt) const throw()
   { return size64(x - pt.x, y - pt.y); }
rect64 point64::operator+(const __rect64 * lpRect) const throw()
   { return rect64(lpRect) + *this; }
rect64 point64::operator-(const __rect64 * lpRect) const throw()
   { return rect64(lpRect) - *this; }

uint32_t point64::ui32() const throw()
{
   return MAKELONG(x, y);
}

uint64_t point64::ui64() const throw()
{
   return MAKELONG64(x, y);
}

LPARAM point64::lparam() const throw()
{
   return MAKELPARAM(x, y);
}






























// pointd
pointd::pointd() throw()
   { /* random filled */ }
pointd::pointd(double initX, double initY) throw()
   { x = (double) initX; y = (double) initY; }
pointd::pointd(POINTD initPt) throw()
   { *(POINTD*)this = initPt; }
pointd::pointd(POINT initPt) throw()
{
   x = (double) initPt.x;
   y = (double) initPt.y;
}
pointd::pointd(SIZED initSize) throw()
   { *(SIZED*)this = initSize; }
pointd::pointd(__point64 pt) throw()
   { x = (int32_t) pt.x; y = (int32_t) pt.y; }
pointd::pointd(LPARAM dwPoint) throw()
   {
      x = (int16_t)GET_X_LPARAM(dwPoint);
      y = (int16_t)GET_Y_LPARAM(dwPoint);
   }

pointd::operator POINTD *() throw()
   { return this; }
pointd::operator const POINTD *() const throw()
   { return this; }

void pointd::offset(int32_t xOffset, int32_t yOffset) throw()
   { x += xOffset; y += yOffset; }
void pointd::offset(POINTD pointd) throw()
   { x += pointd.x; y += pointd.y; }
void pointd::offset(SIZED size) throw()
   { x += size.cx; y += size.cy; }
void pointd::SetPoint(int32_t X, int32_t Y) throw()
   { x = X; y = Y; }
bool pointd::operator==(POINTD pointd) const throw()
   { return (x == pointd.x && y == pointd.y); }
bool pointd::operator!=(POINTD pointd) const throw()
   { return (x != pointd.x || y != pointd.y); }
void pointd::operator+=(SIZED size) throw()
   { x += size.cx; y += size.cy; }
void pointd::operator-=(SIZED size) throw()
   { x -= size.cx; y -= size.cy; }
void pointd::operator+=(POINTD pointd) throw()
   { x += pointd.x; y += pointd.y; }
void pointd::operator-=(POINTD pointd) throw()
   { x -= pointd.x; y -= pointd.y; }
pointd pointd::operator+(SIZED size) const throw()
   { return pointd(x + size.cx, y + size.cy); }
pointd pointd::operator-(SIZED size) const throw()
   { return pointd(x - size.cx, y - size.cy); }
pointd pointd::operator-() const throw()
   { return pointd(-x, -y); }
pointd pointd::operator+(POINTD pt) const throw()
   { return pointd(x +  pt.x, y +  pt.y); }
sized pointd::operator-(POINTD  pt) const throw()
   { return sized(x -  pt.x, y -  pt.y); }
rectd pointd::operator+(LPCRECTD lpRect) const throw()
   { return rectd(lpRect) + *this; }
rectd pointd::operator-(LPCRECTD lpRect) const throw()
   { return rectd(lpRect) - *this; }

uint32_t pointd::ui32() const throw()
{
   return MAKELONG((int32_t) x, (int32_t) y);
}

uint64_t pointd::ui64() const throw()
{
   return MAKELONG64((int32_t) x, (int32_t) y);
}

LPARAM pointd::lparam() const throw()
{
   return MAKELPARAM((int32_t) x, (int32_t) y);
}
