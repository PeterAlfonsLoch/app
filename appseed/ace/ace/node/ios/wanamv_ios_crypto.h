#pragma once


namespace ios
{


   class CLASS_DECL_AURA crypto :
      virtual public ::crypto::crypto
   {
   public:


      crypto(::ace::application * papp);
      virtual ~crypto();


      virtual bool encrypt(memory & storageEncrypt, const memory & storageDecrypt, const char * pszSalt);
      virtual bool decrypt(memory & storageDecrypt, const memory & storageEncrypt, const char * pszSalt);


      virtual string get_crypt_key_file_path();



   };

   
} // namespace ios





