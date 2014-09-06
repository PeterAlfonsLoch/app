#pragma once



namespace draw2d
{


   //////////////////////////////////////////////////////////////////////
   //   Creator : El Barto (ef00@luc.ac.be)
   //   Location : http://www.luc.ac.be/~ef00/ebgfx
   //   Date : 09-04-98
   //////////////////////////////////////////////////////////////////////


   class CLASS_DECL_AURA dib :
      virtual public ::object,
      virtual public ::file::serializable
   {
   public:



      enum e_type
      {

         type_complex,
         type_plain_color

      };

      
      class descriptor
      {
      public:

         e_type            m_etype;
         COLORREF          m_cr;
         class size        m_size;

         bool operator == (const descriptor & d) const
         {

            if(m_etype != d.m_etype)
               return false;

            if(m_size != d.m_size)
               return false;

            switch(m_etype)
            {
            case type_plain_color:
               return m_cr == d.m_cr;
            default:
               return true;
            };

         }

         bool operator != (const descriptor & d) const
         {
            return !operator ==(d);
         }

      };

      BITMAPINFO        m_info;
      COLORREF *        m_pcolorref;
      class size        m_size;
      int32_t           m_iScan;
      bool              m_bMapped; // optionally used by implementation
      descriptor        m_descriptor;


      static float Cosines[360];
      static float Sines[360];
      static int64_t CosN[360]; // * 1 << 31
      static int64_t SinN[360];
      static int64_t Cos10N[10]; // until 10 degress
      static int64_t Sin10N[10]; // more precision * 1 << 34
      static double dPi;


      dib();
      virtual ~dib();


      virtual ::draw2d::graphics * get_graphics();
      virtual ::draw2d::bitmap_sp get_bitmap();
      virtual ::draw2d::bitmap_sp detach_bitmap();


      virtual COLORREF * get_data();


      virtual void construct(int32_t cx, int32_t cy);

      virtual void stretch_dib(dib * pdib);

      void rate_rgb(int iMul,int iDiv);
      virtual bool dc_select(bool bSelect = true);

      virtual COLORREF GetAverageColor();
      virtual bool blend(dib * pdib, dib * pdibRate);
      virtual bool Blend(dib *pdib, dib * pdibA, int32_t A);
      virtual bool Blend(dib *pdib, dib * pdibA);
      virtual bool blend(point ptDst, ::draw2d::dib * pdibSrc, point ptSrc, ::draw2d::dib * pdibAlf, point ptDstAlf, class size size);
      virtual bool blend(point ptDst, ::draw2d::dib * pdibAlf, point ptAlf, class size size);
      virtual bool bitmap_blend(::draw2d::graphics * pgraphics, LPCRECT lprect);
      virtual bool color_blend(COLORREF cr, BYTE bAlpha);
      virtual void BitBlt(dib * pdib, int32_t op);
      virtual int32_t cos(int32_t i, int32_t iAngle);
      virtual int32_t sin(int32_t i, int32_t iAngle);
      virtual int32_t cos10(int32_t i, int32_t iAngle);
      virtual int32_t sin10(int32_t i, int32_t iAngle);

      virtual void map(bool bApplyAlphaTransform = true); // some implementations may requrire to map to m_pcolorref before manipulate it
      virtual void unmap(); // some implementations may require to unmap from m_pcolorref to update *os* bitmap
      virtual void set_mapped();


      virtual bool is_rgb_black();
      virtual void do_xor(dib * pdib);

      virtual void ToAlpha(int32_t i);
      virtual void ToAlphaAndFill(int32_t i, COLORREF cr);
      virtual void GrayToARGB(COLORREF cr);

      virtual void from_alpha();
      virtual void mult_alpha(::draw2d::dib * pdibWork, bool bPreserveAlpha = true);

      virtual void mult_alpha();
      virtual void div_alpha();

      virtual void rotate(dib * pdib, LPCRECT lpcrect, double dAngle, double dScale);
      virtual void rotate(dib * pdib, double dAngle, double dScale);
      virtual void Rotate034(dib * pdib, double dAngle, double dScale);


      virtual void set_rgb(int32_t R, int32_t G, int32_t B);
      virtual bool rgb_from(::draw2d::dib * pdib);



      virtual void SetIconMask(::visual::icon * picon, int32_t cx, int32_t cy);
      virtual void RadialFill(BYTE a, BYTE r, BYTE g, BYTE b, int32_t x, int32_t y, int32_t iRadius);
      virtual void RadialFill(
         BYTE a1, BYTE r1, BYTE g1, BYTE b1, // center colors
         BYTE a2, BYTE r2, BYTE g2, BYTE b2, // border colors
         int32_t x, int32_t y, int32_t iRadius);

      virtual void gradient_fill(COLORREF clr1, COLORREF clr2, POINT pt1, POINT pt2);
      virtual void gradient_horizontal_fill(COLORREF clr1, COLORREF clr2, int start, int end);
      virtual void gradient_vertical_fill(COLORREF clr1, COLORREF clr2, int start, int end);
      virtual void gradient_horizontal_fill(COLORREF clr1, COLORREF clr2);
      virtual void gradient_vertical_fill(COLORREF clr1, COLORREF clr2);


      virtual uint32_t GetPixel(int32_t x, int32_t y);
      virtual void Mask(COLORREF crMask, COLORREF crInMask, COLORREF crOutMask);
      virtual void channel_mask(BYTE uchFind, BYTE uchSet, BYTE uchUnset, visual::rgba::echannel echannel);
      virtual void transparent_color(color color);

      using ::object::create;
      virtual bool create(class size);
      virtual bool create(int32_t iWidth, int32_t iHeight);
      virtual bool create(::draw2d::graphics * pdc);
      virtual bool Destroy();

      virtual bool realize(::draw2d::graphics * pdc);
      virtual bool unrealize();
      virtual bool is_realized();
      virtual bool defer_realize(::draw2d::graphics * pdc);


      virtual void DivideRGB(int32_t iDivide);
      virtual void DivideARGB(int32_t iDivide);
      virtual void DivideA(int32_t iDivide);

      virtual bool from(::draw2d::dib * pdib);
      virtual bool from(::draw2d::graphics * pdc);
      virtual bool from(point ptDst, ::draw2d::graphics * pdc, point ptSrc, class size size);
      virtual bool from(point ptDst, ::draw2d::dib * pdc, point ptSrc, class size size);
      virtual bool from_ignore_alpha(point ptDst, ::draw2d::dib * pdc, point ptSrc, class size size);

      virtual bool to(::draw2d::graphics * pgraphics);
      virtual bool to(::draw2d::graphics * pgraphics, point pt);
      virtual bool to(::draw2d::graphics * pgraphics, class size size);
      virtual bool to(::draw2d::graphics * pgraphics, point pt, class size size);
      virtual bool to(::draw2d::graphics * pgraphics, const RECT & lpcrect);
      virtual bool to(::draw2d::graphics * pgraphics, point pt, class size size, point ptSrc);


      virtual bool pixelate(int32_t iSize);



      virtual void fill_channel(int32_t C, visual::rgba::echannel echannel);
      virtual void FillByte(uchar uch);
      virtual void Fill(int32_t level);
      virtual void Fill (int32_t A, int32_t R, int32_t G, int32_t B );
//      virtual void Fill ( int32_t R, int32_t G, int32_t B );
      virtual void set ( int32_t R, int32_t G, int32_t B );
      virtual void FillGlass ( int32_t R, int32_t G, int32_t B, int32_t A );
      virtual void FillStippledGlass ( int32_t R, int32_t G, int32_t B );
      virtual void Invert();
      virtual void channel_invert(visual::rgba::echannel echannel);
      virtual void channel_multiply(visual::rgba::echannel echannel, double dRate);
      virtual void channel_multiply(visual::rgba::echannel echannel, ::draw2d::dib * pdib);
      virtual void channel_lighten(visual::rgba::echannel echannel, ::draw2d::dib * pdib);
      virtual void channel_darken(visual::rgba::echannel echannel, ::draw2d::dib * pdib);
      virtual void channel_from(visual::rgba::echannel echannel, ::draw2d::dib * pdib);
      virtual void channel_copy(visual::rgba::echannel echannelDst, visual::rgba::echannel echannelSrc);
      virtual void channel_copy(visual::rgba::echannel echannelDst, visual::rgba::echannel echannelSrc, ::draw2d::dib * pdib);

      virtual void Map (int32_t ToRgb, int32_t FromRgb );

      virtual void copy( dib *dib );
      virtual void Paste ( dib *dib );

      virtual void Blend ( dib *dib, int32_t A );
      virtual void Darken ( dib *dib );
      virtual void Difference ( dib *dib );
      virtual void Lighten ( dib *dib );
      virtual void Multiply ( dib *dib );
      virtual void Screen ( dib *dib );

      virtual void copy ( dib *dib, int32_t x, int32_t y );
      virtual void PasteRect ( dib *dib, int32_t x, int32_t y );

      virtual void FillRect ( int32_t x, int32_t y, int32_t w, int32_t h, int32_t R, int32_t G, int32_t B );
      virtual void FillRect ( int32_t x, int32_t y, int32_t w, int32_t h, int32_t A, int32_t R, int32_t G, int32_t B );
      virtual void FillGlassRect ( int32_t x, int32_t y, int32_t w, int32_t h, int32_t R, int32_t G, int32_t B, int32_t A );
      virtual void FillStippledGlassRect ( int32_t x, int32_t y, int32_t w, int32_t h, int32_t R, int32_t G, int32_t B );

      virtual void BlendRect ( dib *dib, int32_t x, int32_t y, int32_t A );
      virtual void DarkenRect ( dib *dib, int32_t x, int32_t y );
      virtual void DifferenceRect ( dib *dib, int32_t x, int32_t y );
      virtual void LightenRect ( dib *dib, int32_t x, int32_t y );
      virtual void MultiplyRect ( dib *dib, int32_t x, int32_t y );
      virtual void ScreenRect ( dib *dib, int32_t x, int32_t y );

      virtual void horizontal_line(int32_t y, int32_t R, int32_t G, int32_t B, int32_t A = 0, int32_t x1 = 0, int32_t x2 = -1);
      virtual void Line ( int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t R, int32_t G, int32_t B );
      virtual void LineGlass ( int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t R, int32_t G, int32_t B, int32_t A );

      virtual void create_frame(class size size, int32_t iFrameCount);
      virtual void set_frame2(void * lpdata, int32_t iFrame, int32_t iFrameCount);
      virtual void set_frame1(void * lpdata, int32_t iFrame, int32_t iFrameCount);
      virtual void get_frame(void * lpdata, int32_t iFrame, int32_t iFrameCount);
      virtual void xor_dib_frame2(void * lpdata, int32_t iFrame, int32_t iFrameCount);


      //virtual int32_t width();
      //virtual int32_t height();
      inline int64_t area() { return m_size.area(); }
      virtual double pi();
      inline class size size() { return m_size; }

      virtual void write(::file::output_stream & ostream);
      virtual void read(::file::input_stream & istream);

      virtual bool update_window(::user::interaction_impl * pui, signal_details * pobj);
      virtual bool print_window(::user::interaction_impl * pui, signal_details * pobj);


      static void static_initialize();

      virtual COLORREF make_colorref(int32_t a, int32_t r, int32_t g, int32_t b);

   };

   class CLASS_DECL_AURA dib_sp :
      public smart_pointer < dib >
   {
   public:

      dib_sp()
      {
      }

      dib_sp(const smart_pointer < dib > & p) :
         smart_pointer < dib > (p)
      {
      }

      dib_sp(allocatorsp allocer) :
         smart_pointer < dib > (allocer)
      {
      }

      dib_sp & operator = (::draw2d::dib * pdib)
      {

         smart_pointer < dib >::operator = (pdib);

         return *this;

      }

   };

   class CLASS_DECL_AURA dibmap :
      virtual public map < class size, class size, ::draw2d::dib_sp, ::draw2d::dib_sp >
   {
   public:

      dibmap(sp(::aura::application) papp) :
         element(papp)
      {
      }


      inline ::draw2d::dib_sp & operator[](class size key)
      {
         ::draw2d::dib_sp & dib = map < class size, class size, ::draw2d::dib_sp, ::draw2d::dib_sp >::operator [](key);
         if(dib.is_null())
         {
            dib.alloc(allocer());
            dib->create(key);
         }
         return dib;
      }


   };


} // namespace draw2d


namespace comparison
{


   template < >
   class CLASS_DECL_AURA hash < const ::draw2d::dib::descriptor & >
   {
   public:

      inline static UINT HashKey (const ::draw2d::dib::descriptor & key)
      {
         UINT ui = (UINT) key.m_etype;
         if(key.m_etype == ::draw2d::dib::type_plain_color)
         {
            ui |= key.m_cr;
         }
         return ui;
      }

   };


} // namespace axis - for class ::comparison::hash const < ::draw2d::dib::descriptor & >



namespace draw2d
{

   class CLASS_DECL_AURA dibmap_ex1 :
      virtual public map < ::draw2d::dib::descriptor, const ::draw2d::dib::descriptor &, ::draw2d::dib_sp, ::draw2d::dib_sp >
   {
   public:


      int32_t m_iLimitCount;


      dibmap_ex1(sp(::aura::application) papp, int32_t iLimitCount = 500) :
         element(papp)
      {

         m_iLimitCount = iLimitCount;

      }


      inline ::draw2d::dib_sp & operator[](class ::draw2d::dib::descriptor key)
      {
         while(get_count() > m_iLimitCount)
         {
            remove_bigger();
         }
         ::draw2d::dib_sp & dib = map < ::draw2d::dib::descriptor, const ::draw2d::dib::descriptor &, ::draw2d::dib_sp, ::draw2d::dib_sp >::operator [](key);
         if(dib.is_null())
         {
            dib.alloc(allocer());
            dib->create(key.m_size);
         }
         return dib;
      }


      void remove_bigger()
      {

         ::draw2d::dib::descriptor keyFind;
         int64_t iAreaMax = 0;
         assoc * passoc = PGetFirstAssoc();
         while(passoc != NULL)
         {
            if(passoc->m_element2->get_ref_count() <= 1 && passoc->m_element2->area() > iAreaMax)
            {
               iAreaMax = passoc->m_element2->area();
               keyFind = passoc->m_element1;
            }
            passoc = passoc->m_pnext;
         }

         if(iAreaMax > 0)
         {
            remove_key(keyFind);
         }
         else
         {
            remove_key(PGetFirstAssoc()->m_element1);
         }
      }

      

   };

} // namespace draw2d





