//#include"framework.h"
//#include"axis/compress/compress.h"
#include "compress_gz.h"
#include "compress_bz.h"


namespace axis
{


   bool compress::ungz(::file::ostream & ostreamUncompressed, const ::file::path & lpcszGzFileCompressed)
   {

      return Application.file().output(ostreamUncompressed, this, &::axis::compress::ungz, lpcszGzFileCompressed);
      
   }


   bool compress::ungz(::file::ostream & ostreamUncompressed, ::file::istream & istreamGzFileCompressed)
   {

      bool done = false;

      int32_t status;

      class memory memIn;
      memIn.allocate(1024 * 8);

      int64_t uiRead = istreamGzFileCompressed.read(memIn.get_data(), memIn.get_size());

      z_stream zstream;
      ZERO(zstream);
      zstream.next_in = (byte *)memIn.get_data();
      zstream.avail_in = (uint32_t)uiRead;
      zstream.total_out = 0;
      zstream.zalloc = Z_NULL;
      zstream.zfree = Z_NULL;

      class memory memory;
      memory.allocate(1024 * 256);
      ASSERT(memory.get_size() <= UINT_MAX);

      // inflateInit2 knows how to deal with gzip format
      if (inflateInit(&zstream) != Z_OK)
      {
         return false;
      }

      while (!done)
      {

         zstream.next_out = memory.get_data();
         zstream.avail_out = (uint32_t)memory.get_size();

         while (zstream.avail_out == 0)
         {

            // Inflate another chunk.
            status = inflate(&zstream, Z_NO_FLUSH);

            ostreamUncompressed.write(memory.get_data(), zstream.total_out);

            if (status == Z_STREAM_END)
            {

               done = true;

            }
            else if (status != Z_OK)
            {

               break;

            }

         }

         uiRead = istreamGzFileCompressed.read(memIn.get_data(), memIn.get_size());

         zstream.next_in = (byte *)memIn.get_data();

         zstream.avail_in = (uint32_t)uiRead;

         zstream.total_out = 0;


      }

      if (inflateEnd(&zstream) != Z_OK || !done)
      {
         
         return true;

      }

      return true;

   }




   bool compress::ungz(::file::file * pfileOut, ::file::file * pfileIn)
   {

      return Application.file().output(pfileOut, this, &::axis::compress::ungz, pfileIn);

   }


   bool compress::uncompress(memory & memory)
   {

      ::memory dest;

      int iRate = 1;
      while(true)
      {

         dest.allocate(memory.get_size() * 10);

         uLong l = dest.get_size();

         int i = ::uncompress(dest.get_data(), &l, memory.get_data(), memory.get_size());

         if (i == Z_OK)
            break;

         if (i == Z_BUF_ERROR)
         {
            iRate++;
            if (iRate > 4)
               return false;
            dest.allocate(dest.get_size() * 2);
            continue;
         }

         return false;

      }

      memory = dest;

      return true;

   }


   bool compress::gz(::file::ostream & ostreamCompressed, const ::file::path & lpcszUncompressed, int iLevel)
   {

      compress_gz gz(get_app(), iLevel);

      return System.file().output(get_app(), ostreamCompressed, &gz, &compress_gz::transfer, lpcszUncompressed);

   }



   bool compress::ungz(::aura::application * papp, const ::file::path & lpcszUncompressed, const ::file::path & lpcszGzFileCompressed)
   {

      return System.file().output(papp, lpcszUncompressed, this, &compress::ungz, lpcszGzFileCompressed);

   }


   bool compress::gz(::aura::application * papp, const ::file::path & lpcszGzFileCompressed, const ::file::path & lpcszUncompressed, int iLevel)
   {

      compress_gz gz(papp, iLevel);

      return System.file().output(papp, lpcszGzFileCompressed, &gz, &compress_gz::transfer, lpcszUncompressed);

   }


   bool compress::unbz(::file::ostream & ostreamUncompressed, const ::file::path & lpcszBzFileCompressed)
   {

      return Application.file().output(ostreamUncompressed, this, &compress::unbz, lpcszBzFileCompressed);

   }


   bool compress::bz(::file::ostream & ostreamBzFileCompressed, const ::file::path & lpcszUncompressed, int iBlockSize, int iVerbosity, int iWorkFactor)
   {

      compress_bz bz(get_app(), iBlockSize, iVerbosity, iWorkFactor);

      return Application.file().output(ostreamBzFileCompressed, &bz, &::compress_bz::transfer, lpcszUncompressed);

   }


   bool compress::bz(::aura::application * papp, const ::file::path & lpcszBzFileCompressed, const ::file::path & lpcszUncompressed, int iBlockSize, int iVerbosity, int iWorkFactor)
   {

      compress_bz bz(papp, iBlockSize, iVerbosity, iWorkFactor);

      return App(papp).file().output(lpcszBzFileCompressed, &bz, &::compress_bz::transfer, lpcszUncompressed);

   }


   bool compress::bz(::file::ostream & ostreamBzFileCompressed, ::file::istream & istreamUncompreseed, int iBlockSize, int iVerbosity, int iWorkFactor)
   {

      compress_bz bz(get_app(), iBlockSize, iVerbosity, iWorkFactor);

      return Application.file().output(ostreamBzFileCompressed, &bz, &::compress_bz::transfer, istreamUncompreseed);

   }


   bool compress::unbz(::aura::application * papp, const ::file::path & lpcszUncompressed, const ::file::path & lpcszGzFileCompressed)
   {

      return System.file().output(papp, lpcszUncompressed, this, &compress::unbz, lpcszGzFileCompressed);

   }


   bool compress::_compress(class memory & memory, void * pdata, memory_size_t ulSize)
   {
      memory.allocate(compressBound((uLong)ulSize) * 2);
      uLongf ulDestSize = (uLongf)memory.get_size();
      int32_t i = ::compress(memory.get_data(), &ulDestSize, (BYTE *)pdata, (uLongf)ulSize);
      memory.allocate(ulDestSize);
      return i == Z_OK;
   }

   bool compress::_uncompress(memory & memoryUncompressed, memory & memoryCompressed, memory_size_t sizeUncompressed)
   {
      memoryUncompressed.allocate(sizeUncompressed);
      uLongf ulSizeUncompressed = (uLongf)sizeUncompressed;
      int32_t i = ::uncompress(memoryUncompressed.get_data(), &ulSizeUncompressed, memoryCompressed.get_data(), (uLong)memoryCompressed.get_size());
      return i == Z_OK;
   }


   void compress::extract_all(const ::file::path & pszFile, ::aura::application * papp)
   {

      string strDir = pszFile;

      ::str::ends_eat_ci(strDir, ".zip");

      Sess(papp).file().copy(strDir, pszFile, false);

   }


   void compress::zip(const ::file::path & pszZip, const ::file::path & psz, ::aura::application * papp)
   {

      zip::InFile infile(papp);

      if (!infile.zip_open(pszZip, 0))
      {

         throw "Could not open zip file";

         return;

      }

      if (System.dir().is(psz, papp))
      {

         ::file::listing patha(papp);

         ::file::path strPath;

         ::file::file_sp file;

         patha.rls_file(psz);

         for (int32_t i = 0; i < patha.get_size(); i++)
         {

            infile.add_file(psz, patha[i].relative());

         }

      }

   }


   void compress::zip(const ::file::path & psz, ::aura::application * papp)
   {

   }


} // namespace core





