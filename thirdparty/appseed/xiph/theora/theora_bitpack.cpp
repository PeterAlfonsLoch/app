/********************************************************************
 *                                                                  *
 * THIS FILE IS PART OF THE OggTheora SOFTWARE CODEC SOURCE CODE.   *
 * USE, DISTRIBUTION AND REPRODUCTION OF THIS LIBRARY SOURCE IS     *
 * GOVERNED BY A BSD-STYLE SOURCE LICENSE INCLUDED WITH THIS SOURCE *
 * IN 'COPYING'. PLEASE READ THESE TERMS BEFORE DISTRIBUTING.       *
 *                                                                  *
 * THE OggTheora SOURCE CODE IS (C) COPYRIGHT 1994-2009             *
 * by the Xiph.Org Foundation and contributors http://www.xiph.org/ *
 *                                                                  *
 ********************************************************************

  function: packing variable sized words into an octet stream
  last mod: $Id: bitpack.c 16503 2009-08-22 18:14:02Z giles $

 ********************************************************************/
#include "framework.h"

/*We're 'MSb' endian; if we write a word but read individual bits,
   then we'll read the MSb first.*/

void oc_pack_readinit(oc_pack_buf *_b,unsigned char *_buf,long _bytes){
  memset(_b,0,sizeof(*_b));
  _b->ptr=_buf;
  _b->stop=_buf+_bytes;
}

static oc_pb_window oc_pack_refill(oc_pack_buf *_b,int32_t _bits){
  const unsigned char *ptr;
  const unsigned char *stop;
  oc_pb_window         window;
  int32_t                  available;
  window=_b->window;
  available=_b->bits;
  ptr=_b->ptr;
  stop=_b->stop;
  while(available<=OC_PB_WINDOW_SIZE-8&&ptr<stop){
    available+=8;
    window|=(oc_pb_window)*ptr++<<(OC_PB_WINDOW_SIZE-available);
  }
  _b->ptr=ptr;
  if(_bits>available){
    if(ptr>=stop){
      _b->eof=1;
      available=OC_LOTS_OF_BITS;
    }
    else window|=*ptr>>(available&7);
  }
  _b->bits=available;
  return window;
}

int32_t oc_pack_look1(oc_pack_buf *_b){
  oc_pb_window window;
  int32_t          available;
  window=_b->window;
  available=_b->bits;
  if(available<1)_b->window=window=oc_pack_refill(_b,1);
  return window>>(OC_PB_WINDOW_SIZE-1);
}

void oc_pack_adv1(oc_pack_buf *_b){
  _b->window<<=1;
  _b->bits--;
}

/*Here we assume that 0<=_bits&&_bits<=32.*/
long oc_pack_read(oc_pack_buf *_b,int32_t _bits){
  oc_pb_window window;
  int32_t          available;
  long         result;
  window=_b->window;
  available=_b->bits;
  if(_bits==0)return 0;
  if(available<_bits){
    window=oc_pack_refill(_b,_bits);
    available=_b->bits;
  }
  result=window>>(OC_PB_WINDOW_SIZE-_bits);
  available-=_bits;
  window<<=1;
  window<<=_bits-1;
  _b->bits=available;
  _b->window=window;
  return result;
}

int32_t oc_pack_read1(oc_pack_buf *_b){
  oc_pb_window window;
  int32_t          available;
  int32_t          result;
  window=_b->window;
  available=_b->bits;
  if(available<1){
    window=oc_pack_refill(_b,1);
    available=_b->bits;
  }
  result=window>>(OC_PB_WINDOW_SIZE-1);
  available--;
  window<<=1;
  _b->bits=available;
  _b->window=window;
  return result;
}

long oc_pack_bytes_left(oc_pack_buf *_b){
  if(_b->eof)return -1;
  return _b->stop-_b->ptr+(_b->bits>>3);
}
