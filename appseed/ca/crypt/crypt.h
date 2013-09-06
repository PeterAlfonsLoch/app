#pragma once


CLASS_DECL_ca bool crypt_decrypt(::primitive::memory & storageDecrypt, const ::primitive::memory & storageEncrypt, const char * pszSalt);
CLASS_DECL_ca bool crypt_encrypt(::primitive::memory & storageEncrypt, const ::primitive::memory & storageDecrypt, const char * pszSalt);

CLASS_DECL_ca bool crypt_file_get(const char * pszFile, string & str, const char * pszSalt);
CLASS_DECL_ca bool crypt_file_set(const char * pszFile, const char * pszData, const char * pszSalt);

#ifndef METROWIN
CLASS_DECL_ca string spa_login_crypt(const char * psz, const char * pszRsa);
#endif

#include "nessie.h"
