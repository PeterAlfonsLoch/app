#include "framework.h"
#include "draw2d_const.h"
#include "draw2d_object.h"
#include "draw2d_region.h"


namespace draw2d
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


   /*bool region::CreateRectRgn(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {

      m_pta.remove_all();

      m_pta.add(pointd(x1, y1));
      m_pta.add(pointd(x2, y2));

      m_etype = type_rect;

      m_bUpdated = false;

      return TRUE;

   }

   bool region::create_rect(LPCRECT lpRect)
   {

      m_pta.remove_all();

      m_pta.add(pointd(lpRect->left, lpRect->top));
      m_pta.add(pointd(lpRect->right, lpRect->bottom));

      m_etype = type_rect;

      m_bUpdated = false;

      return TRUE;

   }

   bool region::CreateEllipticRgn(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
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

   bool region::CreatePolygonRgn(LPPOINT lpPoints, int32_t nCount, int32_t nMode)
   {

      m_pta.remove_all();

      for(int32_t i = 0; i < nCount; i++)
      {
         m_pta.add(pointd(lpPoints[i].x, lpPoints[i].y));
      }

      m_etype = type_polygon;

      m_bUpdated = false;

      return TRUE;

   }

   bool region::CreatePolyPolygonRgn(LPPOINT lpPoints, LPINT lpPolyCounts, int32_t nCount, int32_t nPolyFillMode)
   {

      m_pta.remove_all();
      m_iaCount.remove_all();

      int32_t n = 0;

      for(int32_t i = 0; i < nCount; i++)
      {
         m_iaCount.add(lpPolyCounts[i]);
         for(int32_t j = 0; j < lpPolyCounts[i]; j++)
         {
            m_pta.add(pointd(lpPoints[n].x, lpPoints[n].y));
            n++;
         }
      }

      m_etype = type_poly_polygon;

      m_bUpdated = false;

      return TRUE;

   }

   bool region::CreateRoundRectRgn(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3)
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

   bool region::CreateFromPath(::draw2d::graphics * pgraphics)
   {
      UNREFERENCED_PARAMETER(pgraphics);
      throw interface_only_exception(get_app());
   }

#ifdef WINDOWS

   bool region::CreateFromData(const XFORM* lpXForm, int32_t nCount, const RGNDATA* pRgnData)
   {
      UNREFERENCED_PARAMETER(lpXForm);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(pRgnData);
      throw interface_only_exception(get_app());
   }

   int32_t region::GetRegionData(LPRGNDATA lpRgnData, int32_t nDataSize) const
   {
      UNREFERENCED_PARAMETER(lpRgnData);
      UNREFERENCED_PARAMETER(nDataSize);
      throw interface_only_exception(get_app());
   }

#endif

   void region::SetRectRgn(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
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

   int32_t region::CombineRgn(const region* pRgn1, const region* pRgn2, int32_t nCombineMode)
   {
      UNREFERENCED_PARAMETER(pRgn1);
      UNREFERENCED_PARAMETER(pRgn2);
      UNREFERENCED_PARAMETER(nCombineMode);
      throw interface_only_exception(get_app());
   }

   int32_t region::CopyRgn(const region* pRgnSrc)
   {
      UNREFERENCED_PARAMETER(pRgnSrc);
      throw interface_only_exception(get_app());
   }

   bool region::EqualRgn(const region* pRgn) const
   {
      UNREFERENCED_PARAMETER(pRgn);
      throw interface_only_exception(get_app());
   }

   int32_t region::OffsetRgn(int32_t x, int32_t y)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      throw interface_only_exception(get_app());
   }

   int32_t region::OffsetRgn(POINT point)
   {
      UNREFERENCED_PARAMETER(point);
      throw interface_only_exception(get_app());
   }

   int32_t region::GetRgnBox(LPRECT lpRect) const
   {
      UNREFERENCED_PARAMETER(lpRect);
      throw interface_only_exception(get_app());
   }

   int32_t region::GetRgnBox(rect64 * lpRect) const
   {
      rect rect;
      int32_t iRgn = GetRgnBox(rect);
      *lpRect = rect;
      return iRgn;
   }

   bool region::PtInRegion(int32_t x, int32_t y) const
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


   bool region::create_rect(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
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
      m_x2 = lprect->right;
      m_y2 = lprect->bottom;

      return true;


   }

   bool region::create_oval(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
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
      m_x2 = lprect->right;
      m_y2 = lprect->bottom;

      return true;

   }

   bool region::create_polygon(LPPOINTD lppoints, int32_t nCount, ::draw2d::e_fill_mode efillmode)
   {

      if(m_etype != type_none)
      {

         destroy();

      }

      m_etype = type_polygon;

      m_nCount = nCount;
      m_lppoints = new POINTD[m_nCount];
      memcpy(m_lppoints, lppoints, sizeof(POINT) * m_nCount);
      m_efillmode = efillmode;

      return true;
   }


   bool region::create_polygon(LPPOINT lppoints,int32_t nCount,::draw2d::e_fill_mode efillmode)
   {

      if(m_etype != type_none)
      {

         destroy();

      }

      m_etype = type_polygon;

      m_nCount = nCount;

      m_lppoints = new POINTD[m_nCount];

      for(index i = 0; i < m_nCount; i++)
      {
         
         m_lppoints[i].x = (double) lppoints[i].x;
         
         m_lppoints[i].y = (double) lppoints[i].y;

      }

      m_efillmode = efillmode;

      return true;

   }


   bool region::create_poly_polygon(LPPOINTD lppoints, LPINT lppolycounts, int32_t nCount, ::draw2d::e_fill_mode efillmode)
   {

      if(m_etype != type_none)
      {

         destroy();

      }

      m_etype = type_poly_polygon;

      m_nCount = nCount;

      m_lppolycounts = new INT[m_nCount];

      memcpy(m_lppolycounts, lppolycounts, sizeof(INT) * m_nCount);

      int32_t iTotalCount = 0;

      for(int32_t i = 0; i < nCount; i++)
      {

         iTotalCount += m_lppolycounts[i];

      }
      
      m_lppoints = new POINTD[iTotalCount];

      memcpy(m_lppoints, lppoints, sizeof(POINT) * iTotalCount);

      m_efillmode = efillmode;

      return true;

   }


   bool region::create_poly_polygon(LPPOINT lppoints,LPINT lppolycounts,int32_t nCount,::draw2d::e_fill_mode efillmode)
   {

      if(m_etype != type_none)
      {

         destroy();

      }

      m_etype = type_poly_polygon;

      m_nCount = nCount;

      m_lppolycounts = new INT[m_nCount];

      memcpy(m_lppolycounts,lppolycounts,sizeof(INT)* m_nCount);

      int32_t iTotalCount = 0;

      for(int32_t i = 0; i < nCount; i++)
      {

         iTotalCount += m_lppolycounts[i];

      }
      
      m_lppoints = new POINTD[iTotalCount];

      for(int32_t i = 0; i < iTotalCount; i++)
      {

         m_lppoints[i].x = lppoints[i].x;

         m_lppoints[i].y = lppoints[i].y;

      }

      m_efillmode = efillmode;

      return true;

   }


   //virtual bool add_round_rect(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3);
//      virtual bool add_path(::draw2d::path * ppath);

//      virtual void SetRectRgn(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
//      virtual void SetRectRgn(LPCRECT lpRect);
   bool region::combine(const ::draw2d::region * prgn1, const ::draw2d::region * prgn2, e_combine ecombine)
   {

      if(m_etype != type_none)
      {

         destroy();

      }

      m_etype = type_combine;

      m_pregion1 = new ::draw2d::region(*prgn1);

      m_pregion2 = new ::draw2d::region(*prgn2);

      m_ecombine  = ecombine;

      return true;

   }

   region & region::operator = (const ::draw2d::region & regionSrc)
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
      case type_oval:
         m_x1 = regionSrc.m_x1;
         m_y1 = regionSrc.m_y1;
         m_x2 = regionSrc.m_x2;
         m_y2 = regionSrc.m_y2;
         return *this;
      case type_polygon:
         m_nCount = regionSrc.m_nCount;
         m_lppoints = new POINTD[m_nCount];
         memcpy(m_lppoints, regionSrc.m_lppoints, sizeof(POINTD) * m_nCount);
         m_efillmode = regionSrc.m_efillmode;
         return *this;
      case type_poly_polygon:
         {
            m_nCount = regionSrc.m_nCount;
            m_lppolycounts = new INT[m_nCount];
            memcpy(m_lppolycounts, regionSrc.m_lppolycounts, sizeof(INT) * m_nCount);
            int32_t iTotalCount = 0;
            for(int32_t i = 0; i < m_nCount; i++)
            {
               iTotalCount += m_lppolycounts[i];
            }
            m_lppoints = new POINTD[iTotalCount];
            memcpy(m_lppoints, regionSrc.m_lppoints, sizeof(POINTD) * iTotalCount);
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
         m_pregion1 = new ::draw2d::region(*regionSrc.m_pregion1);
         m_pregion2 = new ::draw2d::region(*regionSrc.m_pregion2);
         m_ecombine = regionSrc.m_ecombine;
         return *this;
      default:
         throw not_implemented(get_app());
      };
      return *this;

   }


   bool region::get_bounding_box(LPRECT lprect) const
   {

      throw interface_only_exception(get_app());

   }

   bool region::contains(POINTD point) const
   {

      return ((region *) this)->internal_contains(point);

   }


   bool region::translate(int32_t x, int32_t y)
   {
      m_bUpdated = false;
      switch(m_etype)
      {
      case type_none:
         return false;
      case type_round_rect:
         m_x3 += x;
         m_y3 += y;
      case type_rect:
      case type_oval:
         m_x1 += x;
         m_y1 += y;
         m_x2 += x;
         m_y2 += y;
         return true;
      case type_polygon:
         for(int32_t i = 0; i < m_nCount; i++)
         {
            m_lppoints[i].x += x;
            m_lppoints[i].y += y;
         }
         return true;
      case type_poly_polygon:
         {
            int32_t iTotalCount = 0;
            for(int32_t i = 0; i < m_nCount; i++)
            {
               iTotalCount += m_lppolycounts[i];
            }
            for(int32_t i = 0; i < iTotalCount; i++)
            {
               m_lppoints[i].x += x;
               m_lppoints[i].y += y;
            }
         }
         return true;
      case type_combine:
         {
            bool bOk1 = m_pregion1->translate(x, y);
            bool bOk2 = m_pregion2->translate(x, y);
            return bOk1 && bOk2;
         }
      default:
         throw not_implemented(get_app());
      };
      return false;

   }

   bool region::translate(POINT p)
   {

      return translate(p.x, p.y);

   }


















   void region::max_bounding_box(LPRECT lprect) const
   {

      ::rectd rect;

      max_bounding_box(rect);

      copy(lprect,rect);

   }


   void region::max_bounding_box_rect(LPRECT lprect) const
   {

      ::rectd rect;

      max_bounding_box_rect(rect);

      copy(lprect,rect);

   }

   void region::max_bounding_box_oval(LPRECT lprect) const
   {

      ::rectd rect;

      max_bounding_box_oval(rect);

      copy(lprect,rect);

   }


   void region::max_bounding_box_polygon(LPRECT lprect) const
   {

      ::rectd rect;

      max_bounding_box_polygon(rect);

      copy(lprect,rect);

   }


   void region::max_bounding_box_poly_polygon(LPRECT lprect) const
   {

      ::rectd rect;

      max_bounding_box_poly_polygon(rect);

      copy(lprect,rect);

   }


   void region::max_bounding_box_combine(LPRECT lprect) const
   {

      ::rectd rect;

      max_bounding_box_combine(rect);

      copy(lprect,rect);

   }




































   void region::max_bounding_box(LPRECTD lprect) const
   {

      switch(m_etype)
      {
      case type_none:
         return;
      case type_rect:
         return max_bounding_box_rect(lprect);
      case type_oval:
         return max_bounding_box_oval(lprect);
      case type_polygon:
         return max_bounding_box_polygon(lprect);
      case type_poly_polygon:
         return max_bounding_box_poly_polygon(lprect);
      case type_combine:
         return max_bounding_box_combine(lprect);
      default:
         throw not_implemented(get_app());
      }

   }


   void region::max_bounding_box_rect(LPRECTD lprect) const
   {

      lprect->left = MIN(lprect->left,m_x1);
      lprect->right = MAX(lprect->right,m_x2);
      lprect->top = MIN(lprect->left,m_y1);
      lprect->bottom = MAX(lprect->right,m_y2);

   }

   void region::max_bounding_box_oval(LPRECTD lprect) const
   {

      lprect->left = MIN(lprect->left,m_x1);
      lprect->right = MAX(lprect->right,m_x2);
      lprect->top = MIN(lprect->left,m_y1);
      lprect->bottom = MAX(lprect->right,m_y2);

   }


   void region::max_bounding_box_polygon(LPRECTD lprect) const
   {

      if(m_nCount <= 0)
         return;

      for(int i = 0; i < m_nCount; i++)
      {

         lprect->left = MIN(lprect->left,m_lppoints[i].x);
         lprect->right = MAX(lprect->right,m_lppoints[i].x);
         lprect->top = MIN(lprect->left,m_lppoints[i].y);
         lprect->bottom = MAX(lprect->right,m_lppoints[i].y);

      }

   }

   void region::max_bounding_box_poly_polygon(LPRECTD lprect) const
   {

      int32_t n = 0;

      for(int32_t i = 0; i < m_nCount;i++)
      {

         int32_t iCount = m_lppolycounts[i];

         for(int j = 0; j < iCount; j++,n++)
         {

            lprect->left = MIN(lprect->left,m_lppoints[n].x);
            lprect->right = MAX(lprect->right,m_lppoints[n].x);
            lprect->top = MIN(lprect->left,m_lppoints[n].y);
            lprect->bottom = MAX(lprect->right,m_lppoints[n].y);

         }

      }

   }


   void region::max_bounding_box_combine(LPRECTD lprect) const
   {

      m_pregion1->max_bounding_box(lprect);

      m_pregion2->max_bounding_box(lprect);

   }









































   bool region::internal_contains(POINTD point)
   {

      switch(m_etype)
      {
      case type_none:
         return false;
      case type_rect:
         return internal_rect_contains(point);
      case type_oval:
         return internal_oval_contains(point);
      case type_polygon:
         return internal_polygon_contains(point);
      case type_poly_polygon:
         return internal_poly_polygon_contains(point);
      case type_combine:
         return internal_combine_contains(point);
      default:
         throw not_implemented(get_app());
      }

      return false;

   }

   bool region::internal_rect_contains(POINTD point)
   {

      return point.x >= m_x1 && point.y >= m_y1 && point.x <= m_x2 && point.y <= m_y2;

   }

   bool region::internal_oval_contains(POINTD point)
   {

      double centerx    = (m_x2 + m_x1) / 2.0;
      double centery    = (m_y2 + m_y1) / 2.0;

      double radiusx    = abs(m_x2 - m_x1) / 2.0;
      double radiusy    = abs(m_y2 - m_y1) / 2.0;

      if(radiusx == 0.0 || radiusy == 0.0)
         return false;

      double x = point.x;
      double y = point.y;

      return ((x - centerx) * (x - centerx) / (radiusx * radiusx) + (y - centery) * (y - centery) / (radiusy * radiusy)) <= 1.0;

   }


   bool region::internal_polygon_contains(POINTD point)
   {

      if(m_nCount <= 0)
         return false;

      if(::polygon_contains(&point, m_lppoints, m_nCount))
         return true;

      return false;

   }

   bool region::internal_poly_polygon_contains(POINTD point)
   {

      int32_t n = 0;

      for(int32_t i = 0; i < m_nCount;i++)
      {
         int32_t iCount = m_lppolycounts[i];
         if(::polygon_contains(&point, &m_lppoints[n], iCount))
            return true;
         n += iCount;
      }

      return false;

   }

   bool region::internal_combine_contains(POINTD point)
   {

      if(m_ecombine == ::draw2d::region::combine_add)
      {
         if(m_pregion1->internal_contains(point))
            return true;
         if(m_pregion2->internal_contains(point))
            return true;
         return false;
      }
      else if(m_ecombine == ::draw2d::region::combine_exclude)
      {
         if(m_pregion2->internal_contains(point))
            return false;
         if(m_pregion1->internal_contains(point))
            return true;
         return false;
      }
      else if(m_ecombine == ::draw2d::region::combine_intersect)
      {
         if(m_pregion1->internal_contains(point))
         {
            if(m_pregion2->internal_contains(point))
               return true;
         }
         return false;
      }
      else if(m_ecombine == ::draw2d::region::combine_xor)
      {
         if(m_pregion1->internal_contains(point))
         {
            if(m_pregion2->internal_contains(point))
               return false;
            else
               return true;
         }
         else if(m_pregion2->internal_contains(point))
         {
            return true;
         }
         else
         {
            return false;
         }
      }
      else
      {
         return false;
      }


   }


} // namespace draw2d





