// Crypto/Rar20Crypto.h
// from 7-zip
#pragma once


namespace crypto
{

   namespace rar20
   {

      class CLASS_DECL_ca data
      {
      public:


         byte SubstTable[256];
         uint32_t Keys[4];


         uint32_t SubstLong(uint32_t t)
         {
            return (uint32_t)SubstTable[(int32_t)t & 255] |
               ((uint32_t)SubstTable[(int32_t)(t >> 8) & 255] << 8) |
               ((uint32_t)SubstTable[(int32_t)(t >> 16) & 255] << 16) |
               ((uint32_t)SubstTable[(int32_t)(t >> 24) & 255] << 24);
         }

         void UpdateKeys(const byte *data);
         void CryptBlock(byte *buf, bool encrypt);
         void EncryptBlock(byte *buf) { CryptBlock(buf, true); }
         void DecryptBlock(byte *buf) { CryptBlock(buf, false); }
         void SetPassword(const byte *password, uint32_t passwordLen);
      };

      class CLASS_DECL_ca decoder:
         public ::libcompress::filter_interface,
         public set_password_interface
      {
      public:


         data _cipher;


         ::ca::HRes Init();
         uint32_t Filter(byte *data, uint32_t size);
         ::ca::HRes CryptoSetPassword(const byte *data, uint32_t size);
      };

   } // namespace rar20

} // namespace crypto

