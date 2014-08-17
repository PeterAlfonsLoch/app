/*
* datatypes branch
*
*/


#pragma once




#ifndef _CRYPTO_INTERNAL_DATATYPES_H
#define _CRYPTO_INTERNAL_DATATYPES_H


#ifndef SRTP_KERNEL_LINUX

/*
* Convert big endian integers to CPU byte order.
*/
#ifdef WORDS_BIGENDIAN
/* Nothing to do. */
# define be32_to_cpu(x)   (x)
# define be64_to_cpu(x)   (x)
#elif defined(HAVE_BYTESWAP_H)
/* We have (hopefully) optimized versions in byteswap.h */
# include <byteswap.h>
# define be32_to_cpu(x)   bswap_32((x))
# define be64_to_cpu(x)   bswap_64((x))
#else

#if defined(__GNUC__) && defined(HAVE_X86)
/* Fall back. */
static inline uint32_t be32_to_cpu(uint32_t v) {
   /* optimized for x86. */
   asm("bswap %0" : "=r" (v) : "0" (v));
   return v;
}
# else /* HAVE_X86 */
#  if defined(LINUX) || defined(APPLEOS)
#  elif defined HAVE_WINSOCK2_H
#   include <winsock2.h>
#  endif
#  define be32_to_cpu(x)   ntohl((x))
# endif /* HAVE_X86 */

static uint64_t be64_to_cpu(uint64_t v) {
# ifdef NO_64BIT_MATH
   /* use the make64 functions to do 64-bit math */
   v = make64(htonl(low32(v)), htonl(high32(v)));
# else
   /* use the native 64-bit math */
   v = (uint64_t)((be32_to_cpu((uint32_t)(v >> 32))) | (((uint64_t)be32_to_cpu((uint32_t)v)) << 32));
# endif
   return v;
}

#endif /* ! SRTP_KERNEL_LINUX */

#endif /* WORDS_BIGENDIAN */


#endif /* _CRYPTO_INTERNAL_DATATYPES_H */