//#include "framework.h"
//#include "draw2d_object.h"
//#include "draw2d_palette.h"


namespace draw2d
{


   bool palette::CreatePalette(LPLOGPALETTE lpLogPalette)
   {
      UNREFERENCED_PARAMETER(lpLogPalette);
      ::exception::throw_interface_only(get_app());
      return false;
   }

   bool palette::CreateHalftonePalette(::draw2d::graphics * pgraphics)
   {
      UNREFERENCED_PARAMETER(pgraphics);
      ::exception::throw_interface_only(get_app());
      return false;
   }

   UINT palette::GetPaletteEntries(UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors) const
   {
      UNREFERENCED_PARAMETER(nStartIndex);
      UNREFERENCED_PARAMETER(nNumEntries);
      UNREFERENCED_PARAMETER(lpPaletteColors);
      ::exception::throw_interface_only(get_app());
      return 0;
   }

   UINT palette::SetPaletteEntries(UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors)
   {
      UNREFERENCED_PARAMETER(nStartIndex);
      UNREFERENCED_PARAMETER(nNumEntries);
      UNREFERENCED_PARAMETER(lpPaletteColors);
      ::exception::throw_interface_only(get_app());
      return 0;
   }

   void palette::AnimatePalette(UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors)
   {
      UNREFERENCED_PARAMETER(nStartIndex);
      UNREFERENCED_PARAMETER(nNumEntries);
      UNREFERENCED_PARAMETER(lpPaletteColors);
      ::exception::throw_interface_only(get_app());
      
   }

   UINT palette::GetNearestPaletteIndex(COLORREF crColor) const
   {
      UNREFERENCED_PARAMETER(crColor);
      ::exception::throw_interface_only(get_app());
      return 0;
   }

   bool palette::ResizePalette(UINT nNumEntries)
   {
      UNREFERENCED_PARAMETER(nNumEntries);
      ::exception::throw_interface_only(get_app());
      return false;
   }

   int32_t palette::GetEntryCount()
   {
      ::exception::throw_interface_only(get_app());
      return 0;
   }


} // namespace draw2d








