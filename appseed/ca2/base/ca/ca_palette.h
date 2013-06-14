#pragma once


namespace ca2
{


   class CLASS_DECL_ca2 palette :
      virtual public ::ca2::graphics_object
   {
   public:


      virtual bool CreatePalette(LPLOGPALETTE lpLogPalette);
      virtual bool CreateHalftonePalette(::ca2::graphics * pgraphics);


      virtual int32_t GetEntryCount();
      virtual UINT GetPaletteEntries(UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors) const;
      virtual UINT SetPaletteEntries(UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors);


// Operations


      virtual void AnimatePalette(UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors);
      virtual UINT GetNearestPaletteIndex(COLORREF crColor) const;
      virtual bool ResizePalette(UINT nNumEntries);


   };


   typedef ::ca::smart_pointer < palette > palette_sp;


} // namespace ca2



