#pragma once

namespace ca5 
{

   class CLASS_DECL_ca2api00200002 crypt :
      virtual public base_object
   {
   public:

      // salt here may be dangerous for the universe

      crypt();
      virtual ~crypt();

      bool encrypt(memory & storageEncrypt, memory & storageDecrypt);
      bool decrypt(memory & storageDecrypt, memory & storageEncrypt);
      bool encrypt(memory & storageEncrypt, const char * pszDecrypt);
      bool decrypt(string & strDecrypt, memory & storageEncrypt);


      int key(memory & storage);
      int encrypt(memory & storageEncrypt, memory & storageDecrypt, memory & storageKey);
      int decrypt(memory & storageDecrypt, memory & storageEncrypt, memory & storageKey);

      string strkey();
      int encrypt(string & str, const char * psz, const char * pszKey);
      int decrypt(string & str, const char * psz, const char * pszKey);

      string md5(const char * psz);

      bool file_set(const char * pszFile, const char * pszData);
      bool file_get(const char * pszFile, string & str);

   };


} //   namespace ca5 