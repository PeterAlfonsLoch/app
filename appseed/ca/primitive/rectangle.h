#pragma once


#include "geometric_types.h"


class point_array;


/////////////////////////////////////////////////////////////////////////////
// rect - A 2-D rectangle, similar to Windows RECT structure.

class CLASS_DECL_ca rect : public tagRECT
{
// Constructors
public:
   // uninitialized rectangle
   rect() throw();
   // from left, top, right, and bottom
   rect(__int64 l, __int64 t, __int64 r, __int64 b) throw();
   // copy constructor
   rect(const RECT& srcRect) throw();
   rect(const __rect64& srcRect) throw();
   // from a pointer to another rect
   rect(LPCRECT lpSrcRect) throw();
   // from a point and size
   rect(POINT point, SIZE size) throw();
   // from two points
   rect(POINT topLeft, POINT bottomRight) throw();

// Attributes (in addition to RECT members)

   // retrieves the width
   int width() const throw();
   // returns the height
   int height() const throw();
   // returns the size
   class size size() const throw();
   // reference to the top-left point
   point& top_left() throw();
   // reference to the bottom-right point
   point& bottom_right() throw();
   // const reference to the top-left point
   const point& top_left() const throw();
   // const reference to the bottom-right point
   const point& bottom_right() const throw();
   // the geometric center point of the rectangle
   point center() const throw();
   // swap the left and right
   void swap_left_right() throw();
   static void WINAPI swap_left_right(LPRECT lpRect) throw();

   // convert between rect and LPRECT/LPCRECT (no need for &)
   operator LPRECT() throw();
   operator LPCRECT() const throw();

   // returns TRUE if rectangle has no area
   bool is_empty() const throw();
   // returns TRUE if rectangle is at (0,0) and has no area
   bool is_null() const throw();
   // returns TRUE if point is within rectangle
   bool contains(POINT point) const throw();

// Operations

   // set rectangle from left, top, right, and bottom
   void set(int x1, int y1, int x2, int y2) throw();
   void set(POINT topLeft, POINT bottomRight) throw();
   // is_empty the rectangle
   void null() throw();
   // copy from another rectangle
   void copy(LPCRECT lpSrcRect) throw();
   // TRUE if exactly the same as another rectangle
   bool is_equal(LPCRECT lpRect) const throw();

   // Inflate rectangle's width and height by
   // x units to the left and right ends of the rectangle
   // and y units to the top and bottom.
   void inflate(int x, int y) throw();
   // Inflate rectangle's width and height by
   // size.cx units to the left and right ends of the rectangle
   // and size.cy units to the top and bottom.
   void inflate(SIZE size) throw();
   // Inflate rectangle's width and height by moving individual sides.
   // Left side is moved to the left, right side is moved to the right,
   // top is moved up and bottom is moved down.
   void inflate(LPCRECT lpRect) throw();
   void inflate(int l, int t, int r, int b) throw();

   // deflate the rectangle's width and height without
   // moving its top or left
   void deflate(int x, int y) throw();
   void deflate(SIZE size) throw();
   void deflate(LPCRECT lpRect) throw();
   void deflate(int l, int t, int r, int b) throw();

   // translate the rectangle by moving its top and left
   void offset(int x, int y) throw();
   void offset(SIZE size) throw();
   void offset(POINT point) throw();
   void normalize() throw();

   // absolute position of rectangle
   void move_to_y(int y) throw();
   void move_to_x(int x) throw();
   void move_to(int x, int y) throw();
   void move_to(POINT point) throw();

   // set this rectangle to intersection of two others
   bool intersect(LPCRECT lpRect1, LPCRECT lpRect2) throw();

   // set this rectangle to bounding union of two others
   bool unite(LPCRECT lpRect1, LPCRECT lpRect2) throw();

   // set this rectangle to minimum of two others
   bool subtract(LPCRECT lpRectSrc1, LPCRECT lpRectSrc2) throw();

// Additional Operations
   void operator=(const RECT& srcRect) throw();
   bool operator==(const RECT& rect) const throw();
   bool operator!=(const RECT& rect) const throw();
   void operator+=(POINT point) throw();
   void operator+=(SIZE size) throw();
   void operator+=(LPCRECT lpRect) throw();
   void operator-=(POINT point) throw();
   void operator-=(SIZE size) throw();
   void operator-=(LPCRECT lpRect) throw();
   void operator&=(const RECT& rect) throw();
   void operator|=(const RECT& rect) throw();

// Operators returning rect values
   rect operator+(POINT point) const throw();
   rect operator-(POINT point) const throw();
   rect operator+(LPCRECT lpRect) const throw();
   rect operator+(SIZE size) const throw();
   rect operator-(SIZE size) const throw();
   rect operator-(LPCRECT lpRect) const throw();
   rect operator&(const RECT& rect2) const throw();
   rect operator|(const RECT& rect2) const throw();
   rect MulDiv(int nMultiplier, int nDivisor) const throw();

   __int64 area();

   bool contains(LPCRECT lpcrect) const;
   void ConstraintV5(LPCRECT lpcrect, const class size sizeMin);
   void Align(int align, LPCRECT lpcrect);
   void ScaleHeightAspect(int iNewHeight, int iCenterX, int iCenterY);
   void ScaleRect(double dx, double dy, int ix, int iy);
   void ExtendOnCenter(LPCRECT lpcrect);
   void FitOnCenterOf(LPCRECT lpcrect);
   void DeflateBottomRightSizeByRate(double dRate);
   void SetBottomRightSize(int iWidth, int iHeight);
   inline point top_right();
   inline point bottom_left();

   void SubtractRectMajor(LPCRECT lpcrectMajor, LPCRECT lpcrectMinor);
   void SubtractRectMinor(LPCRECT lpcrectMajor, LPCRECT lpcrectMinor);


   void get_bounding_rect(const POINT * lppoint, count count);
   void get_bounding_rect(const point_array & pointa);

};

/////////////////////////////////////////////////////////////////////////////
// rect64 - A 2-D rect64angle, similar to Windows RECT structure.

class CLASS_DECL_ca rect64 : public __rect64
{
// Constructors
public:
   // uninitialized rect64angle
   rect64() throw();
   // from left, top, right, and bottom
   rect64(__int64 l, __int64 t, __int64 r, __int64 b) throw();
   // copy constructor
   rect64(const RECT& srcRect) throw();
   // copy constructor
   rect64(const __rect64 & srcRect) throw();
   // from a po__int64er to another rect64
   rect64(const RECT * lpSrcRect) throw();
   // from a po__int64er to another rect64
   rect64(const __rect64 * lpSrcRect) throw();
   // from a __point64 and size
   rect64(__point64 __point64, __size64 size) throw();
   // from two po__int64s
   rect64(__point64 topLeft, __point64 bottomRight) throw();

// Attributes (in addition to RECT members)

   // retrieves the width
   __int64 width() const throw();
   // returns the height
   __int64 height() const throw();
   // returns the size
   size64 size() const throw();
   // reference to the top-left __point64
   point64& top_left() throw();
   // reference to the bottom-right __point64
   point64& bottom_right() throw();
   // const reference to the top-left __point64
   const point64& top_left() const throw();
   // const reference to the bottom-right __point64
   const point64& bottom_right() const throw();
   // the geometric center __point64 of the rect64angle
   point64 center() const throw();
   // swap the left and right
   void swap_left_right() throw();
   static void WINAPI swap_left_right(__rect64 * lpRect) throw();

   // convert between rect64 and __rect64 */const __rect64 * (no need for &)
   operator __rect64 *() throw();
   operator const __rect64 *() const throw();
   operator rect() const;

   // returns TRUE if rect64angle has no area
   bool is_empty() const throw();
   // returns TRUE if rect64angle is at (0,0) and has no area
   bool is_null() const throw();
   // returns TRUE if __point64 is within rect64angle
   bool contains(__point64 pt) const throw();

// Operations

   // set rect64angle from left, top, right, and bottom
   void set(__int64 x1, __int64 y1, __int64 x2, __int64 y2) throw();
   void set(__point64 topLeft, __point64 bottomRight) throw();
   // is_empty the rect64angle
   void null() throw();
   // copy from another rect64angle
   void copy(const __rect64 * lpSrcRect) throw();
   // TRUE if exactly the same as another rect64angle
   bool is_equal(const __rect64 * lpRect) const throw();

   // Inflate rect64angle's width and height by
   // x units to the left and right ends of the rect64angle
   // and y units to the top and bottom.
   void inflate(__int64 x, __int64 y) throw();
   // Inflate rect64angle's width and height by
   // size.cx units to the left and right ends of the rect64angle
   // and size.cy units to the top and bottom.
   void inflate(__size64 size) throw();
   // Inflate rect64angle's width and height by moving individual sides.
   // Left side is moved to the left, right side is moved to the right,
   // top is moved up and bottom is moved down.
   void inflate(const __rect64 * lpRect) throw();
   void inflate(__int64 l, __int64 t, __int64 r, __int64 b) throw();

   // deflate the rect64angle's width and height without
   // moving its top or left
   void deflate(__int64 x, __int64 y) throw();
   void deflate(__size64 size) throw();
   void deflate(const __rect64 * lpRect) throw();
   void deflate(__int64 l, __int64 t, __int64 r, __int64 b) throw();

   // translate the rect64angle by moving its top and left
   void offset(__int64 x, __int64 y) throw();
   void offset(__size64 size) throw();
   void offset(__point64 __point64) throw();
   void normalize() throw();

   // absolute position of rect64angle
   void move_to_y(__int64 y) throw();
   void move_to_x(__int64 x) throw();
   void move_to(__int64 x, __int64 y) throw();
   void move_to(__point64 pt) throw();

   // set this rect64angle to __int64ersection of two others
   bool intersect(const __rect64 * lpRect1, const __rect64 * lpRect2) throw();

   // set this rect64angle to bounding union of two others
   bool unite(const __rect64 * lpRect1, const __rect64 * lpRect2) throw();

   // set this rect64angle to minimum of two others
//   bool subtract(const __rect64 * lpRectSrc1, const __rect64 * lpRectSrc2) throw();

// Additional Operations
   void operator=(const __rect64& srcRect) throw();
   bool operator==(const __rect64& rect64) const throw();
   bool operator!=(const __rect64& rect64) const throw();
   void operator+=(__point64 __point64) throw();
   void operator+=(__size64 size) throw();
   void operator+=(const __rect64 * lpRect) throw();
   void operator-=(__point64 __point64) throw();
   void operator-=(__size64 size) throw();
   void operator-=(const __rect64 * lpRect) throw();
   void operator&=(const __rect64& rect64) throw();
   void operator|=(const __rect64& rect64) throw();

// Operators returning rect64 values
   rect64 operator+(__point64 __point64) const throw();
   rect64 operator-(__point64 __point64) const throw();
   rect64 operator+(const __rect64 * lpRect) const throw();
   rect64 operator+(__size64 size) const throw();
   rect64 operator-(__size64 size) const throw();
   rect64 operator-(const __rect64 * lpRect) const throw();
   rect64 operator&(const __rect64 & rect642) const throw();
   rect64 operator|(const __rect64& rect642) const throw();
   rect64 MulDiv(__int64 nMultiplier, __int64 nDivisor) const throw();

   __int64 area();
   bool contains(const __rect64 * lpcrect) const;
   bool contains(const __rect64 * lpcrect);
   void ConstraintV5(const __rect64 * lpcrect, const class size sizeMin);
   void Align(__int64 align, const __rect64 * lpcrect);
   void ScaleHeightAspect(__int64 iNewHeight, __int64 iCenterX, __int64 iCenterY);
   void ScaleRect(double dx, double dy, __int64 ix, __int64 iy);
   void ExtendOnCenter(const __rect64 * lpcrect);
   void FitOnCenterOf(const __rect64 * lpcrect);
   void DeflateBottomRightSizeByRate(double dRate);
   void SetBottomRightSize(__int64 iWidth, __int64 iHeight);

   inline point64 top_right() const throw();
   inline point64 bottom_left() const throw();

   void SubtractRectMajor(const __rect64 * lpcrectMajor, const __rect64 * lpcrectMinor);
   void SubtractRectMinor(const __rect64 * lpcrectMajor, const __rect64 * lpcrectMinor);

};





inline point rect::top_right()
{
   return point(right, top);
}

inline point rect::bottom_left()
{
   return point(left, bottom);
}

inline point rect::center() const throw()
{
   return point((left + right) / 2, (top + bottom) / 2);
}

inline bool rect::is_null() const throw()
{
   return left == 0 && top == 0 && right == 0 && bottom == 0;
}

inline bool rect::is_empty() const throw()
{
   return width() == 0 && height() == 0;
}









inline point64 rect64::top_right() const throw()
{
   return point64(right, top);
}

inline point64 rect64::bottom_left() const throw()
{
   return point64(left, bottom);
}

inline point64 rect64::center() const throw()
{
   return point64((left + right) / 2, (top + bottom) / 2);
}

inline bool rect64::is_null() const throw()
{
   return left == 0 && top == 0 && right == 0 && bottom == 0;
}

inline bool rect64::is_empty() const throw()
{
   return width() == 0 && height() == 0;
}
