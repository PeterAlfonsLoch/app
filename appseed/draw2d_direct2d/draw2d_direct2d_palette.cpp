#include "framework.h"


namespace draw2d_direct2d
{


   palette::palette(::base::application * papp) :
      element(papp)
   { }
   palette::~palette()
   { }
   // palette
   palette::operator HPALETTE() const
   { 
      return (HPALETTE)(this == NULL ? NULL : get_os_data()); 
   }


   bool palette::CreatePalette(LPLOGPALETTE lpLogPalette)
   { 

      //return Attach(::CreatePalette(lpLogPalette)); 

      return FALSE;

   }


   bool palette::CreateHalftonePalette(::draw2d::graphics * pgraphics)
   {
      //ASSERT(pgraphics != NULL && (dynamic_cast<::draw2d_direct2d::graphics * >(pgraphics))->get_handle1() != NULL); 
      //return Attach(::CreateHalftonePalette((dynamic_cast<::draw2d_direct2d::graphics * >(pgraphics))->get_handle1())); 
      return FALSE;

   }
   UINT palette::GetPaletteEntries(UINT nStartIndex, UINT nNumEntries,
      LPPALETTEENTRY lpPaletteColors) const
   {

#ifdef WINDOWSEX
      ASSERT(get_os_data() != NULL); 
      return ::GetPaletteEntries((HPALETTE)get_os_data(), nStartIndex, nNumEntries, lpPaletteColors); 
#else
      throw todo(get_app());
#endif
   
   }
   UINT palette::SetPaletteEntries(UINT nStartIndex, UINT nNumEntries,
      LPPALETTEENTRY lpPaletteColors)
   { 
#ifdef WINDOWSEX
      ASSERT(get_os_data() != NULL); return ::SetPaletteEntries((HPALETTE)get_os_data(), nStartIndex,
   nNumEntries, lpPaletteColors); 
#else
      throw todo(get_app());
#endif
   
   }
   void palette::AnimatePalette(UINT nStartIndex, UINT nNumEntries,
      LPPALETTEENTRY lpPaletteColors)
   {
      throw todo(get_app());
      
   //   ASSERT(get_os_data() != NULL); ::AnimatePalette((HPALETTE)get_os_data(), nStartIndex, nNumEntries,
   //lpPaletteColors); 
   
   }

   UINT palette::GetNearestPaletteIndex(COLORREF crColor) const
   { 
      
      throw todo(get_app());

   /*   ASSERT(get_os_data() != NULL); return ::GetNearestPaletteIndex((HPALETTE)get_os_data(), crColor); 
   */
   }
   
   bool palette::ResizePalette(UINT nNumEntries)
   {
      throw todo(get_app());

      //ASSERT(get_os_data() != NULL); 
      //return ::ResizePalette((HPALETTE)get_os_data(), nNumEntries) != FALSE;
   }

   int palette::GetEntryCount()
   {
      throw todo(get_app());
      
   //   ASSERT(get_os_data() != NULL); WORD nEntries;
   //::GetObject((HANDLE) get_os_data(), sizeof(WORD), &nEntries); return (int)nEntries; 
   
   }

} // namespace draw2d_direct2d