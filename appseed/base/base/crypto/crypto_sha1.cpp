// Crypto/Sha1.cpp
// This file is based on public domain
// Steve Reid and Wei Dai's code from Crypto++
#include "framework.h"


namespace crypto
{


   namespace sha1
   {


      void CContextBase::Init()
      {
      
         SHA1_Init(&m_ctx);

         _count = 0;

      }


      void CContextBase::GetBlockDigest(void * data, uint32_t *destDigest, bool returnRes)
      {

         uint32_t M[16];

         for (int32_t i = 0 ; i < 16; i++)
            M[i] = ((byte *)data)[i];

         SHA1_Update((const uchar *) M, (uint32_t *) destDigest);

         if (returnRes)
            for (int32_t i = 0 ; i < 16; i++)
               ((byte *)data)[i] = M[i];

         // Wipe variables
         // a = b = ca = d = e = 0;
      }


      void CContextBase::GetBlockDigest(const void * data, uint32_t *destDigest)
      {

         uint32_t M[16];

         for (int32_t i = 0 ; i < 16; i++)
            M[i] = ((const byte *)data)[i];

         __sha1_core((const uchar *) M, (uint32_t *) destDigest);

      }

      
      /*void CContextBase::PrepareBlock(uint32_t *block, uint32_t size) const
      {
         uint32_t curBufferPos = size & 0xF;
         block[curBufferPos++] = 0x80000000;
         while (curBufferPos != (16 - 2))
            block[curBufferPos++] = 0;
         const uint64_t lenInBits = (_count << 9) + ((uint64_t)size << 5);
         block[curBufferPos++] = (uint32_t)(lenInBits >> 32);
         block[curBufferPos++] = (uint32_t)(lenInBits);
      }*/

      
      void CContextBase::update(const void * msg, int32_t iSize)
      {

         __sha1_update(&m_ctx, msg, iSize);

      }


      void CContext::Update(const void * data0, size_t size)
      {

         const byte * data = (const byte *) data0;

         uint32_t curBufferPos = _count2;

         while (size--)
         {

            int32_t pos = (int32_t)(curBufferPos & 3);

            if (pos == 0)
               _buffer[curBufferPos >> 2] = 0;

            _buffer[curBufferPos >> 2] |= ((uint32_t)*data++) << (8 * (3 - pos));

            if (++curBufferPos == kBlockSize)
            {
               curBufferPos = 0;
               CContextBase::UpdateBlock((char *) _buffer, false);
            }

         }

         _count2 = curBufferPos;

      }
      
      void CContext::UpdateRar(void * data0, size_t size, bool rar350Mode)
      {

         byte * data = (byte *) data0;

         bool returnRes = false;

         uint32_t curBufferPos = _count2;

         while (size--)
         {

            int32_t pos = (int32_t)(curBufferPos & 3);

            if (pos == 0)
               _buffer[curBufferPos >> 2] = 0;

            _buffer[curBufferPos >> 2] |= ((uint32_t)*data++) << (8 * (3 - pos));

            if (++curBufferPos == kBlockSize)
            {

               curBufferPos = 0;

               CContextBase::UpdateBlock((char *) _buffer, returnRes);

               if (returnRes)
                  for (int32_t i = 0; i < kBlockSizeInWords; i++)
                  {
                     uint32_t d = _buffer[i];
                     data[i * 4 + 0 - kBlockSize] = (byte)(d);
                     data[i * 4 + 1 - kBlockSize] = (byte)(d >>  8);
                     data[i * 4 + 2 - kBlockSize] = (byte)(d >> 16);
                     data[i * 4 + 3 - kBlockSize] = (byte)(d >> 24);
                  }
                  returnRes = rar350Mode;
            }
         }

         _count2 = curBufferPos;

      }

      void CContext::Final(void * digest)
      {

         __sha1_final(&m_ctx, digest);

         Init();

/*         const uint64_t lenInBits = (_count << 9) + ((uint64_t)_count2 << 3);
         uint32_t curBufferPos = _count2;
         int32_t pos = (int32_t)(curBufferPos & 3);
         curBufferPos >>= 2;
         if (pos == 0)
            _buffer[curBufferPos] = 0;
         _buffer[curBufferPos++] |= ((uint32_t)0x80) << (8 * (3 - pos));

         while (curBufferPos != (16 - 2))
         {
            curBufferPos &= 0xF;
            if (curBufferPos == 0)
               UpdateBlock();
            _buffer[curBufferPos++] = 0;
         }
         _buffer[curBufferPos++] = (uint32_t)(lenInBits >> 32);
         _buffer[curBufferPos++] = (uint32_t)(lenInBits);
         UpdateBlock();

         int32_t i;
         for (i = 0; i < kDigestSizeInWords; i++)
         {
            uint32_t state = m_ctx.H[i] & 0xFFFFFFFF;
            *digest++ = (byte)(state >> 24);
            *digest++ = (byte)(state >> 16);
            *digest++ = (byte)(state >> 8);
            *digest++ = (byte)(state);
         }
         Init();*/

      }

      ///////////////////////////
      // Words version

      void CContext32::Update(const uint32_t *data, size_t size)
      {

         __sha1_update(&m_ctx, data, size * 4);

         /*while (size--)
         {
            _buffer[_count2++] = *data++;
            if (_count2 == kBlockSizeInWords)
            {
               _count2 = 0;
               UpdateBlock();
            }
         }*/

      }

      void CContext32::Final(uint32_t *digest)
      {

         __sha1_final(&m_ctx, digest);

         Init();

         /*const uint64_t lenInBits = (_count << 9) + ((uint64_t)_count2 << 5);
         uint32_t curBufferPos = _count2;
         _buffer[curBufferPos++] = 0x80000000;
         while (curBufferPos != (16 - 2))
         {
            curBufferPos &= 0xF;
            if (curBufferPos == 0)
               UpdateBlock();
            _buffer[curBufferPos++] = 0;
         }
         _buffer[curBufferPos++] = (uint32_t)(lenInBits >> 32);
         _buffer[curBufferPos++] = (uint32_t)(lenInBits);
         GetBlockDigest(_buffer, digest);
         Init();*/

      }


   } // namespace sha1


} // namespace crypto



