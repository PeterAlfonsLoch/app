#include"framework.h"
//#include"axis/zlib/zlib.h"
//#include"axis/zlib/zutil.h"
#include "zlib.h"
#include "zutil.h"
#include "compress_gz.h"


   //#define ALLOC(size) malloc(size)
   //#define TRYFREE(p) {if (p) free(p);}
   //#define Z_BUFSIZE 4096
#define ASCII_FLAG   0x01 /* bit 0 set: file probably ascii text */
#define HEAD_CRC     0x02 /* bit 1 set: header CRC present */
#define EXTRA_FIELD  0x04 /* bit 2 set: extra field present */
#define ORIG_NAME    0x08 /* bit 3 set: original file name present */
#define COMMENT      0x10 /* bit 4 set: file comment present */
#define RESERVED     0xE0 /* bits 5..7: reserved */

   typedef  uchar GZIP;
   typedef  GZIP* LPGZIP;

   //static const int32_t gz_magic[2] = {0x1f, 0x8b}; /* gzip_stream magic header */


   compress_gz::compress_gz(::aura::application * papp, int iLevel) :
      ::object(papp)
   {

      m_iLevel = iLevel;

   }

   compress_gz::~compress_gz()
   {
   }








   bool compress_gz::transfer(::file::ostream & ostreamGzFileCompressed, ::file::istream & istreamUncompressed)
   {

      int iLevel = m_iLevel;

      if (iLevel < 0)
      {

         iLevel = 0;

      }
      else if (iLevel > 9)
      {

         iLevel = 9;

      }

      int32_t status;

      class memory memIn;
      memIn.allocate(1024 * 64);

      int64_t uiRead = istreamUncompressed.read(memIn.get_data(), memIn.get_size());

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
      if (deflateInit2(&zstream, iLevel, Z_DEFLATED, 16 + MAX_WBITS, 9, Z_DEFAULT_STRATEGY) != Z_OK)
      {
         return false;
      }

      // use deflateSetHeader to set original file params

      int iFlush = Z_NO_FLUSH;

      while (true)
      {

         do
         {

            zstream.next_out = memory.get_data();

            zstream.avail_out = (uint32_t)memory.get_size();

            // Inflate another chunk.
            status = deflate(&zstream, iFlush);

            ostreamGzFileCompressed.write(memory.get_data(), (uint32_t)memory.get_size() - zstream.avail_out);

            if (status == Z_STREAM_END)
            {

               goto stop1;

            }
            else if (status != Z_OK)
            {

               goto stop1;

            }

         } while (zstream.avail_out == 0 || zstream.avail_in > 0);

         uiRead = istreamUncompressed.read(memIn.get_data(), memIn.get_size());

         if (uiRead == 0)
         {

            iFlush = Z_FINISH;

			zstream.next_in = (byte *) NULL;

			zstream.avail_in = (uint32_t)0;

         }
		 else
		 {

			 zstream.next_in = (byte *)memIn.get_data();

			 zstream.avail_in = (uint32_t)uiRead;

		 }

      }

      stop1:

      status = deflateEnd(&zstream);
      
      return status >= 0;

   }







   uncompress_gz::uncompress_gz(::aura::application * papp) :
      ::object(papp)
   {

   }

   uncompress_gz::~uncompress_gz()
   {
   }



   bool uncompress_gz::transfer(::file::ostream & ostreamUncompressed, ::file::istream & istreamGzFileCompressed)
   {

      int32_t status;

      class memory memIn;

      memIn.allocate(1024 * 8);

      uint32_t uiRead = istreamGzFileCompressed.read(memIn.get_data(), memIn.get_size());

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
      if (inflateInit2(&zstream, 16 + MAX_WBITS) != Z_OK)
      {
         
         return false;

      }

      while (true)
      {

         do
         {

            zstream.next_out = memory.get_data();
            zstream.avail_out = (uint32_t)memory.get_size();

            // Inflate another chunk.
            status = inflate(&zstream, Z_NO_FLUSH);

            ostreamUncompressed.write(memory.get_data(), memory.get_size()- zstream.avail_out);

            if (status == Z_STREAM_END)
            {

               goto stop1;

            }
            else if (status != Z_OK)
            {

               goto stop1;

            }

         } while (zstream.avail_out == 0 || zstream.avail_in > 0);

         uiRead = istreamGzFileCompressed.read(memIn.get_data(), memIn.get_size());

         zstream.next_in = (byte *)memIn.get_data();

         zstream.avail_in = (uint32_t)uiRead;

      }

      stop1:

      if (inflateEnd(&zstream) != Z_OK)
      {

         return true;

      }

      return true;

   }
