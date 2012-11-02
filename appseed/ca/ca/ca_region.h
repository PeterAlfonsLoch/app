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
      int                  m_x1;
      int                  m_y1;
      int                  m_x2;
      int                  m_y2;
      int                  m_x3;
      int                  m_y3;
      LPPOINT              m_lppoints;
      LPINT                m_lppolycounts;
      int                  m_nCount;
      ::ca::e_fill_mode    m_efillmode;
      ::ca::region *       m_pregion1;
      ::ca::region *       m_pregion2;
      e_combine            m_ecombine;


      region();
      region(const region & region);
      virtual ~region();


      virtual bool create_rect(int x1, int y1, int x2, int y2);
      virtual bool create_rect(LPCRECT lpRect);
      virtual bool create_oval(int x1, int y1, int x2, int y2);
      virtual bool create_oval(LPCRECT lpRect);
      virtual bool create_polygon(LPPOINT lpPoints, int nCount, ::ca::e_fill_mode efillmode);
      virtual bool create_poly_polygon(LPPOINT lpPoints, LPINT lpPolyCounts, int nCount, ::ca::e_fill_mode efillmode);
      //virtual bool add_round_rect(int x1, int y1, int x2, int y2, int x3, int y3);
//      virtual bool add_path(::ca::graphics_path * ppath);

//      virtual void SetRectRgn(int x1, int y1, int x2, int y2);
//      virtual void SetRectRgn(LPCRECT lpRect);
      virtual bool combine(const ::ca::region * prgn1, const ::ca::region * prgn2, e_combine ecombine);
      //virtual int CopyRgn(const ::ca::region* pRgnSrc);
      //virtual bool EqualRgn(const ::ca::region* pRgn) const;
      //virtual int OffsetRgn(int x, int y);
      //virtual int OffsetRgn(POINT point);
      virtual int get_bounding_box(LPRECT lpRect) const;
      //virtual int GetRgnBox(rect64 * lpRect) const;
      //virtual bool PtInRegion(int x, int y) const;
      //virtual bool PtInRegion(POINT point) const;
      //virtual bool RectInRegion(LPCRECT lpRect) const;
//#ifdef WINDOWS
      //virtual int GetRegionData(LPRGNDATA lpRgnData, int nCount) const;
//#endif


      virtual bool destroy();

      region & operator = (const ::ca::region & regionSrc);

   };


   typedef smart_pointer < region > region_sp;


} // namespace ca



