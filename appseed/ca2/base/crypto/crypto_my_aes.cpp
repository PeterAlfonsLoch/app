// Crypto/MyAes.cpp

#include "framework.h"


namespace crypto
{

   // struct CAesTabInit { CAesTabInit() { AesGenTables();} } g_AesTabInit;

   aes_cbc_coder::aes_cbc_coder()
   {
   }

   ::ca2::HRes aes_cbc_coder::Init()
   {
      return S_OK; 
   }

   uint32_t aes_cbc_coder::Filter(byte *data, uint32_t size)
   {
      if (size == 0)
         return 0;
      if (size < AES_BLOCK_SIZE)
         return AES_BLOCK_SIZE;
      size >>= 4;
      _codeFunc(&m_ctx, data, &size);
      return size << 4;
   }

   ::ca2::HRes aes_cbc_coder::SetKey(const byte *data, uint32_t size)
   {
      if ((size & 0x7) != 0 || size < 16 || size > 32)
         return E_INVALIDARG;
      _setKeyFunc(&m_ctx, data, _codeFunc == (cipher_crypt_func_t) &::aes_cbc_nist_encrypt ? direction_encrypt : direction_decrypt);
      return S_OK;
   }

   ::ca2::HRes aes_cbc_coder::SetInitVector(const byte *data, uint32_t size)
   {
      if (size != AES_BLOCK_SIZE)
         return E_INVALIDARG;
      aes_cbc_set_iv(&m_ctx, (void *) data);
      return S_OK;
   }

   aes_cbc_encoder::aes_cbc_encoder()
   { 
      _codeFunc = (cipher_crypt_func_t) &::aes_cbc_nist_encrypt; _setKeyFunc = (cipher_init_func_t) &::aes_cbc_context_init; 
   }

   aes_cbc_decoder::aes_cbc_decoder()
   { 
      _codeFunc = (cipher_crypt_func_t) &::aes_cbc_nist_decrypt; _setKeyFunc = (cipher_init_func_t) &::aes_cbc_context_init; 
   }

} // namespace crypto
