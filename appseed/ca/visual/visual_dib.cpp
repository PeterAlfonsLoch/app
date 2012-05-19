#include "framework.h"
#include "include/FreeImage.h"


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
               ex1::byte_stream stream = Application.get_byte_stream(strFile, ::ex1::file::mode_read | ::ex1::file::shareDenyWrite | ::ex1::file::type_binary);
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
         ex1::file_exception_sp spfe(get_app());
         if(!read_from_file(Application.get_file(varFile, ::ex1::file::mode_read | ::ex1::file::shareDenyWrite | ::ex1::file::type_binary, &spfe)))
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
            ex1::byte_stream stream = Application.get_byte_stream(strFile, ::ex1::file::mode_create | ::ex1::file::mode_write | ::ex1::file::type_binary | ::ex1::file::defer_create_directory);
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

   bool dib_sp::read_from_file(::ex1::file * pfile)
   {
      FIBITMAP * pfi = System.imaging().LoadImageFile(pfile);
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
      ::ex1::filesp spfile;
      spfile = Application.get_file(varFile, ::ex1::file::mode_create | ::ex1::file::mode_write | ::ex1::file::type_binary);
      if(spfile.is_null())
         return false;
      return write_to_file(spfile, psaveimage);
   }

   bool dib_sp::write_to_file(::ex1::file * pfile, save_image * psaveimage)
   {
      save_image saveimageDefault;
      if(psaveimage == NULL)
         psaveimage = &saveimageDefault;

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
      FIBITMAP * pfi7 = System.imaging().HBITMAPtoFI(m_p->get_bitmap());
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
      
      bool bOk = FreeImage_SaveToMemory(eformat, pfi8, pfm1 , PNG_DEFAULT);

      BYTE * pbData;
      DWORD dwSize;
      if(bOk)
         bOk = FreeImage_AcquireMemory(pfm1, &pbData, &dwSize);
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
   }


   save_image::save_image()
   {
      m_eformat = ::visual::image::format_png;
   }

} // namespace visual