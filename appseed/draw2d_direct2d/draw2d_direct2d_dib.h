#pragma once


namespace draw2d_direct2d
{


   //////////////////////////////////////////////////////////////////////
   //   Creator : El Barto (ef00@luc.ac.be)
   //   Location : http://www.luc.ac.be/~ef00/ebgfx
   //   Date : 09-04-98
   //////////////////////////////////////////////////////////////////////

   class CLASS_DECL_DRAW2D_DIRECT2D dib :
      virtual public ::draw2d::dib
   {
   public:

      static float Cosines[360];
      static float Sines[360];
      static int64_t CosN[360]; // * 1 << 31
      static int64_t SinN[360]; 
      static int64_t Cos10N[10]; // until 10 degress
      static int64_t Sin10N[10]; // more precision * 1 << 34
      static double dPi;

      BITMAPINFO           m_info;
      ::draw2d::bitmap_sp      m_spbitmap;
      ::draw2d::bitmap_sp      m_spbitmapMap;
      ::draw2d::graphics_sp    m_spgraphics;
      ::draw2d::graphics_sp    m_spgraphicsMap;
      //class size           m_size;
      bool                 m_bMapped;


      //HBITMAP              m_hbitmapOriginal;

      virtual ::draw2d::graphics * get_graphics();
      virtual ::draw2d::bitmap_sp get_bitmap();
      virtual ::draw2d::bitmap_sp detach_bitmap();


      virtual COLORREF * get_data();

      dib(application * papp);
      virtual void construct(int cx, int cy);
      virtual ~dib();

      static void s_initialize();
      void stretch_dib(::draw2d::dib * pdib);

      bool dc_select(bool bSelect = true);

      COLORREF GetAverageColor();
      bool Blend(::draw2d::dib *pdib, ::draw2d::dib * pdibA, int A);
      bool color_blend(COLORREF cr, BYTE bAlpha);
      void BitBlt(::draw2d::dib * pdib, int op);
      int cos(int i, int iAngle);
      int sin(int i, int iAngle);
      int cos10(int i, int iAngle);
      int sin10(int i, int iAngle);


      virtual void map(bool bApplyAlphaTransform = true); // some implementations may requrire to map to m_pcolorref before manipulate it
      virtual void unmap(); // some implementations may require to unmap from m_pcolorref to update *os* bitmap

      bool is_rgb_black();
      void xor(::draw2d::dib * pdib);

      void ToAlpha(int i);
      void ToAlphaAndFill(int i, COLORREF cr);
      void GrayToARGB(COLORREF cr);

      void from_alpha();
      void mult_alpha(::draw2d::dib * pdibWork, bool bPreserveAlpha = true);
      void set_rgb(int R, int G, int B);

      void rotate(::draw2d::dib * pdib, LPCRECT lpcrect, double dAngle, double dScale);
      void rotate(::draw2d::dib * pdib, double dAngle, double dScale);
      void Rotate034(::draw2d::dib * pdib, double dAngle, double dScale);


      void SetIconMask(::visual::icon * picon, int cx, int cy);
      void RadialFill(BYTE a, BYTE r, BYTE g, BYTE b, int x, int y, int iRadius);
      void RadialFill(
         BYTE a1, BYTE r1, BYTE g1, BYTE b1, // center colors
         BYTE a2, BYTE r2, BYTE g2, BYTE b2, // border colors
         int x, int y, int iRadius);

      uint32_t GetPixel(int x, int y);
      void Mask(COLORREF crMask, COLORREF crInMask, COLORREF crOutMask);
      void channel_mask(BYTE uchFind, BYTE uchSet, BYTE uchUnset, visual::rgba::echannel echannel);
      void transparent_color(color color);
      

      bool create(class size size);
      bool create(int iWidth, int iHeight);
      bool create(::draw2d::graphics * pgraphics);
      bool Destroy();

      virtual bool realize(::draw2d::graphics * pgraphics);
      virtual bool unrealize();
      virtual bool is_realized();
      virtual bool defer_realize(::draw2d::graphics * pgraphics);


      void DivideRGB(int iDivide);
      void DivideARGB(int iDivide);
      void DivideA(int iDivide);

      bool from(::draw2d::graphics * pgraphics);
      bool from(point ptDest, ::draw2d::graphics * pgraphics, point pt, class size sz);

      bool to(::draw2d::graphics * pgraphics, point pt, class size size, point ptSrc);
      
      virtual void fill_channel(int C, visual::rgba::echannel echannel);
      void Fill (int A, int R, int G, int B );
      //void Fill ( int R, int G, int B );
      void FillGlass ( int R, int G, int B, int A );
      void FillStippledGlass ( int R, int G, int B );
      void Invert();
      void channel_invert(visual::rgba::echannel echannel);
      void channel_multiply(visual::rgba::echannel echannel, double dRate);

      void Map (int ToRgb, int FromRgb );

      void copy( ::draw2d::dib *dib );
      void Paste ( ::draw2d::dib *dib );

      void Blend ( ::draw2d::dib *dib, int A );
      void Darken ( ::draw2d::dib *dib );
      void Difference ( ::draw2d::dib *dib );
      void Lighten ( ::draw2d::dib *dib );
      void Multiply ( ::draw2d::dib *dib );
      void Screen ( ::draw2d::dib *dib );

      void copy ( ::draw2d::dib *dib, int x, int y );
      void PasteRect ( ::draw2d::dib *dib, int x, int y );

      void FillRect ( int x, int y, int w, int h, int R, int G, int B );
      void FillGlassRect ( int x, int y, int w, int h, int R, int G, int B, int A );
      void FillStippledGlassRect ( int x, int y, int w, int h, int R, int G, int B );
      
      void BlendRect ( ::draw2d::dib *dib, int x, int y, int A );
      void DarkenRect ( ::draw2d::dib *dib, int x, int y );
      void DifferenceRect ( ::draw2d::dib *dib, int x, int y );
      void LightenRect ( ::draw2d::dib *dib, int x, int y );
      void MultiplyRect ( ::draw2d::dib *dib, int x, int y );
      void ScreenRect ( ::draw2d::dib *dib, int x, int y );

      void Line ( int x1, int y1, int x2, int y2, int R, int G, int B );
      void LineGlass ( int x1, int y1, int x2, int y2, int R, int G, int B, int A );

      void create_frame(class size size, int iFrameCount);
      void set_frame2(void * lpdata, int iFrame, int iFrameCount);
      void set_frame1(void * lpdata, int iFrame, int iFrameCount);
      void get_frame(void * lpdata, int iFrame, int iFrameCount);
      void xor_dib_frame2(void * lpdata, int iFrame, int iFrameCount);


      //int width();
      //int height();
      double pi();

      virtual bool from(::draw2d::graphics * pgraphics, FIBITMAP *pfibitmap, bool bUnloadFI);

#if !defined(METROWIN)
      bool update_window(::core::window * pwnd, signal_details * pobj);
      bool print_window(::core::window * pwnd, signal_details * pobj);
#endif

   };


} // namespace draw2d_direct2d




