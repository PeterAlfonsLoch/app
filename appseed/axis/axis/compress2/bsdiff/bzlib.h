
/*-------------------------------------------------------------*/
/*--- Public header file for the library.                   ---*/
/*---                                               bzlib.h ---*/
/*-------------------------------------------------------------*/

/* ------------------------------------------------------------------
   This file is part of bzip2/libbzip2, a program and library for
   lossless, block-sorting data compression.

   bzip2/libbzip2 version 1.0.4 of 20 December 2006
   Copyright (C) 1996-2006 Julian Seward <jseward@bzip.org>

   Please read the WARNING, DISCLAIMER and PATENTS sections in the
   README file.

   This program is released under the terms of the license contained
   in the file LICENSE.
   ------------------------------------------------------------------ */

#pragma once


#ifndef _BZLIB_H
#define _BZLIB_H


#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define BZ_RUN               0
#define BZ_FLUSH             1
#define BZ_FINISH            2

#define BZ_OK                0
#define BZ_RUN_OK            1
#define BZ_FLUSH_OK          2
#define BZ_FINISH_OK         3
#define BZ_STREAM_END        4
#define BZ_SEQUENCE_ERROR    (-1)
#define BZ_PARAM_ERROR       (-2)
#define BZ_MEM_ERROR         (-3)
#define BZ_DATA_ERROR        (-4)
#define BZ_DATA_ERROR_MAGIC  (-5)
#define BZ_IO_ERROR          (-6)
#define BZ_UNEXPECTED_EOF    (-7)
#define BZ_OUTBUFF_FULL      (-8)
#define BZ_CONFIG_ERROR      (-9)

typedef
   struct {
      char *next_in;
      uint32_t avail_in;
      uint32_t total_in_lo32;
      uint32_t total_in_hi32;

      char *next_out;
      uint32_t avail_out;
      uint32_t total_out_lo32;
      uint32_t total_out_hi32;

      void *state;

      void *(*bzalloc)(void *,int32_t,int32_t);
      void (*bzfree)(void *,void *);
      void *opaque;
   }
   bz_stream;


#ifndef BZ_IMPORT
#define BZ_EXPORT
#endif


#ifdef _WIN32
//#   include <windows.h>
#   ifdef small
      /* windows.h define small to char */
#      undef small
#   endif
/*#ifdef BZ_DLL
#   define BZ_API(func) WINAPI func
#   define BZ_EXTERN __declspec(dllexport)
#elif defined(USE_BZ_DLL)
#   define BZ_API(func) WINAPI func
#   define BZ_EXTERN __declspec(dllimport)
#elif defined(BZ_EXPORT)
#   define BZ_API(func) WINAPI func
#   define BZ_EXTERN extern
#else
   /* import windows dll dynamically */
/*#   define BZ_API(func) (WINAPI * func)
#   define BZ_EXTERN
#endif
#else
#   define BZ_API(func) func
#   define BZ_EXTERN extern*/
#endif

#define BZ_API(func)  func
#define BZ_EXTERN CLASS_DECL_AXIS


/*-- Core (low-level) library functions --*/

BZ_EXTERN int32_t BZ_API(BZ2_bzCompressInit) (
      bz_stream* strm,
      int32_t        blockSize100k,
      int32_t        verbosity,
      int32_t        workFactor
   );

BZ_EXTERN int32_t BZ_API(BZ2_bzCompress) (
      bz_stream* strm,
      int32_t action
   );

BZ_EXTERN int32_t BZ_API(BZ2_bzCompressEnd) (
      bz_stream* strm
   );

BZ_EXTERN int32_t BZ_API(BZ2_bzDecompressInit) (
      bz_stream *strm,
      int32_t       verbosity,
      bool       small
   );

BZ_EXTERN int32_t BZ_API(BZ2_bzDecompress) (
      bz_stream* strm
   );

BZ_EXTERN int32_t BZ_API(BZ2_bzDecompressEnd) (
      bz_stream *strm
   );



/*-- High(er) level library functions --*/

#ifndef BZ_NO_STDIO
#define BZ_MAX_UNUSED 5000

#define BZFILE void

BZ_EXTERN BZFILE* BZ_API(BZ2_bzReadOpen) (
      int32_t*  bzerror,
      _FILE * f,
      int32_t   verbosity,
      bool   small,
      void * unused,
      int32_t   nUnused
   );

BZ_EXTERN void BZ_API(BZ2_bzReadClose) (
      int32_t*    bzerror,
      BZFILE* b
   );

BZ_EXTERN void BZ_API(BZ2_bzReadGetUnused) (
      int32_t*    bzerror,
      BZFILE* b,
      void **  unused,
      int32_t*    nUnused
   );

BZ_EXTERN int32_t BZ_API(BZ2_bzRead) (
      int32_t*    bzerror,
      BZFILE* b,
      void *   buf,
      int32_t     len
   );

BZ_EXTERN BZFILE* BZ_API(BZ2_bzWriteOpen) (
      int32_t*  bzerror,
      _FILE * f,
      int32_t   blockSize100k,
      int32_t   verbosity,
      int32_t   workFactor
   );

BZ_EXTERN void BZ_API(BZ2_bzWrite) (
      int32_t*    bzerror,
      BZFILE* b,
      void *   buf,
      int32_t     len
   );

BZ_EXTERN void BZ_API(BZ2_bzWriteClose) (
      int32_t*          bzerror,
      BZFILE*       b,
      int32_t           abandon,
      uint32_t* nbytes_in,
      uint32_t* nbytes_out
   );

BZ_EXTERN void BZ_API(BZ2_bzWriteClose64) (
      int32_t*          bzerror,
      BZFILE*       b,
      int32_t           abandon,
      uint32_t* nbytes_in_lo32,
      uint32_t* nbytes_in_hi32,
      uint32_t* nbytes_out_lo32,
      uint32_t* nbytes_out_hi32
   );
#endif


/*-- Utility functions --*/

BZ_EXTERN int32_t BZ_API(BZ2_bzBuffToBuffCompress) (
      char*         dest,
      uint32_t* destLen,
      char*         source,
      uint32_t  sourceLen,
      int32_t           blockSize100k,
      int32_t           verbosity,
      int32_t           workFactor
   );

BZ_EXTERN int32_t BZ_API(BZ2_bzBuffToBuffDecompress) (
      char*         dest,
      uint32_t* destLen,
      char*         source,
      uint32_t  sourceLen,
      bool           small,
      int32_t           verbosity
   );


/*--
   Code contributed by Yoshioka Tsuneo (tsuneo@rr.iij4u.or.jp)
   to support better zlib compatibility.
   This code is not _officially_ part of libbzip2 (yet);
   I haven't tested it, documented it, or considered the
   threading-safeness of it.
   If this code breaks, please contact both Yoshioka and me.
--*/

BZ_EXTERN const char * BZ_API(BZ2_bzlibVersion) (
      void
   );

#ifndef BZ_NO_STDIO
BZ_EXTERN BZFILE * BZ_API(BZ2_bzopen) (
      const char *path,
      const char *mode
   );

BZ_EXTERN BZFILE * BZ_API(BZ2_bzdopen) (
      int32_t        fd,
      const char *mode
   );

BZ_EXTERN int32_t BZ_API(BZ2_bzread) (
      BZFILE* b,
      void * buf,
      int32_t len
   );

BZ_EXTERN int32_t BZ_API(BZ2_bzwrite) (
      BZFILE* b,
      void *   buf,
      int32_t     len
   );

BZ_EXTERN int32_t BZ_API(BZ2_bzflush) (
      BZFILE* b
   );

BZ_EXTERN void BZ_API(BZ2_bzclose) (
      BZFILE* b
   );

BZ_EXTERN const char * BZ_API(BZ2_bzerror) (
      BZFILE *b,
      int32_t    *errnum
   );
#endif

#ifdef __cplusplus
}
#endif

#endif

/*-------------------------------------------------------------*/
/*--- end                                           bzlib.h ---*/
/*-------------------------------------------------------------*/
