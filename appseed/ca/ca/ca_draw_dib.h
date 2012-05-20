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

      virtual INT_PTR get_os_data();

      virtual bool Begin (::ca::graphics * pdc, int dxDest, int dyDest, LPBITMAPINFOHEADER lpbi, int dxSrc, int dySrc, UINT wFlags);

      virtual bool End ();

      virtual bool draw(::ca::graphics * pdc, int xDst, int yDst, int dxDst, int dyDst, LPBITMAPINFOHEADER lpbi, LPVOID lpBits, int xSrc, int ySrc, int dxSrc, int dySrc, UINT wFlags );
      virtual bool draw(::ca::dib * pdib, ::ca::graphics * pdc, int xDst, int yDst, int dxDst, int dyDst, UINT wFlags );
      virtual bool draw(::ca::graphics * pdc, int xDst, int yDst, int dxDst, int dyDst, ::ca::dib * dib, int xSrc, int ySrc, int dxSrc, int dySrc, UINT wFlags );

      virtual LPVOID GetBuffer(LPBITMAPINFOHEADER lpbi, DWORD dwSize, DWORD dwFlags);

      virtual bool ProfileDisplay(LPBITMAPINFOHEADER lpbi);

#ifdef WINDOWS
      // palette
      virtual ::ca::palette * get_palette();
      virtual bool set_palette(::ca::palette *);
      virtual bool ChangePalette(::ca::draw_dib * pdd, int iStart, int iLen, LPPALETTEENTRY lppe );
      virtual UINT Realize (::ca::graphics * pdc, bool fBackground );

      virtual bool Start(LONG rate);
      virtual bool Stop();
      virtual bool time(LPDRAWDIBTIME lpddtime);
#endif
   };

   typedef smart_pointer < draw_dib > draw_dib_sp;

} // namespace ca
