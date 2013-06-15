#pragma once


CLASS_DECL_ca bool crypt_decrypt(simple_memory & storageDecrypt, const simple_memory & storageEncrypt, const char * pszSalt);
CLASS_DECL_ca bool crypt_encrypt(simple_memory & storageEncrypt, const simple_memory & storageDecrypt, const char * pszSalt);

CLASS_DECL_ca bool crypt_file_get(const char * pszFile, vsstring & str, const char * pszSalt);
CLASS_DECL_ca bool crypt_file_set(const char * pszFile, const char * pszData, const char * pszSalt);

#ifndef METROWIN
CLASS_DECL_ca vsstring spa_login_crypt(const char * psz, const char * pszRsa);
#endif

#include "nessie.h"
