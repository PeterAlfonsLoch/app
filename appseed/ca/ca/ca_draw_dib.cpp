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
      throw interface_only_exception(get_app());
   }

   bool draw_dib::close()
   {
      throw interface_only_exception(get_app());
   }

   bool draw_dib::Begin ( ::ca::graphics * pdc, int32_t dxDest, int32_t dyDest,
      LPBITMAPINFOHEADER lpbi, int32_t dxSrc, int32_t dySrc, UINT wFlags )
   {
      UNREFERENCED_PARAMETER(pdc);
      UNREFERENCED_PARAMETER(dxDest);
      UNREFERENCED_PARAMETER(dyDest);
      UNREFERENCED_PARAMETER(lpbi);
      UNREFERENCED_PARAMETER(dxSrc);
      UNREFERENCED_PARAMETER(dySrc);
      UNREFERENCED_PARAMETER(wFlags);
      throw interface_only_exception(get_app());
   }

   bool draw_dib::End ()
   {
      throw interface_only_exception(get_app());
   }

   bool draw_dib::draw ( ::ca::graphics * pdc, int32_t xDst, int32_t yDst,
      int32_t dxDst, int32_t dyDst, LPBITMAPINFOHEADER lpbi, LPVOID lpBits,
      int32_t xSrc, int32_t ySrc, int32_t dxSrc, int32_t dySrc, UINT wFlags )
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
      throw interface_only_exception(get_app());
   }

   bool draw_dib::draw (::ca::dib *dib, ::ca::graphics * pgraphics, int32_t xDst, int32_t yDst,
      int32_t dxDst, int32_t dyDst, UINT wFlags)
   {
      UNREFERENCED_PARAMETER(dib);
      UNREFERENCED_PARAMETER(pgraphics);
      UNREFERENCED_PARAMETER(xDst);
      UNREFERENCED_PARAMETER(yDst);
      UNREFERENCED_PARAMETER(dxDst);
      UNREFERENCED_PARAMETER(dyDst);
      UNREFERENCED_PARAMETER(wFlags);
      throw interface_only_exception(get_app());
   }

   bool draw_dib::draw (
      ::ca::graphics * pdc,
      int32_t      xDst,
      int32_t      yDst,
      int32_t      dxDst,
      int32_t      dyDst,
      ::ca::dib *    pdib,
      int32_t      xSrc,
      int32_t      ySrc,
      int32_t      dxSrc,
      int32_t      dySrc,
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
      throw interface_only_exception(get_app());
   }

   LPVOID draw_dib::GetBuffer(LPBITMAPINFOHEADER lpbi, uint32_t dwSize, uint32_t dwFlags )
   {
      UNREFERENCED_PARAMETER(lpbi);
      UNREFERENCED_PARAMETER(dwSize);
      UNREFERENCED_PARAMETER(dwFlags);
      throw interface_only_exception(get_app());
   }

   bool draw_dib::ProfileDisplay(LPBITMAPINFOHEADER lpbi)
   {
      UNREFERENCED_PARAMETER(lpbi);
      throw interface_only_exception(get_app());
   }

#ifdef WINDOWSEX

   ::ca::palette * draw_dib::get_palette()
   {
      throw interface_only_exception(get_app());
   }

   bool draw_dib::set_palette(::ca::palette * ppal)
   {
      UNREFERENCED_PARAMETER(ppal);
      throw interface_only_exception(get_app());
   }

   bool draw_dib::ChangePalette(::ca::draw_dib * pdd, int32_t iStart, int32_t iLen, LPPALETTEENTRY lppe)
   {
      UNREFERENCED_PARAMETER(pdd);
      UNREFERENCED_PARAMETER(iStart);
      UNREFERENCED_PARAMETER(iLen);
      UNREFERENCED_PARAMETER(lppe);
      throw interface_only_exception(get_app());
   }

   UINT draw_dib::Realize(::ca::graphics * pdc, bool fBackground)
   {
      UNREFERENCED_PARAMETER(pdc);
      UNREFERENCED_PARAMETER(fBackground);
      throw interface_only_exception(get_app());
   }

   bool draw_dib::Start(LONG rate)
   {
      UNREFERENCED_PARAMETER(rate);
      throw interface_only_exception(get_app());
   }

   bool draw_dib::Stop()
   {
      throw interface_only_exception(get_app());
   }

   bool draw_dib::time(LPDRAWDIBTIME lpddtime)
   {
      UNREFERENCED_PARAMETER(lpddtime);
      throw interface_only_exception(get_app());
   }

#endif

   int_ptr draw_dib::get_os_data()
   {
      throw interface_only_exception(get_app());
   }

} // namespace ca
