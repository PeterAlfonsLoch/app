#include "framework.h"


namespace crypto
{


   namespace hmac_sha1
   {


      void context::digest(void * digest, const void * text, int32_t text_len, const void * key, int32_t key_len)
      {

         hmac_ctx_t state;

         memset(&state, 0, sizeof(state));

         hmac_init(&state, (const uint8_t *) key, key_len);

         //hmac_start(&state);

         hmac_compute(&state, text, text_len, 20, (uint8_t *) digest);

      }
   
   } // namespace hmac_sha1


} // namespace crypto



