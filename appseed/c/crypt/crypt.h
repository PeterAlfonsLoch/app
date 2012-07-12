#pragma once


CLASS_DECL_c bool crypt_decrypt(simple_memory & storageDecrypt, const simple_memory & storageEncrypt, const char * pszSalt);
CLASS_DECL_c bool crypt_encrypt(simple_memory & storageEncrypt, const simple_memory & storageDecrypt, const char * pszSalt);

CLASS_DECL_c bool crypt_file_get(const char * pszFile, vsstring & str, const char * pszSalt);


#include "nessie.h"
