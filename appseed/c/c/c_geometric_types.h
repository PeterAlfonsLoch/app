#pragma once


inline CLASS_DECL_c long width(LPCRECT lpcrect)
{
   return lpcrect->right - lpcrect->left;
}

inline CLASS_DECL_c long height(LPCRECT lpcrect)
{
   return lpcrect->bottom - lpcrect->top;
}

inline CLASS_DECL_c long width(const RECT & rect)
{
   return width(&rect);
}

inline CLASS_DECL_c long height(const RECT & rect)
{
   return height(&rect);
}

inline CLASS_DECL_c bool inflate_rect(RECT & rect, int dleft, int dtop, int dright, int dbottom)
{
   rect.left   -= dleft;
   rect.right  += dtop;
   rect.top    -= dright;
   rect.top    += dbottom;
   return true;
}

inline CLASS_DECL_c bool inflate_rect(LPRECT lprect, int dleft, int dtop, int dright, int dbottom)
{
   return inflate_rect(*lprect, dleft, dtop, dright, dbottom);
}

inline CLASS_DECL_c bool deflate_rect(RECT & rect, int dleft, int dtop, int dright, int dbottom)
{
   rect.left   += dleft;
   rect.right  -= dtop;
   rect.top    += dright;
   rect.top    -= dbottom;
   return true;
}

inline CLASS_DECL_c bool deflate_rect(LPRECT lprect, int dleft, int dtop, int dright, int dbottom)
{
   return deflate_rect(*lprect, dleft, dtop, dright, dbottom);
}

inline CLASS_DECL_c bool inflate_rect(RECT & rect, int dx, int dy)
{
   return inflate_rect(rect, dx, dy, dx, dy);
}

inline CLASS_DECL_c bool inflate_rect(LPRECT lprect, int dx, int dy)
{
   return inflate_rect(*lprect, dx, dy);
}

inline CLASS_DECL_c bool deflate_rect(RECT & rect, int dx, int dy)
{
   return deflate_rect(rect, dx, dy, dx, dy);
}

inline CLASS_DECL_c bool deflate_rect(LPRECT lprect, int dx, int dy)
{
   return deflate_rect(*lprect, dx, dy);
}

inline CLASS_DECL_c bool inflate_rect(RECT & rect, int d)
{
   return inflate_rect(rect, d, d);
}

inline CLASS_DECL_c bool inflate_rect(LPRECT lprect, int d)
{
   return inflate_rect(*lprect, d);
}

inline CLASS_DECL_c bool deflate_rect(RECT & rect, int d)
{
   return deflate_rect(rect, d, d);
}

inline CLASS_DECL_c bool deflate_rect(LPRECT lprect, int d)
{
   return deflate_rect(*lprect, d);
}

inline CLASS_DECL_c bool rect_by_dimension(RECT & rect, int x, int y, int cx, int cy)
{
   rect.left      = x;
   rect.top       = y;
   rect.right     = x + cx;
   rect.bottom    = y + cy;
   return true;
}

inline CLASS_DECL_c bool rect_dim(RECT & rect, int x, int y, int cx, int cy)
{
   return rect_by_dimension(rect, x, y, cx, cy);
}

inline CLASS_DECL_c bool rect_by_dimension(LPRECT lprect, int x, int y, int cx, int cy)
{
   return rect_by_dimension(*lprect, x, y, cx, cy);
}

inline CLASS_DECL_c bool rect_dim(LPRECT lprect, int x, int y, int cx, int cy)
{
   return rect_by_dimension(lprect, x, y, cx, cy);
}

inline CLASS_DECL_c RECT rect_by_dimension(int x, int y, int cx, int cy)
{
   RECT rect;
   rect_by_dimension(rect, x, cy, cx, cy);
   return rect;
}

inline CLASS_DECL_c RECT rect_dim(int x, int y, int cx, int cy)
{
   return rect_by_dimension(x, y, cx, cy);
}





