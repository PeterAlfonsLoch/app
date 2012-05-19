#include "framework.h"


namespace ca
{


#ifdef WINDOWS


   bool palette::CreatePalette(LPLOGPALETTE lpLogPalette)
   {
      UNREFERENCED_PARAMETER(lpLogPalette);
      throw interface_only_exception();
   }

   bool palette::CreateHalftonePalette(::ca::graphics * pgraphics)
   {
      UNREFERENCED_PARAMETER(pgraphics);
      throw interface_only_exception();
   }

   UINT palette::GetPaletteEntries(UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors) const
   {
      UNREFERENCED_PARAMETER(nStartIndex);
      UNREFERENCED_PARAMETER(nNumEntries);
      UNREFERENCED_PARAMETER(lpPaletteColors);
      throw interface_only_exception();
   }

   UINT palette::SetPaletteEntries(UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors)
   {
      UNREFERENCED_PARAMETER(nStartIndex);
      UNREFERENCED_PARAMETER(nNumEntries);
      UNREFERENCED_PARAMETER(lpPaletteColors);
      throw interface_only_exception();
   }

   void palette::AnimatePalette(UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors)
   {
      UNREFERENCED_PARAMETER(nStartIndex);
      UNREFERENCED_PARAMETER(nNumEntries);
      UNREFERENCED_PARAMETER(lpPaletteColors);
      throw interface_only_exception();
   }

   UINT palette::GetNearestPaletteIndex(COLORREF crColor) const
   {
      UNREFERENCED_PARAMETER(crColor);
      throw interface_only_exception();
   }

   bool palette::ResizePalette(UINT nNumEntries)
   {
      UNREFERENCED_PARAMETER(nNumEntries);
      throw interface_only_exception();
   }

   int palette::GetEntryCount()
   {
      throw interface_only_exception();
   }


#endif


} // namespace ca



