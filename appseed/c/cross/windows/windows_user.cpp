//
//  windows_user.cpp
//  c
//
//  Created by Carlos Gustavo Cecyn Lundgren on 12/8/12.
//
//
#include "framework.h"

CLASS_DECL_c COLORREF GetSysColor(DWORD dw)
{

   switch(dw)
   {
      case COLOR_HIGHLIGHT:
         return ARGB(255, 200, 200, 196);
      case COLOR_BTNSHADOW:
         return ARGB(84, 192, 192, 187);
      case COLOR_BTNTEXT:
         return ARGB(255, 0, 0, 0);
      default:
         return ARGB(255, 0, 0, 0);
   };

}



CLASS_DECL_c int WINAPI GetSystemMetrics(int nIndex)
{

   switch(nIndex)
   {
   case SM_CXHSCROLL:
      return 16;
   case SM_CYHSCROLL:
      return 16;
   }

   return 0;

}



CLASS_DECL_c bool CopyRect(LPRECT prectDest, LPCRECT pcrectSrc)
{

   prectDest->left      = pcrectSrc->left;
   prectDest->top       = pcrectSrc->top;
   prectDest->right     = pcrectSrc->right;
   prectDest->bottom    = pcrectSrc->bottom;

   return true;

}

CLASS_DECL_c bool PtInRect(LPCRECT prect, POINT point)
{
   return point.x >= prect->left && point.x <= prect->right
   && point.y >= prect->top && point.y <= prect->bottom;

}

CLASS_DECL_c bool SetRect(LPRECT prect, long x1, long y1, long x2, long y2)
{

   prect->left = x1;
   prect->top = y1;

   prect->right = x2;
   prect->bottom = y2;
   return true;
}


CLASS_DECL_c bool SetRectEmpty(LPRECT prect)
{

   SetRect(prect, 0, 0, 0, 0);
   return true;
}


CLASS_DECL_c bool EqualRect(LPCRECT prect1, LPCRECT prect2)
{
      return prect1->left == prect2->left
         &&  prect1->top == prect2->top
         &&  prect1->right == prect2->right
         &&  prect1->bottom == prect2->bottom;
}


CLASS_DECL_c bool InflateRect(LPRECT prect, int x, int y)
{
      prect->left -= x;
      prect->top -= y;
      prect->right += x;
      prect->bottom += y;
      return true;
}

CLASS_DECL_c bool OffsetRect(LPRECT prect, int x, int y)
{
      prect->left += x;
      prect->top += y;
      prect->right += x;
      prect->bottom += y;
      return true;
}

CLASS_DECL_c bool x_intersect_rect(LPRECT prect, LPCRECT prect1, LPCRECT prect2)
{
   prect->left = max(prect1->left, prect2->left);
   prect->right = min(prect1->right, prect2->right);
   return prect->right >= prect->left;
}

CLASS_DECL_c bool y_intersect_rect(LPRECT prect, LPCRECT prect1, LPCRECT prect2)
{
   prect->top = max(prect1->top, prect2->top);
   prect->right = min(prect1->bottom, prect2->bottom);
   return prect->bottom >= prect->top;
}

CLASS_DECL_c bool IntersectRect(LPRECT prect, LPCRECT prect1, LPCRECT prect2)
{
   bool bXIntersects = x_intersect_rect(prect, prect1, prect2);
   bool bYIntersects = y_intersect_rect(prect, prect1, prect2);
   return bXIntersects && bYIntersects;
}


CLASS_DECL_c bool UnionRect(LPRECT prect, LPCRECT prect1, LPCRECT prect2)
{
   prect->left = min(prect1->left, prect2->left);
   prect->top = min(prect1->top, prect2->top);
   prect->right = max(prect1->right, prect2->right);
   prect->bottom = max(prect1->bottom, prect2->bottom);
   return ((prect->right - prect->left) > 0) && ((prect->bottom - prect->top) > 0);
}


CLASS_DECL_c bool SubtractRect(LPRECT prect, LPCRECT prect1, LPCRECT prect2)
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
}


#ifndef METROWIN

int
WINAPI
MultiByteToWideChar(
    UINT     CodePage,
    DWORD    dwFlags,
    LPCSTR   lpMultiByteStr,
    int      cbMultiByte,
    LPWSTR  lpWideCharStr,
    int      cchWideChar)
{

   vsstring str(lpMultiByteStr, cbMultiByte);

   wstring wstr(str);

   if(cchWideChar == 0)
      return wstr.get_length();

   int iLen = min(cchWideChar, wstr.get_length());

   if(lpWideCharStr != NULL)
   {

      wcsncpy(lpWideCharStr, wstr, iLen);

      if(cchWideChar > 0)
      {

         lpWideCharStr[iLen] = L'\0';

      }

   }

   return iLen;

}

int
WINAPI
WideCharToMultiByte(
    UINT     CodePage,
    DWORD    dwFlags,
    LPCWSTR  lpWideCharStr,
    int      cchWideChar,
    LPSTR   lpMultiByteStr,
    int      cbMultiByte,
    LPCSTR   lpDefaultChar,
    LPBOOL  lpUsedDefaultChar)
{

   wstring wstr(lpWideCharStr, cchWideChar);

   vsstring str(wstr);

   if(cbMultiByte == 0)
   {
      return str.get_length();
   }

   int iLen = min(cbMultiByte, str.get_length());

   if(lpMultiByteStr != NULL)
   {

      strncpy(lpMultiByteStr, str, iLen);

      if(cbMultiByte > 0)
      {

         lpMultiByteStr[iLen] = '\0';

      }

   }

   return iLen;

}

CLASS_DECL_c vsstring get_system_error_message(DWORD dwError)
{

   vsstring str;

   return str;

}


#endif 

