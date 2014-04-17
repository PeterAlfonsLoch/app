#pragma once


//CLASS_DECL_BASE bool crypt_file_get(const char * pszFile, string & str, const char * pszSalt);

#ifdef MACOS_DEPRECATED

#define BASE_RSA_KEY SecKeyRef

#elif defined(BSD_STYLE_SOCKETS)

typedef struct rsa_st RSA;

#define BASE_RSA_KEY RSA *

#elif defined(METROWIN)

#define BASE_RSA_KEY ::Windows::Security::Cryptography::Core::CryptographicKey ^

#else

#error "BASE_RSA_KEY could not be defined, is RSA implementation missing?"

#endif



namespace crypto
{


   class rsa;


   class CLASS_DECL_BASE crypto :
      virtual public ::object
   {
   public:


      // salt here may be dangerous for the universe


      crypto(sp(base_application) papp);
      virtual ~crypto();


      virtual bool encrypt(primitive::memory & storageEncrypt, const primitive::memory & storageDecrypt, const char * pszSalt);
      virtual bool decrypt(primitive::memory & storageDecrypt, const primitive::memory & storageEncrypt, const char * pszSalt);
      virtual bool encrypt(primitive::memory & storageEncrypt, const char * pszDecrypt, const char * pszSalt);
      virtual bool decrypt(string & strDecrypt, const primitive::memory & storageEncrypt, const char * pszSalt);


      int32_t key(primitive::memory & storage);
      virtual bool encrypt(primitive::memory & storageEncrypt, const primitive::memory & storageDecrypt, const primitive::memory & storageKey);
      virtual bool decrypt(primitive::memory & storageDecrypt, const primitive::memory & storageEncrypt, const primitive::memory & storageKey);

      string strkey();
      int32_t encrypt(string & str, const char * psz, const char * pszKey);
      int32_t decrypt(string & str, const char * psz, const char * pszKey);

      static uint32_t crc32(uint32_t dwPrevious, const char * psz);
      string md5(const char * psz);
      string nessie(const char * psz);
      string sha1(const char * psz);

      string md5(const primitive::memory & mem);
      string sha1(const primitive::memory & mem);

      void md5(primitive::memory & memMd5, const primitive::memory & mem);
      void sha1(primitive::memory & memSha1, const primitive::memory & mem);

      // result is 20-byte digest
      void hmac(void * result, const ::primitive::memory & memMessage, const ::primitive::memory & key);
      void hmac(void * result, const string & memMessage, const string & key);

      bool file_set(var varFile, const char * pszData, const char * pszSalt, sp(base_application) papp);
      bool file_get(var varFile, string & str, const char * pszSalt, sp(base_application) papp);

      // get a new salt - 8 hexadecimal characters long
      // current PHP installations should not exceed 8 characters
      // on dechex( mt_rand() )
      // but we future proof it anyway with substr()
      string v5_get_password_salt();
      // calculate the hash from a salt and a password
      string v5_get_password_hash(const char * pszSalt, const char * pszPassword, int32_t iOrder = 0);
      string v5_get_passhash(const char * pszSalt, const char * pszPassword, int32_t iMaxOrder = 0);
      bool v5_compare_password(const char * pszPassword, const char * pszHash, int32_t iOrder = 0);
      // if iOrder == 0 password is plain
      // if iOrder == 1 password is the first hash
      // if iOrder == (n > 0) password is the nth hash
      bool v5_validate_plain_password(const char * pszPassword);
      string v5_get_password_hash(const char * pszPassword, int32_t iOrder = 0);

      virtual string get_crypt_key_file_path();
      virtual string defer_get_cryptkey();


      virtual sp(rsa) generate_rsa_key();


      void err_load_rsa_strings();
      void err_load_crypto_strings();

      /*int rsa_private_decrypt(::primitive::memory & out, const ::primitive::memory & in,
         const string & n,
         const string & e,
         const string & d,
         const string & p,
         const string & q,
         const string & dmp1,
         const string & dmq1,
         const string & iqmp,
         string strError);*/

      string spa_login_crypt(const char * psz, const char * pszRsa);

      
      virtual void np_make_zigbert_rsa(const string & strDir, const string & strSignerPath, const string & strKeyPath, const string & strOthersPath, const string & strSignature);


   };


   typedef smart_pointer < crypto > crypto_sp;


   class CLASS_DECL_BASE rsa :
      virtual public element
   {
   public:

      mutex m_mutex;
      BASE_RSA_KEY m_prsa;
      string n;
      string e;
      string d;
      string p;
      string q;
      string dmp1;
      string dmq1;
      string iqmp;

      rsa(sp(base_application) papp);
      rsa(sp(base_application) papp, const string & n);
      rsa(sp(base_application) papp,
         const string & n,
         const string & e,
         const string & d,
         const string & p,
         const string & q,
         const string & dmp1,
         const string & dmq1,
         const string & iqmp);
      virtual ~rsa();

      int public_encrypt(::primitive::memory & out, const ::primitive::memory & in, string & strError);
      int private_decrypt(::primitive::memory & out, const ::primitive::memory & in, string & strError);

   };

   typedef spa(rsa) rsaptra;

} //   namespace crypto





#pragma once


CLASS_DECL_BASE bool crypto_decrypt(::primitive::memory & storageDecrypt, const ::primitive::memory & storageEncrypt, const char * pszSalt);
CLASS_DECL_BASE bool crypto_encrypt(::primitive::memory & storageEncrypt, const ::primitive::memory & storageDecrypt, const char * pszSalt);

CLASS_DECL_BASE bool crypto_file_get(const char * pszFile, string & str, const char * pszSalt);
CLASS_DECL_BASE bool crypto_file_set(const char * pszFile, const char * pszData, const char * pszSalt);






CLASS_DECL_BASE void stunCalculateIntegrity_longterm(char* hmac, const char* input, int32_t length, const char *username, const char *realm, const char *password);

CLASS_DECL_BASE void stunCalculateIntegrity_shortterm(char* hmac, const char* input, int32_t length, const char* key);


CLASS_DECL_BASE void hmac_evp_sha1_1234(unsigned char * hmac, unsigned int * hmacSize, const unsigned char * buf, size_t bufLen);
