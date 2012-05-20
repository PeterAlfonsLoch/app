#pragma once

#include "primitive/img.h"

struct FIBITMAP;

namespace ca
{

   //////////////////////////////////////////////////////////////////////
   //   Creator : El Barto (ef00@luc.ac.be)
   //   Location : http://www.luc.ac.be/~ef00/ebgfx
   //   Date : 09-04-98
   //////////////////////////////////////////////////////////////////////

   class CLASS_DECL_ca dib :
      virtual public ::radix::object,
      virtual public ::ex1::byte_serializable
   {
   public:


      virtual ::ca::graphics * get_graphics();
      virtual ::ca::bitmap_sp get_bitmap();
      virtual ::ca::bitmap_sp detach_bitmap();


      virtual COLORREF * get_data();


      virtual void construct(int cx, int cy);

      virtual void stretch_dib(dib * pdib);


      virtual bool dc_select(bool bSelect = true);

      virtual bool from(::ca::graphics * pgraphics, FIBITMAP * pfibitmap, bool bUnloadFI);

      virtual COLORREF GetAverageColor();
      virtual bool blend(dib * pdib, dib * pdibRate);
      virtual bool Blend(dib *pdib, dib * pdibA, int A);
      virtual bool bitmap_blend(::ca::graphics * pgraphics, LPCRECT lprect);
      virtual bool color_blend(COLORREF cr, BYTE bAlpha);
      virtual void BitBlt(dib * pdib, int op);
      virtual int cos(int i, int iAngle);
      virtual int sin(int i, int iAngle);
      virtual int cos10(int i, int iAngle);
      virtual int sin10(int i, int iAngle);

      virtual bool is_rgb_black();
      virtual void do_xor(dib * pdib);

      virtual void ToAlpha(int i);
      virtual void ToAlphaAndFill(int i, COLORREF cr);
      virtual void GrayToARGB(COLORREF cr);

      virtual void from_alpha();
      virtual void mult_alpha(::ca::dib * pdibWork, bool bPreserveAlpha = true);

      virtual void rotate(dib * pdib, LPCRECT lpcrect, double dAngle, double dScale);
      virtual void rotate(dib * pdib, double dAngle, double dScale);
      virtual void Rotate034(dib * pdib, double dAngle, double dScale);


      virtual void set_rgb(int R, int G, int B);
      virtual bool rgb_from(::ca::dib * pdib);



      virtual void SetIconMask(::visual::icon * picon, int cx, int cy);
      virtual void RadialFill(BYTE a, BYTE r, BYTE g, BYTE b, int x, int y, int iRadius);
      virtual void RadialFill(
         BYTE a1, BYTE r1, BYTE g1, BYTE b1, // center colors
         BYTE a2, BYTE r2, BYTE g2, BYTE b2, // border colors
         int x, int y, int iRadius);

      virtual DWORD GetPixel(int x, int y);
      virtual void Mask(COLORREF crMask, COLORREF crInMask, COLORREF crOutMask);
      virtual void channel_mask(BYTE uchFind, BYTE uchSet, BYTE uchUnset, visual::rgba::echannel echannel);
      virtual void transparent_color(color color);


      virtual bool create(size size);
      virtual bool create(int iWidth, int iHeight);
      virtual bool create(::ca::graphics * pdc);
      virtual bool Destroy();


      virtual void DivideRGB(int iDivide);
      virtual void DivideARGB(int iDivide);
      virtual void DivideA(int iDivide);

      virtual bool from(::ca::dib * pdib);
      virtual bool from(::ca::graphics * pdc);
      virtual bool from(point ptDst, ::ca::graphics * pdc, point ptSrc, size size);

      virtual bool to(::ca::graphics * pgraphics);
      virtual bool to(::ca::graphics * pgraphics, point pt);
      virtual bool to(::ca::graphics * pgraphics, size size);
      virtual bool to(::ca::graphics * pgraphics, point pt, size size);
      virtual bool to(::ca::graphics * pgraphics, LPCRECT lpcrect);
      virtual bool to(::ca::graphics * pgraphics, point pt, size size, point ptSrc);


      virtual bool pixelate(int iSize);



      virtual void fill_channel(int C, visual::rgba::echannel echannel);
      virtual void FillByte(unsigned char uch);
      virtual void Fill (int A, int R, int G, int B );
      virtual void Fill ( int R, int G, int B );
      virtual void FillGlass ( int R, int G, int B, int A );
      virtual void FillStippledGlass ( int R, int G, int B );
      virtual void Invert();
      virtual void channel_invert(visual::rgba::echannel echannel);
      virtual void channel_multiply(visual::rgba::echannel echannel, double dRate);
      virtual void channel_multiply(visual::rgba::echannel echannel, ::ca::dib * pdib);
      virtual void channel_lighten(visual::rgba::echannel echannel, ::ca::dib * pdib);
      virtual void channel_darken(visual::rgba::echannel echannel, ::ca::dib * pdib);
      virtual void channel_from(visual::rgba::echannel echannel, ::ca::dib * pdib);
      virtual void channel_copy(visual::rgba::echannel echannelDst, visual::rgba::echannel echannelSrc);

      virtual void Map (int ToRgb, int FromRgb );

      virtual void copy( dib *dib );
      virtual void Paste ( dib *dib );

      virtual void Blend ( dib *dib, int A );
      virtual void Darken ( dib *dib );
      virtual void Difference ( dib *dib );
      virtual void Lighten ( dib *dib );
      virtual void Multiply ( dib *dib );
      virtual void Screen ( dib *dib );

      virtual void copy ( dib *dib, int x, int y );
      virtual void PasteRect ( dib *dib, int x, int y );

      virtual void FillRect ( int x, int y, int w, int h, int R, int G, int B );
      virtual void FillGlassRect ( int x, int y, int w, int h, int R, int G, int B, int A );
      virtual void FillStippledGlassRect ( int x, int y, int w, int h, int R, int G, int B );

      virtual void BlendRect ( dib *dib, int x, int y, int A );
      virtual void DarkenRect ( dib *dib, int x, int y );
      virtual void DifferenceRect ( dib *dib, int x, int y );
      virtual void LightenRect ( dib *dib, int x, int y );
      virtual void MultiplyRect ( dib *dib, int x, int y );
      virtual void ScreenRect ( dib *dib, int x, int y );

      virtual void horizontal_line(int y, int R, int G, int B, int A = 0, int x1 = 0, int x2 = -1);
      virtual void Line ( int x1, int y1, int x2, int y2, int R, int G, int B );
      virtual void LineGlass ( int x1, int y1, int x2, int y2, int R, int G, int B, int A );

      virtual void create_frame(size size, int iFrameCount);
      virtual void set_frame2(void * lpdata, int iFrame, int iFrameCount);
      virtual void set_frame1(void * lpdata, int iFrame, int iFrameCount);
      virtual void get_frame(void * lpdata, int iFrame, int iFrameCount);
      virtual void xor_dib_frame2(void * lpdata, int iFrame, int iFrameCount);


      virtual int width();
      virtual int height();
      virtual int64_t area();
      virtual double pi();
      virtual class size size();

      virtual void write(::ex1::byte_output_stream & ostream);
      virtual void read(::ex1::byte_input_stream & istream);


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
