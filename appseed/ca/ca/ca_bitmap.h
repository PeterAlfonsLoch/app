#pragma once


#include "ca_graphics_object.h"


namespace ca
{


   class CLASS_DECL_ca bitmap :
      virtual public ::ca::graphics_object
   {
   public:


      virtual bool CreateBitmap(::ca::graphics * pdc, int nWidth, int nHeight, UINT nPlanes, UINT nBitcount, const void * lpBits);
      virtual bool CreateBitmapIndirect(::ca::graphics * pdc, LPBITMAP lpBitmap);
      virtual bool CreateCompatibleBitmap(::ca::graphics * pgraphics, int nWidth, int nHeight);
      virtual bool CreateDiscardableBitmap(::ca::graphics * pgraphics, int nWidth, int nHeight);
      virtual bool CreateDIBSection(::ca::graphics * pdc, const BITMAPINFO * lpbmi, UINT usage, void **ppvBits, HANDLE hSection, DWORD offset);
      virtual bool CreateDIBitmap(::ca::graphics * pdc, const BITMAPINFOHEADER *pbmih, DWORD flInit, const void *pjBits, const BITMAPINFO *pbmi, UINT iUsage);

      virtual bool attach(void * posdata);
      virtual void * detach();

      virtual class size SetBitmapDimension(int nWidth, int nHeight);
      virtual class size set_size(class size size);

      virtual class size GetBitmapDimension() const;
      virtual class size get_size() const;
      virtual class size size() const;

   // Operations
      virtual DWORD SetBitmapBits(DWORD dwCount, const void * lpBits);
      virtual DWORD GetBitmapBits(DWORD dwCount, LPVOID lpBits) const;

      virtual void dump(dump_context & dumpcontext) const;


   };


   typedef smart_pointer < bitmap > bitmap_sp;


} // namespace ca

