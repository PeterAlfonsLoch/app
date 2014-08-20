#include "framework.h"
#ifndef METROWIN
#include <openssl/rsa.h>
#include <openssl/ssl.h>
#include <openssl/md5.h>
#include <openssl/rsa.h>
#include <openssl/engine.h>
#include <openssl/err.h>
#include <openssl/crypto.h>
#include <openssl/hmac.h>
#include <openssl/whrlpool.h>
#endif

#define CA4_CRYPT_V5_FINAL_HASH_BYTES (WHIRLPOOL_DIGEST_LENGTH * 16)
#define CA4_CRYPT_V5_SALT_BYTES (CA4_CRYPT_V5_FINAL_HASH_BYTES - WHIRLPOOL_DIGEST_LENGTH)


namespace crypto
{


   crypto::crypto(sp(::axis::application) papp) :
      element(papp)
   {
   }

   crypto::~crypto()
   {
   }


   bool crypto::decrypt(primitive::memory & storageDecrypt, const primitive::memory & storageEncrypt, const char * pszSalt)
   {

      // default implementation - OS may implement its own HOME/UserDir encryption

      string str = defer_get_cryptkey();

      if (str.is_empty())
         return false;

      str += pszSalt;

      primitive::memory key(get_app());

      key.from_string(str);

      return decrypt(storageDecrypt, storageEncrypt, key);

   }

   bool crypto::encrypt(primitive::memory & storageEncrypt, const primitive::memory & storageDecrypt, const char * pszSalt)
   {

      // default implementation - OS may implement its own HOME/UserDir encryption

      string str = defer_get_cryptkey();

      if (str.is_empty())
         return false;

      str += pszSalt;

      primitive::memory key(get_app());

      key.from_string(str);

      return encrypt(storageEncrypt, storageDecrypt, key);

   }



   int32_t crypto::key(primitive::memory & storage)
   {
      storage.allocate(16);
      for (primitive::memory_position i = 0; i < storage.get_size(); i++)
      {
         storage.get_data()[i] = rand() & 0xff;
      }
      return (int32_t)storage.get_size();
   }

   /**
   AES encryption/decryption demo program using OpenSSL EVP apis
   gcc -Wall openssl_aes.ca -lcrypto

   this is public domain code.

   Saju Pillai (saju.pillai@gmail.com)
   **/
   //http://stackoverflow.com/questions/10366950/openssl-using-evp-vs-algorithm-api-for-symmetric-crypto

   bool crypto::encrypt(primitive::memory & storageEncrypt, const primitive::memory & storageDecrypt, const primitive::memory & memKeyData)
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

      int32_t plainlen = (int32_t)storageDecrypt.get_size();

      int32_t cipherlen, tmplen;

      EVP_CIPHER_CTX ctx;

      EVP_CIPHER_CTX_init(&ctx);

      EVP_EncryptInit(&ctx, EVP_aes_256_ecb(), memSha1.get_data(), iv.get_data());

      cipherlen = (int32_t)(storageDecrypt.get_size() + EVP_CIPHER_CTX_block_size(&ctx) - 1);

      storageEncrypt.allocate(cipherlen);

      if (!EVP_EncryptUpdate(&ctx, storageEncrypt.get_data(), &cipherlen, storageDecrypt.get_data(), plainlen))
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


   bool crypto::decrypt(primitive::memory & storageDecrypt, const primitive::memory & storageEncrypt, const primitive::memory & memKeyData)
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

      int32_t cipherlen = (int32_t)storageEncrypt.get_size();

      int32_t plainlen, tmplen;

      EVP_CIPHER_CTX ctx;

      EVP_CIPHER_CTX_init(&ctx);

      EVP_DecryptInit(&ctx, EVP_aes_256_ecb(), memSha1.get_data(), iv.get_data());

      plainlen = (int32_t)storageEncrypt.get_size() + EVP_CIPHER_CTX_block_size(&ctx);

      storageDecrypt.allocate(plainlen);

      if (!EVP_DecryptUpdate(&ctx, storageDecrypt.get_data(), &plainlen, storageEncrypt.get_data(), cipherlen))
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

   string crypto::strkey()
   {
      primitive::memory storage;
      key(storage);
      return System.base64().encode(storage);
   }

   int32_t crypto::encrypt(string & strEncrypt, const char * pszDecrypt, const char * pszKey)
   {
      primitive::memory storageDecrypt;
      primitive::memory storageEncrypt;
      primitive::memory storageKey;
      if (pszDecrypt == NULL || strlen(pszDecrypt) == 0)
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

   int32_t crypto::decrypt(string & strDecrypt, const char * pszEncrypt, const char * pszKey)
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


   string crypto::md5(const char * psz)
   {

      primitive::memory buf;

      ::md5::md5 md5;

      md5.initialize();

      md5.update(psz, strlen(psz));

      md5.finalize();

      return md5.to_string();

   }



   string crypto::md5(const primitive::memory & mem)
   {

      primitive::memory memMd5;

      md5(memMd5, mem);

      return memMd5.to_hex();


   }

   void crypto::md5(primitive::memory & memMd5, const primitive::memory & mem)
   {

      ::md5::md5 md5;

      md5.initialize();

      md5.update(mem, mem.get_size());

      md5.finalize();

      md5.get(memMd5);

   }

   string crypto::sha1(const primitive::memory & mem)
   {

      primitive::memory memSha1;

      sha1(memSha1, mem);

      return memSha1.to_hex();

   }

   string crypto::sha1(const char * psz)
   {

      primitive::memory memSha1;

      memSha1.allocate(32);

      string strSha1;

      SHA1((const unsigned char *) psz,strlen(psz),memSha1.get_data());

      strSha1 = memSha1.to_hex();

      return strSha1;

   }


   void crypto::sha1(primitive::memory & memSha1, const primitive::memory & mem)
   {

      memSha1.allocate(32);

      SHA1(mem.get_data(), mem.get_size(), memSha1.get_data());


   }


   bool crypto::file_set(var varFile, const char * pszData, const char * pszSalt, sp(::axis::application) papp)
   {
      primitive::memory memoryEncrypt;
      encrypt(memoryEncrypt, pszData, pszSalt);
      Sess(papp).file().put_contents(varFile, memoryEncrypt);
      return true;
   }

   bool crypto::file_get(var varFile, string & str, const char * pszSalt, sp(::axis::application) papp)
   {
      primitive::memory memoryEncrypt;
      Sess(papp).file().as_memory(varFile, memoryEncrypt);
      decrypt(str, memoryEncrypt, pszSalt);
      return true;
   }

   bool crypto::encrypt(primitive::memory & storageEncrypt, const char * pszDecrypt, const char * pszSalt)
   {
      primitive::memory memoryDecrypt;
      memoryDecrypt.from_asc(pszDecrypt);
      return encrypt(storageEncrypt, memoryDecrypt, pszSalt);
   }

   bool crypto::decrypt(string & strDecrypt, const primitive::memory & storageEncrypt, const char * pszSalt)
   {
      primitive::memory memoryDecrypt;
      if (!decrypt(memoryDecrypt, storageEncrypt, pszSalt))
         return false;
      memoryDecrypt.to_asc(strDecrypt);
      return true;
   }


   // get a new salt - 8 hexadecimal characters long
   // current PHP installations should not exceed 8 characters
   // on dechex( mt_rand() )
   // but we future proof it anyway with substr()
   string crypto::v5_get_password_salt()
   {
      string strSalt;
      string strFormat;
      for(int32_t i = 0; i < CA4_CRYPT_V5_FINAL_HASH_BYTES - WHIRLPOOL_DIGEST_LENGTH; i += 2)
      {
         int64_t iDigit = System.math().RandRange(0, 255);
         strFormat.Format("%02x", iDigit);
         strSalt += strFormat;
      }
      return strSalt;
   }

   // calculate the hash from a salt and a password
   // slow hash is more secure for personal attack possibility (strong fast hashs are only good for single transactional operations and not for a possibly lifetime password)
   string crypto::v5_get_password_hash(const char * pszSalt, const char * pszPassword, int32_t iOrder)
   {
      string strHash(pszPassword);
      string strSalt(pszSalt);
      strSalt = strSalt.Left(CA4_CRYPT_V5_SALT_BYTES);
      for(int32_t i = iOrder; i < CA4_CRYPT_V5_FINAL_HASH_BYTES - WHIRLPOOL_DIGEST_LENGTH; i++)
      {
         string strStepSalt = strSalt.Mid(i) + strSalt.Left(i);
         strHash = nessie(strStepSalt + strHash);
      }
      return strSalt + strHash;
   }

   string crypto::v5_get_passhash(const char * pszSalt, const char * pszPassword, int32_t iMaxOrder)
   {
      string strHash(pszPassword);
      string strSalt(pszSalt);
      strSalt = strSalt.Left(CA4_CRYPT_V5_SALT_BYTES);
      for (int32_t i = 0; i < iMaxOrder; i++)
      {
         string strStepSalt = strSalt.Mid(i) + strSalt.Left(i);
         strHash = nessie(strStepSalt + strHash);
      }
      return strSalt + strHash;
   }

   bool crypto::v5_compare_password(const char * pszPassword, const char * pszHash, int32_t iOrder)
   {
      string strHash(pszHash);
      string strSalt = strHash.Left(CA4_CRYPT_V5_SALT_BYTES);
      return strHash == v5_get_password_hash(strSalt, pszPassword, iOrder);
   }

   bool crypto::v5_validate_plain_password(const char * pszPassword)
   {
      string str(pszPassword);
      if (str.get_length() < 6)
         return false;
      return ::str::has_all_v1(pszPassword);
   }

   string crypto::v5_get_password_hash(const char * pszPassword, int32_t iOrder)
   {
      return v5_get_password_hash(v5_get_password_salt(), pszPassword, iOrder);
   }

   uint32_t crypto::crc32(uint32_t dwPrevious, const char * psz)
   {
      return (uint32_t) ::crc32(dwPrevious, (const byte *)psz, (uInt)strlen(psz));
   }


   void crypto::hmac(void * result, const primitive::memory & memMessage, const primitive::memory & memKey)
   {

      unsigned int md_len = 0;

      HMAC(EVP_sha1(), memKey.get_data(), memKey.get_size(), memMessage.get_data(), memMessage.get_size(), (unsigned char *) result, &md_len);

   }


   void crypto::hmac(void * result, const string & strMessage, const string & strKey)
   {

      unsigned int md_len = 0;

      HMAC(EVP_sha1(),strKey,strKey.length(),(const unsigned char *) (const char *) strMessage,strMessage.length(),(unsigned char *)result,&md_len);

   }

   string crypto::get_crypt_key_file_path()
   {

      throw interface_only_exception(get_app());

   }


   string crypto::defer_get_cryptkey()
   {

      string strPath = get_crypt_key_file_path();

      string str = Application.file().as_string(strPath);

      if (str.has_char())
         return str;

      for (int32_t i = 0; i < 256; i++)
      {

         char ch = System.math().rnd() % (10 + 26 + 26);

         if (ch < 10)
            ch += '0';
         else if (ch < (10 + 26))
            ch += 'a';
         else
            ch += 'A';

         str += ch;

      }

      Application.file().put_contents(strPath, str);

      return str;


   }


#ifdef MACOS_DEPRECATED


   SecKeyRef crypto::get_new_rsa_key()
   {

      CFMutableDictionaryRef parameters = CFDictionaryCreateMutable(NULL, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);

      CFDictionaryAddValue(parameters, kSecAttrKeyType, kSecAttrKeyTypeRSA);

      CFDictionaryAddValue(parameters, kSecAttrKeySizeInBits, (CFTypeRef)1024);

      SecKeyRef prsa = SecKeyGenerateSymmetric(parameters, NULL);

      if (prsa == NULL)
         return;

      CFRelease(parameters);

      return rsa;

   }

   void crypto::free_rsa_key(SecKeyRef prsa)
   {

      CFRelease(prsa);

   }


#elif defined(BSD_STYLE_SOCKETS)


   sp(::crypto::rsa) crypto::generate_rsa_key()
   {

      sp(::crypto::rsa) rsa = canew(::crypto::rsa(get_app()));

      RSA * & prsa = rsa->m_prsa;

      prsa = RSA_generate_key(1024, 65537, NULL, NULL);

      char * n      = BN_bn2hex(prsa->n);
      char * e      = BN_bn2hex(prsa->e);
      char * d      = BN_bn2hex(prsa->d);
      char * p      = BN_bn2hex(prsa->p);
      char * q      = BN_bn2hex(prsa->q);
      char * dmp1   = BN_bn2hex(prsa->dmp1);
      char * dmq1   = BN_bn2hex(prsa->dmq1);
      char * iqmp   = BN_bn2hex(prsa->iqmp);

      rsa->n = n;
      rsa->e = e;
      rsa->d = d;
      rsa->p = p;
      rsa->q = q;
      rsa->dmp1 = dmp1;
      rsa->dmq1 = dmq1;
      rsa->iqmp = iqmp;

      OPENSSL_free(n);
      OPENSSL_free(e);
      OPENSSL_free(d);
      OPENSSL_free(p);
      OPENSSL_free(q);
      OPENSSL_free(dmp1);
      OPENSSL_free(dmq1);
      OPENSSL_free(iqmp);

      return rsa;

   }




#else


   sp(::crypto::rsa) crypto::generate_rsa_key()
   {

      ::Windows::Security::Cryptography::Core::AsymmetricKeyAlgorithmProvider ^ provider =
         ::Windows::Security::Cryptography::Core::AsymmetricKeyAlgorithmProvider::OpenAlgorithm(
         ::Windows::Security::Cryptography::Core::AsymmetricAlgorithmNames::RsaPkcs1);

      
      return canew(::crypto::rsa(get_app(), provider->CreateKeyPair(1024)));

   }

   /*void crypto::free_rsa_key(sp(::crypto::rsa) prsa)
   {

      UNREFERENCED_PARAMETER(prsa);

   }*/

#endif

   void crypto::err_load_rsa_strings()
   {
#if defined(BSD_STYLE_SOCKETS)
      ERR_load_RSA_strings();

#endif

   }


   void crypto::err_load_crypto_strings()
   {

#if defined(BSD_STYLE_SOCKETS)
      ERR_load_crypto_strings();
#endif

   }


   rsa::rsa(sp(::axis::application) papp) :
      element(papp),
      m_mutex(papp)
   {
#ifdef METROWIN

      m_prsa = nullptr;
#else
      m_prsa = NULL;
#endif

   }


   rsa::rsa(sp(::axis::application) papp, const string & nParam)
   {

#ifdef MACOS_DEPRECATED

      CFMutableDictionaryRef parameters = CFDictionaryCreateMutable(NULL, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);

      CFDictionaryAddValue(parameters, kSecAttrKeyType, kSecAttrKeyTypeRSA);

      // not needed, defaults to true    CFDictionaryAddValue(parameters, kSecAttrCanEncrypt, kCFBooleanTrue);

      primitive::memory memKeyData;

      memKeyData.from_hex(strPass);

      CFDataRef keyData = memKeyData.get_os_cf_data();

      CFErrorRef error = NULL;

      m_prsa = SecKeyCreateFromData(parameters, keyData, &error);

      if (error != NULL)
      {

         CFRelease(parameters);

         CFRelease(keyData);

         CFRelease(error);

         throw resource_exception(get_app());

      }

      CFRelease(parameters);

      CFRelease(keyData);


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

      ::file::memory_buffer memfile(get_app());

      blob.Magic = 0x31415352; // BCRYPT_RSAPUBLIC_MAGIC;
      blob.BitLength = 1024;
      blob.cbPublicExp = 3;
      blob.cbModulus = 1024 / 8;
      blob.cbPrime1 = 0;
      blob.cbPrime2 = 0;

      primitive::memory memVer(get_app());

      memVer.from_hex("00");

      memVer.prefix_der_uint();

      memfile.write(&blob, sizeof(blob));

      primitive::memory memMod(get_app());

      string strRsaModulus(nParam);

      memMod.from_hex(strRsaModulus);

      //memMod.reverse();



      //memMod.prefix_der_uint();

      primitive::memory memExp(get_app());

      memExp.from_hex("10001");

      //memExp.reverse();

      memfile.write(memExp.get_data(), memExp.get_size());

      memfile.write(memMod.get_data(), memMod.get_size());

      //memExp.prefix_der_uint();

      ::Windows::Security::Cryptography::Core::AsymmetricKeyAlgorithmProvider ^ cipher =
         ::Windows::Security::Cryptography::Core::AsymmetricKeyAlgorithmProvider::OpenAlgorithm(::Windows::Security::Cryptography::Core::AsymmetricAlgorithmNames::RsaPkcs1);


      primitive::memory memKey(get_app());

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

      m_prsa = cipher->ImportPublicKey(memfile.get_memory()->get_os_crypt_buffer(), ::Windows::Security::Cryptography::Core::CryptographicPublicKeyBlobType::BCryptPublicKey);

#else

      m_prsa = RSA_new();

      n = nParam;
      e = "10001";

      BN_hex2bn(&m_prsa->n, n);
      BN_hex2bn(&m_prsa->e, e);

#endif

   }

#ifdef BSD_STYLE_SOCKETS

   rsa::rsa(sp(::axis::application) papp,
      const string & n,
      const string & e,
      const string & d,
      const string & p,
      const string & q,
      const string & dmp1,
      const string & dmq1,
      const string & iqmp) :
      element(papp),
      m_mutex(papp)
   {

      m_prsa = RSA_new();

      BN_hex2bn(&m_prsa->n, n);
      BN_hex2bn(&m_prsa->e, e);
      BN_hex2bn(&m_prsa->d, d);
      BN_hex2bn(&m_prsa->p, p);
      BN_hex2bn(&m_prsa->q, q);
      BN_hex2bn(&m_prsa->dmp1, dmp1);
      BN_hex2bn(&m_prsa->dmq1, dmq1);
      BN_hex2bn(&m_prsa->iqmp, iqmp);

   }

#endif

   rsa::~rsa()
   {

#ifdef MACOS_DEPRECATED
      if (m_prsa != NULL)
      {

         CFRelease(m_prsa);
         m_prsa = NULL;
      }
#elif defined(METROWIN)

      m_prsa = nullptr;

#else
      if (m_prsa != NULL)
      {

         RSA_free(m_prsa);
         m_prsa = NULL;

      }
#endif

   }
   
   int rsa::public_encrypt(::primitive::memory & out, const ::primitive::memory & in, string & strError)
   {
#ifdef MACOS_DEPRECATED


      SecTransformRef transform = SecEncryptTransformCreate(m_prsa, &error);

      if (error != NULL)
      {

         CFRelease(error);

         return "";

      }

      SecTransformSetAttribute(transform, kSecPaddingKey, kSecPaddingPKCS1Key, &error);

      if (error != NULL)
      {

         CFRelease(transform);

         CFRelease(error);

         return "";

      }

      primitive::memory memDataIn;

      memDataIn.from_hex(strRsaModulus);

      CFDataRef dataIn = memDataIn.get_os_cf_data();

      SecTransformSetAttribute(transform, kSecTransformInputAttributeName, dataIn, &error);

      if (error != NULL)
      {

         CFRelease(dataIn);

         CFRelease(transform);

         CFRelease(error);

         return "";

      }

      /* Encrypt the data. */

      CFDataRef data = (CFDataRef)SecTransformExecute(transform, &error);

      if (error != NULL)
      {

         CFRelease(dataIn);

         CFRelease(transform);

         CFRelease(error);

         return "";

      }


      string strHex;

      primitive::memory memory;

      memory.set_os_cf_data(data);

      memory.to_hex(strHex);

      CFRelease(data);

      CFRelease(dataIn);

      CFRelease(transform);

#elif defined(METROWIN)



      out.set_os_crypt_buffer(::Windows::Security::Cryptography::Core::CryptographicEngine::Encrypt(m_prsa, in.get_os_crypt_buffer(), nullptr));




#else

      int32_t i = RSA_public_encrypt((int32_t)in.get_size(), (const uchar *)(const char *)in.get_data(), out.get_data(), m_prsa, RSA_PKCS1_PADDING);

      strError = ERR_error_string(ERR_get_error(), NULL);

      out.allocate(i);



#endif

      return out.get_size();


   }

   int rsa::private_decrypt(::primitive::memory & out, const ::primitive::memory & in, string & strError)
   {


#if defined(METROWIN)



out.set_os_crypt_buffer(::Windows::Security::Cryptography::Core::CryptographicEngine::Decrypt(m_prsa, in.get_os_crypt_buffer(), nullptr));




#else

      single_lock sl(&m_mutex, true);
      
      int32_t iRsaSize = 8192;

      out.allocate(iRsaSize);

      ::count i = RSA_private_decrypt((int)in.get_size(), in.get_data(), out.get_data(), m_prsa, RSA_PKCS1_PADDING);

      if (i < 0 || i >(1024 * 1024))
      {
         
         strError = ERR_error_string(ERR_get_error(), NULL);

         return (int)i;

      }

      out.allocate(i);

#endif

      return out.get_size();

   }

   string crypto::spa_login_crypt(const char * psz, const char * pszRsa)
   {

      sp(::crypto::rsa) prsa = canew(::crypto::rsa(get_app(), pszRsa));

      primitive::memory memory;

      primitive::memory memIn;

      hex_to_memory(memIn, psz);

      memory.allocate(2048);

      string strError;

      int i = prsa->public_encrypt(memory, memIn, strError);

      if (i < 0 || i >(1024 * 1024))
      {

         TRACE0(strError);

      }

      string strHex;

      memory_to_hex(strHex, memory);

      return strHex;

   }


   void crypto::np_make_zigbert_rsa(const string & strDir, const string & strSignerPath, const string & strKeyPath, const string & strOthersPath, const string & strSignature)
   {
#ifndef METROWIN
      X509 * signer = NULL;
      {
         string strSigner = Application.file().as_string(strSignerPath);
         BIO * pbio = BIO_new_mem_buf((void *)(LPCTSTR)strSigner, (int32_t)strSigner.get_length());
         //signer = PEM_read_bio_X509_AUX(pbio, NULL, 0, NULL);
         signer = PEM_read_bio_X509(pbio, NULL, 0, NULL);
         BIO_free(pbio);
      }

      EVP_PKEY * pkey;
      {
         string strKey = Application.file().as_string(strKeyPath);
         BIO * pbio = BIO_new_mem_buf((void *)(LPCTSTR)strKey, (int32_t)strKey.get_length());
         pkey = PEM_read_bio_PrivateKey(pbio, NULL, NULL, NULL);
         BIO_free(pbio);
      }


      stack_st_X509 * pstack509 = NULL;
      {
         string strOthers = Application.file().as_string(strOthersPath);
         array < X509 * > xptra;
         strsize iStart = 0;
         strsize iFind;
         string strEnd = "-----END CERTIFICATE-----";
         string strCertificate;
         strsize iEndLen = strEnd.get_length();
         ::count iCount = 0;
         while ((iFind = strOthers.find("-----BEGIN CERTIFICATE-----", iStart)) >= 0)
         {
            strsize iEnd = strOthers.find(strEnd, iFind);
            if (iEnd < 0)
               break;
            strCertificate = strOthers.Mid(iFind, iEnd + iEndLen - iFind);
            X509 * x;
            BIO * pbio = BIO_new(BIO_s_mem());
            BIO_puts(pbio, strCertificate);
            //x = PEM_read_bio_X509_AUX(pbio, NULL, 0, NULL);
            x = PEM_read_bio_X509(pbio, NULL, 0, NULL);
            BIO_free(pbio);
            if (x == NULL)
            {
               return;
            }
            xptra.add(x);
            iCount++;
            iStart = iEnd + iEndLen;
         }
         pstack509 = sk_X509_new_null();

         for (int32_t i = 0; i < xptra.get_count(); i++)
         {
            sk_X509_push(pstack509, xptra[i]);
         }
      }

      BIO * input = BIO_new_mem_buf((void *)(LPCTSTR)strSignature, (int32_t)strSignature.get_length());

      PKCS7 * pkcs7 = PKCS7_sign(signer, pkey, pstack509, input, PKCS7_BINARY | PKCS7_DETACHED);

      BIO_free(input);
      sk_X509_free(pstack509);
      EVP_PKEY_free(pkey);
      X509_free(signer);

      BIO * output = BIO_new(BIO_s_mem());

      i2d_PKCS7_bio(output, pkcs7);

      char * pchData = NULL;
      long count = BIO_get_mem_data(output, &pchData);

      Application.file().put_contents(System.dir().path(strDir, "META-INF/zigbert.rsa"), pchData, count);

      BIO_free(output);
      PKCS7_free(pkcs7);
#endif
   }

} // namespace crypto




void
stunCalculateIntegrity_longterm(char* hmac, const char* input, int32_t length,
const char *username, const char *realm, const char *password)
{

#ifndef METROWIN
   uint32_t resultSize = 0;
   uchar HA1[16];
   char HA1_text[1024];

   snprintf(HA1_text, sizeof(HA1_text), "%s:%s:%s", username, realm, password);
   MD5((uchar *)HA1_text, strlen(HA1_text), HA1);

   HMAC(EVP_sha1(),
      HA1, 16,
      (const uchar*)input, length,
      (uchar*)hmac, &resultSize);
#endif
}

void
stunCalculateIntegrity_shortterm(char* hmac, const char* input, int32_t length, const char* key)
{
#ifndef METROWIN
   uint32_t resultSize = 0;
   HMAC(EVP_sha1(),
      key, (int)strlen(key),
      (const uchar*)input, length,
      (uchar*)hmac, &resultSize);
#endif
}

void hmac_evp_sha1_1234(unsigned char * hmac, unsigned int * hmacSize, const unsigned char * buf, size_t bufLen)
{
#ifndef METROWIN
   
   HMAC(EVP_sha1(),
      "1234", 4,
      (const uchar*)buf, bufLen - 20 - 4,
      hmac, hmacSize);
#endif

}

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
