#pragma once


namespace windows
{


   class CLASS_DECL_BASE crypto :
      virtual public ::crypto::crypto
   {
   public:


      crypto(sp(::axis::application) papp);
      virtual ~crypto();


      virtual bool encrypt(primitive::memory & storageEncrypt, const primitive::memory & storageDecrypt, const char * pszSalt);
      virtual bool decrypt(primitive::memory & storageDecrypt, const primitive::memory & storageEncrypt, const char * pszSalt);


   }; 


} // namespace base



