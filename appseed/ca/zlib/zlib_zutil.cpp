/* zutil.c -- target dependent utility functions for the compression library
 * Copyright (C) 1995-2005 Jean-loup Gailly.
 * For conditions of distribution and use, see copyright notice in zlib.h
 */

/* @(#) $Id$ */
#include "framework.h"



#include "zutil.h"

#ifndef NO_DUMMY_DECL
struct internal_state      {int32_t dummy;}; /* for buggy compilers */
#endif

const char * const z_errmsg[10] = {
"need dictionary",     /* Z_NEED_DICT       2  */
"stream end",          /* Z_STREAM_END      1  */
"",                    /* Z_OK              0  */
"file error",          /* Z_ERRNO         (-1) */
"stream error",        /* Z_STREAM_ERROR  (-2) */
"data error",          /* Z_DATA_ERROR    (-3) */
"insufficient primitive::memory", /* Z_MEM_ERROR     (-4) */
"buffer error",        /* Z_BUF_ERROR     (-5) */
"incompatible version",/* Z_VERSION_ERROR (-6) */
""};


const char * ZEXPORT zlibVersion()
{
    return ZLIB_VERSION;
}

uint_ptr ZEXPORT zlibCompileFlags()
{
    uint_ptr flags;

    flags = 0;
    switch (sizeof(uint32_t)) {
    case 2:     break;
    case 4:     flags += 1;     break;
    case 8:     flags += 2;     break;
    default:    flags += 3;
    }
    switch (sizeof(uint_ptr)) {
    case 2:     break;
    case 4:     flags += 1 << 2;        break;
    case 8:     flags += 2 << 2;        break;
    default:    flags += 3 << 2;
    }
    switch (sizeof(voidpf)) {
    case 2:     break;
    case 4:     flags += 1 << 4;        break;
    case 8:     flags += 2 << 4;        break;
    default:    flags += 3 << 4;
    }
    switch (sizeof(z_off_t)) {
    case 2:     break;
    case 4:     flags += 1 << 6;        break;
    case 8:     flags += 2 << 6;        break;
    default:    flags += 3 << 6;
    }
#ifdef DEBUG
    flags += 1 << 8;
#endif
#if defined(ASMV) || defined(ASMINF)
    flags += 1 << 9;
#endif
#ifdef ZLIB_WINAPI
    flags += 1 << 10;
#endif
#ifdef BUILDFIXED
    flags += 1 << 12;
#endif
#ifdef DYNAMIC_CRC_TABLE
    flags += 1 << 13;
#endif
#ifdef NO_GZCOMPRESS
    flags += 1L << 16;
#endif
#ifdef NO_GZIP
    flags += 1L << 17;
#endif
#ifdef PKZIP_BUG_WORKAROUND
    flags += 1L << 20;
#endif
#ifdef FASTEST
    flags += 1L << 21;
#endif
#ifdef STDC
#  ifdef NO_vsnprintf
        flags += 1L << 25;
#    ifdef HAS_vsprintf_void
        flags += 1L << 26;
#    endif
#  else
#    ifdef HAS_vsnprintf_void
        flags += 1L << 26;
#    endif
#  endif
#else
        flags += 1L << 24;
#  ifdef NO_snprintf
        flags += 1L << 25;
#    ifdef HAS_sprintf_void
        flags += 1L << 26;
#    endif
#  else
#    ifdef HAS_snprintf_void
        flags += 1L << 26;
#    endif
#  endif
#endif
    return flags;
}

#ifdef DEBUG

#  ifndef verbose
#    define verbose 0
#  endif
int32_t z_verbose = verbose;

void z_error (const char *m)
{
    fprintf(stderr, "%s\n", m);
    exit(1);
}
#endif

/* exported to allow conversion of error code to string for compress() and
 * uncompress()
 */
const char * ZEXPORT zError(
    int32_t err)
{
    return ERR_MSG(err);
}

#if defined(_WIN32_WCE)
    /* The Microsoft C Run-Time Library for Windows CE doesn't have
     * errno.  We define it as a global var to simplify porting.
     * Its value is always 0 and should not be used.
     */
    int32_t errno = 0;
#endif

#ifndef HAVE_MEMCPY

void zmemcpy(dest, source, len)
    byte* dest;
    const byte* source;
    uint32_t  len;
{
    if (len == 0) return;
    do {
        *dest++ = *source++; /* ??? to be unrolled */
    } while (--len != 0);
}

int32_t zmemcmp(s1, s2, len)
    const byte* s1;
    const byte* s2;
    uint32_t  len;
{
    uint32_t j;

    for (j = 0; j < len; j++) {
        if (s1[j] != s2[j]) return 2*(s1[j] > s2[j])-1;
    }
    return 0;
}

void zmemzero(dest, len)
    byte* dest;
    uint32_t  len;
{
    if (len == 0) return;
    do {
        *dest++ = 0;  /* ??? to be unrolled */
    } while (--len != 0);
}
#endif


#ifdef SYS16BIT

#ifdef __TURBOC__
/* Turbo C in 16-bit mode */

#  define MY_ZCALLOC

/* Turbo C malloc() does not allow dynamic allocation of 64K bytes
 * and farmalloc(64K) returns a pointer with an offset of 8, so we
 * must fix the pointer. Warning: the pointer must be put back to its
 * original form in order to free it, use zcfree().
 */

#define MAX_PTR 10
/* 10*64K = 640K */

zlib_local int32_t next_ptr = 0;

typedef struct ptr_table_s {
    voidpf org_ptr;
    voidpf new_ptr;
} ptr_table;

zlib_local ptr_table table[MAX_PTR];
/* This table is used to remember the original form of pointers
 * to large buffers (64K). Such pointers are normalized with a zero offset.
 * Since MSDOS is not a preemptive multitasking OS, this table is not
 * protected from concurrent access. This hack doesn't work anyway on
 * a protected system like OS/2. Use Microsoft C instead.
 */

voidpf zcalloc (voidpf opaque, uint32_t items, uint32_t size)
{
    voidpf buf = opaque; /* just to make some compilers happy */
    uint32_t bsize = (uint32_t)items*size;

    /* If we allocate less than 65520 bytes, we assume that farmalloc
     * will return a usable pointer which doesn't have to be normalized.
     */
    if (bsize < 65520L) {
        buf = farmalloc(bsize);
        if (*(uint16_t*)&buf != 0) return buf;
    } else {
        buf = farmalloc(bsize + 16L);
    }
    if (buf == NULL || next_ptr >= MAX_PTR) return NULL;
    table[next_ptr].org_ptr = buf;

    /* Normalize the pointer to seg:0 */
    *((uint16_t*)&buf+1) += ((uint16_t)((uchar*)buf-0) + 15) >> 4;
    *(uint16_t*)&buf = 0;
    table[next_ptr++].new_ptr = buf;
    return buf;
}

void  zcfree (voidpf opaque, voidpf ptr)
{
    int32_t n;
    if (*(uint16_t*)&ptr != 0) { /* object < 64K */
        farfree(ptr);
        return;
    }
    /* find the original pointer */
    for (n = 0; n < next_ptr; n++) {
        if (ptr != table[n].new_ptr) continue;

        farfree(table[n].org_ptr);
        while (++n < next_ptr) {
            table[n-1] = table[n];
        }
        next_ptr--;
        return;
    }
    ptr = opaque; /* just to make some compilers happy */
    Assert(0, "zcfree: ptr not found");
}

#endif /* __TURBOC__ */


#ifdef M_I86
/* Microsoft C in 16-bit mode */

#  define MY_ZCALLOC

#if (!defined(_MSC_VER) || (_MSC_VER <= 600))
#  define _halloc  halloc
#  define _hfree   hfree
#endif

voidpf zcalloc (voidpf opaque, uint32_t items, uint32_t size)
{
    if (opaque) opaque = 0; /* to make compiler happy */
    return _halloc((long)items, size);
}

void  zcfree (voidpf opaque, voidpf ptr)
{
    if (opaque) opaque = 0; /* to make compiler happy */
    _hfree(ptr);
}

#endif /* M_I86 */

#endif /* SYS16BIT */


#ifndef MY_ZCALLOC /* Any system without a special alloc function */

#ifndef STDC
extern voidp  malloc OF((uint32_t size));
extern voidp  calloc OF((uint32_t items, uint32_t size));
extern void   free   OF((voidpf ptr));
#endif

voidpf zcalloc (
    voidpf opaque,
    uint32_t items,
    uint32_t size)
{
    if (opaque) items += size - size; /* make compiler happy */
    return sizeof(uint32_t) > 2 ? (voidpf)malloc(items * size) :
                              (voidpf)calloc(items, size);
}

void  zcfree (
    voidpf opaque,
    voidpf ptr)
{
    free(ptr);
    if (opaque) return; /* make compiler happy */
}

#endif /* MY_ZCALLOC */
