#include "framework.h"
#ifndef METROWIN
#include "include/freeimage.h"
#endif

namespace visual
{

   dib_sp::dib_sp()
   {
   }

   dib_sp::dib_sp(::ca::application * papp) :
      ::ca::dib_sp(papp)
   {
   }

   dib_sp::~dib_sp()
   {
   }



   bool dib_sp::load_from_file(var varFile)
   {

      // image cache load
      // cache of decompression time
      string strFile;
      if(varFile.get_type() == var::type_string)
      //if(false)
      {
         strFile = varFile;
         strFile.replace(":/", "\\_");
         strFile.replace(":\\", "\\_\\");
         strFile.replace("/", "\\");
         strFile = System.dir().time("cache", strFile);
         strFile += ".dib";
         if(Application.file().exists(strFile))
         {
            try
            {
               gen::byte_stream stream = Application.file().get_byte_stream(strFile, ::gen::file::mode_read | ::gen::file::shareDenyWrite | ::gen::file::type_binary);
               m_p->read(stream);
               return true;
            }
            catch(...)
            {
            }
         }
      }


      try
      {

         if(!read_from_file(Application.file().get_file(varFile, ::gen::file::mode_read | ::gen::file::shareDenyWrite | ::gen::file::type_binary)))
            return false;

      }
      catch(...)
      {

         return false;

      }


      // image cache write
      if(strFile.has_char())
      {
         try
         {
            gen::byte_stream stream = Application.file().get_byte_stream(strFile, ::gen::file::mode_create | ::gen::file::mode_write | ::gen::file::type_binary | ::gen::file::defer_create_directory);
            m_p->write(stream);
         }
         catch(...)
         {
         }
      }
      return true;
   }

   bool dib_sp::load_from_matter(const char * pszMatter)
   {
      return load_from_file(Application.dir().matter(pszMatter));
   }

   bool dib_sp::read_from_file(::gen::file * pfile)
   {
      FIBITMAP * pfi = Application.visual().imaging().LoadImageFile(pfile);
      if(pfi == NULL)
         return false;
      ::ca::graphics_sp spgraphics(get_app());
      spgraphics->CreateCompatibleDC(NULL);
      if(!m_p->from(spgraphics, pfi, true))
         return false;
      return true;
   }

   bool dib_sp::save_to_file(var varFile, save_image * psaveimage)
   {
      ::gen::filesp spfile;
      spfile = Application.file().get_file(varFile, ::gen::file::mode_create | ::gen::file::mode_write | ::gen::file::type_binary);
      if(spfile.is_null())
         return false;
      return write_to_file(spfile, psaveimage);
   }

   bool dib_sp::write_to_file(::gen::file * pfile, save_image * psaveimage)
   {
      save_image saveimageDefault;
      if(psaveimage == NULL)
         psaveimage = &saveimageDefault;

#ifdef METROWIN

      throw todo(get_app());

#else

      FREE_IMAGE_FORMAT eformat;
      bool b8 = false;
      bool b24 = false;
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
         break;
      default:
         return false;
      }




      FIMEMORY * pfm1 = FreeImage_OpenMemory();
      FIBITMAP * pfi7 = Application.visual().imaging().HBITMAPtoFI(m_p->get_bitmap());
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

      bool bOk = FreeImage_SaveToMemory(eformat, pfi8, pfm1 , PNG_DEFAULT) != FALSE;

      BYTE * pbData = NULL;
      DWORD dwSize;
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


   save_image::save_image()
   {
      m_eformat = ::visual::image::format_png;
   }

} // namespace visual
