#include "framework.h"


namespace metrowin
{


   crypto::crypto(sp(::aura::application) papp) :
      element(papp),
      ::crypto::crypto(papp)
   {
   }


   crypto::~crypto()
   {
   }


   bool crypto::decrypt(primitive::memory & storageDecrypt, const primitive::memory & storageEncrypt, const char * pszSalt)
   {

      UNREFERENCED_PARAMETER(pszSalt);

      ::Windows::Security::Cryptography::DataProtection::DataProtectionProvider ^ provider = ref new ::Windows::Security::Cryptography::DataProtection::DataProtectionProvider;

      ::Windows::Storage::Streams::IBuffer ^ bufferIn = storageEncrypt.get_os_crypt_buffer();

      ::Windows::Storage::Streams::IBuffer ^ bufferOut = ::wait(provider->UnprotectAsync(bufferIn));

      storageDecrypt.set_os_crypt_buffer(bufferOut);

      return true;

   }

   bool crypto::encrypt(primitive::memory & storageEncrypt, const primitive::memory & storageDecrypt, const char * pszSalt)
   {

      UNREFERENCED_PARAMETER(pszSalt);

      ::Windows::Security::Cryptography::DataProtection::DataProtectionProvider ^ provider = ref new ::Windows::Security::Cryptography::DataProtection::DataProtectionProvider("LOCAL=user");

      ::Windows::Storage::Streams::IBuffer ^ bufferIn = storageDecrypt.get_os_crypt_buffer();

      ::Windows::Storage::Streams::IBuffer ^ bufferOut = ::wait(provider->ProtectAsync(bufferIn));

      storageEncrypt.set_os_crypt_buffer(bufferOut);

      return true;

   }


} // namespace metrowin



