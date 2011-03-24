#pragma once

namespace visual
{

   class CLASS_DECL_ca font :
      virtual public ::radix::object
   {
   public:
      enum Effects
      {
         EffectSimple = 0,
         EffectEmbossed = 1
      };
   private:
      int            m_iFontHiHeight;
      //static const DWORD m_dwAllocationAddUp;
      //LPVOID         m_lpData;
      //DWORD         m_dwSize;
      //DWORD         m_dwAllocation;
      //int            m_iUsedGlyphs;
      ::ca::graphics *         m_pDC;
      //static mutex m_mutex;

      glyph_set      m_glyphset;

   protected:
      ::ca::font_sp         m_pFont;
      ::ca::font *         m_pOldFont;

      LPBYTE         m_lpBitmap;

   public:

      font(::ca::application * papp);
      virtual ~font();

   protected:
      glyph * GetGlyph(WCHAR wchar);
      glyph * GetGlyph(CHAR ch);
      glyph * GetGlyph(UINT ui);
      //glyph * GetNewGlyph();

   public:
      void OnUpdateFont();
      void OnSetFont();
      int GetMegaHeight();
      void AddGlyphs(const char * lpStr);
      BOOL AddGlyph(WCHAR wchar);
      BOOL AddGlyph(CHAR ch);
      BOOL AddGlyph(UINT ui);
      TEXTMETRIC      m_tm;
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
         int                     iCharsPositions,
         int                  iOffset);

      void SimpleTextOut(
         ::ca::graphics                     *pdc,
         int                     x,
         int                     y,
         string                 &str,   
         LPINT                lpiCharsPositions,
         int                     iCharsPositions);

      void TextOutEx(
         ::ca::graphics                  *pdc,
         LPCRECT               lpcrect,
         double               dRateX,
         double               dHeight,
         string              &str,   
         LPINT                  lpiCharsPositions,
         int                  iCharsPositions,
         int                  iOffset,
         int                  iEffect);

      ::ca::font * GetFont();
      void clear();
      void SetFont(::ca::font *pFont);

   };

} // namespace visual
