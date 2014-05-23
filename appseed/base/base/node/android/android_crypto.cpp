#include "framework.h"


namespace android
{


   crypto::crypto(sp(::base::application) papp) :
      element(papp),
      ::ca2::crypto(papp)
   {
   }


   crypto::~crypto()
   {
   }


   string crypto::get_crypt_key_file_path()
   {

      return System.dir().path(getenv("home"), ".ca2/cryptkey");

   }


   bool crypto::decrypt(primitive::memory & storageDecrypt, const primitive::memory & storageEncrypt, const char * pszSalt)
   {

      simple_memory memOut;

      simple_memory memIn;

      memIn.write(storageEncrypt.get_data(), storageEncrypt.get_size());

      if(!::crypt_decrypt(memOut, memIn, pszSalt))
         return false;


      storageDecrypt = memOut;

      return true;

   }

   bool crypto::encrypt(primitive::memory & storageEncrypt, const primitive::memory & storageDecrypt, const char * pszSalt)
   {

      simple_memory memOut;

      simple_memory memIn;

      memIn.write(storageDecrypt.get_data(), storageDecrypt.get_size());

      if(!::crypt_encrypt(memOut, memIn, pszSalt))
         return false;


      storageEncrypt = memOut;

      return true;

   }


} // namespace android


