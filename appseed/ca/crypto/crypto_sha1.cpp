// Crypto/Sha1.cpp
// This file is based on public domain
// Steve Reid and Wei Dai's code from Crypto++

#include "StdAfx.h"

namespace crypto
{

   namespace sha1
   {


      void CContextBase::Init()
      {
         __sha1_init(&m_ctx);
         _count = 0;
      }

      void CContextBase::GetBlockDigest(char * data, uint32 *destDigest, bool returnRes)
      {

         uint32_t M[16];

         for (int i = 0 ; i < 16; i++)
            M[i] = data[i];

         __sha1_core((const unsigned char *) M, (uint32_t *) destDigest);

         if (returnRes)
            for (int i = 0 ; i < 16; i++)
               data[i] = M[i];

         // Wipe variables
         // a = b = c = d = e = 0;
      }


      
      /*void CContextBase::PrepareBlock(uint32 *block, unsigned size) const
      {
         unsigned curBufferPos = size & 0xF;
         block[curBufferPos++] = 0x80000000;
         while (curBufferPos != (16 - 2))
            block[curBufferPos++] = 0;
         const uint64 lenInBits = (_count << 9) + ((uint64)size << 5);
         block[curBufferPos++] = (uint32)(lenInBits >> 32);
         block[curBufferPos++] = (uint32)(lenInBits);
      }*/

      
      void CContextBase::update(uint8_t * msg, int iSize)
      {
         __sha1_update(&m_ctx, msg, iSize);
      }

      void CContext::Update(const byte *data, size_t size)
      {
         unsigned curBufferPos = _count2;
         while (size--)
         {
            int pos = (int)(curBufferPos & 3);
            if (pos == 0)
               _buffer[curBufferPos >> 2] = 0;
            _buffer[curBufferPos >> 2] |= ((uint32)*data++) << (8 * (3 - pos));
            if (++curBufferPos == kBlockSize)
            {
               curBufferPos = 0;
               CContextBase::UpdateBlock((char *) _buffer, false);
            }
         }
         _count2 = curBufferPos;
      }
      
      void CContext::UpdateRar(byte *data, size_t size, bool rar350Mode)
      {
         bool returnRes = false;
         unsigned curBufferPos = _count2;
         while (size--)
         {
            int pos = (int)(curBufferPos & 3);
            if (pos == 0)
               _buffer[curBufferPos >> 2] = 0;
            _buffer[curBufferPos >> 2] |= ((uint32)*data++) << (8 * (3 - pos));
            if (++curBufferPos == kBlockSize)
            {
               curBufferPos = 0;
               CContextBase::UpdateBlock((char *) _buffer, returnRes);
               if (returnRes)
                  for (int i = 0; i < kBlockSizeInWords; i++)
                  {
                     uint32 d = _buffer[i];
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

      void CContext::Final(byte *digest)
      {
         __sha1_final(&m_ctx, digest);
         Init();
/*         const uint64 lenInBits = (_count << 9) + ((uint64)_count2 << 3);
         unsigned curBufferPos = _count2;
         int pos = (int)(curBufferPos & 3);
         curBufferPos >>= 2;
         if (pos == 0)
            _buffer[curBufferPos] = 0;
         _buffer[curBufferPos++] |= ((uint32)0x80) << (8 * (3 - pos));

         while (curBufferPos != (16 - 2))
         {
            curBufferPos &= 0xF;
            if (curBufferPos == 0)
               UpdateBlock();
            _buffer[curBufferPos++] = 0;
         }
         _buffer[curBufferPos++] = (uint32)(lenInBits >> 32);
         _buffer[curBufferPos++] = (uint32)(lenInBits);
         UpdateBlock();

         int i;
         for (i = 0; i < kDigestSizeInWords; i++)
         {
            uint32 state = m_ctx.H[i] & 0xFFFFFFFF;
            *digest++ = (byte)(state >> 24);
            *digest++ = (byte)(state >> 16);
            *digest++ = (byte)(state >> 8);
            *digest++ = (byte)(state);
         }
         Init();*/
      }

      ///////////////////////////
      // Words version

      void CContext32::Update(const uint32 *data, size_t size)
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

      void CContext32::Final(uint32 *digest)
      {
         __sha1_final(&m_ctx, digest);
         Init();
         /*const uint64 lenInBits = (_count << 9) + ((uint64)_count2 << 5);
         unsigned curBufferPos = _count2;
         _buffer[curBufferPos++] = 0x80000000;
         while (curBufferPos != (16 - 2))
         {
            curBufferPos &= 0xF;
            if (curBufferPos == 0)
               UpdateBlock();
            _buffer[curBufferPos++] = 0;
         }
         _buffer[curBufferPos++] = (uint32)(lenInBits >> 32);
         _buffer[curBufferPos++] = (uint32)(lenInBits);
         GetBlockDigest(_buffer, digest);
         Init();*/
      }


   }


}
