#pragma once




//CLASS_DECL_AXIS bool crypt_file_get(const char * pszFile, string & str, const char * pszSalt);

#ifdef MACOS_DEPRECATED

#define AXIS_RSA_KEY SecKeyRef

#elif defined(BSD_STYLE_SOCKETS)



typedef struct rsa_st RSA;

#define AXIS_RSA_KEY RSA *

#elif defined(METROWIN)

#define AXIS_RSA_KEY ::Windows::Security::Cryptography::Core::CryptographicKey ^

#else

#error "AXIS_RSA_KEY could not be defined, is RSA implementation missing?"

#endif



//#include "crypto_nessie.h"
//#include "crypto_md5.h"


#include <openssl/md5.h>

template < >
inline string to_string(MD5_CTX & ctx)
{

   unsigned char digest[MD5_DIGEST_LENGTH];

   MD5_Final(digest,&ctx);

   return ::hex::lower_from(digest,MD5_DIGEST_LENGTH);

}



#include "crypto_crypto.h"




//CLASS_DECL_AXIS bool hex_to_memory(primitive::memory & memory, const char * pszHex);
//CLASS_DECL_AXIS void memory_to_hex(string & strHex, primitive::memory & memory);




