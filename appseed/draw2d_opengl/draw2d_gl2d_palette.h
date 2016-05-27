#pragma once

namespace draw2d_gl2d
{

   class CLASS_DECL_DRAW2D_GL2D palette : 
      virtual public ::draw2d_gl2d::object,
      virtual public ::draw2d::palette
   {
   public:
      static palette* from_handle(::aura::application * papp, HPALETTE hPalette);

      palette(::aura::application * papp);
      bool CreatePalette(LPLOGPALETTE lpLogPalette);
      bool CreateHalftonePalette(::draw2d::dib * pdib);

   // Attributes
      operator HPALETTE() const;
      int32_t GetEntryCount();
      UINT GetPaletteEntries(UINT nStartIndex, UINT nNumEntries,
            LPPALETTEENTRY lpPaletteColors) const;
      UINT SetPaletteEntries(UINT nStartIndex, UINT nNumEntries,
            LPPALETTEENTRY lpPaletteColors);

   // Operations
      void AnimatePalette(UINT nStartIndex, UINT nNumEntries,
            LPPALETTEENTRY lpPaletteColors);
      UINT GetNearestPaletteIndex(COLORREF crColor) const;
      bool ResizePalette(UINT nNumEntries);

   // Implementation
      virtual ~palette();
   };

} // namespace draw2d_gl2d