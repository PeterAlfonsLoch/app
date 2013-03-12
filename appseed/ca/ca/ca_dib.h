#pragma once


struct FIBITMAP;


namespace ca
{


   //////////////////////////////////////////////////////////////////////
   //   Creator : El Barto (ef00@luc.ac.be)
   //   Location : http://www.luc.ac.be/~ef00/ebgfx
   //   Date : 09-04-98
   //////////////////////////////////////////////////////////////////////


   class CLASS_DECL_ca dib :
      virtual public ::ca::object,
      virtual public ::ca::byte_serializable
   {
   public:


      int32_t         cx;
      int32_t         cy;
      int32_t         scan;


      dib();
      virtual ~dib();


      virtual ::ca::graphics * get_graphics();
      virtual ::ca::bitmap_sp get_bitmap();
      virtual ::ca::bitmap_sp detach_bitmap();


      virtual COLORREF * get_data();


      virtual void construct(int32_t cx, int32_t cy);

      virtual void stretch_dib(dib * pdib);


      virtual bool dc_select(bool bSelect = true);

      virtual bool from(::ca::graphics * pgraphics, FIBITMAP * pfibitmap, bool bUnloadFI);

      virtual COLORREF GetAverageColor();
      virtual bool blend(dib * pdib, dib * pdibRate);
      virtual bool Blend(dib *pdib, dib * pdibA, int32_t A);
      virtual bool bitmap_blend(::ca::graphics * pgraphics, LPCRECT lprect);
      virtual bool color_blend(COLORREF cr, BYTE bAlpha);
      virtual void BitBlt(dib * pdib, int32_t op);
      virtual int32_t cos(int32_t i, int32_t iAngle);
      virtual int32_t sin(int32_t i, int32_t iAngle);
      virtual int32_t cos10(int32_t i, int32_t iAngle);
      virtual int32_t sin10(int32_t i, int32_t iAngle);

      virtual void map(); // some implementations may requrire to map to m_pcolorref before manipulate it
      virtual void unmap(); // some implementations may require to unmap from m_pcolorref to update *os* bitmap


      virtual bool is_rgb_black();
      virtual void do_xor(dib * pdib);

      virtual void ToAlpha(int32_t i);
      virtual void ToAlphaAndFill(int32_t i, COLORREF cr);
      virtual void GrayToARGB(COLORREF cr);

      virtual void from_alpha();
      virtual void mult_alpha(::ca::dib * pdibWork, bool bPreserveAlpha = true);

      virtual void rotate(dib * pdib, LPCRECT lpcrect, double dAngle, double dScale);
      virtual void rotate(dib * pdib, double dAngle, double dScale);
      virtual void Rotate034(dib * pdib, double dAngle, double dScale);


      virtual void set_rgb(int32_t R, int32_t G, int32_t B);
      virtual bool rgb_from(::ca::dib * pdib);



      virtual void SetIconMask(::visual::icon * picon, int32_t cx, int32_t cy);
      virtual void RadialFill(BYTE a, BYTE r, BYTE g, BYTE b, int32_t x, int32_t y, int32_t iRadius);
      virtual void RadialFill(
         BYTE a1, BYTE r1, BYTE g1, BYTE b1, // center colors
         BYTE a2, BYTE r2, BYTE g2, BYTE b2, // border colors
         int32_t x, int32_t y, int32_t iRadius);

      virtual uint32_t GetPixel(int32_t x, int32_t y);
      virtual void Mask(COLORREF crMask, COLORREF crInMask, COLORREF crOutMask);
      virtual void channel_mask(BYTE uchFind, BYTE uchSet, BYTE uchUnset, visual::rgba::echannel echannel);
      virtual void transparent_color(color color);


      virtual bool create(size);
      virtual bool create(int32_t iWidth, int32_t iHeight);
      virtual bool create(::ca::graphics * pdc);
      virtual bool Destroy();

      virtual bool realize(::ca::graphics * pdc);
      virtual bool unrealize();
      virtual bool is_realized();
      virtual bool defer_realize(::ca::graphics * pdc);


      virtual void DivideRGB(int32_t iDivide);
      virtual void DivideARGB(int32_t iDivide);
      virtual void DivideA(int32_t iDivide);

      virtual bool from(::ca::dib * pdib);
      virtual bool from(::ca::graphics * pdc);
      virtual bool from(point ptDst, ::ca::graphics * pdc, point ptSrc, size size);

      virtual bool to(::ca::graphics * pgraphics);
      virtual bool to(::ca::graphics * pgraphics, point pt);
      virtual bool to(::ca::graphics * pgraphics, size size);
      virtual bool to(::ca::graphics * pgraphics, point pt, size size);
      virtual bool to(::ca::graphics * pgraphics, LPCRECT lpcrect);
      virtual bool to(::ca::graphics * pgraphics, point pt, size size, point ptSrc);


      virtual bool pixelate(int32_t iSize);



      virtual void fill_channel(int32_t C, visual::rgba::echannel echannel);
      virtual void FillByte(uchar uch);
      virtual void Fill (int32_t A, int32_t R, int32_t G, int32_t B );
//      virtual void Fill ( int32_t R, int32_t G, int32_t B );
      virtual void set ( int32_t R, int32_t G, int32_t B );
      virtual void FillGlass ( int32_t R, int32_t G, int32_t B, int32_t A );
      virtual void FillStippledGlass ( int32_t R, int32_t G, int32_t B );
      virtual void Invert();
      virtual void channel_invert(visual::rgba::echannel echannel);
      virtual void channel_multiply(visual::rgba::echannel echannel, double dRate);
      virtual void channel_multiply(visual::rgba::echannel echannel, ::ca::dib * pdib);
      virtual void channel_lighten(visual::rgba::echannel echannel, ::ca::dib * pdib);
      virtual void channel_darken(visual::rgba::echannel echannel, ::ca::dib * pdib);
      virtual void channel_from(visual::rgba::echannel echannel, ::ca::dib * pdib);
      virtual void channel_copy(visual::rgba::echannel echannelDst, visual::rgba::echannel echannelSrc);

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

      virtual void create_frame(size size, int32_t iFrameCount);
      virtual void set_frame2(void * lpdata, int32_t iFrame, int32_t iFrameCount);
      virtual void set_frame1(void * lpdata, int32_t iFrame, int32_t iFrameCount);
      virtual void get_frame(void * lpdata, int32_t iFrame, int32_t iFrameCount);
      virtual void xor_dib_frame2(void * lpdata, int32_t iFrame, int32_t iFrameCount);


      //virtual int32_t width();
      //virtual int32_t height();
      inline int64_t area() { return cx * cy; }
      virtual double pi();
      inline class size size() { return ::size(cx, cy); }

      virtual void write(::ca::byte_output_stream & ostream);
      virtual void read(::ca::byte_input_stream & istream);


   };

   typedef smart_pointer < dib > dib_sp;


   class CLASS_DECL_ca dibmap :
      virtual public ::collection::map < size, size, ::ca::dib_sp, ::ca::dib_sp >
   {
   public:

      dibmap(::ca::application * papp) :
         ca(papp)
      {
      }


      inline ::ca::dib_sp & operator[](class size key)
      {
         ::ca::dib_sp & dib = ::collection::map < class size, class size, ::ca::dib_sp, ::ca::dib_sp >::operator [](key);
         if(dib.is_null())
            dib.create(get_app());
         return dib;
      }

   };


} // namespace ca




