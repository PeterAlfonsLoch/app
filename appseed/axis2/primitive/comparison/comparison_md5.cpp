/////////////////////////////////////////////////////////////////////////
// MD5.cpp
// Implementation file for MD5 class
//
// This C++ Class implementation of the original RSA Data Security, Inc.
// MD5 Message-Digest Algorithm is copyright (c) 2002, Gary McNickle.
// All rights reserved.  This software is a derivative of the "RSA Data
//  Security, Inc. MD5 Message-Digest Algorithm"
//
// You may use this software free of any charge, but without any
// warranty or implied warranty, provided that you follow the terms
// of the original RSA copyright, listed below.
//
// Original RSA Data Security, Inc. Copyright notice
/////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
// rights reserved.
//
// License to copy and use this software is granted provided that it
// is identified as the "RSA Data Security, Inc. MD5 Message-Digest
// Algorithm" in all material mentioning or referencing this software
// or this function.
// License is also granted to make and use derivative works provided
// that such works are identified as "derived from the RSA Data
// Security, Inc. MD5 Message-Digest Algorithm" in all material
// mentioning or referencing the derived work.
// RSA Data Security, Inc. makes no representations concerning either
// the merchantability of this software or the suitability of this
// software for any particular purpose. It is provided "as is"
// without express or implied warranty of any kind.
// These notices must be retained in any copies of any part of this
// documentation and/or software.
/////////////////////////////////////////////////////////////////////////
#include "framework.h"


#if defined(LINUX ) || defined(ANDROID) || defined(APPLEOS)
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#endif


uchar PADDING[64] =
{
  0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21



/*
 * This is an OpenSSL-compatible implementation of the RSA Data Security, Inc.
 * MD5 Message-Digest Algorithm (RFC 1321).
 *
 * Homepage:
 * http://openwall.info/wiki/people/solar/software/public-domain-source-code/md5
 *
 * Author:
 * Alexander Peslyak, better known as Solar Designer <solar at openwall.com>
 *
 * This software was written by Alexander Peslyak in 2001.  No copyright is
 * claimed, and the software is hereby placed in the public domain.
 * In case this attempt to disclaim copyright and place the software in the
 * public domain is deemed NULL and void, then the software is
 * Copyright (c) 2001 Alexander Peslyak and it is hereby released to the
 * general public under the following terms:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted.
 *
 * There's ABSOLUTELY NO WARRANTY, express or implied.
 *
 * (This is a heavily cut-down "BSD license".)
 *
 * This differs from Colin Plumb's older public domain implementation in that
 * no exactly 32-bit integer data type is required (any 32-bit or wider
 * uint32_t integer data type will do), there's no compile-time endianness
 * configuration, and the function prototypes match OpenSSL's.  No code from
 * Colin Plumb's implementation has been reused; this comment merely compares
 * the properties of the two independent implementations.
 *
 * The primary goals of this implementation are portability and ease of use.
 * It is meant to be fast, but not as fast as possible.  Some known
 * optimizations are not included to reduce source code size and avoid
 * compile-time configuration.
 */

/*
 * The basic MD5 functions.
 *
 * F and G are optimized compared to their RFC 1321 definitions for
 * architectures that lack an AND-NOT instruction, just like in Colin Plumb's
 * implementation.
 */
#define F(x, y, z)			((z) ^ ((x) & ((y) ^ (z))))
#define G(x, y, z)			((y) ^ ((z) & ((x) ^ (y))))
#define H(x, y, z)			((x) ^ (y) ^ (z))
#define I(x, y, z)			((y) ^ ((x) | ~(z)))

/*
 * The MD5 transformation for all four rounds.
 */
#define STEP(f, a, b, c, d, x, t, s) \
	(a) += f((b), (c), (d)) + (x) + (t); \
	(a) = (((a) << (s)) | (((a) & 0xffffffff) >> (32 - (s)))); \
	(a) += (b);

/*
 * SET reads 4 input bytes in little-endian byte order and stores them
 * in a properly aligned uint16_t in host byte order.
 *
 * The check for little-endian architectures that tolerate unaligned
 * memory accesses is just an optimization.  Nothing will break if it
 * doesn't work.
 */
#if defined(__i386__) || defined(__x86_64__) || defined(__vax__)
typedef uint32_t MD5_u32plus;
#define SET(n) \
	(*(MD5_u32plus *)&ptr[(n) * 4])
#define GET(n) \
	SET(n)
#else
#define SET(n) \
	(m_ctx.block[(n)] = \
	(uint32_t)ptr[(n) * 4] | \
	((uint32_t)ptr[(n) * 4 + 1] << 8) | \
	((uint32_t)ptr[(n) * 4 + 2] << 16) | \
	((uint32_t)ptr[(n) * 4 + 3] << 24))
#define GET(n) \
	(m_ctx.block[(n)])
#endif

namespace md5
{

   md5::md5()
   {
      initialize();
   }


   /*
    * This processes one or more 64-byte data blocks, but does NOT update
    * the bit counters.  There are no alignment requirements.
    */
   const void * md5::body(const void *data, uint32_t size)
   {
	   const uchar *ptr;
	   uint32_t a, b, c, d;
	   uint32_t saved_a, saved_b, saved_c, saved_d;

	   ptr = (uchar *) data;

	   a = m_ctx.a;
	   b = m_ctx.b;
	   c = m_ctx.c;
	   d = m_ctx.d;

	   do {
		   saved_a = a;
		   saved_b = b;
		   saved_c = c;
		   saved_d = d;

   /* Round 1 */
		   STEP(F, a, b, c, d, SET(0), 0xd76aa478, 7)
		   STEP(F, d, a, b, c, SET(1), 0xe8c7b756, 12)
		   STEP(F, c, d, a, b, SET(2), 0x242070db, 17)
		   STEP(F, b, c, d, a, SET(3), 0xc1bdceee, 22)
		   STEP(F, a, b, c, d, SET(4), 0xf57c0faf, 7)
		   STEP(F, d, a, b, c, SET(5), 0x4787c62a, 12)
		   STEP(F, c, d, a, b, SET(6), 0xa8304613, 17)
		   STEP(F, b, c, d, a, SET(7), 0xfd469501, 22)
		   STEP(F, a, b, c, d, SET(8), 0x698098d8, 7)
		   STEP(F, d, a, b, c, SET(9), 0x8b44f7af, 12)
		   STEP(F, c, d, a, b, SET(10), 0xffff5bb1, 17)
		   STEP(F, b, c, d, a, SET(11), 0x895cd7be, 22)
		   STEP(F, a, b, c, d, SET(12), 0x6b901122, 7)
		   STEP(F, d, a, b, c, SET(13), 0xfd987193, 12)
		   STEP(F, c, d, a, b, SET(14), 0xa679438e, 17)
		   STEP(F, b, c, d, a, SET(15), 0x49b40821, 22)

   /* Round 2 */
		   STEP(G, a, b, c, d, GET(1), 0xf61e2562, 5)
		   STEP(G, d, a, b, c, GET(6), 0xc040b340, 9)
		   STEP(G, c, d, a, b, GET(11), 0x265e5a51, 14)
		   STEP(G, b, c, d, a, GET(0), 0xe9b6c7aa, 20)
		   STEP(G, a, b, c, d, GET(5), 0xd62f105d, 5)
		   STEP(G, d, a, b, c, GET(10), 0x02441453, 9)
		   STEP(G, c, d, a, b, GET(15), 0xd8a1e681, 14)
		   STEP(G, b, c, d, a, GET(4), 0xe7d3fbc8, 20)
		   STEP(G, a, b, c, d, GET(9), 0x21e1cde6, 5)
		   STEP(G, d, a, b, c, GET(14), 0xc33707d6, 9)
		   STEP(G, c, d, a, b, GET(3), 0xf4d50d87, 14)
		   STEP(G, b, c, d, a, GET(8), 0x455a14ed, 20)
		   STEP(G, a, b, c, d, GET(13), 0xa9e3e905, 5)
		   STEP(G, d, a, b, c, GET(2), 0xfcefa3f8, 9)
		   STEP(G, c, d, a, b, GET(7), 0x676f02d9, 14)
		   STEP(G, b, c, d, a, GET(12), 0x8d2a4c8a, 20)

   /* Round 3 */
		   STEP(H, a, b, c, d, GET(5), 0xfffa3942, 4)
		   STEP(H, d, a, b, c, GET(8), 0x8771f681, 11)
		   STEP(H, c, d, a, b, GET(11), 0x6d9d6122, 16)
		   STEP(H, b, c, d, a, GET(14), 0xfde5380c, 23)
		   STEP(H, a, b, c, d, GET(1), 0xa4beea44, 4)
		   STEP(H, d, a, b, c, GET(4), 0x4bdecfa9, 11)
		   STEP(H, c, d, a, b, GET(7), 0xf6bb4b60, 16)
		   STEP(H, b, c, d, a, GET(10), 0xbebfbc70, 23)
		   STEP(H, a, b, c, d, GET(13), 0x289b7ec6, 4)
		   STEP(H, d, a, b, c, GET(0), 0xeaa127fa, 11)
		   STEP(H, c, d, a, b, GET(3), 0xd4ef3085, 16)
		   STEP(H, b, c, d, a, GET(6), 0x04881d05, 23)
		   STEP(H, a, b, c, d, GET(9), 0xd9d4d039, 4)
		   STEP(H, d, a, b, c, GET(12), 0xe6db99e5, 11)
		   STEP(H, c, d, a, b, GET(15), 0x1fa27cf8, 16)
		   STEP(H, b, c, d, a, GET(2), 0xc4ac5665, 23)

   /* Round 4 */
		   STEP(I, a, b, c, d, GET(0), 0xf4292244, 6)
		   STEP(I, d, a, b, c, GET(7), 0x432aff97, 10)
		   STEP(I, c, d, a, b, GET(14), 0xab9423a7, 15)
		   STEP(I, b, c, d, a, GET(5), 0xfc93a039, 21)
		   STEP(I, a, b, c, d, GET(12), 0x655b59c3, 6)
		   STEP(I, d, a, b, c, GET(3), 0x8f0ccc92, 10)
		   STEP(I, c, d, a, b, GET(10), 0xffeff47d, 15)
		   STEP(I, b, c, d, a, GET(1), 0x85845dd1, 21)
		   STEP(I, a, b, c, d, GET(8), 0x6fa87e4f, 6)
		   STEP(I, d, a, b, c, GET(15), 0xfe2ce6e0, 10)
		   STEP(I, c, d, a, b, GET(6), 0xa3014314, 15)
		   STEP(I, b, c, d, a, GET(13), 0x4e0811a1, 21)
		   STEP(I, a, b, c, d, GET(4), 0xf7537e82, 6)
		   STEP(I, d, a, b, c, GET(11), 0xbd3af235, 10)
		   STEP(I, c, d, a, b, GET(2), 0x2ad7d2bb, 15)
		   STEP(I, b, c, d, a, GET(9), 0xeb86d391, 21)

		   a += saved_a;
		   b += saved_b;
		   c += saved_c;
		   d += saved_d;

		   ptr += 64;
	   } while (size -= 64);

	   m_ctx.a = a;
	   m_ctx.b = b;
	   m_ctx.c = c;
	   m_ctx.d = d;

	   return ptr;
   }

   void md5::initialize()
   {
	   m_ctx.a = 0x67452301;
	   m_ctx.b = 0xefcdab89;
	   m_ctx.c = 0x98badcfe;
	   m_ctx.d = 0x10325476;

	   m_ctx.lo = 0;
	   m_ctx.hi = 0;
   }

   void md5::update(const void *data, size_t size)
   {
	   size_t saved_lo;
	   uint_ptr used, free;

	   saved_lo = m_ctx.lo;
	   if ((m_ctx.lo = (saved_lo + size) & 0x1fffffff) < saved_lo)
		   m_ctx.hi++;
	   m_ctx.hi += size >> 29;

	   used = saved_lo & 0x3f;

	   if (used) {
		   free = 64 - used;

		   if (size < free) {
			   memcpy_dup(&m_ctx.buffer[used], data, size);
			   return;
		   }

		   memcpy_dup(&m_ctx.buffer[used], data, free);
		   data = (uchar *)data + free;
		   size -= free;
		   body(m_ctx.buffer, 64);
	   }

	   if (size >= 64) {
		   data = body(data, size & ~(uint32_t)0x3f);
		   size &= 0x3f;
	   }

	   memcpy_dup(m_ctx.buffer, data, size);
   }

   void md5::finalize()
   {
      uchar * result = m_uchaDigest;
	   uint_ptr used, free;

	   used = m_ctx.lo & 0x3f;

	   m_ctx.buffer[used++] = 0x80;

	   free = 64 - used;

	   if (free < 8) {
		   memset_dup(&m_ctx.buffer[used], 0, free);
		   body(m_ctx.buffer, 64);
		   used = 0;
		   free = 64;
	   }

	   memset_dup(&m_ctx.buffer[used], 0, free - 8);

	   m_ctx.lo <<= 3;
	   m_ctx.buffer[56] = (uchar) low_byte(m_ctx.lo);
      m_ctx.buffer[57] = (uchar) low_byte(m_ctx.lo >> 8);
      m_ctx.buffer[58] = (uchar) low_byte(m_ctx.lo >> 16);
      m_ctx.buffer[59] = (uchar) low_byte(m_ctx.lo >> 24);
      m_ctx.buffer[60] = (uchar) low_byte(m_ctx.hi);
      m_ctx.buffer[61] = (uchar) low_byte(m_ctx.hi >> 8);
      m_ctx.buffer[62] = (uchar) low_byte(m_ctx.hi >> 16);
      m_ctx.buffer[63] = (uchar) low_byte(m_ctx.hi >> 24);

	   body(m_ctx.buffer, 64);

	   result[0] = low_byte(m_ctx.a);
	   result[1] = low_byte(m_ctx.a >> 8);
	   result[2] = low_byte(m_ctx.a >> 16);
      result[3] = low_byte(m_ctx.a >> 24);
      result[4] = low_byte(m_ctx.b);
      result[5] = low_byte(m_ctx.b >> 8);
      result[6] = low_byte(m_ctx.b >> 16);
      result[7] = low_byte(m_ctx.b >> 24);
      result[8] = low_byte(m_ctx.c);
      result[9] = low_byte(m_ctx.c >> 8);
      result[10] = low_byte(m_ctx.c >> 16);
      result[11] = low_byte(m_ctx.c >> 24);
      result[12] = low_byte(m_ctx.d);
      result[13] = low_byte(m_ctx.d >> 8);
      result[14] = low_byte(m_ctx.d >> 16);
      result[15] = low_byte(m_ctx.d >> 24);

	   memset_dup(&m_ctx, 0, sizeof(m_ctx));
   }


   const uchar * md5::digest()
   {

      return m_uchaDigest;

   }


   string md5::to_string()
   {

	   string str;
      str.GetBufferSetLength(32);
      char * psz = (char *) (const char *) str;
      hex::lower_from(psz, m_uchaDigest, 16);
      psz[32] = '\0';
      str.ReleaseBuffer();
      return str;

   }


   void md5::get(::primitive::memory & mem)
   {

      mem.assign(m_uchaDigest, 16);

   }



} // namespace md5


string get_file_md5_by_map(const char * path)
{

#ifdef METROWIN


   wstring wstr(path);

   HANDLE hfile = ::CreateFile2(wstr, FILE_READ_DATA, FILE_SHARE_WRITE | FILE_SHARE_READ, OPEN_EXISTING, NULL);

   if(hfile == INVALID_HANDLE_VALUE)
   {

      return "";

   }

   DWORD dwHigh;

#ifdef AMD64

   DWORD64 dwSize = ::GetFileSize(hfile, &dwHigh);

   dwSize |= ((DWORD64) dwHigh) << 32;

#else

   DWORD dwSize = ::GetFileSize(hfile, &dwHigh);

   if(dwHigh > 0)
   {

      // cannot optimize getting md5 by map by mapping file entirely into memory view

      return "";

   }

#endif

   HANDLE hfilemap = CreateFileMappingFromApp(
      hfile,
      NULL,
      PAGE_READONLY,
      dwSize,
      NULL);

   if(hfilemap == NULL)
   {

      CloseHandle(hfile);

      return "";

   }

   char * pview = (char *) MapViewOfFileFromApp(
      hfilemap,
      FILE_MAP_READ,
      0,
      0);

   if(pview == NULL)
   {

      CloseHandle(hfile);

      CloseHandle(hfilemap);

      return "";

   }

#elif defined(WINDOWS)


   wstring wstr(path);

   HANDLE hfile = ::CreateFileW(wstr, FILE_READ_DATA, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

   if(hfile == INVALID_HANDLE_VALUE)
   {

      return "";

   }

   DWORD dwHigh;


#ifdef AMD64

   DWORD64 dwSize = ::GetFileSize(hfile, &dwHigh);

   dwSize |= ((DWORD64) dwHigh) << 32;

#else

   uint32_t dwSize = ::GetFileSize(hfile, &dwHigh);

   if(dwHigh > 0)
   {

      // cannot optimize getting md5 by map by mapping file entirely into memory view

      return "";

   }

#endif

   HANDLE hfilemap = CreateFileMapping(
      hfile,
      NULL,
      PAGE_READONLY,
      0,
      0,
      NULL);

   if(hfilemap == NULL)
   {

      CloseHandle(hfile);

      return "";

   }

   char * pview = (char *) MapViewOfFile(
      hfilemap,
      FILE_MAP_READ,
      0,
      0,
      0
      );

   if(pview == NULL)
   {

      CloseHandle(hfile);

      CloseHandle(hfilemap);

      return "";

   }
#else

   int32_t fd = ::open(path, O_RDONLY);

   if(fd == -1)
   {

      return "";

   }

   int64_t dwSize = ::get_file_size(fd);

   char * pview = (char *) mmap(NULL, dwSize, PROT_READ, MAP_PRIVATE, fd, 0);

   if(pview == MAP_FAILED)
   {

      ::close(fd);

      return "";

   }


#endif

   ::md5::md5 md5;

   md5.initialize();

   md5.update(pview, dwSize);

   md5.finalize();

#ifdef WINDOWS

   UnmapViewOfFile(pview);

   CloseHandle(hfilemap);

   CloseHandle(hfile);

#else

   munmap(pview, dwSize);

   close(fd);

#endif

   return md5.to_string();

}

string get_file_md5_by_read(const char * path)
{


   uint64_t uiSize;
#ifdef METROWIN

   DWORD dwRead;

   wstring wstr(path);

   CREATEFILE2_EXTENDED_PARAMETERS ep;

   memset(&ep, 0, sizeof(ep));
   ep.dwSize = sizeof(ep);
   ep.dwFileAttributes = FILE_ATTRIBUTE_NORMAL;



   HANDLE hfile = ::CreateFile2(wstr, GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, OPEN_EXISTING, &ep);

   if(hfile == INVALID_HANDLE_VALUE)
      return "";

   DWORD dwHigh;

   uiSize = ::GetFileSize(hfile, &dwHigh);

   uiSize |= (0x7fffffff & (uint64_t) dwHigh) << 32;


#elif defined(WINDOWS)

   DWORD dwRead;

   wstring wstr(path);

   HANDLE hfile = ::CreateFileW(wstr, GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

   if(hfile == INVALID_HANDLE_VALUE)
      return "";

   uiSize = fsize_dup(hfile);

#else

   int64_t dwRead;

   int32_t fd = ::open(path, O_RDONLY);

   if(fd == -1)
   {

      return "";

   }

   uiSize = ::get_file_size(fd);

#endif

   int32_t iAlloc = min((int32_t) uiSize, 1024 * 1024 * 8);

   char * psz = (char *) memory_alloc(iAlloc);

   ::md5::md5 md5;

   md5.initialize();

   while(true)
   {

#ifdef WINDOWS

      if(!::ReadFile(hfile, psz, min((int32_t) uiSize, iAlloc), &dwRead, NULL))
      {
         break;
      }

      if(dwRead == 0)
      {
         break;
      }


#else

      dwRead = ::read(fd, psz, min((int32_t) uiSize, iAlloc));

      if(dwRead <= 0)
      {
         break;
      }

#endif

      md5.update(psz, dwRead);

      if(uiSize <= 0)
         break;

      uiSize -= dwRead;

   }

   if(uiSize != 0)
   {

      memory_free_dbg(psz, 0);

      return "";

   }


   md5.finalize();

   memory_free_dbg(psz, 0);


#ifdef WINDOWS

   ::CloseHandle(hfile);

#else

   close(fd);

#endif

   return md5.to_string();

}


string get_file_md5(const char * path)
{

   string strMd5 = get_file_md5_by_map(path);

   if(strMd5.has_char())
      return strMd5;

   return get_file_md5_by_read(path);

}




string get_md5(const void * data, ::count c)
{

   if(c < 0)
   {

      c = strlen_dup((const char *) data);

   }

   ::md5::md5 md5;

   md5.initialize();

   md5.update((void *) data, c);

   md5.finalize();

   return md5.to_string();

}



