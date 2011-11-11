#include "StdAfx.h"

namespace ca
{

   BOOL bitmap::CreateBitmap(int nWidth, int nHeight, UINT nPlanes,
      UINT nBitcount, const void * lpBits)
   {
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      UNREFERENCED_PARAMETER(nPlanes);
      UNREFERENCED_PARAMETER(nBitcount);
      UNREFERENCED_PARAMETER(lpBits);
      throw not_implemented_exception();   
   }
   BOOL bitmap::CreateBitmapIndirect(LPBITMAP lpBitmap)
   {
      UNREFERENCED_PARAMETER(lpBitmap);
      throw not_implemented_exception();   
   }
   BOOL bitmap::CreateDIBSection(::ca::graphics * pdc, const BITMAPINFO * lpbmi, UINT usage, void **ppvBits, HANDLE hSection, DWORD offset)
   {
      UNREFERENCED_PARAMETER(pdc);
      UNREFERENCED_PARAMETER(lpbmi);
      UNREFERENCED_PARAMETER(usage);
      UNREFERENCED_PARAMETER(ppvBits);
      UNREFERENCED_PARAMETER(hSection);
      UNREFERENCED_PARAMETER(offset);
      throw not_implemented_exception();   
   }
   BOOL bitmap::CreateDIBitmap(::ca::graphics * pdc, const BITMAPINFOHEADER *pbmih, DWORD flInit, const void *pjBits, const BITMAPINFO *pbmi, UINT iUsage)
   {
      UNREFERENCED_PARAMETER(pdc);
      UNREFERENCED_PARAMETER(pbmih);
      UNREFERENCED_PARAMETER(flInit);
      UNREFERENCED_PARAMETER(pjBits);
      UNREFERENCED_PARAMETER(pbmi);
      UNREFERENCED_PARAMETER(iUsage);
      throw not_implemented_exception();   
   }

   DWORD bitmap::SetBitmapBits(DWORD dwCount, const void * lpBits)
   {
      UNREFERENCED_PARAMETER(dwCount);
      UNREFERENCED_PARAMETER(lpBits);
      throw not_implemented_exception();   
   }
   DWORD bitmap::GetBitmapBits(DWORD dwCount, LPVOID lpBits) const
   {
      UNREFERENCED_PARAMETER(dwCount);
      UNREFERENCED_PARAMETER(lpBits);
      throw not_implemented_exception();   
   }
   size bitmap::SetBitmapDimension(int nWidth, int nHeight)
   {
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      throw not_implemented_exception();   
   }
   size bitmap::GetBitmapDimension() const
   {
      throw not_implemented_exception();   
   }

   BOOL bitmap::CreateCompatibleBitmap(::ca::graphics * pgraphics, int nWidth, int nHeight)
   {
      UNREFERENCED_PARAMETER(pgraphics);
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      throw not_implemented_exception();   
   }
   BOOL bitmap::CreateDiscardableBitmap(::ca::graphics * pgraphics, int nWidth, int nHeight)
   {
      UNREFERENCED_PARAMETER(pgraphics);
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      throw not_implemented_exception();   
   }
   int bitmap::GetBitmap(BITMAP* pBitMap)
   {
      UNREFERENCED_PARAMETER(pBitMap);
      throw not_implemented_exception();   
   }

   #ifdef _DEBUG
   void ::ca::bitmap::dump(dump_context & dumpcontext) const
   {
      UNREFERENCED_PARAMETER(dumpcontext);
      throw interface_only_exception();
   }
   #endif


} // namespace ca