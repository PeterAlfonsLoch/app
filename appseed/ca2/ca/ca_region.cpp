#include "StdAfx.h"

namespace ca
{

   BOOL region::CreateRectRgn(int x1, int y1, int x2, int y2)
   {

      m_pta.remove_all();

      m_pta.add(double_point(x1, y1));
      m_pta.add(double_point(x2, y2));

      m_etype = type_rect;

      m_bUpdated = false;

      return TRUE;

   }

   BOOL region::CreateRectRgnIndirect(LPCRECT lpRect)
   {

      m_pta.remove_all();

      m_pta.add(double_point(lpRect->left, lpRect->top));
      m_pta.add(double_point(lpRect->right, lpRect->bottom));

      m_etype = type_rect;

      m_bUpdated = false;

      return TRUE;

   }

   BOOL region::CreateEllipticRgn(int x1, int y1, int x2, int y2)
   {
      
      m_pta.remove_all();

      m_pta.add(double_point(x1, y1));
      m_pta.add(double_point(x2, y2));

      m_etype = type_elliptic;

      m_bUpdated = false;

      return TRUE;

   }

   BOOL region::CreateEllipticRgnIndirect(LPCRECT lpRect)
   {
      
      m_pta.remove_all();

      m_pta.add(double_point(lpRect->left, lpRect->top));
      m_pta.add(double_point(lpRect->right, lpRect->bottom));

      m_etype = type_elliptic;

      m_bUpdated = false;

      return TRUE;

   }

   BOOL region::CreatePolygonRgn(LPPOINT lpPoints, int nCount, int nMode)
   {

      m_pta.remove_all();

      for(int i = 0; i < nCount; i++)
      {
         m_pta.add(double_point(lpPoints[i].x, lpPoints[i].y));
      }

      m_etype = type_polygon;

      m_bUpdated = false;

      return TRUE;

   }

   BOOL region::CreatePolyPolygonRgn(LPPOINT lpPoints, LPINT lpPolyCounts, int nCount, int nPolyFillMode)
   {
      
      m_pta.remove_all();
      m_iaCount.remove_all();

      int n = 0;

      for(int i = 0; i < nCount; i++)
      {
         m_iaCount.add(lpPolyCounts[i]);
         for(int j = 0; j < lpPolyCounts[i]; j++)
         {
            m_pta.add(double_point(lpPoints[n].x, lpPoints[n].y));
            n++;
         }
      }

      m_etype = type_poly_polygon;

      m_bUpdated = false;

      return TRUE;

   }

   BOOL region::CreateRoundRectRgn(int x1, int y1, int x2, int y2, int x3, int y3)
   {
      
      m_pta.remove_all();
      m_iaCount.remove_all();

      m_pta.add(double_point(x1, y1));
      m_pta.add(double_point(x2, y2));
      m_pta.add(double_point(x3, y3));

      m_etype = type_polygon;

      m_bUpdated = false;

      return TRUE;

   }

   BOOL region::CreateFromPath(::ca::graphics * pgraphics)
   {
      UNREFERENCED_PARAMETER(pgraphics);
      throw interface_only_exception();   
   }

   BOOL region::CreateFromData(const XFORM* lpXForm, int nCount, const RGNDATA* pRgnData)
   {
      UNREFERENCED_PARAMETER(lpXForm);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(pRgnData);
      throw interface_only_exception();   
   }

   int region::GetRegionData(LPRGNDATA lpRgnData, int nDataSize) const
   {
      UNREFERENCED_PARAMETER(lpRgnData);
      UNREFERENCED_PARAMETER(nDataSize);
      throw interface_only_exception();   
   }

   void region::SetRectRgn(int x1, int y1, int x2, int y2)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      throw interface_only_exception();   
   }

   void region::SetRectRgn(LPCRECT lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception();   
   }

   int region::CombineRgn(const region* pRgn1, const region* pRgn2, int nCombineMode)
   {
      UNREFERENCED_PARAMETER(pRgn1);
      UNREFERENCED_PARAMETER(pRgn2);
      UNREFERENCED_PARAMETER(nCombineMode);
      throw interface_only_exception();   
   }

   int region::CopyRgn(const region* pRgnSrc)
   {
      UNREFERENCED_PARAMETER(pRgnSrc);
      throw interface_only_exception();   
   }

   BOOL region::EqualRgn(const region* pRgn) const
   {
      UNREFERENCED_PARAMETER(pRgn);
      throw interface_only_exception();   
   }

   int region::OffsetRgn(int x, int y)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      throw interface_only_exception();   
   }

   int region::OffsetRgn(POINT point)
   {
      UNREFERENCED_PARAMETER(point);
      throw interface_only_exception();   
   }
   
   int region::GetRgnBox(LPRECT lpRect) const
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception();   
   }
   
   int region::GetRgnBox(rect64 * lpRect) const
   {
      rect rect;
      int iRgn = GetRgnBox(rect);
      *lpRect = rect;
      return iRgn;
   }

   BOOL region::PtInRegion(int x, int y) const
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      throw interface_only_exception();   
   }

   BOOL region::PtInRegion(POINT point) const
   {
      UNREFERENCED_PARAMETER(point);
      throw interface_only_exception();   
   }

   BOOL region::RectInRegion(LPCRECT lpRect) const
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception();   
   }

} // namespace ca