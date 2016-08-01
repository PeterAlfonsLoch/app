#pragma once

#if !defined(APPLEOS) && !defined(ANDROID)

#if BYTE_ORDER == BIG_ENDIAN

#define HTONS(n) (n)
#define NTOHS(n) (n)
#define HTONL(n) (n)
#define NTOHL(n) (n)

#else

#define HTONS(n) (((((uint16_t)(n) & 0xFF)) << 8) | (((uint16_t)(n) & 0xFF00) >> 8))
#define NTOHS(n) (((((uint16_t)(n) & 0xFF)) << 8) | (((uint16_t)(n) & 0xFF00) >> 8))

#define HTONL(n) (((((unsigned long)(n) & 0xFF)) << 24) | \
   ((((unsigned long)(n)& 0xFF00)) << 8) | \
   ((((unsigned long)(n)& 0xFF0000)) >> 8) | \
   ((((unsigned long)(n)& 0xFF000000)) >> 24))

#define NTOHL(n) (((((unsigned long)(n) & 0xFF)) << 24) | \
   ((((unsigned long)(n)& 0xFF00)) << 8) | \
   ((((unsigned long)(n)& 0xFF0000)) >> 8) | \
   ((((unsigned long)(n)& 0xFF000000)) >> 24))
#endif

#endif

#if BYTE_ORDER == BIG_ENDIAN

#define HTONLL(n) (n)
#define NTOHLL(n) (n)

#else

//#ifdef WINDOWS
//#define HTONLL(n) (((((uint64_t)(n) & 0xFFu64)) << 56) | \
//   ((((uint64_t)(n) & 0xFF00u64)) << 40) | \
//   ((((uint64_t)(n) & 0xFF0000u64)) << 24) | \
//   ((((uint64_t)(n) & 0xFF000000u64)) << 8) | \
//   ((((uint64_t)(n) & 0xFF00000000u64)) >> 8) | \
//   ((((uint64_t)(n) & 0xFF0000000000u64)) >> 24) | \
//   ((((uint64_t)(n) & 0xFF000000000000u64)) >> 40) | \
//   ((((uint64_t)(n) & 0xFF00000000000000u64)) >> 56))
//
//   #else
#define HTONLL(n) (((((uint64_t)(n) & 0xFFuLL)) << 56) | \
   ((((uint64_t)(n) & 0xFF00uLL)) << 40) | \
   ((((uint64_t)(n) & 0xFF0000uLL)) << 24) | \
   ((((uint64_t)(n) & 0xFF000000uLL)) << 8) | \
   ((((uint64_t)(n) & 0xFF00000000uLL)) >> 8) | \
   ((((uint64_t)(n) & 0xFF0000000000uLL)) >> 24) | \
   ((((uint64_t)(n) & 0xFF000000000000uLL)) >> 40) | \
   ((((uint64_t)(n) & 0xFF00000000000000uLL)) >> 56))
//   #endif
//
//#ifdef WINDOWS
//#define NTOHLL(n) (((((uint64_t)(n) & 0xFFu64)) << 56) | \
//   ((((uint64_t)(n) & 0xFF00u64)) << 40) | \
//   ((((uint64_t)(n) & 0xFF0000u64)) << 24) | \
//   ((((uint64_t)(n) & 0xFF000000u64)) << 8) | \
//   ((((uint64_t)(n) & 0xFF00000000u64)) >> 8) | \
//   ((((uint64_t)(n) & 0xFF0000000000u64)) >> 24) | \
//   ((((uint64_t)(n) & 0xFF000000000000u64)) >> 40) | \
//   ((((uint64_t)(n) & 0xFF00000000000000u64)) >> 56))
//#else
#define NTOHLL(n) (((((uint64_t)(n) & 0xFFuLL)) << 56) | \
   ((((uint64_t)(n) & 0xFF00uLL)) << 40) | \
   ((((uint64_t)(n) & 0xFF0000uLL)) << 24) | \
   ((((uint64_t)(n) & 0xFF000000uLL)) << 8) | \
   ((((uint64_t)(n) & 0xFF00000000uLL)) >> 8) | \
   ((((uint64_t)(n) & 0xFF0000000000uLL)) >> 24) | \
   ((((uint64_t)(n) & 0xFF000000000000uLL)) >> 40) | \
   ((((uint64_t)(n) & 0xFF00000000000000uLL)) >> 56))
//#endif
#endif


#if defined(METROWIN)

/*uint16_t htons(uint16_t n);
uint16_t ntohs(uint16_t n);
unsigned long htonl(unsigned long n);
unsigned long ntohl(unsigned long n);*/

#define AF_INET         2               // internetwork: UDP, TCP, etc.
#define AF_INET6        23              // Internetwork Version 6


#define htons(n) HTONS(n)
#define ntohs(n) NTOHS(n)

#define htonl(n) HTONL(n)
#define ntohl(n) NTOHL(n)

#endif

