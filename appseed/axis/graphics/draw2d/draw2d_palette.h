#pragma once


namespace draw2d
{


   class CLASS_DECL_AXIS palette :
      virtual public ::draw2d::object
   {
   public:


      virtual bool CreatePalette(LPLOGPALETTE lpLogPalette);
      virtual bool CreateHalftonePalette(::draw2d::graphics * pgraphics);


      virtual int32_t GetEntryCount();
      virtual UINT GetPaletteEntries(UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors) const;
      virtual UINT SetPaletteEntries(UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors);


// Operations


      virtual void AnimatePalette(UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors);
      virtual UINT GetNearestPaletteIndex(COLORREF crColor) const;
      virtual bool ResizePalette(UINT nNumEntries);


   };


   typedef smart_pointer < palette > palette_sp;


} // namespace draw2d



