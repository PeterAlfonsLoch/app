#include "framework.h"
#include <openssl/ssl.h>
#include <openssl/md5.h>
#include <openssl/err.h>


int crypt_encrypt(simple_memory & storageEncrypt, const simple_memory & storageDecrypt, simple_memory & key)
{
   int plainlen = (int) storageDecrypt.get_size();
   int cipherlen, tmplen;
   unsigned char iv[8] = {1,2,3,4,5,6,7,8};
   EVP_CIPHER_CTX ctx;
   EVP_CIPHER_CTX_init(&ctx);
   EVP_EncryptInit(&ctx,EVP_bf_cbc(),(unsigned char *) key.get_data(),iv);
   cipherlen = (int) (storageDecrypt.get_size() + 16 - 1); //; 16 = key size
   storageEncrypt.allocate(cipherlen);
   if (!EVP_EncryptUpdate(&ctx,(unsigned char *) storageEncrypt.get_data(),&cipherlen, (const unsigned char *) storageDecrypt.get_data(),plainlen))
   {
      return -1;
   }
   if (!EVP_EncryptFinal(&ctx,((unsigned char *) storageEncrypt.get_data())+cipherlen,&tmplen))
   {
      return -1;
   }
   cipherlen += tmplen;
   storageEncrypt.allocate(cipherlen);
   EVP_CIPHER_CTX_cleanup(&ctx);
   return cipherlen;
}

int crypt_decrypt(simple_memory & storageDecrypt, const simple_memory & storageEncrypt, simple_memory & key)
{
   int cipherlen = (int) storageEncrypt.get_size();
   int plainlen, tmplen;
   unsigned char iv[8] = {1,2,3,4,5,6,7,8};
   EVP_CIPHER_CTX ctx;
   EVP_CIPHER_CTX_init(&ctx);
   EVP_DecryptInit(&ctx,EVP_bf_cbc(), (const unsigned char *) key.get_data(),iv);
   plainlen = (int) storageEncrypt.get_size();
   storageDecrypt.allocate(plainlen);
   if(!EVP_DecryptUpdate(&ctx, (unsigned char *) storageDecrypt.get_data(),&plainlen, (const unsigned char *) storageEncrypt.get_data(),cipherlen))
   {
      return -1;
   }
   if (!EVP_DecryptFinal(&ctx,((unsigned char *) storageDecrypt.get_data())+plainlen,&tmplen))
   {
      storageDecrypt.allocate(plainlen);
      EVP_CIPHER_CTX_cleanup(&ctx);
      return plainlen;
   }
   plainlen += tmplen;
   storageDecrypt.allocate(plainlen);
   EVP_CIPHER_CTX_cleanup(&ctx);
   return plainlen;
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





CLASS_DECL_c vsstring spa_login_crypt(const char * psz, const char * pszRsa)
{

   RSA * rsa = RSA_new();

   BN_hex2bn(&rsa->n, pszRsa);
   BN_hex2bn(&rsa->e, "10001");


   simple_memory memory;
   simple_memory memIn;

   memIn.from_hex(psz);

   memory.allocate(2048);

   int i = RSA_public_encrypt((int) memIn.get_size(), (const unsigned char * ) (const char *) memIn.get_data(), (unsigned char *)  memory.get_data(), rsa, RSA_PKCS1_PADDING);

   const char * pszError = ERR_error_string(ERR_get_error(), NULL);

   //TRACE(psz);


   memory.allocate(i);

   vsstring strHex;

   memory.to_hex(strHex);

   RSA_free(rsa);

   return strHex;

}



