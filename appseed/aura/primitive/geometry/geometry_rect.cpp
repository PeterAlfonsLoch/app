#include "framework.h"


void rect::DeflateBottomRightSizeByRate(double dRate)
{
    double dx = width();
    double dy = height();
    double dxNew = dx / dRate;
    double dyNew = dy / dRate;
    dx = dx - dxNew;
    dy = dy - dyNew;
    right -= (long) dx;
    bottom -= (long) dy;
}

void rect::SetBottomRightSize(int32_t iWidth, int32_t iHeight)
{
    right = left + iWidth;
    bottom = top + iHeight;
}

void rect::ExtendOnCenter(const RECT & rect)
{

   int32_t cx = width();
   int32_t cy = height();

   double dx = ::width(rect);
   double dy = ::height(rect);
   double dr = MAX(dx / cx, dy / cy);

   int32_t cw = (int32_t) (cx * dr);
   int32_t ch = (int32_t) (cy * dr);
   
   left = (LONG) ((dx - cw) / 2.0);
   top = (LONG) ((dy - ch) / 2.0);
   right = left + cw;
   bottom = top + ch;
   
}

void rect::FitOnCenterOf(const RECT & rect,SIZE size)
{
   int32_t cx = size.cx;
   int32_t cy = size.cy;

   double dx = ::width(rect);
   double dy = ::height(rect);
   double dr = MIN(cx == 0 ? 1 : dx / cx,cy == 0 ? 1 : dy / cy);

   int32_t cw = cx == 0 ? (int32_t)dx : ((int32_t)(cx * dr));
   int32_t ch = cy == 0 ? (int32_t)dy : ((int32_t)(cy * dr));

   left = (LONG)((rect.left) + (dx - cw) / 2.0);
   top = (LONG)((rect.top) + (dy - ch) / 2.0);
   right = left + cw;
   bottom = top + ch;

}

void rect::FitOnCenterOf(const RECT & rect)
{
   
   FitOnCenterOf(rect,size());
   
}


void rect::CenterOf(const RECT & rect,SIZE size)
{
   int32_t cx = size.cx;
   int32_t cy = size.cy;

   LONG dx = ::width(rect);
   LONG dy = ::height(rect);

   left     = rect.left   + (dx - cx) / 2;
   top      = rect.top    + (dy - cy) / 2;
   right    = left            + cx;
   bottom   = top             + cy;

}

void rect::CenterOf(const RECT & rect)
{

   CenterOf(rect,size());

}


void rect::ScaleRect(double dx, double dy, int32_t ix, int32_t iy)
{
   left    = (LONG) (((left    - ix) * dx) + ix);
   top     = (LONG) (((top     - iy) * dy) + iy);
   right   = (LONG) (((right   - ix) * dx) + ix);
   bottom  = (LONG) (((bottom  - iy) * dy) + iy);

}

void rect::ScaleHeightAspect(int32_t iNewHeight, int32_t iCenterX, int32_t iCenterY)
{
   int32_t iHeight = height();
   if(iHeight != 0)
   {
      double d = (double) iNewHeight / iHeight;
      ScaleRect(d, d, iCenterX, iCenterY);
   }
}

void rect::Align(int32_t align, const RECT & rect)
{

   point pt(0, 0);

   if((align & align_horizontal) == align_horizontal_center)
   {
      pt.x = rect.left + (rect.right - rect.left) / 2 - width() / 2 - left;
   }
   else if((align & align_horizontal) == align_left)
   {
      pt.x = rect.left - left;
   }
   else if((align & align_horizontal) == align_right)
   {
      pt.x = rect.right - right;
   }

   if((align & align_vertical) ==  align_vertical_center)
   {
      pt.y = rect.top + (rect.bottom - rect.top) / 2 - height() / 2 - top;
   }
   else if((align & align_vertical) == align_top)
   {
      pt.y = rect.top - top;
   }
   else if((align & align_vertical) == align_bottom)
   {
      pt.y = rect.bottom - bottom;
   }

   offset(pt);

}

void rect::constraint_v5(const RECT & rect, const class size sizeMin)
{
   if(left < rect.left)
      left = rect.left;
   if(right > rect.right)
      right = rect.right;
   if(top < rect.top)
      top = rect.top;
   if(bottom > rect.bottom)
      bottom = rect.bottom;

   if(width() < sizeMin.cx)
      right = left + sizeMin.cx;
   if(height() < sizeMin.cy)
      bottom = top + sizeMin.cy;

}

void rect::constraint_v7(const RECT & rect)
{

   ::size size = this->size();

   if(size.cx > ::width(rect))
   {

      intersect_x(this,&rect);

   }
   else if(intersect_x(this, &rect))
   {

      if(left == rect.left)
      {

         right = left + size.cx;

      }
      else
      {

         left = right - size.cx;

      }

   }

   if(size.cy > ::height(rect))
   {

      intersect_y(this,&rect);

   }
   else if(intersect_y(this,&rect))
   {

      if(top == rect.top)
      {

         bottom = top + size.cy;

      }
      else
      {

         top = bottom - size.cy;

      }

   }

}

bool rect::contains(const RECT & rect) const
{
   return rect.left >= left
      && rect.right <= right
      && rect.top >= top
      && rect.bottom <= bottom;
}

// Subtract minor from major and return the greatest box around.
void rect::SubtractRectMajor(LPCRECT lpcrectMajor, LPCRECT lpcrectMinor)
{
   rect rectIntersect;
   rect rectRet(*this);
   if(!rectIntersect.intersect(lpcrectMajor, lpcrectMinor))
   {
      rectRet = *lpcrectMajor;
   }
   else
   {
      if(rectIntersect == *lpcrectMajor)
      {
         rectRet.set(0, 0, 0, 0);
      }
      else
      {
         if(rectIntersect.left == lpcrectMajor->left
            && rectIntersect.right == lpcrectMajor->right)
         {
            if(rectIntersect.top == lpcrectMajor->top)
            {
               rectRet.set(
                  lpcrectMajor->left,
                  rectIntersect.top,
                  lpcrectMajor->right,
                  lpcrectMajor->bottom);
            }
            else if(rectIntersect.bottom == lpcrectMajor->bottom)
            {
               rectRet.set(
                  lpcrectMajor->left,
                  lpcrectMajor->top,
                  lpcrectMajor->right,
                  rectIntersect.bottom);
            }
            else
            {
               rectRet = *lpcrectMajor;
            }
         }
         else if(rectIntersect.top == lpcrectMajor->top
            && rectIntersect.bottom == lpcrectMajor->bottom)
         {
            if(rectIntersect.left == lpcrectMajor->left)
            {
               rectRet.set(
                  rectIntersect.left,
                  lpcrectMajor->top,
                  lpcrectMajor->right,
                  lpcrectMajor->bottom);
            }
            else if(rectIntersect.right == lpcrectMajor->right)
            {
               rectRet.set(
                  lpcrectMajor->left,
                  lpcrectMajor->top,
                  rectIntersect.right,
                  lpcrectMajor->bottom);
            }
            else
            {
               rectRet = *lpcrectMajor;
            }
         }
         else
         {
            rectRet = *lpcrectMajor;
         }
      }
   }
   *this = rectRet;
   return;

}

void rect::SubtractRectMinor(LPCRECT lpcrectMajor, LPCRECT lpcrectMinor)
{
   UNREFERENCED_PARAMETER(lpcrectMajor);
   UNREFERENCED_PARAMETER(lpcrectMinor);
}

LONG rect::minimum_signed_absolute_dimension(bool bNegativePreference) const throw()
{

   LONG w = width();

   LONG h = height();

   if(abs(w) < abs(h))
   {

      return w;

   }
   else if(abs(h) < abs(w))
   {

      return h;

   }
   else if(bNegativePreference) // absolutely equal, prefer negative ...
   {

      return min(w, h);

   }
   else // ... otherwise prefer positive
   {

      return max(w,h);

   }


}


LONG rect::minimum_signed_absolute_dimension(bool bPositivePreference) const throw()
{

   LONG w = width();

   LONG h = height();

   if(abs(w) > abs(h))
   {

      return w;

   }
   else if(abs(h) > abs(w))
   {

      return h;

   }
   else if(bPositivePreference) // absolutely equal, prefer positive ...
   {

      return max(w,h);

   }
   else // ... otherwise prefer negative
   {

      return min(w,h);

   }


}





void rect64::DeflateBottomRightSizeByRate(double dRate)
{
    double dx = (double) width();
    double dy = (double) height();
    double dxNew = dx / dRate;
    double dyNew = dy / dRate;
    dx = dx - dxNew;
    dy = dy - dyNew;
    right -= (long) dx;
    bottom -= (long) dy;
}

void rect64::SetBottomRightSize(int64_t iWidth, int64_t iHeight)
{
    right = left + iWidth;
    bottom = top + iHeight;
}

void rect64::ExtendOnCenter(const __rect64 *  lpcrect)
{
    int64_t cx = width();
    int64_t cy = height();

    double dx = (double) (lpcrect->right - lpcrect->left);
    double dy = (double) (lpcrect->bottom - lpcrect->top);
    double dr = MAX(dx / cx, dy / cy);

    int64_t cw = (int64_t) (cx * dr);
   int64_t ch = (int64_t) (cy * dr);
   left = (long) ((dx - cw) / 2.0);
   top = (long) ((dy - ch) / 2.0);
    right = left + cw;
    bottom = top + ch;
}


void rect64::FitOnCenterOf(const __rect64 *  lpcrect)
{
    int64_t cx = width();
    int64_t cy = height();

    double dx = (double) (lpcrect->right - lpcrect->left);
    double dy = (double) (lpcrect->bottom - lpcrect->top);
    double dr = MIN(cx == 0 ? 1 : dx / cx, cy == 0 ? 1 : dy / cy);

    int64_t cw = cx == 0 ? (int64_t) dx : ((int64_t) (cx * dr));
   int64_t ch = cy == 0 ? (int64_t) dy : ((int64_t) (cy * dr));
   left = (long) ((lpcrect->left) + (dx - cw) / 2.0);
   top = (long) ((lpcrect->top) + (dy - ch) / 2.0);
    right = left + cw;
    bottom = top + ch;
}

void rect64::ScaleRect(double dx, double dy, int64_t ix, int64_t iy)
{
   left    = (long) (((left    - ix) * dx) + ix);
   top     = (long) (((top     - iy) * dy) + iy);
   right   = (long) (((right   - ix) * dx) + ix);
   bottom  = (long) (((bottom  - iy) * dy) + iy);

}

void rect64::ScaleHeightAspect(int64_t iNewHeight, int64_t iCenterX, int64_t iCenterY)
{
   int64_t iHeight = height();
   if(iHeight != 0)
   {
      double d = (double) iNewHeight / iHeight;
      ScaleRect(d, d, iCenterX, iCenterY);
   }
}

void rect64::Align(int64_t align, const __rect64 *  lpcrect)
{

   point64 pt(0, 0);

   if((align & align_horizontal) == align_horizontal_center)
   {
      pt.x = lpcrect->left + (lpcrect->right - lpcrect->left) / 2 - width() / 2 - left;
   }
   else if((align & align_horizontal) == align_left)
   {
      pt.x = lpcrect->left - left;
   }
   else if((align & align_horizontal) == align_right)
   {
      pt.x = lpcrect->right - right;
   }

   if((align & align_vertical) ==  align_vertical_center)
   {
      pt.y = lpcrect->top + (lpcrect->bottom - lpcrect->top) / 2 - height() / 2 - top;
   }
   else if((align & align_vertical) == align_top)
   {
      pt.y = lpcrect->top - top;
   }
   else if((align & align_vertical) == align_bottom)
   {
      pt.y = lpcrect->bottom - bottom;
   }

   offset(pt);

}

void rect64::ConstraintV5(const __rect64 *  lpcrect, const class size sizeMin)
{
   if(left < lpcrect->left)
      left = lpcrect->left;
   if(right > lpcrect->right)
      right = lpcrect->right;
   if(top < lpcrect->top)
      top = lpcrect->top;
   if(bottom > lpcrect->bottom)
      bottom = lpcrect->bottom;

   if(width() < sizeMin.cx)
      right = left + sizeMin.cx;
   if(height() < sizeMin.cy)
      bottom = top + sizeMin.cy;

}

bool rect64::contains(const __rect64 *  lpcrect) const
{
   return lpcrect->left >= left
      && lpcrect->right <= right
      && lpcrect->top >= top
      && lpcrect->bottom <= bottom;
}

// Subtract minor from major and return the greatest box around.
void rect64::SubtractRectMajor(const __rect64 *  lpcrectMajor, const __rect64 *  lpcrectMinor)
{
   rect64 rectIntersect;
   rect64 rectRet(*this);
   if(!rectIntersect.intersect(lpcrectMajor, lpcrectMinor))
   {
      rectRet = *lpcrectMajor;
   }
   else
   {
      if(rectIntersect == *lpcrectMajor)
      {
         rectRet.set(0, 0, 0, 0);
      }
      else
      {
         if(rectIntersect.left == lpcrectMajor->left
            && rectIntersect.right == lpcrectMajor->right)
         {
            if(rectIntersect.top == lpcrectMajor->top)
            {
               rectRet.set(
                  lpcrectMajor->left,
                  rectIntersect.top,
                  lpcrectMajor->right,
                  lpcrectMajor->bottom);
            }
            else if(rectIntersect.bottom == lpcrectMajor->bottom)
            {
               rectRet.set(
                  lpcrectMajor->left,
                  lpcrectMajor->top,
                  lpcrectMajor->right,
                  rectIntersect.bottom);
            }
            else
            {
               rectRet = *lpcrectMajor;
            }
         }
         else if(rectIntersect.top == lpcrectMajor->top
            && rectIntersect.bottom == lpcrectMajor->bottom)
         {
            if(rectIntersect.left == lpcrectMajor->left)
            {
               rectRet.set(
                  rectIntersect.left,
                  lpcrectMajor->top,
                  lpcrectMajor->right,
                  lpcrectMajor->bottom);
            }
            else if(rectIntersect.right == lpcrectMajor->right)
            {
               rectRet.set(
                  lpcrectMajor->left,
                  lpcrectMajor->top,
                  rectIntersect.right,
                  lpcrectMajor->bottom);
            }
            else
            {
               rectRet = *lpcrectMajor;
            }
         }
         else
         {
            rectRet = *lpcrectMajor;
         }
      }
   }
   *this = rectRet;
   return;

}

void rect64::SubtractRectMinor(const __rect64 *  lpcrectMajor, const __rect64 *  lpcrectMinor)
{
   UNREFERENCED_PARAMETER(lpcrectMajor);
   UNREFERENCED_PARAMETER(lpcrectMinor);
}



























// rect
rect::rect() throw()
   { /* random filled */ }
rect::rect(int64_t l, int64_t t, int64_t r, int64_t b) throw()
   { left = (int32_t) l; top = (int32_t) t; right = (int32_t) r; bottom = (int32_t) b; }
rect::rect(const RECT& srcRect) throw()
   { ::CopyRect(this, (LPCRECT) &srcRect); }
rect::rect(const __rect64& srcRect) throw()
   { ::copy(this, &srcRect); }
rect::rect(LPCRECT lpSrcRect) throw()
   { ::CopyRect(this, lpSrcRect); }
rect::rect(POINT point, SIZE size) throw()
   { right = (left = point.x) + size.cx; bottom = (top = point.y) + size.cy; }
rect::rect(POINT topLeft, POINT bottomRight) throw()
   { left = topLeft.x; top = topLeft.y;
      right = bottomRight.x; bottom = bottomRight.y; }
int32_t rect::width() const throw()
   { return right - left; }
int32_t rect::height() const throw()
   { return bottom - top; }
class size rect::size() const throw()
   {
      class size sizeRet(right - left, bottom - top);
      return sizeRet; }
class size rect::size(LONG cx, LONG cy) throw()
{
   right = left + cx;
   bottom = top + cy;
   class size sizeRet(right - left,bottom - top);
   return sizeRet;
}
point& rect::top_left() throw()
   { return *((point*)this); }
point& rect::bottom_right() throw()
   { return *((point*)this+1); }
const point& rect::top_left() const throw()
   { return *((point*)this); }
const point& rect::bottom_right() const throw()
   { return *((point*)this+1); }
void rect::swap_left_right() throw()
   { swap_left_right(LPRECT(this)); }
void WINAPI rect::swap_left_right(LPRECT lpRect) throw()
   { LONG temp = lpRect->left; lpRect->left = lpRect->right; lpRect->right = temp; }
rect::operator LPRECT() throw()
   { return this; }
rect::operator LPCRECT() const throw()
   { return (LPCRECT) this; }
bool rect::contains(POINT point) const throw()
   { return ::PtInRect((LPCRECT) this, point) != FALSE; }
void rect::set(int32_t x1, int32_t y1, int32_t x2, int32_t y2) throw()
   { ::SetRect(this, x1, y1, x2, y2); }
void rect::set(POINT topLeft, POINT bottomRight) throw()
   { ::SetRect(this, topLeft.x, topLeft.y, bottomRight.x, bottomRight.y); }
void rect::null() throw()
   { ::SetRectEmpty(this); }
void rect::copy(LPCRECT lpSrcRect) throw()
   { ::CopyRect(this, lpSrcRect); }
bool rect::is_equal(LPCRECT lpRect) const throw()
   { return ::EqualRect((LPCRECT) this, lpRect) != FALSE; }
void rect::inflate(int32_t x, int32_t y) throw()
   { ::InflateRect(this, x, y); }
void rect::inflate(SIZE size) throw()
   { ::InflateRect(this, size.cx, size.cy); }
void rect::deflate(int32_t x, int32_t y) throw()
   { ::InflateRect(this, -x, -y); }
void rect::deflate(SIZE size) throw()
   { ::InflateRect(this, -size.cx, -size.cy); }
void rect::offset(int32_t x, int32_t y) throw()
   { ::OffsetRect(this, x, y); }
void rect::offset(POINT point) throw()
   { ::OffsetRect(this, point.x, point.y); }
void rect::offset(SIZE size) throw()
   { ::OffsetRect(this, size.cx, size.cy); }
void rect::move_to_y(int32_t y) throw()
   { bottom = height() + y; top = y; }
void rect::move_to_x(int32_t x) throw()
   { right = width() + x; left = x; }
void rect::move_to(int32_t x, int32_t y) throw()
   { move_to_x(x); move_to_y(y); }
void rect::move_to(POINT pt) throw()
   { move_to_x(pt.x); move_to_y(pt.y); }
bool rect::intersect_x(LPCRECT lpRect1,LPCRECT lpRect2) throw()
{
   return ::x_intersect_rect(this,lpRect1,lpRect2) != FALSE;
}
bool rect::intersect_y(LPCRECT lpRect1,LPCRECT lpRect2) throw()
{
   return ::y_intersect_rect(this,lpRect1,lpRect2) != FALSE;
}
bool rect::intersect(LPCRECT lpRect1,LPCRECT lpRect2) throw()
   { return ::IntersectRect(this, lpRect1, lpRect2) != FALSE;}
rect rect::intersect(LPCRECT lpcrect) const throw()
{
   ::rect rect;
   ::IntersectRect(&rect,this,lpcrect);
   return rect;
}
bool rect::null_intersect(LPCRECT lpRect1,LPCRECT lpRect2) throw()
{
   return ::null_intersect_rect(this,lpRect1,lpRect2) != FALSE;
}
bool rect::top_left_null_intersect(LPCRECT lpRect1,LPCRECT lpRect2) throw()
{
   return ::top_left_null_intersect_rect(this,lpRect1,lpRect2) != FALSE;
}
bool rect::unite(LPCRECT lpRect1,LPCRECT lpRect2) throw()
   { return ::UnionRect(this, lpRect1, lpRect2) != FALSE; }
void rect::operator=(const RECT& srcRect) throw()
   { ::CopyRect(this, (LPCRECT) &srcRect); }
bool rect::operator==(const RECT& rect) const throw()
   { return ::EqualRect((LPCRECT)this, (LPCRECT) &rect) != FALSE; }
bool rect::operator!=(const RECT& rect) const throw()
   { return ::EqualRect((LPCRECT)this, (LPCRECT) &rect) == FALSE; }
void rect::operator+=(POINT point) throw()
   { ::OffsetRect(this, point.x, point.y); }
void rect::operator+=(SIZE size) throw()
   { ::OffsetRect(this, size.cx, size.cy); }
void rect::operator+=(LPCRECT lpRect) throw()
   { inflate(lpRect); }
void rect::operator-=(POINT point) throw()
   { ::OffsetRect(this, -point.x, -point.y); }
void rect::operator-=(SIZE size) throw()
   { ::OffsetRect(this, -size.cx, -size.cy); }
void rect::operator-=(LPCRECT lpRect) throw()
   { deflate(lpRect); }
void rect::operator&=(const RECT& rect) throw()
   { ::IntersectRect(this, this, (LPCRECT)&rect); }
void rect::operator|=(const RECT& rect) throw()
   { ::UnionRect(this, this,(LPCRECT) &rect); }
rect rect::operator+(POINT pt) const throw()
   { rect rect(*this); ::OffsetRect(&rect, pt.x, pt.y); return rect; }
rect rect::operator-(POINT pt) const throw()
   { rect rect(*this); ::OffsetRect(&rect, -pt.x, -pt.y); return rect; }
rect rect::operator+(SIZE size) const throw()
   { rect rect(*this); ::OffsetRect(&rect, size.cx, size.cy); return rect; }
rect rect::operator-(SIZE size) const throw()
   { rect rect(*this); ::OffsetRect(&rect, -size.cx, -size.cy); return rect; }
rect rect::operator+(LPCRECT lpRect) const throw()
   { class rect rect((LPCRECT)this); rect.inflate(lpRect); return rect; }
rect rect::operator-(LPCRECT lpRect) const throw()
   { class rect rect((LPCRECT)this); rect.deflate(lpRect); return rect; }
rect rect::operator&(const RECT& rect2) const throw()
   { class rect rect; ::IntersectRect(&rect, (LPCRECT)this, (LPCRECT)&rect2);
      return rect; }
rect rect::operator|(const RECT& rect2) const throw()
   { class rect rect; ::UnionRect(&rect, (LPCRECT)this, (LPCRECT)&rect2);
      return rect; }
bool rect::subtract(LPCRECT lpRectSrc1, LPCRECT lpRectSrc2) throw()
   { return ::SubtractRect(this, lpRectSrc1, lpRectSrc2) != FALSE; }

void rect::normalize() throw()
   {
      int32_t nTemp;
      if (left > right)
      {
         nTemp = left;
         left = right;
         right = nTemp;
      }
      if (top > bottom)
      {
         nTemp = top;
         top = bottom;
         bottom = nTemp;
      }
   }

void rect::inflate(LPCRECT lpRect) throw()
   {
      left -= lpRect->left;      top -= lpRect->top;
      right += lpRect->right;      bottom += lpRect->bottom;
   }

void rect::inflate(int32_t l, int32_t t, int32_t r, int32_t b) throw()
   {
      left -= l;         top -= t;
      right += r;         bottom += b;
   }

void rect::deflate(LPCRECT lpRect) throw()
{
   left += lpRect->left;   top += lpRect->top;
   right -= lpRect->right;   bottom -= lpRect->bottom;
}

void rect::deflate(int32_t l, int32_t t, int32_t r, int32_t b) throw()
   {
      left += l;      top += t;
      right -= r;      bottom -= b;
   }

rect rect::MulDiv(int32_t nMultiplier, int32_t nDivisor) const throw()
   {
      return rect(
         ::MulDiv(left, nMultiplier, nDivisor),
         ::MulDiv(top, nMultiplier, nDivisor),
         ::MulDiv(right, nMultiplier, nDivisor),
         ::MulDiv(bottom, nMultiplier, nDivisor));
   }

int64_t rect::area()
   { return size().area(); }


void rect::get_bounding_rect(const POINT * lppoint, ::count count)
{

   point_array::get_bounding_rect(this, lppoint, count);

}

void rect::get_bounding_rect(const point_array & pointa)
{

   pointa.get_bounding_rect(this);

}






































































// rect64
rect64::rect64() throw()
   { /* random filled */ }
rect64::rect64(int64_t l, int64_t t, int64_t r, int64_t b) throw()
   { left = l; top = t; right = r; bottom = b; }
rect64::rect64(const __rect64 & srcRect) throw()
   { ::copy(this, &srcRect); }
rect64::rect64(const RECT & srcRect) throw()
   { ::copy(this, &srcRect); }
rect64::rect64(const __rect64 * lpSrcRect) throw()
   { ::copy(this, lpSrcRect); }
rect64::rect64(const RECT * lpSrcRect) throw()
   { ::copy(this, lpSrcRect); }
rect64::rect64(__point64 point64, __size64 size64) throw()
   { right = (left = point64.x) + size64.cx; bottom = (top = point64.y) + size64.cy; }
rect64::rect64(__point64 topLeft, __point64 bottomRight) throw()
   { left = topLeft.x; top = topLeft.y;
      right = bottomRight.x; bottom = bottomRight.y; }
int64_t rect64::width() const throw()
   { return right - left; }
int64_t rect64::height() const throw()
   { return bottom - top; }
size64 rect64::size() const throw()
   { return size64(right - left, bottom - top); }
point64& rect64::top_left() throw()
   { return *((point64*)this); }
point64& rect64::bottom_right() throw()
   { return *((point64*)this+1); }
const point64& rect64::top_left() const throw()
   { return *((point64*)this); }
const point64& rect64::bottom_right() const throw()
   { return *((point64*)this+1); }
void rect64::swap_left_right() throw()
   { swap_left_right((__rect64 *)(this)); }
void WINAPI rect64::swap_left_right(__rect64 * lpRect) throw()
   { int64_t temp = lpRect->left; lpRect->left = lpRect->right; lpRect->right = temp; }
rect64::operator __rect64 *() throw()
   { return this; }
rect64::operator const __rect64 *() const throw()
   { return this; }
rect64::operator rect() const
{
   return rect(*this);
}
bool rect64::contains(__point64 point) const throw()
   { return ::contains(this, point); }
void rect64::set(int64_t x1, int64_t y1, int64_t x2, int64_t y2) throw()
   { ::set_rect(this, x1, y1, x2, y2); }
void rect64::set(__point64 topLeft, __point64 bottomRight) throw()
   { ::set_rect(this, topLeft.x, topLeft.y, bottomRight.x, bottomRight.y); }
void rect64::null() throw()
   { ::null(this); }
void rect64::copy(const __rect64 * lpSrcRect) throw()
   { ::copy(this, lpSrcRect); }
bool rect64::is_equal(const __rect64 * lpRect) const throw()
   { return ::is_equal(this, lpRect); }
void rect64::inflate(int64_t x, int64_t y) throw()
   { ::inflate(this, x, y); }
void rect64::inflate(__size64 size64) throw()
   { ::inflate(this, size64.cx, size64.cy); }
void rect64::deflate(int64_t x, int64_t y) throw()
   { ::inflate(this, -x, -y); }
void rect64::deflate(__size64 size64) throw()
   { ::inflate(this, -size64.cx, -size64.cy); }
void rect64::offset(int64_t x, int64_t y) throw()
   { ::offset(this, x, y); }
void rect64::offset(__point64 point64) throw()
   { ::offset(this, point64.x, point64.y); }
void rect64::offset(__size64 size64) throw()
   { ::offset(this, size64.cx, size64.cy); }
void rect64::move_to_y(int64_t y) throw()
   { bottom = height() + y; top = y; }
void rect64::move_to_x(int64_t x) throw()
   { right = width() + x; left = x; }
void rect64::move_to(int64_t x, int64_t y) throw()
   { move_to_x(x); move_to_y(y); }
void rect64::move_to(__point64 pt) throw()
   { move_to_x(pt.x); move_to_y(pt.y); }
bool rect64::intersect(const __rect64 * lpRect1, const __rect64 * lpRect2) throw()
   { return ::intersect(this, lpRect1, lpRect2);}
bool rect64::unite(const __rect64 * lpRect1, const __rect64 * lpRect2) throw()
   { return ::unite(this, lpRect1, lpRect2); }
void rect64::operator=(const __rect64& srcRect) throw()
   { ::copy(this, &srcRect); }
bool rect64::operator==(const __rect64& rect64) const throw()
   { return ::is_equal(this, &rect64); }
bool rect64::operator!=(const __rect64& rect64) const throw()
   { return !::is_equal(this, &rect64); }
void rect64::operator+=(__point64 point64) throw()
   { ::offset(this, point64.x, point64.y); }
void rect64::operator+=(__size64 size64) throw()
   { ::offset(this, size64.cx, size64.cy); }
void rect64::operator+=(const __rect64 * lpRect) throw()
   { inflate(lpRect); }
void rect64::operator-=(__point64 point64) throw()
   { ::offset(this, -point64.x, -point64.y); }
void rect64::operator-=(__size64 size64) throw()
   { ::offset(this, -size64.cx, -size64.cy); }
void rect64::operator-=(const __rect64 * lpRect) throw()
   { deflate(lpRect); }
void rect64::operator&=(const __rect64& rect64) throw()
   { ::intersect(this, this, &rect64); }
void rect64::operator|=(const __rect64& rect64) throw()
   { ::unite(this, this, &rect64); }
rect64 rect64::operator+(__point64 pt) const throw()
   { rect64 rect64(*this); ::offset(&rect64, pt.x, pt.y); return rect64; }
rect64 rect64::operator-(__point64 pt) const throw()
   { rect64 rect64(*this); ::offset(&rect64, -pt.x, -pt.y); return rect64; }
rect64 rect64::operator+(__size64 size64) const throw()
   { rect64 rect64(*this); ::offset(&rect64, size64.cx, size64.cy); return rect64; }
rect64 rect64::operator-(__size64 size64) const throw()
   { rect64 rect64(*this); ::offset(&rect64, -size64.cx, -size64.cy); return rect64; }
rect64 rect64::operator+(const __rect64 * lpRect) const throw()
   { rect64 rect64(this); rect64.inflate(lpRect); return rect64; }
rect64 rect64::operator-(const __rect64 * lpRect) const throw()
   { rect64 rect64(this); rect64.deflate(lpRect); return rect64; }
rect64 rect64::operator&(const __rect64& rect2) const throw()
   { rect64 rect64; ::intersect(&rect64, this, &rect2);
      return rect64; }
rect64 rect64::operator|(const __rect64& rect2) const throw()
   { rect64 rect64; ::unite(&rect64, this, &rect2);
      return rect64; }
//bool rect64::subtract(const __rect64 * lpRectSrc1, const __rect64 * lpRectSrc2) throw()
//   { return ::subtract(this, lpRectSrc1, lpRectSrc2); }

void rect64::normalize() throw()
   {
      int64_t nTemp;
      if (left > right)
      {
         nTemp = left;
         left = right;
         right = nTemp;
      }
      if (top > bottom)
      {
         nTemp = top;
         top = bottom;
         bottom = nTemp;
      }
   }

void rect64::inflate(const __rect64 * lpRect) throw()
   {
      left -= lpRect->left;      top -= lpRect->top;
      right += lpRect->right;      bottom += lpRect->bottom;
   }

void rect64::inflate(int64_t l, int64_t t, int64_t r, int64_t b) throw()
   {
      left -= l;         top -= t;
      right += r;         bottom += b;
   }

void rect64::deflate(const __rect64 * lpRect) throw()
   {
      left += lpRect->left;   top += lpRect->top;
      right -= lpRect->right;   bottom -= lpRect->bottom;
   }

void rect64::deflate(int64_t l, int64_t t, int64_t r, int64_t b) throw()
   {
      left += l;      top += t;
      right -= r;      bottom -= b;
   }

rect64 rect64::MulDiv(int64_t nMultiplier, int64_t nDivisor) const throw()
   {
      return rect64(
         ::MulDiv(left, nMultiplier, nDivisor),
         ::MulDiv(top, nMultiplier, nDivisor),
         ::MulDiv(right, nMultiplier, nDivisor),
         ::MulDiv(bottom, nMultiplier, nDivisor));
   }

int64_t rect64::area()
   { return size().area(); }

















































// rectd
rectd::rectd() throw()
   { /* random filled */ }
rectd::rectd(double l, double t, double r, double b) throw()
   { left = (double) l; top = (double) t; right = (double) r; bottom = (double) b; }
rectd::rectd(const RECTD& srcRect) throw()
   { ::copy(this, &srcRect); }
rectd::rectd(const __rect64& srcRect) throw()
   { ::copy(this, &srcRect); }
rectd::rectd(LPCRECTD lpSrcRect) throw()
   { ::copy(this, lpSrcRect); }
rectd::rectd(POINTD point, SIZED size) throw()
   { right = (left = point.x) + size.cx; bottom = (top = point.y) + size.cy; }
rectd::rectd(POINTD topLeft, POINTD bottomRight) throw()
   { left = topLeft.x; top = topLeft.y;
      right = bottomRight.x; bottom = bottomRight.y; }
double rectd::width() const throw()
   { return right - left; }
double rectd::height() const throw()
   { return bottom - top; }
class sized rectd::size() const throw()
{
   class sized sizeRet(right - left, bottom - top);
   return sizeRet;
}

pointd & rectd::top_left() throw()
   { return *((pointd*)this); }
pointd & rectd::bottom_right() throw()
   { return *((pointd*)this+1); }
const pointd & rectd::top_left() const throw()
   { return *((pointd*)this); }
const pointd & rectd::bottom_right() const throw()
   { return *((pointd*)this+1); }
void rectd::swap_left_right() throw()
   { swap_left_right(LPRECTD(this)); }
void WINAPI rectd::swap_left_right(LPRECTD lpRect) throw()
   { double temp = lpRect->left; lpRect->left = lpRect->right; lpRect->right = temp; }
rectd::operator LPRECTD() throw()
   { return this; }
rectd::operator LPCRECTD() const throw()
   { return (LPCRECTD) this; }
bool rectd::contains(POINTD point) const throw()
   { return ::contains((LPCRECTD) this, point) != FALSE; }
void rectd::set(double x1, double y1, double x2, double y2) throw()
   { ::set_rect(this, x1, y1, x2, y2); }
void rectd::set(POINTD topLeft, POINTD bottomRight) throw()
   { ::set_rect(this, topLeft.x, topLeft.y, bottomRight.x, bottomRight.y); }
void rectd::null() throw()
   { ::null(this); }
void rectd::copy(LPCRECTD lpSrcRect) throw()
   { ::copy(this, lpSrcRect); }
bool rectd::is_equal(LPCRECTD lpRect) const throw()
   { return ::is_equal((LPCRECTD) this, lpRect) != FALSE; }
void rectd::inflate(double x, double y) throw()
   { ::inflate(this, x, y); }
void rectd::inflate(SIZED size) throw()
   { ::inflate(this, size.cx, size.cy); }
void rectd::deflate(double x, double y) throw()
   { ::inflate(this, -x, -y); }
void rectd::deflate(SIZED size) throw()
   { ::inflate(this, -size.cx, -size.cy); }
void rectd::offset(double x, double y) throw()
   { ::offset(this, x, y); }
void rectd::offset(POINTD point) throw()
   { ::offset(this, point.x, point.y); }
void rectd::offset(SIZED size) throw()
   { ::offset(this, size.cx, size.cy); }
void rectd::move_to_y(double y) throw()
   { bottom = height() + y; top = y; }
void rectd::move_to_x(double x) throw()
   { right = width() + x; left = x; }
void rectd::move_to(double x, double y) throw()
   { move_to_x(x); move_to_y(y); }
void rectd::move_to(POINTD pt) throw()
   { move_to_x(pt.x); move_to_y(pt.y); }
bool rectd::intersect(LPCRECTD lpRect1, LPCRECTD lpRect2) throw()
{ return ::intersect(this, lpRect1, lpRect2) != FALSE;}
bool rectd::unite(LPCRECTD lpRect1, LPCRECTD lpRect2) throw()
   { return ::unite(this, lpRect1, lpRect2) != FALSE; }
void rectd::operator=(const RECTD& srcRect) throw()
   { ::copy(this, (LPCRECTD) &srcRect); }
bool rectd::operator==(const RECTD& rectd) const throw()
   { return ::is_equal((LPCRECTD)this, (LPCRECTD) &rectd) != FALSE; }
bool rectd::operator!=(const RECTD& rectd) const throw()
   { return !::is_equal((LPCRECTD)this, (LPCRECTD) &rectd) != FALSE; }
void rectd::operator+=(POINTD point) throw()
   { ::offset(this, point.x, point.y); }
void rectd::operator+=(SIZED size) throw()
   { ::offset(this, size.cx, size.cy); }
void rectd::operator+=(LPCRECTD lpRect) throw()
   { inflate(lpRect); }
void rectd::operator-=(POINTD point) throw()
   { ::offset(this, -point.x, -point.y); }
void rectd::operator-=(SIZED size) throw()
   { ::offset(this, -size.cx, -size.cy); }
void rectd::operator-=(LPCRECTD lpRect) throw()
   { deflate(lpRect); }
void rectd::operator&=(const RECTD& rectd) throw()
   { ::intersect(this, this, (LPCRECTD)&rectd); }
void rectd::operator|=(const RECTD& rectd) throw()
   { ::unite(this, this,(LPCRECTD) &rectd); }
rectd rectd::operator+(POINTD pt) const throw()
   { rectd rectd(*this); ::offset(&rectd, pt.x, pt.y); return rectd; }
rectd rectd::operator-(POINTD pt) const throw()
   { rectd rectd(*this); ::offset(&rectd, -pt.x, -pt.y); return rectd; }
rectd rectd::operator+(SIZED size) const throw()
   { rectd rectd(*this); ::offset(&rectd, size.cx, size.cy); return rectd; }
rectd rectd::operator-(SIZED size) const throw()
   { rectd rectd(*this); ::offset(&rectd, -size.cx, -size.cy); return rectd; }
rectd rectd::operator+(LPCRECTD lpRect) const throw()
   { class rectd rectd((LPCRECTD)this); rectd.inflate(lpRect); return rectd; }
rectd rectd::operator-(LPCRECTD lpRect) const throw()
   { class rectd rectd((LPCRECTD)this); rectd.deflate(lpRect); return rectd; }
rectd rectd::operator&(const RECTD& rect2) const throw()
{ class rectd rectd; ::intersect(&rectd, (LPCRECTD)this, (LPCRECTD)&rect2);
      return rectd; }
rectd rectd::operator|(const RECTD& rect2) const throw()
   { class rectd rectd; ::unite(&rectd, (LPCRECTD)this, (LPCRECTD)&rect2);
      return rectd; }
//bool rectd::subtract(LPCRECTD lpRectSrc1, LPCRECTD lpRectSrc2) throw()
  // { return ::subtract(this, lpRectSrc1, lpRectSrc2) != FALSE; }

void rectd::normalize() throw()
   {
      double nTemp;
      if (left > right)
      {
         nTemp = left;
         left = right;
         right = nTemp;
      }
      if (top > bottom)
      {
         nTemp = top;
         top = bottom;
         bottom = nTemp;
      }
   }

void rectd::inflate(LPCRECTD lpRect) throw()
   {
      left -= lpRect->left;      top -= lpRect->top;
      right += lpRect->right;      bottom += lpRect->bottom;
   }

void rectd::inflate(double l, double t, double r, double b) throw()
   {
      left -= l;         top -= t;
      right += r;         bottom += b;
   }

void rectd::deflate(LPCRECTD lpRect) throw()
{
   left += lpRect->left;   top += lpRect->top;
   right -= lpRect->right;   bottom -= lpRect->bottom;
}

void rectd::deflate(double l, double t, double r, double b) throw()
   {
      left += l;      top += t;
      right -= r;      bottom -= b;
   }

rectd rectd::MulDiv(double nMultiplier, double nDivisor) const throw()
   {
      return rectd(  left     *  nMultiplier / nDivisor,
                     top      *  nMultiplier / nDivisor,
                     right    *  nMultiplier / nDivisor,
                     bottom   *  nMultiplier / nDivisor);
   }

double rectd::area()
   { return size().area(); }


void rectd::get_bounding_rect(const POINTD * lppoint, ::count count)
{

   pointd_array::get_bounding_rect(this, lppoint, count);

}

void rectd::get_bounding_rect(const pointd_array & pointa)
{

   pointa.get_bounding_rect(this);

}





void rectd::CenterOf(LPCRECTD lpcrect,SIZED size)
{
   double cx = size.cx;
   double cy = size.cy;

   double dx = ::width(lpcrect);
   double dy = ::height(lpcrect);

   left     = lpcrect->left + (dx - cx) / 2;
   top      = lpcrect->top + (dy - cy) / 2;
   right    = left + cx;
   bottom   = top + cy;

}

void rectd::CenterOf(LPCRECTD lpcrect)
{

   CenterOf(lpcrect,size());

}
