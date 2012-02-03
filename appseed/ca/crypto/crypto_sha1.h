// Crypto/Sha1.h
// This file is based on public domain
// Steve Reid and Wei Dai's code from Crypto++

#pragma once

// Sha1 implementation in RAR before version 3.60 has bug:
// it changes data bytes in some cases.
// So this class supports both versions: normal_SHA and rar3Mode

namespace crypto
{

   namespace sha1 
   {

      const unsigned kBlockSize = 64;
      const unsigned kDigestSize = 20;

      const unsigned kBlockSizeInWords = (kBlockSize >> 2);
      const unsigned kDigestSizeInWords = (kDigestSize >> 2);

      class CLASS_DECL_ca CContextBase
      {
      protected:
         sha1_ctx_t     m_ctx;
         uint64         _count;
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
         void GetBlockDigest(const void * blockData, uint32 *destDigest);
         void GetBlockDigest(void * blockData, uint32 *destDigest, bool returnRes);
         //void
         // PrepareBlock can be used only when size <= 13. size in Words
//         void PrepareBlock(uint32 *block, unsigned int size) const;
         void update(const void * msg, int iSize);
      };

      class CLASS_DECL_ca CContextBase2: public CContextBase
      {
      protected:
         unsigned _count2;
         uint32_t _buffer[kBlockSizeInWords];
         void UpdateBlock() { CContextBase::UpdateBlock(_buffer); }
      public:
         void Init() { CContextBase::Init(); _count2 = 0; }
      };

      class CLASS_DECL_ca CContext: public CContextBase2
      {
      public:
         void Update(const void * data, size_t size);
         void UpdateRar(void * data, size_t size, bool rar350Mode);
         void Final(void * digest);
      };

      class CLASS_DECL_ca CContext32: public CContextBase2
      {
      public:
         void Update(const uint32 *data, size_t size);
         void Final(uint32 *digest);
      };

   } // namespace sha1

} // namespace crypto

