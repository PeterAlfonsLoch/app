#include "framework.h"
#include <openssl/ssl.h>
#include <openssl/md5.h>


#define V5_FINAL_HASH_BYTES (DIGESTBYTES * 16)
#define V5_SALT_BYTES (V5_FINAL_HASH_BYTES - DIGESTBYTES)


namespace ca4
{


   crypt::crypt(::ca::application * papp) :
      ca(papp)
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



   int crypt::key(primitive::memory & storage)
   {
      storage.allocate(16);
      for(primitive::memory_position i = 0; i < storage.get_size(); i++)
      {
         storage.get_data()[i] = rand() & 0xff;
      }
      return (int) storage.get_size();
   }


   int crypt::encrypt(primitive::memory & storageEncrypt, const primitive::memory & storageDecrypt, primitive::memory & key)
   {
      int plainlen = (int) storageDecrypt.get_size();
      int cipherlen, tmplen;
      unsigned char iv[8] = {1,2,3,4,5,6,7,8};
      EVP_CIPHER_CTX ctx;
      EVP_CIPHER_CTX_init(&ctx);
      EVP_EncryptInit(&ctx,EVP_bf_cbc(),key.get_data(),iv);
      cipherlen = (int) (storageDecrypt.get_size() + 16 - 1); //; 16 = key size
      storageEncrypt.allocate(cipherlen);
      if (!EVP_EncryptUpdate(&ctx,storageEncrypt.get_data(),&cipherlen, storageDecrypt.get_data(),plainlen))
      {
         return -1;
      }
      if (!EVP_EncryptFinal(&ctx,storageEncrypt.get_data()+cipherlen,&tmplen))
      {
         return -1;
      }
      cipherlen += tmplen;
      storageEncrypt.allocate(cipherlen);
      EVP_CIPHER_CTX_cleanup(&ctx);
      return cipherlen;
   }


   int crypt::decrypt(primitive::memory & storageDecrypt, const primitive::memory & storageEncrypt, primitive::memory & key)
   {
      int cipherlen = (int) storageEncrypt.get_size();
      int plainlen, tmplen;
      unsigned char iv[8] = {1,2,3,4,5,6,7,8};
      EVP_CIPHER_CTX ctx;
      EVP_CIPHER_CTX_init(&ctx);
      EVP_DecryptInit(&ctx,EVP_bf_cbc(),key.get_data(),iv);
      plainlen = (int) storageEncrypt.get_size();
      storageDecrypt.allocate(plainlen);
      if(!EVP_DecryptUpdate(&ctx,storageDecrypt.get_data(),&plainlen,storageEncrypt.get_data(),cipherlen))
      {
         return -1;
      }
      if (!EVP_DecryptFinal(&ctx,storageDecrypt.get_data()+plainlen,&tmplen))
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
      System.base64().decode(storageKey, pszKey);
      int cipherlen = encrypt(storageEncrypt, storageDecrypt, storageKey);
      strEncrypt = System.base64().encode(storageEncrypt);
      return cipherlen;
   }

   int crypt::decrypt(string & strDecrypt, const char * pszEncrypt, const char * pszKey)
   {
      primitive::memory storageEncrypt;
      primitive::memory storageDecrypt;
      primitive::memory storageKey;
      System.base64().decode(storageEncrypt, pszEncrypt);
      System.base64().decode(storageKey, pszKey);
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
      MD5_Update(&ctx, psz, (unsigned long) strlen(psz));
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


   string crypt::md5(primitive::memory & mem)
   {
      int iBufSize = 16;
      unsigned char * buf = new unsigned char[iBufSize];
      MD5_CTX ctx;
      MD5_Init(&ctx);
      //int iRead;
      MD5_Update(&ctx, mem, (unsigned long) mem.get_size());
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

   string crypt::sha1(primitive::memory & mem)
   {
      int iBufSize = 20;
      unsigned char * buf = new unsigned char[iBufSize];
      crypto::sha1::CContext ctx;
      ctx.Init();
      //int iRead;
      ctx.update(mem, (int) mem.get_size());
      ctx.Final(buf);
      string str;
      string strFormat;
      for(int i = 0; i < 20; i++)
      {
         strFormat.Format("%02x", buf[i]);
         str += strFormat;
      }
      delete [] buf;
      return str;
   }


   bool crypt::file_set(var varFile, const char * pszData, const char * pszSalt, ::ca::application * papp)
   {
      primitive::memory memoryEncrypt;
      encrypt(memoryEncrypt, pszData, pszSalt);
      App(papp).file().put_contents(varFile, memoryEncrypt);
      return true;
   }

   bool crypt::file_get(var varFile, string & str, const char * pszSalt, ::ca::application * papp)
   {
      primitive::memory memoryEncrypt;
      App(papp).file().as_memory(varFile, memoryEncrypt);
      decrypt(str, memoryEncrypt, pszSalt);
      return true;
   }

   bool crypt::encrypt(primitive::memory & storageEncrypt, const char * pszDecrypt, const char * pszSalt)
   {
      primitive::memory memoryDecrypt;
      memoryDecrypt.FromAsc(pszDecrypt);
      return encrypt(storageEncrypt, memoryDecrypt, pszSalt);
   }

   bool crypt::decrypt(string & strDecrypt, const primitive::memory & storageEncrypt, const char * pszSalt)
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
         int64_t iDigit = System.math().RandRange(0, 255);
         strFormat.Format("%02x", iDigit);
         strSalt += strFormat;
      }
      return strSalt;
   }

   // calculate the hash from a salt and a password
   // slow hash is more secure for personal attack possibility (strong fast hashs are only good for single transactional operations and not for a possibly lifetime password)
   string crypt::v5_get_password_hash(const char * pszSalt, const char * pszPassword, int iOrder)
   {
      string strHash(pszPassword);
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
      string strHash(pszPassword);
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

   DWORD crypt::crc32(DWORD dwPrevious, const void * psz, ::primitive::memory_size iCount)
   {
      if(iCount == (::primitive::memory_size) -1)
         iCount = strlen((const char*) psz);
      return ::crc32(dwPrevious, (const Bytef *) psz, iCount);
   }

   DWORD crypt::crc32(DWORD dwPrevious, const char * psz)
   {
      return crc32(dwPrevious, psz, (::primitive::memory_size) -1);
   }

   void crypt::hmac(void * result, const primitive::memory & memMessage, const primitive::memory & memKey)
   {

      crypto::hmac_sha1::context context;

      context.digest(result, memMessage.get_data(), (int) memMessage.get_size(), memKey.get_data(), (int) memKey.get_size());

   }

   void crypt::hmac(void * result, const string & strMessage, const string & strKey)
   {

      crypto::hmac_sha1::context context;

      context.digest(result, strMessage, (int) strMessage.get_length(), strKey, (int) strKey.get_length());

   }

   string crypt::get_crypt_key_file_path()
   {

      throw interface_only_exception();

   }


   string crypt::defer_get_cryptkey()
   {

      string strPath = get_crypt_key_file_path();

      string str = Application.file().as_string(strPath);

      if(str.has_char())
         return str;

      for(int i = 0; i < 256; i++)
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


} // namespace ca4





bool crypt_file_get(const char * pszFile, string & str, const char * pszSalt)
{

   vsstring vsstr;

   if(!crypt_file_get(pszFile, vsstr, pszSalt))
      return false;

   str = vsstr;

   return true;

}


