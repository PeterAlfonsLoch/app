/*
*  sha1.h
*
*  Copyright (C) 1998, 2009
*  Paul E. Jones <paulej@packetizer.com>
*  All Rights Reserved
*
*****************************************************************************
*  $Id: sha1.h 12 2009-06-22 19:34:25Z paulej $
*****************************************************************************
*
*  Description:
*      This class implements the Secure Hashing Standard as defined
*      in FIPS PUB 180-1 published April 17, 1995.
*
*      Many of the variable names in the SHA1Context, especially the
*      single character names, were used because those were the names
*      used in the publication.
*
*      Please read the file sha1.ca for more information.
*
*/
#pragma once


BEGIN_EXTERN_C

/*
*  This structure will hold context information for the hashing
*  operation
*/
typedef struct SHA1Context
{
   uint32_t Message_Digest[5]; /* Message Digest (output)          */

   uint32_t Length_Low;        /* Message length in bits           */
   uint32_t Length_High;       /* Message length in bits           */

   uchar Message_Block[64]; /* 512-bit message blocks      */
   int32_t Message_Block_Index;    /* Index into message block array   */

   int32_t Computed;               /* Is the digest computed?          */
   int32_t Corrupted;              /* Is the message digest corruped?  */
} sha1_ctx_t;

/*
*  Function Prototypes
*/
void __sha1_init(sha1_ctx_t *);
void __sha1_update(sha1_ctx_t *, const void *, size_t);
int32_t  __sha1_final(sha1_ctx_t *, void *);

void __sha1_core(const uchar Message_Block[64], uint32_t Message_Digest[5]);



END_EXTERN_C





