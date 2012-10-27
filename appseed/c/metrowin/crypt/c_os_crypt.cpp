#include "framework.h"



bool crypt_decrypt(simple_memory & storageDecrypt, const simple_memory & storageEncrypt, simple_memory & memSalt)
{

   UNREFERENCED_PARAMETER(memSalt);

   ::Windows::Security::Cryptography::DataProtection::DataProtectionProvider ^ provider = ref new ::Windows::Security::Cryptography::DataProtection::DataProtectionProvider;

   ::Windows::Storage::Streams::IBuffer ^ bufferIn = storageEncrypt.get_os_stream_buffer();

   ::Windows::Storage::Streams::IBuffer ^ bufferOut = wait(provider->UnprotectAsync(bufferIn));

   storageDecrypt.set_os_stream_buffer(bufferOut);

   return true;

}

bool crypt_encrypt(simple_memory & storageEncrypt, const simple_memory & storageDecrypt, simple_memory & memSalt)
{

   UNREFERENCED_PARAMETER(memSalt);

   ::Windows::Security::Cryptography::DataProtection::DataProtectionProvider ^ provider = ref new ::Windows::Security::Cryptography::DataProtection::DataProtectionProvider;

   ::Windows::Storage::Streams::IBuffer ^ bufferIn = storageDecrypt.get_os_stream_buffer();

   ::Windows::Storage::Streams::IBuffer ^ bufferOut = wait(provider->ProtectAsync(bufferIn));

   storageEncrypt.set_os_stream_buffer(bufferOut);

   return true;

}
