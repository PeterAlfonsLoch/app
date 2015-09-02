#pragma once

typedef struct bio_st BIO;


namespace metrowin
{


   class CLASS_DECL_AXIS SSLInitializer:
      public ::object
   {
   public:

      static ::aura::system * s_psystem;

      /**
      init openssl
      bio_err
      create random file
      */
      SSLInitializer(::aura::application * papp);

      /**
      remove random file
      */
      ~SSLInitializer();

      void DeleteRandFile();

      /** SSL; mutex locking function callback. */
      //static_function void SSL_locking_function(int32_t mode, int32_t n, const char *file, int32_t line);

      /** Return thread id. */
      //static_function unsigned long SSL_id_function();

      BIO *bio_err;

   private:
      string m_rand_file;
      long m_rand_size;

   };


   class CLASS_DECL_AXIS crypto :
      virtual public ::crypto::crypto
   {
   public:

      SSLInitializer *                             m_psslinit;



      crypto(::aura::application * papp);
      virtual ~crypto();


      virtual bool encrypt(primitive::memory & storageEncrypt, const primitive::memory & storageDecrypt, const char * pszSalt);
      virtual bool decrypt(primitive::memory & storageDecrypt, const primitive::memory & storageEncrypt, const char * pszSalt);
	  static_function uint32_t crc32(uint32_t dwPrevious,const char * psz);
      
      void md5(primitive::memory & memMd5,const primitive::memory & mem);
      void sha1(primitive::memory & memSha1,const primitive::memory & mem);
      //void nessie(primitive::memory & memSha1,const primitive::memory & mem);

      //// result is 20-byte digest
      //void hmac(void * result,const ::primitive::memory & memMessage,const ::primitive::memory & key);
      //void hmac(void * result,const string & memMessage,const string & key);


   }; 


} // namespace ca4



