#pragma once


namespace draw2d
{


   class CLASS_DECL_AXIS region :
      virtual public object
   {
   public:


      enum e_combine
      {

         combine_add,
         combine_exclude,
         combine_intersect,
         combine_xor

      };


      enum e_type
      {

         type_none,
         type_rect,
         type_oval,
         type_polygon,
         type_poly_polygon,
         type_round_rect,
         type_combine

      };


      e_type                  m_etype;
      double                 m_x1;
      double                 m_y1;
      double                 m_x2;
      double                 m_y2;
      double                 m_x3;
      double                 m_y3;
      LPPOINTD                m_lppoints;
      LPINT                   m_lppolycounts;
      int32_t                 m_nCount;
      ::draw2d::e_fill_mode      m_efillmode;
      ::draw2d::region *      m_pregion1;
      ::draw2d::region *      m_pregion2;
      e_combine               m_ecombine;


      region();
      region(const region & region);
      virtual ~region();


      virtual bool create_rect(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
      virtual bool create_rect(LPCRECT lpRect);
      virtual bool create_oval(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
      virtual bool create_oval(LPCRECT lpRect);
      virtual bool create_polygon(LPPOINT lpPoints, int32_t nCount, ::draw2d::e_fill_mode efillmode);
      virtual bool create_polygon(LPPOINTD lpPoints,int32_t nCount,::draw2d::e_fill_mode efillmode);
      virtual bool create_poly_polygon(LPPOINTD lpPoints, LPINT lpPolyCounts, int32_t nCount, ::draw2d::e_fill_mode efillmode);
      virtual bool create_poly_polygon(LPPOINT lpPoints,LPINT lpPolyCounts,int32_t nCount,::draw2d::e_fill_mode efillmode);
      //virtual bool add_round_rect(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3);
//      virtual bool add_path(::draw2d::path * ppath);

//      virtual void SetRectRgn(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
//      virtual void SetRectRgn(LPCRECT lpRect);
      virtual bool combine(const ::draw2d::region * prgn1, const ::draw2d::region * prgn2, e_combine ecombine);
      //virtual int32_t CopyRgn(const ::draw2d::region* pRgnSrc);
      //virtual bool EqualRgn(const ::draw2d::region* pRgn) const;
      virtual bool translate(int32_t x, int32_t y);
      virtual bool translate(POINT point);
      virtual bool get_bounding_box(LPRECT lpRect) const;
      //virtual int32_t GetRgnBox(rect64 * lpRect) const;
      //virtual bool contains(int32_t x, int32_t y) const;
      virtual bool contains(POINT point) { return contains(pointd(point));  }
      virtual bool contains(POINTD point) const;
      //virtual bool RectInRegion(LPCRECT lpRect) const;
//#ifdef WINDOWS
      //virtual int32_t GetRegionData(LPRGNDATA lpRgnData, int32_t nCount) const;
//#endif

      bool internal_contains(POINT pt) { return internal_contains(pointd(pt));  }
      bool internal_rect_contains(POINT pt){ return internal_rect_contains(pointd(pt)); }
      bool internal_oval_contains(POINT pt){ return internal_oval_contains(pointd(pt)); }
      bool internal_polygon_contains(POINT pt){ return internal_polygon_contains(pointd(pt)); }
      bool internal_poly_polygon_contains(POINT pt){ return internal_poly_polygon_contains(pointd(pt)); }
      bool internal_combine_contains(POINT pt){ return internal_combine_contains(pointd(pt)); }


      bool internal_contains(POINTD pt);
      bool internal_rect_contains(POINTD pt);
      bool internal_oval_contains(POINTD pt);
      bool internal_polygon_contains(POINTD pt);
      bool internal_poly_polygon_contains(POINTD pt);
      bool internal_combine_contains(POINTD pt);

      virtual void max_bounding_box(LPRECT lpRect) const;
      virtual void max_bounding_box_rect(LPRECT lpRect) const;
      virtual void max_bounding_box_oval(LPRECT lpRect) const;
      virtual void max_bounding_box_polygon(LPRECT lpRect) const;
      virtual void max_bounding_box_poly_polygon(LPRECT lpRect) const;
      virtual void max_bounding_box_combine(LPRECT lpRect) const;

      virtual void max_bounding_box(LPRECTD lpRect) const;
      virtual void max_bounding_box_rect(LPRECTD lpRect) const;
      virtual void max_bounding_box_oval(LPRECTD lpRect) const;
      virtual void max_bounding_box_polygon(LPRECTD lpRect) const;
      virtual void max_bounding_box_poly_polygon(LPRECTD lpRect) const;
      virtual void max_bounding_box_combine(LPRECTD lpRect) const;

      virtual bool destroy();

      region & operator = (const ::draw2d::region & regionSrc);

   };


   class CLASS_DECL_AXIS region_sp :
      public smart_pointer < region >
   {
   public:

      region_sp()
      {
      }

      region_sp(const smart_pointer < region > & p) :
         smart_pointer < region > (p)
      {
      }

      region_sp(allocatorsp allocer) :
         smart_pointer < region > (allocer)
      {
      }


   };


} // namespace draw2d






