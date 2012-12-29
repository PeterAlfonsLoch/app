
#ifndef PORTABLE_C__
#define PORTABLE_C__

#include <limits.h>

/* Definition of minimum-width integer types
 *
 * u8   -> unsigned integer type, at least 8 bits, equivalent to unsigned char
 * u16  -> unsigned integer type, at least 16 bits
 * u32  -> unsigned integer type, at least 32 bits
 *
 * s8, s16, s32  -> signed counterparts of u8, u16, u32
 *
 * Always use macro's T8(), T16() or T32() to obtain exact-width results,
 * i.e., to specify the size of the result of each expression.
 */

/*typedef signed char s8;
typedef unsigned char u8;

#if UINT_MAX >= 4294967295UL

typedef int16_t s16;
typedef int32_t s32;
typedef uint16_t u16;
typedef uint32_t u32;

#define ONE32   0xffffffffU

#else

typedef int32_t s16;
typedef signed long s32;
typedef uint32_t u16;
typedef unsigned long u32;

#define ONE32   0xffffffffUL

#endif*/

#if UINT_MAX >= 4294967295UL

#define NESSIE_ONE32   0xffffffffU

#else

#define NESSIE_ONE32   0xffffffffUL

#endif

#define ONE8    0xffU
#define ONE16   0xffffU

#define T8(x)   ((x) & ONE8)
#define T16(x)  ((x) & ONE16)
#define T32(x)  ((x) & ONE32)

#ifdef _MSC_VER
//typedef uint64_t u64;
//typedef int64_t s64;
#define LL(v)   (v##ui64)
#define ONE64   LL(0xffffffffffffffff)
#else  /* !_MSC_VER */
//typedef unsigned long long u64;
//typedef signed long long s64;
#define LL(v)   (v##ULL)
#define ONE64   LL(0xffffffffffffffff)
#endif /* ?_MSC_VER */
#define T64(x)  ((x) & ONE64)
#define ROTR64(v, n)   (((v) >> (n)) | T64((v) << (64 - (n))))
/*
 * Note: the test is used to detect native 64-bit architectures;
 * if the unsigned long is strictly greater than 32-bit, it is
 * assumed to be at least 64-bit. This will not work correctly
 * on (old) 36-bit architectures (PDP-11 for instance).
 *
 * On non-64-bit architectures, "long long" is used.
 */

/*
 * U8TO32_BIG(c) returns the 32-bit value stored in big-endian convention
 * in the unsigned char array pointed to by c.
 */
#define U8TO32_BIG(c)  (((u32)T8(*(c)) << 24) | ((u32)T8(*((c) + 1)) << 16) | ((u32)T8(*((c) + 2)) << 8) | ((u32)T8(*((c) + 3))))

/*
 * U8TO32_LITTLE(c) returns the 32-bit value stored in little-endian convention
 * in the unsigned char array pointed to by c.
 */
#define U8TO32_LITTLE(c)  (((u32)T8(*(c))) | ((u32)T8(*((c) + 1)) << 8) | (u32)T8(*((c) + 2)) << 16) | ((u32)T8(*((c) + 3)) << 24))

/*
 * U8TO32_BIG(c, v) stores the 32-bit-value v in big-endian convention
 * into the unsigned char array pointed to by c.
 */
#define U32TO8_BIG(c, v)    do { u32 x = (v); u8 *d = (c); d[0] = T8(x >> 24); d[1] = T8(x >> 16); d[2] = T8(x >> 8); d[3] = T8(x); } while (0)

/*
 * U8TO32_LITTLE(c, v) stores the 32-bit-value v in little-endian convention
 * into the unsigned char array pointed to by c.
 */
#define U32TO8_LITTLE(c, v)    do { u32 x = (v); u8 *d = (c); d[0] = T8(x); d[1] = T8(x >> 8); d[2] = T8(x >> 16); d[3] = T8(x >> 24); } while (0)

/*
 * ROTL32(v, n) returns the value of the 32-bit unsigned value v after
 * a rotation of n bits to the left. It might be replaced by the appropriate
 * architecture-specific macro.
 *
 * It evaluates v and n twice.
 *
 * The compiler might emit a warning if n is the constant 0. The result
 * is undefined if n is greater than 31.
 */
#define ROTL32(v, n)   (T32((v) << (n)) | ((v) >> (32 - (n))))

/*
 * Whirlpool-specific definitions.
 */

#define NESSIE_DIGESTBYTES 64
#define NESSIE_DIGESTBITS  (8*NESSIE_DIGESTBYTES) /* 512 */

#define NESSIE_WBLOCKBYTES 64
#define NESSIE_WBLOCKBITS  (8*NESSIE_WBLOCKBYTES) /* 512 */

#define NESSIE_LENGTHBYTES 32
#define NESSIE_LENGTHBITS  (8*NESSIE_LENGTHBYTES) /* 256 */

typedef struct NESSIEstruct {
   uint8_t  bitLength[NESSIE_LENGTHBYTES]; /* global number of hashed bits (256-bit counter) */
   uint8_t  buffer[NESSIE_WBLOCKBYTES];   /* buffer of data to hash */
   int32_t bufferBits;              /* current number of bits on the buffer */
   int32_t bufferPos;              /* current (possibly incomplete) byte slot on the buffer */
   uint64_t hash[NESSIE_DIGESTBYTES/8];    /* the hashing state */
} NESSIEstruct;


CLASS_DECL_c void NESSIEinit(struct NESSIEstruct * const structpointer);
CLASS_DECL_c void NESSIEadd(const unsigned char * const source, unsigned long sourceBits, struct NESSIEstruct * const structpointer);
CLASS_DECL_c void NESSIEfinalize(struct NESSIEstruct * const structpointer, unsigned char * const result);

vsstring crypt_nessie(const char * psz);

#endif   /* PORTABLE_C__ */

