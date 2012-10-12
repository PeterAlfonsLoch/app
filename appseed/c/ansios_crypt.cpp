//
//  ansios_crypt.cpp
//  c
//
//  Created by Carlos Gustavo Cecyn Lundgren on 10/12/12.
//
//
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