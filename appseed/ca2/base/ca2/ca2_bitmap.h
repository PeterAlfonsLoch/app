#pragma once


#include "ca_graphics_object.h"


namespace ca2
{


   class CLASS_DECL_ca2 bitmap :
      virtual public ::ca2::graphics_object
   {
   public:


      virtual bool CreateBitmap(::ca2::graphics * pdc, int32_t nWidth, int32_t nHeight, UINT nPlanes, UINT nBitcount, const void * lpBits, int32_t stride);
      virtual bool CreateBitmapIndirect(::ca2::graphics * pdc, LPBITMAP lpBitmap);
      virtual bool CreateCompatibleBitmap(::ca2::graphics * pgraphics, int32_t nWidth, int32_t nHeight);
      virtual bool CreateDiscardableBitmap(::ca2::graphics * pgraphics, int32_t nWidth, int32_t nHeight);
      virtual bool CreateDIBSection(::ca2::graphics * pdc, const BITMAPINFO * lpbmi, UINT usage, void **ppvBits, int * stride, HANDLE hSection, uint32_t offset);
      virtual bool CreateDIBitmap(::ca2::graphics * pdc, const BITMAPINFOHEADER *pbmih, uint32_t flInit, const void *pjBits, const BITMAPINFO *pbmi, UINT iUsage);

      virtual bool attach(void * posdata);
      virtual void * detach();

      virtual class size SetBitmapDimension(int32_t nWidth, int32_t nHeight);
      virtual class size set_size(class size size);

      virtual class size GetBitmapDimension() const;
      virtual class size get_size() const;
      virtual class size size() const;

   // Operations
      virtual uint32_t SetBitmapBits(uint32_t dwCount, const void * lpBits);
      virtual uint32_t GetBitmapBits(uint32_t dwCount, LPVOID lpBits) const;

      virtual void dump(dump_context & dumpcontext) const;


   };


   typedef ::ca::smart_pointer < bitmap > bitmap_sp;


} // namespace ca2

