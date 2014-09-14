#include "framework.h"
#ifndef METROWIN
#include "freeimage/Source/FreeImage.h"
#endif


#include "axis/freetype/include/ft2build.h"


#include FT_FREETYPE_H


CLASS_DECL_BASE void draw_bitmap(::draw2d::dib * pdib,int32_t dx,int32_t dy,FT_Bitmap * bitmap,FT_Int x,FT_Int y);


namespace visual
{


   dib_sp::dib_sp()
   {
   }

   dib_sp::dib_sp(allocatorsp allocer) :
      ::draw2d::dib_sp(allocer)
   {
   }

   dib_sp::~dib_sp()
   {
   }



   bool dib_sp::load_from_file(var varFile, bool bCache)
   {

      return Sys(m_p->m_pauraapp).visual().imaging().load_from_file(m_p, varFile, bCache, m_p->m_pauraapp);

   }


   bool dib_sp::load_from_matter(const char * pszMatter)
   {

      return Sys(m_p->m_pauraapp).visual().imaging().load_from_file(m_p, Sess(m_p->m_pauraapp).dir().matter(pszMatter), true, m_p->m_pauraapp);

   }


   bool dib_sp::read_from_file(::file::buffer_sp spfile)
   {

      return Sys(m_p->m_pauraapp).visual().imaging().read_from_file(m_p, spfile, m_p->m_pauraapp);

   }


   bool dib_sp::save_to_file(var varFile, save_image * psaveimage)
   {
      ::file::buffer_sp spfile;
      spfile = Sess(m_p->m_pauraapp).file().get_file(varFile, ::file::mode_create | ::file::mode_write | ::file::type_binary | ::file::defer_create_directory);
      if(spfile.is_null())
         return false;
      return write_to_file(spfile, psaveimage);
   }

   bool dib_sp::write_to_file(::file::buffer_sp  pfile, save_image * psaveimage)
   {
      save_image saveimageDefault;
      if(psaveimage == NULL)
         psaveimage = &saveimageDefault;

#ifdef METROWIN

      throw todo(m_p->m_pauraapp);

#else

      FREE_IMAGE_FORMAT eformat;
      bool b8 = false;
      bool b24 = false;
      int iFreeImageSave = 0;
      switch(psaveimage->m_eformat)
      {
      case ::visual::image::format_png:
         eformat = FIF_PNG;
         break;
      case ::visual::image::format_bmp:
         eformat = FIF_BMP;
         break;
      case ::visual::image::format_gif:
         b8 = true;
         eformat = FIF_GIF;
         break;
      case ::visual::image::format_jpeg:
         b24 = true;
         eformat = FIF_JPEG;
         if (psaveimage->m_iQuality > 80)
         {
            iFreeImageSave |= JPEG_QUALITYSUPERB;
         }
         else if (psaveimage->m_iQuality > 67)
         {
            iFreeImageSave |= JPEG_QUALITYGOOD;
         }
         else if (psaveimage->m_iQuality > 33)
         {
            iFreeImageSave |= JPEG_QUALITYNORMAL;
         }
         else if (psaveimage->m_iQuality > 15)
         {
            iFreeImageSave |= JPEG_QUALITYAVERAGE;
         }
         else
         {
            iFreeImageSave |= JPEG_QUALITYBAD;
         }
         break;
      default:
         return false;
      }




      FIMEMORY * pfm1 = FreeImage_OpenMemory();
      FIBITMAP * pfi7 = Sys(m_p->m_pauraapp).visual().imaging().HBITMAPtoFI(m_p->get_bitmap());
      FIBITMAP * pfi8 = NULL;
      bool bConv;
      if(b8)
      {
         pfi8 = FreeImage_ConvertTo8Bits(pfi7);
         bConv = true;
      }
      else if(b24)
      {
         pfi8 = FreeImage_ConvertTo24Bits(pfi7);
         bConv = true;
      }
      else
      {
         pfi8 = pfi7;
         bConv = false;
      }

      bool bOk = FreeImage_SaveToMemory(eformat, pfi8, pfm1 , iFreeImageSave) != FALSE;

      BYTE * pbData = NULL;
      DWORD dwSize = 0;
      if(bOk)
         bOk = FreeImage_AcquireMemory(pfm1, &pbData, &dwSize) != FALSE;
      if(bOk)
      {
         try
         {
            pfile->write(pbData, dwSize);
         }
         catch(...)
         {
            bOk = false;
         }
      }

      FreeImage_CloseMemory(pfm1);
      if(bConv)
      {
         FreeImage_Unload(pfi8);
      }
      FreeImage_Unload(pfi7);

      return bOk != FALSE;

#endif

   }


   bool dib_sp::from(class draw2d::graphics * pgraphics, struct FIBITMAP * pfi, bool bUnload)
   {

      return Sys(m_p->m_pauraapp).visual().imaging().from(m_p, pgraphics, pfi, bUnload);

   }


   save_image::save_image()
   {
      m_eformat = ::visual::image::format_png;
      m_iQuality = 100;
   }




} // namespace visual


CLASS_DECL_BASE void draw_bitmap(::draw2d::dib * m_p, int32_t dx,int32_t dy,FT_Bitmap * bitmap,FT_Int x,FT_Int y)
{

   FT_Int  i,j,p,q;
   FT_Int  x_max = x + bitmap->width;
   FT_Int  y_max = y + bitmap->rows;

   m_p->map();

   for(i = x,p = 0; i < x_max; i++,p++)
   {
      for(j = y,q = 0; j < y_max; j++,q++)
      {
         if(i < 0 || j < 0 || i >= m_p->m_size.cx || j >= m_p->m_size.cy)
            continue;

         int32_t a = bitmap->buffer[q * bitmap->width + p];

         *((COLORREF *)&((byte *)m_p->get_data())[(dy + j) * m_p->m_iScan + (dx + i) * 4]) = ARGB(a,0,0,0);

      }
   }

}
