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
         SHA_CTX     m_ctx;
         uint64_t         _count;
         void UpdateBlock(void * data, bool returnRes)
         {
            GetBlockDigest(data, &m_ctx, returnRes);
            _count++;
         }
         void UpdateBlock(const void * data)
         {
            GetBlockDigest(data, &m_ctx);
            _count++;
         }
      public:
         void Init();
         void GetBlockDigest(const void * blockData,SHA_CTX *destDigest);
         void GetBlockDigest(void * blockData,SHA_CTX *destDigest,bool returnRes);
         //void
         // PrepareBlock can be used only when size <= 13. size in Words
         //         void PrepareBlock(uint32_t *block, uint32_t size) const;
         void update(const void * msg, int32_t iSize);
      };

      class CLASS_DECL_BASE CContextBase2 : public CContextBase
      {
      protected:
         uint32_t _count2;
         uint32_t _buffer[kBlockSizeInWords];
         void UpdateBlock() { CContextBase::UpdateBlock(_buffer); }
      public:
         void Init() { CContextBase::Init(); _count2 = 0; }
      };

      class CLASS_DECL_BASE CContext : public CContextBase2
      {
      public:
         void Update(const void * data, size_t size);
         void UpdateRar(void * data, size_t size, bool rar350Mode);
         void Final(void * digest);
      };

      class CLASS_DECL_BASE CContext32 : public CContextBase2
      {
      public:
         void Update(const uint32_t *data, size_t size);
         void Final(uint32_t *digest);
      };


   } // namespace sha1


} // namespace crypto



