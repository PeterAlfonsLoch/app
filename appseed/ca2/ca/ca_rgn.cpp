#include "StdAfx.h"

namespace ca
{

   BOOL rgn::CreateRectRgn(int x1, int y1, int x2, int y2)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      throw interface_only_exception();   
   }

   BOOL rgn::CreateRectRgnIndirect(LPCRECT lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception();   
   }

   BOOL rgn::CreateEllipticRgn(int x1, int y1, int x2, int y2)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      throw interface_only_exception();   
   }

   BOOL rgn::CreateEllipticRgnIndirect(LPCRECT lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception();   
   }

   BOOL rgn::CreatePolygonRgn(LPPOINT lpPoints, int nCount, int nMode)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(nMode);
      throw interface_only_exception();   
   }

   BOOL rgn::CreatePolyPolygonRgn(LPPOINT lpPoints, LPINT lpPolyCounts, int nCount, int nPolyFillMode)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(lpPolyCounts);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(nPolyFillMode);
      throw interface_only_exception();   
   }

   BOOL rgn::CreateRoundRectRgn(int x1, int y1, int x2, int y2, int x3, int y3)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      UNREFERENCED_PARAMETER(x3);
      UNREFERENCED_PARAMETER(y3);
      throw interface_only_exception();   
   }

   BOOL rgn::CreateFromPath(::ca::graphics * pgraphics)
   {
      UNREFERENCED_PARAMETER(pgraphics);
      throw interface_only_exception();   
   }

   BOOL rgn::CreateFromData(const XFORM* lpXForm, int nCount, const RGNDATA* pRgnData)
   {
      UNREFERENCED_PARAMETER(lpXForm);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(pRgnData);
      throw interface_only_exception();   
   }

   int rgn::GetRegionData(LPRGNDATA lpRgnData, int nDataSize) const
   {
      UNREFERENCED_PARAMETER(lpRgnData);
      UNREFERENCED_PARAMETER(nDataSize);
      throw interface_only_exception();   
   }

   void rgn::SetRectRgn(int x1, int y1, int x2, int y2)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      throw interface_only_exception();   
   }

   void rgn::SetRectRgn(LPCRECT lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception();   
   }

   int rgn::CombineRgn(const rgn* pRgn1, const rgn* pRgn2, int nCombineMode)
   {
      UNREFERENCED_PARAMETER(pRgn1);
      UNREFERENCED_PARAMETER(pRgn2);
      UNREFERENCED_PARAMETER(nCombineMode);
      throw interface_only_exception();   
   }

   int rgn::CopyRgn(const rgn* pRgnSrc)
   {
      UNREFERENCED_PARAMETER(pRgnSrc);
      throw interface_only_exception();   
   }

   BOOL rgn::EqualRgn(const rgn* pRgn) const
   {
      UNREFERENCED_PARAMETER(pRgn);
      throw interface_only_exception();   
   }

   int rgn::OffsetRgn(int x, int y)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      throw interface_only_exception();   
   }

   int rgn::OffsetRgn(POINT point)
   {
      UNREFERENCED_PARAMETER(point);
      throw interface_only_exception();   
   }
   
   int rgn::GetRgnBox(LPRECT lpRect) const
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception();   
   }
   
   int rgn::GetRgnBox(rect64 * lpRect) const
   {
      rect rect;
      int iRgn = GetRgnBox(rect);
      *lpRect = rect;
      return iRgn;
   }

   BOOL rgn::PtInRegion(int x, int y) const
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      throw interface_only_exception();   
   }

   BOOL rgn::PtInRegion(POINT point) const
   {
      UNREFERENCED_PARAMETER(point);
      throw interface_only_exception();   
   }

   BOOL rgn::RectInRegion(LPCRECT lpRect) const
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception();   
   }

} // namespace ca