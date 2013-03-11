#pragma once




namespace ca
{


   class CLASS_DECL_ca region :
      virtual public graphics_object
   {
   public:


      enum e_combine
      {

         combine_add,
         combine_exclude,
         combine_intersect,

      };


      enum e_type
      {

         type_none,
         type_rect,
         type_oval,
         type_polygon,
         type_poly_polygon,
         type_round_rect,
         type_combine,

      };


      e_type               m_etype;
      int32_t                  m_x1;
      int32_t                  m_y1;
      int32_t                  m_x2;
      int32_t                  m_y2;
      int32_t                  m_x3;
      int32_t                  m_y3;
      LPPOINT              m_lppoints;
      LPINT                m_lppolycounts;
      int32_t                  m_nCount;
      ::ca::e_fill_mode    m_efillmode;
      ::ca::region *       m_pregion1;
      ::ca::region *       m_pregion2;
      e_combine            m_ecombine;


      region();
      region(const region & region);
      virtual ~region();


      virtual bool create_rect(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
      virtual bool create_rect(LPCRECT lpRect);
      virtual bool create_oval(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
      virtual bool create_oval(LPCRECT lpRect);
      virtual bool create_polygon(LPPOINT lpPoints, int32_t nCount, ::ca::e_fill_mode efillmode);
      virtual bool create_poly_polygon(LPPOINT lpPoints, LPINT lpPolyCounts, int32_t nCount, ::ca::e_fill_mode efillmode);
      //virtual bool add_round_rect(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3);
//      virtual bool add_path(::ca::graphics_path * ppath);

//      virtual void SetRectRgn(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
//      virtual void SetRectRgn(LPCRECT lpRect);
      virtual bool combine(const ::ca::region * prgn1, const ::ca::region * prgn2, e_combine ecombine);
      //virtual int32_t CopyRgn(const ::ca::region* pRgnSrc);
      //virtual bool EqualRgn(const ::ca::region* pRgn) const;
      virtual bool translate(int32_t x, int32_t y);
      virtual bool translate(POINT point);
      virtual bool get_bounding_box(LPRECT lpRect) const;
      //virtual int32_t GetRgnBox(rect64 * lpRect) const;
      //virtual bool contains(int32_t x, int32_t y) const;
      virtual bool contains(POINT point) const;
      //virtual bool RectInRegion(LPCRECT lpRect) const;
//#ifdef WINDOWS
      //virtual int32_t GetRegionData(LPRGNDATA lpRgnData, int32_t nCount) const;
//#endif

      bool internal_contains(LPPOINT lppt);
      bool internal_rect_contains(LPPOINT lppt);
      bool internal_oval_contains(LPPOINT lppt);
      bool internal_polygon_contains(LPPOINT lppt);
      bool internal_poly_polygon_contains(LPPOINT lppt);
      bool internal_combine_contains(LPPOINT lppt);


      virtual bool destroy();

      region & operator = (const ::ca::region & regionSrc);

   };


   typedef smart_pointer < region > region_sp;


} // namespace ca



