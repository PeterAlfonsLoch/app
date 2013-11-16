#pragma once


CLASS_DECL_BOOT bool crypt_decrypt(::primitive::memory & storageDecrypt, const ::primitive::memory & storageEncrypt, const char * pszSalt);
CLASS_DECL_BOOT bool crypt_encrypt(::primitive::memory & storageEncrypt, const ::primitive::memory & storageDecrypt, const char * pszSalt);

CLASS_DECL_BOOT bool crypt_file_get(const char * pszFile, string & str, const char * pszSalt);
CLASS_DECL_BOOT bool crypt_file_set(const char * pszFile, const char * pszData, const char * pszSalt);

CLASS_DECL_BOOT string spa_login_crypt(const char * psz, const char * pszRsa);

#include "nessie.h"
