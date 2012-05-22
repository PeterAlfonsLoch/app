//////////////////////////////////////////////////////////////////////
// draw_dib.cpp: implementation of the draw_dib class.
//
//   Creator : El Barto (ef00@luc.ac.be)
//   Location : http://www.luc.ac.be/~ef00/ebgfx
//   Date : 09-04-98
//
//////////////////////////////////////////////////////////////////////

#include "framework.h"

namespace ca
{

   bool draw_dib::open()
   {
      throw interface_only_exception();
   }

   bool draw_dib::close()
   {
      throw interface_only_exception();
   }

   bool draw_dib::Begin ( ::ca::graphics * pdc, int dxDest, int dyDest,
      LPBITMAPINFOHEADER lpbi, int dxSrc, int dySrc, UINT wFlags )
   {
      UNREFERENCED_PARAMETER(pdc);
      UNREFERENCED_PARAMETER(dxDest);
      UNREFERENCED_PARAMETER(dyDest);
      UNREFERENCED_PARAMETER(lpbi);
      UNREFERENCED_PARAMETER(dxSrc);
      UNREFERENCED_PARAMETER(dySrc);
      UNREFERENCED_PARAMETER(wFlags);
      throw interface_only_exception();
   }

   bool draw_dib::End ()
   {
      throw interface_only_exception();
   }

   bool draw_dib::draw ( ::ca::graphics * pdc, int xDst, int yDst,
      int dxDst, int dyDst, LPBITMAPINFOHEADER lpbi, LPVOID lpBits,
      int xSrc, int ySrc, int dxSrc, int dySrc, UINT wFlags )
   {
      UNREFERENCED_PARAMETER(pdc);
      UNREFERENCED_PARAMETER(xDst);
      UNREFERENCED_PARAMETER(yDst);
      UNREFERENCED_PARAMETER(dxDst);
      UNREFERENCED_PARAMETER(dyDst);
      UNREFERENCED_PARAMETER(lpbi);
      UNREFERENCED_PARAMETER(lpBits);
      UNREFERENCED_PARAMETER(xSrc);
      UNREFERENCED_PARAMETER(ySrc);
      UNREFERENCED_PARAMETER(dxSrc);
      UNREFERENCED_PARAMETER(dySrc);
      UNREFERENCED_PARAMETER(wFlags);
      throw interface_only_exception();
   }

   bool draw_dib::draw (::ca::dib *dib, ::ca::graphics * pgraphics, int xDst, int yDst,
      int dxDst, int dyDst, UINT wFlags)
   {
      UNREFERENCED_PARAMETER(dib);
      UNREFERENCED_PARAMETER(pgraphics);
      UNREFERENCED_PARAMETER(xDst);
      UNREFERENCED_PARAMETER(yDst);
      UNREFERENCED_PARAMETER(dxDst);
      UNREFERENCED_PARAMETER(dyDst);
      UNREFERENCED_PARAMETER(wFlags);
      throw interface_only_exception();
   }

   bool draw_dib::draw (
      ::ca::graphics * pdc,
      int      xDst,
      int      yDst,
      int      dxDst,
      int      dyDst,
      ::ca::dib *    pdib,
      int      xSrc,
      int      ySrc,
      int      dxSrc,
      int      dySrc,
      UINT     wFlags )
   {
      UNREFERENCED_PARAMETER(pdc);
      UNREFERENCED_PARAMETER(xDst);
      UNREFERENCED_PARAMETER(yDst);
      UNREFERENCED_PARAMETER(dxDst);
      UNREFERENCED_PARAMETER(dyDst);
      UNREFERENCED_PARAMETER(pdib);
      UNREFERENCED_PARAMETER(xSrc);
      UNREFERENCED_PARAMETER(ySrc);
      UNREFERENCED_PARAMETER(dxSrc);
      UNREFERENCED_PARAMETER(dySrc);
      UNREFERENCED_PARAMETER(wFlags);
      throw interface_only_exception();
   }

   LPVOID draw_dib::GetBuffer(LPBITMAPINFOHEADER lpbi, DWORD dwSize, DWORD dwFlags )
   {
      UNREFERENCED_PARAMETER(lpbi);
      UNREFERENCED_PARAMETER(dwSize);
      UNREFERENCED_PARAMETER(dwFlags);
      throw interface_only_exception();
   }

   bool draw_dib::ProfileDisplay(LPBITMAPINFOHEADER lpbi)
   {
      UNREFERENCED_PARAMETER(lpbi);
      throw interface_only_exception();
   }

#ifdef WINDOWS

   ::ca::palette * draw_dib::get_palette()
   {
      throw interface_only_exception();
   }

   bool draw_dib::set_palette(::ca::palette * ppal)
   {
      UNREFERENCED_PARAMETER(ppal);
      throw interface_only_exception();
   }

   bool draw_dib::ChangePalette(::ca::draw_dib * pdd, int iStart, int iLen, LPPALETTEENTRY lppe)
   {
      UNREFERENCED_PARAMETER(pdd);
      UNREFERENCED_PARAMETER(iStart);
      UNREFERENCED_PARAMETER(iLen);
      UNREFERENCED_PARAMETER(lppe);
      throw interface_only_exception();
   }

   UINT draw_dib::Realize(::ca::graphics * pdc, bool fBackground)
   {
      UNREFERENCED_PARAMETER(pdc);
      UNREFERENCED_PARAMETER(fBackground);
      throw interface_only_exception();
   }

   bool draw_dib::Start(LONG rate)
   {
      UNREFERENCED_PARAMETER(rate);
      throw interface_only_exception();
   }

   bool draw_dib::Stop()
   {
      throw interface_only_exception();
   }

   bool draw_dib::time(LPDRAWDIBTIME lpddtime)
   {
      UNREFERENCED_PARAMETER(lpddtime);
      throw interface_only_exception();
   }

#endif

   int_ptr draw_dib::get_os_data()
   {
      throw interface_only_exception();
   }

} // namespace ca
