// Crypto/MyAes.h
// from 7-zip
#pragma once


namespace crypto
{

   
   class aes_cbc_coder:
      public ::libcompress::filter_interface,
      public ::crypto::properties_interface
   {
   public:


      cipher_crypt_func_t     _codeFunc;
      cipher_init_func_t      _setKeyFunc;
      aes_cbc_ctx_t           m_ctx;


      aes_cbc_coder();


      HRes Init();
      uint32_t Filter(byte *data, uint32_t size);
      HRes SetKey(const byte *data, uint32_t size);
      HRes SetInitVector(const byte *data, uint32_t size);
   };

   struct aes_cbc_encoder :
      public aes_cbc_coder
   {
      public:
      aes_cbc_encoder();
   };

   struct aes_cbc_decoder :
      public aes_cbc_coder
   {
   public:
      aes_cbc_decoder();
   };

} // namespace crypto
