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

// Crypto/Sha1.h
// This file is based on public domain
// Steve Reid and Wei Dai's code from Crypto++

// Sha1 implementation in RAR before version 3.60 has bug:
// it changes data bytes in some cases.
// So this class supports both versions: normal_SHA and rar3Mode

namespace crypto
{

   namespace sha1 
   {

      const uint32_t kBlockSize = 64;
      const uint32_t kDigestSize = 20;

      const uint32_t kBlockSizeInWords = (kBlockSize >> 2);
      const uint32_t kDigestSizeInWords = (kDigestSize >> 2);

      class CLASS_DECL_BASE CContextBase
      {
      protected:
         sha1_ctx_t     m_ctx;
         uint64_t         _count;
         void UpdateBlock(void * data, bool returnRes)
         {
            GetBlockDigest(data, m_ctx.Message_Digest, returnRes);
            _count++;
         }
         void UpdateBlock(const void * data)
         {
            GetBlockDigest(data, m_ctx.Message_Digest);
            _count++;
         }
      public:
         void Init();
         void GetBlockDigest(const void * blockData, uint32_t *destDigest);
         void GetBlockDigest(void * blockData, uint32_t *destDigest, bool returnRes);
         //void
         // PrepareBlock can be used only when size <= 13. size in Words
//         void PrepareBlock(uint32_t *block, uint32_t size) const;
         void update(const void * msg, int32_t iSize);
      };

      class CLASS_DECL_BASE CContextBase2: public CContextBase
      {
      protected:
         uint32_t _count2;
         uint32_t _buffer[kBlockSizeInWords];
         void UpdateBlock() { CContextBase::UpdateBlock(_buffer); }
      public:
         void Init() { CContextBase::Init(); _count2 = 0; }
      };

      class CLASS_DECL_BASE CContext: public CContextBase2
      {
      public:
         void Update(const void * data, size_t size);
         void UpdateRar(void * data, size_t size, bool rar350Mode);
         void Final(void * digest);
      };

      class CLASS_DECL_BASE CContext32: public CContextBase2
      {
      public:
         void Update(const uint32_t *data, size_t size);
         void Final(uint32_t *digest);
      };


   } // namespace sha1


} // namespace crypto



