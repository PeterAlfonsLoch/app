#include "framework.h"
#include <sys/times.h>

DWORD get_tick_count()
{
   timeval tv;
   gettimeofday(&tv, NULL);
   return (DWORD) ((((int64_t) tv.tv_sec * 1000) + ((tv.tv_usec / 1000) % 1000)) % ((int64_t) 1 << (sizeof(DWORD) * 8)));
}


/*CLASS_DECL_BASE bool CopyRect(LPRECT prectDest, LPCRECT prectSrc)
{
      prectDest->left = prectSrc->left;
      prectDest->top = prectSrc->top;
      prectDest->right = prectSrc->right;
      prectDest->bottom = prectSrc->bottom;
   return true;
}

CLASS_DECL_BASE bool PtInRect(LPCRECT prect, POINT point)
{
   return point.x >= prect->left && point.x <= prect->right
   && point.y >= prect->top && point.y <= prect->bottom;

}

CLASS_DECL_BASE bool SetRect(LPRECT prect, long x1, long y1, long x2, long y2)
{

   prect->left = x1;
   prect->top = y1;

   prect->right = x2;
   prect->bottom = y2;
   return true;
}


CLASS_DECL_BASE bool SetRectEmpty(LPRECT prect)
{

   SetRect(prect, 0, 0, 0, 0);
   return true;
}


CLASS_DECL_BASE bool EqualRect(LPCRECT prect1, LPCRECT prect2)
{
      return prect1->left == prect2->left
         &&  prect1->top == prect2->top
         &&  prect1->right == prect2->right
         &&  prect1->bottom == prect2->bottom;
}


CLASS_DECL_BASE bool InflateRect(LPRECT prect, int32_t x, int32_t y)
{
      prect->left -= x;
      prect->top -= y;
      prect->right += x;
      prect->bottom += y;
      return true;
}

CLASS_DECL_BASE bool OffsetRect(LPRECT prect, int32_t x, int32_t y)
{
      prect->left += x;
      prect->top += y;
      prect->right += x;
      prect->bottom += y;
      return true;
}

CLASS_DECL_BASE bool x_intersect_rect(LPRECT prect, LPCRECT prect1, LPCRECT prect2)
{
   prect->left = MAX(prect1->left, prect2->left);
   prect->right = MIN(prect1->right, prect2->right);
   return prect->right >= prect->left;
}

CLASS_DECL_BASE bool y_intersect_rect(LPRECT prect, LPCRECT prect1, LPCRECT prect2)
{
   prect->top = MAX(prect1->top, prect2->top);
   prect->right = MIN(prect1->bottom, prect2->bottom);
   return prect->bottom >= prect->top;
}

CLASS_DECL_BASE bool IntersectRect(LPRECT prect, LPCRECT prect1, LPCRECT prect2)
{
   bool bXIntersects = x_intersect_rect(prect, prect1, prect2);
   bool bYIntersects = y_intersect_rect(prect, prect1, prect2);
   return bXIntersects && bYIntersects;
}


CLASS_DECL_BASE bool UnionRect(LPRECT prect, LPCRECT prect1, LPCRECT prect2)
{
   prect->left = MIN(prect1->left, prect2->left);
   prect->top = MIN(prect1->top, prect2->top);
   prect->right = MAX(prect1->right, prect2->right);
   prect->bottom = MAX(prect1->bottom, prect2->bottom);
   return ((prect->right - prect->left) > 0) && ((prect->bottom - prect->top) > 0);
}


CLASS_DECL_BASE bool SubtractRect(LPRECT prect, LPCRECT prect1, LPCRECT prect2)
{
   RECT rect;
   bool bXIntersects = x_intersect_rect(&rect, prect1, prect2);
   bool bYIntersects = y_intersect_rect(&rect, prect1, prect2);
   if(bXIntersects)
   {
      prect->left    = rect.left;
      prect->right   = rect.right;
   }
   if(bYIntersects)
   {
      prect->top    = rect.top;
      prect->bottom   = rect.bottom;
   }
   return bXIntersects || bYIntersects;
}*/




CLASS_DECL_CORE errno_t fopen_s(FILE ** pFile, const char * pFileName, const char * mode)
{
   if(pFile == NULL)
   {
      return EINVAL;
   }

   *pFile = fopen(pFileName, mode);

   if(*pFile == NULL)
   {
      return errno;
   }

   return 0;

}
