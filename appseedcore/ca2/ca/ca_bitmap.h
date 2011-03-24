#pragma once

namespace ca
{

   class CLASS_DECL_ca bitmap : 
      virtual public ::ca::graphics_object
   {
   public:

      virtual BOOL CreateBitmap(int nWidth, int nHeight, UINT nPlanes, UINT nBitcount,
            const void * lpBits);
      virtual BOOL CreateBitmapIndirect(LPBITMAP lpBitmap);
      virtual BOOL CreateCompatibleBitmap(::ca::graphics * pgraphics, int nWidth, int nHeight);
      virtual BOOL CreateDiscardableBitmap(::ca::graphics * pgraphics, int nWidth, int nHeight);
      virtual BOOL CreateDIBSection(::ca::graphics * pdc, const BITMAPINFO * lpbmi, UINT usage, void **ppvBits, HANDLE hSection, DWORD offset);
      virtual BOOL CreateDIBitmap(::ca::graphics * pdc, const BITMAPINFOHEADER *pbmih, DWORD flInit, const void *pjBits, const BITMAPINFO *pbmi, UINT iUsage);

      virtual int GetBitmap(BITMAP* pBitMap);

   // Operations
      virtual DWORD SetBitmapBits(DWORD dwCount, const void * lpBits);
      virtual DWORD GetBitmapBits(DWORD dwCount, LPVOID lpBits) const;
      virtual size SetBitmapDimension(int nWidth, int nHeight);
      virtual size GetBitmapDimension() const;

   #ifdef _DEBUG
      virtual void dump(dump_context & dumpcontext) const;
   #endif
   };

   typedef smart_pointer < bitmap > bitmap_sp;

} // namespace ca