#include "framework.h"
#include "metrowin.h"


#define CA4_CRYPT_V5_FINAL_HASH_BYTES (WHIRLPOOL_DIGEST_LENGTH * 16)
#define CA4_CRYPT_V5_SALT_BYTES (CA4_CRYPT_V5_FINAL_HASH_BYTES - WHIRLPOOL_DIGEST_LENGTH)



namespace metrowin
{


   crypto::crypto(::aura::application *  papp) :
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






      void crypto::md5(primitive::memory & memMd5,const primitive::memory & mem)
      {

         ::Windows::Security::Cryptography::Core::HashAlgorithmProvider ^ hasher =
            ::Windows::Security::Cryptography::Core::HashAlgorithmProvider::OpenAlgorithm(::Windows::Security::Cryptography::Core::HashAlgorithmNames::Md5);

         memMd5.set_os_crypt_buffer(hasher->HashData(mem.get_os_crypt_buffer()));

      }


      void crypto::sha1(primitive::memory & memSha1,const primitive::memory & mem)
      {

         ::Windows::Security::Cryptography::Core::HashAlgorithmProvider ^ hasher =
            ::Windows::Security::Cryptography::Core::HashAlgorithmProvider::OpenAlgorithm(::Windows::Security::Cryptography::Core::HashAlgorithmNames::Sha1);

         memSha1.set_os_crypt_buffer(hasher->HashData(mem.get_os_crypt_buffer()));

      }


} // namespace metrowin



