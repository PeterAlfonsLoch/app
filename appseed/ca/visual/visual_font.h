#pragma once

namespace visual
{

   class CLASS_DECL_ca font :
      virtual public ::ca::object
   {
   public:


      enum Effects
      {
         EffectSimple = 0,
         EffectEmbossed = 1
      };

//#ifdef WINDOWS
      TEXTMETRIC      m_tm;
//#endif

      int32_t            m_iFontHiHeight;
      //static const uint32_t m_dwAllocationAddUp;
      //LPVOID         m_lpData;
      //uint32_t         m_dwSize;
      //uint32_t         m_dwAllocation;
      //int32_t            m_iUsedGlyphs;
      ::ca::graphics *         m_pDC;
      //static mutex m_mutex;

      glyph_set      m_glyphset;

      ::ca::font_sp        m_spfont;
      ::ca::font *         m_pfontOld;

      LPBYTE         m_lpBitmap;


      font(sp(::ca::application) papp);
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


      void AddXFGlyphs(string2a *p2DTokens);
      //void OffsetDataPointers(LPVOID lpData);


      void UnselectFont();
      void ClearDC();
      void SelectFont();
      void SetDC(::ca::graphics * pgraphics);
      void EmbossedTextOut(
         ::ca::graphics                  * pgraphics,
         LPCRECT               lpcrect,
         double               dRateX,
         double               dHeight,
         string                 &str);

      void EmbossedTextOut(
         ::ca::graphics                     *pdc,
         LPCRECT               lpcrect,
         double               dRateX,
         double               dHeight,
         string                 &str,
         LPINT                 lpiCharsPositions,
         int32_t                     iCharsPositions,
         int32_t                  iOffset);

      void SimpleTextOut(
         ::ca::graphics                     *pdc,
         int32_t                     x,
         int32_t                     y,
         string                 &str,
         LPINT                lpiCharsPositions,
         int32_t                     iCharsPositions);

      void TextOutEx(
         ::ca::graphics                  *pdc,
         LPCRECT               lpcrect,
         double               dRateX,
         double               dHeight,
         string              &str,
         LPINT                  lpiCharsPositions,
         int32_t                  iCharsPositions,
         int32_t                  iOffset,
         int32_t                  iEffect);

      ::ca::font * GetFont();
      void clear();

   };

} // namespace visual
