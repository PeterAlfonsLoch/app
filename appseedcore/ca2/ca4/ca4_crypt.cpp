#include "StdAfx.h"


#include "ca4_nessie.h"


#include <wincrypt.h>



void NESSIEinit(struct NESSIEstruct * const structpointer);
void NESSIEadd(const unsigned char * const source, unsigned long sourceBits, struct NESSIEstruct * const structpointer);
void NESSIEfinalize(struct NESSIEstruct * const structpointer, unsigned char * const result);


#define V5_FINAL_HASH_BYTES (DIGESTBYTES * 16)
#define V5_SALT_BYTES (V5_FINAL_HASH_BYTES - DIGESTBYTES)


namespace ca4
{

   crypt::crypt()
   {
   }

   crypt::~crypt()
   {
   }

   bool crypt::decrypt(primitive::memory & storageDecrypt, primitive::memory & storageEncrypt, const char * pszSalt)
   {
      DATA_BLOB DataIn;
      DATA_BLOB DataOut;

      if(pszSalt == NULL)
         pszSalt = "";

      DATA_BLOB DataSalt;
      primitive::memory memorySalt;
      memorySalt.from_string(pszSalt);
      DataSalt.pbData = memorySalt.GetAllocation();    
      DataSalt.cbData = memorySalt.GetStorageSize();

      //--------------------------------------------------------------------
      // Initialize the DataIn structure.

      DataIn.pbData = storageEncrypt.GetAllocation();    
      DataIn.cbData = storageEncrypt.GetStorageSize();

      wchar_t * lpwsz = NULL;

      //--------------------------------------------------------------------
      //  Begin protect phase. Note that the encryption key is created
      //  by the function and is not passed.

      if(CryptUnprotectData(
         &DataIn,
         NULL, // A description string
                                            // to be included with the
                                            // encrypted data. 
         &DataSalt,                               // Optional entropy not used.
         NULL,                               // Reserved.
         NULL,                               // Pass NULL for the 
                                            // prompt structure.
         0,
         &DataOut))
      {
         TRACE("crypt::decrypt The encryption phase worked. \n");
         storageDecrypt.allocate(DataOut.cbData);
         memcpy(storageDecrypt.GetAllocation(), DataOut.pbData, DataOut.cbData);
         LocalFree(lpwsz);
         LocalFree(DataOut.pbData);
         return true;
      }
      else
      {
         TRACELASTERROR();
         TRACE("crypt::decrypt Decryption error! (1)");
         return false;
      }
   }

   int crypt::key(primitive::memory & storage)
   {
      storage.allocate(16);
      for(int i = 0; i < storage.GetStorageSize(); i++)
      {
         storage.GetAllocation()[i] = rand() & 0xff;
      }
      return storage.GetStorageSize();
   }

   bool crypt::encrypt(primitive::memory & storageEncrypt, primitive::memory & storageDecrypt, const char * pszSalt)
   {
      DATA_BLOB DataIn;
      DATA_BLOB DataOut;

      if(pszSalt == NULL)
         pszSalt = "";

      DATA_BLOB DataSalt;
      primitive::memory memorySalt;
      memorySalt.from_string(pszSalt);
      DataSalt.pbData = memorySalt.GetAllocation();    
      DataSalt.cbData = memorySalt.GetStorageSize();


      //--------------------------------------------------------------------
      // Initialize the DataIn structure.

      DataIn.pbData = (BYTE *) storageDecrypt.GetAllocation();    
      DataIn.cbData = storageDecrypt.GetStorageSize();

//      wchar_t * lpwsz = NULL;

      //--------------------------------------------------------------------
      //  Begin protect phase. Note that the encryption key is created
      //  by the function and is not passed.

      if(CryptProtectData(
           &DataIn,
           NULL, // A description string
                                               // to be included with the
                                               // encrypted data. 
           &DataSalt,                               // Optional entropy not used.
           NULL,                               // Reserved.
           NULL,                               // Pass NULL for the 
                                               // prompt structure.
           0,
           &DataOut))
      {
         TRACE("crypt::encrypt The encryption phase worked. \n");
         storageEncrypt.allocate(DataOut.cbData);
         memcpy(storageEncrypt.GetAllocation(), DataOut.pbData, DataOut.cbData);
         LocalFree(DataOut.pbData);
         return true;
      }
      else
      {
         TRACE("crypt::encrypt Encryption error! (1)");
          return false;
      }

   }

   int crypt::encrypt(primitive::memory & storageEncrypt, primitive::memory & storageDecrypt, primitive::memory & key)
   { 
      int plainlen = storageDecrypt.GetStorageSize();
      int cipherlen, tmplen;
      unsigned char iv[8] = {1,2,3,4,5,6,7,8};
      EVP_CIPHER_CTX ctx;
      EVP_CIPHER_CTX_init(&ctx);
      EVP_EncryptInit(&ctx,EVP_bf_cbc(),key.GetAllocation(),iv);
      cipherlen = storageDecrypt.GetStorageSize() + 16 - 1; //; 16 = key size
      storageEncrypt.allocate(cipherlen);
      if (!EVP_EncryptUpdate(&ctx,storageEncrypt.GetAllocation(),&cipherlen,storageDecrypt.GetAllocation(),plainlen))
      {
         return -1;
      }
      if (!EVP_EncryptFinal(&ctx,storageEncrypt.GetAllocation()+cipherlen,&tmplen))
      {
         return -1;
      }
      cipherlen += tmplen;
      storageEncrypt.allocate(cipherlen);
      EVP_CIPHER_CTX_cleanup(&ctx);
      return cipherlen; 
   }


   int crypt::decrypt(primitive::memory & storageDecrypt, primitive::memory & storageEncrypt, primitive::memory & key)
   {
      int cipherlen = storageEncrypt.GetStorageSize();
      int plainlen, tmplen;
      unsigned char iv[8] = {1,2,3,4,5,6,7,8};
      EVP_CIPHER_CTX ctx;
      EVP_CIPHER_CTX_init(&ctx);
      EVP_DecryptInit(&ctx,EVP_bf_cbc(),key.GetAllocation(),iv);
      plainlen = storageEncrypt.GetStorageSize();
      storageDecrypt.allocate(plainlen);
      if(!EVP_DecryptUpdate(&ctx,storageDecrypt.GetAllocation(),&plainlen,storageEncrypt.GetAllocation(),cipherlen))
      {
         return -1;
      }
      if (!EVP_DecryptFinal(&ctx,storageDecrypt.GetAllocation()+plainlen,&tmplen))
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

   string crypt::strkey()
   {
      primitive::memory storage;
      key(storage);
      return System.base64().encode(storage);
   }

   int crypt::encrypt(string & strEncrypt, const char * pszDecrypt, const char * pszKey)
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
      System.base64().decode(pszKey, storageKey);
      int cipherlen = encrypt(storageEncrypt, storageDecrypt, storageKey);
      strEncrypt = System.base64().encode(storageEncrypt);
      return cipherlen;
   }

   int crypt::decrypt(string & strDecrypt, const char * pszEncrypt, const char * pszKey)
   {
      primitive::memory storageEncrypt;
      primitive::memory storageDecrypt;
      primitive::memory storageKey;
      System.base64().decode(pszEncrypt, storageEncrypt);
      System.base64().decode(pszKey, storageKey);
      int plainlen = decrypt(storageDecrypt, storageEncrypt, storageKey);
      storageDecrypt.to_string(strDecrypt);
      return plainlen;
   }


   string crypt::md5(const char * psz)
   {
      int iBufSize = 16;
      unsigned char * buf = new unsigned char[iBufSize];
      MD5_CTX ctx;
      MD5_Init(&ctx);
      //int iRead;
      MD5_Update(&ctx, psz, strlen(psz));
      MD5_Final(buf,&ctx);
      string str;
      string strFormat;
      for(int i = 0; i < 16; i++)
      {
         strFormat.Format("%02x", buf[i]);
         str += strFormat;
      }
      delete [] buf;
      return str;
   }


   bool crypt::file_set(const char * pszFile, const char * pszData, const char * pszSalt)
   {
      primitive::memory memoryEncrypt;
      encrypt(memoryEncrypt, pszData, pszSalt);
      System.file().put_contents(pszFile, memoryEncrypt);
      return true;
   }
   
   bool crypt::file_get(const char * pszFile, string & str, const char * pszSalt)
   {
      primitive::memory memoryEncrypt;
      System.file().as_memory(pszFile, memoryEncrypt, &System);
      decrypt(str, memoryEncrypt, pszSalt);
      return true;
   }

   bool crypt::encrypt(primitive::memory & storageEncrypt, const char * pszDecrypt, const char * pszSalt)
   {
      primitive::memory memoryDecrypt;
      memoryDecrypt.FromAsc(pszDecrypt);
      return encrypt(storageEncrypt, memoryDecrypt, pszSalt);
   }

   bool crypt::decrypt(string & strDecrypt, primitive::memory & storageEncrypt, const char * pszSalt)
   {
      primitive::memory memoryDecrypt;
      if(!decrypt(memoryDecrypt, storageEncrypt, pszSalt))
         return false;
      memoryDecrypt.ToAsc(strDecrypt);
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
      for(int i = 0; i < V5_FINAL_HASH_BYTES - DIGESTBYTES; i+=2)
      {
         int iDigit = System.math().RandRange(0, 255);
         strFormat.Format("%02x", iDigit);
         strSalt += strFormat;
      }
      return strSalt;
   }

   // calculate the hash from a salt and a password
   // slow hash is more secure for personal attack possibility (strong fast hashs are only good for single transactional operations and not for a possibly lifetime password)
   string crypt::v5_get_password_hash(const char * pszSalt, const char * pszPassword, int iOrder)
   {
      string strHash;
      if(iOrder <= 0)
      {
         strHash = nessie(pszPassword);
      }
      else
      {
         strHash = pszPassword;
      }
      string strSalt(pszSalt);
      strSalt = strSalt.Left(V5_SALT_BYTES);
      for(int i = iOrder; i < V5_FINAL_HASH_BYTES - DIGESTBYTES; i++)
      {
         string strStepSalt = strSalt.Mid(i) + strSalt.Left(i);
         strHash = nessie(strStepSalt + strHash);
      }
      return strSalt + strHash;
   }

   string crypt::v5_get_passhash(const char * pszSalt, const char * pszPassword, int iMaxOrder)
   {
      string strHash;
      strHash = nessie(pszPassword);
      string strSalt(pszSalt);
      strSalt = strSalt.Left(V5_SALT_BYTES);
      for(int i = 0; i < iMaxOrder; i++)
      {
         string strStepSalt = strSalt.Mid(i) + strSalt.Left(i);
         strHash = nessie(strStepSalt + strHash);
      }
      return strSalt + strHash;
   }

   bool crypt::v5_compare_password(const char * pszPassword, const char * pszHash, int iOrder)
   {
      string strHash(pszHash);
      string strSalt = strHash.Left(V5_SALT_BYTES);
      return strHash == v5_get_password_hash(strSalt, pszPassword, iOrder);
   }

   bool crypt::v5_validate_plain_password(const char * pszPassword)
   {
      string str(pszPassword);
      if(str.get_length() < 6)
         return false;
      return gen::str::has_all_v1(pszPassword);
   }

   string crypt::v5_get_password_hash(const char * pszPassword, int iOrder)
   {
      return v5_get_password_hash(v5_get_password_salt(), pszPassword, iOrder);
   }

   DWORD crypt::crc32(DWORD dwPrevious, const char * psz, int iCount)
   {
      if(iCount < 0)
         iCount = strlen(psz);
      return ::crc32(dwPrevious, (const Bytef *) psz, iCount);
   }

} // namespace ca4