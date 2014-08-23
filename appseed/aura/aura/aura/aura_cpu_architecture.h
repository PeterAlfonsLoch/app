/* CpuArch.h -- CPU specific code
2010-10-26: Igor Pavlov : Public domain */
// from 7-zip on 2012-12-23, dawn
#pragma once


/*
MY_CPU_LE means that CPU is LITTLE ENDIAN.
If MY_CPU_LE is not defined, we don't know about that property of platform (it can be LITTLE ENDIAN).

MY_CPU_LE_UNALIGN means that CPU is LITTLE ENDIAN and CPU supports unaligned memory accesses.
If MY_CPU_LE_UNALIGN is not defined, we don't know about these properties of platform.
*/

#if defined(_M_X64) || defined(_M_AMD64) || defined(__x86_64__)
#define MY_CPU_AMD64
#endif

#if defined(MY_CPU_AMD64) || defined(_M_IA64)
#define MY_CPU_64BIT
#endif

#if defined(_M_IX86) || defined(__i386__)
#define MY_CPU_X86
#endif

#if defined(MY_CPU_X86) || defined(MY_CPU_AMD64)
#define MY_CPU_X86_OR_AMD64
#endif

#if defined(MY_CPU_X86) || defined(_M_ARM)
#define MY_CPU_32BIT
#endif

#if defined(_WIN32) && defined(_M_ARM)
#define MY_CPU_ARM_LE
#endif

#if defined(_WIN32) && defined(_M_IA64)
#define MY_CPU_IA64_LE
#endif

#if defined(MY_CPU_X86_OR_AMD64)
#define MY_CPU_LE_UNALIGN
#endif

#if defined(MY_CPU_X86_OR_AMD64) || defined(MY_CPU_ARM_LE)  || defined(MY_CPU_IA64_LE) || defined(__ARMEL__) || defined(__MIPSEL__) || defined(__LITTLE_ENDIAN__)
#define MY_CPU_LE
#endif

#if defined(__BIG_ENDIAN__)
#define MY_CPU_BE
#endif

#if defined(MY_CPU_LE) && defined(MY_CPU_BE)
Stop_Compiling_Bad_Endian
#endif

#ifdef MY_CPU_LE_UNALIGN

#define GetUi16(p) (*(const uint16_t *)(p))
#define GetUi32(p) (*(const uint32_t *)(p))
#define GetUi64(p) (*(const uint64_t *)(p))
#define SetUi16(p, d) *(uint16_t *)(p) = (d);
#define SetUi32(p, d) *(uint32_t *)(p) = (d);
#define SetUi64(p, d) *(uint64_t *)(p) = (d);

#else

#define GetUi16(p) (((const byte *)(p))[0] | ((uint16_t)((const byte *)(p))[1] << 8))

#define GetUi32(p) ( \
   ((const byte *)(p))[0]        | \
   ((uint32_t)((const byte *)(p))[1] <<  8) | \
   ((uint32_t)((const byte *)(p))[2] << 16) | \
   ((uint32_t)((const byte *)(p))[3] << 24))

#define GetUi64(p) (GetUi32(p) | ((uint64_t)GetUi32(((const byte *)(p)) + 4) << 32))

#define SetUi16(p, d) { uint32_t _x_ = (d); \
   ((byte *)(p))[0] = (byte)_x_; \
   ((byte *)(p))[1] = (byte)(_x_ >> 8); }

#define SetUi32(p, d) { uint32_t _x_ = (d); \
   ((byte *)(p))[0] = (byte)_x_; \
   ((byte *)(p))[1] = (byte)(_x_ >> 8); \
   ((byte *)(p))[2] = (byte)(_x_ >> 16); \
   ((byte *)(p))[3] = (byte)(_x_ >> 24); }

#define SetUi64(p, d) { uint64_t _x64_ = (d); \
   SetUi32(p, (uint32_t)_x64_); \
   SetUi32(((byte *)(p)) + 4, (uint32_t)(_x64_ >> 32)); }

#endif

#if defined(MY_CPU_LE_UNALIGN) && defined(_WIN64) && (_MSC_VER >= 1300)

   //#pragma intrinsic(_byteswap_ulong)
   //#pragma intrinsic(_byteswap_uint64)
#define GetBe32(p) _byteswap_ulong(*(const uint32_t *)(const byte *)(p))
#define GetBe64(p) _byteswap_uint64(*(const uint64_t *)(const byte *)(p))

#else

#define GetBe32(p) ( \
   ((uint32_t)((const byte *)(p))[0] << 24) | \
   ((uint32_t)((const byte *)(p))[1] << 16) | \
   ((uint32_t)((const byte *)(p))[2] <<  8) | \
   ((const byte *)(p))[3] )

#define GetBe64(p) (((uint64_t)GetBe32(p) << 32) | GetBe32(((const byte *)(p)) + 4))

#endif

#define GetBe16(p) (((uint16_t)((const byte *)(p))[0] << 8) | ((const byte *)(p))[1])


#ifdef MY_CPU_X86_OR_AMD64

struct Cx86cpuid
{
   uint32_t maxFunc;
   uint32_t vendor[3];
   uint32_t ver;
   uint32_t b;
   uint32_t c;
   uint32_t d;
};

enum
{
   CPU_FIRM_INTEL,
   CPU_FIRM_AMD,
   CPU_FIRM_VIA
};

CLASS_DECL_AURA int32_t x86cpuid_CheckAndRead(struct Cx86cpuid *p);
CLASS_DECL_AURA int32_t x86cpuid_GetFirm(const struct Cx86cpuid *p);

#define x86cpuid_GetFamily(p) (((p)->ver >> 8) & 0xFF00F)
#define x86cpuid_GetModel(p) (((p)->ver >> 4) & 0xF00F)
#define x86cpuid_GetStepping(p) ((p)->ver & 0xF)

CLASS_DECL_AURA int32_t CPU_Is_InOrder();
CLASS_DECL_AURA int32_t CPU_Is_Aes_Supported();

#endif

