#include "framework.h"
#ifndef METROWIN
#include <openssl/ssl.h>
#include <openssl/md5.h>
#include <openssl/err.h>
#endif

CLASS_DECL_c bool crypt_encrypt(simple_memory & storageEncrypt, const simple_memory & storageDecrypt, simple_memory & key);

CLASS_DECL_c bool crypt_decrypt(simple_memory & storageDecrypt, const simple_memory & storageEncrypt, simple_memory & key);

bool crypt_encrypt(simple_memory & storageEncrypt, const simple_memory & storageDecrypt, const char * pszSalt)
{

   simple_memory key(get_md5(pszSalt));

   return crypt_encrypt(storageEncrypt, storageDecrypt, key);

}


bool crypt_decrypt(simple_memory & storageDecrypt, const simple_memory & storageEncrypt, const char * pszSalt)
{

   simple_memory key(get_md5(pszSalt));

   return crypt_decrypt(storageDecrypt, storageEncrypt, key);

}


int crypt_encrypt(vsstring & strEncrypt, const char * pszDecrypt, const char * pszKey)
{
   simple_memory storageDecrypt;
   simple_memory storageEncrypt;
   simple_memory storageKey;
   if(pszDecrypt == NULL || strlen(pszDecrypt) == 0)
   {
      strEncrypt = "";
      return 0;
   }
   storageDecrypt.from_string(pszDecrypt);
   base64 base64;
   base64.decode(storageKey, pszKey);
   int cipherlen = crypt_encrypt(storageEncrypt, storageDecrypt, storageKey);
   strEncrypt = base64.encode(storageEncrypt);
   return cipherlen;
}


bool crypt_decrypt(vsstring & strDecrypt, const simple_memory & storageEncrypt, const char * pszSalt)
{
   simple_memory memoryDecrypt;
   if(!crypt_decrypt(memoryDecrypt, storageEncrypt, pszSalt))
      return false;
   memoryDecrypt.ToAsc(strDecrypt);
   return true;
}

bool crypt_encrypt(simple_memory & storageEncrypt, const char * pszDecrypt, const char * pszSalt)
{
   simple_memory memoryDecrypt;
   memoryDecrypt.FromAsc(pszDecrypt);
   return crypt_encrypt(storageEncrypt, memoryDecrypt, pszSalt);
}

bool crypt_file_get(const char * pszFile, vsstring & str, const char * pszSalt)
{
   simple_memory memoryEncrypt;
   if(!file_get_memory_dup(memoryEncrypt, pszFile))
      return false;
   if(memoryEncrypt.get_size() <= 0)
      return false;
   crypt_decrypt(str, memoryEncrypt, pszSalt);
   return true;
}

bool crypt_file_set(const char * pszFile, const char * pszData, const char * pszSalt)
{
   simple_memory memoryEncrypt;
   crypt_encrypt(memoryEncrypt, pszData, pszSalt);
   file_put_contents_dup(pszFile, memoryEncrypt);
   return true;
}




#ifndef METROWIN
CLASS_DECL_c vsstring spa_login_crypt(const char * psz, const char * pszRsa)
{
    
#ifdef MACOS
    
    CFMutableDictionaryRef parameters = CFDictionaryCreateMutable(NULL, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
    
    CFDictionaryAddValue(parameters, kSecAttrKeyType, kSecAttrKeyTypeRSA);
    
// not needed, defaults to true    CFDictionaryAddValue(parameters, kSecAttrCanEncrypt, kCFBooleanTrue);
    
    simple_memory memKeyData;
    
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
    
    simple_memory memDataIn;
    
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
    
    
    vsstring str;
    
    simple_memory memory;
    
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


   simple_memory memory;
   simple_memory memIn;

   memIn.from_hex(psz);

   memory.allocate(2048);

   int i = RSA_public_encrypt((int) memIn.get_size(), (const unsigned char * ) (const char *) memIn.get_data(), (unsigned char *)  memory.get_data(), rsa, RSA_PKCS1_PADDING);

   ERR_error_string(ERR_get_error(), NULL);
//   const char * pszError = ERR_error_string(ERR_get_error(), NULL);

   //TRACE(psz);


   memory.allocate(i);

   vsstring strHex;

   memory.to_hex(strHex);

   RSA_free(rsa);

   return strHex;
    
#endif

}


#endif
