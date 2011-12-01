#include "StdAfx.h"
#include <io.h>
#include <wchar.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <share.h>

namespace ca4
{
   bool compress::ungz(ex1::writer & ostreamUncompressed, const char * lpcszGzFileCompressed)
   {
      int fileUn = _wopen(gen::international::utf8_to_unicode(lpcszGzFileCompressed), _O_BINARY | _O_RDONLY);
      if (fileUn == -1)
      {
         TRACE("ungz wopen error %s", lpcszGzFileCompressed);
         return false;
      }
      gzFile file = gzdopen(fileUn, "rb");
      if (file == NULL)
      {
         TRACE("ungz gzopen error %s", lpcszGzFileCompressed);
         return false;
      }
      class primitive::memory memory;
      memory.allocate(1024 * 256);
      int uncomprLen;
      while((uncomprLen = gzread(file, memory, (unsigned int) memory.get_size())) > 0)
      {
         ostreamUncompressed.write(memory, uncomprLen);
      }
      gzclose(file);
      return true;
   }


   bool compress::gz(ex1::writer & ostreamCompressed, const char * lpcszUncompressed)
   {
      string str(lpcszUncompressed);
      FILE * fileUn = _wfopen(gen::international::utf8_to_unicode(lpcszUncompressed), L"rb");
      if (fileUn == NULL)
      {
         int err;
         _get_errno(&err);
         fprintf(stderr, "gz fopen error %d %s", err, lpcszUncompressed);
         return false;
      }
      gzip gz(ostreamCompressed);
      class primitive::memory memory;
      memory.allocate(1024 * 256);
      int uncomprLen;
      while((uncomprLen = fread(memory, 1, (size_t) memory.get_size(), fileUn)) > 0)
      {
         gz.write(memory, uncomprLen);
      }
      fclose(fileUn);
      gz.finish();
      return true;
   }

   bool compress::null(ex1::writer & ostream, ex1::reader & istream)
   {
      class primitive::memory memory;
      memory.allocate(1024 * 256);
      int uiRead;
      while((uiRead = istream.read(memory, memory.get_size())) > 0)
      {
         ostream.write(memory, uiRead);
      }
      return true;
   }

   bool compress::ungz(const char * lpcszUncompressed, const char * lpcszGzFileCompressed)
   {
      return System.file().output(lpcszUncompressed, this, &compress::ungz, lpcszGzFileCompressed);
   }

   bool compress::gz(const char * lpcszGzFileCompressed, const char * lpcszUncompressed)
   {
      return System.file().output(lpcszGzFileCompressed, this, &compress::gz, lpcszUncompressed);
   }

   bool compress::unbz(::ex1::writer & ostreamUncompressed, const char * lpcszBzFileCompressed)
   {
      BZFILE * file = BZ2_bzopen(lpcszBzFileCompressed, "rb");
      if (file == NULL)
      {
         TRACE("unbz bzopen error %s", lpcszBzFileCompressed);
         return false;
      }
      primitive::memory memory;
      memory.allocate(1024 * 16 * 1024);
      int uncomprLen;
      while((uncomprLen = BZ2_bzread(file, memory, (int) memory.get_size())) > 0)
      {
         ostreamUncompressed.write(memory, uncomprLen);
      }
      BZ2_bzclose(file);
      return true;
   }

   bool compress::bz(ex1::writer & ostreamBzFileCompressed, const char * lpcszUncompressed)
   {
      ::ex1::filesp file = System.get_file(lpcszUncompressed, ex1::file::mode_read | ex1::file::type_binary);
      if(file.is_null())
      {
         return false;
      }
      return bz_stream(ostreamBzFileCompressed, file);
   }

   bool compress::bz_stream(ex1::writer & ostreamBzFileCompressed, ex1::reader & istreamFileUncompressed)
   {
      bzip bz(ostreamBzFileCompressed);
      class primitive::memory memory;
      memory.allocate(1024 * 256);
      ::primitive::memory_size uncomprLen;
      while((uncomprLen = istreamFileUncompressed.read(memory, memory.get_size())) > 0)
      {
         bz.write(memory, uncomprLen);
      }
      bz.finish();
      return true;
   }

   bool compress::unbz(const char * lpcszUncompressed, const char * lpcszGzFileCompressed)
   {
      return System.file().output(lpcszUncompressed, this, &compress::unbz, lpcszGzFileCompressed);
   }

   bool compress::bz(const char * lpcszGzFileCompressed, const char * lpcszUncompressed)
   {
      return System.file().output(lpcszGzFileCompressed, this, &compress::bz_stream, lpcszUncompressed);
   }

   bool compress::_compress(class primitive::memory & memory, void * pdata, unsigned long ulSize)
   {
      memory.allocate(compressBound(ulSize) * 2);
      unsigned long ulDestSize = (unsigned long) memory.get_size();
      int i = ::zlib_compress(memory.get_data(), &ulDestSize, (BYTE *) pdata, ulSize);
      memory.allocate(ulDestSize);
      return i == Z_OK;
   }

   bool compress::_uncompress(primitive::memory & memoryUncompressed, primitive::memory & memoryCompressed, unsigned long ulSizeUncompressed)
   {
      memoryUncompressed.allocate(ulSizeUncompressed);
      int i = ::uncompress(memoryUncompressed.get_data(), &ulSizeUncompressed, memoryCompressed.get_data(), (uLong) memoryCompressed.get_size());
      return i == Z_OK;
   }


   void compress::extract_all(const char * pszFile, ::ca::application * papp)
   {
      string strDir = pszFile;
      gen::str::ends_eat_ci(strDir, ".zip");
      App(papp).file().copy(strDir, pszFile, false);
   }

   void compress::zip(const char * pszZip, const char * psz)
   {
      zip::InFile infile(get_app());

      ::ex1::file_exception_sp fe(get_app());

      if(!infile.zip_open(pszZip, 0, &fe))
      {
         throw "Could not open zip file";
         return;
      }

      if(System.dir().is(psz))
      {
         stringa straPath;
         stringa straRelative;
         string strPath;
         ::ex1::filesp file;
         System.dir().rls(psz, &straPath, NULL, &straRelative);
         for(int i = 0; i < straPath.get_size(); i++)
         {
            strPath = straPath[i];
            if(!System.dir().is(strPath))
            {
               infile.add_file(psz, straRelative[i]);

            }
         }
      }

   }

   void compress::zip(const char * psz)
   {
   }

} // namespace ca4
