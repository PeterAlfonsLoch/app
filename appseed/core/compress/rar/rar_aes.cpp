// Crypto/RarAes.cpp
// Note: you must include MyAes.cpp to project to initialize AES tables

#include "framework.h"

namespace crypto
{
   namespace rar29
   {

      decoder::decoder():
   _thereIsSalt(false),
      _needCalculate(true),
      _rar350Mode(false)
   {
      for (int32_t i = 0; i < sizeof(_salt); i++)
         _salt[i] = 0;
   }

   HRes decoder::SetDecoderProperties2(const byte *data, uint32_t size)
   {
      bool thereIsSaltPrev = _thereIsSalt;
      _thereIsSalt = false;
      if (size == 0)
         return S_OK;
      if (size < 8)
         return E_INVALIDARG;
      _thereIsSalt = true;
      bool same = false;
      if (_thereIsSalt == thereIsSaltPrev)
      {
         same = true;
         if (_thereIsSalt)
         {
            for (uint32_t i = 0; i < sizeof(_salt); i++)
               if (_salt[i] != data[i])
               {
                  same = false;
                  break;
               }
         }
      }
      for (uint32_t i = 0; i < sizeof(_salt); i++)
         _salt[i] = data[i];
      if (!_needCalculate && !same)
         _needCalculate = true;
      return S_OK;
   }

   static const uint32_t kMaxPasswordLength = 127 * 2;

   HRes decoder::CryptoSetPassword(const byte *data, uint32_t size)
   {
      if (size > kMaxPasswordLength)
         size = kMaxPasswordLength;
      bool same = false;
      if (size == buffer.GetCapacity())
      {
         same = true;
         for (uint32_t i = 0; i < size; i++)
            if (data[i] != buffer[i])
            {
               same = false;
               break;
            }
      }
      if (!_needCalculate && !same)
         _needCalculate = true;
      buffer.SetCapacity(size);
      memcpy(buffer, data, size);
      return S_OK;
   }

   HRes decoder::Init()
   {
      Calculate();
//      aes_cbc_init(&m_ctx, aeskey, kRarAesKeySize);
      aes_cbc_context_init(&m_ctx, aesKey, direction_decrypt);
      return S_OK;
   }

   void decoder::Calculate()
   {
      if (_needCalculate)
      {
         const uint32_t kSaltSize = 8;

         byte rawPassword[kMaxPasswordLength + kSaltSize];

         memcpy(rawPassword, buffer, buffer.GetCapacity());

         size_t rawLength = buffer.GetCapacity();

         if (_thereIsSalt)
         {
            memcpy(rawPassword + rawLength, _salt, kSaltSize);
            rawLength += kSaltSize;
         }

         ::crypto::sha1::CContext sha;
         sha.Init();

         // rar reverts hash for sha.
         const uint32_t kNumRounds = (1 << 18);
         uint32_t i;
         for (i = 0; i < kNumRounds; i++)
         {
            sha.UpdateRar(rawPassword, rawLength, _rar350Mode);
            sha.Update(rawPassword, rawLength);
            byte pswNum[3] = { (byte)i, (byte)(i >> 8), (byte)(i >> 16) };
            sha.UpdateRar(pswNum, 3, _rar350Mode);
            sha.update(pswNum, 3);
            if (i % (kNumRounds / 16) == 0)
            {
               ::crypto::sha1::CContext shaTemp = sha;
               byte digest[20];
               shaTemp.Final(digest);
               _aesInit[i / (kNumRounds / 16)] = (byte)digest[4 * 4 + 3];
            }
         }
         /*
         // it's test message for sha
         const char *message = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
         sha.Update((const byte *)message, strlen(message));
         */
         byte digest[20];
         sha.Final(digest);
         for (i = 0; i < 4; i++)
            for (uint32_t j = 0; j < 4; j++)
               aesKey[i * 4 + j] = (digest[i * 4 + 3 - j]);
      }
      _needCalculate = false;
   }

   } // namespace rar29

} // namespace crypto

