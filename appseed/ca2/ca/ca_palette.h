#pragma once

namespace ca
{

#ifdef WINDOWS
   class CLASS_DECL_ca palette :
      virtual public ::ca::graphics_object
   {
   public:

      virtual BOOL CreatePalette(LPLOGPALETTE lpLogPalette);
      virtual BOOL CreateHalftonePalette(::ca::graphics * pgraphics);

      virtual int GetEntryCount();
      virtual UINT GetPaletteEntries(UINT nStartIndex, UINT nNumEntries,
            LPPALETTEENTRY lpPaletteColors) const;
      virtual UINT SetPaletteEntries(UINT nStartIndex, UINT nNumEntries,
            LPPALETTEENTRY lpPaletteColors);

   // Operations
      virtual void AnimatePalette(UINT nStartIndex, UINT nNumEntries,
            LPPALETTEENTRY lpPaletteColors);
      virtual UINT GetNearestPaletteIndex(COLORREF crColor) const;
      virtual BOOL ResizePalette(UINT nNumEntries);

   };

   typedef smart_pointer < palette > palette_sp;

#endif


} // namespace ca
