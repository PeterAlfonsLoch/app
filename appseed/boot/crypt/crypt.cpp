#include "framework.h"
#ifndef METROWIN
#include <openssl/ssl.h>
#include <openssl/md5.h>
#include <openssl/err.h>
#endif

CLASS_DECL_BOOT int32_t crypt_encrypt(::primitive::memory & storageEncrypt, const ::primitive::memory & storageDecrypt, ::primitive::memory & key);

CLASS_DECL_BOOT int32_t crypt_decrypt(::primitive::memory & storageDecrypt, const ::primitive::memory & storageEncrypt, ::primitive::memory & key);

bool crypt_encrypt(::primitive::memory & storageEncrypt, const ::primitive::memory & storageDecrypt, const char * pszSalt)
{

   ::primitive::memory key;

   key.from_string(get_md5(pszSalt));

   return crypt_encrypt(storageEncrypt, storageDecrypt, key) > 0;

}


bool crypt_decrypt(::primitive::memory & storageDecrypt, const ::primitive::memory & storageEncrypt, const char * pszSalt)
{

   ::primitive::memory key;

   key.from_string(get_md5(pszSalt));

   return crypt_decrypt(storageDecrypt, storageEncrypt, key) > 0;

}


int32_t crypt_encrypt(string & strEncrypt, const char * pszDecrypt, const char * pszKey)
{
   ::primitive::memory storageDecrypt;
   ::primitive::memory storageEncrypt;
   ::primitive::memory storageKey;
   if(pszDecrypt == NULL || strlen(pszDecrypt) == 0)
   {
      strEncrypt = "";
      return 0;
   }
   storageDecrypt.from_string(pszDecrypt);
   threadSystem.base64().decode(storageKey, pszKey);
   int32_t cipherlen = crypt_encrypt(storageEncrypt, storageDecrypt, storageKey);
   strEncrypt = threadSystem.base64().encode(storageEncrypt);
   return cipherlen;
}


bool crypt_decrypt(string & strDecrypt, const ::primitive::memory & storageEncrypt, const char * pszSalt)
{
   ::primitive::memory memoryDecrypt;
   if(!crypt_decrypt(memoryDecrypt, storageEncrypt, pszSalt))
      return false;
   memoryDecrypt.to_asc(strDecrypt);
   return true;
}

bool crypt_encrypt(::primitive::memory & storageEncrypt, const char * pszDecrypt, const char * pszSalt)
{
   ::primitive::memory memoryDecrypt;
   memoryDecrypt.from_asc(pszDecrypt);
   return crypt_encrypt(storageEncrypt, memoryDecrypt, pszSalt);
}

bool crypt_file_get(const char * pszFile, string & str, const char * pszSalt)
{
   ::primitive::memory memoryEncrypt;
   if(!file_get_memory_dup(memoryEncrypt, pszFile))
      return false;
   if(memoryEncrypt.get_size() <= 0)
      return false;
   crypt_decrypt(str, memoryEncrypt, pszSalt);
   return true;
}

bool crypt_file_set(const char * pszFile, const char * pszData, const char * pszSalt)
{
   ::primitive::memory memoryEncrypt;
   crypt_encrypt(memoryEncrypt, pszData, pszSalt);
   file_put_contents_dup(pszFile, memoryEncrypt);
   return true;
}




#ifndef METROWIN
CLASS_DECL_BOOT string spa_login_crypt(const char * psz, const char * pszRsa)
{

#ifdef MACOS

    CFMutableDictionaryRef parameters = CFDictionaryCreateMutable(NULL, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);

    CFDictionaryAddValue(parameters, kSecAttrKeyType, kSecAttrKeyTypeRSA);

// not needed, defaults to true    CFDictionaryAddValue(parameters, kSecAttrCanEncrypt, kCFBooleanTrue);

    ::primitive::memory memKeyData;

    memKeyData.from_hex(pszRsa);

    CFDataRef keyData = memKeyData.get_os_cf_data();

    CFErrorRef error = NULL;

    SecKeyRef key = SecKeyCreateFromData(parameters, keyData, &error);

    if(error != NULL)
    {

        CFRelease(parameters);

        CFRelease(keyData);

        CFRelease(error);

        return "";

    }

    SecTransformRef transform = SecEncryptTransformCreate(key, &error);


    if(error != NULL)
    {

        CFRelease(parameters);

        CFRelease(keyData);

        CFRelease(key);

        CFRelease(error);

        return "";

    }


    SecTransformSetAttribute(transform, kSecPaddingKey, kSecPaddingPKCS1Key, &error);

    if(error != NULL)
    {

        CFRelease(transform);

        CFRelease(keyData);

        CFRelease(parameters);

        CFRelease(key);

        CFRelease(error);

        return "";

    }

    ::primitive::memory memDataIn;

    memDataIn.from_hex(pszRsa);

    CFDataRef dataIn = memDataIn.get_os_cf_data();

    SecTransformSetAttribute(transform, kSecTransformInputAttributeName, dataIn, &error);

    if(error != NULL)
    {

        CFRelease(dataIn);

        CFRelease(transform);

        CFRelease(parameters);

        CFRelease(keyData);

        CFRelease(key);

        CFRelease(error);

        return "";

    }

    /* Encrypt the data. */

    CFDataRef data = (CFDataRef) SecTransformExecute(transform, &error);

    if(error != NULL)
    {

        CFRelease(dataIn);

        CFRelease(transform);

        CFRelease(parameters);

        CFRelease(keyData);

        CFRelease(key);

        CFRelease(error);

        return "";

    }


    string str;

    ::primitive::memory memory;

    memory.set_os_cf_data(data);

    memory.to_hex(str);

    CFRelease(data);

    CFRelease(dataIn);

    CFRelease(transform);

    CFRelease(keyData);

    CFRelease(parameters);

    CFRelease(key);

    return str;

#else

   RSA * rsa = RSA_new();

   BN_hex2bn(&rsa->n, pszRsa);
   BN_hex2bn(&rsa->e, "10001");


   ::primitive::memory memory;
   ::primitive::memory memIn;

   memIn.from_hex(psz);

   memory.allocate(2048);

   int32_t i = RSA_public_encrypt((int32_t) memIn.get_size(), (const uchar * ) (const char *) memIn.get_data(), (uchar *)  memory.get_data(), rsa, RSA_PKCS1_PADDING);

   ERR_error_string(ERR_get_error(), NULL);
//   const char * pszError = ERR_error_string(ERR_get_error(), NULL);

   //TRACE(psz);


   memory.allocate(i);

   string strHex;

   memory.to_hex(strHex);

   RSA_free(rsa);

   return strHex;

#endif

}


#endif
