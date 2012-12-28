#pragma once

#if defined(MACOS) || defined(LINUX)
#include <netinet/in.h>
#endif


CLASS_DECL_c bool from_string(in6_addr * addr, const char * string);
CLASS_DECL_c vsstring to_string(const in6_addr *addr);
CLASS_DECL_c bool from_string(in_addr * addr, const char * string);
CLASS_DECL_c vsstring to_string(const in_addr *addr);

CLASS_DECL_c unsigned long c_inet_addr(const char *src);
CLASS_DECL_c int32_t c_inet_pton(int32_t af, const char *src, void *dst);
CLASS_DECL_c const char * c_inet_ntop(int32_t af, const void *src, char *dst, int32_t cnt);
CLASS_DECL_c vsstring c_inet_ntop(int32_t af, const void *src);


CLASS_DECL_c vsstring c_gethostbyname(const char * hostname);

#ifndef MACOS

#if BYTE_ORDER == BIG_ENDIAN

#define HTONS(n) (n)
#define NTOHS(n) (n)
#define HTONL(n) (n)
#define NTOHL(n) (n)

#else

#define HTONS(n) (((((unsigned short)(n) & 0xFF)) << 8) | (((unsigned short)(n) & 0xFF00) >> 8))
#define NTOHS(n) (((((unsigned short)(n) & 0xFF)) << 8) | (((unsigned short)(n) & 0xFF00) >> 8))

#define HTONL(n) (((((unsigned long)(n) & 0xFF)) << 24) | \
                  ((((unsigned long)(n) & 0xFF00)) << 8) | \
                  ((((unsigned long)(n) & 0xFF0000)) >> 8) | \
                  ((((unsigned long)(n) & 0xFF000000)) >> 24))

#define NTOHL(n) (((((unsigned long)(n) & 0xFF)) << 24) | \
                  ((((unsigned long)(n) & 0xFF00)) << 8) | \
                  ((((unsigned long)(n) & 0xFF0000)) >> 8) | \
                  ((((unsigned long)(n) & 0xFF000000)) >> 24))
#endif

#endif

#if 0

unsigned short htons(unsigned short n);
unsigned short ntohs(unsigned short n);
unsigned long htonl(unsigned long n);
unsigned long ntohl(unsigned long n);

#define htons(n) HTONS(n)
#define ntohs(n) NTOHS(n)

#define htonl(n) HTONL(n)
#define ntohl(n) NTOHL(n)

#endif

