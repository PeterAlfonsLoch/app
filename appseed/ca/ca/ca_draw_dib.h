#pragma once

#ifdef WINDOWS
#include <vfw.h>
#endif

namespace ca
{

   //////////////////////////////////////////////////////////////////////
   // draw_dib.h: interface for the draw_dib class.
   //
   //   Creator : El Barto (ef00@luc.ac.be)
   //   Location : http://www.luc.ac.be/~ef00/ebgfx
   //   Date : 09-04-98
   //
   //////////////////////////////////////////////////////////////////////

   class CLASS_DECL_ca draw_dib :
      virtual public ::radix::object
   {
   public:

      virtual bool open ();
      virtual bool close ();

      virtual int_ptr get_os_data();

      virtual bool Begin (::ca::graphics * pdc, int32_t dxDest, int32_t dyDest, LPBITMAPINFOHEADER lpbi, int32_t dxSrc, int32_t dySrc, UINT wFlags);

      virtual bool End ();

      virtual bool draw(::ca::graphics * pdc, int32_t xDst, int32_t yDst, int32_t dxDst, int32_t dyDst, LPBITMAPINFOHEADER lpbi, LPVOID lpBits, int32_t xSrc, int32_t ySrc, int32_t dxSrc, int32_t dySrc, UINT wFlags );
      virtual bool draw(::ca::dib * pdib, ::ca::graphics * pdc, int32_t xDst, int32_t yDst, int32_t dxDst, int32_t dyDst, UINT wFlags );
      virtual bool draw(::ca::graphics * pdc, int32_t xDst, int32_t yDst, int32_t dxDst, int32_t dyDst, ::ca::dib * dib, int32_t xSrc, int32_t ySrc, int32_t dxSrc, int32_t dySrc, UINT wFlags );

      virtual LPVOID GetBuffer(LPBITMAPINFOHEADER lpbi, uint32_t dwSize, uint32_t dwFlags);

      virtual bool ProfileDisplay(LPBITMAPINFOHEADER lpbi);

#ifdef WINDOWSEX
      // palette
      virtual ::ca::palette * get_palette();
      virtual bool set_palette(::ca::palette *);
      virtual bool ChangePalette(::ca::draw_dib * pdd, int32_t iStart, int32_t iLen, LPPALETTEENTRY lppe );
      virtual UINT Realize (::ca::graphics * pdc, bool fBackground );

      virtual bool Start(LONG rate);
      virtual bool Stop();
      virtual bool time(LPDRAWDIBTIME lpddtime);
#endif
   };

   typedef smart_pointer < draw_dib > draw_dib_sp;

} // namespace ca
