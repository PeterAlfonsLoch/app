#pragma once

namespace metrowin
{

   class CLASS_DECL_metrowin palette : 
      virtual public ::metrowin::graphics_object,
      virtual public ::ca2::palette
   {
   public:
      static palette* from_handle(::ca2::application * papp, HPALETTE hPalette);

      palette(::ca2::application * papp);
      bool CreatePalette(LPLOGPALETTE lpLogPalette);
      bool CreateHalftonePalette(::ca2::graphics * pgraphics);

   // Attributes
      operator HPALETTE() const;
      int GetEntryCount();
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

} // namespace metrowin