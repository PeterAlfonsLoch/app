#include "framework.h"
#include "compress_bz.h"
#include <bzlib.h>


#define MAKEU64(hi, lo) ((((uint64_t)hi) << 32) | ((uint64_t) lo))

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

//static const int32_t gz_magic[2] = {0x1f, 0x8b}; /* gzip magic header */

#define BZ_SETERR(err) m_z_err = err
extern "C"
{
   typedef  void *(* bzalloc)(void *,int32_t,int32_t);
   typedef  void(* bzfree)(void *,void *);

}

                                      //byte *                   m_outbuf; /* output buffer */
                                      //uint_ptr                   m_crc;     /* crc32 of uncompressed data */





compress_bz::compress_bz(::aura::application * papp, int iBlockSize, int iVerbosity, int iWorkFactor)
{

   m_iBlockSize = iBlockSize;
   m_iVerbosity = iVerbosity;
   m_iWorkFactor = iWorkFactor;

}

compress_bz::~compress_bz()
{


}


bool compress_bz::transfer(::file::ostream & ostreamBzFileCompressed, ::file::istream & istreamUncompressed)
{

   memory                     memory;
   int32_t                    m_CurrentBufferSize;
   bz_stream                  zstream;
   int32_t                    m_z_err;   /* error code for last stream operation */
//   memory_size_t              n, n2, ret;
   memory_size_t              ret;

   ZERO(zstream);

   int iBlockSize             = m_iBlockSize;
   int iVerbosity             = m_iVerbosity;
   int iWorkFactor            = m_iWorkFactor;

   class memory memIn;
   memIn.allocate(1024 * 64);

   int64_t uiRead             = istreamUncompressed.read(memIn.get_data(), memIn.get_size());

   iBlockSize                 = MAX(1, MIN(9, iBlockSize));
   iVerbosity                 = MAX(0, MIN(4, iVerbosity));
   iWorkFactor                = MAX(0, MIN(250, iWorkFactor));

   m_CurrentBufferSize        = 1024 * 1024 * 8;
   int32_t blockSize100k      = iBlockSize; // 900k
   int32_t workFactor         = iWorkFactor;
   int32_t verbosity          = iVerbosity;
   memory.allocate(m_CurrentBufferSize);

   zstream.bzalloc = (bzalloc)0;
   zstream.bzfree = (bzfree)0;
   zstream.opaque = (void *)0;
   zstream.next_in = NULL;
   zstream.next_out = NULL;
   zstream.avail_in = 0;
   zstream.avail_out = 0;
   m_z_err = BZ_OK;
   
   //   m_crc = crc32(0L,NULL,0);
   
   int32_t err = BZ2_bzCompressInit(&zstream, blockSize100k, verbosity, workFactor);
   
   if (err != BZ_OK || memory.get_data() == NULL)
   {
      
      return false;

   }

   m_z_err = BZ_OK;

   int iState = BZ_RUN;

   while (true)
   {

      do
      {

         zstream.next_out = (char *)memIn.get_data();
         zstream.avail_out = (uint32_t)memIn.get_size();

         ret = BZ2_bzCompress(&zstream, iState);

         ostreamBzFileCompressed.write(memory.get_data(), memIn.get_size() - zstream.avail_out);

         if (ret == BZ_STREAM_END)
         {

            goto stop1;

         }
         else if (ret != BZ_OK)
         {

            goto stop1;

         }

      } while (zstream.avail_out == 0);

      uiRead = istreamUncompressed.read(memIn.get_data(), memIn.get_size());

      if (uiRead == 0)
      {

         iState = BZ_FINISH;

         continue;

      }

      zstream.next_in = (char *)memIn.get_data();

      zstream.avail_in = (uint32_t)uiRead;


   }

stop1:

   BZ_SETERR(BZ_OK);
   BZ2_bzCompressEnd(&(zstream));


   return ret >= 0;

}



uncompress_bz::uncompress_bz(::aura::application * papp) :
   ::object(papp)
{

}

uncompress_bz::~uncompress_bz()
{
}


bool uncompress_bz::transfer(::file::ostream & ostreamUncompressed, ::file::istream & istreamGzFileCompressed)
{

   bool done = false;

   int32_t status;

   class memory memIn;
   memIn.allocate(1024 * 8);

   int64_t uiRead = istreamGzFileCompressed.read(memIn.get_data(), memIn.get_size());

   bz_stream zstream;
   ZERO(zstream);
   zstream.next_in = (char *)memIn.get_data();
   zstream.avail_in = (uint32_t)uiRead;

   class memory memory;
   memory.allocate(1024 * 256);
   ASSERT(memory.get_size() <= UINT_MAX);

   // inflateInit2 knows how to deal with gzip format
   if (BZ2_bzDecompressInit(&zstream, 0, 0) != BZ_OK)
   {
      return false;
   }

   while (!done)
   {

      do
      {

         zstream.next_out = (char *)memory.get_data();
         zstream.avail_out = (uint32_t)memory.get_size();

         // Inflate another chunk.
         status = BZ2_bzDecompress(&zstream);

         ostreamUncompressed.write(memory.get_data(), memory.get_size()-zstream.avail_out);

         if (status == BZ_STREAM_END)
         {

            goto stop1;

         }
         else if (status != BZ_OK)
         {

            goto stop1;

         }

      } while (zstream.avail_out == 0);

      uiRead = istreamGzFileCompressed.read(memIn.get_data(), memIn.get_size());

      zstream.next_in = (char *)memIn.get_data();

      zstream.avail_in = (uint32_t)uiRead;

   }

   stop1:

   if (BZ2_bzDecompressEnd(&zstream) != BZ_OK || !done)
   {

      return true;

   }

   return true;

}
