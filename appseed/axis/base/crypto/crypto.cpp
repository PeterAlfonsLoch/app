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



