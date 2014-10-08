//   Creator : El Barto (ef00@luc.ac.be)
//   Location : http://www.luc.ac.be/~ef00/ebgfx
//   Date : 09-04-98
//////////////////////////////////////////////////////////////////////
#include "framework.h"
#include "draw2d.h"
#include <math.h>

byte byte_clip(double d);


byte byte_clip(double d)
{
   if(d >= 255.0)
      return 255;
   if(d <= 0.0)
      return 0;
   return (byte) d;
}

namespace draw2d
{

   //   Creator : El Barto (ef00@luc.ac.be)
   //   Location : http://www.luc.ac.be/~ef00/ebgfx
   //   Date : 09-04-98
   //////////////////////////////////////////////////////////////////////


   float dib::Cosines[360];
   float dib::Sines[360];

   int64_t dib::CosN[360]; // * 1 << 31
   int64_t dib::SinN[360];

   int64_t dib::Cos10N[10]; // until 10 degress
   int64_t dib::Sin10N[10]; // more precision * 1 << 34

   double dib::dPi;

   dib::dib()
   {

      m_size.cx      = 0;

      m_size.cy      = 0;

      m_iScan    = 0;

   }


   dib::~dib()
   {

   }


   ::draw2d::graphics * dib::get_graphics()
   {

      throw interface_only_exception(get_app());

   }


   ::draw2d::bitmap_sp dib::get_bitmap()
   {

      throw interface_only_exception(get_app());

   }


   ::draw2d::bitmap_sp dib::detach_bitmap()
   {

      throw interface_only_exception(get_app());

   }


   void dib::construct (int32_t cx,  int32_t cy)
   {

      UNREFERENCED_PARAMETER(cx);
      UNREFERENCED_PARAMETER(cy);

      throw interface_only_exception(get_app());

   }


   COLORREF * dib::get_data()
   {

      return m_pcolorref;

   }


   bool dib::realize(::draw2d::graphics * pdc)
   {

      UNREFERENCED_PARAMETER(pdc);
      return true;

   }


   bool dib::unrealize()
   {

      return true;

   }


   bool dib::is_realized()
   {

      return true;

   }

   bool dib::defer_realize(::draw2d::graphics * pdc)
   {

      if(is_realized())
         return true;

      return realize(pdc);

   }


   bool dib::create(class size size)
   {
      return create(size.cx, size.cy);
   }

   bool dib::create(int32_t width, int32_t height)
   {
      return create(::size(width, height));
   }

   bool dib::dc_select(bool bSelect)
   {
      UNREFERENCED_PARAMETER(bSelect);
      throw interface_only_exception(get_app());
   }

   bool dib::create(::draw2d::graphics * pdc)
   {
      ::draw2d::bitmap & bitmap = *pdc->get_current_bitmap();
      if(&bitmap == NULL)
         return FALSE;

      throw not_implemented(get_app());
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

   bool dib::Destroy ()
   {
      throw interface_only_exception(get_app());
   }

   bool dib::to(::draw2d::graphics * pgraphics)
   {
      return to(pgraphics, null_point(), size());
   }

   bool dib::to(::draw2d::graphics * pgraphics, point pt)
   {
      return to(pgraphics, pt, size());
   }

   bool dib::to(::draw2d::graphics * pgraphics, class size size)
   {
      return to(pgraphics, null_point(), size);
   }

   bool dib::to(::draw2d::graphics * pgraphics, const RECT & rect)
   {
      return to(pgraphics,::top_left(rect),::size(rect));
   }

   bool dib::to(::draw2d::graphics * pgraphics, point pt, class size size)
   {
      return to(pgraphics, pt, size, point(0, 0));
   }

   bool dib::to(::draw2d::graphics * pgraphics, point pt, class size size, point ptSrc)
   {
      UNREFERENCED_PARAMETER(pgraphics);
      UNREFERENCED_PARAMETER(pt);
      UNREFERENCED_PARAMETER(size);
      UNREFERENCED_PARAMETER(ptSrc);
      throw interface_only_exception(get_app());
   }

   bool dib::from(::draw2d::dib * pdib)
   {

      if(!create(pdib->size()))
         return false;

      map();
      pdib->map();
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

   bool dib::from(::draw2d::graphics * pdc)
   {
      UNREFERENCED_PARAMETER(pdc);
      throw interface_only_exception(get_app());
   }

   bool dib::from(point ptDst, ::draw2d::graphics * pdc, point ptSrc, class size size)
   {
      return get_graphics()->from(ptDst, size, pdc, ptSrc, SRCCOPY) != FALSE;
   }

   bool dib::from(point ptDst, ::draw2d::dib * pdibSrc, point ptSrc, class size size)
   {

      dib * pdibDst = this;

      pdibDst->map();
      pdibSrc->map();

      if(ptSrc.x < 0)
      {
         ptDst.x -= ptSrc.x;
         ptSrc.x = 0;
      }

      if(ptSrc.y < 0)
      {
         ptDst.y -= ptSrc.y;
         ptSrc.y = 0;
      }

      if(ptDst.x < 0)
      {
         size.cx += ptDst.x;
         ptDst.x = 0;
      }

      if(size.cx < 0)
         return true;

      if(ptDst.y < 0)
      {
         size.cy += ptDst.y;
         ptDst.y = 0;
      }

      if(size.cy < 0)
         return true;

      int xEnd = MIN(size.cx, MIN(pdibSrc->m_size.cx - ptSrc.x, pdibDst->m_size.cx - ptDst.x));

      int yEnd = MIN(size.cy, MIN(pdibSrc->m_size.cy - ptSrc.y, pdibDst->m_size.cy - ptDst.y));

      if(xEnd < 0)
         return false;

      if(yEnd < 0)
         return false;

      int32_t scanDst = pdibDst->m_iScan;

      int32_t scanSrc = pdibSrc->m_iScan;

      byte * pdst = &((byte *)pdibDst->m_pcolorref)[scanDst * ptDst.y + ptDst.x * sizeof(COLORREF)];

      byte * psrc = &((byte *)pdibSrc->m_pcolorref)[scanSrc * ptSrc.y + ptSrc.x * sizeof(COLORREF)];

      COLORREF * pdst2;

      COLORREF * psrc2;

      for(int y = 0; y < yEnd; y++)
      {

         pdst2 = (COLORREF *) &pdst[scanDst * y];

         psrc2 = (COLORREF *)&psrc[scanSrc * y];

         for(int x = 0; x < xEnd; x++)
         {

            *pdst2 = *psrc2;

            pdst2++;

            psrc2++;

         }

      }

      return true;

   }

   bool dib::from_ignore_alpha(point ptDst, ::draw2d::dib * pdib, point ptSrc, class size size)
   {

      if(ptDst.x < 0)
      {
         size.cx += ptDst.x;
         ptDst.x = 0;
      }

      if(size.cx < 0)
         return true;

      if(ptDst.y < 0)
      {
         size.cy += ptDst.y;
         ptDst.y = 0;
      }

      if(size.cy < 0)
         return true;

      int xEnd = MIN(size.cx, MIN(pdib->m_size.cx - ptSrc.x, m_size.cx - ptDst.x));

      int yEnd = MIN(size.cy, MIN(pdib->m_size.cy - ptSrc.y, m_size.cy - ptDst.y));

      if(xEnd < 0)
         return false;

      if(yEnd < 0)
         return false;

      int32_t s1 = m_iScan / sizeof(COLORREF);

      int32_t s2 = pdib->m_iScan / sizeof(COLORREF);

      COLORREF * pdst = &m_pcolorref[s1 * ptDst.y] + ptDst.x;

      COLORREF * psrc = &pdib->m_pcolorref[s2 * ptSrc.y] + ptSrc.x;

      COLORREF * pdst2;

      COLORREF * psrc2;

      int i = 0;

      for(int y = 0; y < yEnd; y++)
      {

         pdst2 = &pdst[s1 * y];

         psrc2 = &psrc[s2 * y];

         for(int x = 0; x < xEnd; x++)
         {

            if(argb_get_a_value(*psrc2) == 0)
            {
               i++;
            }
            else
            {
               *pdst2 = *psrc2;
            }

            pdst2++;

            psrc2++;

         }

      }

      return true;

   }


   bool dib::blend(point ptDst, ::draw2d::dib * pdibSrc, point ptSrc, ::draw2d::dib * pdibAlf, point ptDstAlf, class size size)
   {

      dib * pdibDst = this;

      pdibDst->map();
      pdibSrc->map();
      pdibAlf->map();

      if (ptSrc.x < 0)
      {
         ptDst.x -= ptSrc.x;
         ptDstAlf.x -= ptSrc.x;
         ptSrc.x = 0;
      }

      if (ptSrc.y < 0)
      {
         ptDst.y -= ptSrc.y;
         ptDstAlf.y -= ptSrc.y;
         ptSrc.y = 0;
      }

      if (ptDst.x < 0)
      {
         size.cx += ptDst.x;
         ptDst.x = 0;
      }

      if (size.cx < 0)
         return true;

      if (ptDst.y < 0)
      {
         size.cy += ptDst.y;
         ptDst.y = 0;
      }

      if (size.cy < 0)
         return true;

      int xEnd = MIN(size.cx, MIN(pdibSrc->m_size.cx - ptSrc.x, pdibDst->m_size.cx - ptDst.x));

      int yEnd = MIN(size.cy, MIN(pdibSrc->m_size.cy - ptSrc.y, pdibDst->m_size.cy - ptDst.y));

      if (xEnd < 0)
         return false;

      if (yEnd < 0)
         return false;


      if (ptDstAlf.x < 0)
      {
      }

      int32_t scanDst = pdibDst->m_iScan;

      int32_t scanSrc = pdibSrc->m_iScan;

      int32_t scanAlf = pdibAlf->m_iScan;

      byte * pdst = &((byte *)pdibDst->m_pcolorref)[scanDst * ptDst.y + ptDst.x * sizeof(COLORREF)];

      byte * psrc = &((byte *)pdibSrc->m_pcolorref)[scanSrc * ptSrc.y + ptSrc.x * sizeof(COLORREF)];

      byte * palf = &((byte *)pdibAlf->m_pcolorref)[- scanAlf * ptDstAlf.y - ptDstAlf.x * sizeof(COLORREF)] + 3;

      byte * pdst2;

      byte * psrc2;

      byte * palf2;

      int x1;
      int x2;
      int y1;
      int y2;

      x1 = ptDstAlf.x;
      x2 = pdibAlf->m_size.cx + x1;
      y1 = ptDstAlf.y;
      y2 = pdibAlf->m_size.cy + y1;


      int a;

      for (int y = 0; y < yEnd; y++)
      {

         pdst2 = (byte *) &pdst[scanDst * y];

         psrc2 = (byte *) &psrc[scanSrc * y];

         palf2 = (byte *) &palf[scanAlf * y];

         for (int x = 0; x < xEnd; x++)
         {

            if (psrc2[3] > 0)
            {
               if (false && x >= x1 && x < x2 && y >= y1 && y < y2)
               {

                  a = (*palf2 * psrc2[3]) / 255;
                  a = psrc2[3];
                  //a = (int) (byte) sqrt((float) (*palf2 * psrc2[3]));
                  pdst2[3] = (BYTE)MAX(a, pdst2[3]);
                  //pdst2[3] = (BYTE)((((int)psrc2[3] - (int)pdst2[3]) * a + ((int)pdst2[3] * 255)) / 255);
                  pdst2[3] = (BYTE)(MAX(psrc2[3], pdst2[3]));

//                  if (a > 0)
                  {

                     pdst2[0] = (BYTE)((((int)psrc2[0] - (int)pdst2[0]) * a + ((int)pdst2[0] * 255)) / 255);
                     pdst2[1] = (BYTE)((((int)psrc2[1] - (int)pdst2[1]) * a + ((int)pdst2[1] * 255)) / 255);
                     pdst2[2] = (BYTE)((((int)psrc2[2] - (int)pdst2[2]) * a + ((int)pdst2[2] * 255)) / 255);

                  }

               }
               else
               {

                  //pdst2[3] = (BYTE)(MAX(psrc2[3], pdst2[3]));
                  //pdst2[3] = (BYTE)((((int)psrc2[3] - (int)pdst2[3]) * (int)psrc2[3] + ((int)pdst2[3] * 255)) / 255);
                  //pdst2[0] = (BYTE)((((int)psrc2[0] - (int)pdst2[0]) * (int)psrc2[3] + ((int)pdst2[0] * 255)) / 255);
                  //pdst2[1] = (BYTE)((((int)psrc2[1] - (int)pdst2[1]) * (int)psrc2[3] + ((int)pdst2[1] * 255)) / 255);
                  //pdst2[2] = (BYTE)((((int)psrc2[2] - (int)pdst2[2]) * (int)psrc2[3] + ((int)pdst2[2] * 255)) / 255);
                  pdst2[3] = (BYTE)(MAX(((((int)psrc2[3] - (int)pdst2[3]) * (int)psrc2[3] + ((int)pdst2[3] * 255)) / 255), pdst2[3]));
                  pdst2[0] = (BYTE)((((int)psrc2[0] - (int)pdst2[0]) * (int)psrc2[3] + ((int)pdst2[0] * 255)) / 255);
                  pdst2[1] = (BYTE)((((int)psrc2[1] - (int)pdst2[1]) * (int)psrc2[3] + ((int)pdst2[1] * 255)) / 255);
                  pdst2[2] = (BYTE)((((int)psrc2[2] - (int)pdst2[2]) * (int)psrc2[3] + ((int)pdst2[2] * 255)) / 255);

               }
            }


            pdst2+=4;

            psrc2+=4;

            palf2+=4;


         }

      }

      return true;

   }

   bool dib::blend(point ptDst,::draw2d::dib * pdibSrc, point ptSrc, class size size)
   {

      dib * pdibDst = this;

      pdibDst->map();
      pdibSrc->map();

      if (ptSrc.x < 0)
      {
         ptDst.x -= ptSrc.x;
         ptSrc.x = 0;
      }

      if (ptSrc.y < 0)
      {
         ptDst.y -= ptSrc.y;
         ptSrc.y = 0;
      }

      if (ptDst.x < 0)
      {
         size.cx += ptDst.x;
         ptDst.x = 0;
      }

      if (size.cx < 0)
         return true;

      if (ptDst.y < 0)
      {
         size.cy += ptDst.y;
         ptDst.y = 0;
      }

      if (size.cy < 0)
         return true;

      int xEnd = MIN(size.cx, MIN(pdibSrc->m_size.cx - ptSrc.x, pdibDst->m_size.cx - ptDst.x));

      int yEnd = MIN(size.cy, MIN(pdibSrc->m_size.cy - ptSrc.y, pdibDst->m_size.cy - ptDst.y));

      if (xEnd < 0)
         return false;

      if (yEnd < 0)
         return false;

      int32_t scanDst = pdibDst->m_iScan;

      int32_t scanSrc = pdibSrc->m_iScan;

      byte * pdst = &((byte *)pdibDst->m_pcolorref)[scanDst * ptDst.y + ptDst.x * sizeof(COLORREF)] + 3;

      byte * psrc = &((byte *)pdibSrc->m_pcolorref)[scanSrc * ptSrc.y + ptSrc.x * sizeof(COLORREF)] + 3;

      byte * pdst2;

      byte * psrc2;

      for (int y = 0; y < yEnd; y++)
      {

         pdst2 = (byte *) &pdst[scanDst * y];

         psrc2 = (byte *) &psrc[scanSrc * y];

         for (int x = 0; x < xEnd; x++)
         {

            *pdst2 = *psrc2 * *pdst2 / 255;

            pdst2+=4;

            psrc2+=4;

         }

      }

      return true;

   }

   void dib::set( int32_t R, int32_t G, int32_t B )
   {
      int64_t size = area();

      COLORREF * pcr = get_data();

      for(int32_t i=0; i < size; i++)
      {
         ((byte *) pcr)[0] = R;
         ((byte *) pcr)[1] = G;
         ((byte *) pcr)[2] = B;
         pcr++;
      }

   }

/*   void dib::Fill ( int32_t R, int32_t G, int32_t B )
   {
      COLORREF color=RGB ( B, G, R );
      int64_t size = area();

      COLORREF * pcr;

      int64_t iSize32 = size / 32;
      int32_t i;
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
   */


   void dib::ToAlpha(int32_t i)
   {
      BYTE *dst=(BYTE*)get_data();
      int64_t size = area();

      while ( size-- )
      {
         dst[3] = dst[i];
         dst+=4;
      }
   }

   void dib::from_alpha()
   {
      BYTE *dst=(BYTE*)get_data();
      int64_t size = area();

      while ( size-- )
      {
         dst[0] = dst[3];
         dst[1] = dst[3];
         dst[2] = dst[3];
         dst+=4;
      }
   }

   void dib::mult_alpha(::draw2d::dib * pdib, bool bPreserveAlpha)
   {
      UNREFERENCED_PARAMETER(pdib);
      UNREFERENCED_PARAMETER(bPreserveAlpha);

      BYTE *dst=(BYTE*)get_data();
      int64_t size = area();


      // >> 8 instead of / 255 subsequent alpha_blend operations say thanks on true_blend because (255) * (1/254) + (255) * (254/255) > 255


      while (size >= 8)
      {
         dst[0] = LOBYTE(((int32_t)dst[0] * (int32_t)dst[3])>> 8);
         dst[1] = LOBYTE(((int32_t)dst[1] * (int32_t)dst[3])>> 8);
         dst[2] = LOBYTE(((int32_t)dst[2] * (int32_t)dst[3])>> 8);

         dst[4+0] = LOBYTE(((int32_t)dst[4+0] * (int32_t)dst[4+3])>> 8);
         dst[4+1] = LOBYTE(((int32_t)dst[4+1] * (int32_t)dst[4+3])>> 8);
         dst[4+2] = LOBYTE(((int32_t)dst[4+2] * (int32_t)dst[4+3])>> 8);

         dst[8+0] = LOBYTE(((int32_t)dst[8+0] * (int32_t)dst[8+3])>> 8);
         dst[8+1] = LOBYTE(((int32_t)dst[8+1] * (int32_t)dst[8+3])>> 8);
         dst[8+2] = LOBYTE(((int32_t)dst[8+2] * (int32_t)dst[8+3])>> 8);

         dst[12+0] = LOBYTE(((int32_t)dst[12+0] * (int32_t)dst[12+3])>> 8);
         dst[12+1] = LOBYTE(((int32_t)dst[12+1] * (int32_t)dst[12+3])>> 8);
         dst[12+2] = LOBYTE(((int32_t)dst[12+2] * (int32_t)dst[12+3])>> 8);

         dst[16+0] = LOBYTE(((int32_t)dst[16+0] * (int32_t)dst[16+3])>> 8);
         dst[16+1] = LOBYTE(((int32_t)dst[16+1] * (int32_t)dst[16+3])>> 8);
         dst[16+2] = LOBYTE(((int32_t)dst[16+2] * (int32_t)dst[16+3])>> 8);

         dst[20+0] = LOBYTE(((int32_t)dst[20+0] * (int32_t)dst[20+3])>> 8);
         dst[20+1] = LOBYTE(((int32_t)dst[20+1] * (int32_t)dst[20+3])>> 8);
         dst[20+2] = LOBYTE(((int32_t)dst[20+2] * (int32_t)dst[20+3])>> 8);

         dst[24+0] = LOBYTE(((int32_t)dst[24+0] * (int32_t)dst[24+3])>> 8);
         dst[24+1] = LOBYTE(((int32_t)dst[24+1] * (int32_t)dst[24+3])>> 8);
         dst[24+2] = LOBYTE(((int32_t)dst[24+2] * (int32_t)dst[24+3])>> 8);

         dst[28+0] = LOBYTE(((int32_t)dst[28+0] * (int32_t)dst[28+3])>> 8);
         dst[28+1] = LOBYTE(((int32_t)dst[28+1] * (int32_t)dst[28+3])>> 8);
         dst[28+2] = LOBYTE(((int32_t)dst[28+2] * (int32_t)dst[28+3])>> 8);

         dst += 4 * 8;
         size -= 8;
      }
      while(size--)
      {
         dst[0] = LOBYTE(((int32_t)dst[0] * (int32_t)dst[3])>> 8);
         dst[1] = LOBYTE(((int32_t)dst[1] * (int32_t)dst[3])>> 8);
         dst[2] = LOBYTE(((int32_t)dst[2] * (int32_t)dst[3])>> 8);
         dst += 4;
      }
   }

   void dib::mult_alpha()
   {

      BYTE *dst=(BYTE*)get_data();
      int64_t size = area();


      //  / 255 instead of / 255 subsequent alpha_blend operations say thanks on true_blend because (255) * (1/254) + (255) * (254/255) > 255


      while (size >= 8)
      {
         dst[0] = byte_clip(((int32_t)dst[0] * (int32_t)dst[3]) / 255);
         dst[1] = byte_clip(((int32_t)dst[1] * (int32_t)dst[3]) / 255);
         dst[2] = byte_clip(((int32_t)dst[2] * (int32_t)dst[3]) / 255);

         dst[4+0] = byte_clip(((int32_t)dst[4+0] * (int32_t)dst[4+3]) / 255);
         dst[4+1] = byte_clip(((int32_t)dst[4+1] * (int32_t)dst[4+3]) / 255);
         dst[4+2] = byte_clip(((int32_t)dst[4+2] * (int32_t)dst[4+3]) / 255);

         dst[8+0] = byte_clip(((int32_t)dst[8+0] * (int32_t)dst[8+3]) / 255);
         dst[8+1] = byte_clip(((int32_t)dst[8+1] * (int32_t)dst[8+3]) / 255);
         dst[8+2] = byte_clip(((int32_t)dst[8+2] * (int32_t)dst[8+3]) / 255);

         dst[12+0] = byte_clip(((int32_t)dst[12+0] * (int32_t)dst[12+3]) / 255);
         dst[12+1] = byte_clip(((int32_t)dst[12+1] * (int32_t)dst[12+3]) / 255);
         dst[12+2] = byte_clip(((int32_t)dst[12+2] * (int32_t)dst[12+3]) / 255);

         dst[16+0] = byte_clip(((int32_t)dst[16+0] * (int32_t)dst[16+3]) / 255);
         dst[16+1] = byte_clip(((int32_t)dst[16+1] * (int32_t)dst[16+3]) / 255);
         dst[16+2] = byte_clip(((int32_t)dst[16+2] * (int32_t)dst[16+3]) / 255);

         dst[20+0] = byte_clip(((int32_t)dst[20+0] * (int32_t)dst[20+3]) / 255);
         dst[20+1] = byte_clip(((int32_t)dst[20+1] * (int32_t)dst[20+3]) / 255);
         dst[20+2] = byte_clip(((int32_t)dst[20+2] * (int32_t)dst[20+3]) / 255);

         dst[24+0] = byte_clip(((int32_t)dst[24+0] * (int32_t)dst[24+3]) / 255);
         dst[24+1] = byte_clip(((int32_t)dst[24+1] * (int32_t)dst[24+3]) / 255);
         dst[24+2] = byte_clip(((int32_t)dst[24+2] * (int32_t)dst[24+3]) / 255);

         dst[28+0] = byte_clip(((int32_t)dst[28+0] * (int32_t)dst[28+3]) / 255);
         dst[28+1] = byte_clip(((int32_t)dst[28+1] * (int32_t)dst[28+3]) / 255);
         dst[28+2] = byte_clip(((int32_t)dst[28+2] * (int32_t)dst[28+3]) / 255);

         dst += 4 * 8;
         size -= 8;
      }
      while(size--)
      {
         dst[0] = byte_clip(((int32_t)dst[0] * (int32_t)dst[3]) / 255);
         dst[1] = byte_clip(((int32_t)dst[1] * (int32_t)dst[3]) / 255);
         dst[2] = byte_clip(((int32_t)dst[2] * (int32_t)dst[3]) / 255);
         dst += 4;
      }
   }


   void dib::div_alpha()
   {

      BYTE *dst=(BYTE*)get_data();
      int64_t size = area();


      // >> 8 instead of / 255 subsequent alpha_blend operations say thanks on true_blend because (255) * (1/254) + (255) * (254/255) > 255


/*      while (size >= 8)
      {
         dst[0] = LOBYTE(((int32_t)dst[0] * (int32_t)dst[3])>> 8);
         dst[1] = LOBYTE(((int32_t)dst[1] * (int32_t)dst[3])>> 8);
         dst[2] = LOBYTE(((int32_t)dst[2] * (int32_t)dst[3])>> 8);

         dst[4+0] = LOBYTE(((int32_t)dst[4+0] * (int32_t)dst[4+3])>> 8);
         dst[4+1] = LOBYTE(((int32_t)dst[4+1] * (int32_t)dst[4+3])>> 8);
         dst[4+2] = LOBYTE(((int32_t)dst[4+2] * (int32_t)dst[4+3])>> 8);

         dst[8+0] = LOBYTE(((int32_t)dst[8+0] * (int32_t)dst[8+3])>> 8);
         dst[8+1] = LOBYTE(((int32_t)dst[8+1] * (int32_t)dst[8+3])>> 8);
         dst[8+2] = LOBYTE(((int32_t)dst[8+2] * (int32_t)dst[8+3])>> 8);

         dst[12+0] = LOBYTE(((int32_t)dst[12+0] * (int32_t)dst[12+3])>> 8);
         dst[12+1] = LOBYTE(((int32_t)dst[12+1] * (int32_t)dst[12+3])>> 8);
         dst[12+2] = LOBYTE(((int32_t)dst[12+2] * (int32_t)dst[12+3])>> 8);

         dst[16+0] = LOBYTE(((int32_t)dst[16+0] * (int32_t)dst[16+3])>> 8);
         dst[16+1] = LOBYTE(((int32_t)dst[16+1] * (int32_t)dst[16+3])>> 8);
         dst[16+2] = LOBYTE(((int32_t)dst[16+2] * (int32_t)dst[16+3])>> 8);

         dst[20+0] = LOBYTE(((int32_t)dst[20+0] * (int32_t)dst[20+3])>> 8);
         dst[20+1] = LOBYTE(((int32_t)dst[20+1] * (int32_t)dst[20+3])>> 8);
         dst[20+2] = LOBYTE(((int32_t)dst[20+2] * (int32_t)dst[20+3])>> 8);

         dst[24+0] = LOBYTE(((int32_t)dst[24+0] * (int32_t)dst[24+3])>> 8);
         dst[24+1] = LOBYTE(((int32_t)dst[24+1] * (int32_t)dst[24+3])>> 8);
         dst[24+2] = LOBYTE(((int32_t)dst[24+2] * (int32_t)dst[24+3])>> 8);

         dst[28+0] = LOBYTE(((int32_t)dst[28+0] * (int32_t)dst[28+3])>> 8);
         dst[28+1] = LOBYTE(((int32_t)dst[28+1] * (int32_t)dst[28+3])>> 8);
         dst[28+2] = LOBYTE(((int32_t)dst[28+2] * (int32_t)dst[28+3])>> 8);

         dst += 4 * 8;
         size -= 8;
      }*/
      while(size--)
      {
         if(dst[3] == 0)
         {
            dst[0] = 0;
            dst[1] = 0;
            dst[2] = 0;
         }
         else
         {
            dst[0] = byte_clip((int32_t) dst[0] * 255 / (int32_t) dst[3]);
            dst[1] = byte_clip((int32_t) dst[1] * 255 / (int32_t) dst[3]);
            dst[2] = byte_clip((int32_t) dst[2] * 255 / (int32_t) dst[3]);
         }

         dst += 4;

      }

   }

   void dib::Map(int32_t ToRgb, int32_t FromRgb)
   {
      byte * dst= (byte *) get_data();
      int64_t size = area();

      while ( size-- )
      {
         *dst = (byte) (*dst == FromRgb ? ToRgb : *dst);
         dst+=4;
      }
   }


   void dib::ToAlphaAndFill(int32_t i, COLORREF cr)
   {
      BYTE *dst=(BYTE*)get_data();
      int64_t size = area();

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
      int64_t size = area();

      uint32_t dwB = rgba_get_b(cr);
      uint32_t dwG = rgba_get_g(cr);
      uint32_t dwR = rgba_get_r(cr);

      while (size-- > 0)
      {
         dst[3] = dst[0];
         dst[0] = (BYTE)(((dwB * dst[3]) / 256) & 0xff);
         dst[1] = (BYTE)(((dwG * dst[3]) / 256) & 0xff);
         dst[2] = (BYTE)(((dwR * dst[3]) / 256) & 0xff);
         dst+=4;
      }
   }


   void dib::BitBlt(dib *pdib, int32_t op)
   {
      if(op == 123) // zero dest RGB, invert alpha, and OR src RGB
      {

         COLORREF _colorref = RGB ( 0, 0, 0 ) | (255 << 24);
         COLORREF colorrefa[2];
         colorrefa[0] = _colorref;
         colorrefa[1] = _colorref;

         COLORREF _colorrefN = RGB ( 255, 255, 255) | (0 << 24);
         COLORREF colorrefaN[2];
         colorrefaN[0] = _colorrefN;

         colorrefaN[1] = _colorrefN;

         int64_t isize = area();
         LPDWORD lpbitsSrc= (LPDWORD) pdib->get_data();
         LPDWORD lpbitsDest= (LPDWORD) get_data();

         memcpy(lpbitsDest, lpbitsSrc, (size_t) (isize * sizeof(COLORREF)));

      }

   }

   void dib::BitBlt(int cxParam, int cyParam, dib *pdib,int32_t op)
   {
      if(op == 1 && m_size == pdib->m_size && pdib->m_iScan == m_iScan) // op == 1 indicates can ignore cxParam and cyParam and perform full memcpy
      {

         memcpy(m_pcolorref,pdib->m_pcolorref,cyParam * m_iScan);

      }
      else if(op == 0 || op == 1)
      {


         int iStrideSrc = pdib->m_iScan;

         if(iStrideSrc <= 0)
         {

            iStrideSrc = cxParam * sizeof(COLORREF);

         }

         if(m_iScan == iStrideSrc && m_iScan == pdib->m_iScan)
         {

            memcpy(m_pcolorref,pdib->m_pcolorref,cyParam * m_iScan);

         }
         else
         {

            int wsrc = iStrideSrc / sizeof(COLORREF);
            int wdst = m_iScan / sizeof(COLORREF);
            int cw = MIN(cxParam, m_size.cx) * sizeof(COLORREF);

            int h = MIN(cyParam,m_size.cy);


            COLORREF * psrc = pdib ->m_pcolorref;
            COLORREF * pdst = m_pcolorref;

            for(int i = 0; i < h; i++)
            {

               memcpy(pdst,psrc,cw);

               pdst += wdst;

               psrc += wsrc;

            }

         }

      }

   }

   void dib::Invert()
   {
      int64_t size = area();
      LPBYTE lpb = (LPBYTE) get_data();
      for ( int32_t i=0; i<size; i++ )
      {
         lpb[0] = 255 - lpb[0];
         lpb[1] = 255 - lpb[1];
         lpb[2] = 255 - lpb[2];
         lpb += 4;
      }
   }

   void dib::channel_invert(visual::rgba::echannel echannel)
   {
      int64_t size=area();
      LPBYTE lpb = (LPBYTE) get_data();
      lpb += ((int32_t)echannel) % 4;
      for ( int32_t i=0; i<size; i++ )
      {
         *lpb = 255 - *lpb;
         lpb += 4;
      }
   }

   void dib::channel_multiply(visual::rgba::echannel echannel, double dRate)
   {
      if(dRate < 0)
         return;
      int64_t size = area();
      LPBYTE lpb = (LPBYTE) get_data();
      lpb += ((int32_t)echannel) % 4;
       int32_t iDiv = 256 * 256;
       int32_t iMul = (int32_t) (dRate * ((double) iDiv));
       int32_t iRes;
      for( int64_t i = 0; i < size; i++)
      {
         iRes = *lpb * iMul / iDiv;
         *lpb = (byte) (iRes > 255 ? 255 : iRes);
         lpb += 4;
      }
   }

   void dib::channel_multiply(visual::rgba::echannel echannel, ::draw2d::dib * pdib)
   {

//      int64_t size = area();

      LPBYTE lpb1 = (LPBYTE) get_data();

      LPBYTE lpb2 = (LPBYTE) pdib->get_data();

      lpb1 += ((int32_t)echannel) % 4;

      lpb2 += ((int32_t)echannel) % 4;

      for( int32_t y = 0; y < m_size.cy; y++)
      {

         LPBYTE lpb1_2 = lpb1 + (m_iScan * y);

         LPBYTE lpb2_2 = lpb2 + (pdib->m_iScan * y);

         for ( int32_t x = 0; x < m_size.cx; x++)
         {

            *lpb2 = (BYTE)(((uint32_t)*lpb1_2 * (uint32_t)*lpb2_2) / 255);

            lpb1_2 += 4;

            lpb2_2 += 4;

         }

      }

   }


   void dib::channel_darken(visual::rgba::echannel echannel, ::draw2d::dib * pdib)
   {
       int64_t size = area();
      LPBYTE lpb1 = (LPBYTE) get_data();
      LPBYTE lpb2 = (LPBYTE) pdib->get_data();
      lpb1 += ((int32_t)echannel) % 4;
      lpb2 += ((int32_t)echannel) % 4;
      for( int64_t i = 0; i < size; i++)
      {
         *lpb1 = *lpb1 < *lpb2 ? *lpb1 : *lpb2;
         lpb1 += 4;
         lpb2 += 4;
      }
   }

   void dib::channel_lighten(visual::rgba::echannel echannel, ::draw2d::dib * pdib)
   {
       int64_t size = area();
      LPBYTE lpb1 = (LPBYTE) get_data();
      LPBYTE lpb2 = (LPBYTE) pdib->get_data();
      lpb1 += ((int32_t)echannel) % 4;
      lpb2 += ((int32_t)echannel) % 4;
      for( int64_t i = 0; i < size; i++)
      {
         *lpb1 = *lpb1 > *lpb2 ? *lpb1 : *lpb2;
         lpb1 += 4;
         lpb2 += 4;
      }
   }

   void dib::channel_from(visual::rgba::echannel echannel, ::draw2d::dib * pdib)
   {
      map();
      pdib->map();
      int64_t size = area();
       int64_t size64 = size / 64;
      LPBYTE lpb1 = (LPBYTE) get_data();
      LPBYTE lpb2 = (LPBYTE) pdib->get_data();
      lpb1 += ((int32_t)echannel) % 4;
      lpb2 += ((int32_t)echannel) % 4;
       int64_t i = 0;
      for(; i < size64; i++)
      {
         lpb1[4 *  0]  =  lpb2[4 *  0];
         lpb1[4 *  1]  =  lpb2[4 *  1];
         lpb1[4 *  2]  =  lpb2[4 *  2];
         lpb1[4 *  3]  =  lpb2[4 *  3];
         lpb1[4 *  4]  =  lpb2[4 *  4];
         lpb1[4 *  5]  =  lpb2[4 *  5];
         lpb1[4 *  6]  =  lpb2[4 *  6];
         lpb1[4 *  7]  =  lpb2[4 *  7];
         lpb1[4 *  8]  =  lpb2[4 *  8];
         lpb1[4 *  9]  =  lpb2[4 *  9];
         lpb1[4 * 10]  =  lpb2[4 * 10];
         lpb1[4 * 11]  =  lpb2[4 * 11];
         lpb1[4 * 12]  =  lpb2[4 * 12];
         lpb1[4 * 13]  =  lpb2[4 * 13];
         lpb1[4 * 14]  =  lpb2[4 * 14];
         lpb1[4 * 15]  =  lpb2[4 * 15];
         lpb1[4 * 16]  =  lpb2[4 * 16];
         lpb1[4 * 17]  =  lpb2[4 * 17];
         lpb1[4 * 18]  =  lpb2[4 * 18];
         lpb1[4 * 19]  =  lpb2[4 * 19];
         lpb1[4 * 20]  =  lpb2[4 * 20];
         lpb1[4 * 21]  =  lpb2[4 * 21];
         lpb1[4 * 22]  =  lpb2[4 * 22];
         lpb1[4 * 23]  =  lpb2[4 * 23];
         lpb1[4 * 24]  =  lpb2[4 * 24];
         lpb1[4 * 25]  =  lpb2[4 * 25];
         lpb1[4 * 26]  =  lpb2[4 * 26];
         lpb1[4 * 27]  =  lpb2[4 * 27];
         lpb1[4 * 28]  =  lpb2[4 * 28];
         lpb1[4 * 29]  =  lpb2[4 * 29];
         lpb1[4 * 30]  =  lpb2[4 * 30];
         lpb1[4 * 31]  =  lpb2[4 * 31];

         lpb1[4 * 32]  =  lpb2[4 * 32];
         lpb1[4 * 33]  =  lpb2[4 * 33];
         lpb1[4 * 34]  =  lpb2[4 * 34];
         lpb1[4 * 35]  =  lpb2[4 * 35];
         lpb1[4 * 36]  =  lpb2[4 * 36];
         lpb1[4 * 37]  =  lpb2[4 * 37];
         lpb1[4 * 38]  =  lpb2[4 * 38];
         lpb1[4 * 39]  =  lpb2[4 * 39];
         lpb1[4 * 40]  =  lpb2[4 * 40];
         lpb1[4 * 41]  =  lpb2[4 * 41];
         lpb1[4 * 42]  =  lpb2[4 * 42];
         lpb1[4 * 43]  =  lpb2[4 * 43];
         lpb1[4 * 44]  =  lpb2[4 * 44];
         lpb1[4 * 45]  =  lpb2[4 * 45];
         lpb1[4 * 46]  =  lpb2[4 * 46];
         lpb1[4 * 47]  =  lpb2[4 * 47];
         lpb1[4 * 48]  =  lpb2[4 * 48];
         lpb1[4 * 49]  =  lpb2[4 * 49];
         lpb1[4 * 50]  =  lpb2[4 * 50];
         lpb1[4 * 51]  =  lpb2[4 * 51];
         lpb1[4 * 52]  =  lpb2[4 * 52];
         lpb1[4 * 53]  =  lpb2[4 * 53];
         lpb1[4 * 54]  =  lpb2[4 * 54];
         lpb1[4 * 55]  =  lpb2[4 * 55];
         lpb1[4 * 56]  =  lpb2[4 * 56];
         lpb1[4 * 57]  =  lpb2[4 * 57];
         lpb1[4 * 58]  =  lpb2[4 * 58];
         lpb1[4 * 59]  =  lpb2[4 * 59];
         lpb1[4 * 60]  =  lpb2[4 * 60];
         lpb1[4 * 61]  =  lpb2[4 * 61];
         lpb1[4 * 62]  =  lpb2[4 * 62];
         lpb1[4 * 63]  =  lpb2[4 * 63];

         lpb1 += 4 * 64;
         lpb2 += 4 * 64;
      }
      i *= 64;
      for(; i < size; i++)
      {
         *lpb1 = *lpb2;
         lpb1 += 4;
         lpb2 += 4;
      }
   }


   void dib::FillGlass ( int32_t R, int32_t G, int32_t B, int32_t A )
   {
      BYTE *dst=(BYTE*)get_data();
      int64_t size = area();

      while ( size-- )
      {
         dst[0]=(BYTE)(((B-dst[0])*A+(dst[0]<<8))>>8);
         dst[1]=(BYTE)(((G-dst[1])*A+(dst[1]<<8))>>8);
         dst[2]=(BYTE)(((R-dst[2])*A+(dst[2]<<8))>>8);
         dst+=4;
      }
   }

   void dib::FillStippledGlass ( int32_t R, int32_t G, int32_t B )
   {
      COLORREF color = RGB ( B, G, R );
      int32_t w = m_size.cx;
      int32_t h = m_size.cy;

      for ( int32_t j=0; j<w; j++ )
      {
         for ( int32_t i=0; i<h; i++ )
         {
            get_data()[j*w+i]=((i+j)&0x1) ? get_data()[j*w+i] : color;
         }
      }
   }

   void dib::copy(dib * dib)
   {

      if (area() <= 0)
         return;

      // If DibSize Wrong Re-create dib
      if(dib->m_size != size())
         dib->create(size());

      // do copy

      map();

      dib->map();

      if (get_data() == NULL || dib->get_data() == NULL)
         return;

      memcpy ( dib->get_data(), get_data(), (size_t) area() * sizeof(COLORREF) );


   }


   void dib::Paste(dib * dib)
   {

      if (size() != dib->m_size)
         create(dib->size());

      dib->defer_realize(get_graphics());
      defer_realize(dib->get_graphics());

      map();
      dib->map();
      // If DibSize Wrong Re-create dib
      // do Paste

      if (m_iScan == dib->m_iScan)
      {
         memcpy(get_data(), dib->get_data(), m_size.cy * m_iScan);
      }
      else
      {

         int iScan = MIN(m_iScan, dib->m_iScan);

         for (int i = 0; i < m_iScan; i++)
         {
            memcpy(&((byte *)get_data())[m_iScan * i], &((byte *)dib->get_data())[dib->m_iScan * i], iScan);
         }

      }


   }

   bool dib::bitmap_blend(::draw2d::graphics * pgraphics, LPCRECT lprect)
   {

      rect rect(lprect);

      return pgraphics->BitBlt(rect.left, rect.top, rect.width(), rect.height(), get_graphics(), 0, 0, SRCCOPY) != FALSE;

   }


   bool dib::color_blend(COLORREF cr, BYTE bAlpha)
   {

      BYTE *dst=(BYTE*)get_data();
      int64_t size = area();

      uint32_t dwB = rgba_get_b(cr);
      uint32_t dwG = rgba_get_g(cr);
      uint32_t dwR = rgba_get_r(cr);

      uint32_t dwB_ = dwB << 8;
      uint32_t dwG_ = dwG << 8;
      uint32_t dwR_ = dwR << 8;

      while ( size-- )
      {
         dst[0]=(BYTE)(((dst[0]-dwB)*bAlpha+dwB_)>>8);
         dst[1]=(BYTE)(((dst[1]-dwG)*bAlpha+dwG_)>>8);
         dst[2]=(BYTE)(((dst[2]-dwG)*bAlpha+dwR_)>>8);
         dst+=4;
      }
      return true;
   }


   void dib::Blend(dib * dib, int32_t A)
   {
      if(m_size != dib->m_size )
         return;

      BYTE *src=(BYTE*)dib->get_data();
      BYTE *dst=(BYTE*)get_data();
      int64_t size = area();

      while ( size-- )
      {
         dst[0]=(BYTE)(((src[0]-dst[0])*A+(dst[0]<<8))>>8);
         dst[1]=(BYTE)(((src[1]-dst[1])*A+(dst[1]<<8))>>8);
         dst[2]=(BYTE)(((src[2]-dst[2])*A+(dst[2]<<8))>>8);
         dst+=4;
         src+=4;
      }
   }

   bool dib::Blend(dib *pDib, dib *DibA, int32_t A)
   {
      if(m_size != pDib->m_size ||
         m_size != DibA->size())
         return false;

      BYTE *src=(BYTE*)pDib->get_data();
      BYTE *dst=(BYTE*)get_data();
      BYTE *alf=(BYTE*)DibA->get_data();
      int64_t size = area();

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


   bool dib::Blend(dib *pDib, dib *DibA)
   {
      if (m_size != pDib->m_size ||
         m_size != DibA->size())
         return false;

      map();
      pDib->map();
      DibA->map();

      BYTE *src = (BYTE*)pDib->get_data();
      BYTE *dst = (BYTE*)get_data();
      BYTE *alf = ((BYTE*)DibA->get_data()) + 3;
      int64_t size = area();

      while (size--)
      {
         dst[0] = (BYTE)(((src[0] - dst[0])* (*alf) + (dst[0] << 8)) >> 8);
         dst[1] = (BYTE)(((src[1] - dst[1])* (*alf) + (dst[1] << 8)) >> 8);
         dst[2] = (BYTE)(((src[2] - dst[2])* (*alf) + (dst[2] << 8)) >> 8);
         dst += 4;
         src += 4;
         alf += 4;
      }

      return true;
   }



   bool dib::blend(dib * pdib, dib * pdibRate)
   {
      if(m_size != pdib->m_size ||
         m_size != pdibRate->size())
         return false;

      BYTE *src=(BYTE*)pdib->get_data();
      BYTE *dst=(BYTE*)get_data();
      BYTE *alf=(BYTE*)pdibRate->get_data();
      int64_t size = area();

      while(size >= 2)
      {
         dst[00] = (BYTE) (((((int32_t)src[00] - (int32_t)dst[00]) * (int32_t)alf[00]) + (int32_t)dst[00] * (int32_t)255) / 255);
         dst[01] = (BYTE) (((((int32_t)src[01] - (int32_t)dst[01]) * (int32_t)alf[01]) + (int32_t)dst[01] * (int32_t)255) / 255);
         dst[02] = (BYTE) (((((int32_t)src[02] - (int32_t)dst[02]) * (int32_t)alf[02]) + (int32_t)dst[02] * (int32_t)255) / 255);
         dst[03] = (BYTE) (((((int32_t)src[03] - (int32_t)dst[03]) * (int32_t)alf[03]) + (int32_t)dst[03] * (int32_t)255) / 255);
         dst[04] = (BYTE) (((((int32_t)src[04] - (int32_t)dst[04]) * (int32_t)alf[04]) + (int32_t)dst[04] * (int32_t)255) / 255);
         dst[05] = (BYTE) (((((int32_t)src[05] - (int32_t)dst[05]) * (int32_t)alf[05]) + (int32_t)dst[05] * (int32_t)255) / 255);
         dst[06] = (BYTE) (((((int32_t)src[06] - (int32_t)dst[06]) * (int32_t)alf[06]) + (int32_t)dst[06] * (int32_t)255) / 255);
         dst[07] = (BYTE) (((((int32_t)src[07] - (int32_t)dst[07]) * (int32_t)alf[07]) + (int32_t)dst[07] * (int32_t)255) / 255);
         dst+=4 * 2;
         src+=4 * 2;
         alf+=4 * 2;
         size-=2;
      }
      while(size > 0)
      {
         dst[00] = (BYTE) (((((int32_t)src[00] - (int32_t)dst[00]) * (int32_t)alf[00]) + (int32_t)dst[00] * (int32_t)255) / 255);
         dst[01] = (BYTE) (((((int32_t)src[01] - (int32_t)dst[01]) * (int32_t)alf[01]) + (int32_t)dst[01] * (int32_t)255) / 255);
         dst[02] = (BYTE) (((((int32_t)src[02] - (int32_t)dst[02]) * (int32_t)alf[02]) + (int32_t)dst[02] * (int32_t)255) / 255);
         dst[03] = (BYTE) (((((int32_t)src[03] - (int32_t)dst[03]) * (int32_t)alf[03]) + (int32_t)dst[03] * (int32_t)255) / 255);
         dst+=4;
         src+=4;
         alf+=4;
         size--;
      }

      return true;
   }

   void dib::Darken ( dib *dib )
   {
      if ( size()!=dib->m_size )
         return;

      BYTE *src=(BYTE*)dib->get_data();
      BYTE *dst=(BYTE*)get_data();
      int64_t size = area();

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
      if ( size()!=dib->m_size )
         return;

      BYTE *src=(BYTE*)dib->get_data();
      BYTE *dst=(BYTE*)get_data();
      int64_t size = area();

      while ( size-- )
      {
         int32_t Difference;
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
      if ( size()!=dib->m_size )
         return;

      BYTE *src=(BYTE*)dib->get_data();
      BYTE *dst=(BYTE*)get_data();
      int64_t size = area();

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
      if ( size()!=dib->m_size )
         return;

      BYTE *src=(BYTE*)dib->get_data();
      BYTE *dst=(BYTE*)get_data();
      int64_t size = area();

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
      if ( size()!=dib->m_size )
         return;

      BYTE *src=(BYTE*)dib->get_data();
      BYTE *dst=(BYTE*)get_data();
      int64_t size = area();

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

   void dib::copy ( dib *dib, int32_t x, int32_t y )
   {
      // Clip Rect
      int32_t px=(x>=0) ? x : 0;
      int32_t py=(y>=0) ? y : 0;
      int32_t dx = ((x + dib->m_size.cx)<m_size.cx) ? dib->m_size.cx : m_size.cx - x;
      int32_t dy = ((y + dib->m_size.cy)<m_size.cy) ? dib->m_size.cy : m_size.cy - y;
      dx=(x>=0) ? dx : dx + x;
      dy=(y>=0) ? dy : dy + y;

      // If Nothing to copy return
      if ( (dx<=0) || (dy<=0) )
         return;
      // If DibSize Wrong Re-create dib
      if ((dx != dib->m_size.cx) || (dy != dib->m_size.cy))
         dib->create(dx, dy);

      map();
      dib->map();

      // Prepare buffer Addresses
      COLORREF *src = get_data() + (py*m_size.cx) + px;
      COLORREF *dst=dib->get_data();

      // Do copy
      while ( dy-- )
      {
         for ( int32_t i=0; i<dx; i++ )
            dst[i]=src[i];
         src += m_size.cx;
         dst += dib->m_size.cx;
      }

   }

   void dib::PasteRect ( dib *dib, int32_t x, int32_t y )
   {
      // Clip Rect
      int32_t px=(x>=0) ? x : 0;
      int32_t py=(y>=0) ? y : 0;
      int32_t dx = ((x + dib->m_size.cx)<m_size.cx) ? dib->m_size.cx : m_size.cx - x;
      int32_t dy = ((y + dib->m_size.cy)<m_size.cy) ? dib->m_size.cy : m_size.cy - y;
      dx=(x>=0) ? dx : dx + x;
      dy=(y>=0) ? dy : dy + y;

      // If Nothing to Paste return
      if ( (dx<=0) || (dy<=0) )
         return;

      // Prepare buffer Addresses
      COLORREF *src = dib->get_data() + ((py - y)*dib->m_size.cx) + px - x;
      COLORREF *dst = get_data() + (py*m_size.cx) + px;

      // Do Paste
      while ( dy-- )
      {
         for ( int32_t i=0; i<dx; i++ )
            dst[i]=src[i];
         src += dib->m_size.cx;
         dst += m_size.cx;
      }
   }

   void dib::FillRect ( int32_t x, int32_t y, int32_t w, int32_t h, int32_t R, int32_t G, int32_t B )
   {
      // Clip Rect
      int32_t px=(x>=0) ? x : 0;
      int32_t py=(y>=0) ? y : 0;
      int32_t dx = ((x + w)<m_size.cx) ? w : m_size.cx - x;
      int32_t dy = ((y + h)<m_size.cy) ? h : m_size.cy - y;
      dx=(x>=0) ? dx : dx + x;
      dy=(y>=0) ? dy : dy + y;

      // If Nothing to Fill return
      if ( (dx<=0) || (dy<=0) )
         return;

      // Prepare buffer Address
      COLORREF *dst = get_data() + (py*m_size.cx) + px;
      COLORREF color=RGB ( B, G, R );

      // Do Fill
      while ( dy-- )
      {
         for ( int32_t i=0; i<dx; i++ )
         {
            dst[i]=color;
         }
         dst += m_size.cx;
      }
   }

   void dib::FillRect ( int32_t x, int32_t y, int32_t w, int32_t h, int32_t A, int32_t R, int32_t G, int32_t B )
   {
      // Clip Rect
      int32_t px = x;
      if(w < 0)
      {
         px += w;
         w = -w;
      }

      px=(px>=0) ? px : 0;
      int32_t py = y;
      if(h < 0)
      {
         py += h;
         h = -h;
      }
      py = (py>=0) ? py : 0;
      int32_t dx;
      dx = ((px + w)<m_size.cx) ? w : m_size.cx - px;
      int32_t dy;
      dy = ((py + h)<m_size.cy) ? h : m_size.cy - py;
      dx=(px>=0) ? dx : dx + x;
      dy=(py>=0) ? dy : dy + y;

      // If Nothing to Fill return
      if ( (dx<=0) || (dy<=0) )
         return;

      // Prepare buffer Address
      COLORREF *dst = get_data() + (py*m_size.cx) + px;
      COLORREF color=ARGB (A, B, G, R );

      // Do Fill
      while ( dy-- )
      {
         for ( int32_t i=0; i<dx; i++ )
         {
            dst[i]=color;
         }
         dst += m_size.cx;
      }
   }

   void dib::FillGlassRect ( int32_t x, int32_t y, int32_t w, int32_t h, int32_t R, int32_t G, int32_t B, int32_t A )
   {
      // Clip Rect
      int32_t px=(x>=0) ? x : 0;
      int32_t py=(y>=0) ? y : 0;
      int32_t dx = ((x + w)<m_size.cx) ? w : m_size.cx - x;
      int32_t dy = ((y + h)<m_size.cy) ? h : m_size.cy - y;
      dx=(x>=0) ? dx : dx + x;
      dy=(y>=0) ? dy : dy + y;

      // If Nothing to FillGlass return
      if ( (dx<=0) || (dy<=0) )
         return;

      // Prepare buffer Address
      BYTE *dst = (BYTE *)get_data() + ((py*m_size.cx) + px) * 4;

      // Do FillGlass
      while ( dy-- )
      {
         for ( int32_t i=0; i<dx; i++ )
         {
            dst[0]=(BYTE)(((B-dst[0])*A+(dst[0]<<8))>>8);
            dst[1]=(BYTE)(((G-dst[1])*A+(dst[1]<<8))>>8);
            dst[2]=(BYTE)(((R-dst[2])*A+(dst[2]<<8))>>8);
            dst+=4;
         }
         dst+=(m_size.cx-dx)<<2;
      }
   }

   void dib::FillStippledGlassRect ( int32_t x, int32_t y, int32_t w, int32_t h, int32_t R, int32_t G, int32_t B )
   {
      // Clip Rect
      int32_t px=(x>=0) ? x : 0;
      int32_t py=(y>=0) ? y : 0;
      int32_t dx=((x+w)<m_size.cx) ? w : m_size.cx-x;
      int32_t dy=((y+h)<m_size.cy) ? h : m_size.cy-y;
      dx=(x>=0) ? dx : dx + x;
      dy=(y>=0) ? dy : dy + y;

      // If Nothing to FillStippledGlass return
      if ( (dx<=0) || (dy<=0) )
         return;

      // Prepare buffer Address
      COLORREF *dst=get_data()+(py*m_size.cx)+px;
      COLORREF color=RGB ( B, G, R );

      // Do FillStippledGlass
      for ( int32_t j=0; j<dy; j++ )
      {
         for ( int32_t i=0; i<dx; i++ )
         {
            dst[i]=((i+j)&0x1) ? dst[i] : color;
         }
         dst+=m_size.cx;
      }
   }

   void dib::BlendRect ( dib *dib, int32_t x, int32_t y, int32_t A )
   {
      // Clip Rect
      int32_t px=(x>=0) ? x : 0;
      int32_t py=(y>=0) ? y : 0;
      int32_t dx=((x+dib->m_size.cx)<m_size.cx) ? dib->m_size.cx : m_size.cx-x;
      int32_t dy=((y+dib->m_size.cy)<m_size.cy) ? dib->m_size.cy : m_size.cy-y;
      dx=(x>=0) ? dx : dx + x;
      dy=(y>=0) ? dy : dy + y;

      // If Nothing to Blend return
      if ( (dx<=0) || (dy<=0) )
         return;

      // Prepare buffer Addresses
      BYTE *src=(BYTE *)dib->get_data()+(((py-y)*dib->m_size.cx)+px-x)*4;
      BYTE *dst=(BYTE *)get_data()+((py*m_size.cx)+px)*4;

      // Do Blend
      while ( dy-- )
      {
         for ( int32_t i=0; i<dx; i++ )
         {
            dst[0]=(BYTE)(((src[0]-dst[0])*A+(dst[0]<<8))>>8);
            dst[1]=(BYTE)(((src[1]-dst[1])*A+(dst[1]<<8))>>8);
            dst[2]=(BYTE)(((src[2]-dst[2])*A+(dst[2]<<8))>>8);
            dst+=4;
            src+=4;
         }
         dst+=(m_size.cx-dx)<<2;
         src+=(dib->m_size.cx-dx)<<2;
      }
   }

   void dib::DarkenRect ( dib *dib, int32_t x, int32_t y )
   {
      // Clip Rect
      int32_t px=(x>=0) ? x : 0;
      int32_t py=(y>=0) ? y : 0;
      int32_t dx=((x+dib->m_size.cx)<m_size.cx) ? dib->m_size.cx : m_size.cx-x;
      int32_t dy=((y+dib->m_size.cy)<m_size.cy) ? dib->m_size.cy : m_size.cy-y;
      dx=(x>=0) ? dx : dx + x;
      dy=(y>=0) ? dy : dy + y;

      // If Nothing to Darken return
      if ( (dx<=0) || (dy<=0) )
         return;

      // Prepare buffer Addresses
      BYTE *src=(BYTE *)dib->get_data()+(((py-y)*dib->m_size.cx)+px-x)*4;
      BYTE *dst=(BYTE *)get_data()+((py*m_size.cx)+px)*4;

      // Do Darken
      while ( dy-- )
      {
         for ( int32_t i=0; i<dx; i++ )
         {
            dst[0]=(BYTE)((src[0]<dst[0]) ? src[0] : dst[0]);
            dst[1]=(BYTE)((src[1]<dst[1]) ? src[1] : dst[1]);
            dst[2]=(BYTE)((src[2]<dst[2]) ? src[2] : dst[2]);
            dst+=4;
            src+=4;
         }
         dst+=(m_size.cx-dx)<<2;
         src+=(dib->m_size.cx-dx)<<2;
      }
   }

   void dib::DifferenceRect ( dib *dib, int32_t x, int32_t y )
   {
      // Clip Rect
      int32_t px=(x>=0) ? x : 0;
      int32_t py=(y>=0) ? y : 0;
      int32_t dx=((x+dib->m_size.cx)<m_size.cx) ? dib->m_size.cx : m_size.cx-x;
      int32_t dy=((y+dib->m_size.cy)<m_size.cy) ? dib->m_size.cy : m_size.cy-y;
      dx=(x>=0) ? dx : dx + x;
      dy=(y>=0) ? dy : dy + y;

      // If Nothing to Difference return
      if ( (dx<=0) || (dy<=0) )
         return;

      // Prepare buffer Addresses
      BYTE *src=(BYTE *)dib->get_data()+(((py-y)*dib->m_size.cx)+px-x)*4;
      BYTE *dst=(BYTE *)get_data()+((py*m_size.cx)+px)*4;

      // Do Difference
      while ( dy-- )
      {
         for ( int32_t i=0; i<dx; i++ )
         {
            int32_t Difference;
            Difference=src[0]-dst[0];
            dst[0]=(BYTE)((Difference<0) ? -Difference : Difference);
            Difference=src[1]-dst[1];
            dst[1]=(BYTE)((Difference<0) ? -Difference : Difference);
            Difference=src[2]-dst[2];
            dst[2]=(BYTE)((Difference<0) ? -Difference : Difference);
            dst+=4;
            src+=4;
         }
         dst+=(m_size.cx-dx)<<2;
         src+=(dib->m_size.cx-dx)<<2;
      }
   }

   void dib::LightenRect ( dib *dib, int32_t x, int32_t y )
   {
      // Clip Rect
      int32_t px=(x>=0) ? x : 0;
      int32_t py=(y>=0) ? y : 0;
      int32_t dx=((x+dib->m_size.cx)<m_size.cx) ? dib->m_size.cx : m_size.cx-x;
      int32_t dy=((y+dib->m_size.cy)<m_size.cy) ? dib->m_size.cy : m_size.cy-y;
      dx=(x>=0) ? dx : dx + x;
      dy=(y>=0) ? dy : dy + y;

      // If Nothing to Lighten return
      if ( (dx<=0) || (dy<=0) )
         return;

      // Prepare buffer Addresses
      BYTE *src=(BYTE *)dib->get_data()+(((py-y)*dib->m_size.cx)+px-x)*4;
      BYTE *dst=(BYTE *)get_data()+((py*m_size.cx)+px)*4;

      // Do Lighten
      while ( dy-- )
      {
         for ( int32_t i=0; i<dx; i++ )
         {
            dst[0]=(BYTE)((src[0]>dst[0]) ? src[0] : dst[0]);
            dst[1]=(BYTE)((src[1]>dst[1]) ? src[1] : dst[1]);
            dst[2]=(BYTE)((src[2]>dst[2]) ? src[2] : dst[2]);
            dst+=4;
            src+=4;
         }
         dst+=(m_size.cx-dx)<<2;
         src+=(dib->m_size.cx-dx)<<2;
      }
   }

   void dib::MultiplyRect ( dib *dib, int32_t x, int32_t y )
   {
      // Clip Rect
      int32_t px=(x>=0) ? x : 0;
      int32_t py=(y>=0) ? y : 0;
      int32_t dx=((x+dib->m_size.cx)<m_size.cx) ? dib->m_size.cx : m_size.cx-x;
      int32_t dy=((y+dib->m_size.cy)<m_size.cy) ? dib->m_size.cy : m_size.cy-y;
      dx=(x>=0) ? dx : dx + x;
      dy=(y>=0) ? dy : dy + y;

      // If Nothing to Multiply return
      if ( (dx<=0) || (dy<=0) )
         return;

      // Prepare buffer Addresses
      BYTE *src=(BYTE *)dib->get_data()+(((py-y)*dib->m_size.cx)+px-x)*4;
      BYTE *dst=(BYTE *)get_data()+((py*m_size.cx)+px)*4;

      // Do Multiply
      while ( dy-- )
      {
         for ( int32_t i=0; i<dx; i++ )
         {
            dst[0]=(BYTE)(((src[0])*(dst[0]))>>8);
            dst[1]=(BYTE)(((src[1])*(dst[1]))>>8);
            dst[2]=(BYTE)(((src[2])*(dst[2]))>>8);
            dst+=4;
            src+=4;
         }
         dst+=(m_size.cx-dx)<<2;
         src+=(dib->m_size.cx-dx)<<2;
      }
   }

   void dib::ScreenRect ( dib *dib, int32_t x, int32_t y )
   {
      // Clip Rect
      int32_t px=(x>=0) ? x : 0;
      int32_t py=(y>=0) ? y : 0;
      int32_t dx=((x+dib->m_size.cx)<m_size.cx) ? dib->m_size.cx : m_size.cx-x;
      int32_t dy=((y+dib->m_size.cy)<m_size.cy) ? dib->m_size.cy : m_size.cy-y;
      dx=(x>=0) ? dx : dx + x;
      dy=(y>=0) ? dy : dy + y;

      // If Nothing to Screen return
      if ( (dx<=0) || (dy<=0) )
         return;

      // Prepare buffer Addresses
      BYTE *src=(BYTE *)dib->get_data()+(((py-y)*dib->m_size.cx)+px-x)*4;
      BYTE *dst=(BYTE *)get_data()+((py*m_size.cx)+px)*4;

      // Do Screen
      while ( dy-- )
      {
         for ( int32_t i=0; i<dx; i++ )
         {
            dst[0]=(BYTE)(255-(((255-src[0])*(255-dst[0]))>>8));
            dst[1]=(BYTE)(255-(((255-src[1])*(255-dst[1]))>>8));
            dst[2]=(BYTE)(255-(((255-src[2])*(255-dst[2]))>>8));
            dst+=4;
            src+=4;
         }
         dst+=(m_size.cx-dx)<<2;
         src+=(dib->m_size.cx-dx)<<2;
      }
   }

   //////////////////////////////////////////////////////////////////////
   // Line Functions
   //////////////////////////////////////////////////////////////////////

   /*void dib::Line ( int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t R, int32_t G, int32_t B )
   {
   int32_t dx, dy, k1, k2, d, x, y;
   COLORREF color=RGB ( B, G, R );

   dx=x2-x1;
   dy=y2-y1;
   d=(dy<<1)-dx;
   k1=dy<<1;
   k2=(dy-dx)<<1;
   x=x1;
   y=y1;

   get_data()[y*m_size.cx+x]=color;
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
   get_data()[y*m_size.cx+x]=color;
   }
   }*/


   void dib::horizontal_line(int32_t y, int32_t R, int32_t G, int32_t B, int32_t A, int32_t x1, int32_t x2)
   {
      if(m_size.cx == 0)
         return;
      x1 %= m_size.cx;
      x2 %= m_size.cx;
      if(x2 < 0)
         x2 += m_size.cx;
      if(x1 < 0)
         x1 += m_size.cx;
      COLORREF color=RGB ( B, G, R ) | (A << 24);
      COLORREF * pdata = get_data() + y * (m_iScan / sizeof(COLORREF));
      for(int32_t x = x1; x <= x2; x++)
      {
         *pdata = color;
         pdata++;
      }
   }

   void dib::Line ( int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t R, int32_t G, int32_t B )
   {
      int32_t d, x, y, core, ay, sx, sy, dx, dy;
      COLORREF color=RGB ( B, G, R );

      dx=x2-x1;
      core=abs ( dx )<<1;
      sx=(dx<0) ? -1 : 1;
      dy=y2-y1;
      ay=abs ( dy )<<1;
      sy=(dy<0) ? -1 : 1;
      x=x1;
      y=y1;

      if ( core>ay )
      {
         d=ay-(core>>1);
         while ( x!=x2 )
         {
            get_data()[y*(m_iScan / sizeof(COLORREF)) + x] = color;
            if ( d>=0 )
            {
               y+=sy;
               d-=core;
            }
            x+=sx;
            d+=ay;
         }
      }
      else
      {
         d=core-(ay>>1);
         while ( y!=y2 )
         {
            get_data()[y*(m_iScan / sizeof(COLORREF)) + x] = color;
            if ( d>=0 )
            {
               x+=sx;
               d-=ay;
            }
            y+=sy;
            d+=core;
         }
      }
   }

   void dib::LineGlass ( int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t R, int32_t G, int32_t B, int32_t A )
   {
      int32_t d, x, y, core, ay, sx, sy, dx, dy;
//      COLORREF color=RGB ( B, G, R );
      BYTE *dst=(BYTE *)get_data();

      dx=x2-x1;
      core=abs ( dx )<<1;
      sx=(dx<0) ? -1 : 1;
      dy=y2-y1;
      ay=abs ( dy )<<1;
      sy=(dy<0) ? -1 : 1;
      x=x1;
      y=y1;

      if ( core>ay )
      {
         d=ay-(core>>1);
         while ( x!=x2 )
         {
            dst[(y*(m_iScan / sizeof(COLORREF))+x)<<2]=(BYTE)(((B-dst[(y*(m_iScan / sizeof(COLORREF))+x)<<2])*A+(dst[(y*(m_iScan / sizeof(COLORREF))+x)<<2]<<8))>>8);
            dst[((y*(m_iScan / sizeof(COLORREF))+x)<<2)+1]=(BYTE)(((G-dst[((y*(m_iScan / sizeof(COLORREF))+x)<<2)+1])*A+(dst[((y*(m_iScan / sizeof(COLORREF))+x)<<2)+1]<<8))>>8);
            dst[((y*(m_iScan / sizeof(COLORREF))+x)<<2)+2]=(BYTE)(((R-dst[((y*(m_iScan / sizeof(COLORREF))+x)<<2)+2])*A+(dst[((y*(m_iScan / sizeof(COLORREF))+x)<<2)+2]<<8))>>8);
            if ( d>=0 )
            {
               y+=sy;
               d-=core;
            }
            x+=sx;
            d+=ay;
         }
      }
      else
      {
         d=core-(ay>>1);
         while ( y!=y2 )
         {
            dst[(y*(m_iScan / sizeof(COLORREF))+x)<<2]=(BYTE)(((B-dst[(y*(m_iScan / sizeof(COLORREF))+x)<<2])*A+(dst[(y*(m_iScan / sizeof(COLORREF))+x)<<2]<<8))>>8);
            dst[((y*(m_iScan / sizeof(COLORREF))+x)<<2)+1]=(BYTE)(((G-dst[((y*(m_iScan / sizeof(COLORREF))+x)<<2)+1])*A+(dst[((y*(m_iScan / sizeof(COLORREF))+x)<<2)+1]<<8))>>8);
            dst[((y*(m_iScan / sizeof(COLORREF))+x)<<2)+2]=(BYTE)(((R-dst[((y*(m_iScan / sizeof(COLORREF))+x)<<2)+2])*A+(dst[((y*(m_iScan / sizeof(COLORREF))+x)<<2)+2]<<8))>>8);
            if ( d>=0 )
            {
               x+=sx;
               d-=ay;
            }
            y+=sy;
            d+=core;
         }
      }
   }

   void dib::Mask(COLORREF crMask, COLORREF crInMask, COLORREF crOutMask)
   {
      COLORREF crFind = RGB(rgba_get_b(crMask), rgba_get_g(crMask), rgba_get_r(crMask));
      COLORREF crSet = RGB(rgba_get_b(crInMask), rgba_get_g(crInMask), rgba_get_r(crInMask));
      COLORREF crUnset  = RGB(rgba_get_b(crOutMask), rgba_get_g(crOutMask), rgba_get_r(crOutMask));

      int64_t size = area();

      for ( int32_t i=0; i<size; i++ )
         if(get_data()[i]== crFind)
            get_data()[i] = crSet;
         else
            get_data()[i] = crUnset;

   }

   void dib::transparent_color(color color)
   {
      COLORREF crFind = color.get_rgb();
      int64_t iSize = area();

      for (int32_t i=0; i<iSize; i++ )
         if((get_data()[i] & 0x00ffffff) == crFind)
            ((LPBYTE)&get_data()[i])[3] = 255;
         else
            ((LPBYTE)&get_data()[i])[3] = 0;
   }

   void dib::channel_mask(uchar uchFind, uchar uchSet, uchar uchUnset, visual::rgba::echannel echannel)
   {
      int32_t size = (m_iScan / sizeof(COLORREF)) * m_size.cy;
      uchar * puch = (uchar * ) get_data();
      puch += ((int32_t) echannel) % 4;

      for(int32_t i = 0; i < size; i++)
      {
         if(*puch == uchFind)
            *puch = uchSet;
         else
            *puch = uchUnset;
         puch += 4;
      }
   }

   uint32_t dib::GetPixel(int32_t x, int32_t y)
   {
      uint32_t dw = *(get_data() + x + (m_size.cy - y - 1) * (m_iScan / sizeof(COLORREF)));
      return RGB(rgba_get_b(dw), rgba_get_g(dw), rgba_get_r(dw));
   }

   // too slow for animation on AMD XP gen_hon.
   // TOP SUGGESTION:
   // The gradient can´t have more then 256 levels of the most bright color
   // (white). So creating a radial fill of radius 256 and then using fasting
   // stretching algorithms is much faster than calculating radial fill.
   void dib::RadialFill(BYTE alpha, BYTE red, BYTE green, BYTE blue, int32_t xCenter, int32_t yCenter, int32_t iRadius)
   {
      if (iRadius == 0)
         return;
      /*if(version == 0)
      {

      int32_t iR = iRadius - 1;

      int32_t xL = xCenter - iR;
      int32_t xU = xCenter + iR;
      int32_t yL = yCenter - iR;
      int32_t yU = yCenter + iR;


      if(xL < 0) xL = 0;
      if(xU >= m_Size.(m_iScan / sizeof(COLORREF))) xU = m_Size.(m_iScan / sizeof(COLORREF)) - 1;
      if(yL < 0) yL = 0;
      if(yU >= m_Size.m_size.cy) yU = m_Size.m_size.cy - 1;


      BYTE *dst = ((BYTE*)(get_data() + xL + yL * m_Size.(m_iScan / sizeof(COLORREF))));
      uint32_t dwAdd = ((m_Size.(m_iScan / sizeof(COLORREF)) - 1 - xU) + xL) * 4;
      int32_t size=m_Size.(m_iScan / sizeof(COLORREF))*m_Size.m_size.cy;
      double iLevel;

      int32_t dx, dy;
      int32_t dx0, dy0;
      int32_t dx1, dy1;
      int32_t dx2, dy2;
      int32_t dx3, dy3;
      int32_t dx4, dy4;
      int32_t dx5, dy5;
      int32_t dx6, dy6;
      int32_t dx7, dy7;
      int32_t dx8, dy8;
      int32_t dx9, dy9;
      int32_t dxA, dyA;
      int32_t dxB, dyB;
      int32_t dxC, dyC;
      int32_t dxD, dyD;
      int32_t dxE, dyE;
      int32_t dxF, dyF;

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
      int32_t x, y;

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
         LPBYTE lpb = ((LPBYTE) NULL) +  (*((uint_ptr *) &lpbAlloc[3]) & ~3);


         int32_t x, y;
         int32_t b;

//         int32_t r2 = iRadius * iRadius;

         for(y = 0; y < iRadius; y++)
         {
            for(x = y; x < iRadius; x++)
            {
               b = (int32_t) (sqrt((double) (x * x) + (y * y)) * 255 / iRadius);
               if(b > 255)
                  b = 0;
               else
                  b = 255 - b;


               lpb[x + y * iRadius] = (byte) b;
               lpb[y + x * iRadius] = (byte) b;
            }
         }


         int32_t iR = iRadius - 1;

         int32_t xL = xCenter - iR;
         int32_t xU = xCenter + iR;
         int32_t yL = yCenter - iR;
         int32_t yU = yCenter + iR;


         if(xL < 0) xL = 0;
         if(xU >= m_size.cx) xU = m_size.cx - 1;
         if(yL < 0) yL = 0;
         if(yU >= m_size.cy) yU = m_size.cy - 1;


         BYTE *dst = ((BYTE*)(get_data() + xL + yL * (m_iScan / sizeof(COLORREF))));
         uint32_t dwAdd = (((m_iScan / sizeof(COLORREF)) - 1 - xU) + xL) * 4;
//         int64_t size = area();

         int32_t dx, dy;

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
      int32_t xCenter, int32_t yCenter, int32_t iRadius)
   {
      if (iRadius == 0)
         return;

      map();
      /*if(version == 0)
      {

      int32_t iR = iRadius - 1;

      int32_t xL = xCenter - iR;
      int32_t xU = xCenter + iR;
      int32_t yL = yCenter - iR;
      int32_t yU = yCenter + iR;


      if(xL < 0) xL = 0;
      if(xU >= m_Size.(m_iScan / sizeof(COLORREF))) xU = m_Size.(m_iScan / sizeof(COLORREF)) - 1;
      if(yL < 0) yL = 0;
      if(yU >= m_Size.m_size.cy) yU = m_Size.m_size.cy - 1;


      BYTE *dst = ((BYTE*)(get_data() + xL + yL * m_Size.(m_iScan / sizeof(COLORREF))));
      uint32_t dwAdd = ((m_Size.(m_iScan / sizeof(COLORREF)) - 1 - xU) + xL) * 4;
      int32_t size=m_Size.(m_iScan / sizeof(COLORREF))*m_Size.m_size.cy;
      double iLevel;

      int32_t dx, dy;
      int32_t dx0, dy0;
      int32_t dx1, dy1;
      int32_t dx2, dy2;
      int32_t dx3, dy3;
      int32_t dx4, dy4;
      int32_t dx5, dy5;
      int32_t dx6, dy6;
      int32_t dx7, dy7;
      int32_t dx8, dy8;
      int32_t dx9, dy9;
      int32_t dxA, dyA;
      int32_t dxB, dyB;
      int32_t dxC, dyC;
      int32_t dxD, dyD;
      int32_t dxE, dyE;
      int32_t dxF, dyF;

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
      int32_t x, y;

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

         primitive::memory mem;

         mem.allocate((iRadius * iRadius) + 4);

         LPBYTE lpbAlloc = mem.get_data();

         LPBYTE lpb = lpbAlloc;


         int32_t x, y;
         int32_t b;

//         int32_t r2 = iRadius * iRadius;

         for(y = 0; y < iRadius; y++)
         {
            for(x = y; x < iRadius; x++)
            {
               b = (int32_t) (sqrt((double) (x * x) + (y * y)) * 255 / iRadius);
               if(b > 255)
                  b = 0;
               else
                  b = ~b;


               lpb[x + y * iRadius] = (byte) b;
               lpb[y + x * iRadius] = (byte) b;
            }
         }


         int32_t iR = iRadius - 1;

         int32_t xL = xCenter - iR;
         int32_t xU = xCenter + iR;
         int32_t yL = yCenter - iR;
         int32_t yU = yCenter + iR;


         if(xL < 0) xL = 0;
         if(xU >= m_size.cx) xU = m_size.cx - 1;
         if(yL < 0) yL = 0;
         if(yU >= m_size.cy) yU = m_size.cy - 1;


         BYTE *dst = ((BYTE*)(get_data() + xL + yL * (m_iScan / sizeof(COLORREF))));
         uint32_t dwAdd = ((m_size.cx - 1 - xU) + xL) * 4;
//         int64_t size = area();

         int32_t dx, dy;

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

      }
   }



   void dib::SetIconMask(::visual::icon * picon, int32_t cx, int32_t cy)
   {

      throw todo(get_app());

      // xxx todo create(m_size.cx, m_size.cy);

      if(m_size.cx <= 0 || m_size.cy <= 0)
         return;




      // White blend dib
      dib dib1;

      throw todo(get_app());

      // xxx todo dib1.create(m_size.cx, m_size.cy);

      dib1.Fill(0, 255, 255, 255);

#ifdef METROWIN

      throw not_implemented(get_app());

#else

      dib1.get_graphics()->DrawIcon(
         0, 0,
         picon,
         m_size.cx, m_size.cy,
         0,
         NULL,
         DI_IMAGE | DI_MASK);

#endif

      // Black blend dib
      ::draw2d::dib_sp spdib2(allocer());


      throw todo(get_app());

      // xxx todo spdib2->create(m_size.cx, m_size.cy);
      spdib2->Fill(0, 0, 0, 0);

#ifdef METROWIN

      throw not_implemented(get_app());

#else

      spdib2->get_graphics()->DrawIcon(
         0, 0,
         picon,
         m_size.cx, m_size.cy,
         0,
         NULL,
         DI_IMAGE | DI_MASK);

#endif

      // Mask dib
      dib dibM;
      throw todo(get_app());

      // xxx todo dibM.create(m_size.cx, m_size.cy);

#ifdef METROWIN

      throw not_implemented(get_app());

#else

      dibM.get_graphics()->DrawIcon(
         0, 0,
         picon,
         m_size.cx, m_size.cy,
         0,
         NULL,
         DI_MASK);

#endif

      BYTE * r1=(BYTE*)dib1.get_data();
      BYTE * r2=(BYTE*)spdib2->get_data();
      BYTE * srcM=(BYTE*)dibM.get_data();
      BYTE * dest=(BYTE*)get_data();
      int32_t iSize = m_size.cx*m_size.cy;

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
            bMax = MAX(b, bMax);
            b =(BYTE)(r1[1]  - r2[1]);
            bMax = MAX(b, bMax);
            b =(BYTE)(r1[2]  - r2[2]);
            bMax = MAX(b, bMax);
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
      // ::draw2d::dib_sp spdib(allocer());
      //   spdib->Paste(this);

      int32_t l = MAX(m_size.cx, m_size.cy);


      int32_t jmax = MIN(l, m_size.cy / 2);
      int32_t jmin = - jmax;
      int32_t imax = MIN(l, m_size.cx / 2);
      int32_t imin = - imax;


      int32_t joff = m_size.cy / 2;
      int32_t ioff = m_size.cx / 2;

      //int32_t iAngle = iStep % 360;
      //int32_t iAngle = iStep;
      //int32_t iAngle = 1;
      //int32_t k = 0;

      /*     for ( int32_t j=jmin; j<jmax; j++ )
      {
      for ( int32_t i=imin; i<imax; i++ )
      {
      int32_t x, y;

      // A Combination of a 2d Translation/rotation/Scale Matrix
      x=int32_t(cos10(i, iAngle) - sin10(j, iAngle)) + ioff;
      y=int32_t(sin10(i, iAngle) + cos10(j, iAngle)) + joff;
      get_data()[(j+joff)*m_size.cx+(i+ioff)]=
      spdib->get_data()[abs(y%m_size.cy)*m_size.cx+abs(x%m_size.cx)];
      //k++;
      }
      (j+joff)*m_size.cx+(i+ioff)
      }*/

      int32_t k = 0;
      double dCos = ::cos(dAngle * pi() / 180.0) * dScale;
      double dSin = ::sin(dAngle * pi() / 180.0) * dScale;
      int32_t cx1 = m_size.cx - 1;
      int32_t cy1 = m_size.cy - 1;
      for ( int32_t j=jmin; j<jmax; j++ )
      {
         for ( int32_t i=imin; i<imax; i++ )
         {
            int32_t x, y;

            // A Combination of a 2d Translation/rotation/Scale Matrix
            //x=abs((int32_t(dCos * i - dSin * j) + ioff) % m_size.cx);
            //y=abs((int32_t(dSin * i + dCos * j) + joff) % m_size.cy);

            x = (int32_t) abs((dCos * i - dSin * j) + ioff);
            y = (int32_t) abs((dSin * i + dCos * j) + joff);

            if((x / m_size.cx) % 2 == 0)
            {
               x %= m_size.cx;
            }
            else
            {
               x = cx1 - (x % m_size.cx);
            }

            if((y / m_size.cy) % 2 == 0)
            {
               y %= m_size.cy;
            }
            else
            {
               y = cy1 - (y % m_size.cy);
            }



            get_data()[(j+joff)*m_size.cx+(i+ioff)]=
               pdib->get_data()[y * m_size.cx + x];
            k++;
         }
      }
   }


   void dib::Rotate034(dib * pdib, double dAngle, double dScale)
   {

      int32_t l = MAX(m_size.cx, m_size.cy);


      int32_t jmax = MIN(l, m_size.cy / 2);
      int32_t jmin = - jmax;
      int32_t imax = MIN(l, m_size.cx / 2);
      int32_t imin = - imax;


      if((m_size.cy % 2) == 1)
         jmax++;

      if((m_size.cx % 2) == 1)
         imax++;

      int32_t joff = m_size.cy / 2;
      int32_t ioff = m_size.cx / 2;


      int32_t k = 0;
      double dCos = ::cos(dAngle * pi() / 180.0) * dScale;
      double dSin = ::sin(dAngle * pi() / 180.0) * dScale;
      int32_t cx1 = m_size.cx - 1;
      int32_t cy1 = m_size.cy - 1;
      for ( int32_t j=jmin; j<jmax; j++ )
      {
         for ( int32_t i=imin; i<imax; i++ )
         {
            int32_t x, y;

            // A Combination of a 2d Translation/rotation/Scale Matrix
            //x=abs((int32_t(dCos * i - dSin * j) + ioff) % m_size.cx);
            //y=abs((int32_t(dSin * i + dCos * j) + joff) % m_size.cy);

            x = (int32_t) abs((dCos * i - dSin * j) + ioff);
            y = (int32_t) abs((dSin * i + dCos * j) + joff);

            if((x / m_size.cx) % 2 == 0)
            {
               x %= m_size.cx;
            }
            else
            {
               x = cx1 - (x % m_size.cx);
            }

            if((y / m_size.cy) % 2 == 0)
            {
               y %= m_size.cy;
            }
            else
            {
               y = cy1 - (y % m_size.cy);
            }



            get_data()[(j+joff)*m_size.cx+(i+ioff)]=
               pdib->get_data()[y * m_size.cx + x];
            k++;
         }
      }
   }

   void dib::rotate(dib * pdib,LPCRECT lpcrect,double dAngle,double dScale)
   {
      // ::draw2d::dib_sp spdib(allocer());
      //   spdib->Paste(this);



      rect rect(lpcrect);

//      int32_t cx = rect.width();
  //    int32_t cy = rect.height();

      int32_t l = MAX(m_size.cx, m_size.cy);

      int32_t jmax = MIN(l, m_size.cy / 2);
      int32_t jmin = - jmax;
      int32_t imax = MIN(l, m_size.cx / 2);
      int32_t imin = - imax;


      int32_t joff = m_size.cy / 2 + rect.left;
      int32_t ioff = m_size.cx / 2 + rect.top;

      //int32_t iAngle = iStep % 360;
      //int32_t iAngle = iStep;
      //int32_t iAngle = 1;
      //int32_t k = 0;

      /*     for ( int32_t j=jmin; j<jmax; j++ )
      {
      for ( int32_t i=imin; i<imax; i++ )
      {
      int32_t x, y;

      // A Combination of a 2d Translation/rotation/Scale Matrix
      x=int32_t(cos10(i, iAngle) - sin10(j, iAngle)) + ioff;
      y=int32_t(sin10(i, iAngle) + cos10(j, iAngle)) + joff;
      get_data()[(j+joff)*m_size.cx+(i+ioff)]=
      spdib->get_data()[abs(y%m_size.cy)*m_size.cx+abs(x%m_size.cx)];
      //k++;
      }
      (j+joff)*m_size.cx+(i+ioff)
      }*/

      int32_t k = 0;
      double dCos = ::cos(dAngle * pi() / 180.0) * dScale;
      double dSin = ::sin(dAngle * pi() / 180.0) * dScale;
      int32_t cx1 = m_size.cx - 1;
      int32_t cy1 = m_size.cy - 1;
      for ( int32_t j=jmin; j<jmax; j++ )
      {
         for ( int32_t i=imin; i<imax; i++ )
         {
            int32_t x, y;

            // A Combination of a 2d Translation/rotation/Scale Matrix
            //x=abs((int32_t(dCos * i - dSin * j) + ioff) % m_size.cx);
            //y=abs((int32_t(dSin * i + dCos * j) + joff) % m_size.cy);

            x = (int32_t) abs((dCos * i - dSin * j) + ioff);
            y = (int32_t) abs((dSin * i + dCos * j) + joff);

            if((x / m_size.cx) % 2 == 0)
            {
               x %= m_size.cx;
            }
            else
            {
               x = cx1 - (x % m_size.cx);
            }

            if((y / m_size.cy) % 2 == 0)
            {
               y %= m_size.cy;
            }
            else
            {
               y = cy1 - (y % m_size.cy);
            }



            get_data()[(j+joff)*m_size.cx+(i+ioff)]=
               pdib->get_data()[y * m_size.cx + x];
            k++;
         }
      }
   }

   /*int32_t dib::cos(int32_t i, int32_t iAngle)
   {
   return (int32_t) (((_int64) i * CosN[iAngle]) >> 32);
   }

   int32_t dib::sin(int32_t i, int32_t iAngle)
   {
   return (int32_t) (((_int64) i * SinN[iAngle]) >> 32);
   }*/


   void dib::FillByte(uchar uch)
   {

      if(area() <= 0 || get_data() == NULL)
         return;

      memset(get_data(), uch, (::primitive::memory_size) (area() * sizeof(COLORREF)));

   }

   void dib::Fill(int32_t level)
   {

      if(level == 0)
      {

         zero(m_pcolorref, (size_t) area() * sizeof(COLORREF));

      }
      else
      {

#ifdef WINDOWS

         FillMemory(m_pcolorref, (size_t) area() * sizeof(COLORREF), level);

#else

         memset(m_pcolorref, level, (size_t) area() * sizeof(COLORREF));

#endif

      }

   }


   COLORREF dib::make_colorref(int32_t a, int32_t r, int32_t g, int32_t b)
   {

      return ARGB(a, b, g, r);

   }


   void dib::Fill (int32_t a, int32_t r, int32_t g, int32_t b)
   {

      map();

      if(a == r && a == g && a == b)
      {

         memset(m_pcolorref,a,area() * sizeof(COLORREF));

      }
      else
      {

         COLORREF color = make_colorref(a,r,g,b);
         int64_t size = area();

         COLORREF * pcr = m_pcolorref;

#pragma omp parallel for
         for(int64_t i = 0;i < size;i++)
            pcr[i] = color;

      }

   }

   COLORREF dib::GetAverageColor()
   {
      map();
      double dR = 0.0;
      double dG = 0.0;
      double dB = 0.0;
      int32_t iRLine;
      int32_t iGLine;
      int32_t iBLine;
      double dDiv = m_size.cx * m_size.cy;
      if(dDiv > 0)
      {

         for (int32_t y = 0; y < m_size.cy; y++)
         {
            iRLine = 0;
            iGLine = 0;
            iBLine = 0;
            LPBYTE lpb = ((LPBYTE)get_data()) + m_iScan * y;
            for (int32_t x = 0; x < m_size.cx; x++)
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
         int32_t iR = (int32_t) dR;
         int32_t iG = (int32_t) dG;
         int32_t iB = (int32_t) dB;
         return RGB(iR, iG, iB);
      }
      else
      {
         return 0;
      }

   }


   void dib::do_xor(dib * pdib)
   {
      if(m_size.cx != pdib->m_size.cx
         || m_size.cy != pdib->m_size.cy)
      {
         return;
      }
      int32_t iCount = m_size.cx * m_size.cy;
      LPDWORD lpd1 = (LPDWORD) get_data();
      LPDWORD lpd2 = (LPDWORD) pdib->get_data();
      for(int32_t i = 0; i < iCount; i++)
      {
         *lpd1 = *lpd1 ^ *lpd2;
         lpd1++;
         lpd2++;
      }
   }

   void dib::create_frame(::size size, int32_t iFrameCount)
   {
      int32_t iSliceCount = (int32_t) sqrt((double) iFrameCount);
      int32_t iFrameWidth = size.cx / iSliceCount;
      int32_t iFrameHeight = size.cy / iSliceCount;
      create(iFrameWidth, iFrameHeight);
   }

   void dib::set_frame1(void * lpdata, int32_t iFrame, int32_t iFrameCount)
   {
      int32_t iSliceCount = (int32_t) sqrt((double) iFrameCount);
      if(iSliceCount == 0)
         iSliceCount = 1;
      int32_t iFrameWidth = m_size.cx / iSliceCount;
      int32_t iFrameHeight = m_size.cy / iSliceCount;
      int32_t iX = iFrame % iSliceCount;
      int32_t iY = iFrame / iSliceCount;
      COLORREF * lpDest = &get_data()[iFrameWidth * iX + iY * iFrameHeight * m_size.cx];
      COLORREF * lpSrc = (COLORREF *) lpdata;
      COLORREF * lpDestLine;
      for(int32_t y = 0; y < iFrameHeight; y++)
      {
         lpDestLine = &lpDest[y * m_size.cx];
         for(int32_t x = 0; x < iFrameWidth; x++)
         {
            *lpDestLine = *lpSrc;
            lpDestLine++;
            lpSrc++;
         }
      }
   }

   void dib::set_frame2(void * lpdata, int32_t iFrame, int32_t iFrameCount)
   {
      int32_t iSliceCount = (int32_t) sqrt((double) iFrameCount);
      if(iSliceCount == 0)
         iSliceCount = 1;
      int32_t iFrameWidth = m_size.cx / iSliceCount;
      int32_t iFrameHeight = m_size.cy / iSliceCount;
      int32_t iX = iFrame % iSliceCount;
      int32_t iY = iFrame / iSliceCount;
      COLORREF * lpDest = &get_data()[iFrameWidth * iX + iY * iFrameHeight * m_size.cx];
      COLORREF * lpSrc = (COLORREF *) lpdata;
      COLORREF * lpDestLine;
      for(int32_t y = iFrameHeight - 1; y >= 0; y--)
      {
         lpDestLine = &lpDest[y * m_size.cx];
         for(int32_t x = 0; x < iFrameWidth; x++)
         {
            *lpDestLine = *lpSrc;
            lpDestLine++;
            lpSrc++;
         }
      }
   }

   void dib::xor_dib_frame2(void * lpdata, int32_t iFrame, int32_t iFrameCount)
   {
      int32_t iSliceCount = (int32_t) sqrt((double) iFrameCount);
      if(iSliceCount == 0)
         iSliceCount = 1;
      int32_t iFrameWidth = m_size.cx / iSliceCount;
      int32_t iFrameHeight = m_size.cy / iSliceCount;
      int32_t iX = iFrame % iSliceCount;
      int32_t iY = iFrame / iSliceCount;
      COLORREF * lpDest = &get_data()[iFrameWidth * iX + iY * iFrameHeight * m_size.cx];
      COLORREF * lpSrc = (COLORREF *) lpdata;
      COLORREF * lpDestLine;
      for(int32_t y = iFrameHeight - 1; y >= 0; y--)
      {
         lpDestLine = &lpDest[y * m_size.cx];
         for(int32_t x = 0; x < iFrameWidth; x++)
         {
            *lpDestLine ^= *lpSrc;
            lpDestLine++;
            lpSrc++;
         }
      }
   }

   void dib::get_frame(void * lpdata, int32_t iFrame, int32_t iFrameCount)
   {
      int32_t iSliceCount = (int32_t) sqrt((double) iFrameCount);
      int32_t iFrameWidth = m_size.cx / iSliceCount;
      int32_t iFrameHeight = m_size.cy / iSliceCount;
      int32_t iX = iFrame % iSliceCount;
      int32_t iY = iFrame / iSliceCount;
      COLORREF * lpSrc = &get_data()[iFrameWidth * iX + iY * iFrameHeight *  m_size.cx];
      COLORREF * lpDest = (COLORREF *) lpdata;
      COLORREF * lpSrcLine;
      for(int32_t y = 0; y < iFrameHeight; y++)
      {
         lpSrcLine = &lpSrc[y * m_size.cx];
         for(int32_t x = 0; x < iFrameWidth; x++)
         {
            *lpDest = *lpSrcLine;
            lpDest++;
            lpSrcLine++;
         }
      }
   }

   bool dib::is_rgb_black()
   {
      int32_t iSize = m_size.cx * m_size.cy;
      COLORREF * lp = get_data();
      for(int32_t i = 0; i < iSize; i++)
      {
         if((*lp & 0x00FFFFFF) != 0)
            return false;
         lp++;
      }
      return true;
   }

   void dib::DivideRGB(int32_t iDivide)
   {
      if(iDivide == 0)
      {
         return;
      }
      int32_t iCount = m_size.cx * m_size.cy;
      LPBYTE lp = ((LPBYTE) get_data());
      int32_t i = 0;
      int32_t iCount1 = iCount - iCount % 8;
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

   void dib::DivideARGB(int32_t iDivide)
   {
      if(iDivide == 0)
      {
         return;
      }
      int32_t iCount = m_size.cx * m_size.cy;
      LPBYTE lp = ((LPBYTE) get_data());
      for(int32_t i = 0; i < iCount; i++)
      {
         lp[0] /= (byte) iDivide;
         lp[1] /= (byte) iDivide;
         lp[2] /= (byte) iDivide;
         lp[3] /= (byte) iDivide;
         lp +=4;
      }
   }

   void dib::DivideA(int32_t iDivide)
   {
      if(iDivide == 0)
      {
         return;
      }
      int32_t iCount = m_size.cx * m_size.cy;
      LPBYTE lp = ((LPBYTE) get_data());
      for(int32_t i = 0; i < iCount; i++)
      {
         lp[3] /= (byte) iDivide;
         lp +=4;
      }
   }


   void dib::stretch_dib(dib * pdib)
   {
      UNREFERENCED_PARAMETER(pdib);
      throw interface_only_exception(get_app());
   }

   int32_t dib::cos(int32_t i, int32_t iAngle)
   {
      UNREFERENCED_PARAMETER(i);
      UNREFERENCED_PARAMETER(iAngle);
      throw interface_only_exception(get_app());
   }

   int32_t dib::sin(int32_t i, int32_t iAngle)
   {
      UNREFERENCED_PARAMETER(i);
      UNREFERENCED_PARAMETER(iAngle);
      throw interface_only_exception(get_app());
   }

   int32_t dib::cos10(int32_t i, int32_t iAngle)
   {
      UNREFERENCED_PARAMETER(i);
      UNREFERENCED_PARAMETER(iAngle);
      throw interface_only_exception(get_app());
   }

   int32_t dib::sin10(int32_t i, int32_t iAngle)
   {
      UNREFERENCED_PARAMETER(i);
      UNREFERENCED_PARAMETER(iAngle);
      throw interface_only_exception(get_app());
   }

/*   int32_t dib::m_size.cx
   {
      throw interface_only_exception(get_app());
   }

   int32_t dib::m_size.cy
   {
      throw interface_only_exception(get_app());
   }

   int64_t dib::area()
   {
      return ((int64_t) m_size.cx) * ((int64_t)m_size.cy);
   }

   size dib::m_size
   {
      return size64(m_size.cx, m_size.cy);
   }*/

   double dib::pi()
   {
      return atan(1.0)*4.0;
   }


   void dib::fill_channel(int32_t intensity, visual::rgba::echannel echannel)
   {
      map();
           int32_t offset = ((int32_t)echannel) % 4;
          int64_t size=area();

          COLORREF * pcr = (COLORREF *) &((byte *)m_pcolorref)[offset];

          BYTE * pb;

          int64_t iSize32 = size / 32;
          int32_t i;
          for (i=0; i < iSize32; i+=32 )
          {
             pb = (byte *) &pcr[i];
             pb[0 * 4] = (byte) intensity;
             pb[1 * 4] = (byte) intensity;
             pb[2 * 4] = (byte) intensity;
             pb[3 * 4] = (byte) intensity;
             pb[4 * 4] = (byte) intensity;
             pb[5 * 4] = (byte) intensity;
             pb[6 * 4] = (byte) intensity;
             pb[7 * 4] = (byte) intensity;
             pb[8 * 4] = (byte) intensity;
             pb[9 * 4] = (byte) intensity;
             pb[10 * 4] = (byte) intensity;
             pb[11 * 4] = (byte) intensity;
             pb[12 * 4] = (byte) intensity;
             pb[13 * 4] = (byte) intensity;
             pb[14 * 4] = (byte) intensity;
             pb[15 * 4] = (byte) intensity;
             pb[16 * 4] = (byte) intensity;
             pb[17 * 4] = (byte) intensity;
             pb[18 * 4] = (byte) intensity;
             pb[19 * 4] = (byte) intensity;
             pb[20 * 4] = (byte) intensity;
             pb[21 * 4] = (byte) intensity;
             pb[22 * 4] = (byte) intensity;
             pb[23 * 4] = (byte) intensity;
             pb[24 * 4] = (byte) intensity;
             pb[25 * 4] = (byte) intensity;
             pb[26 * 4] = (byte) intensity;
             pb[27 * 4] = (byte) intensity;
             pb[28 * 4] = (byte) intensity;
             pb[29 * 4] = (byte) intensity;
             pb[30 * 4] = (byte) intensity;
             pb[31 * 4] = (byte) intensity;
          }

          for (i=0; i<size; i++ )
          {
             *((BYTE * ) &pcr[i]) = (byte) intensity;
          }
   }


   void dib::channel_copy(visual::rgba::echannel echannelDst, visual::rgba::echannel echannelSrc)
   {

      map();

      echannelDst = (visual::rgba::echannel) (((int32_t) echannelDst) % 4);
      echannelSrc = (visual::rgba::echannel) (((int32_t) echannelSrc) % 4);

      if(echannelDst == echannelSrc)
         return;

      byte * pdataDst = (byte *) get_data() + ((int32_t)echannelDst);

      byte * pdataSrc = (byte *) get_data() + ((int32_t)echannelSrc);

      for(int32_t y = 0; y < m_size.cy; y++)
      {

         byte * pdst = &pdataDst[m_iScan * y];

         byte * psrc = &pdataSrc[m_iScan * y];

         for(int32_t x = 0; x < m_size.cx; x++)
         {

            *pdst = *psrc;

            pdst += 4;

            psrc += 4;

         }
      }
   }

   void dib::channel_copy(visual::rgba::echannel echannelDst, visual::rgba::echannel echannelSrc, draw2d::dib * pdib)
   {

      if(m_size != pdib->size())
         return;

      map();

      if(m_pcolorref == NULL)
         return;

      pdib->map();

      if(pdib->m_pcolorref == NULL)
         return;

      echannelDst = (visual::rgba::echannel) (((int32_t) echannelDst) % 4);
      echannelSrc = (visual::rgba::echannel) (((int32_t) echannelSrc) % 4);

      byte * pdataDst = (byte *) get_data() + ((int32_t)echannelDst);

      byte * pdataSrc = (byte *) pdib->get_data() + ((int32_t)echannelDst);

      for(int32_t y = 0; y < m_size.cy; y++)
      {

         byte * pdst = &pdataDst[m_iScan * y];

         byte * psrc = &pdataSrc[pdib->m_iScan * y];

         for(int32_t x = 0; x < m_size.cx; x++)
         {

            *pdst = *psrc;

            pdst += 4;

            psrc += 4;

         }
      }
   }

   void dib::write(::file::output_stream & ostream)
   {

      synch_lock ml(&user_mutex());

      ostream << (int32_t) m_size.cx;
      ostream << (int32_t) m_size.cy;
      if(area() <= 0)
         return;
      map();
      int wc = m_size.cx * sizeof(COLORREF);
      for(int32_t i = 0; i < m_size.cy; i++)
      {
         ostream.write(&((byte *) get_data())[m_iScan * i], wc);
      }

   }

   void dib::read(::file::input_stream & istream)
   {

      synch_lock ml(&user_mutex());

      int32_t width;
      int32_t height;
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
      map();
      int wc = width * sizeof(COLORREF);
      for(int32_t i = 0; i < m_size.cy; i++)
      {
         istream.read(&((byte *) get_data())[m_iScan * i], wc);
      }
   }

   void dib::set_rgb ( int32_t R, int32_t G, int32_t B )
   {

      map();

      BYTE *dst=(BYTE*)m_pcolorref;
      int64_t size = area();

      BYTE uchB = (byte) R;
      BYTE uchG = (byte) G;
      BYTE uchR = (byte) B;

      int32_t i = 0;;


      while ( size-- )
      {
         dst[3] = dst[i];
         dst[0] = uchB;
         dst[1] = uchG;
         dst[2] = uchR;
         dst+=4;
      }


/*      COLORREF color = RGB(B, G, R);
      int64_t size = area();

      COLORREF * pcr;

      int64_t iSize32 = size / 32;
      int32_t i;
      for (i = 0; i < iSize32; i += 32)
      {
         pcr = &m_pcolorref[i];
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

      for (i = 0; i<size; i++)
      {
         m_pcolorref[i] = color;
      }*/

   }

   bool dib::rgb_from(::draw2d::dib * pdib)
   {
      if(!create(pdib->size()))
         return false;
      try
      {
         byte * puchSrc = (byte *) get_data();
         byte * puchDst = (byte *) pdib->get_data();
         int64_t iArea = pdib->area();
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


   bool dib::pixelate(int32_t iSize)
   {

      if(iSize <= 1)
         return true;



      int32_t w = m_size.cx;
      int32_t h = m_size.cy;
      int32_t s = m_iScan / sizeof(COLORREF);

      int32_t xCount = w / iSize;
      int32_t yCount = h / iSize;



      int32_t iDiv;
      int32_t iDiv2;

      int32_t a;
      int32_t r;
      int32_t g;
      int32_t b;
      int32_t a2;
      int32_t r2;
      int32_t g2;
      int32_t b2;
      bool bFirst;
      COLORREF * pdata = get_data();
      int32_t x1;
      int32_t y1;
      for(int32_t x = 0; x < xCount; x++)
      {
         x1 = x * iSize;
         for(int32_t y = 0; y < yCount; y++)
         {
            y1 = y * iSize;
            a = 0;
            r = 0;
            g = 0;
            b = 0;
            a2 = 0;
            r2 = 0;
            g2 = 0;
            b2 = 0;
            iDiv = 0;
            iDiv2 = 0;
            bFirst = true;
            for(int32_t i = 0; i < iSize; i++)
            {
               for(int32_t j = 0; j < iSize; j++)
               {
                  COLORREF cr = pdata[x1 + i + (y1 + j) * s];
                  a += argb_get_a_value(cr);
                  r += argb_get_r_value(cr);
                  g += argb_get_g_value(cr);
                  b += argb_get_b_value(cr);
                  iDiv++;
                  if(iDiv >= 64)
                  {
                     a2 = (a2 * iDiv2 + a / iDiv) / (iDiv2 + 1);
                     r2 = (r2 * iDiv2 + r / iDiv) / (iDiv2 + 1);
                     g2 = (g2 * iDiv2 + g / iDiv) / (iDiv2 + 1);
                     b2 = (b2 * iDiv2 + b / iDiv) / (iDiv2 + 1);
                     a = 0;
                     r = 0;
                     g = 0;
                     b = 0;
                     iDiv = 0;
                     iDiv2++;
                  }
               }
            }
            if(iDiv > 0)
            {
               a2 = (a2 * iDiv2 + a / iDiv) / (iDiv2 + 1);
               r2 = (r2 * iDiv2 + r / iDiv) / (iDiv2 + 1);
               g2 = (g2 * iDiv2 + g / iDiv) / (iDiv2 + 1);
               b2 = (b2 * iDiv2 + b / iDiv) / (iDiv2 + 1);
            }
            COLORREF cr = ARGB(a2, r2, g2, b2);
            for(int32_t i = 0; i < iSize; i++)
            {
               for(int32_t j = 0; j < iSize; j++)
               {
                  pdata[x1 + i + (y1 + j) * s] = cr;
               }
            }
         }

      }


      if(w % iSize != 0)
      {
         int32_t x = xCount;
         int32_t x1 = x * iSize;
         int32_t iMax = w - xCount * iSize;
         for(int32_t y = 0; y < yCount; y++)
         {
            y1 = y * iSize;
            a = 0;
            r = 0;
            g = 0;
            b = 0;
            a2 = 0;
            r2 = 0;
            g2 = 0;
            b2 = 0;
            iDiv = 0;
            iDiv2 = 0;
            bFirst = true;
            for(int32_t i = 0; i < iMax; i++)
            {
               for(int32_t j = 0; j < iSize; j++)
               {
                  COLORREF cr = pdata[x1 + i + (y1 + j) * w];
                  a += argb_get_a_value(cr);
                  r += argb_get_r_value(cr);
                  g += argb_get_g_value(cr);
                  b += argb_get_b_value(cr);
                  iDiv++;
                  if(iDiv >= 64)
                  {
                     a2 = (a2 * iDiv2 + a / iDiv) / (iDiv2 + 1);
                     r2 = (r2 * iDiv2 + r / iDiv) / (iDiv2 + 1);
                     g2 = (g2 * iDiv2 + g / iDiv) / (iDiv2 + 1);
                     b2 = (b2 * iDiv2 + b / iDiv) / (iDiv2 + 1);
                     a = 0;
                     r = 0;
                     g = 0;
                     b = 0;
                     iDiv = 0;
                     iDiv2++;
                  }
               }
            }
            if(iDiv > 0)
            {
               a2 = (a2 * iDiv2 + a / iDiv) / (iDiv2 + 1);
               r2 = (r2 * iDiv2 + r / iDiv) / (iDiv2 + 1);
               g2 = (g2 * iDiv2 + g / iDiv) / (iDiv2 + 1);
               b2 = (b2 * iDiv2 + b / iDiv) / (iDiv2 + 1);
            }
            COLORREF cr = ARGB(a2, r2, g2, b2);
            for(int32_t i = 0; i < iMax; i++)
            {
               for(int32_t j = 0; j < iSize; j++)
               {
                  pdata[x1 + i + (y1 + j) * w] = cr;
               }
            }
         }

      }

      if(h % iSize != 0)
      {
         int32_t y = yCount;
         int32_t y1 = y * iSize;
         int32_t jMax = h - yCount * iSize;
         for(int32_t x = 0; x < xCount; x++)
         {
            x1 = x * iSize;
            a = 0;
            r = 0;
            g = 0;
            b = 0;
            a2 = 0;
            r2 = 0;
            g2 = 0;
            b2 = 0;
            iDiv = 0;
            iDiv2 = 0;
            bFirst = true;
            for(int32_t i = 0; i < iSize; i++)
            {
               for(int32_t j = 0; j < jMax; j++)
               {
                  COLORREF cr = pdata[x1 + i + (y1 + j) * w];
                  a += argb_get_a_value(cr);
                  r += argb_get_r_value(cr);
                  g += argb_get_g_value(cr);
                  b += argb_get_b_value(cr);
                  iDiv++;
                  if(iDiv >= 64)
                  {
                     a2 = (a2 * iDiv2 + a / iDiv) / (iDiv2 + 1);
                     r2 = (r2 * iDiv2 + r / iDiv) / (iDiv2 + 1);
                     g2 = (g2 * iDiv2 + g / iDiv) / (iDiv2 + 1);
                     b2 = (b2 * iDiv2 + b / iDiv) / (iDiv2 + 1);
                     a = 0;
                     r = 0;
                     g = 0;
                     b = 0;
                     iDiv = 0;
                     iDiv2++;
                  }
               }
            }
            if(iDiv > 0)
            {
               a2 = (a2 * iDiv2 + a / iDiv) / (iDiv2 + 1);
               r2 = (r2 * iDiv2 + r / iDiv) / (iDiv2 + 1);
               g2 = (g2 * iDiv2 + g / iDiv) / (iDiv2 + 1);
               b2 = (b2 * iDiv2 + b / iDiv) / (iDiv2 + 1);
            }
            COLORREF cr = ARGB(a2, r2, g2, b2);
            for(int32_t i = 0; i < iSize; i++)
            {
               for(int32_t j = 0; j < jMax; j++)
               {
                  pdata[x1 + i + (y1 + j) * w] = cr;
               }
            }
         }

      }

      if(w % iSize != 0)
      {
         int32_t x = xCount;
         int32_t x1 = x * iSize;
         int32_t iMax = w - xCount * iSize;
         int32_t y = yCount;
         int32_t y1 = y * iSize;
         int32_t jMax = h - yCount * iSize;
         x1 = x * iSize;
         a = 0;
         r = 0;
         g = 0;
         b = 0;
         a2 = 0;
         r2 = 0;
         g2 = 0;
         b2 = 0;
         iDiv = 0;
         iDiv2 = 0;
         bFirst = true;
         for(int32_t i = 0; i < iMax; i++)
         {
            for(int32_t j = 0; j < jMax; j++)
            {
               COLORREF cr = pdata[x1 + i + (y1 + j) * w];
               a += argb_get_a_value(cr);
               r += argb_get_r_value(cr);
               g += argb_get_g_value(cr);
               b += argb_get_b_value(cr);
               iDiv++;
               if(iDiv >= 64)
               {
                  a2 = (a2 * iDiv2 + a / iDiv) / (iDiv2 + 1);
                  r2 = (r2 * iDiv2 + r / iDiv) / (iDiv2 + 1);
                  g2 = (g2 * iDiv2 + g / iDiv) / (iDiv2 + 1);
                  b2 = (b2 * iDiv2 + b / iDiv) / (iDiv2 + 1);
                  a = 0;
                  r = 0;
                  g = 0;
                  b = 0;
                  iDiv = 0;
                  iDiv2++;
               }
            }
         }
         if(iDiv > 0)
         {
            a2 = (a2 * iDiv2 + a / iDiv) / (iDiv2 + 1);
            r2 = (r2 * iDiv2 + r / iDiv) / (iDiv2 + 1);
            g2 = (g2 * iDiv2 + g / iDiv) / (iDiv2 + 1);
            b2 = (b2 * iDiv2 + b / iDiv) / (iDiv2 + 1);
         }
         COLORREF cr = ARGB(a2, r2, g2, b2);
         for(int32_t i = 0; i < iMax; i++)
         {
            for(int32_t j = 0; j < jMax; j++)
            {
               pdata[x1 + i + (y1 + j) * w] = cr;
            }
         }
      }

      return true;

   }


   void dib::rate_rgb(int iMul,int iDiv)
   {
      map();
      try
      {
         byte * puch = (byte *)get_data();
         int64_t iArea = area();
         while(iArea > 0)
         {
            puch[0] = MAX(0,MIN(255,puch[0] * iMul / iDiv));
            puch[1] = MAX(0,MIN(255,puch[1] * iMul / iDiv));
            puch[2] = MAX(0,MIN(255,puch[2] * iMul / iDiv));
            puch+=4;
            iArea--;
         }
      }
      catch(...)
      {
      }
   }


   void dib::map(bool bApplyAlphaTransform)
   {

      UNREFERENCED_PARAMETER(bApplyAlphaTransform);

   }


   void dib::unmap()
   {

   }


   void dib::set_mapped()
   {

   }


   bool dib::update_window(::user::draw_interface * pwnd,signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pwnd);
      UNREFERENCED_PARAMETER(pobj);

      // default implementation does nothing, dib should be now updated (before calling update interaction_impl)
      // and ready to be queried if post queried

//      throw interface_only_exception(get_app());


      return true;

   }


   bool dib::print_window(::user::draw_interface * pwnd,signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pwnd);
      UNREFERENCED_PARAMETER(pobj);
      throw interface_only_exception(get_app());
   }


   void dib::gradient_fill(COLORREF clr1, COLORREF clr2, POINT pt1, POINT pt2)
   {

      double dx = pt2.x - pt1.x;

      double dy = pt1.y - pt2.y;

      if(dx == 0.0 && dy == 0.0)
      {
         Fill(
            byte_clip(argb_get_a_value(clr1) * 0.5 + argb_get_a_value(clr2) * 0.5),
            byte_clip(argb_get_r_value(clr1) * 0.5 + argb_get_r_value(clr2) * 0.5),
            byte_clip(argb_get_g_value(clr1) * 0.5 + argb_get_g_value(clr2) * 0.5),
            byte_clip(argb_get_b_value(clr1) * 0.5 + argb_get_b_value(clr2) * 0.5));
      }
      else if(dx == 0.0)
      {

         gradient_horizontal_fill(clr1, clr2, pt1.y, pt2.y);

      }
      else if(dy == 0.0)
      {

         gradient_vertical_fill(clr1, clr2, pt1.x, pt2.x);

      }
      else
      {

//         int x1 = MIN(pt1.x, pt2.x);

  //       int x2 = MAX(pt1.x, pt2.x);

    //     int y1 = MIN(pt1.y, pt2.y);

      //   int y2 = MAX(pt1.y, pt2.y);

//         int top = y1;
//
  //       int left = x1;
//
  //       int right = m_size.cx - x2;
          //
       //  int bottom = m_size.cy - y2;

         int dim = MAX(m_size.cx, m_size.cy);

         double angle = atan2(dy, dx);

         ::draw2d::dib_sp dib(allocer());

         if(abs(dx) > abs(dy))
         {

            double sin = ::sin(angle);

            dib->create((int32_t) (dim / sin), (int32_t) (dim / sin));

            dib->gradient_horizontal_fill(clr1, clr2, pt1.y, pt2.y);

            dib->rotate(this, -angle, 1.0);

         }
         else
         {

            double cos = ::cos(angle);

            dib->create((int32_t) (dim / cos), (int32_t) (dim / cos));

            dib->gradient_vertical_fill(clr1, clr2, pt1.x, pt2.x);

            dib->rotate(this, System.math().GetPi() - angle, 1.0);

         }

      }


   }

   void dib::gradient_horizontal_fill(COLORREF clr1, COLORREF clr2, int start, int end)
   {

      if(end < start)
      {
         ::sort::swap(&start, &end);
         ::sort::swap(&clr1, &clr2);
      }

      end = MIN(end, m_size.cy - 1);
      COLORREF clr = clr1;
      byte * pb = (byte *) m_pcolorref;
      COLORREF * pdata;
      int line = 0;
      for(; line < start; line++)
      {
         pdata = (COLORREF *) &pb[m_iScan * line];
         for(int row = 0; row < m_size.cx; row++)
         {
            *pdata = clr;
            pdata++;
         }
      }
      double d;
      for(; line < end; line++)
      {

         d = ((double) (line - start)) / ((double) (end - start));

         clr = ARGB(
                  byte_clip(argb_get_a_value(clr1) * (1.0 - d) + argb_get_a_value(clr2) * d),
                  byte_clip(argb_get_r_value(clr1) * (1.0 - d) + argb_get_r_value(clr2) * d),
                  byte_clip(argb_get_g_value(clr1) * (1.0 - d) + argb_get_g_value(clr2) * d),
                  byte_clip(argb_get_b_value(clr1) * (1.0 - d) + argb_get_b_value(clr2) * d));

         pdata = (COLORREF *) &pb[m_iScan * line];
         for(int row = 0; row < m_size.cx; row++)
         {
            *pdata = clr;
            pdata++;
         }
      }
      clr = clr2;
      for(; line < m_size.cy; line++)
      {
         pdata = (COLORREF *) &pb[m_iScan * line];
         for(int row = 0; row < m_size.cx; row++)
         {
            *pdata = clr;
            pdata++;
         }
      }
   }

   void dib::gradient_vertical_fill(COLORREF clr1, COLORREF clr2, int start, int end)
   {

      if(end < start)
      {
         ::sort::swap(&start, &end);
         ::sort::swap(&clr1, &clr2);
      }

      end = MIN(end, m_size.cx - 1);
      COLORREF clr = clr1;
      byte * pb = (byte *) m_pcolorref;
      COLORREF * pdata;
      int row = 0;
      for(; row < start; row++)
      {
         pdata = (COLORREF *) &pb[sizeof(COLORREF) * row];
         for(int line = 0; line < m_size.cy; line++)
         {
            *pdata = clr;
            pdata+=m_iScan;
         }
      }
      double d;
      for(; row < end; row++)
      {

         d = ((double) (row - start)) / ((double) (end - start));

         clr = ARGB(
                  byte_clip(argb_get_a_value(clr1) * (1.0 - d) + argb_get_a_value(clr2) * d),
                  byte_clip(argb_get_r_value(clr1) * (1.0 - d) + argb_get_r_value(clr2) * d),
                  byte_clip(argb_get_g_value(clr1) * (1.0 - d) + argb_get_g_value(clr2) * d),
                  byte_clip(argb_get_b_value(clr1) * (1.0 - d) + argb_get_b_value(clr2) * d));

         pdata = (COLORREF *) &pb[sizeof(COLORREF) * row];
         for(int line = 0; line < m_size.cx; line++)
         {
            *pdata = clr;
            pdata+=m_iScan;
         }
      }
      clr = clr2;
      for(; row < m_size.cx; row++)
      {
         pdata = (COLORREF *) &pb[sizeof(COLORREF) * row];
         for(int line = 0; line < m_size.cx; line++)
         {
            *pdata = clr;
            pdata+=m_iScan;
         }
      }
   }

   void dib::gradient_horizontal_fill(COLORREF clr1, COLORREF clr2)
   {
      gradient_horizontal_fill(clr1, clr2, 0, m_size.cy - 1);
   }

   void dib::gradient_vertical_fill(COLORREF clr1, COLORREF clr2)
   {
      gradient_vertical_fill(clr1, clr2, 0, m_size.cx - 1);
   }


   void dib::static_initialize()
   {
      double dCos;
      double dSin;
      double d32 = (1U << 31);
      dPi = atan(1.0) * 4.0;;
      int32_t i;
       for ( i=0; i<360; i++ )
      {
         dCos = ::cos ( i/180.0*dPi );
         dSin = ::sin ( i/180.0*dPi );
         Cosines[i]=float(dCos);
         Sines[i]=float(dSin);
         CosN[i] = (int64_t) (dCos * d32);
         SinN[i] = (int64_t) (dSin * d32);
      }
      d32 = (1U << 31);
      d32 *= 8;
       for(i = 0; i < 10; i++)
      {
         dCos = ::cos ( i/180.0*dPi );
         dSin = ::sin ( i/180.0*dPi );
         Cos10N[i] = (int64_t) (dCos * d32);
         Sin10N[i] = (int64_t) (dSin * d32);
      }

   }


   void dib_paste(dib * pdibthis, dib *pdib)
   {

      pdibthis->Paste(pdib);

   }


   void dib_alloc(::aura::application * papp, dib * & pdib)
   {

      App(papp).alloc(pdib);

   }


   void dib_create(dib * pdib, int w, int h)
   {

      pdib->create(w, h);

   }


   unsigned int * dib_get_data(dib * pdib)
   {

      return (unsigned int * ) pdib->m_pcolorref;

   }


   graphics * dib_get_graphics(dib * pdib)
   {

      return pdib->get_graphics();

   }


} // namespace draw2d




