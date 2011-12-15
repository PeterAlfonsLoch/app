//   Creator : El Barto (ef00@luc.ac.be)
//   Location : http://www.luc.ac.be/~ef00/ebgfx
//   Date : 09-04-98
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include <math.h>

namespace ca
{
   ::ca::graphics * dib::get_graphics()
   {
      throw interface_only_exception();
   }

   ::ca::bitmap_sp dib::get_bitmap()
   {
      throw interface_only_exception();
   }

   ::ca::bitmap_sp dib::detach_bitmap()
   {
      throw interface_only_exception();
   }

   void dib::construct (int cx,  int cy)
   {
      UNREFERENCED_PARAMETER(cx);
      UNREFERENCED_PARAMETER(cy);
      throw interface_only_exception();
   }

   COLORREF * dib::get_data()
   {
      return NULL;
   }

   BOOL dib::create(class size size)
   {
      return create(size.cx, size.cy);
   }

   BOOL dib::create(int width, int height)
   {
      UNREFERENCED_PARAMETER(width);
      UNREFERENCED_PARAMETER(height);
      throw interface_only_exception();
   }

   bool dib::dc_select(bool bSelect)
   {
      UNREFERENCED_PARAMETER(bSelect);
      throw interface_only_exception();
   }

   BOOL dib::create(::ca::graphics * pdc)
   {
      ::ca::bitmap & bitmap = pdc->GetCurrentBitmap();
      if(&bitmap == NULL)
         return FALSE;

      throw not_implemented_exception();
      /*
      BITMAP bm;
      bitmap.GetObject(sizeof(bm), &bm);
      if(!create(bm.bmWidth, bm.bmHeight))
      {
         return FALSE;
      }
      from(pdc);*/
      return TRUE;
   }

   BOOL dib::Destroy ()
   {
      throw interface_only_exception();
   }

   bool dib::to(::ca::graphics * pgraphics)
   {
      return to(pgraphics, null_point(), size());
   }

   bool dib::to(::ca::graphics * pgraphics, point pt)
   {
      return to(pgraphics, pt, size());
   }

   bool dib::to(::ca::graphics * pgraphics, class size size)
   {
      return to(pgraphics, null_point(), size);
   }

   bool dib::to(::ca::graphics * pgraphics, LPCRECT lpcrect)
   {
      class rect rect(lpcrect);
      return to(pgraphics, rect.top_left(), rect.size());
   }

   bool dib::to(::ca::graphics * pgraphics, point pt, class size size)
   {
      return to(pgraphics, pt, size, point(0, 0));
   }

   bool dib::to(::ca::graphics * pgraphics, point pt, class size size, point ptSrc)
   {
      UNREFERENCED_PARAMETER(pgraphics);
      UNREFERENCED_PARAMETER(pt);
      UNREFERENCED_PARAMETER(size);
      UNREFERENCED_PARAMETER(ptSrc);
      throw interface_only_exception();
   }

   bool dib::from(::ca::dib * pdib)
   {
      if(!create(pdib->size()))
         return false;
      try
      {
         memcpy(get_data(), pdib->get_data(), (size_t) (sizeof(COLORREF) * area()));
      }
      catch(...)
      {
         return false;
      }
      return true;
   }

   bool dib::from(::ca::graphics * pdc)
   {
      UNREFERENCED_PARAMETER(pdc);
      throw interface_only_exception();
   }

   bool dib::from(point ptDst, ::ca::graphics * pdc, point ptSrc, class size size)
   {
      return get_graphics()->from(ptDst, size, pdc, ptSrc, SRCCOPY) != FALSE;
   }

   void dib::Fill ( int R, int G, int B )
   {
      COLORREF color=RGB ( B, G, R );
      int size=width()*height();

      COLORREF * pcr;

      int iSize32 = size / 32;
      int i;
      for (i=0; i < iSize32; i+=32 )
      {
         pcr = &get_data()[i];
         pcr[0] = color;
         pcr[1] = color;
         pcr[2] = color;
         pcr[3] = color;
         pcr[4] = color;
         pcr[5] = color;
         pcr[6] = color;
         pcr[7] = color;
         pcr[8] = color;
         pcr[9] = color;
         pcr[10] = color;
         pcr[11] = color;
         pcr[12] = color;
         pcr[13] = color;
         pcr[14] = color;
         pcr[15] = color;
         pcr[16] = color;
         pcr[17] = color;
         pcr[18] = color;
         pcr[19] = color;
         pcr[20] = color;
         pcr[21] = color;
         pcr[22] = color;
         pcr[23] = color;
         pcr[24] = color;
         pcr[25] = color;
         pcr[26] = color;
         pcr[27] = color;
         pcr[28] = color;
         pcr[29] = color;
         pcr[30] = color;
         pcr[31] = color;
      }

      for (i=0; i<size; i++ )
      {
         get_data()[i]=color;
      }
   }

   void dib::ToAlpha(int i)
   {
      BYTE *dst=(BYTE*)get_data();
      int size=width()*height();

      while ( size-- )
      {
         dst[3] = dst[i];
         dst+=4;
      }
   }

   void dib::from_alpha()
   {
      BYTE *dst=(BYTE*)get_data();
      __int64 size = area();

      while ( size-- )
      {
         dst[0] = dst[3];
         dst[1] = dst[3];
         dst[2] = dst[3];
         dst+=4;
      }
   }

   void dib::mult_alpha(::ca::dib * pdib, bool bPreserveAlpha)
   {
      UNREFERENCED_PARAMETER(pdib);
      UNREFERENCED_PARAMETER(bPreserveAlpha);

      BYTE *dst=(BYTE*)get_data();
      __int64 size = area();


      // >> 8 instead of / 255 subsequent alpha_blend operations say thanks on true_blend because (255) * (1/254) + (255) * (254/255) > 255


      while (size >= 8)
      {
         dst[0] = LOBYTE(((int)dst[0] * (int)dst[3])>> 8);
         dst[1] = LOBYTE(((int)dst[1] * (int)dst[3])>> 8);
         dst[2] = LOBYTE(((int)dst[2] * (int)dst[3])>> 8);

         dst[4+0] = LOBYTE(((int)dst[4+0] * (int)dst[4+3])>> 8);
         dst[4+1] = LOBYTE(((int)dst[4+1] * (int)dst[4+3])>> 8);
         dst[4+2] = LOBYTE(((int)dst[4+2] * (int)dst[4+3])>> 8);

         dst[8+0] = LOBYTE(((int)dst[8+0] * (int)dst[8+3])>> 8);
         dst[8+1] = LOBYTE(((int)dst[8+1] * (int)dst[8+3])>> 8);
         dst[8+2] = LOBYTE(((int)dst[8+2] * (int)dst[8+3])>> 8);

         dst[12+0] = LOBYTE(((int)dst[12+0] * (int)dst[12+3])>> 8);
         dst[12+1] = LOBYTE(((int)dst[12+1] * (int)dst[12+3])>> 8);
         dst[12+2] = LOBYTE(((int)dst[12+2] * (int)dst[12+3])>> 8);

         dst[16+0] = LOBYTE(((int)dst[16+0] * (int)dst[16+3])>> 8);
         dst[16+1] = LOBYTE(((int)dst[16+1] * (int)dst[16+3])>> 8);
         dst[16+2] = LOBYTE(((int)dst[16+2] * (int)dst[16+3])>> 8);

         dst[20+0] = LOBYTE(((int)dst[20+0] * (int)dst[20+3])>> 8);
         dst[20+1] = LOBYTE(((int)dst[20+1] * (int)dst[20+3])>> 8);
         dst[20+2] = LOBYTE(((int)dst[20+2] * (int)dst[20+3])>> 8);

         dst[24+0] = LOBYTE(((int)dst[24+0] * (int)dst[24+3])>> 8);
         dst[24+1] = LOBYTE(((int)dst[24+1] * (int)dst[24+3])>> 8);
         dst[24+2] = LOBYTE(((int)dst[24+2] * (int)dst[24+3])>> 8);

         dst[28+0] = LOBYTE(((int)dst[28+0] * (int)dst[28+3])>> 8);
         dst[28+1] = LOBYTE(((int)dst[28+1] * (int)dst[28+3])>> 8);
         dst[28+2] = LOBYTE(((int)dst[28+2] * (int)dst[28+3])>> 8);

         dst += 4 * 8;
         size -= 8;
      }
      while(size--)
      {
         dst[0] = LOBYTE(((int)dst[0] * (int)dst[3])>> 8);
         dst[1] = LOBYTE(((int)dst[1] * (int)dst[3])>> 8);
         dst[2] = LOBYTE(((int)dst[2] * (int)dst[3])>> 8);
         dst += 4;
      }
   }

   void dib::Map(int ToRgb, int FromRgb)
   {
      byte * dst= (byte *) get_data();
      int size=width()*height();

      while ( size-- )
      {
         *dst = (byte) (*dst == FromRgb ? ToRgb : *dst);
         dst+=4;
      }
   }


   void dib::ToAlphaAndFill(int i, COLORREF cr)
   {
      BYTE *dst=(BYTE*)get_data();
      int size=width()*height();

      BYTE uchB = rgba_get_b(cr);
      BYTE uchG = rgba_get_g(cr);
      BYTE uchR = rgba_get_r(cr);

      while ( size-- )
      {
         dst[3] = dst[i];
         dst[0] = uchB;
         dst[1] = uchG;
         dst[2] = uchR;
         dst+=4;
      }
   }

   void dib::GrayToARGB(COLORREF cr)
   {
      BYTE *dst=(BYTE*)get_data();
      int size=width()*height();

      DWORD dwB = rgba_get_b(cr);
      DWORD dwG = rgba_get_g(cr);
      DWORD dwR = rgba_get_r(cr);

      while (size-- > 0)
      {
         dst[3] = dst[0];
         dst[0] = (BYTE)(((dwB * dst[3]) / 256) & 0xff);
         dst[1] = (BYTE)(((dwG * dst[3]) / 256) & 0xff);
         dst[2] = (BYTE)(((dwR * dst[3]) / 256) & 0xff);
         dst+=4;
      }
   }


   void dib::BitBlt(dib *pdib, int op)
   {
      if(op == 123) // zero dest RGB, invert alpha, and OR src RGB
      {
         int isize=width()*height();
         LPDWORD lpbitsSrc= (LPDWORD) pdib->get_data();
         LPDWORD lpbitsDest= (LPDWORD) get_data();

         COLORREF _colorref = RGB ( 0, 0, 0 ) | (255 << 24);
         COLORREF colorrefa[2];
         colorrefa[0] = _colorref;
         colorrefa[1] = _colorref;

         COLORREF _colorrefN = RGB ( 255, 255, 255) | (0 << 24);
         COLORREF colorrefaN[2];
         colorrefaN[0] = _colorrefN;
         colorrefaN[1] = _colorrefN;
#ifdef _AMD64_

         //x64
#else
    #ifdef WINDOWS
         _asm
         {
            emms
               mov      eax, isize
               mov      ebx, lpbitsDest
               mov      ecx, lpbitsSrc
               movq     mm0, colorrefa
               movq     mm7, colorrefaN
fill_loop:
            cmp      eax, 1
               jle      fill_last
               movq     mm1, [ebx]
            movq     mm2, [ecx]
            pandn    mm1, mm0
               pand     mm2, mm7
               por      mm1, mm2
               movq     [ebx], mm1

               sub      eax, 2
               add      ebx, 8
               add      ecx, 8

               jmp      fill_loop

fill_last:
            emms
         }
         #endif
#endif
      }

   }


   void dib::Invert()
   {
      int size=width()*height();
      LPBYTE lpb = (LPBYTE) get_data();
      for ( int i=0; i<size; i++ )
      {
         lpb[0] = 255 - lpb[0];
         lpb[1] = 255 - lpb[1];
         lpb[2] = 255 - lpb[2];
         lpb += 4;
      }
   }

   void dib::channel_invert(visual::rgba::echannel echannel)
   {
      __int64 size=area();
      LPBYTE lpb = (LPBYTE) get_data();
      lpb += ((int)echannel) % 4;
      for ( int i=0; i<size; i++ )
      {
         *lpb = 255 - *lpb;
         lpb += 4;
      }
   }

   void dib::channel_multiply(visual::rgba::echannel echannel, double dRate)
   {
      if(dRate < 0)
         return;
      register __int64 size = area();
      LPBYTE lpb = (LPBYTE) get_data();
      lpb += ((int)echannel) % 4;
      register int iDiv = 256 * 256;
      register int iMul = (int) (dRate * ((double) iDiv));
      register int iRes;
      for(register __int64 i = 0; i < size; i++)
      {
         iRes = *lpb * iMul / iDiv;
         *lpb = (byte) (iRes > 255 ? 255 : iRes);
         lpb += 4;
      }
   }

   void dib::channel_multiply(visual::rgba::echannel echannel, ::ca::dib * pdib)
   {
      register __int64 size = area();
      LPBYTE lpb1 = (LPBYTE) get_data();
      LPBYTE lpb2 = (LPBYTE) pdib->get_data();
      lpb1 += ((int)echannel) % 4;
      lpb2 += ((int)echannel) % 4;
      for(register __int64 i = 0; i < size; i++)
      {
         *lpb1 = (BYTE)(((unsigned int)*lpb1 * (unsigned int)*lpb2) / 255);
         lpb1 += 4;
         lpb2 += 4;
      }
   }

   void dib::channel_darken(visual::rgba::echannel echannel, ::ca::dib * pdib)
   {
      register __int64 size = area();
      LPBYTE lpb1 = (LPBYTE) get_data();
      LPBYTE lpb2 = (LPBYTE) pdib->get_data();
      lpb1 += ((int)echannel) % 4;
      lpb2 += ((int)echannel) % 4;
      for(register __int64 i = 0; i < size; i++)
      {
         *lpb1 = *lpb1 < *lpb2 ? *lpb1 : *lpb2;
         lpb1 += 4;
         lpb2 += 4;
      }
   }

   void dib::channel_lighten(visual::rgba::echannel echannel, ::ca::dib * pdib)
   {
      register __int64 size = area();
      LPBYTE lpb1 = (LPBYTE) get_data();
      LPBYTE lpb2 = (LPBYTE) pdib->get_data();
      lpb1 += ((int)echannel) % 4;
      lpb2 += ((int)echannel) % 4;
      for(register __int64 i = 0; i < size; i++)
      {
         *lpb1 = *lpb1 > *lpb2 ? *lpb1 : *lpb2;
         lpb1 += 4;
         lpb2 += 4;
      }
   }

   void dib::channel_from(visual::rgba::echannel echannel, ::ca::dib * pdib)
   {
      register __int64 size = area();
      LPBYTE lpb1 = (LPBYTE) get_data();
      LPBYTE lpb2 = (LPBYTE) pdib->get_data();
      lpb1 += ((int)echannel) % 4;
      lpb2 += ((int)echannel) % 4;
      for(register __int64 i = 0; i < size; i++)
      {
         *lpb1 = *lpb2;
         lpb1 += 4;
         lpb2 += 4;
      }
   }


   void dib::FillGlass ( int R, int G, int B, int A )
   {
      BYTE *dst=(BYTE*)get_data();
      int size=width()*height();

      while ( size-- )
      {
         dst[0]=(BYTE)(((B-dst[0])*A+(dst[0]<<8))>>8);
         dst[1]=(BYTE)(((G-dst[1])*A+(dst[1]<<8))>>8);
         dst[2]=(BYTE)(((R-dst[2])*A+(dst[2]<<8))>>8);
         dst+=4;
      }
   }

   void dib::FillStippledGlass ( int R, int G, int B )
   {
      COLORREF color=RGB ( B, G, R );
      int w=width();
      int h=height();

      for ( int j=0; j<w; j++ )
      {
         for ( int i=0; i<h; i++ )
         {
            get_data()[j*w+i]=((i+j)&0x1) ? get_data()[j*w+i] : color;
         }
      }
   }

   void dib::copy(dib * dib)
   {
      // If DibSize Wrong Re-create dib
      if ( (dib->width()!=width()) || (dib->height()!=height()) )
         dib->create ( width(), height() );
      // do copy
      memcpy ( dib->get_data(), get_data(), width()*height()*4 );
   }


   void dib::Paste ( dib *dib )
   {
      // If DibSize Wrong Re-create dib
      if ( (width()!=dib->width()) || (height()!=dib->height()) )
         create ( dib->width(), dib->height() );
      // do Paste
      memcpy ( get_data(), dib->get_data(), width()*height()*4 );
   }

   bool dib::bitmap_blend(::ca::graphics * pgraphics, LPCRECT lprect)
   {
      rect rect(lprect);
      return System.imaging().bitmap_blend(
         pgraphics,
         rect.top_left(),
         rect.size(),
         get_graphics(),
         null_point());
   }


   bool dib::color_blend(COLORREF cr, BYTE bAlpha)
   {

      BYTE *dst=(BYTE*)get_data();
      int size=width()*height();

      DWORD dwB = rgba_get_b(cr);
      DWORD dwG = rgba_get_g(cr);
      DWORD dwR = rgba_get_r(cr);

      DWORD dwB_ = dwB << 8;
      DWORD dwG_ = dwG << 8;
      DWORD dwR_ = dwR << 8;

      while ( size-- )
      {
         dst[0]=(BYTE)(((dst[0]-dwB)*bAlpha+dwB_)>>8);
         dst[1]=(BYTE)(((dst[1]-dwG)*bAlpha+dwG_)>>8);
         dst[2]=(BYTE)(((dst[2]-dwG)*bAlpha+dwR_)>>8);
         dst+=4;
      }
      return true;
   }


   void dib::Blend(dib * dib, int A)
   {
      if(size() != dib->size() )
         return;

      BYTE *src=(BYTE*)dib->get_data();
      BYTE *dst=(BYTE*)get_data();
      int size=width()*height();

      while ( size-- )
      {
         dst[0]=(BYTE)(((src[0]-dst[0])*A+(dst[0]<<8))>>8);
         dst[1]=(BYTE)(((src[1]-dst[1])*A+(dst[1]<<8))>>8);
         dst[2]=(BYTE)(((src[2]-dst[2])*A+(dst[2]<<8))>>8);
         dst+=4;
         src+=4;
      }
   }

   bool dib::Blend(dib *pDib, dib *DibA, int A)
   {
      if(size() != pDib->size() ||
         size() != DibA->size())
         return false;

      BYTE *src=(BYTE*)pDib->get_data();
      BYTE *dst=(BYTE*)get_data();
      BYTE *alf=(BYTE*)DibA->get_data();
      int size=width()*height();

      A = 2 - A;

      while ( size-- )
      {
         dst[0]=(BYTE)(((src[0]-dst[0])*alf[A]+(dst[0]<<8))>>8);
         dst[1]=(BYTE)(((src[1]-dst[1])*alf[A]+(dst[1]<<8))>>8);
         dst[2]=(BYTE)(((src[2]-dst[2])*alf[A]+(dst[2]<<8))>>8);
         dst+=4;
         src+=4;
         alf+=4;
      }

      return true;
   }

   bool dib::blend(dib * pdib, dib * pdibRate)
   {
      if(size() != pdib->size() ||
         size() != pdibRate->size())
         return false;

      BYTE *src=(BYTE*)pdib->get_data();
      BYTE *dst=(BYTE*)get_data();
      BYTE *alf=(BYTE*)pdibRate->get_data();
      int size=width()*height();

      while(size >= 2)
      {
         dst[00] = (BYTE) (((((int)src[00] - (int)dst[00]) * (int)alf[00]) + (int)dst[00] * (int)255) / 255);
         dst[01] = (BYTE) (((((int)src[01] - (int)dst[01]) * (int)alf[01]) + (int)dst[01] * (int)255) / 255);
         dst[02] = (BYTE) (((((int)src[02] - (int)dst[02]) * (int)alf[02]) + (int)dst[02] * (int)255) / 255);
         dst[03] = (BYTE) (((((int)src[03] - (int)dst[03]) * (int)alf[03]) + (int)dst[03] * (int)255) / 255);
         dst[04] = (BYTE) (((((int)src[04] - (int)dst[04]) * (int)alf[04]) + (int)dst[04] * (int)255) / 255);
         dst[05] = (BYTE) (((((int)src[05] - (int)dst[05]) * (int)alf[05]) + (int)dst[05] * (int)255) / 255);
         dst[06] = (BYTE) (((((int)src[06] - (int)dst[06]) * (int)alf[06]) + (int)dst[06] * (int)255) / 255);
         dst[07] = (BYTE) (((((int)src[07] - (int)dst[07]) * (int)alf[07]) + (int)dst[07] * (int)255) / 255);
         dst+=4 * 2;
         src+=4 * 2;
         alf+=4 * 2;
         size-=2;
      }
      while(size > 0)
      {
         dst[00] = (BYTE) (((((int)src[00] - (int)dst[00]) * (int)alf[00]) + (int)dst[00] * (int)255) / 255);
         dst[01] = (BYTE) (((((int)src[01] - (int)dst[01]) * (int)alf[01]) + (int)dst[01] * (int)255) / 255);
         dst[02] = (BYTE) (((((int)src[02] - (int)dst[02]) * (int)alf[02]) + (int)dst[02] * (int)255) / 255);
         dst[03] = (BYTE) (((((int)src[03] - (int)dst[03]) * (int)alf[03]) + (int)dst[03] * (int)255) / 255);
         dst+=4;
         src+=4;
         alf+=4;
         size--;
      }

      return true;
   }

   void dib::Darken ( dib *dib )
   {
      if ( size()!=dib->size() )
         return;

      BYTE *src=(BYTE*)dib->get_data();
      BYTE *dst=(BYTE*)get_data();
      int size=width()*height();

      while ( size-- )
      {
         dst[0]=(BYTE)((src[0]<dst[0]) ? src[0] : dst[0]);
         dst[1]=(BYTE)((src[1]<dst[1]) ? src[1] : dst[1]);
         dst[2]=(BYTE)((src[2]<dst[2]) ? src[2] : dst[2]);
         dst+=4;
         src+=4;
      }
   }

   void dib::Difference ( dib *dib )
   {
      if ( size()!=dib->size() )
         return;

      BYTE *src=(BYTE*)dib->get_data();
      BYTE *dst=(BYTE*)get_data();
      int size=width()*height();

      while ( size-- )
      {
         int Difference;
         Difference=src[0]-dst[0];
         dst[0]=(BYTE)((Difference<0) ? -Difference : Difference);
         Difference=src[1]-dst[1];
         dst[1]=(BYTE)((Difference<0) ? -Difference : Difference);
         Difference=src[2]-dst[2];
         dst[2]=(BYTE)((Difference<0) ? -Difference : Difference);
         dst+=4;
         src+=4;
      }
   }

   void dib::Lighten ( dib *dib )
   {
      if ( size()!=dib->size() )
         return;

      BYTE *src=(BYTE*)dib->get_data();
      BYTE *dst=(BYTE*)get_data();
      int size=width()*height();

      while ( size-- )
      {
         dst[0]=(BYTE)((src[0]>dst[0]) ? src[0] : dst[0]);
         dst[1]=(BYTE)((src[1]>dst[1]) ? src[1] : dst[1]);
         dst[2]=(BYTE)((src[2]>dst[2]) ? src[2] : dst[2]);
         dst+=4;
         src+=4;
      }
   }

   void dib::Multiply ( dib *dib )
   {
      if ( size()!=dib->size() )
         return;

      BYTE *src=(BYTE*)dib->get_data();
      BYTE *dst=(BYTE*)get_data();
      int size=width()*height();

      while ( size-- )
      {
         dst[0]=(BYTE)(((src[0])*(dst[0]))>>8);
         dst[1]=(BYTE)(((src[1])*(dst[1]))>>8);
         dst[2]=(BYTE)(((src[2])*(dst[2]))>>8);
         dst+=4;
         src+=4;
      }
   }

   void dib::Screen ( dib *dib )
   {
      if ( size()!=dib->size() )
         return;

      BYTE *src=(BYTE*)dib->get_data();
      BYTE *dst=(BYTE*)get_data();
      int size=width()*height();

      while ( size-- )
      {
         dst[0]=(BYTE)(255-(((255-src[0])*(255-dst[0]))>>8));
         dst[1]=(BYTE)(255-(((255-src[1])*(255-dst[1]))>>8));
         dst[2]=(BYTE)(255-(((255-src[2])*(255-dst[2]))>>8));
         dst+=4;
         src+=4;
      }
   }

   //////////////////////////////////////////////////////////////////////
   // Rectangle Functions
   //////////////////////////////////////////////////////////////////////

   void dib::copy ( dib *dib, int x, int y )
   {
      // Clip Rect
      int px=(x>=0) ? x : 0;
      int py=(y>=0) ? y : 0;
      int dx=((x+dib->width())<width()) ? dib->width() : width()-x;
      int dy=((y+dib->height())<height()) ? dib->height() : height()-y;
      dx=(x>=0) ? dx : dx + x;
      dy=(y>=0) ? dy : dy + y;

      // If Nothing to copy return
      if ( (dx<=0) || (dy<=0) )
         return;
      // If DibSize Wrong Re-create dib
      if ( (dx!=dib->width()) || (dy!=dib->height()) )
         dib->create ( dx, dy );

      // Prepare buffer Addresses
      COLORREF *src=get_data()+(py*width())+px;
      COLORREF *dst=dib->get_data();

      // Do copy
      while ( dy-- )
      {
         for ( int i=0; i<dx; i++ )
            dst[i]=src[i];
         src+=width();
         dst+=dib->width();
      }
   }

   void dib::PasteRect ( dib *dib, int x, int y )
   {
      // Clip Rect
      int px=(x>=0) ? x : 0;
      int py=(y>=0) ? y : 0;
      int dx=((x+dib->width())<width()) ? dib->width() : width()-x;
      int dy=((y+dib->height())<height()) ? dib->height() : height()-y;
      dx=(x>=0) ? dx : dx + x;
      dy=(y>=0) ? dy : dy + y;

      // If Nothing to Paste return
      if ( (dx<=0) || (dy<=0) )
         return;

      // Prepare buffer Addresses
      COLORREF *src=dib->get_data()+((py-y)*dib->width())+px-x;
      COLORREF *dst=get_data()+(py*width())+px;

      // Do Paste
      while ( dy-- )
      {
         for ( int i=0; i<dx; i++ )
            dst[i]=src[i];
         src+=dib->width();
         dst+=width();
      }
   }

   void dib::FillRect ( int x, int y, int w, int h, int R, int G, int B )
   {
      // Clip Rect
      int px=(x>=0) ? x : 0;
      int py=(y>=0) ? y : 0;
      int dx=((x+w)<width()) ? w : width()-x;
      int dy=((y+h)<height()) ? h : height()-y;
      dx=(x>=0) ? dx : dx + x;
      dy=(y>=0) ? dy : dy + y;

      // If Nothing to Fill return
      if ( (dx<=0) || (dy<=0) )
         return;

      // Prepare buffer Address
      COLORREF *dst=get_data()+(py*width())+px;
      COLORREF color=RGB ( B, G, R );

      // Do Fill
      while ( dy-- )
      {
         for ( int i=0; i<dx; i++ )
         {
            dst[i]=color;
         }
         dst+=width();
      }
   }

   void dib::FillGlassRect ( int x, int y, int w, int h, int R, int G, int B, int A )
   {
      // Clip Rect
      int px=(x>=0) ? x : 0;
      int py=(y>=0) ? y : 0;
      int dx=((x+w)<width()) ? w : width()-x;
      int dy=((y+h)<height()) ? h : height()-y;
      dx=(x>=0) ? dx : dx + x;
      dy=(y>=0) ? dy : dy + y;

      // If Nothing to FillGlass return
      if ( (dx<=0) || (dy<=0) )
         return;

      // Prepare buffer Address
      BYTE *dst=(BYTE *)get_data()+((py*width())+px)*4;

      // Do FillGlass
      while ( dy-- )
      {
         for ( int i=0; i<dx; i++ )
         {
            dst[0]=(BYTE)(((B-dst[0])*A+(dst[0]<<8))>>8);
            dst[1]=(BYTE)(((G-dst[1])*A+(dst[1]<<8))>>8);
            dst[2]=(BYTE)(((R-dst[2])*A+(dst[2]<<8))>>8);
            dst+=4;
         }
         dst+=(width()-dx)<<2;
      }
   }

   void dib::FillStippledGlassRect ( int x, int y, int w, int h, int R, int G, int B )
   {
      // Clip Rect
      int px=(x>=0) ? x : 0;
      int py=(y>=0) ? y : 0;
      int dx=((x+w)<width()) ? w : width()-x;
      int dy=((y+h)<height()) ? h : height()-y;
      dx=(x>=0) ? dx : dx + x;
      dy=(y>=0) ? dy : dy + y;

      // If Nothing to FillStippledGlass return
      if ( (dx<=0) || (dy<=0) )
         return;

      // Prepare buffer Address
      COLORREF *dst=get_data()+(py*width())+px;
      COLORREF color=RGB ( B, G, R );

      // Do FillStippledGlass
      for ( int j=0; j<dy; j++ )
      {
         for ( int i=0; i<dx; i++ )
         {
            dst[i]=((i+j)&0x1) ? dst[i] : color;
         }
         dst+=width();
      }
   }

   void dib::BlendRect ( dib *dib, int x, int y, int A )
   {
      // Clip Rect
      int px=(x>=0) ? x : 0;
      int py=(y>=0) ? y : 0;
      int dx=((x+dib->width())<width()) ? dib->width() : width()-x;
      int dy=((y+dib->height())<height()) ? dib->height() : height()-y;
      dx=(x>=0) ? dx : dx + x;
      dy=(y>=0) ? dy : dy + y;

      // If Nothing to Blend return
      if ( (dx<=0) || (dy<=0) )
         return;

      // Prepare buffer Addresses
      BYTE *src=(BYTE *)dib->get_data()+(((py-y)*dib->width())+px-x)*4;
      BYTE *dst=(BYTE *)get_data()+((py*width())+px)*4;

      // Do Blend
      while ( dy-- )
      {
         for ( int i=0; i<dx; i++ )
         {
            dst[0]=(BYTE)(((src[0]-dst[0])*A+(dst[0]<<8))>>8);
            dst[1]=(BYTE)(((src[1]-dst[1])*A+(dst[1]<<8))>>8);
            dst[2]=(BYTE)(((src[2]-dst[2])*A+(dst[2]<<8))>>8);
            dst+=4;
            src+=4;
         }
         dst+=(width()-dx)<<2;
         src+=(dib->width()-dx)<<2;
      }
   }

   void dib::DarkenRect ( dib *dib, int x, int y )
   {
      // Clip Rect
      int px=(x>=0) ? x : 0;
      int py=(y>=0) ? y : 0;
      int dx=((x+dib->width())<width()) ? dib->width() : width()-x;
      int dy=((y+dib->height())<height()) ? dib->height() : height()-y;
      dx=(x>=0) ? dx : dx + x;
      dy=(y>=0) ? dy : dy + y;

      // If Nothing to Darken return
      if ( (dx<=0) || (dy<=0) )
         return;

      // Prepare buffer Addresses
      BYTE *src=(BYTE *)dib->get_data()+(((py-y)*dib->width())+px-x)*4;
      BYTE *dst=(BYTE *)get_data()+((py*width())+px)*4;

      // Do Darken
      while ( dy-- )
      {
         for ( int i=0; i<dx; i++ )
         {
            dst[0]=(BYTE)((src[0]<dst[0]) ? src[0] : dst[0]);
            dst[1]=(BYTE)((src[1]<dst[1]) ? src[1] : dst[1]);
            dst[2]=(BYTE)((src[2]<dst[2]) ? src[2] : dst[2]);
            dst+=4;
            src+=4;
         }
         dst+=(width()-dx)<<2;
         src+=(dib->width()-dx)<<2;
      }
   }

   void dib::DifferenceRect ( dib *dib, int x, int y )
   {
      // Clip Rect
      int px=(x>=0) ? x : 0;
      int py=(y>=0) ? y : 0;
      int dx=((x+dib->width())<width()) ? dib->width() : width()-x;
      int dy=((y+dib->height())<height()) ? dib->height() : height()-y;
      dx=(x>=0) ? dx : dx + x;
      dy=(y>=0) ? dy : dy + y;

      // If Nothing to Difference return
      if ( (dx<=0) || (dy<=0) )
         return;

      // Prepare buffer Addresses
      BYTE *src=(BYTE *)dib->get_data()+(((py-y)*dib->width())+px-x)*4;
      BYTE *dst=(BYTE *)get_data()+((py*width())+px)*4;

      // Do Difference
      while ( dy-- )
      {
         for ( int i=0; i<dx; i++ )
         {
            int Difference;
            Difference=src[0]-dst[0];
            dst[0]=(BYTE)((Difference<0) ? -Difference : Difference);
            Difference=src[1]-dst[1];
            dst[1]=(BYTE)((Difference<0) ? -Difference : Difference);
            Difference=src[2]-dst[2];
            dst[2]=(BYTE)((Difference<0) ? -Difference : Difference);
            dst+=4;
            src+=4;
         }
         dst+=(width()-dx)<<2;
         src+=(dib->width()-dx)<<2;
      }
   }

   void dib::LightenRect ( dib *dib, int x, int y )
   {
      // Clip Rect
      int px=(x>=0) ? x : 0;
      int py=(y>=0) ? y : 0;
      int dx=((x+dib->width())<width()) ? dib->width() : width()-x;
      int dy=((y+dib->height())<height()) ? dib->height() : height()-y;
      dx=(x>=0) ? dx : dx + x;
      dy=(y>=0) ? dy : dy + y;

      // If Nothing to Lighten return
      if ( (dx<=0) || (dy<=0) )
         return;

      // Prepare buffer Addresses
      BYTE *src=(BYTE *)dib->get_data()+(((py-y)*dib->width())+px-x)*4;
      BYTE *dst=(BYTE *)get_data()+((py*width())+px)*4;

      // Do Lighten
      while ( dy-- )
      {
         for ( int i=0; i<dx; i++ )
         {
            dst[0]=(BYTE)((src[0]>dst[0]) ? src[0] : dst[0]);
            dst[1]=(BYTE)((src[1]>dst[1]) ? src[1] : dst[1]);
            dst[2]=(BYTE)((src[2]>dst[2]) ? src[2] : dst[2]);
            dst+=4;
            src+=4;
         }
         dst+=(width()-dx)<<2;
         src+=(dib->width()-dx)<<2;
      }
   }

   void dib::MultiplyRect ( dib *dib, int x, int y )
   {
      // Clip Rect
      int px=(x>=0) ? x : 0;
      int py=(y>=0) ? y : 0;
      int dx=((x+dib->width())<width()) ? dib->width() : width()-x;
      int dy=((y+dib->height())<height()) ? dib->height() : height()-y;
      dx=(x>=0) ? dx : dx + x;
      dy=(y>=0) ? dy : dy + y;

      // If Nothing to Multiply return
      if ( (dx<=0) || (dy<=0) )
         return;

      // Prepare buffer Addresses
      BYTE *src=(BYTE *)dib->get_data()+(((py-y)*dib->width())+px-x)*4;
      BYTE *dst=(BYTE *)get_data()+((py*width())+px)*4;

      // Do Multiply
      while ( dy-- )
      {
         for ( int i=0; i<dx; i++ )
         {
            dst[0]=(BYTE)(((src[0])*(dst[0]))>>8);
            dst[1]=(BYTE)(((src[1])*(dst[1]))>>8);
            dst[2]=(BYTE)(((src[2])*(dst[2]))>>8);
            dst+=4;
            src+=4;
         }
         dst+=(width()-dx)<<2;
         src+=(dib->width()-dx)<<2;
      }
   }

   void dib::ScreenRect ( dib *dib, int x, int y )
   {
      // Clip Rect
      int px=(x>=0) ? x : 0;
      int py=(y>=0) ? y : 0;
      int dx=((x+dib->width())<width()) ? dib->width() : width()-x;
      int dy=((y+dib->height())<height()) ? dib->height() : height()-y;
      dx=(x>=0) ? dx : dx + x;
      dy=(y>=0) ? dy : dy + y;

      // If Nothing to Screen return
      if ( (dx<=0) || (dy<=0) )
         return;

      // Prepare buffer Addresses
      BYTE *src=(BYTE *)dib->get_data()+(((py-y)*dib->width())+px-x)*4;
      BYTE *dst=(BYTE *)get_data()+((py*width())+px)*4;

      // Do Screen
      while ( dy-- )
      {
         for ( int i=0; i<dx; i++ )
         {
            dst[0]=(BYTE)(255-(((255-src[0])*(255-dst[0]))>>8));
            dst[1]=(BYTE)(255-(((255-src[1])*(255-dst[1]))>>8));
            dst[2]=(BYTE)(255-(((255-src[2])*(255-dst[2]))>>8));
            dst+=4;
            src+=4;
         }
         dst+=(width()-dx)<<2;
         src+=(dib->width()-dx)<<2;
      }
   }

   //////////////////////////////////////////////////////////////////////
   // Line Functions
   //////////////////////////////////////////////////////////////////////

   /*void dib::Line ( int x1, int y1, int x2, int y2, int R, int G, int B )
   {
   int dx, dy, k1, k2, d, x, y;
   COLORREF color=RGB ( B, G, R );

   dx=x2-x1;
   dy=y2-y1;
   d=(dy<<1)-dx;
   k1=dy<<1;
   k2=(dy-dx)<<1;
   x=x1;
   y=y1;

   get_data()[y*width()+x]=color;
   while (x<dx)
   {
   if (d<=0)
   {
   d+=k1;
   x++;
   }
   else
   {
   d+=k2;
   x++;
   y++;
   }
   get_data()[y*width()+x]=color;
   }
   }*/


   void dib::horizontal_line(int y, int R, int G, int B, int A, int x1, int x2)
   {
      if(width() == 0)
         return;
      x1 %= width();
      x2 %= width();
      if(x2 < 0)
         x2 += width();
      if(x1 < 0)
         x1 += width();
      COLORREF color=RGB ( B, G, R ) | (A << 24);
      COLORREF * pdata = get_data() + y * width();
      for(int x = x1; x <= x2; x++)
      {
         *pdata = color;
         pdata++;
      }
   }

   void dib::Line ( int x1, int y1, int x2, int y2, int R, int G, int B )
   {
      int d, x, y, ca, ay, sx, sy, dx, dy;
      COLORREF color=RGB ( B, G, R );

      dx=x2-x1;
      ca=abs ( dx )<<1;
      sx=(dx<0) ? -1 : 1;
      dy=y2-y1;
      ay=abs ( dy )<<1;
      sy=(dy<0) ? -1 : 1;
      x=x1;
      y=y1;

      if ( ca>ay )
      {
         d=ay-(ca>>1);
         while ( x!=x2 )
         {
            get_data()[y*width()+x]=color;
            if ( d>=0 )
            {
               y+=sy;
               d-=ca;
            }
            x+=sx;
            d+=ay;
         }
      }
      else
      {
         d=ca-(ay>>1);
         while ( y!=y2 )
         {
            get_data()[y*width()+x]=color;
            if ( d>=0 )
            {
               x+=sx;
               d-=ay;
            }
            y+=sy;
            d+=ca;
         }
      }
   }

   void dib::LineGlass ( int x1, int y1, int x2, int y2, int R, int G, int B, int A )
   {
      int d, x, y, ca, ay, sx, sy, dx, dy;
//      COLORREF color=RGB ( B, G, R );
      BYTE *dst=(BYTE *)get_data();

      dx=x2-x1;
      ca=abs ( dx )<<1;
      sx=(dx<0) ? -1 : 1;
      dy=y2-y1;
      ay=abs ( dy )<<1;
      sy=(dy<0) ? -1 : 1;
      x=x1;
      y=y1;

      if ( ca>ay )
      {
         d=ay-(ca>>1);
         while ( x!=x2 )
         {
            dst[(y*width()+x)<<2]=(BYTE)(((B-dst[(y*width()+x)<<2])*A+(dst[(y*width()+x)<<2]<<8))>>8);
            dst[((y*width()+x)<<2)+1]=(BYTE)(((G-dst[((y*width()+x)<<2)+1])*A+(dst[((y*width()+x)<<2)+1]<<8))>>8);
            dst[((y*width()+x)<<2)+2]=(BYTE)(((R-dst[((y*width()+x)<<2)+2])*A+(dst[((y*width()+x)<<2)+2]<<8))>>8);
            if ( d>=0 )
            {
               y+=sy;
               d-=ca;
            }
            x+=sx;
            d+=ay;
         }
      }
      else
      {
         d=ca-(ay>>1);
         while ( y!=y2 )
         {
            dst[(y*width()+x)<<2]=(BYTE)(((B-dst[(y*width()+x)<<2])*A+(dst[(y*width()+x)<<2]<<8))>>8);
            dst[((y*width()+x)<<2)+1]=(BYTE)(((G-dst[((y*width()+x)<<2)+1])*A+(dst[((y*width()+x)<<2)+1]<<8))>>8);
            dst[((y*width()+x)<<2)+2]=(BYTE)(((R-dst[((y*width()+x)<<2)+2])*A+(dst[((y*width()+x)<<2)+2]<<8))>>8);
            if ( d>=0 )
            {
               x+=sx;
               d-=ay;
            }
            y+=sy;
            d+=ca;
         }
      }
   }

   void dib::Mask(COLORREF crMask, COLORREF crInMask, COLORREF crOutMask)
   {
      COLORREF crFind = RGB(rgba_get_b(crMask), rgba_get_g(crMask), rgba_get_r(crMask));
      COLORREF crSet = RGB(rgba_get_b(crInMask), rgba_get_g(crInMask), rgba_get_r(crInMask));
      COLORREF crUnset  = RGB(rgba_get_b(crOutMask), rgba_get_g(crOutMask), rgba_get_r(crOutMask));

      int size=width()*height();

      for ( int i=0; i<size; i++ )
         if(get_data()[i]== crFind)
            get_data()[i] = crSet;
         else
            get_data()[i] = crUnset;

   }

   void dib::transparent_color(color color)
   {
      COLORREF crFind = color.get_rgb();
      __int64 iSize = area();

      for (int i=0; i<iSize; i++ )
         if((get_data()[i] & 0x00ffffff) == crFind)
            ((LPBYTE)&get_data()[i])[3] = 255;
         else
            ((LPBYTE)&get_data()[i])[3] = 0;
   }

   void dib::channel_mask(unsigned char uchFind, unsigned char uchSet, unsigned char uchUnset, visual::rgba::echannel echannel)
   {
      int size = width() * height();
      unsigned char * puch = (unsigned char * ) get_data();
      puch += ((int) echannel) % 4;

      for(int i = 0; i < size; i++)
      {
         if(*puch == uchFind)
            *puch = uchSet;
         else
            *puch = uchUnset;
         puch += 4;
      }
   }

   DWORD dib::GetPixel(int x, int y)
   {
      DWORD dw = *(get_data() + x + (height() - y - 1) * width());
      return RGB(rgba_get_b(dw), rgba_get_g(dw), rgba_get_r(dw));
   }

   // too slow for animation on AMD XP Atlhon.
   // TOP SUGGESTION:
   // The gradient can´t have more then 256 levels of the most bright color
   // (white). So creating a radial fill of radius 256 and then using fasting
   // stretching algorithms is much faster than calculating radial fill.
   void dib::RadialFill(BYTE alpha, BYTE red, BYTE green, BYTE blue, int xCenter, int yCenter, int iRadius)
   {
      if (iRadius == 0)
         return;
      /*if(version == 0)
      {

      int iR = iRadius - 1;

      int xL = xCenter - iR;
      int xU = xCenter + iR;
      int yL = yCenter - iR;
      int yU = yCenter + iR;


      if(xL < 0) xL = 0;
      if(xU >= m_Size.cx) xU = m_Size.cx - 1;
      if(yL < 0) yL = 0;
      if(yU >= m_Size.cy) yU = m_Size.cy - 1;


      BYTE *dst = ((BYTE*)(get_data() + xL + yL * m_Size.cx));
      DWORD dwAdd = ((m_Size.cx - 1 - xU) + xL) * 4;
      int size=m_Size.cx*m_Size.cy;
      double iLevel;

      int dx, dy;
      int dx0, dy0;
      int dx1, dy1;
      int dx2, dy2;
      int dx3, dy3;
      int dx4, dy4;
      int dx5, dy5;
      int dx6, dy6;
      int dx7, dy7;
      int dx8, dy8;
      int dx9, dy9;
      int dxA, dyA;
      int dxB, dyB;
      int dxC, dyC;
      int dxD, dyD;
      int dxE, dyE;
      int dxF, dyF;

      unsigned long dr;
      unsigned long dq;
      unsigned long dr0, dq0;
      unsigned long dr1, dq1;
      unsigned long dr2, dq2;
      unsigned long dr3, dq3;
      unsigned long dr4, dq4;
      unsigned long dr5, dq5;
      unsigned long dr6, dq6;
      unsigned long dr7, dq7;
      unsigned long dr8, dq8;
      unsigned long dr9, dq9;
      unsigned long drA, dqA;
      unsigned long drB, dqB;
      unsigned long drC, dqC;
      unsigned long drD, dqD;
      unsigned long drE, dqE;
      unsigned long drF, dqF;
      int x, y;

      {
      for(y = yL; y <= yU; y++)
      {
      for(x = xL; x <= xU; x++)
      {
      dx = abs(x - xCenter);
      dy = abs(y - yCenter);
      isqrt((dx * dx) + (dy * dy), &dr, &dq);
      if(dr < iRadius)
      {
      iLevel = 1.0 - dr * 1.0 / iRadius;
      dst[0] = blue  * iLevel;
      dst[1] = green * iLevel;
      dst[2] = red   * iLevel;
      }
      dst += 4;
      }
      dst += dwAdd;
      }
      }
      }
      else if(version == 1)*/
      {

         LPBYTE lpbAlloc = (LPBYTE) malloc((iRadius * iRadius) + 4);
         LPBYTE lpb = (LPBYTE) (((int) lpbAlloc + 3) & ~3);


         int x, y;
         int b;

//         int r2 = iRadius * iRadius;

         for(y = 0; y < iRadius; y++)
         {
            for(x = y; x < iRadius; x++)
            {
               b = (int) (sqrt((double) (x * x) + (y * y)) * 255 / iRadius);
               if(b > 255)
                  b = 0;
               else
                  b = 255 - b;


               lpb[x + y * iRadius] = (byte) b;
               lpb[y + x * iRadius] = (byte) b;
            }
         }


         int iR = iRadius - 1;

         int xL = xCenter - iR;
         int xU = xCenter + iR;
         int yL = yCenter - iR;
         int yU = yCenter + iR;


         if(xL < 0) xL = 0;
         if(xU >= width()) xU = width() - 1;
         if(yL < 0) yL = 0;
         if(yU >= height()) yU = height() - 1;


         BYTE *dst = ((BYTE*)(get_data() + xL + yL * width()));
         DWORD dwAdd = ((width() - 1 - xU) + xL) * 4;
//         int size=width()*height();

         int dx, dy;

         // Top Left

         for(y = yL; y <= yU; y++)
         {
            for(x = xL; x <= xU; x++)
            {
               dx = abs(x - xCenter);
               dy = abs(y - yCenter);
               b = lpb[dx + dy * iRadius];
               dst[0] = byte(blue     * b / 255);
               dst[1] = byte(green    * b / 255);
               dst[2] = byte(red      * b / 255);
               dst[3] = byte(alpha    * b / 255);
               dst += 4;
            }
            dst += dwAdd;
         }

         free(lpbAlloc);
      }
   }


   void dib::RadialFill(
      BYTE alpha1, BYTE red1, BYTE green1, BYTE blue1,
      BYTE alpha2, BYTE red2, BYTE green2, BYTE blue2,
      int xCenter, int yCenter, int iRadius)
   {
      if (iRadius == 0)
         return;
      /*if(version == 0)
      {

      int iR = iRadius - 1;

      int xL = xCenter - iR;
      int xU = xCenter + iR;
      int yL = yCenter - iR;
      int yU = yCenter + iR;


      if(xL < 0) xL = 0;
      if(xU >= m_Size.cx) xU = m_Size.cx - 1;
      if(yL < 0) yL = 0;
      if(yU >= m_Size.cy) yU = m_Size.cy - 1;


      BYTE *dst = ((BYTE*)(get_data() + xL + yL * m_Size.cx));
      DWORD dwAdd = ((m_Size.cx - 1 - xU) + xL) * 4;
      int size=m_Size.cx*m_Size.cy;
      double iLevel;

      int dx, dy;
      int dx0, dy0;
      int dx1, dy1;
      int dx2, dy2;
      int dx3, dy3;
      int dx4, dy4;
      int dx5, dy5;
      int dx6, dy6;
      int dx7, dy7;
      int dx8, dy8;
      int dx9, dy9;
      int dxA, dyA;
      int dxB, dyB;
      int dxC, dyC;
      int dxD, dyD;
      int dxE, dyE;
      int dxF, dyF;

      unsigned long dr;
      unsigned long dq;
      unsigned long dr0, dq0;
      unsigned long dr1, dq1;
      unsigned long dr2, dq2;
      unsigned long dr3, dq3;
      unsigned long dr4, dq4;
      unsigned long dr5, dq5;
      unsigned long dr6, dq6;
      unsigned long dr7, dq7;
      unsigned long dr8, dq8;
      unsigned long dr9, dq9;
      unsigned long drA, dqA;
      unsigned long drB, dqB;
      unsigned long drC, dqC;
      unsigned long drD, dqD;
      unsigned long drE, dqE;
      unsigned long drF, dqF;
      int x, y;

      {
      for(y = yL; y <= yU; y++)
      {
      for(x = xL; x <= xU; x++)
      {
      dx = abs(x - xCenter);
      dy = abs(y - yCenter);
      isqrt((dx * dx) + (dy * dy), &dr, &dq);
      if(dr < iRadius)
      {
      iLevel = 1.0 - dr * 1.0 / iRadius;
      dst[0] = blue  * iLevel;
      dst[1] = green * iLevel;
      dst[2] = red   * iLevel;
      }
      dst += 4;
      }
      dst += dwAdd;
      }
      }
      }
      else if(version == 1)*/
      {

         LPBYTE lpbAlloc = (LPBYTE) malloc((iRadius * iRadius) + 4);
         LPBYTE lpb = (LPBYTE) (((int) lpbAlloc + 3) & ~3);


         int x, y;
         int b;

//         int r2 = iRadius * iRadius;

         for(y = 0; y < iRadius; y++)
         {
            for(x = y; x < iRadius; x++)
            {
               b = (int) (sqrt((double) (x * x) + (y * y)) * 255 / iRadius);
               if(b > 255)
                  b = 0;
               else
                  b = ~b;


               lpb[x + y * iRadius] = (byte) b;
               lpb[y + x * iRadius] = (byte) b;
            }
         }


         int iR = iRadius - 1;

         int xL = xCenter - iR;
         int xU = xCenter + iR;
         int yL = yCenter - iR;
         int yU = yCenter + iR;


         if(xL < 0) xL = 0;
         if(xU >= width()) xU = width() - 1;
         if(yL < 0) yL = 0;
         if(yU >= height()) yU = height() - 1;


         BYTE *dst = ((BYTE*)(get_data() + xL + yL * width()));
         DWORD dwAdd = ((width() - 1 - xU) + xL) * 4;
//         int size=width()*height();

         int dx, dy;

         BYTE bComp;

         // Top Left

         for(y = yL; y <= yU; y++)
         {
            for(x = xL; x <= xU; x++)
            {
               dx = abs(x - xCenter);
               dy = abs(y - yCenter);
               b = lpb[dx + dy * iRadius];
               bComp = (byte) ~b;
               dst[0] = byte(((blue1  * b) + (blue2  * bComp)) / 255);
               dst[1] = byte(((green1 * b) + (green2 * bComp)) / 255);
               dst[2] = byte(((red1   * b) + (red2   * bComp)) / 255);
               dst[3] = byte(((alpha1 * b) + (alpha2 * bComp)) / 255);
               dst += 4;
            }
            dst += dwAdd;
         }

         free(lpbAlloc);
      }
   }

   void dib::SetIconMask(::visual::icon * picon, int cx, int cy)
   {
      create(cx, cy);

      if(cx <= 0 || cy <= 0)
         return;




      // White blend dib
      dib dib1;
      dib1.create(cx, cy);
      dib1.Fill(255, 255, 255);

      dib1.get_graphics()->DrawIcon(
         0, 0,
         picon,
         cx, cy,
         0,
         NULL,
         DI_IMAGE | DI_MASK);

      // Black blend dib
      ::ca::dib_sp spdib2(get_app());
      spdib2->create(cx, cy);
      spdib2->Fill(0, 0, 0);

      spdib2->get_graphics()->DrawIcon(
         0, 0,
         picon,
         cx, cy,
         0,
         NULL,
         DI_IMAGE | DI_MASK);

      // Mask dib
      dib dibM;
      dibM.create(cx, cy);

      dibM.get_graphics()->DrawIcon(
         0, 0,
         picon,
         cx, cy,
         0,
         NULL,
         DI_MASK);

      BYTE * r1=(BYTE*)dib1.get_data();
      BYTE * r2=(BYTE*)spdib2->get_data();
      BYTE * srcM=(BYTE*)dibM.get_data();
      BYTE * dest=(BYTE*)get_data();
      int iSize = width()*height();

      BYTE b;
      BYTE bMax;
      while ( iSize-- > 0)
      {
         if(srcM[0] == 255)
         {
            bMax = 0;
         }
         else
         {
            bMax = 0;
            b =(BYTE)(r1[0]  - r2[0]);
            bMax = max(b, bMax);
            b =(BYTE)(r1[1]  - r2[1]);
            bMax = max(b, bMax);
            b =(BYTE)(r1[2]  - r2[2]);
            bMax = max(b, bMax);
            bMax = 255 - bMax;
         }
         dest[0]  =  bMax;
         dest[1]  =  bMax;
         dest[2]  =  bMax;
         dest     += 4;
         srcM     += 4;
         r1       += 4;
         r2       += 4;
      }



   }

   void dib::rotate(dib * pdib, double dAngle, double dScale)
   {
      // ::ca::dib_sp spdib(get_app());
      //   spdib->Paste(this);

      int cx = width();
      int cy = height();

      int l = max(cx, cy);


      int jmax = min(l, cy / 2);
      int jmin = - jmax;
      int imax = min(l, cx / 2);
      int imin = - imax;


      int joff = cy / 2;
      int ioff = cx / 2;

      //int iAngle = iStep % 360;
      //int iAngle = iStep;
      //int iAngle = 1;
      //int k = 0;

      /*     for ( int j=jmin; j<jmax; j++ )
      {
      for ( int i=imin; i<imax; i++ )
      {
      int x, y;

      // A Combination of a 2d Translation/rotation/Scale Matrix
      x=int(cos10(i, iAngle) - sin10(j, iAngle)) + ioff;
      y=int(sin10(i, iAngle) + cos10(j, iAngle)) + joff;
      get_data()[(j+joff)*cx+(i+ioff)]=
      spdib->get_data()[abs(y%height())*width()+abs(x%width())];
      //k++;
      }
      (j+joff)*cx+(i+ioff)
      }*/

      int k = 0;
      double dCos = ::cos(dAngle * pi() / 180.0) * dScale;
      double dSin = ::sin(dAngle * pi() / 180.0) * dScale;
      int cx1 = width() - 1;
      int cy1 = height() - 1;
      for ( int j=jmin; j<jmax; j++ )
      {
         for ( int i=imin; i<imax; i++ )
         {
            int x, y;

            // A Combination of a 2d Translation/rotation/Scale Matrix
            //x=abs((int(dCos * i - dSin * j) + ioff) % width());
            //y=abs((int(dSin * i + dCos * j) + joff) % height());

            x = (int) abs((dCos * i - dSin * j) + ioff);
            y = (int) abs((dSin * i + dCos * j) + joff);

            if((x / width()) % 2 == 0)
            {
               x %= width();
            }
            else
            {
               x = cx1 - (x % width());
            }

            if((y / height()) % 2 == 0)
            {
               y %= height();
            }
            else
            {
               y = cy1 - (y % height());
            }



            get_data()[(j+joff)*cx+(i+ioff)]=
               pdib->get_data()[y * cx + x];
            k++;
         }
      }
   }


   void dib::Rotate034(dib * pdib, double dAngle, double dScale)
   {

      int cx = width();
      int cy = height();

      int l = max(cx, cy);


      int jmax = min(l, cy / 2);
      int jmin = - jmax;
      int imax = min(l, cx / 2);
      int imin = - imax;


      if((cy % 2) == 1)
         jmax++;

      if((cx % 2) == 1)
         imax++;

      int joff = cy / 2;
      int ioff = cx / 2;


      int k = 0;
      double dCos = ::cos(dAngle * pi() / 180.0) * dScale;
      double dSin = ::sin(dAngle * pi() / 180.0) * dScale;
      int cx1 = width() - 1;
      int cy1 = height() - 1;
      for ( int j=jmin; j<jmax; j++ )
      {
         for ( int i=imin; i<imax; i++ )
         {
            int x, y;

            // A Combination of a 2d Translation/rotation/Scale Matrix
            //x=abs((int(dCos * i - dSin * j) + ioff) % width());
            //y=abs((int(dSin * i + dCos * j) + joff) % height());

            x = (int) abs((dCos * i - dSin * j) + ioff);
            y = (int) abs((dSin * i + dCos * j) + joff);

            if((x / width()) % 2 == 0)
            {
               x %= width();
            }
            else
            {
               x = cx1 - (x % width());
            }

            if((y / height()) % 2 == 0)
            {
               y %= height();
            }
            else
            {
               y = cy1 - (y % height());
            }



            get_data()[(j+joff)*cx+(i+ioff)]=
               pdib->get_data()[y * cx + x];
            k++;
         }
      }
   }

   void dib::rotate(
      dib * pdib,
      LPCRECT lpcrect,
      double dAngle,
      double dScale)
   {
      // ::ca::dib_sp spdib(get_app());
      //   spdib->Paste(this);



      rect rect(lpcrect);

      int cx = rect.width();
      int cy = rect.height();

      int l = max(cx, cy);

      int jmax = min(l, cy / 2);
      int jmin = - jmax;
      int imax = min(l, cx / 2);
      int imin = - imax;


      int joff = cy / 2 + rect.left;
      int ioff = cx / 2 + rect.top;

      //int iAngle = iStep % 360;
      //int iAngle = iStep;
      //int iAngle = 1;
      //int k = 0;

      /*     for ( int j=jmin; j<jmax; j++ )
      {
      for ( int i=imin; i<imax; i++ )
      {
      int x, y;

      // A Combination of a 2d Translation/rotation/Scale Matrix
      x=int(cos10(i, iAngle) - sin10(j, iAngle)) + ioff;
      y=int(sin10(i, iAngle) + cos10(j, iAngle)) + joff;
      get_data()[(j+joff)*cx+(i+ioff)]=
      spdib->get_data()[abs(y%height())*width()+abs(x%width())];
      //k++;
      }
      (j+joff)*cx+(i+ioff)
      }*/

      int k = 0;
      double dCos = ::cos(dAngle * pi() / 180.0) * dScale;
      double dSin = ::sin(dAngle * pi() / 180.0) * dScale;
      int cx1 = cx - 1;
      int cy1 = cy - 1;
      for ( int j=jmin; j<jmax; j++ )
      {
         for ( int i=imin; i<imax; i++ )
         {
            int x, y;

            // A Combination of a 2d Translation/rotation/Scale Matrix
            //x=abs((int(dCos * i - dSin * j) + ioff) % width());
            //y=abs((int(dSin * i + dCos * j) + joff) % height());

            x = (int) abs((dCos * i - dSin * j) + ioff);
            y = (int) abs((dSin * i + dCos * j) + joff);

            if((x / cx) % 2 == 0)
            {
               x %= cx;
            }
            else
            {
               x = cx1 - (x % cx);
            }

            if((y / cy) % 2 == 0)
            {
               y %= cy;
            }
            else
            {
               y = cy1 - (y % cy);
            }



            get_data()[(j+joff)*width()+(i+ioff)]=
               pdib->get_data()[y * width() + x];
            k++;
         }
      }
   }

   /*int dib::cos(int i, int iAngle)
   {
   return (int) (((_int64) i * CosN[iAngle]) >> 32);
   }

   int dib::sin(int i, int iAngle)
   {
   return (int) (((_int64) i * SinN[iAngle]) >> 32);
   }*/




   void dib::Fill (int A, int R, int G, int B )
   {
      COLORREF color = RGB ( B, G, R ) | (A << 24);
      int size=width()*height();

      COLORREF * pcr;

      int iSize32 = size / 32;
      int i;
      for (i=0; i < iSize32; i+=32 )
      {
         pcr = &get_data()[i];
         pcr[0] = color;
         pcr[1] = color;
         pcr[2] = color;
         pcr[3] = color;
         pcr[4] = color;
         pcr[5] = color;
         pcr[6] = color;
         pcr[7] = color;
         pcr[8] = color;
         pcr[9] = color;
         pcr[10] = color;
         pcr[11] = color;
         pcr[12] = color;
         pcr[13] = color;
         pcr[14] = color;
         pcr[15] = color;
         pcr[16] = color;
         pcr[17] = color;
         pcr[18] = color;
         pcr[19] = color;
         pcr[20] = color;
         pcr[21] = color;
         pcr[22] = color;
         pcr[23] = color;
         pcr[24] = color;
         pcr[25] = color;
         pcr[26] = color;
         pcr[27] = color;
         pcr[28] = color;
         pcr[29] = color;
         pcr[30] = color;
         pcr[31] = color;
      }

      for (i=0; i<size; i++ )
      {
         get_data()[i]=color;
      }

   }

   COLORREF dib::GetAverageColor()
   {
      double dR = 0.0;
      double dG = 0.0;
      double dB = 0.0;
      int iRLine;
      int iGLine;
      int iBLine;
      double dDiv = width() * height();
      if(dDiv > 0)
      {
         LPBYTE lpb = (LPBYTE) get_data();
         for (int y = 0; y < height(); y++)
         {
            iRLine = 0;
            iGLine = 0;
            iBLine = 0;
            for (int x = 0; x < width(); x++)
            {
               iRLine += lpb[2];
               iGLine += lpb[1];
               iBLine += lpb[0];
               lpb += 4;
            }
            dR += iRLine / dDiv;
            dG += iGLine / dDiv;
            dB += iBLine / dDiv;
         }
         int iR = (int) dR;
         int iG = (int) dG;
         int iB = (int) dB;
         return RGB(iR, iG, iB);
      }
      else
      {
         return 0;
      }

   }


   void dib::do_xor(dib * pdib)
   {
      if(width() != pdib->width()
         || height() != pdib->height())
      {
         return;
      }
      int iCount = width() * height();
      LPDWORD lpd1 = (LPDWORD) get_data();
      LPDWORD lpd2 = (LPDWORD) pdib->get_data();
      for(int i = 0; i < iCount; i++)
      {
         *lpd1 = *lpd1 ^ *lpd2;
         lpd1++;
         lpd2++;
      }
   }

   void dib::create_frame(class size size, int iFrameCount)
   {
      int iSliceCount = (int) sqrt((double) iFrameCount);
      int iFrameWidth = size.cx / iSliceCount;
      int iFrameHeight = size.cy / iSliceCount;
      create(iFrameWidth, iFrameHeight);
   }

   void dib::set_frame1(void * lpdata, int iFrame, int iFrameCount)
   {
      int iSliceCount = (int) sqrt((double) iFrameCount);
      if(iSliceCount == 0)
         iSliceCount = 1;
      int iFrameWidth = width() / iSliceCount;
      int iFrameHeight = height() / iSliceCount;
      int iX = iFrame % iSliceCount;
      int iY = iFrame / iSliceCount;
      COLORREF * lpDest = &get_data()[iFrameWidth * iX + iY * iFrameHeight * width()];
      COLORREF * lpSrc = (COLORREF *) lpdata;
      COLORREF * lpDestLine;
      for(int y = 0; y < iFrameHeight; y++)
      {
         lpDestLine = &lpDest[y * width()];
         for(int x = 0; x < iFrameWidth; x++)
         {
            *lpDestLine = *lpSrc;
            lpDestLine++;
            lpSrc++;
         }
      }
   }

   void dib::set_frame2(void * lpdata, int iFrame, int iFrameCount)
   {
      int iSliceCount = (int) sqrt((double) iFrameCount);
      if(iSliceCount == 0)
         iSliceCount = 1;
      int iFrameWidth = width() / iSliceCount;
      int iFrameHeight = height() / iSliceCount;
      int iX = iFrame % iSliceCount;
      int iY = iFrame / iSliceCount;
      COLORREF * lpDest = &get_data()[iFrameWidth * iX + iY * iFrameHeight * width()];
      COLORREF * lpSrc = (COLORREF *) lpdata;
      COLORREF * lpDestLine;
      for(int y = iFrameHeight - 1; y >= 0; y--)
      {
         lpDestLine = &lpDest[y * width()];
         for(int x = 0; x < iFrameWidth; x++)
         {
            *lpDestLine = *lpSrc;
            lpDestLine++;
            lpSrc++;
         }
      }
   }

   void dib::xor_dib_frame2(void * lpdata, int iFrame, int iFrameCount)
   {
      int iSliceCount = (int) sqrt((double) iFrameCount);
      if(iSliceCount == 0)
         iSliceCount = 1;
      int iFrameWidth = width() / iSliceCount;
      int iFrameHeight = height() / iSliceCount;
      int iX = iFrame % iSliceCount;
      int iY = iFrame / iSliceCount;
      COLORREF * lpDest = &get_data()[iFrameWidth * iX + iY * iFrameHeight * width()];
      COLORREF * lpSrc = (COLORREF *) lpdata;
      COLORREF * lpDestLine;
      for(int y = iFrameHeight - 1; y >= 0; y--)
      {
         lpDestLine = &lpDest[y * width()];
         for(int x = 0; x < iFrameWidth; x++)
         {
            *lpDestLine ^= *lpSrc;
            lpDestLine++;
            lpSrc++;
         }
      }
   }

   void dib::get_frame(void * lpdata, int iFrame, int iFrameCount)
   {
      int iSliceCount = (int) sqrt((double) iFrameCount);
      int iFrameWidth = width() / iSliceCount;
      int iFrameHeight = height() / iSliceCount;
      int iX = iFrame % iSliceCount;
      int iY = iFrame / iSliceCount;
      COLORREF * lpSrc = &get_data()[iFrameWidth * iX + iY * iFrameHeight *  width()];
      COLORREF * lpDest = (COLORREF *) lpdata;
      COLORREF * lpSrcLine;
      for(int y = 0; y < iFrameHeight; y++)
      {
         lpSrcLine = &lpSrc[y * width()];
         for(int x = 0; x < iFrameWidth; x++)
         {
            *lpDest = *lpSrcLine;
            lpDest++;
            lpSrcLine++;
         }
      }
   }

   bool dib::is_rgb_black()
   {
      int iSize = width() * height();
      COLORREF * lp = get_data();
      for(int i = 0; i < iSize; i++)
      {
         if((*lp & 0x00FFFFFF) != 0)
            return false;
         lp++;
      }
      return true;
   }

   void dib::DivideRGB(int iDivide)
   {
      if(iDivide == 0)
      {
         return;
      }
      int iCount = width() * height();
      LPBYTE lp = ((LPBYTE) get_data());
      int i = 0;
      int iCount1 = iCount - iCount % 8;
      for(; i < iCount1; i++)
      {
         lp[0] /= (byte) iDivide;
         lp[1] /= (byte) iDivide;
         lp[2] /= (byte) iDivide;

         lp[4] /= (byte) iDivide;
         lp[5] /= (byte) iDivide;
         lp[6] /= (byte) iDivide;

         lp[8] /= (byte) iDivide;
         lp[9] /= (byte) iDivide;
         lp[10] /= (byte) iDivide;

         lp[12] /= (byte) iDivide;
         lp[13] /= (byte) iDivide;
         lp[14] /= (byte) iDivide;

         lp[16] /= (byte) iDivide;
         lp[17] /= (byte) iDivide;
         lp[28] /= (byte) iDivide;

         lp[20] /= (byte) iDivide;
         lp[21] /= (byte) iDivide;
         lp[22] /= (byte) iDivide;

         lp[24] /= (byte) iDivide;
         lp[25] /= (byte) iDivide;
         lp[26] /= (byte) iDivide;

         lp[28] /= (byte) iDivide;
         lp[29] /= (byte) iDivide;
         lp[30] /= (byte) iDivide;

         lp += 4 * 8;
      }
      for(; i < iCount; i++)
      {
         lp[0] /= (byte) iDivide;
         lp[1] /= (byte) iDivide;
         lp[2] /= (byte) iDivide;
         lp +=4;
      }
   }

   void dib::DivideARGB(int iDivide)
   {
      if(iDivide == 0)
      {
         return;
      }
      int iCount = width() * height();
      LPBYTE lp = ((LPBYTE) get_data());
      for(int i = 0; i < iCount; i++)
      {
         lp[0] /= (byte) iDivide;
         lp[1] /= (byte) iDivide;
         lp[2] /= (byte) iDivide;
         lp[3] /= (byte) iDivide;
         lp +=4;
      }
   }

   void dib::DivideA(int iDivide)
   {
      if(iDivide == 0)
      {
         return;
      }
      int iCount = width() * height();
      LPBYTE lp = ((LPBYTE) get_data());
      for(int i = 0; i < iCount; i++)
      {
         lp[3] /= (byte) iDivide;
         lp +=4;
      }
   }


   void dib::stretch_dib(dib * pdib)
   {
      UNREFERENCED_PARAMETER(pdib);
      throw interface_only_exception();
   }

   int dib::cos(int i, int iAngle)
   {
      UNREFERENCED_PARAMETER(i);
      UNREFERENCED_PARAMETER(iAngle);
      throw interface_only_exception();
   }

   int dib::sin(int i, int iAngle)
   {
      UNREFERENCED_PARAMETER(i);
      UNREFERENCED_PARAMETER(iAngle);
      throw interface_only_exception();
   }

   int dib::cos10(int i, int iAngle)
   {
      UNREFERENCED_PARAMETER(i);
      UNREFERENCED_PARAMETER(iAngle);
      throw interface_only_exception();
   }

   int dib::sin10(int i, int iAngle)
   {
      UNREFERENCED_PARAMETER(i);
      UNREFERENCED_PARAMETER(iAngle);
      throw interface_only_exception();
   }

   int dib::width()
   {
      throw interface_only_exception();
   }

   int dib::height()
   {
      throw interface_only_exception();
   }

   __int64 dib::area()
   {
      return ((__int64) width()) * ((__int64)height());
   }

   size dib::size()
   {
      return size64(width(), height());
   }

   double dib::pi()
   {
      return atan(1.0)*4.0;
   }


   void dib::fill_channel(int C, visual::rgba::echannel echannel)
   {
      UNREFERENCED_PARAMETER(C);
      UNREFERENCED_PARAMETER(echannel);
      throw interface_only_exception();
   }


   void dib::channel_copy(visual::rgba::echannel echannelDst, visual::rgba::echannel echannelSrc)
   {
      echannelDst = (visual::rgba::echannel) (((int) echannelDst) % 4);
      echannelSrc = (visual::rgba::echannel) (((int) echannelSrc) % 4);
      if(echannelDst == echannelSrc)
         return;
      byte * lpDst = &((byte *) get_data())[((int)echannelDst)];
      byte * lpSrc = &((byte *) get_data())[((int)echannelSrc)];
      __int64 iArea = area();
      while(iArea > 0)
      {
         *lpDst = *lpSrc;
         lpDst += 4;
         lpSrc += 4;
         iArea--;
      }
   }

   void dib::write(::ex1::byte_output_stream & ostream)
   {
      ostream << (int) width();
      ostream << (int) height();
      if(area() <= 0)
         return;
      ostream.write(get_data(), (::primitive::memory_size)(sizeof(COLORREF) * area()));
   }

   void dib::read(::ex1::byte_input_stream & istream)
   {
      int width;
      int height;
      istream >> width;
      if(width < 0)
         return;
      istream >> height;
      if(height < 0)
         return;
      if((width * height) <= 0)
         return;
      if(!create(width, height))
         throw 0;
      istream.read(get_data(), (::primitive::memory_size)(sizeof(COLORREF) * area()));
   }

   void dib::set_rgb ( int R, int G, int B )
   {
      UNREFERENCED_PARAMETER(R);
      UNREFERENCED_PARAMETER(G);
      UNREFERENCED_PARAMETER(B);
      throw not_implemented_exception();
   }

   bool dib::rgb_from(::ca::dib * pdib)
   {
      if(!create(pdib->size()))
         return false;
      try
      {
         byte * puchSrc = (byte *) get_data();
         byte * puchDst = (byte *) pdib->get_data();
         __int64 iArea = pdib->area();
         while(iArea > 0)
         {
            *puchDst++ = *puchSrc++;
            *puchDst++ = *puchSrc++;
            *puchDst++ = *puchSrc++;
            puchDst++;
            puchSrc++;
            iArea--;
         }
      }
      catch(...)
      {
         return false;
      }
      return true;
   }

   bool dib::from(::ca::graphics * pgraphics, FIBITMAP * pfibitmap, bool bUnloadFI)
   {
      throw interface_only_exception();
      return false;
   }

} // namespace ca
