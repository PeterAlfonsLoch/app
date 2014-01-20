/********************************************************************
 *                                                                  *
 * THIS FILE IS PART OF THE OggVorbis SOFTWARE CODEC SOURCE CODE.   *
 * USE, DISTRIBUTION AND REPRODUCTION OF THIS LIBRARY SOURCE IS     *
 * GOVERNED BY A BSD-STYLE SOURCE LICENSE INCLUDED WITH THIS SOURCE *
 * IN 'COPYING'. PLEASE READ THESE TERMS BEFORE DISTRIBUTING.       *
 *                                                                  *
 * THE OggVorbis SOURCE CODE IS (C) COPYRIGHT 1994-2007             *
 * by the Xiph.Org Foundation http://www.xiph.org/                  *
 *                                                                  *
 ********************************************************************

 function: toplevel libogg include
 last mod: $Id: ogg.h 18044 2011-08-01 17:55:20Z gmaxwell $

 ********************************************************************/
#ifndef _OGG_H
#define _OGG_H

#include "base/base/base/base.h"

#include <string.h>
#include <stdlib.h>
#include <limits.h>


#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <ogg/os_types.h>

typedef struct {
  void *iov_base;
  size_t iov_len;
} ogg_iovec_t;

typedef struct {
  long endbyte;
  int32_t  endbit;

  uchar *buffer;
  uchar *ptr;
  long storage;
} oggpack_buffer;

/* ogg_page is used to encapsulate the data in one Ogg bitstream page *****/

typedef struct {
  uchar *header;
  long header_len;
  uchar *body;
  long body_len;
} ogg_page;

/* ogg_stream_state contains the current encode/decode state of a logical
   Ogg bitstream **********************************************************/

typedef struct {
  uchar   *body_data;    /* bytes from packet bodies */
  long    body_storage;          /* storage elements allocated */
  long    body_fill;             /* elements stored; fill mark */
  long    body_returned;         /* elements of fill returned */


  int32_t     *lacing_vals;      /* The values that will go to the segment table */
  int64_t *granule_vals; /* granulepos values for headers. Not compact
                                this way, but it is simple coupled to the
                                lacing fifo */
  long    lacing_storage;
  long    lacing_fill;
  long    lacing_packet;
  long    lacing_returned;

  uchar    header[282];      /* working space for header encode */
  int32_t              header_fill;

  int32_t     e_o_s;          /* set when we have buffered the last packet in the
                             logical bitstream */
  int32_t     b_o_s;          /* set after we've written the initial page
                             of a logical bitstream */
  long    serialno;
  long    pageno;
  int64_t  packetno;  /* sequence number for decode; the framing
                             knows where there's a hole in the data,
                             but we need coupling so that the codec
                             (which is in a separate abstraction
                             layer) also knows about the gap */
  int64_t   granulepos;

} ogg_stream_state;

/* ogg_packet is used to encapsulate the data and metadata belonging
   to a single raw Ogg/Vorbis packet *************************************/

typedef struct {
  uchar *packet;
  long  bytes;
  long  b_o_s;
  long  e_o_s;

  int64_t  granulepos;

  int64_t  packetno;     /* sequence number for decode; the framing
                                knows where there's a hole in the data,
                                but we need coupling so that the codec
                                (which is in a separate abstraction
                                layer) also knows about the gap */
} ogg_packet;

typedef struct {
  uchar *data;
  int32_t storage;
  int32_t fill;
  int32_t returned;

  int32_t unsynced;
  int32_t headerbytes;
  int32_t bodybytes;
} ogg_sync_state;

/* Ogg BITSTREAM PRIMITIVES: bitstream ************************/

extern void  oggpack_writeinit(oggpack_buffer *b);
extern int32_t   oggpack_writecheck(oggpack_buffer *b);
extern void  oggpack_writetrunc(oggpack_buffer *b,long bits);
extern void  oggpack_writealign(oggpack_buffer *b);
extern void  oggpack_writecopy(oggpack_buffer *b,void *source,long bits);
extern void  oggpack_reset(oggpack_buffer *b);
extern void  oggpack_writeclear(oggpack_buffer *b);
extern void  oggpack_readinit(oggpack_buffer *b,uchar *buf,int32_t bytes);
extern void  oggpack_write(oggpack_buffer *b,uint_ptr value,int32_t bits);
extern long  oggpack_look(oggpack_buffer *b,int32_t bits);
extern long  oggpack_look1(oggpack_buffer *b);
extern void  oggpack_adv(oggpack_buffer *b,int32_t bits);
extern void  oggpack_adv1(oggpack_buffer *b);
extern long  oggpack_read(oggpack_buffer *b,int32_t bits);
extern long  oggpack_read1(oggpack_buffer *b);
extern long  oggpack_bytes(oggpack_buffer *b);
extern long  oggpack_bits(oggpack_buffer *b);
extern uchar *oggpack_get_buffer(oggpack_buffer *b);

extern void  oggpackB_writeinit(oggpack_buffer *b);
extern int32_t   oggpackB_writecheck(oggpack_buffer *b);
extern void  oggpackB_writetrunc(oggpack_buffer *b,long bits);
extern void  oggpackB_writealign(oggpack_buffer *b);
extern void  oggpackB_writecopy(oggpack_buffer *b,void *source,long bits);
extern void  oggpackB_reset(oggpack_buffer *b);
extern void  oggpackB_writeclear(oggpack_buffer *b);
extern void  oggpackB_readinit(oggpack_buffer *b,uchar *buf,int32_t bytes);
extern void  oggpackB_write(oggpack_buffer *b,uint_ptr value,int32_t bits);
extern long  oggpackB_look(oggpack_buffer *b,int32_t bits);
extern long  oggpackB_look1(oggpack_buffer *b);
extern void  oggpackB_adv(oggpack_buffer *b,int32_t bits);
extern void  oggpackB_adv1(oggpack_buffer *b);
extern long  oggpackB_read(oggpack_buffer *b,int32_t bits);
extern long  oggpackB_read1(oggpack_buffer *b);
extern long  oggpackB_bytes(oggpack_buffer *b);
extern long  oggpackB_bits(oggpack_buffer *b);
extern uchar *oggpackB_get_buffer(oggpack_buffer *b);

/* Ogg BITSTREAM PRIMITIVES: encoding **************************/

extern int32_t      ogg_stream_packetin(ogg_stream_state *os, ogg_packet *op);
extern int32_t      ogg_stream_iovecin(ogg_stream_state *os, ogg_iovec_t *iov,
                                   int32_t count, long e_o_s, int64_t granulepos);
extern int32_t      ogg_stream_pageout(ogg_stream_state *os, ogg_page *og);
extern int32_t      ogg_stream_pageout_fill(ogg_stream_state *os, ogg_page *og, int32_t nfill);
extern int32_t      ogg_stream_flush(ogg_stream_state *os, ogg_page *og);
extern int32_t      ogg_stream_flush_fill(ogg_stream_state *os, ogg_page *og, int32_t nfill);

/* Ogg BITSTREAM PRIMITIVES: decoding **************************/

extern int32_t      ogg_sync_init(ogg_sync_state *oy);
extern int32_t      ogg_sync_clear(ogg_sync_state *oy);
extern int32_t      ogg_sync_reset(ogg_sync_state *oy);
extern int32_t      ogg_sync_destroy(ogg_sync_state *oy);
extern int32_t      ogg_sync_check(ogg_sync_state *oy);

extern char    *ogg_sync_buffer(ogg_sync_state *oy, long size);
extern int32_t      ogg_sync_wrote(ogg_sync_state *oy, long bytes);
extern long     ogg_sync_pageseek(ogg_sync_state *oy,ogg_page *og);
extern int32_t      ogg_sync_pageout(ogg_sync_state *oy, ogg_page *og);
extern int32_t      ogg_stream_pagein(ogg_stream_state *os, ogg_page *og);
extern int32_t      ogg_stream_packetout(ogg_stream_state *os,ogg_packet *op);
extern int32_t      ogg_stream_packetpeek(ogg_stream_state *os,ogg_packet *op);

/* Ogg BITSTREAM PRIMITIVES: general ***************************/

extern int32_t      ogg_stream_init(ogg_stream_state *os,int32_t serialno);
extern int32_t      ogg_stream_clear(ogg_stream_state *os);
extern int32_t      ogg_stream_reset(ogg_stream_state *os);
extern int32_t      ogg_stream_reset_serialno(ogg_stream_state *os,int32_t serialno);
extern int32_t      ogg_stream_destroy(ogg_stream_state *os);
extern int32_t      ogg_stream_check(ogg_stream_state *os);
extern int32_t      ogg_stream_eos(ogg_stream_state *os);

extern void     ogg_page_checksum_set(ogg_page *og);

extern int32_t      ogg_page_version(const ogg_page *og);
extern int32_t      ogg_page_continued(const ogg_page *og);
extern int32_t      ogg_page_bos(const ogg_page *og);
extern int32_t      ogg_page_eos(const ogg_page *og);
extern int64_t  ogg_page_granulepos(const ogg_page *og);
extern int32_t      ogg_page_serialno(const ogg_page *og);
extern long     ogg_page_pageno(const ogg_page *og);
extern int32_t      ogg_page_packets(const ogg_page *og);

extern void     ogg_packet_clear(ogg_packet *op);


#ifdef __cplusplus
}
#endif

#endif  /* _OGG_H */
