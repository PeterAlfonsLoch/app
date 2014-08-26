#pragma once


inline CLASS_DECL_AURA LONG width(LPCRECT lpcrect)
{
   return lpcrect->right - lpcrect->left;
}

inline CLASS_DECL_AURA LONG height(LPCRECT lpcrect)
{
   return lpcrect->bottom - lpcrect->top;
}

inline CLASS_DECL_AURA LONG width(const RECT & rect)
{
   return width(&rect);
}

inline CLASS_DECL_AURA LONG height(const RECT & rect)
{
   return height(&rect);
}

inline CLASS_DECL_AURA LONG area(LPCRECT lpcrect)
{
   return width(lpcrect) * height(lpcrect);
}

inline CLASS_DECL_AURA LONG area(const RECT & rect)
{
   return width(rect) * height(rect);
}


inline CLASS_DECL_AURA RECT & inflate_rect(RECT & rect, LONG dleft, LONG dtop, LONG dright, LONG dbottom)
{
   rect.left -= dleft;
   rect.right += dtop;
   rect.top -= dright;
   rect.top += dbottom;
   return rect;
}

inline CLASS_DECL_AURA LPRECT inflate_rect(LPRECT lprect, LONG dleft, LONG dtop, LONG dright, LONG dbottom)
{
   return &inflate_rect(*lprect, dleft, dtop, dright, dbottom);
}

inline CLASS_DECL_AURA RECT & deflate_rect(RECT & rect, LONG dleft, LONG dtop, LONG dright, LONG dbottom)
{
   rect.left += dleft;
   rect.right -= dtop;
   rect.top += dright;
   rect.top -= dbottom;
   return rect;
}

inline CLASS_DECL_AURA LPRECT deflate_rect(LPRECT lprect, LONG dleft, LONG dtop, LONG dright, LONG dbottom)
{
   return &deflate_rect(*lprect, dleft, dtop, dright, dbottom);
}

inline CLASS_DECL_AURA RECT & inflate_rect(RECT & rect, LONG dx, LONG dy)
{
   return inflate_rect(rect, dx, dy, dx, dy);
}

inline CLASS_DECL_AURA LPRECT inflate_rect(LPRECT lprect, LONG dx, LONG dy)
{
   return &inflate_rect(*lprect, dx, dy);
}

inline CLASS_DECL_AURA RECT & deflate_rect(RECT & rect, LONG dx, LONG dy)
{
   return deflate_rect(rect, dx, dy, dx, dy);
}

inline CLASS_DECL_AURA LPRECT deflate_rect(LPRECT lprect, LONG dx, LONG dy)
{
   return &deflate_rect(*lprect, dx, dy);
}

inline CLASS_DECL_AURA RECT & inflate_rect(RECT & rect, LONG d)
{
   return inflate_rect(rect, d, d);
}

inline CLASS_DECL_AURA LPRECT inflate_rect(LPRECT lprect, LONG d)
{
   return &inflate_rect(*lprect, d);
}

inline CLASS_DECL_AURA RECT & deflate_rect(RECT & rect, LONG d)
{
   return deflate_rect(rect, d, d);
}

inline CLASS_DECL_AURA LPRECT deflate_rect(LPRECT lprect, LONG d)
{
   return &deflate_rect(*lprect, d);
}

inline CLASS_DECL_AURA RECT & rect_by_dimension(RECT & rect, LONG x, LONG y, LONG cx, LONG cy)
{
   rect.left = x;
   rect.top = y;
   rect.right = x + cx;
   rect.bottom = y + cy;
   return rect;
}

inline CLASS_DECL_AURA RECT & rect_dim(RECT & rect, LONG x, LONG y, LONG cx, LONG cy)
{
   return rect_by_dimension(rect, x, y, cx, cy);
}

inline CLASS_DECL_AURA LPRECT rect_by_dimension(LPRECT lprect, LONG x, LONG y, LONG cx, LONG cy)
{
   return &rect_by_dimension(*lprect, x, y, cx, cy);
}

inline CLASS_DECL_AURA LPRECT rect_dim(LPRECT lprect, LONG x, LONG y, LONG cx, LONG cy)
{
   return rect_by_dimension(lprect, x, y, cx, cy);
}

inline CLASS_DECL_AURA ::rect rect_by_dimension(LONG x, LONG y, LONG cx, LONG cy)
{
   ::rect r;
   return rect_by_dimension(r, x, y, cx, cy);
}

inline CLASS_DECL_AURA ::rect rect_dim(LONG x, LONG y, LONG cx, LONG cy)
{
   return rect_by_dimension(x, y, cx, cy);
}


inline CLASS_DECL_AURA POINT & point_by_coordinate(POINT & p, LONG x, LONG y)
{
   p.x = x;
   p.y = y;
   return p;
}

inline CLASS_DECL_AURA POINT & point_coord(POINT & p, LONG x, LONG y)
{
   return point_by_coordinate(p, x, y);
}


inline CLASS_DECL_AURA LPPOINT point_by_coordinate(LPPOINT lppt, LONG x, LONG y)
{
   return &point_by_coordinate(*lppt, x, y);
}

inline CLASS_DECL_AURA LPPOINT point_coord(LPPOINT lppt, LONG x, LONG y)
{
   return point_by_coordinate(lppt, x, y);
}

inline CLASS_DECL_AURA POINT point_by_coordinate(LONG x, LONG y)
{
   POINT p;
   return point_by_coordinate(p, x, y);
}

inline CLASS_DECL_AURA POINT point_coord(LONG x, LONG y)
{
   return point_by_coordinate(x, y);
}

inline CLASS_DECL_AURA POINT & offset(POINT & pt, LONG x, LONG y)
{
   pt.x += x;
   pt.y += y;
   return pt;
}

CLASS_DECL_AURA bool polygon_contains(LPPOINT lppt, LPPOINT lpptPolygon, int iCount);

CLASS_DECL_AURA bool polygon_contains(LPPOINTD lppt,LPPOINTD lpptPolygon,int iCount);


inline CLASS_DECL_AURA POINT & top_left(LPRECT lpcrect)
{
   return *(POINT *) lpcrect;
}

inline CLASS_DECL_AURA const POINT & top_left(LPCRECT lpcrect)
{
   return *(const POINT *)lpcrect;
}

inline CLASS_DECL_AURA const POINT & top_left(const RECT & rect)
{
   return ::top_left(&rect);
}




CLASS_DECL_AURA bool deflate(LPRECT prect,LPCRECT lpcrect);



#ifdef APPLEOS




void copy(CGRect & rectDst, const RECT & rectSrc);
void copy(LPRECT lprectDst, const CGRect & rectSrc);

#endif


CLASS_DECL_AURA int_bool IsRectEmpty(const RECT & rect);



