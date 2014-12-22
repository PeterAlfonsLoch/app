#include "framework.h"
#include "axis/zlib/zlib.h"
#include "axis/zlib/zutil.h"
#include "gzip_stream.h"


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


gzip_stream::gzip_stream(::file::stream_buffer * pfileDest) :
   ::file::output_stream(pfileDest)
{

   construct();

}


gzip_stream::gzip_stream(::file::output_stream & ostreamDest) :
   ::file::output_stream(ostreamDest)
{

   construct();

}


gzip_stream::~gzip_stream()
{

}


void gzip_stream::write(const void * buf, ::primitive::memory_size iSize)
{
   m_crc = (uint32_t) crc32(m_crc, (const byte *) buf, (uInt) iSize);
   m_zstream.next_in       = (byte*)buf;
   m_zstream.avail_in      = (uint32_t) iSize;
   while (m_zstream.avail_in != 0)
   {
      if(m_zstream.avail_out == 0)
      {
         m_zstream.next_out = m_memory.get_data();
         ::file::output_stream::write(m_memory.get_data(), m_memory.get_size());
         m_zstream.avail_out = (uint32_t) m_memory.get_size();
      }
      m_z_err = deflate(&(m_zstream), Z_NO_FLUSH);
      if(m_z_err != Z_OK)
         break;
   }
}

void gzip_stream::construct()
{
   int32_t iLevel = Z_BEST_COMPRESSION;
   int32_t iStrategy = Z_DEFAULT_STRATEGY;
   m_memory.allocate(1024 * 1024 * 8);

   m_zstream.zalloc = (alloc_func)0;
   m_zstream.zfree = (free_func)0;
   m_zstream.opaque = (voidpf)0;
   m_zstream.next_in = Z_NULL;
   m_zstream.next_out = Z_NULL;
   m_zstream.avail_in = 0;
   m_zstream.avail_out = 0;
   m_z_err = Z_OK;
   m_crc = (uint32_t) crc32(0L, Z_NULL, 0);
   int32_t err = deflateInit2(&(m_zstream), iLevel,Z_DEFLATED, -MAX_WBITS, DEF_MEM_LEVEL, iStrategy);
   if (err != Z_OK || m_memory.get_data() == Z_NULL)
   {
      destroy();
      return;
   }
   GZIP header[10]={0x1f,0x8b,Z_DEFLATED, 0 /*flags*/, 0,0,0,0 /*time*/, 0 /*xflags*/, OS_CODE};
   ::file::output_stream::write(header,10);
   m_zstream.next_out      = m_memory.get_data();
   m_zstream.avail_out     = (uint32_t) m_memory.get_size();
}





void gzip_stream::finish()
{
   if(_finish() != Z_OK)
   {
      destroy();
      return;
   }
   putLong(m_crc);
   putLong (m_zstream.total_in);
   destroy();
}

int32_t gzip_stream::_finish()
{
   int32_t done = 0;
   int32_t len = 0;
   m_zstream.avail_in = 0; /* should be zero already anyway */
   for (;;)
   {
      len = (int32_t) (m_memory.get_size() - m_zstream.avail_out);

      if (len != 0)
      {
         ::file::output_stream::write(m_memory.get_data(), len);
         m_zstream.next_out   = m_memory.get_data();
         m_zstream.avail_out  = (uint32_t) m_memory.get_size();
      }
      if(done)
         break;
      m_z_err = deflate(&(m_zstream), Z_FINISH);

      /* Ignore the second of two consecutive flushes: */
      if(len == 0 && m_z_err == Z_BUF_ERROR)
         m_z_err = Z_OK;

      /* deflate has finished flushing only when it hasn't used up
      * all the available space in the output buffer:
      */
      done = (m_zstream.avail_out != 0 || m_z_err == Z_STREAM_END);

      if (m_z_err != Z_OK && m_z_err != Z_STREAM_END)
         break;
   }
   return  m_z_err == Z_STREAM_END ? Z_OK : m_z_err;
}
int32_t gzip_stream::destroy()
{
   int32_t err = Z_OK;
   if (m_zstream.state != NULL)
   {
      err = deflateEnd(&(m_zstream));
   }
   if (m_z_err < 0) err = m_z_err;
   return err;
}

void gzip_stream::putLong (uint_ptr x)
{
   for(int32_t n = 0; n < 4; n++)
   {
      uchar ca=(uchar)(x & 0xff);
      ::file::output_stream::write(&ca,1);
      x >>= 8;
   }
}






