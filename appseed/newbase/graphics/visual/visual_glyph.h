#pragma once


namespace visual
{


   class CLASS_DECL_BASE glyph
   {
   public:


      UINT   m_ui;

      array <point_array, point_array &> m_pointsets;

#ifdef WINDOWSEX

      GLYPHMETRICS   m_gm;

#endif


      glyph();
      virtual ~glyph();


      void DrawGlyph(::draw2d::graphics * pdc, bool bFill, double dRateX, LPPOINT lppointoffset);

#ifdef WINDOWSEX

      void Initialize(LPTTPOLYGONHEADER lpph, uint32_t cbSize, int32_t iFontHiHeight);

#endif

      void GetGlyphRect(int32_t x, int32_t y, LPRECT lpRect);

      void clear();

      glyph & operator = (const glyph & glyph);

      bool operator <= (const glyph & glyph) const;


   };


} // namespace visual



