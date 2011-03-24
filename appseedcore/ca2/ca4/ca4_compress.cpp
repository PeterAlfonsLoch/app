#include "StdAfx.h"
#include <io.h>  
#include <wchar.h>  
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <share.h> 

namespace ca4
{
   bool compress::ungz(ex1::output_stream & ostreamUncompressed, const char * lpcszGzFileCompressed)
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
      while((uncomprLen = gzread(file, memory, memory.get_size())) > 0)
      {
         ostreamUncompressed.write(memory, uncomprLen);
      }
      gzclose(file);
      return true;
   }


   bool compress::gz(ex1::output_stream & ostreamCompressed, const char * lpcszUncompressed)
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
      while((uncomprLen = fread(memory, 1, memory.get_size(), fileUn)) > 0)
      {
         gz.write(memory, uncomprLen);
      }
      fclose(fileUn);
      gz.finish();
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

   bool compress::unbz(::ex1::output_stream & ostreamUncompressed, const char * lpcszBzFileCompressed)
   {
      int fileUn = _wopen(gen::international::utf8_to_unicode(lpcszBzFileCompressed), _O_BINARY | _O_RDONLY);
      if (fileUn == -1)
      {
         TRACE("unbz wopen error %s", lpcszBzFileCompressed);
         return false;
      }
      BZFILE * file = BZ2_bzdopen(fileUn, "rb");
      if (file == NULL)
      {
         TRACE("unbz bzopen error %s", lpcszBzFileCompressed);
         return false;
      }
      primitive::memory memory;
      memory.allocate(1024 * 16 * 1024);
      int uncomprLen;
      while((uncomprLen = BZ2_bzread(file, memory, memory.get_size())) > 0)
      {
         ostreamUncompressed.write(memory, uncomprLen);
      }
      BZ2_bzclose(file);
      return true;
   }

   bool compress::bz(ex1::output_stream & ostreamCompressed, const char * lpcszUncompressed)
   {
      FILE * fileUn = _wfopen(gen::international::utf8_to_unicode(lpcszUncompressed), L"rb");
      if (fileUn == NULL)
      {
         int err;
         _get_errno(&err);
         fprintf(stderr, "gz fopen error %d %s", err, lpcszUncompressed);
         return false;
      }
      bzip bz(ostreamCompressed);
      class primitive::memory memory;
      memory.allocate(1024 * 256);
      int uncomprLen;
      while((uncomprLen = fread(memory, 1, memory.get_size(), fileUn)) > 0)
      {
         bz.write(memory, uncomprLen);
      }
      fclose(fileUn);
      bz.finish();
      return true;
   }

   bool compress::unbz(const char * lpcszUncompressed, const char * lpcszGzFileCompressed)
   {
      return System.file().output(lpcszUncompressed, this, &compress::unbz, lpcszGzFileCompressed);
   }

   bool compress::bz(const char * lpcszGzFileCompressed, const char * lpcszUncompressed)
   {
      return System.file().output(lpcszGzFileCompressed, this, &compress::bz, lpcszUncompressed);
   }

   bool compress::_compress(class primitive::memory & memory, void * pdata, unsigned long ulSize)
   {
      memory.allocate(compressBound(ulSize) * 2);
      unsigned long ulDestSize = memory.GetStorageSize();
      int i = ::zlib_compress(memory.GetAllocation(), &ulDestSize, (BYTE *) pdata, ulSize);
      memory.allocate(ulDestSize);
      return i == Z_OK;
   }
   
   bool compress::_uncompress(primitive::memory & memoryUncompressed, primitive::memory & memoryCompressed, unsigned long ulSizeUncompressed)
   {
      memoryUncompressed.allocate(ulSizeUncompressed);
      int i = ::uncompress(memoryUncompressed.GetAllocation(), &ulSizeUncompressed, memoryCompressed.GetAllocation(), memoryCompressed.GetStorageSize());
      return i == Z_OK;
   }


} // namespace ca4