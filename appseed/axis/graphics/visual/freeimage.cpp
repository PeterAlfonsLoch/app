#include "framework.h"
#include "fiasco_finder.h"


#include <math.h>

#include "freeimage/Source/FreeImage.h"
#include "graphics/visual/visual_FreeImageFileProc.h"


void cra_from_quada(array < COLORREF > & cra, RGBQUAD * pquad, int iCount);

bool gif_load_frame(::draw2d::dib * pdibCompose, ::visual::dib_sp::array * pdiba, ::visual::dib_sp::pointer * pointer, int uFrameIndex, byte * ba, int iScan, array < COLORREF > & cra, int transparentIndex);

bool freeimage_load_diba_frame(::draw2d::dib * pdibCompose, ::visual::dib_sp::array * pdiba, int iFrame, FIBITMAP * pfi, ::aura::application * papp);

bool freeimage_load_diba_from_file(::visual::dib_sp::array * pdiba, ::file::buffer_sp pfile, ::aura::application * papp)
{

   if (pfile == NULL)
      return false;

   FreeImageIO io;
   io.read_proc = __ReadProc2;
   io.seek_proc = __SeekProc2;
   io.tell_proc = __TellProc2;
   io.write_proc = __WriteProc2;

   FIMULTIBITMAP * m = NULL;


   ::draw2d::dib_sp dibCompose(papp->allocer());

   try
   {

      pfile->seek_to_begin();

      FREE_IMAGE_FORMAT format;

      format = FreeImage_GetFileTypeFromHandle(&io, (::file::stream_buffer *)pfile.m_p);

      pfile->seek_to_begin();

      if (true)
      {
         m = FreeImage_OpenMultiBitmapFromHandle(format, &io, (::file::stream_buffer *)pfile.m_p, 0);
         int c = FreeImage_GetPageCount(m);

         for (index i = 0; i < c; i++)
         {

            ::visual::dib_sp::pointer * p = canew(::visual::dib_sp::pointer);

            pdiba->add(p);

            p->m_dib.alloc(papp->allocer());


            FIBITMAP * pfi = FreeImage_LockPage(m, i);



            if (pfi != NULL)
            {

               int w = FreeImage_GetWidth(pfi);

               int h = FreeImage_GetHeight(pfi);

               FITAG * ptag;

               if (i == 0)
               {

                  if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "LogicalWidth", &ptag))
                  {

                     if (FreeImage_GetTagType(ptag) == FIDT_SHORT)
                     {
                        
                        pdiba->m_size.cx = *((short *)FreeImage_GetTagValue(ptag));

                     }

                  }

                  if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "LogicalHeight", &ptag))
                  {

                     if (FreeImage_GetTagType(ptag) == FIDT_SHORT)
                     {

                        pdiba->m_size.cy = *((short *)FreeImage_GetTagValue(ptag));

                     }

                  }
                  if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "GlobalPalette", &ptag))
                  {

                     if (FreeImage_GetTagType(ptag) == FIDT_PALETTE)
                     {

                        cra_from_quada(pdiba->m_cra, (RGBQUAD *)FreeImage_GetTagValue(ptag), FreeImage_GetTagCount(ptag));

                     }

                  }

                  if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "Loop", &ptag))
                  {

                     if (FreeImage_GetTagType(ptag) == FIDT_LONG)
                     {

                        pdiba->m_uiLoopCount = *((long *)FreeImage_GetTagValue(ptag));

                     }

                  }

                  dibCompose->create(pdiba->m_size + size(10, 10));


                  dibCompose->Fill(0);


               }
               p->m_rect.left = 0;
               if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "FrameLeft", &ptag))
               {

                  if (FreeImage_GetTagType(ptag) == FIDT_SHORT)
                  {

                     p->m_rect.left = *((short *)FreeImage_GetTagValue(ptag));

                  }

               }
               p->m_rect.right = p->m_rect.left + w;
               p->m_rect.top = 0;
               if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "FrameTop", &ptag))
               {

                  if (FreeImage_GetTagType(ptag) == FIDT_SHORT)
                  {

                     p->m_rect.top = *((short *)FreeImage_GetTagValue(ptag));

                  }

               }
               p->m_rect.bottom = p->m_rect.top + h;
               if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "NoLocalPalette", &ptag))
               {

                  if (FreeImage_GetTagType(ptag) == FIDT_BYTE)
                  {

                     p->m_bLocalPalette = *((byte *)FreeImage_GetTagValue(ptag)) == 0;

                  }

               }
               p->m_edisposal = ::visual::dib_sp::pointer::disposal_undefined;
               if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "DisposalMethod", &ptag))
               {

                  if (FreeImage_GetTagType(ptag) == FIDT_BYTE)
                  {
                     switch (*((byte *)FreeImage_GetTagValue(ptag)))
                     {
                     case 0:
                        p->m_edisposal = ::visual::dib_sp::pointer::disposal_undefined;
                        break;
                     case 1:
                        p->m_edisposal = ::visual::dib_sp::pointer::disposal_none;
                        break;
                     case 2:
                        p->m_edisposal = ::visual::dib_sp::pointer::disposal_background;
                        break;
                     case 3:
                        p->m_edisposal = ::visual::dib_sp::pointer::disposal_previous;
                        break;
                     default:
                        p->m_edisposal = ::visual::dib_sp::pointer::disposal_undefined;
                        break;
                     }
                     
 
                  }

               }

               if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "FrameTime", &ptag))
               {

                  if (FreeImage_GetTagType(ptag) == FIDT_LONG)
                  {

                     p->m_dwTime = *((long *)FreeImage_GetTagValue(ptag));

                  }

               }

               //::draw2d::graphics_sp spgraphics(papp->allocer());

               //spgraphics->CreateCompatibleDC(NULL);

               if(!freeimage_load_diba_frame(dibCompose, pdiba, i, pfi, papp))
               {
                  output_debug_string("failed to load page image");
               }

               pdiba->m_dwTotal += p->m_dwTime;


                  //try
                  //{
                  //   FreeImage_UnlockPage(m, pfi, false);

                  //}
                  //catch (...)
                  //{


                  //}

            }


            




         }
      }
   }
   catch (...)
   {
      return false;

   }

   return true;
}


bool freeimage_load_diba_frame(::draw2d::dib * pdibCompose, ::visual::dib_sp::array * pdiba, int iFrame, FIBITMAP * pfi, ::aura::application * papp)
{

   if (pfi == NULL)
      return false;

   if (papp == NULL)
      papp = get_thread_app();

   ::visual::dib_sp::pointer * p = pdiba->element_at(iFrame);

   BITMAPINFO * pbi = NULL;

   void * pdata = NULL;

   pbi = FreeImage_GetInfo(pfi);

   pdata = FreeImage_GetBits(pfi);

   int w = FreeImage_GetWidth(pfi);
   int h = FreeImage_GetHeight(pfi);

   if (!p->m_dib->create(w, h))
      return false;

   int transparentIndex = FreeImage_GetTransparentIndex(pfi);

   bool bIsTransparent = FreeImage_IsTransparent(pfi) != 0;

   if (!bIsTransparent)
   {

      transparentIndex = -1;

   }

   RGBQUAD quad;

   if (FreeImage_GetBackgroundColor(pfi, &quad))
   {

      output_debug_string("has background color");

   }

   int iScan = FreeImage_GetPitch(pfi);

   if (FreeImage_GetBPP(pfi) == 8)
   {

      if (p->m_bLocalPalette && pbi->bmiHeader.biClrUsed > 0)
      {

         array < COLORREF > cra;

         cra_from_quada(cra, pbi->bmiColors, pbi->bmiHeader.biClrUsed);

         if (!gif_load_frame(pdibCompose, pdiba, p, iFrame, (byte *)pdata, iScan , cra, transparentIndex))
         {

            return false;

         }

      }
      else
      {

         if (!gif_load_frame(pdibCompose, pdiba, p, iFrame, (byte *)pdata, iScan, pdiba->m_cra, transparentIndex))
         {

            return false;

         }

      }

   }
   else
   {

      return false;

   }


//   pdib->map();
//
//   int stride = pbi->bmiHeader.biWidth * sizeof(COLORREF);
//
//#if  defined(VSNORD)
//
//   for (index y = 0; y < pdib->m_size.cy; y++)
//   {
//
//      byte * pbDst = ((byte *)pdib->m_pcolorref) + ((pdib->m_size.cy - y - 1) * pdib->m_iScan);
//
//      byte * pbSrc = (byte *)pdata + (y * stride);
//
//      for (index x = 0; x < pdib->m_size.cx; x++)
//      {
//
//         pbDst[0] = pbSrc[2];
//
//         pbDst[1] = pbSrc[1];
//
//         pbDst[2] = pbSrc[0];
//
//         pbDst[3] = pbSrc[3];
//
//         pbDst += 4;
//
//         pbSrc += 4;
//
//      }
//
//   }
//
//#elif defined(APPLEOS)
//
//   byte * pbDst = (byte *)pdib->m_pcolorref;
//
//   byte * pbSrc = (byte *)pdata;
//
//   ::count c = (count)pdib->area();
//
//   while (c-- > 0)
//   {
//
//      pbDst[0] = pbSrc[2];
//
//      pbDst[1] = pbSrc[1];
//
//      pbDst[2] = pbSrc[0];
//
//      pbDst[3] = pbSrc[3];
//
//      pbDst += 4;
//
//      pbSrc += 4;
//
//   }
//
//   /*
//
//   byte * pbDst;
//
//   byte * pbSrc;
//
//   for(int i = 0; i < pdib->m_size.cy; i++)
//   {
//
//   pbDst = &((byte *) pdib->m_pcolorref)[pdib->m_iScan * (pdib->m_size.cy - i - 1)];
//
//   pbSrc = &((byte *) pdata)[pbi->bmiHeader.biWidth * sizeof(COLORREF) * i];
//
//   for(int j = 0; j < pdib->m_size.cx; j++)
//   {
//
//   pbDst[0] = pbSrc[2];
//
//   pbDst[1] = pbSrc[1];
//
//   pbDst[2] = pbSrc[0];
//
//   pbDst[3] = pbSrc[3];
//
//   pbDst += 4;
//
//   pbSrc += 4;
//
//   }
//
//   }*/
//
//#else
//   for (int i = 0; i < pdib->m_size.cy; i++)
//   {
//
//      memcpy(
//         &((byte *)pdib->m_pcolorref)[pdib->m_iScan * (pdib->m_size.cy - i - 1)],
//         &((byte *)pdata)[pbi->bmiHeader.biWidth * sizeof(COLORREF) * i],
//         pdib->m_iScan);
//
//   }
//#endif
//
//#if defined(LINUX) || defined(VSNORD)
//   pdib->mult_alpha();
//#endif

   return true;


}




void cra_from_quada(array < COLORREF > & cra, RGBQUAD * pquad, int iCount)
{

   cra.set_size(iCount);

   for (index i = 0; i < iCount; i++)
   {

      cra[i] = ARGB(255, pquad[i].rgbBlue, pquad[i].rgbGreen, pquad[i].rgbRed);

      if (cra[i] == ARGB(255, 255, 255, 255))
      {

         output_debug_string("completely white");

      }

   }

}