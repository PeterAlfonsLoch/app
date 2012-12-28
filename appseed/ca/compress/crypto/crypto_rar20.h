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
         uint32 Keys[4];


         uint32 SubstLong(uint32 t)
         {
            return (uint32)SubstTable[(int32_t)t & 255] |
               ((uint32)SubstTable[(int32_t)(t >> 8) & 255] << 8) |
               ((uint32)SubstTable[(int32_t)(t >> 16) & 255] << 16) |
               ((uint32)SubstTable[(int32_t)(t >> 24) & 255] << 24);
         }

         void UpdateKeys(const byte *data);
         void CryptBlock(byte *buf, bool encrypt);
         void EncryptBlock(byte *buf) { CryptBlock(buf, true); }
         void DecryptBlock(byte *buf) { CryptBlock(buf, false); }
         void SetPassword(const byte *password, uint32 passwordLen);
      };

      class CLASS_DECL_ca decoder:
         public ::compress::filter_interface,
         public set_password_interface
      {
      public:


         data _cipher;


         ex1::HRes Init();
         uint32 Filter(byte *data, uint32 size);
         ex1::HRes CryptoSetPassword(const byte *data, uint32 size);
      };

   } // namespace rar20

} // namespace crypto

