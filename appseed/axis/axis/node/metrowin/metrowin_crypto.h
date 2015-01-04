#pragma once


namespace metrowin
{


   class CLASS_DECL_AXIS crypto :
      virtual public ::crypto::crypto
   {
   public:


      crypto(::aura::application * papp);
      virtual ~crypto();


      virtual bool encrypt(primitive::memory & storageEncrypt, const primitive::memory & storageDecrypt, const char * pszSalt);
      virtual bool decrypt(primitive::memory & storageDecrypt, const primitive::memory & storageEncrypt, const char * pszSalt);
      static uint32_t crc32(uint32_t dwPrevious,const char * psz);
      
      void md5(primitive::memory & memMd5,const primitive::memory & mem);
      void sha1(primitive::memory & memSha1,const primitive::memory & mem);
      //void nessie(primitive::memory & memSha1,const primitive::memory & mem);

      //// result is 20-byte digest
      //void hmac(void * result,const ::primitive::memory & memMessage,const ::primitive::memory & key);
      //void hmac(void * result,const string & memMessage,const string & key);


   }; 


} // namespace ca4



