#include "framework.h"
#ifndef METROWIN
#ifdef WINDOWS
#define min MIN
#define max MAX
#undef new
#include <gdiplus.h>
#undef min
#undef max
int GetEncoderClsid(const WCHAR* format,CLSID* pClsid);
#elif defined(LINUX) || defined(APPLEOS)
#include "freeimage/Source/FreeImage.h"
#endif
#endif


//#include "ft2build.h"


//#include FT_FREETYPE_H


namespace visual
{


   dib_sp::dib_sp()
   {
   }

   dib_sp::dib_sp(const allocatorsp & allocer) :
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

      bool bOk = false;

#ifdef BASE_FREEIMAGE
      bool b8 = false;
      bool b24 = false;
      int iFreeImageSave = 0;
      FREE_IMAGE_FORMAT eformat = (FREE_IMAGE_FORMAT) 0;
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
         if(psaveimage->m_iQuality > 80)
         {
            iFreeImageSave |= JPEG_QUALITYSUPERB;
         }
         else if(psaveimage->m_iQuality > 67)
         {
            iFreeImageSave |= JPEG_QUALITYGOOD;
         }
         else if(psaveimage->m_iQuality > 33)
         {
            iFreeImageSave |= JPEG_QUALITYNORMAL;
         }
         else if(psaveimage->m_iQuality > 15)
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

      bOk = FreeImage_SaveToMemory(eformat,pfi8,pfm1,iFreeImageSave) != FALSE;

      BYTE * pbData = NULL;
      DWORD dwSize = 0;
      if(bOk)
         bOk = FreeImage_AcquireMemory(pfm1,&pbData,&dwSize) != FALSE;
      if(bOk)
      {
         try
         {
            pfile->write(pbData,dwSize);
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


#else
      IStream* pstream = SHCreateMemStream(NULL, NULL);

      Gdiplus::EncoderParameters encoderParameters;

      CLSID encoderClsid;
      bool b8 = false;
      bool b24 = false;
      int iFreeImageSave = 0;
      ULONG quality;
      switch(psaveimage->m_eformat)
      {
      case ::visual::image::format_png:
         GetEncoderClsid(L"image/png",&encoderClsid);
         break;
      case ::visual::image::format_bmp:
         GetEncoderClsid(L"image/bmp",&encoderClsid);
         break;
      case ::visual::image::format_gif:
         b8 = true;
         GetEncoderClsid(L"image/gif",&encoderClsid);
         break;
      case ::visual::image::format_jpeg:
         b24 = true;
         GetEncoderClsid(L"image/jpeg",&encoderClsid);
         encoderParameters.Count = 1;
         encoderParameters.Parameter[0].Guid = Gdiplus::EncoderQuality;
         encoderParameters.Parameter[0].Type = Gdiplus::EncoderParameterValueTypeLong;
         encoderParameters.Parameter[0].NumberOfValues = 1;
         quality = psaveimage->m_iQuality;
         encoderParameters.Parameter[0].Value = &quality;
         break;
      default:
         return false;
      }

      Gdiplus::Bitmap * pbitmap = new Gdiplus::Bitmap(m_p->m_size.cx,m_p->m_size.cy,m_p->m_iScan,PixelFormat32bppARGB,(BYTE *)m_p->m_pcolorref);

      if(psaveimage->m_eformat == ::visual::image::format_jpeg)
      {
         pbitmap->Save(pstream,&encoderClsid,&encoderParameters);
      }
      else
      {
         pbitmap->Save(pstream,&encoderClsid,NULL);
      }

      ::primitive::memory mem;
      STATSTG stg;
      ZERO(stg);
      pstream->Stat(&stg,STATFLAG_NONAME);
      mem.allocate(stg.cbSize.QuadPart);
      LARGE_INTEGER l;
      l.QuadPart = 0;
      pstream->Seek(l,STREAM_SEEK_SET,NULL);

      ULONG ulPos = 0;
      ULONG ulRead;
      ULONG ul;
      do
      {

         ulRead = 0;

         ul = stg.cbSize.QuadPart - ulPos;

         pstream->Read(&mem.get_data()[ulPos],ul,&ulRead);

         ulPos+=ulRead;

      } while(ulRead > 0 && stg.cbSize.QuadPart - ulPos > 0);

      pfile->write(mem.get_data(),ulPos);

      delete pbitmap;

      pstream->Release();



#endif

      return bOk != FALSE;

#endif

   }




   save_image::save_image()
   {
      m_eformat = ::visual::image::format_png;
      m_iQuality = 100;
   }


#ifdef BASE_FREEIMAGE
   bool dib_sp::from(class draw2d::graphics * pgraphics,struct FIBITMAP * pfi,bool bUnload)
   {

      return Sys(m_p->m_pauraapp).visual().imaging().from(m_p,pgraphics,pfi,bUnload);

   }
#endif

} // namespace visual


#if 0


CLASS_DECL_BASE void draw_freetype_bitmap(::draw2d::dib * m_p,int32_t dx,int32_t dy,void * pftbitmap,int xParam,int yParam)
{

   FT_Bitmap * bitmap = (FT_Bitmap *) pftbitmap;
   FT_Int x = (FT_Int) xParam;
   FT_Int y = (FT_Int) yParam;

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


CLASS_DECL_BASE void draw_freetype_bitmap(::draw2d::dib * m_p,int32_t dx,int32_t dy,void * pftbitmap,int xParam,int yParam,byte aParam,byte r,byte g,byte b)
{

   FT_Bitmap * bitmap = (FT_Bitmap *)pftbitmap;
   FT_Int x = (FT_Int)xParam;
   FT_Int y = (FT_Int)yParam;

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

         if(a > 0)
         {

            *((COLORREF *)&((byte *)m_p->get_data())[(dy + j) * m_p->m_iScan + (dx + i) * 4]) = ARGB(a * aParam / 255,r,g,b);

         }
         else
         {

            *((COLORREF *)&((byte *)m_p->get_data())[(dy + j) * m_p->m_iScan + (dx + i) * 4]) = 0;

         }

      }
   }

}

#endif

#ifdef WINDOWSEX


int GetEncoderClsid(const WCHAR* format,CLSID* pClsid)
{
   UINT  num = 0;          // number of image encoders
   UINT  size = 0;         // size of the image encoder array in bytes

   Gdiplus::ImageCodecInfo* pImageCodecInfo = NULL;

   Gdiplus::GetImageEncodersSize(&num,&size);
   if(size == 0)
      return -1;  // Failure

   pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));
   if(pImageCodecInfo == NULL)
      return -1;  // Failure

   GetImageEncoders(num,size,pImageCodecInfo);

   for(UINT j = 0; j < num; ++j)
   {
      if(wcscmp(pImageCodecInfo[j].MimeType,format) == 0)
      {
         *pClsid = pImageCodecInfo[j].Clsid;
         free(pImageCodecInfo);
         return j;  // Success
      }
   }

   free(pImageCodecInfo);
   return -1;  // Failure
}


#endif


