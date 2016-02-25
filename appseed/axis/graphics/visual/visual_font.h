#pragma once

namespace visual
{

   class CLASS_DECL_AXIS font :
      virtual public ::object
   {
   public:


      enum Effects
      {
         EffectSimple = 0,
         EffectEmbossed = 1
      };

      ::draw2d::text_metric			m_tm;

      int32_t						m_iFontHiHeight;
      ::draw2d::graphics *			m_pDC;

      glyph_set						m_glyphset;

      ::draw2d::font_sp				m_spfont;
      ::draw2d::font *				m_pfontOld;

      LPBYTE						m_lpBitmap;


      font(::aura::application * papp);
      virtual ~font();

      glyph * GetGlyph(WCHAR wchar);
      glyph * GetGlyph(CHAR ch);
      glyph * GetGlyph(UINT ui);
      //glyph * GetNewGlyph();

      void OnUpdateFont();
      void OnSetFont();
      int32_t GetMegaHeight();
      void AddGlyphs(const char * lpStr);
      bool AddGlyph(WCHAR wchar);
      bool AddGlyph(CHAR ch);
      bool AddGlyph(UINT ui);


      void AddXFGlyphs(string2a & str2aTokens);
      //void OffsetDataPointers(LPVOID lpData);


      void UnselectFont();
      void ClearDC();
      void SelectFont();
      void SetDC(::draw2d::graphics * pdc);
      void EmbossedTextOut(
         ::draw2d::dib                  * pdib,
         const RECT &               lpcrect,
         double               dRateX,
         double               dHeight,
         string                 &str);

      void EmbossedTextOut(
         ::draw2d::dib                     * pdib,
         const RECT &               lpcrect,
         double               dRateX,
         double               dHeight,
         string                 &str,
         LPINT                 lpiCharsPositions,
         int32_t                     iCharsPositions,
         int32_t                  iOffset);

      void SimpleTextOut(
         ::draw2d::dib                     *pdib,
         int32_t                     x,
         int32_t                     y,
         string                 &str,
         LPINT                lpiCharsPositions,
         int32_t                     iCharsPositions);

      void TextOutEx(
         ::draw2d::dib                  *pdib,
         const RECT &               lpcrect,
         double               dRateX,
         double               dHeight,
         string              &str,
         LPINT                  lpiCharsPositions,
         int32_t                  iCharsPositions,
         int32_t                  iOffset,
         int32_t                  iEffect);

      ::draw2d::font * GetFont();
      void clear();

   };

} // namespace visual
