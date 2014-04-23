#pragma once

#if !defined(APPLE_OS) && !defined(ANDROID)

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

