#pragma once


CLASS_DECL_ca bool crypt_file_get(const char * pszFile, string & str, const char * pszSalt);


namespace ca4
{


   class CLASS_DECL_ca crypt :
      virtual public ::radix::object
   {
   public:


      // salt here may be dangerous for the universe


      crypt(::ca::application * papp);
      virtual ~crypt();


      virtual bool encrypt(primitive::memory & storageEncrypt, const primitive::memory & storageDecrypt, const char * pszSalt);
      virtual bool decrypt(primitive::memory & storageDecrypt, const primitive::memory & storageEncrypt, const char * pszSalt);
      virtual bool encrypt(primitive::memory & storageEncrypt, const char * pszDecrypt, const char * pszSalt);
      virtual bool decrypt(string & strDecrypt, const primitive::memory & storageEncrypt, const char * pszSalt);


      int key(primitive::memory & storage);
      virtual bool encrypt(primitive::memory & storageEncrypt, const primitive::memory & storageDecrypt, primitive::memory & storageKey);
      virtual bool decrypt(primitive::memory & storageDecrypt, const primitive::memory & storageEncrypt, primitive::memory & storageKey);

      string strkey();
      int encrypt(string & str, const char * psz, const char * pszKey);
      int decrypt(string & str, const char * psz, const char * pszKey);

      static DWORD crc32(DWORD dwPrevious, const void * pvoid, ::primitive::memory_size size);
      static DWORD crc32(DWORD dwPrevious, const char * psz);
      string md5(const char * psz);
      string nessie(const char * psz);

      string md5(primitive::memory & mem);
      string sha1(primitive::memory & mem);

      // result is 20-byte digest
      void hmac(void * result, const ::primitive::memory & memMessage, const ::primitive::memory & key);
      void hmac(void * result, const string & memMessage, const string & key);

      bool file_set(var varFile, const char * pszData, const char * pszSalt, ::ca::application * papp);
      bool file_get(var varFile, string & str, const char * pszSalt, ::ca::application * papp);

      // get a new salt - 8 hexadecimal characters long
      // current PHP installations should not exceed 8 characters
      // on dechex( mt_rand() )
      // but we future proof it anyway with substr()
      string v5_get_password_salt();
      // calculate the hash from a salt and a password
      string v5_get_password_hash(const char * pszSalt, const char * pszPassword, int iOrder = 0);
      string v5_get_passhash(const char * pszSalt, const char * pszPassword, int iMaxOrder = 0);
      bool v5_compare_password(const char * pszPassword, const char * pszHash, int iOrder = 0);
      // if iOrder == 0 password is plain
      // if iOrder == 1 password is the first hash
      // if iOrder == (n > 0) password is the nth hash
      bool v5_validate_plain_password(const char * pszPassword);
      string v5_get_password_hash(const char * pszPassword, int iOrder = 0);

      virtual string get_crypt_key_file_path();
      virtual string defer_get_cryptkey();


   };


   typedef ::ca::smart_pointer < crypt > crypt_sp;


} //   namespace ca4



