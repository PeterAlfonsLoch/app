#pragma once




//CLASS_DECL_BASE bool crypt_file_get(const char * pszFile, string & str, const char * pszSalt);

#ifdef MACOS_DEPRECATED

#define BASE_RSA_KEY SecKeyRef

#elif defined(BSD_STYLE_SOCKETS)

typedef struct rsa_st RSA;

#define BASE_RSA_KEY RSA *

#elif defined(METROWIN)

#define BASE_RSA_KEY ::Windows::Security::Cryptography::Core::CryptographicKey ^

#else

#error "BASE_RSA_KEY could not be defined, is RSA implementation missing?"

#endif



#include "crypto_sha1.h"
#include "crypto_nessie.h"
#include "crypto_hmac_sha1.h"
#include "crypto_md5.h"



#include "crypto_crypto.h"




CLASS_DECL_BASE bool hex_to_memory(primitive::memory & memory, const char * pszHex);
CLASS_DECL_BASE void memory_to_hex(string & strHex, primitive::memory & memory);




