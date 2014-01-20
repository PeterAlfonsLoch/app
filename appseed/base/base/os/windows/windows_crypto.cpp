#include "framework.h"
#include <Wincrypt.h>



int32_t crypto_decrypt(::primitive::memory & storageDecrypt, const ::primitive::memory & storageEncrypt, ::primitive::memory & memorySalt)
{

   DATA_BLOB DataIn;
   DATA_BLOB DataOut;

   DATA_BLOB DataSalt;
   DataSalt.pbData = (BYTE *) memorySalt.get_data();
   DataSalt.cbData = (uint32_t) memorySalt.get_size();

   //--------------------------------------------------------------------
   // Initialize the DataIn structure.

   DataIn.pbData = (BYTE *) storageEncrypt.get_data();
   DataIn.cbData = (uint32_t) storageEncrypt.get_size();

   wchar_t * lpwsz = NULL;

   //--------------------------------------------------------------------
   //  begin protect phase. Note that the encryption key is created
   //  by the function and is not passed.

   if(CryptUnprotectData(
      &DataIn,
      NULL, // A description string
                                          // to be included with the
                                          // encrypted data.
      &DataSalt,                               // Optional entropy not used.
      NULL,                               // Reserved.
      NULL,                               // Pass NULL for the
                                          // prompt structure.
      0,
      &DataOut))
   {
//      TRACE("crypt::decrypt The encryption phase worked. \n");
      storageDecrypt.allocate(DataOut.cbData);
      memcpy(storageDecrypt.get_data(), DataOut.pbData, DataOut.cbData);
      LocalFree(lpwsz);
      LocalFree(DataOut.pbData);
      return 1;
   }
   else
   {
      uint32_t dwLastError = GetLastError();
  //    TRACELASTERROR();
    //  TRACE("crypt::decrypt Decryption error! (1)");
      return 0;
   }
}

int32_t crypto_encrypt(::primitive::memory & storageEncrypt, const ::primitive::memory & storageDecrypt, ::primitive::memory & memorySalt)
{
   DATA_BLOB DataIn;
   DATA_BLOB DataOut;

   DATA_BLOB DataSalt;
   DataSalt.pbData = (BYTE *) memorySalt.get_data();
   DataSalt.cbData = (uint32_t) memorySalt.get_size();


   //--------------------------------------------------------------------
   // Initialize the DataIn structure.

   DataIn.pbData = (BYTE *) storageDecrypt.get_data();
   DataIn.cbData = (uint32_t) storageDecrypt.get_size();

//      wchar_t * lpwsz = NULL;

   //--------------------------------------------------------------------
   //  begin protect phase. Note that the encryption key is created
   //  by the function and is not passed.

   if(CryptProtectData(
         &DataIn,
         NULL, // A description string
                                             // to be included with the
                                             // encrypted data.
         &DataSalt,                               // Optional entropy not used.
         NULL,                               // Reserved.
         NULL,                               // Pass NULL for the
                                             // prompt structure.
         0,
         &DataOut))
   {
      //TRACE("crypt::encrypt The encryption phase worked. \n");
      storageEncrypt.allocate(DataOut.cbData);
      memcpy(storageEncrypt.get_data(), DataOut.pbData, DataOut.cbData);
      LocalFree(DataOut.pbData);
      return 1;
   }
   else
   {
      uint32_t dwLastError = GetLastError();
      //TRACE("crypt::encrypt Encryption error! (1)");
         return 0;
   }

}
