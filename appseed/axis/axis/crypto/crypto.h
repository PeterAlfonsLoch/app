#pragma once



#if defined(METROWIN)

#define OPENSSL_CRYPTO

#else

#define OPENSSL_CRYPTO

#endif

//CLASS_DECL_AXIS bool crypt_file_get(const char * pszFile, string & str, const char * pszSalt);

#ifdef MACOS_DEPRECATED

#define AXIS_RSA_KEY SecKeyRef

#elif defined(OPENSSL_CRYPTO)



typedef struct rsa_st RSA;

#define AXIS_RSA_KEY RSA *

#elif defined(METROWIN)

#define AXIS_RSA_KEY ::Windows::Security::Cryptography::Core::CryptographicKey ^

#else

#error "AXIS_RSA_KEY could not be defined, is RSA implementation missing?"

#endif



//#include "crypto_nessie.h"
//#include "crypto_md5.h"


#include "openssl/md5.h"

template < >
inline string & to_string(string & str, MD5_CTX & ctx)
{

   unsigned char digest[MD5_DIGEST_LENGTH];

   MD5_Final(digest,&ctx);

   str = ::hex::lower_from(digest,MD5_DIGEST_LENGTH);

   return str;

}



#include "crypto_crypto.h"




//CLASS_DECL_AXIS bool hex_to_memory(primitive::memory & memory, const char * pszHex);
//CLASS_DECL_AXIS void memory_to_hex(string & strHex, primitive::memory & memory);




