#pragma once

#ifdef _WINDOWS
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

      virtual BOOL open ();
      virtual BOOL close ();

      virtual void * get_os_data();

      virtual BOOL Begin (::ca::graphics * pdc, int dxDest, int dyDest, LPBITMAPINFOHEADER lpbi, int dxSrc, int dySrc, UINT wFlags);

      virtual BOOL End ();

      virtual BOOL draw(::ca::graphics * pdc, int xDst, int yDst, int dxDst, int dyDst, LPBITMAPINFOHEADER lpbi, LPVOID lpBits, int xSrc, int ySrc, int dxSrc, int dySrc, UINT wFlags );
      virtual BOOL draw(::ca::dib * pdib, ::ca::graphics * pdc, int xDst, int yDst, int dxDst, int dyDst, UINT wFlags );
      virtual BOOL draw(::ca::graphics * pdc, int xDst, int yDst, int dxDst, int dyDst, ::ca::dib * dib, int xSrc, int ySrc, int dxSrc, int dySrc, UINT wFlags );

      virtual LPVOID GetBuffer(LPBITMAPINFOHEADER lpbi, DWORD dwSize, DWORD dwFlags);

      virtual BOOL ProfileDisplay(LPBITMAPINFOHEADER lpbi);

#ifdef WINDOWS
      // palette
      virtual ::ca::palette * get_palette();
      virtual BOOL set_palette(::ca::palette *);
      virtual BOOL ChangePalette(::ca::draw_dib * pdd, int iStart, int iLen, LPPALETTEENTRY lppe );
      virtual UINT Realize (::ca::graphics * pdc, BOOL fBackground );

      virtual BOOL Start(LONG rate);
      virtual BOOL Stop();
      virtual BOOL time(LPDRAWDIBTIME lpddtime);
#endif
   };

   typedef smart_pointer < draw_dib > draw_dib_sp;

} // namespace ca
