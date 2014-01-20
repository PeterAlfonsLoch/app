/********************************************************************
 *                                                                  *
 * THIS FILE IS PART OF THE OggVorbis SOFTWARE CODEC SOURCE CODE.   *
 * USE, DISTRIBUTION AND REPRODUCTION OF THIS LIBRARY SOURCE IS     *
 * GOVERNED BY A BSD-STYLE SOURCE LICENSE INCLUDED WITH THIS SOURCE *
 * IN 'COPYING'. PLEASE READ THESE TERMS BEFORE DISTRIBUTING.       *
 *                                                                  *
 * THE OggVorbis SOURCE CODE IS (C) COPYRIGHT 1994-2001             *
 * by the Xiph.Org Foundation http://www.xiph.org/                  *

 ********************************************************************

 function: libvorbis codec headers
 last mod: $Id: codec.h 17021 2010-03-24 09:29:41Z xiphmont $

 ********************************************************************/

#ifndef _vorbis_codec_h_
#define _vorbis_codec_h_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include <ogg/ogg.h>

   



   struct codec_setup_info;

   struct private_state;


typedef struct vorbis_info{
  int32_t version;
  int32_t channels;
  long rate;

  /* The below bitrate declarations are *hints*.
     Combinations of the three values carry the following implications:

     all three set to the same value:
       implies a fixed rate bitstream
     only nominal set:
       implies a VBR stream that averages the nominal bitrate.  No hard
       upper/lower limit
     upper and or lower set:
       implies a VBR bitstream that obeys the bitrate limits. nominal
       may also be set to give a nominal rate.
     none set:
       the coder does not care to speculate.
  */

  long bitrate_upper;
  long bitrate_nominal;
  long bitrate_lower;
  long bitrate_window;

  codec_setup_info * codec_setup;
} vorbis_info;

/* vorbis_dsp_state buffers the current vorbis audio
   analysis/synthesis state.  The DSP state belongs to a specific
   logical bitstream ****************************************************/
typedef struct vorbis_dsp_state{
  int32_t analysisp;
  vorbis_info *vi;

  float **pcm;
  float **pcmret;
  int32_t      pcm_storage;
  int32_t      pcm_current;
  int32_t      pcm_returned;

  int32_t  preextrapolate;
  int32_t  eofflag;

  long lW;
  long W;
  long nW;
  long centerW;

  int64_t granulepos;
  int64_t sequence;

  int64_t glue_bits;
  int64_t time_bits;
  int64_t floor_bits;
  int64_t res_bits;

  private_state       *backend_state;
} vorbis_dsp_state;

typedef struct vorbis_block{
  /* necessary stream state for linking to the framing abstraction */
  float  **pcm;       /* this is a pointer into local storage */
  oggpack_buffer opb;

  long  lW;
  long  W;
  long  nW;
  int32_t   pcmend;
  int32_t   mode;

  int32_t         eofflag;
  int64_t granulepos;
  int64_t sequence;
  vorbis_dsp_state *vd; /* For read-only access of configuration */

  /* local storage to avoid remallocing; it's up to the mapping to
     structure it */
  void               *localstore;
  long                localtop;
  long                localalloc;
  long                totaluse;
  struct alloc_chain *reap;

  /* bitmetrics for the frame */
  long glue_bits;
  long time_bits;
  long floor_bits;
  long res_bits;

  void *internal;

} vorbis_block;

/* vorbis_block is a single block of data to be processed as part of
the analysis/synthesis stream; it belongs to a specific logical
bitstream, but is independent from other vorbis_blocks belonging to
that logical bitstream. *************************************************/

struct alloc_chain{
  void *ptr;
  struct alloc_chain *next;
};

/* vorbis_info contains all the setup information specific to the
   specific compression/decompression mode in progress (eg,
   psychoacoustic settings, channel setup, options, codebook
   etc). vorbis_info and substructures are in backends.h.
*********************************************************************/

/* the comments are not part of vorbis_info so that vorbis_info can be
   static storage */
typedef struct vorbis_comment{
  /* unlimited user comment fields.  libvorbis writes 'libvorbis'
     whatever vendor is set to in encode */
  char **user_comments;
  int32_t   *comment_lengths;
  int32_t    comments;
  char  *vendor;

} vorbis_comment;


/* libvorbis encodes in two abstraction layers; first we perform DSP
   and produce a packet (see docs/analysis.txt).  The packet is then
   coded into a framed OggSquish bitstream by the second layer (see
   docs/framing.txt).  Decode is the reverse process; we sync/frame
   the bitstream and extract individual packets, then decode the
   packet back into PCM audio.

   The extra framing/packetizing is used in streaming formats, such as
   files.  Over the net (such as with UDP), the framing and
   packetization aren't necessary as they're provided by the transport
   and the streaming layer is not used */

/* Vorbis PRIMITIVES: general ***************************************/

void     vorbis_info_init(vorbis_info *vi);
void     vorbis_info_clear(vorbis_info *vi);
int32_t      vorbis_info_blocksize(vorbis_info *vi,int32_t zo);
void     vorbis_comment_init(vorbis_comment *vc);
void     vorbis_comment_add(vorbis_comment *vc, const char *comment);
void     vorbis_comment_add_tag(vorbis_comment *vc,
                                       const char *tag, const char *contents);
char    *vorbis_comment_query(vorbis_comment *vc, const char *tag, int32_t count);
extern int32_t      vorbis_comment_query_count(vorbis_comment *vc, const char *tag);
extern void     vorbis_comment_clear(vorbis_comment *vc);

extern int32_t      vorbis_block_init(vorbis_dsp_state *v, vorbis_block *vb);
extern int32_t      vorbis_block_clear(vorbis_block *vb);
extern void     vorbis_dsp_clear(vorbis_dsp_state *v);
extern double   vorbis_granule_time(vorbis_dsp_state *v,
                                    int64_t granulepos);

extern const char *vorbis_version_string();

/* Vorbis PRIMITIVES: analysis/DSP layer ****************************/

extern int32_t      vorbis_analysis_init(vorbis_dsp_state *v,vorbis_info *vi);
extern int32_t      vorbis_commentheader_out(vorbis_comment *vc, ogg_packet *op);
extern int32_t      vorbis_analysis_headerout(vorbis_dsp_state *v,
                                          vorbis_comment *vc,
                                          ogg_packet *op,
                                          ogg_packet *op_comm,
                                          ogg_packet *op_code);
extern float  **vorbis_analysis_buffer(vorbis_dsp_state *v,int32_t vals);
extern int32_t      vorbis_analysis_wrote(vorbis_dsp_state *v,int32_t vals);
extern int32_t      vorbis_analysis_blockout(vorbis_dsp_state *v,vorbis_block *vb);
extern int32_t      vorbis_analysis(vorbis_block *vb,ogg_packet *op);

extern int32_t      vorbis_bitrate_addblock(vorbis_block *vb);
extern int32_t      vorbis_bitrate_flushpacket(vorbis_dsp_state *vd,
                                           ogg_packet *op);

/* Vorbis PRIMITIVES: synthesis layer *******************************/
extern int32_t      vorbis_synthesis_idheader(ogg_packet *op);
extern int32_t      vorbis_synthesis_headerin(vorbis_info *vi,vorbis_comment *vc,
                                          ogg_packet *op);

extern int32_t      vorbis_synthesis_init(vorbis_dsp_state *v,vorbis_info *vi);
extern int32_t      vorbis_synthesis_restart(vorbis_dsp_state *v);
extern int32_t      vorbis_synthesis(vorbis_block *vb,ogg_packet *op);
extern int32_t      vorbis_synthesis_trackonly(vorbis_block *vb,ogg_packet *op);
extern int32_t      vorbis_synthesis_blockin(vorbis_dsp_state *v,vorbis_block *vb);
extern int32_t      vorbis_synthesis_pcmout(vorbis_dsp_state *v,float ***pcm);
extern int32_t      vorbis_synthesis_lapout(vorbis_dsp_state *v,float ***pcm);
extern int32_t      vorbis_synthesis_read(vorbis_dsp_state *v,int32_t samples);
extern long     vorbis_packet_blocksize(vorbis_info *vi,ogg_packet *op);

extern int32_t      vorbis_synthesis_halfrate(vorbis_info *v,int32_t flag);
extern int32_t      vorbis_synthesis_halfrate_p(vorbis_info *v);

/* Vorbis ERRORS and return codes ***********************************/

#define OV_FALSE      -1
#define OV_EOF        -2
#define OV_HOLE       -3

#define OV_EREAD      -128
#define OV_EFAULT     -129
#define OV_EIMPL      -130
#define OV_EINVAL     -131
#define OV_ENOTVORBIS -132
#define OV_EBADHEADER -133
#define OV_EVERSION   -134
#define OV_ENOTAUDIO  -135
#define OV_EBADPACKET -136
#define OV_EBADLINK   -137
#define OV_ENOSEEK    -138

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

