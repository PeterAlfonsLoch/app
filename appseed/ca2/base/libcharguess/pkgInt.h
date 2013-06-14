/*
   libcharguess   -   Guess the encoding/charset of a string
    Copyright (C) 2003  Stephane Corbe <noubi@users.sourceforge.net>
   Based on Mozilla sources

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef nsPkgInt_h__
#define nsPkgInt_h__
#include "types.h"

typedef enum {
  eIdxSft4bits  = 3,
  eIdxSft8bits  = 2,
  eIdxSft16bits = 1
} nsIdxSft; 

typedef enum {
  eSftMsk4bits  = 7,
  eSftMsk8bits  = 3,
  eSftMsk16bits = 1
} nsSftMsk; 

typedef enum {
  eBitSft4bits  = 2,
  eBitSft8bits  = 3,
  eBitSft16bits = 4
} nsBitSft; 

typedef enum {
  eUnitMsk4bits  = 0x0000000FL,
  eUnitMsk8bits  = 0x000000FFL,
  eUnitMsk16bits = 0x0000FFFFL
} nsUnitMsk; 

typedef struct nsPkgInt {
  nsIdxSft  idxsft;
  nsSftMsk  sftmsk;
  nsBitSft  bitsft;
  nsUnitMsk unitmsk;
  uint32_t  *data;
} nsPkgInt;


#define PCK16BITS(a,b)            ((uint32_t)(((b) << 16) | (a)))

#define PCK8BITS(a,b,ca,d)         PCK16BITS( ((uint32_t)(((b) << 8) | (a))),  \
                                             ((uint32_t)(((d) << 8) | (ca))))

#define PCK4BITS(a,b,ca,d,e,f,g,h) PCK8BITS(  ((uint32_t)(((b) << 4) | (a))), \
                                             ((uint32_t)(((d) << 4) | (ca))), \
                                             ((uint32_t)(((f) << 4) | (e))), \
                                             ((uint32_t)(((h) << 4) | (g))) )

#define GETFROMPCK(i, ca) \
 (((((ca).data)[(i)>>(ca).idxsft])>>(((i)&(ca).sftmsk)<<(ca).bitsft))&(ca).unitmsk)

#endif /* nsPkgInt_h__ */

