//#include"framework.h"
//#include"axis/compress/compress.h"




namespace axis
{


   bool compress::ungz(::file::ostream & ostreamUncompressed, const ::file::path & lpcszGzFileCompressed)
   {

      int32_t fileUn = ansi_open(lpcszGzFileCompressed, ansi_file_flag(::file::type_binary | ::file::mode_read));

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

      int_ptr uncomprLen;

      while ((uncomprLen = gzread(file, memory, (uint32_t)memory.get_size())) > 0)
      {

         ostreamUncompressed.write(memory, uncomprLen);

      }

      gzclose(file);

      return true;

   }


   bool compress::ungz(::file::memory_buffer & memoryfile)
   {

      int64_t dataLength = memoryfile.get_length();

      bool done = false;
      int32_t status;

      z_stream strm;
      strm.next_in = (byte *)memoryfile.get_data();
      strm.avail_in = (uint32_t)dataLength;
      strm.total_out = 0;
      strm.zalloc = Z_NULL;
      strm.zfree = Z_NULL;

      ::file::memory_buffer memoryfileOut(get_app());
      class primitive::memory memory;
      memory.allocate(1024 * 256);
      ASSERT(memory.get_size() <= UINT_MAX);

      // inflateInit2 knows how to deal with gzip format
      if (inflateInit2(&strm, (15 + 32)) != Z_OK)
      {
         return false;
      }

      while (!done)
      {

         strm.next_out = memory.get_data();
         strm.avail_out = (uint32_t)memory.get_size();

         // Inflate another chunk.
         status = inflate(&strm, Z_SYNC_FLUSH);

         memoryfileOut.write(memory.get_data(), memory.get_size() - strm.avail_out);

         if (status == Z_STREAM_END)
         {
            done = true;
         }
         else if (status != Z_OK)
         {
            break;
         }
      }

      memoryfile = memoryfileOut;

      if (inflateEnd(&strm) != Z_OK || !done)
      {
         return true;
      }

      return true;

   }


   bool compress::gz(::file::ostream & ostreamCompressed, const ::file::path & lpcszUncompressed)
   {
      string str(lpcszUncompressed);
      FILE * fileUn = ansi_fopen(lpcszUncompressed, "rb");
      if (fileUn == NULL)
      {
         int32_t err;
         ansi_get_errno(&err);
         fprintf(stderr, "gz fopen error %d %s", err, lpcszUncompressed.c_str());
         return false;
      }
      gzip_stream gz(ostreamCompressed);
      class primitive::memory memory;
      memory.allocate(1024 * 256);
      ::primitive::memory_size uncomprLen;
      while ((uncomprLen = (::primitive::memory_size) fread(memory, 1, (size_t)memory.get_size(), fileUn)) > 0)
      {
         gz.write(memory, uncomprLen);
      }
      fclose(fileUn);
      gz.finish();
      return true;
   }


   bool compress::ungz(::aura::application * papp, const ::file::path & lpcszUncompressed, const ::file::path & lpcszGzFileCompressed)
   {

      return System.file().output(papp, lpcszUncompressed, this, &compress::ungz, lpcszGzFileCompressed);

   }


   bool compress::gz(::aura::application * papp, const ::file::path & lpcszGzFileCompressed, const ::file::path & lpcszUncompressed)
   {

      return System.file().output(papp, lpcszGzFileCompressed, this, &compress::gz, lpcszUncompressed);

   }


   bool compress::unbz(::file::ostream & ostreamUncompressed, const ::file::path & lpcszBzFileCompressed)
   {

      BZFILE * file = BZ2_bzopen(lpcszBzFileCompressed, "rb");

      if (file == NULL)
      {

         TRACE("unbz bzopen error %s", lpcszBzFileCompressed);

         return false;

      }

      primitive::memory memory;

      memory.allocate(1024 * 16 * 1024);

      int32_t uncomprLen;

      while ((uncomprLen = BZ2_bzread(file, memory, (int32_t)memory.get_size())) > 0)
      {

         ostreamUncompressed.write(memory, uncomprLen);

      }

      BZ2_bzclose(file);

      return true;

   }


   bool compress::bz(::file::ostream & ostreamBzFileCompressed, const ::file::path & lpcszUncompressed)
   {

      ::file::buffer_sp file = Application.file().get_file(lpcszUncompressed, ::file::mode_read | ::file::type_binary);

      if (file.is_null())
      {

         return false;

      }

      ::file::istream is(file);

      return bz_stream(ostreamBzFileCompressed, is);

   }


   bool compress::bz_stream(::file::ostream & ostreamBzFileCompressed, ::file::istream & istreamFileUncompressed)
   {
      bzip_stream bz(ostreamBzFileCompressed);
      class primitive::memory memory;
      memory.allocate(1024 * 256);
      ::primitive::memory_size uncomprLen;
      while ((uncomprLen = istreamFileUncompressed.read(memory, memory.get_size())) > 0)
      {
         bz.write(memory, uncomprLen);
      }
      bz.finish();
      return true;
   }

   bool compress::unbz(::aura::application * papp, const ::file::path & lpcszUncompressed, const ::file::path & lpcszGzFileCompressed)
   {
      return System.file().output(papp, lpcszUncompressed, this, &compress::unbz, lpcszGzFileCompressed);
   }

   bool compress::bz(::aura::application * papp, const ::file::path & lpcszGzFileCompressed, const ::file::path & lpcszUncompressed)
   {
      return System.file().output(papp, lpcszGzFileCompressed, this, &compress::bz, lpcszUncompressed);
   }

   bool compress::_compress(class primitive::memory & memory, void * pdata, ::primitive::memory_size ulSize)
   {
      memory.allocate(compressBound((uLong)ulSize) * 2);
      uLongf ulDestSize = (uLongf)memory.get_size();
      int32_t i = ::compress(memory.get_data(), &ulDestSize, (BYTE *)pdata, (uLongf)ulSize);
      memory.allocate(ulDestSize);
      return i == Z_OK;
   }

   bool compress::_uncompress(primitive::memory & memoryUncompressed, primitive::memory & memoryCompressed, ::primitive::memory_size sizeUncompressed)
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

         ::file::buffer_sp file;

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

   bool compress::null(::file::ostream & ostream, ::file::istream & istream)
   {
      class primitive::memory memory;
      memory.allocate(1024 * 256);
      ::primitive::memory_size  uiRead;
      while ((uiRead = istream.read(memory, memory.get_size())) > 0)
      {
         ostream.write(memory, uiRead);
      }
      return true;
   }




} // namespace core





