#include "crypto_openssl.h"


template < >
CLASS_DECL_AURA void to_string(string & str, const MD5_CTX & ctx)
{

   unsigned char digest[MD5_DIGEST_LENGTH];

   MD5_Final(digest, (MD5_CTX *)&ctx);

   str = ::hex::lower_from(digest, MD5_DIGEST_LENGTH);

}

template < >
CLASS_DECL_AURA void to_string(string & str, const WHIRLPOOL_CTX & ctx)
{

   unsigned char digest[WHIRLPOOL_DIGEST_LENGTH];

   WHIRLPOOL_Final(digest, (WHIRLPOOL_CTX *) &ctx);

   str = ::hex::lower_from(digest, WHIRLPOOL_DIGEST_LENGTH);

}