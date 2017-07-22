//#include"framework.h"
//#include"axis/compress/compress.h"
#include "compress_gz.h"
#include "compress_bz.h"


namespace axis
{

   compress_department::compress_department(::aura::application * papp) :
      ::object(papp),
      ::aura::department(papp)
   {


   }

   bool compress_department::ungz(::aura::application * papp, ::file::ostream & ostreamUncompressed, const ::file::path & lpcszGzFileCompressed)
   {

      uncompress_gz ungz(papp);

      return App(papp).file().output(ostreamUncompressed, &ungz, &::uncompress_gz::transfer, lpcszGzFileCompressed);
      
   }






   bool compress_department::ungz(::aura::application * papp, ::file::file * pfileOut, ::file::file * pfileIn)
   {

      uncompress_gz ungz(papp);

      return App(papp).file().output(pfileOut, &ungz, &::uncompress_gz::transfer, pfileIn);

   }


   bool compress_department::ungz(::aura::application * papp, ::primitive::memory_base & memOut, ::primitive::memory_base & memIn)
   {

      memory_file fileOut(papp, &memOut);

      memory_file fileIn(papp, &memIn);

      return ungz(papp, &fileOut, &fileIn);

   }


   bool compress_department::ungz(::aura::application * papp, ::primitive::memory_base & mem)
   {

      memory memOut;

      if (!ungz(papp, memOut, mem))
      {

         return false;

      }

      mem = memOut;

      return true;

   }


   bool compress_department::gz(::aura::application * papp, ::file::ostream & ostreamCompressed, const ::file::path & lpcszUncompressed, int iLevel)
   {

      compress_gz gz(papp, iLevel);

      return App(papp).file().output(ostreamCompressed, &gz, &compress_gz::transfer, lpcszUncompressed);

   }

   bool compress_department::gz(::aura::application * papp, ::file::file * pfileOut, const ::file::path & lpcszUncompressed, int iLevel)
   {

      compress_gz gz(papp, iLevel);

      return App(papp).file().output(pfileOut, &gz, &compress_gz::transfer, lpcszUncompressed);


   }


   bool compress_department::gz(::aura::application * papp, ::file::file * pfileOut, ::file::file * pfileIn, int iLevel)
   {

      compress_gz gz(papp, iLevel);

      return App(papp).file().output(pfileOut, &gz, &compress_gz::transfer, pfileIn);


   }



   bool compress_department::ungz(::aura::application * papp, const ::file::path & lpcszUncompressed, const ::file::path & lpcszGzFileCompressed)
   {

      uncompress_gz ungz(papp);

      return App(papp).file().output(lpcszUncompressed, &ungz, &::uncompress_gz::transfer, lpcszGzFileCompressed);

   }



   bool compress_department::gz(::aura::application * papp, const ::file::path & lpcszGzFileCompressed, const ::file::path & lpcszUncompressed, int iLevel)
   {

      compress_gz gz(papp, iLevel);

      return App(papp).file().output(lpcszGzFileCompressed, &gz, &compress_gz::transfer, lpcszUncompressed);

   }


   bool compress_department::unbz(::aura::application * papp, ::file::ostream & ostreamUncompressed, const ::file::path & lpcszBzFileCompressed)
   {

      uncompress_bz unbz(papp);

      return App(papp).file().output(ostreamUncompressed, &unbz, &::uncompress_bz::transfer, lpcszBzFileCompressed);

   }


   bool compress_department::bz(::aura::application * papp, ::file::ostream & ostreamBzFileCompressed, const ::file::path & lpcszUncompressed, int iBlockSize, int iVerbosity, int iWorkFactor)
   {

      compress_bz bz(papp, iBlockSize, iVerbosity, iWorkFactor);

      return App(papp).file().output(ostreamBzFileCompressed, &bz, &::compress_bz::transfer, lpcszUncompressed);

   }


   bool compress_department::bz(::aura::application * papp, const ::file::path & lpcszBzFileCompressed, const ::file::path & lpcszUncompressed, int iBlockSize, int iVerbosity, int iWorkFactor)
   {

      compress_bz bz(papp, iBlockSize, iVerbosity, iWorkFactor);

      return App(papp).file().output(lpcszBzFileCompressed, &bz, &::compress_bz::transfer, lpcszUncompressed);

   }


   bool compress_department::bz(::aura::application * papp, ::file::ostream & ostreamBzFileCompressed, ::file::istream & istreamUncompreseed, int iBlockSize, int iVerbosity, int iWorkFactor)
   {

      compress_bz bz(papp, iBlockSize, iVerbosity, iWorkFactor);

      return App(papp).file().output(ostreamBzFileCompressed, &bz, &::compress_bz::transfer, istreamUncompreseed);

   }


   bool compress_department::unbz(::aura::application * papp, const ::file::path & lpcszUncompressed, const ::file::path & lpcszGzFileCompressed)
   {

      uncompress_bz unbz(papp);

      return App(papp).file().output(lpcszUncompressed, &unbz, &::uncompress_bz::transfer, lpcszGzFileCompressed);


   }


   bool compress_department::compress(class memory & memory, void * pdata, memory_size_t ulSize)
   {
      memory.allocate(compressBound((uLong)ulSize) * 2);
      uLongf ulDestSize = (uLongf)memory.get_size();
      int32_t i = ::compress(memory.get_data(), &ulDestSize, (BYTE *)pdata, (uLongf)ulSize);
      memory.allocate(ulDestSize);
      return i == Z_OK;
   }

   bool compress_department::uncompress(memory & memoryUncompressed, memory & memoryCompressed, memory_size_t sizeUncompressed)
   {
      memoryUncompressed.allocate(sizeUncompressed);
      uLongf ulSizeUncompressed = (uLongf)sizeUncompressed;
      int32_t i = ::uncompress(memoryUncompressed.get_data(), &ulSizeUncompressed, memoryCompressed.get_data(), (uLong)memoryCompressed.get_size());
      return i == Z_OK;
   }

   bool compress_department::uncompress(memory & dest, memory & memory)
   {

      int iRate = 1;
      while (true)
      {

         dest.allocate(memory.get_size() * 10);

         uLong l = dest.get_size();

         int i = ::uncompress(dest.get_data(), &l, memory.get_data(), memory.get_size());

         if (i == Z_OK)
         {

            dest.allocate(l);
          
            return true;

         }

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

   }

   ::count compress_department::extract_all(const ::file::path & pszFile, ::aura::application * papp)
   {

      string strDir = pszFile;

      ::str::ends_eat_ci(strDir, ".zip");

      Sess(papp).file().copy(strDir, pszFile, false);
      
      return -1;


   }


   bool compress_department::zip(const ::file::path & pszZip, const ::file::path & psz, ::aura::application * papp)
   {

      thisstart;

      zip::in_file infile(papp);

      if (!infile.zip_open(pszZip, 0))
      {

         thiserr << "Could not open zip file";

         return false;

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

      return true;

   }


   bool compress_department::zip(const ::file::path & psz, ::aura::application * papp)
   {

      throw todo(get_app());

      return false;

   }


   bool compress_department::unzip(::aura::application * papp, const ::file::path & pathUncompressed, const ::file::path & pathZipFileCompressed)
   {

      if (!zip::util().extract(papp, pathZipFileCompressed, pathUncompressed))
      {

         return false;

      }

      return true;

   }
   


} // namespace core





