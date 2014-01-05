#include "framework.h"
#ifndef METROWIN
#include <openssl/ssl.h>
#include <openssl/md5.h>
#include <openssl/err.h>
#endif


bool hex_to_memory(primitive::memory & memory, const char * pszHex)
{
   ::count len = strlen(pszHex);
   ::count count = (len + 1) / 2;
   memory.allocate(count);
   index i = 0;
   byte b;
   while (*pszHex != '\0')
   {
      char ch = (char)tolower(*pszHex);
      if (ch >= '0' && ch <= '9')
      {
         b = ch - '0';
      }
      else if (ch >= 'a' && ch <= 'f')
      {
         b = ch - 'a' + 10;
      }
      else
      {
         return false;
      }
      pszHex++;
      if (*pszHex == '\0')
      {
         memory.get_data()[i] = b;
         return true;
      }
      b = b << 4;
      ch = (char)tolower(*pszHex);
      if (ch >= '0' && ch <= '9')
      {
         b |= (ch - '0');
      }
      else if (ch >= 'a' && ch <= 'f')
      {
         b |= (ch - 'a' + 10);
      }
      else
      {
         return false;
      }
      pszHex++;
      memory.get_data()[i] = b;
      i++;
   }
   return true;
}


void memory_to_hex(string & strHex, primitive::memory & memory)
{
   ::count count = memory.get_size();
   LPSTR lpsz = strHex.GetBufferSetLength(count * 2);
   for (index i = 0; i < count; i++)
   {
      *lpsz++ = ::hex::lower_from((byte)((memory.get_data()[i] >> 4) & 0xf));
      *lpsz++ = ::hex::lower_from((byte)(memory.get_data()[i] & 0xf));
   }
   strHex.ReleaseBuffer(count * 2);
}





CLASS_DECL_BASE int32_t crypto_encrypt(::primitive::memory & storageEncrypt, const ::primitive::memory & storageDecrypt, ::primitive::memory & key);

CLASS_DECL_BASE int32_t crypto_decrypt(::primitive::memory & storageDecrypt, const ::primitive::memory & storageEncrypt, ::primitive::memory & key);

bool crypto_encrypt(::primitive::memory & storageEncrypt, const ::primitive::memory & storageDecrypt, const char * pszSalt)
{

   ::primitive::memory key;

   key.from_string(get_md5(pszSalt));

   return crypto_encrypt(storageEncrypt, storageDecrypt, key) > 0;

}


bool crypto_decrypt(::primitive::memory & storageDecrypt, const ::primitive::memory & storageEncrypt, const char * pszSalt)
{

   ::primitive::memory key;

   key.from_string(get_md5(pszSalt));

   return crypto_decrypt(storageDecrypt, storageEncrypt, key) > 0;

}


int32_t crypto_encrypt(string & strEncrypt, const char * pszDecrypt, const char * pszKey)
{
   ::primitive::memory storageDecrypt;
   ::primitive::memory storageEncrypt;
   ::primitive::memory storageKey;
   if (pszDecrypt == NULL || strlen(pszDecrypt) == 0)
   {
      strEncrypt = "";
      return 0;
   }
   storageDecrypt.from_string(pszDecrypt);
   threadSystem.base64().decode(storageKey, pszKey);
   int32_t cipherlen = crypto_encrypt(storageEncrypt, storageDecrypt, storageKey);
   strEncrypt = threadSystem.base64().encode(storageEncrypt);
   return cipherlen;
}


bool crypto_decrypt(string & strDecrypt, const ::primitive::memory & storageEncrypt, const char * pszSalt)
{
   ::primitive::memory memoryDecrypt;
   if (!crypto_decrypt(memoryDecrypt, storageEncrypt, pszSalt))
      return false;
   memoryDecrypt.to_asc(strDecrypt);
   return true;
}

bool crypto_encrypt(::primitive::memory & storageEncrypt, const char * pszDecrypt, const char * pszSalt)
{
   ::primitive::memory memoryDecrypt;
   memoryDecrypt.from_asc(pszDecrypt);
   return crypto_encrypt(storageEncrypt, memoryDecrypt, pszSalt);
}

bool crypto_file_get(const char * pszFile, string & str, const char * pszSalt)
{
   ::primitive::memory memoryEncrypt;
   if (!file_get_memory_dup(memoryEncrypt, pszFile))
      return false;
   if (memoryEncrypt.get_size() <= 0)
      return false;
   crypto_decrypt(str, memoryEncrypt, pszSalt);
   return true;
}

bool crypto_file_set(const char * pszFile, const char * pszData, const char * pszSalt)
{
   ::primitive::memory memoryEncrypt;
   crypto_encrypt(memoryEncrypt, pszData, pszSalt);
   file_put_contents_dup(pszFile, memoryEncrypt);
   return true;
}




CLASS_DECL_BASE string spa_login_crypt(const char * psz, const char * pszRsa)
{

#if 0 // MACOS

   CFMutableDictionaryRef parameters = CFDictionaryCreateMutable(NULL, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);

   CFDictionaryAddValue(parameters, kSecAttrKeyType, kSecAttrKeyTypeRSA);

   // not needed, defaults to true    CFDictionaryAddValue(parameters, kSecAttrCanEncrypt, kCFBooleanTrue);

   ::primitive::memory memKeyData;

   memKeyData.from_hex(pszRsa);

   CFDataRef keyData = memKeyData.get_os_cf_data();

   CFErrorRef error = NULL;

   SecKeyRef key = SecKeyCreateFromData(parameters, keyData, &error);

   if (error != NULL)
   {

      CFRelease(parameters);

      CFRelease(keyData);

      CFRelease(error);

      return "";

   }

   SecTransformRef transform = SecEncryptTransformCreate(key, &error);


   if (error != NULL)
   {

      CFRelease(parameters);

      CFRelease(keyData);

      CFRelease(key);

      CFRelease(error);

      return "";

   }


   SecTransformSetAttribute(transform, kSecPaddingKey, kSecPaddingPKCS1Key, &error);

   if (error != NULL)
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

   if (error != NULL)
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

   CFDataRef data = (CFDataRef)SecTransformExecute(transform, &error);

   if (error != NULL)
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
#elif defined(METROWIN)


   typedef struct _BCRYPT_RSAKEY_BLOB {
      ULONG Magic;
      ULONG BitLength;
      ULONG cbPublicExp;
      ULONG cbModulus;
      ULONG cbPrime1;
      ULONG cbPrime2;
   } BCRYPT_RSAKEY_BLOB;

   BCRYPT_RSAKEY_BLOB blob;

   ::file::memory_buffer memfile(NULL);

   blob.Magic = 0x31415352; // BCRYPT_RSAPUBLIC_MAGIC;
   blob.BitLength = 1024;
   blob.cbPublicExp = 3;
   blob.cbModulus = 1024 / 8;
   blob.cbPrime1 = 0;
   blob.cbPrime2 = 0;

   primitive::memory memVer;

   memVer.from_hex("00");

   memVer.prefix_der_uint();

   memfile.write(&blob, sizeof(blob));

   primitive::memory memMod;

   memMod.from_hex(pszRsa);

   //memMod.reverse();



   //memMod.prefix_der_uint();

   primitive::memory memExp;

   memExp.from_hex("10001");

   //memExp.reverse();

   memfile.write(memExp.get_data(), memExp.get_size());

   memfile.write(memMod.get_data(), memMod.get_size());

   //memExp.prefix_der_uint();

   ::Windows::Security::Cryptography::Core::AsymmetricKeyAlgorithmProvider ^ cipher =
      ::Windows::Security::Cryptography::Core::AsymmetricKeyAlgorithmProvider::OpenAlgorithm(::Windows::Security::Cryptography::Core::AsymmetricAlgorithmNames::RsaPkcs1);


   primitive::memory memKey;

   //memKey = memVer;
   //memKey += memMod;
   memKey = memMod;
   memKey += memExp;


   memKey.prefix_der_sequence();

   //      string strRsaPrivateKey = "-----BEGIN RSA PRIVATE KEY-----\r\n";
   //    strRsaPrivateKey += chunk_split(System.base64().encode(memKey));
   //  strRsaPrivateKey += "-----END RSA PRIVATE KEY-----";

   //memKey.allocate(strRsaPrivateKey.get_length());

   //memcpy(memKey.get_data(), strRsaPrivateKey, memKey.get_size());

   ::Windows::Security::Cryptography::Core::CryptographicKey ^ cipherkey = cipher->ImportPublicKey(memfile.get_memory()->get_os_crypt_buffer(), ::Windows::Security::Cryptography::Core::CryptographicPublicKeyBlobType::BCryptPublicKey);

   primitive::memory memIn;

   hex_to_memory(memIn, psz);

   primitive::memory memory;

   memory.set_os_crypt_buffer(::Windows::Security::Cryptography::Core::CryptographicEngine::Encrypt(cipherkey, memIn.get_os_crypt_buffer(), nullptr));

   string strHex;
   memory_to_hex(strHex, memory);

   return strHex;
#else

   RSA * rsa = RSA_new();

   BN_hex2bn(&rsa->n, pszRsa);
   BN_hex2bn(&rsa->e, "10001");


   ::primitive::memory memory;
   ::primitive::memory memIn;

   memIn.from_hex(psz);

   memory.allocate(2048);

   int32_t i = RSA_public_encrypt((int32_t)memIn.get_size(), (const uchar *)(const char *)memIn.get_data(), (uchar *)memory.get_data(), rsa, RSA_PKCS1_PADDING);

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


