#pragma once


namespace ca
{


   class CLASS_DECL_ca palette :
      virtual public ::ca::graphics_object
   {
   public:


      virtual bool CreatePalette(LPLOGPALETTE lpLogPalette);
      virtual bool CreateHalftonePalette(::ca::graphics * pgraphics);


      virtual int32_t GetEntryCount();
      virtual UINT GetPaletteEntries(UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors) const;
      virtual UINT SetPaletteEntries(UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors);


// Operations


      virtual void AnimatePalette(UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors);
      virtual UINT GetNearestPaletteIndex(COLORREF crColor) const;
      virtual bool ResizePalette(UINT nNumEntries);


   };


   typedef smart_pointer < palette > palette_sp;


} // namespace ca



