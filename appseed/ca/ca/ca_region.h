#pragma once




namespace ca
{


   class CLASS_DECL_ca region :
      virtual public graphics_object
   {
   public:

      enum e_type
      {
         type_none,
         type_rect,
         type_elliptic,
         type_polygon,
         type_poly_polygon,
         type_round,
      };

      pointd_array            m_pta;
      int_array               m_iaCount;
      e_type                  m_etype;

      
      region();


      virtual bool CreateRectRgn(int x1, int y1, int x2, int y2);
      virtual bool CreateRectRgnIndirect(LPCRECT lpRect);
      virtual bool CreateEllipticRgn(int x1, int y1, int x2, int y2);
      virtual bool CreateEllipticRgnIndirect(LPCRECT lpRect);
      virtual bool CreatePolygonRgn(LPPOINT lpPoints, int nCount, int nMode);
      virtual bool CreatePolyPolygonRgn(LPPOINT lpPoints, LPINT lpPolyCounts,
            int nCount, int nPolyFillMode);
      virtual bool CreateRoundRectRgn(int x1, int y1, int x2, int y2, int x3, int y3);
      virtual bool CreateFromPath(::ca::graphics * pgraphics);
   #ifdef WINDOWS
      virtual bool CreateFromData(const XFORM* lpXForm, int nCount,
         const RGNDATA* pRgnData);
   #endif

      virtual void SetRectRgn(int x1, int y1, int x2, int y2);
      virtual void SetRectRgn(LPCRECT lpRect);
      virtual int CombineRgn(const ::ca::region* pRgn1, const ::ca::region* pRgn2, int nCombineMode);
      virtual int CopyRgn(const ::ca::region* pRgnSrc);
      virtual bool EqualRgn(const ::ca::region* pRgn) const;
      virtual int OffsetRgn(int x, int y);
      virtual int OffsetRgn(POINT point);
      virtual int GetRgnBox(LPRECT lpRect) const;
      virtual int GetRgnBox(rect64 * lpRect) const;
      virtual bool PtInRegion(int x, int y) const;
      virtual bool PtInRegion(POINT point) const;
      virtual bool RectInRegion(LPCRECT lpRect) const;
#ifdef WINDOWS
      virtual int GetRegionData(LPRGNDATA lpRgnData, int nCount) const;
#endif

      region & operator = (const ::ca::region & regionSrc);

   };


   typedef smart_pointer < region > region_sp;


} // namespace ca



