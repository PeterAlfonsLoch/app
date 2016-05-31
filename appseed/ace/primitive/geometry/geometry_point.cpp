//#include "framework.h"

// point
point::point() throw()
   { /* random filled */ }
point::point(int64_t initX, int64_t initY) throw()
   { x = (int32_t) initX; y = (int32_t) initY; }
point::point(POINT initPt) throw()
   { *(POINT*)this = initPt; }
point::point(SIZE initSize) throw()
   { *(SIZE*)this = initSize; }
point::point(POINT64 pt) throw()
   { x = (int32_t) pt.x; y = (int32_t) pt.y; }
point::point(const POINT64 * ppt) throw()
{
   x = (int32_t)ppt->x; y = (int32_t)ppt->y;
}


point::point(const ::lparam & dwPoint) throw()
{

   x = dwPoint.x();

   y = dwPoint.y();

}


point::point(POINTD pt) throw()
{
   x = (int32_t)pt.x; y = (int32_t)pt.y;
}
point::point(const POINTD * ppt) throw()
{
   x = (int32_t)ppt->x; y = (int32_t)ppt->y;
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
point64::point64(POINT64 initPt) throw()
   { *(POINT64*)this = initPt; }
point64::point64(POINT initPt) throw()
   { x = initPt.x; y = initPt.y; }
point64::point64(const POINT64 * pinitPt) throw()
   { *(POINT64*)this = *pinitPt; }
point64::point64(SIZE64 initSize) throw()
   { *(SIZE64*)this = initSize; }


point64::point64(const ::lparam & dwPoint) throw()
{
   
   x = dwPoint.x();
   
   y = dwPoint.y();

}


point64::operator POINT64 *() throw()
   { return this; }
point64::operator const POINT64 *() const throw()
   { return this; }


void point64::offset(int64_t xOffset, int64_t yOffset) throw()
   { x += xOffset; y += yOffset; }
void point64::offset(POINT64 point64) throw()
   { x += point64.x; y += point64.y; }
void point64::offset(SIZE64 size64) throw()
   { x += size64.cx; y += size64.cy; }
void point64::SetPoint(int64_t X, int64_t Y) throw()
   { x = X; y = Y; }
bool point64::operator==(POINT64 point64) const throw()
   { return (x == point64.x && y == point64.y); }
bool point64::operator!=(POINT64 point64) const throw()
   { return (x != point64.x || y != point64.y); }
void point64::operator+=(SIZE64 size64) throw()
   { x += size64.cx; y += size64.cy; }
void point64::operator-=(SIZE64 size64) throw()
   { x -= size64.cx; y -= size64.cy; }
void point64::operator+=(POINT64 point64) throw()
   { x += point64.x; y += point64.y; }
void point64::operator-=(POINT64 point64) throw()
   { x -= point64.x; y -= point64.y; }
point64 point64::operator+(SIZE64 size64) const throw()
   { return point64(x + size64.cx, y + size64.cy); }
point64 point64::operator-(SIZE64 size64) const throw()
   { return point64(x - size64.cx, y - size64.cy); }
point64 point64::operator-() const throw()
   { return point64(-x, -y); }
point64 point64::operator+(POINT64 pt) const throw()
   { return point64(x + pt.x, y + pt.y); }
size64 point64::operator-(POINT64 pt) const throw()
   { return size64(x - pt.x, y - pt.y); }
rect64 point64::operator+(const RECT64 * lpRect) const throw()
   { return rect64(lpRect) + *this; }
rect64 point64::operator-(const RECT64 * lpRect) const throw()
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

pointd::pointd(POINT64 pt) throw()
{

   x = (int32_t) pt.x;
   
   y = (int32_t) pt.y;

}


pointd::pointd(const ::lparam & dwPoint) throw()
{
   
   x = dwPoint.x();
   
   y = dwPoint.y();

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




point3d point3d::rotate(point3d p)
{

   point3d p1;
   p1.x = x *cos(p.z) - y * sin(p.z) ;
   p1.y = x *sin(p.z) + y * cos(p.z) ;
   p1.z = z;

   point3d p2;
   p2.y = p1.y*cos(p.x) - p1.z * sin(p.x) ;
   p2.z = p1.y *sin(p.x) + p1.z * cos(p.x) ;
   p2.x = p1.x;

   point3d p3;
   p3.z = p2.z *cos(p.y) - p2.x * sin(p.y) ;
   p3.x = p2.z *sin(p.y) + p2.x * cos(p.y) ;
   p3.y = p2.y;

   return p3;
}


