// Crypto/RarAes.h
// from 7-zip
#pragma once

#define AES_BLOCK_SIZE 16

namespace crypto
{

   namespace rar29
   {

      const uint32_t kRarAesKeySize = 16;

      class decoder:
        public aes_cbc_decoder,
        public ::libcompress::set_decoder_properties2_interface,
        public ::crypto::set_password_interface
      {
      public:

         byte               _salt[8];
         bool               _thereIsSalt;
         ::file::byte_buffer   buffer;
         byte               aesKey[kRarAesKeySize];
         byte               _aesInit[AES_BLOCK_SIZE];
         bool               _needCalculate;
         bool               _rar350Mode;

         void Calculate();
         HRes Init();
         HRes CryptoSetPassword(const byte *aData, uint32_t aSize);
         HRes SetDecoderProperties2(const byte *data, uint32_t size);

         decoder();
         void SetRar350Mode(bool rar350Mode) { _rar350Mode = rar350Mode; }
      };

   } // namespace rar29

} // namespace crypto


