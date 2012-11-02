#include "framework.h"


namespace ca
{


   region::region()
   {

      m_etype        = type_none;
      m_bUpdated     = false;

   }

   region::region(const region & region)
   {

      m_etype        = type_none;
      m_bUpdated     = false;
      operator = (region);

   }


   region::~region()
   {
      if(m_etype != type_none)
      {
         destroy();
      }
   }

   bool region::destroy()
   {

      e_type etype = m_etype;

      m_etype = type_none;

      switch(etype)
      {
      case type_none:
         return false;
      case type_rect:
         return true;
      case type_oval:
         return true;
      case type_polygon:
         delete m_lppoints;
         return true;
      case type_poly_polygon:
         delete m_lppoints;
         delete m_lppolycounts;
         return true;
      case type_round_rect:
         return true;
      case type_combine:
         delete m_pregion1;
         delete m_pregion2;
         return true;
      default:
         throw not_implemented(get_app());
      };

   }


   /*bool region::CreateRectRgn(int x1, int y1, int x2, int y2)
   {

      m_pta.remove_all();

      m_pta.add(pointd(x1, y1));
      m_pta.add(pointd(x2, y2));

      m_etype = type_rect;

      m_bUpdated = false;

      return TRUE;

   }

   bool region::CreateRectRgnIndirect(LPCRECT lpRect)
   {

      m_pta.remove_all();

      m_pta.add(pointd(lpRect->left, lpRect->top));
      m_pta.add(pointd(lpRect->right, lpRect->bottom));

      m_etype = type_rect;

      m_bUpdated = false;

      return TRUE;

   }

   bool region::CreateEllipticRgn(int x1, int y1, int x2, int y2)
   {

      m_pta.remove_all();

      m_pta.add(pointd(x1, y1));
      m_pta.add(pointd(x2, y2));

      m_etype = type_elliptic;

      m_bUpdated = false;

      return TRUE;

   }

   bool region::CreateEllipticRgnIndirect(LPCRECT lpRect)
   {

      m_pta.remove_all();

      m_pta.add(pointd(lpRect->left, lpRect->top));
      m_pta.add(pointd(lpRect->right, lpRect->bottom));

      m_etype = type_elliptic;

      m_bUpdated = false;

      return TRUE;

   }

   bool region::CreatePolygonRgn(LPPOINT lpPoints, int nCount, int nMode)
   {

      m_pta.remove_all();

      for(int i = 0; i < nCount; i++)
      {
         m_pta.add(pointd(lpPoints[i].x, lpPoints[i].y));
      }

      m_etype = type_polygon;

      m_bUpdated = false;

      return TRUE;

   }

   bool region::CreatePolyPolygonRgn(LPPOINT lpPoints, LPINT lpPolyCounts, int nCount, int nPolyFillMode)
   {

      m_pta.remove_all();
      m_iaCount.remove_all();

      int n = 0;

      for(int i = 0; i < nCount; i++)
      {
         m_iaCount.add(lpPolyCounts[i]);
         for(int j = 0; j < lpPolyCounts[i]; j++)
         {
            m_pta.add(pointd(lpPoints[n].x, lpPoints[n].y));
            n++;
         }
      }

      m_etype = type_poly_polygon;

      m_bUpdated = false;

      return TRUE;

   }

   bool region::CreateRoundRectRgn(int x1, int y1, int x2, int y2, int x3, int y3)
   {

      m_pta.remove_all();
      m_iaCount.remove_all();

      m_pta.add(pointd(x1, y1));
      m_pta.add(pointd(x2, y2));
      m_pta.add(pointd(x3, y3));

      m_etype = type_polygon;

      m_bUpdated = false;

      return TRUE;

   }

   bool region::CreateFromPath(::ca::graphics * pgraphics)
   {
      UNREFERENCED_PARAMETER(pgraphics);
      throw interface_only_exception(get_app());
   }

#ifdef WINDOWS

   bool region::CreateFromData(const XFORM* lpXForm, int nCount, const RGNDATA* pRgnData)
   {
      UNREFERENCED_PARAMETER(lpXForm);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(pRgnData);
      throw interface_only_exception(get_app());
   }

   int region::GetRegionData(LPRGNDATA lpRgnData, int nDataSize) const
   {
      UNREFERENCED_PARAMETER(lpRgnData);
      UNREFERENCED_PARAMETER(nDataSize);
      throw interface_only_exception(get_app());
   }

#endif

   void region::SetRectRgn(int x1, int y1, int x2, int y2)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      throw interface_only_exception(get_app());
   }

   void region::SetRectRgn(LPCRECT lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception(get_app());
   }

   int region::CombineRgn(const region* pRgn1, const region* pRgn2, int nCombineMode)
   {
      UNREFERENCED_PARAMETER(pRgn1);
      UNREFERENCED_PARAMETER(pRgn2);
      UNREFERENCED_PARAMETER(nCombineMode);
      throw interface_only_exception(get_app());
   }

   int region::CopyRgn(const region* pRgnSrc)
   {
      UNREFERENCED_PARAMETER(pRgnSrc);
      throw interface_only_exception(get_app());
   }

   bool region::EqualRgn(const region* pRgn) const
   {
      UNREFERENCED_PARAMETER(pRgn);
      throw interface_only_exception(get_app());
   }

   int region::OffsetRgn(int x, int y)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      throw interface_only_exception(get_app());
   }

   int region::OffsetRgn(POINT point)
   {
      UNREFERENCED_PARAMETER(point);
      throw interface_only_exception(get_app());
   }

   int region::GetRgnBox(LPRECT lpRect) const
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception(get_app());
   }

   int region::GetRgnBox(rect64 * lpRect) const
   {
      rect rect;
      int iRgn = GetRgnBox(rect);
      *lpRect = rect;
      return iRgn;
   }

   bool region::PtInRegion(int x, int y) const
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      throw interface_only_exception(get_app());
   }

   bool region::PtInRegion(POINT point) const
   {
      UNREFERENCED_PARAMETER(point);
      throw interface_only_exception(get_app());
   }

   bool region::RectInRegion(LPCRECT lpRect) const
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception(get_app());
   }
*/


   bool region::create_rect(int x1, int y1, int x2, int y2)
   {

      if(m_etype != type_none)
      {

         destroy();

      }

      m_etype = type_rect;

      m_x1 = x1;
      m_y1 = y1;
      m_x2 = x2;
      m_y2 = y2;

      return true;


   }

   bool region::create_rect(LPCRECT lprect)
   {

      if(m_etype != type_none)
      {

         destroy();

      }

      m_etype = type_rect;

      m_x1 = lprect->left;
      m_y1 = lprect->top;
      m_x2 = lprect->left;
      m_y2 = lprect->top;

      return true;


   }

   bool region::create_oval(int x1, int y1, int x2, int y2)
   {

      if(m_etype != type_none)
      {

         destroy();

      }

      m_etype = type_oval;

      m_x1 = x1;
      m_y1 = y1;
      m_x2 = x2;
      m_y2 = y2;

      return true;

   }

   bool region::create_oval(LPCRECT lprect)
   {

      if(m_etype != type_none)
      {

         destroy();

      }

      m_etype = type_oval;

      m_x1 = lprect->left;
      m_y1 = lprect->top;
      m_x2 = lprect->left;
      m_y2 = lprect->top;

      return true;

   }

   bool region::create_polygon(LPPOINT lppoints, int nCount, ::ca::e_fill_mode efillmode)
   {

      if(m_etype != type_none)
      {

         destroy();

      }

      m_etype = type_polygon;

      m_nCount = nCount;
      m_lppoints = new POINT[m_nCount];
      memcpy(m_lppoints, lppoints, sizeof(POINT) * m_nCount);
      m_efillmode = efillmode;

      return true;
   }

   bool region::create_poly_polygon(LPPOINT lppoints, LPINT lppolycounts, int nCount, ::ca::e_fill_mode efillmode)
   {

      if(m_etype != type_none)
      {

         destroy();

      }

      m_etype = type_poly_polygon;

      m_nCount = nCount;
      m_lppolycounts = new INT[m_nCount];
      memcpy(m_lppolycounts, lppolycounts, sizeof(INT) * m_nCount);
      int iTotalCount = 0;
      for(int i = 0; i < nCount; i++)
      {
         iTotalCount += m_lppolycounts[i];
      }
      m_lppoints = new POINT[iTotalCount];
      memcpy(m_lppoints, lppoints, sizeof(POINT) * iTotalCount);
      m_efillmode = efillmode;

      return true;

   }
   //virtual bool add_round_rect(int x1, int y1, int x2, int y2, int x3, int y3);
//      virtual bool add_path(::ca::graphics_path * ppath);

//      virtual void SetRectRgn(int x1, int y1, int x2, int y2);
//      virtual void SetRectRgn(LPCRECT lpRect);
   bool region::combine(const ::ca::region * prgn1, const ::ca::region * prgn2, e_combine ecombine)
   {

      if(m_etype != type_none)
      {

         destroy();

      }

      m_etype = type_combine;

      m_pregion1 = new ::ca::region(*prgn1);

      m_pregion2 = new ::ca::region(*prgn2);

      m_ecombine  = ecombine;

      return true;

   }

   region & region::operator = (const ::ca::region & regionSrc)
   {

      if(this == &regionSrc)
         return *this;

      if(m_etype != type_none)
      {

         destroy();

      }

      m_etype = regionSrc.m_etype;

      switch(m_etype)
      {
      case type_none:
         return *this;
      case type_rect:
         m_x1 = regionSrc.m_x1;
         m_y1 = regionSrc.m_y1;
         m_x2 = regionSrc.m_x2;
         m_y2 = regionSrc.m_y2;
         return *this;
      case type_oval:
         m_x1 = regionSrc.m_x1;
         m_y1 = regionSrc.m_y1;
         m_x2 = regionSrc.m_x2;
         m_y2 = regionSrc.m_y2;
         return *this;
      case type_polygon:
         m_nCount = regionSrc.m_nCount;
         m_lppoints = new POINT[m_nCount];
         memcpy(m_lppoints, regionSrc.m_lppoints, sizeof(POINT) * m_nCount);
         m_efillmode = regionSrc.m_efillmode;
         return *this;
      case type_poly_polygon:
         {
            m_nCount = regionSrc.m_nCount;
            m_lppolycounts = new INT[m_nCount];
            memcpy(m_lppolycounts, regionSrc.m_lppolycounts, sizeof(INT) * m_nCount);
            int iTotalCount = 0;
            for(int i = 0; i < m_nCount; i++)
            {
               iTotalCount += m_lppolycounts[i];
            }
            m_lppoints = new POINT[iTotalCount];
            memcpy(m_lppoints, regionSrc.m_lppoints, sizeof(POINT) * iTotalCount);
            m_efillmode = regionSrc.m_efillmode;
         }
         return *this;
      case type_round_rect:
         m_x1 = regionSrc.m_x1;
         m_y1 = regionSrc.m_y1;
         m_x2 = regionSrc.m_x2;
         m_y2 = regionSrc.m_y2;
         m_x3 = regionSrc.m_x3;
         m_y3 = regionSrc.m_y3;
         return *this;
      case type_combine:
         m_pregion1 = new ::ca::region(*regionSrc.m_pregion1);
         m_pregion2 = new ::ca::region(*regionSrc.m_pregion2);
         m_ecombine = regionSrc.m_ecombine;
         return *this;
      default:
         throw not_implemented(get_app());
      };
      return *this;

   }

} // namespace ca
