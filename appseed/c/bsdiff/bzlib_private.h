
/*-------------------------------------------------------------*/
/*--- Private header _FILE for the library.                  ---*/
/*---                                       bzlib_private.h ---*/
/*-------------------------------------------------------------*/

/* ------------------------------------------------------------------
   This _FILE is part of bzip2/libbzip2, a program and library for
   lossless, block-sorting data compression.

   bzip2/libbzip2 version 1.0.4 of 20 December 2006
   Copyright (C) 1996-2006 Julian Seward <jseward@bzip.org>

   Please read the WARNING, DISCLAIMER and PATENTS sections in the
   README _FILE.

   This program is released under the terms of the license contained
   in the _FILE LICENSE.
   ------------------------------------------------------------------ */


#pragma once


#ifndef _BZLIB_PRIVATE_H
#define _BZLIB_PRIVATE_H

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif


#include "bzlib.h"



/*-- General stuff. --*/

#define BZ_VERSION  "1.0.4, 20-Dec-2006"

#undef Bool
#undef True
#undef False

typedef unsigned char   Bool;
typedef char            Char;
typedef unsigned char   UChar;
typedef int             int32;
typedef unsigned int    uint32;
typedef short           Int16;
typedef unsigned short  UInt16;




#define True   ((Bool) 1)
#define False  ((Bool) 0)




#ifndef __GNUC__
#define __inline__  /* */
#endif

#ifndef BZ_NO_STDIO

extern void BZ2_bz__AssertH__fail ( int errcode );
#define AssertH(cond,errcode) \
   { if (!(cond)) BZ2_bz__AssertH__fail ( errcode ); }

#if BZ_DEBUG
#define AssertD(cond,msg) \
   { if (!(cond)) {       \
      fprintf ( stderr_dup,   \
        "\n\nlibbzip2(debug build): internal error\n\t%s\n", msg );\
      exit(1); \
   }}
#else
#define AssertD(cond,msg) /* */
#endif

#define VPrintf0(zf)  \
   fprintf_dup(stderr_dup,zf)
#define VPrintf1(zf,za1) \
   fprintf_dup(stderr_dup,zf,za1)
#define VPrintf2(zf,za1,za2) \
   fprintf_dup(stderr_dup,zf,za1,za2)
#define VPrintf3(zf,za1,za2,za3) \
   fprintf_dup(stderr_dup,zf,za1,za2,za3)
#define VPrintf4(zf,za1,za2,za3,za4) \
   fprintf_dup(stderr_dup,zf,za1,za2,za3,za4)
#define VPrintf5(zf,za1,za2,za3,za4,za5) \
   fprintf_dup(stderr_dup,zf,za1,za2,za3,za4,za5)

#else

extern void bz_internal_error ( int errcode );
#define AssertH(cond,errcode) \
   { if (!(cond)) bz_internal_error ( errcode ); }
#define AssertD(cond,msg)                do { } while (0)
#define VPrintf0(zf)                     do { } while (0)
#define VPrintf1(zf,za1)                 do { } while (0)
#define VPrintf2(zf,za1,za2)             do { } while (0)
#define VPrintf3(zf,za1,za2,za3)         do { } while (0)
#define VPrintf4(zf,za1,za2,za3,za4)     do { } while (0)
#define VPrintf5(zf,za1,za2,za3,za4,za5) do { } while (0)

#endif


#define BZALLOC(nnn) (strm->bzalloc)(strm->opaque,(nnn),1)
#define BZFREE(ppp)  (strm->bzfree)(strm->opaque,(ppp))


/*-- Header bytes. --*/

#define BZ_HDR_B 0x42   /* 'B' */
#define BZ_HDR_Z 0x5a   /* 'Z' */
#define BZ_HDR_h 0x68   /* 'h' */
#define BZ_HDR_0 0x30   /* '0' */

/*-- Constants for the back end. --*/

#define BZ_MAX_ALPHA_SIZE 258
#define BZ_MAX_CODE_LEN    23

#define BZ_RUNA 0
#define BZ_RUNB 1

#define BZ_N_GROUPS 6
#define BZ_G_SIZE   50
#define BZ_N_ITERS  4

#define BZ_MAX_SELECTORS (2 + (900000 / BZ_G_SIZE))



/*-- Stuff for randomising repetitive blocks. --*/

extern int32 BZ2_rNums[512];

#define BZ_RAND_DECLS                          \
   int32 rNToGo;                               \
   int32 rTPos                                 \

#define BZ_RAND_INIT_MASK                      \
   s->rNToGo = 0;                              \
   s->rTPos  = 0                               \

#define BZ_RAND_MASK ((s->rNToGo == 1) ? 1 : 0)

#define BZ_RAND_UPD_MASK                       \
   if (s->rNToGo == 0) {                       \
      s->rNToGo = BZ2_rNums[s->rTPos];         \
      s->rTPos++;                              \
      if (s->rTPos == 512) s->rTPos = 0;       \
   }                                           \
   s->rNToGo--;



/*-- Stuff for doing CRCs. --*/

extern uint32 BZ2_crc32Table[256];

#define BZ_INITIALISE_CRC(crcVar)              \
{                                              \
   crcVar = 0xffffffffL;                       \
}

#define BZ_FINALISE_CRC(crcVar)                \
{                                              \
   crcVar = ~(crcVar);                         \
}

#define BZ_UPDATE_CRC(crcVar,cha)              \
{                                              \
   crcVar = (crcVar << 8) ^                    \
            BZ2_crc32Table[(crcVar >> 24) ^    \
                           ((UChar)cha)];      \
}



/*-- States and modes for compression. --*/

#define BZ_M_IDLE      1
#define BZ_M_RUNNING   2
#define BZ_M_FLUSHING  3
#define BZ_M_FINISHING 4

#define BZ_S_OUTPUT    1
#define BZ_S_INPUT     2

#define BZ_N_RADIX 2
#define BZ_N_QSORT 12
#define BZ_N_SHELL 18
#define BZ_N_OVERSHOOT (BZ_N_RADIX + BZ_N_QSORT + BZ_N_SHELL + 2)




/*-- Structure holding all the compression-side stuff. --*/

typedef
   struct {
      /* pointer back to the struct bz_stream */
      bz_stream* strm;

      /* mode this stream is in, and whether inputting */
      /* or outputting data */
      int32    mode;
      int32    state;

      /* remembers avail_in when flush/finish requested */
      uint32   avail_in_expect;

      /* for doing the block sorting */
      uint32*  arr1;
      uint32*  arr2;
      uint32*  ftab;
      int32    origPtr;

      /* aliases for arr1 and arr2 */
      uint32*  ptr;
      UChar*   block;
      UInt16*  mtfv;
      UChar*   zbits;

      /* for deciding when to use the fallback sorting algorithm */
      int32    workFactor;

      /* run-length-encoding of the input */
      uint32   state_in_ch;
      int32    state_in_len;
      BZ_RAND_DECLS;

      /* input and output limits and current posns */
      int32    nblock;
      int32    nblockMAX;
      int32    numZ;
      int32    state_out_pos;

      /* map of bytes used in block */
      int32    nInUse;
      Bool     inUse[256];
      UChar    unseqToSeq[256];

      /* the buffer for bit stream creation */
      uint32   bsBuff;
      int32    bsLive;

      /* block and combined CRCs */
      uint32   blockCRC;
      uint32   combinedCRC;

      /* misc administratium */
      int32    verbosity;
      int32    blockNo;
      int32    blockSize100k;

      /* stuff for coding the MTF values */
      int32    nMTF;
      int32    mtfFreq    [BZ_MAX_ALPHA_SIZE];
      UChar    selector   [BZ_MAX_SELECTORS];
      UChar    selectorMtf[BZ_MAX_SELECTORS];

      UChar    len     [BZ_N_GROUPS][BZ_MAX_ALPHA_SIZE];
      int32    code    [BZ_N_GROUPS][BZ_MAX_ALPHA_SIZE];
      int32    rfreq   [BZ_N_GROUPS][BZ_MAX_ALPHA_SIZE];
      /* second dimension: only 3 needed; 4 makes index calculations faster */
      uint32   len_pack[BZ_MAX_ALPHA_SIZE][4];

   }
   e_state;



/*-- externs for compression. --*/

extern void
BZ2_blockSort ( e_state* );

extern void
BZ2_compressBlock ( e_state*, Bool );

extern void
BZ2_bsInitWrite ( e_state* );

extern void
BZ2_hbAssignCodes ( int32*, UChar*, int32, int32, int32 );

extern void
BZ2_hbMakeCodeLengths ( UChar*, int32*, int32, int32 );



/*-- states for decompression. --*/

#define BZ_X_IDLE        1
#define BZ_X_OUTPUT      2

#define BZ_X_MAGIC_1     10
#define BZ_X_MAGIC_2     11
#define BZ_X_MAGIC_3     12
#define BZ_X_MAGIC_4     13
#define BZ_X_BLKHDR_1    14
#define BZ_X_BLKHDR_2    15
#define BZ_X_BLKHDR_3    16
#define BZ_X_BLKHDR_4    17
#define BZ_X_BLKHDR_5    18
#define BZ_X_BLKHDR_6    19
#define BZ_X_BCRC_1      20
#define BZ_X_BCRC_2      21
#define BZ_X_BCRC_3      22
#define BZ_X_BCRC_4      23
#define BZ_X_RANDBIT     24
#define BZ_X_ORIGPTR_1   25
#define BZ_X_ORIGPTR_2   26
#define BZ_X_ORIGPTR_3   27
#define BZ_X_MAPPING_1   28
#define BZ_X_MAPPING_2   29
#define BZ_X_SELECTOR_1  30
#define BZ_X_SELECTOR_2  31
#define BZ_X_SELECTOR_3  32
#define BZ_X_CODING_1    33
#define BZ_X_CODING_2    34
#define BZ_X_CODING_3    35
#define BZ_X_MTF_1       36
#define BZ_X_MTF_2       37
#define BZ_X_MTF_3       38
#define BZ_X_MTF_4       39
#define BZ_X_MTF_5       40
#define BZ_X_MTF_6       41
#define BZ_X_ENDHDR_2    42
#define BZ_X_ENDHDR_3    43
#define BZ_X_ENDHDR_4    44
#define BZ_X_ENDHDR_5    45
#define BZ_X_ENDHDR_6    46
#define BZ_X_CCRC_1      47
#define BZ_X_CCRC_2      48
#define BZ_X_CCRC_3      49
#define BZ_X_CCRC_4      50



/*-- Constants for the fast MTF decoder. --*/

#define MTFA_SIZE 4096
#define MTFL_SIZE 16



/*-- Structure holding all the decompression-side stuff. --*/

typedef
   struct {
      /* pointer back to the struct bz_stream */
      bz_stream* strm;

      /* state indicator for this stream */
      int32    state;

      /* for doing the final run-length decoding */
      UChar    state_out_ch;
      int32    state_out_len;
      Bool     blockRandomised;
      BZ_RAND_DECLS;

      /* the buffer for bit stream reading */
      uint32   bsBuff;
      int32    bsLive;

      /* misc administratium */
      int32    blockSize100k;
      Bool     smallDecompress;
      int32    currBlockNo;
      int32    verbosity;

      /* for undoing the Burrows-Wheeler transform */
      int32    origPtr;
      uint32   tPos;
      int32    k0;
      int32    unzftab[256];
      int32    nblock_used;
      int32    cftab[257];
      int32    cftabCopy[257];

      /* for undoing the Burrows-Wheeler transform (FAST) */
      uint32   *tt;

      /* for undoing the Burrows-Wheeler transform (SMALL) */
      UInt16   *ll16;
      UChar    *ll4;

      /* stored and calculated CRCs */
      uint32   storedBlockCRC;
      uint32   storedCombinedCRC;
      uint32   calculatedBlockCRC;
      uint32   calculatedCombinedCRC;

      /* map of bytes used in block */
      int32    nInUse;
      Bool     inUse[256];
      Bool     inUse16[16];
      UChar    seqToUnseq[256];

      /* for decoding the MTF values */
      UChar    mtfa   [MTFA_SIZE];
      int32    mtfbase[256 / MTFL_SIZE];
      UChar    selector   [BZ_MAX_SELECTORS];
      UChar    selectorMtf[BZ_MAX_SELECTORS];
      UChar    len  [BZ_N_GROUPS][BZ_MAX_ALPHA_SIZE];

      int32    limit  [BZ_N_GROUPS][BZ_MAX_ALPHA_SIZE];
      int32    base   [BZ_N_GROUPS][BZ_MAX_ALPHA_SIZE];
      int32    perm   [BZ_N_GROUPS][BZ_MAX_ALPHA_SIZE];
      int32    minLens[BZ_N_GROUPS];

      /* save area for scalars in the main decompress code */
      int32    save_i;
      int32    save_j;
      int32    save_t;
      int32    save_alphaSize;
      int32    save_nGroups;
      int32    save_nSelectors;
      int32    save_EOB;
      int32    save_groupNo;
      int32    save_groupPos;
      int32    save_nextSym;
      int32    save_nblockMAX;
      int32    save_nblock;
      int32    save_es;
      int32    save_N;
      int32    save_curr;
      int32    save_zt;
      int32    save_zn;
      int32    save_zvec;
      int32    save_zj;
      int32    save_gSel;
      int32    save_gMinlen;
      int32*   save_gLimit;
      int32*   save_gBase;
      int32*   save_gPerm;

   }
   DState;



/*-- Macros for decompression. --*/

#define BZ_GET_FAST(cccc)                     \
    s->tPos = s->tt[s->tPos];                 \
    cccc = (UChar)(s->tPos & 0xff);           \
    s->tPos >>= 8;

#define BZ_GET_FAST_C(cccc)                   \
    c_tPos = c_tt[c_tPos];                    \
    cccc = (UChar)(c_tPos & 0xff);            \
    c_tPos >>= 8;

#define SET_LL4(i,n)                                          \
   { if (((i) & 0x1) == 0)                                    \
        s->ll4[(i) >> 1] = (s->ll4[(i) >> 1] & 0xf0) | (n); else    \
        s->ll4[(i) >> 1] = (s->ll4[(i) >> 1] & 0x0f) | ((n) << 4);  \
   }

#define GET_LL4(i)                             \
   ((((uint32)(s->ll4[(i) >> 1])) >> (((i) << 2) & 0x4)) & 0xF)

#define SET_LL(i,n)                          \
   { s->ll16[i] = (UInt16)(n & 0x0000ffff);  \
     SET_LL4(i, n >> 16);                    \
   }

#define GET_LL(i) \
   (((uint32)s->ll16[i]) | (GET_LL4(i) << 16))

#define BZ_GET_SMALL(cccc)                            \
      cccc = BZ2_indexIntoF ( s->tPos, s->cftab );    \
      s->tPos = GET_LL(s->tPos);


/*-- externs for decompression. --*/

extern int32
BZ2_indexIntoF ( int32, int32* );

extern int32
BZ2_decompress ( DState* );

extern void
BZ2_hbCreateDecodeTables ( int32*, int32*, int32*, UChar*,
                           int32,  int32, int32 );


#endif


/*-- BZ_NO_STDIO seems to make NULL disappear on some platforms. --*/

#ifdef BZ_NO_STDIO
#ifndef NULL
#define NULL 0
#endif
#endif


/*-------------------------------------------------------------*/
/*--- end                                   bzlib_private.h ---*/
/*-------------------------------------------------------------*/
