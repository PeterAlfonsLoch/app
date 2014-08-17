#pragma once


namespace crypto
{


   namespace hmac_sha1
   {


      class CLASS_DECL_BASE context
      {
      public:

         // digest is 20-byte digest
         void digest(void * digest, const void * text, int32_t text_len, const void * key, int32_t key_len);

      };


   } // namespace hmac_sha1


} // namespace crypto


