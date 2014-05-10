#pragma once


namespace draw2d_cairo
{


   class CLASS_DECL_DRAW2D_CAIRO region :
      virtual public ::draw2d::region
   {
   public:

      cairo_t *               m_pdc;
      cairo_surface_t *       m_psurface;
      rect                    m_rectBoundingBoxInternal;



      region(sp(::base::application) papp);
      virtual ~region();


      //virtual void * get_os_data() const;


      /*bool CreateRectRgn(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
      bool CreateRectRgnIndirect(LPCRECT lpRect);
      bool CreateEllipticRgn(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
      bool CreateEllipticRgnIndirect(LPCRECT lpRect);
      bool CreatePolygonRgn(LPPOINT lpPoints, int32_t nCount, int32_t nMode);
      bool CreatePolyPolygonRgn(LPPOINT lpPoints, LPINT lpPolyCounts,
            int32_t nCount, int32_t nPolyFillMode);
      bool CreateRoundRectRgn(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3);
      bool CreateFromPath(::draw2d::graphics * pgraphics);
      bool CreateFromData(const XFORM* lpXForm, int32_t nCount,
         const RGNDATA* pRgnData);*/

   // Operations
      //void SetRectRgn(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
      //void SetRectRgn(LPCRECT lpRect);
      //int32_t CombineRgn(const ::draw2d::region* pRgn1, const ::draw2d::region* pRgn2, int32_t nCombineMode);
      //int32_t CopyRgn(const ::draw2d::region* pRgnSrc);
      //bool EqualRgn(const ::draw2d::region* pRgn) const;
      //int32_t OffsetRgn(int32_t x, int32_t y);
      //int32_t OffsetRgn(POINT point);
      //int32_t GetRgnBox(LPRECT lpRect) const;
      //bool PtInRegion(int32_t x, int32_t y) const;
      //bool PtInRegion(POINT point) const;
      //bool RectInRegion(LPCRECT lpRect) const;
// xxx      int32_t GetRegionData(LPRGNDATA lpRgnData, int32_t nCount) const;

      bool mask(cairo_t * pdc);
      bool mask_rect(cairo_t * pdc);
      bool mask_oval(cairo_t * pdc);
      bool mask_polygon(cairo_t * pdc);
      bool mask_poly_polygon(cairo_t * pdc);
      bool mask_combine(cairo_t * pdc);

      bool clip(cairo_t * pdc);
      bool clip_rect(cairo_t * pdc);
      bool clip_oval(cairo_t * pdc);
      bool clip_polygon(cairo_t * pdc);

      bool is_simple_positive_region();

      virtual void * get_os_data() const;



   };


} // namespace draw2d_cairo


