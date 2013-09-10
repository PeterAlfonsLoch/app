#include "framework.h"
#ifndef METROWIN
#include <openssl/ssl.h>
#include <openssl/md5.h>
#endif

#define CA4_CRYPT_V5_FINAL_HASH_BYTES (NESSIE_DIGESTBYTES * 16)
#define CA4_CRYPT_V5_SALT_BYTES (CA4_CRYPT_V5_FINAL_HASH_BYTES - NESSIE_DIGESTBYTES)


namespace core
{


   crypt::crypt(sp(base_application) papp) :
      base_element(papp)
   {
   }

   crypt::~crypt()
   {
   }


   bool crypt::decrypt(primitive::memory & storageDecrypt, const primitive::memory & storageEncrypt, const char * pszSalt)
   {

      // default implementation - OS may implement its own HOME/UserDir encryption

      string str = defer_get_cryptkey();

      if(str.is_empty())
         return false;

      str += pszSalt;

      primitive::memory key(get_app());

      key.from_string(str);

      return decrypt(storageDecrypt, storageEncrypt, key);

   }

   bool crypt::encrypt(primitive::memory & storageEncrypt, const primitive::memory & storageDecrypt, const char * pszSalt)
   {

      // default implementation - OS may implement its own HOME/UserDir encryption

      string str = defer_get_cryptkey();

      if(str.is_empty())
         return false;

      str += pszSalt;

      primitive::memory key(get_app());

      key.from_string(str);

      return encrypt(storageEncrypt, storageDecrypt, key);

   }



   int32_t crypt::key(primitive::memory & storage)
   {
      storage.allocate(16);
      for(primitive::memory_position i = 0; i < storage.get_size(); i++)
      {
         storage.get_data()[i] = rand() & 0xff;
      }
      return (int32_t) storage.get_size();
   }

   /**
   AES encryption/decryption demo program using OpenSSL EVP apis
   gcc -Wall openssl_aes.ca -lcrypto

   this is public domain code.

   Saju Pillai (saju.pillai@gmail.com)
   **/
   //http://stackoverflow.com/questions/10366950/openssl-using-evp-vs-algorithm-api-for-symmetric-crypto

   bool crypt::encrypt(primitive::memory & storageEncrypt, const primitive::memory & storageDecrypt, const primitive::memory & memKeyData)
   {

      primitive::memory memSha1(get_app());

      sha1(memSha1, memKeyData);

      primitive::memory iv(get_app());

      iv.allocate(32);

      iv.set(0);


#ifdef METROWIN

      ::Windows::Security::Cryptography::Core::SymmetricKeyAlgorithmProvider ^ cipher =
         ::Windows::Security::Cryptography::Core::SymmetricKeyAlgorithmProvider::OpenAlgorithm(::Windows::Security::Cryptography::Core::SymmetricAlgorithmNames::AesEcb);

      ::Windows::Security::Cryptography::Core::CryptographicKey ^ cipherkey = cipher->CreateSymmetricKey(memSha1.get_os_crypt_buffer());

      storageEncrypt.set_os_crypt_buffer(::Windows::Security::Cryptography::Core::CryptographicEngine::Encrypt(cipherkey, storageDecrypt.get_os_crypt_buffer(), iv.get_os_crypt_buffer()));

      return true;

#elif defined(MACOS)

      CFMutableDictionaryRef parameters = CFDictionaryCreateMutable(NULL, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);

      CFDictionaryAddValue(parameters, kSecAttrKeyType, kSecAttrKeyTypeAES);

      CFDataRef keyData = memSha1.get_os_cf_data();

      CFErrorRef error = NULL;

      SecKeyRef key = SecKeyCreateFromData(parameters, keyData, &error);

      if(error != NULL)
      {

         CFRelease(error);

         CFRelease(keyData);

         CFRelease(parameters);

         return false;

      }

      SecTransformRef transform = SecEncryptTransformCreate(key, &error);

      if(error != NULL)
      {

         CFRelease(error);

         CFRelease(key);

         CFRelease(keyData);

         CFRelease(parameters);

         return false;

      }

      SecTransformSetAttribute(transform, kSecPaddingKey, kSecPaddingPKCS1Key, &error);

      if(error != NULL)
      {

         CFRelease(transform);

         CFRelease(keyData);

         CFRelease(parameters);

         CFRelease(key);

         CFRelease(error);

         return false;

      }

      CFDataRef dataIv = iv.get_os_cf_data();

      SecTransformSetAttribute(transform, kSecIVKey, dataIv, &error);

      if(error != NULL)
      {

         CFRelease(dataIv);

         CFRelease(transform);

         CFRelease(parameters);

         CFRelease(keyData);

         CFRelease(key);

         CFRelease(error);

         return false;

      }

      CFDataRef dataIn = storageDecrypt.get_os_cf_data();

      SecTransformSetAttribute(transform, kSecTransformInputAttributeName, dataIn, &error);

      if(error != NULL)
      {

         CFRelease(dataIn);

         CFRelease(dataIv);

         CFRelease(transform);

         CFRelease(parameters);

         CFRelease(keyData);

         CFRelease(key);

         CFRelease(error);

         return false;

      }

      /* Encrypt the data. */

      CFDataRef data = (CFDataRef) SecTransformExecute(transform, &error);

      if(error != NULL)
      {

         CFRelease(dataIn);

         CFRelease(dataIv);

         CFRelease(transform);

         CFRelease(parameters);

         CFRelease(keyData);

         CFRelease(key);

         CFRelease(error);

         return false;

      }

      ::primitive::memory memory;

      storageEncrypt.set_os_cf_data(data);

      CFRelease(data);

      CFRelease(dataIv);

      CFRelease(dataIn);

      CFRelease(transform);

      CFRelease(keyData);

      CFRelease(parameters);

      CFRelease(key);

      return true;

#else

      int32_t plainlen = (int32_t) storageDecrypt.get_size();

      int32_t cipherlen, tmplen;

      EVP_CIPHER_CTX ctx;

      EVP_CIPHER_CTX_init(&ctx);

      EVP_EncryptInit(&ctx, EVP_aes_256_ecb(), memSha1.get_data(), iv.get_data());

      cipherlen = (int32_t) (storageDecrypt.get_size() + EVP_CIPHER_CTX_block_size(&ctx) - 1);

      storageEncrypt.allocate(cipherlen);

      if (!EVP_EncryptUpdate(&ctx,storageEncrypt.get_data(), &cipherlen, storageDecrypt.get_data(), plainlen))
      {

         storageEncrypt.allocate(0);

         EVP_CIPHER_CTX_cleanup(&ctx);

         return false;

      }

      if (!EVP_EncryptFinal(&ctx, storageEncrypt.get_data() + cipherlen, &tmplen))
      {

         storageEncrypt.allocate(0);

         EVP_CIPHER_CTX_cleanup(&ctx);

         return false;

      }

      cipherlen += tmplen;

      storageEncrypt.allocate(cipherlen);

      EVP_CIPHER_CTX_cleanup(&ctx);

      return true;

#endif

   }


   bool crypt::decrypt(primitive::memory & storageDecrypt, const primitive::memory & storageEncrypt, const primitive::memory & memKeyData)
   {

      primitive::memory memSha1;

      sha1(memSha1, memKeyData);

      primitive::memory iv;

      iv.allocate(32);

      iv.set(0);

#ifdef METROWIN

      ::Windows::Security::Cryptography::Core::SymmetricKeyAlgorithmProvider ^ cipher =
         ::Windows::Security::Cryptography::Core::SymmetricKeyAlgorithmProvider::OpenAlgorithm(::Windows::Security::Cryptography::Core::SymmetricAlgorithmNames::AesEcb);

      ::Windows::Security::Cryptography::Core::CryptographicKey ^ cipherkey = cipher->CreateSymmetricKey(memSha1.get_os_crypt_buffer());

      storageDecrypt.set_os_crypt_buffer(::Windows::Security::Cryptography::Core::CryptographicEngine::Decrypt(cipherkey, storageDecrypt.get_os_crypt_buffer(), iv.get_os_crypt_buffer()));

      return true;

#elif defined(MACOS)

      CFMutableDictionaryRef parameters = CFDictionaryCreateMutable(NULL, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);

      CFDictionaryAddValue(parameters, kSecAttrKeyType, kSecAttrKeyTypeAES);

      CFDataRef keyData = memSha1.get_os_cf_data();

      CFErrorRef error = NULL;

      SecKeyRef key = SecKeyCreateFromData(parameters, keyData, &error);

      if(error != NULL)
      {

         CFRelease(error);

         CFRelease(keyData);

         CFRelease(parameters);

         return false;

      }

      SecTransformRef transform = SecDecryptTransformCreate(key, &error);

      if(error != NULL)
      {

         CFRelease(error);

         CFRelease(key);

         CFRelease(keyData);

         CFRelease(parameters);

         return false;

      }

      SecTransformSetAttribute(transform, kSecPaddingKey, kSecPaddingPKCS1Key, &error);

      if(error != NULL)
      {

         CFRelease(transform);

         CFRelease(keyData);

         CFRelease(parameters);

         CFRelease(key);

         CFRelease(error);

         return false;

      }

      CFDataRef dataIv = iv.get_os_cf_data();

      SecTransformSetAttribute(transform, kSecIVKey, dataIv, &error);

      if(error != NULL)
      {

         CFRelease(dataIv);

         CFRelease(transform);

         CFRelease(parameters);

         CFRelease(keyData);

         CFRelease(key);

         CFRelease(error);

         return false;

      }

      CFDataRef dataIn = storageEncrypt.get_os_cf_data();

      SecTransformSetAttribute(transform, kSecTransformInputAttributeName, dataIn, &error);

      if(error != NULL)
      {

         CFRelease(dataIn);

         CFRelease(dataIv);

         CFRelease(transform);

         CFRelease(parameters);

         CFRelease(keyData);

         CFRelease(key);

         CFRelease(error);

         return false;

      }

      /* Encrypt the data. */

      CFDataRef data = (CFDataRef) SecTransformExecute(transform, &error);

      if(error != NULL)
      {

         CFRelease(dataIn);

         CFRelease(dataIv);

         CFRelease(transform);

         CFRelease(parameters);

         CFRelease(keyData);

         CFRelease(key);

         CFRelease(error);

         return false;

      }

      ::primitive::memory memory;

      storageDecrypt.set_os_cf_data(data);

      CFRelease(data);

      CFRelease(dataIv);

      CFRelease(dataIn);

      CFRelease(transform);

      CFRelease(keyData);

      CFRelease(parameters);

      CFRelease(key);

      return true;

#else

      int32_t cipherlen = (int32_t) storageEncrypt.get_size();

      int32_t plainlen, tmplen;

      EVP_CIPHER_CTX ctx;

      EVP_CIPHER_CTX_init(&ctx);

      EVP_DecryptInit(&ctx, EVP_aes_256_ecb(), memSha1.get_data(), iv.get_data());

      plainlen = (int32_t) storageEncrypt.get_size() + EVP_CIPHER_CTX_block_size(&ctx);

      storageDecrypt.allocate(plainlen);

      if(!EVP_DecryptUpdate(&ctx, storageDecrypt.get_data(), &plainlen, storageEncrypt.get_data(), cipherlen))
      {

         storageDecrypt.allocate(0);

         EVP_CIPHER_CTX_cleanup(&ctx);

         return false;

      }

      if (!EVP_DecryptFinal(&ctx, storageDecrypt.get_data() + plainlen, &tmplen))
      {

         storageDecrypt.allocate(0);

         EVP_CIPHER_CTX_cleanup(&ctx);

         return false;

      }

      plainlen += tmplen;

      storageDecrypt.allocate(plainlen);

      EVP_CIPHER_CTX_cleanup(&ctx);

      return true;

#endif

   }

   string crypt::strkey()
   {
      primitive::memory storage;
      key(storage);
      return System.base64().encode(storage);
   }

   int32_t crypt::encrypt(string & strEncrypt, const char * pszDecrypt, const char * pszKey)
   {
      primitive::memory storageDecrypt;
      primitive::memory storageEncrypt;
      primitive::memory storageKey;
      if(pszDecrypt == NULL || strlen(pszDecrypt) == 0)
      {
         strEncrypt = "";
         return 0;
      }
      storageDecrypt.from_string(pszDecrypt);
      System.base64().decode(storageKey, pszKey);
      int32_t cipherlen = encrypt(storageEncrypt, storageDecrypt, storageKey);
      strEncrypt = System.base64().encode(storageEncrypt);
      return cipherlen;
   }

   int32_t crypt::decrypt(string & strDecrypt, const char * pszEncrypt, const char * pszKey)
   {
      primitive::memory storageEncrypt;
      primitive::memory storageDecrypt;
      primitive::memory storageKey;
      System.base64().decode(storageEncrypt, pszEncrypt);
      System.base64().decode(storageKey, pszKey);
      int32_t plainlen = decrypt(storageDecrypt, storageEncrypt, storageKey);
      storageDecrypt.to_string(strDecrypt);
      return plainlen;
   }


   string crypt::md5(const char * psz)
   {

      primitive::memory buf;

      ::crypto::md5::context ctx(get_app());

      ctx.update(psz, strlen(psz));

      return ctx.to_hex();

   }


   string crypt::md5(const primitive::memory & mem)
   {

      primitive::memory memMd5;

      md5(memMd5, mem);

      return memMd5.to_hex();


   }

   void crypt::md5(primitive::memory & memMd5, const primitive::memory & mem)
   {

      ::crypto::md5::context ctx(get_app());

      ctx.update(mem, mem.get_size());

      ctx.get(memMd5);

   }

   string crypt::sha1(const primitive::memory & mem)
   {

      primitive::memory memSha1;

      sha1(memSha1, mem);

      return memSha1.to_hex();

   }

   void crypt::sha1(primitive::memory & memSha1, const primitive::memory & mem)
   {

      memSha1.allocate(32);

      crypto::sha1::CContext ctx;

      ctx.Init();

      ctx.update(mem, (int32_t) mem.get_size());

      ctx.Final(memSha1.get_data());

   }


   bool crypt::file_set(var varFile, const char * pszData, const char * pszSalt, sp(base_application) papp)
   {
      primitive::memory memoryEncrypt;
      encrypt(memoryEncrypt, pszData, pszSalt);
      App(papp).file().put_contents(varFile, memoryEncrypt);
      return true;
   }

   bool crypt::file_get(var varFile, string & str, const char * pszSalt, sp(base_application) papp)
   {
      primitive::memory memoryEncrypt;
      App(papp).file().as_memory(varFile, memoryEncrypt);
      decrypt(str, memoryEncrypt, pszSalt);
      return true;
   }

   bool crypt::encrypt(primitive::memory & storageEncrypt, const char * pszDecrypt, const char * pszSalt)
   {
      primitive::memory memoryDecrypt;
      memoryDecrypt.from_asc(pszDecrypt);
      return encrypt(storageEncrypt, memoryDecrypt, pszSalt);
   }

   bool crypt::decrypt(string & strDecrypt, const primitive::memory & storageEncrypt, const char * pszSalt)
   {
      primitive::memory memoryDecrypt;
      if(!decrypt(memoryDecrypt, storageEncrypt, pszSalt))
         return false;
      memoryDecrypt.to_asc(strDecrypt);
      return true;
   }


   // get a new salt - 8 hexadecimal characters long
   // current PHP installations should not exceed 8 characters
   // on dechex( mt_rand() )
   // but we future proof it anyway with substr()
   string crypt::v5_get_password_salt()
   {
      string strSalt;
      string strFormat;
      for(int32_t i = 0; i < CA4_CRYPT_V5_FINAL_HASH_BYTES - NESSIE_DIGESTBYTES; i+=2)
      {
         int64_t iDigit = System.math().RandRange(0, 255);
         strFormat.Format("%02x", iDigit);
         strSalt += strFormat;
      }
      return strSalt;
   }

   // calculate the hash from a salt and a password
   // slow hash is more secure for personal attack possibility (strong fast hashs are only good for single transactional operations and not for a possibly lifetime password)
   string crypt::v5_get_password_hash(const char * pszSalt, const char * pszPassword, int32_t iOrder)
   {
      string strHash(pszPassword);
      string strSalt(pszSalt);
      strSalt = strSalt.Left(CA4_CRYPT_V5_SALT_BYTES);
      for(int32_t i = iOrder; i < CA4_CRYPT_V5_FINAL_HASH_BYTES - NESSIE_DIGESTBYTES; i++)
      {
         string strStepSalt = strSalt.Mid(i) + strSalt.Left(i);
         strHash = nessie(strStepSalt + strHash);
      }
      return strSalt + strHash;
   }

   string crypt::v5_get_passhash(const char * pszSalt, const char * pszPassword, int32_t iMaxOrder)
   {
      string strHash(pszPassword);
      string strSalt(pszSalt);
      strSalt = strSalt.Left(CA4_CRYPT_V5_SALT_BYTES);
      for(int32_t i = 0; i < iMaxOrder; i++)
      {
         string strStepSalt = strSalt.Mid(i) + strSalt.Left(i);
         strHash = nessie(strStepSalt + strHash);
      }
      return strSalt + strHash;
   }

   bool crypt::v5_compare_password(const char * pszPassword, const char * pszHash, int32_t iOrder)
   {
      string strHash(pszHash);
      string strSalt = strHash.Left(CA4_CRYPT_V5_SALT_BYTES);
      return strHash == v5_get_password_hash(strSalt, pszPassword, iOrder);
   }

   bool crypt::v5_validate_plain_password(const char * pszPassword)
   {
      string str(pszPassword);
      if(str.get_length() < 6)
         return false;
      return ::str::has_all_v1(pszPassword);
   }

   string crypt::v5_get_password_hash(const char * pszPassword, int32_t iOrder)
   {
      return v5_get_password_hash(v5_get_password_salt(), pszPassword, iOrder);
   }

   uint32_t crypt::crc32(uint32_t dwPrevious, const char * psz)
   {
      return (uint32_t) ::crc32(dwPrevious, (const byte *) psz, (uInt) strlen(psz));
   }

   void crypt::hmac(void * result, const primitive::memory & memMessage, const primitive::memory & memKey)
   {

      crypto::hmac_sha1::context context;

      context.digest(result, memMessage.get_data(), (int32_t) memMessage.get_size(), memKey.get_data(), (int32_t) memKey.get_size());

   }

   void crypt::hmac(void * result, const string & strMessage, const string & strKey)
   {

      crypto::hmac_sha1::context context;

      context.digest(result, strMessage, (int32_t) strMessage.get_length(), strKey, (int32_t) strKey.get_length());

   }

   string crypt::get_crypt_key_file_path()
   {

      throw interface_only_exception(get_app());

   }


   string crypt::defer_get_cryptkey()
   {

      string strPath = get_crypt_key_file_path();

      string str = Application.file().as_string(strPath);

      if(str.has_char())
         return str;

      for(int32_t i = 0; i < 256; i++)
      {

         char ch = Application.math().rnd() % (10 + 26 + 26);

         if(ch < 10)
            ch += '0';
         else if(ch < (10 + 26))
            ch += 'a';
         else
            ch += 'A';

         str += ch;

      }

      Application.file().put_contents(strPath, str);

      return str;


   }


} // namespace core



/*

bool crypt_file_get(const char * pszFile, string & str, const char * pszSalt)
{

   string vsstr;

   if(!crypt_file_get(pszFile, vsstr, pszSalt))
      return false;

   str = vsstr;

   return true;

}


*/
