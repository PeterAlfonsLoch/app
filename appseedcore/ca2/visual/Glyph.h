#pragma once

namespace visual
{

   class CLASS_DECL_ca glyph  
   {
   public:
      glyph();
      virtual ~glyph();

   public:
      UINT   m_ui;
      base_array <point_array, point_array &> m_pointsets;
      GLYPHMETRICS   m_gm;

   public:   
      void DrawGlyph(
         ::ca::graphics *      pdc,
         bool      bFill,
         double      dRateX,
         LPPOINT      lppointoffset);
      
      void Initialize(
         LPTTPOLYGONHEADER lpph,
         DWORD cbSize,
         int iFontHiHeight);
      
      void GetGlyphRect(
         int x,
         int y,
         LPRECT lpRect);

      void clear();

      glyph & operator = (const glyph & glyph);
      bool operator <= (const glyph & glyph) const;


   };

} // namespace visual
