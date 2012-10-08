#include "framework.h"
#include <Wincrypt.h>



bool crypt_decrypt(simple_memory & storageDecrypt, const simple_memory & storageEncrypt, simple_memory & memorySalt)
{

   DATA_BLOB DataIn;
   DATA_BLOB DataOut;

   DATA_BLOB DataSalt;
   DataSalt.pbData = (BYTE *) memorySalt.get_data();
   DataSalt.cbData = (DWORD) memorySalt.get_size();

   //--------------------------------------------------------------------
   // Initialize the DataIn structure.

   DataIn.pbData = (BYTE *) storageEncrypt.get_data();
   DataIn.cbData = (DWORD) storageEncrypt.get_size();

   wchar_t * lpwsz = NULL;

   //--------------------------------------------------------------------
   //  Begin protect phase. Note that the encryption key is created
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
      return true;
   }
   else
   {
      DWORD dwLastError = GetLastError();
  //    TRACELASTERROR();
    //  TRACE("crypt::decrypt Decryption error! (1)");
      return false;
   }
}

bool crypt_encrypt(simple_memory & storageEncrypt, const simple_memory & storageDecrypt, simple_memory & memorySalt)
{
   DATA_BLOB DataIn;
   DATA_BLOB DataOut;

   DATA_BLOB DataSalt;
   DataSalt.pbData = (BYTE *) memorySalt.get_data();
   DataSalt.cbData = (DWORD) memorySalt.get_size();


   //--------------------------------------------------------------------
   // Initialize the DataIn structure.

   DataIn.pbData = (BYTE *) storageDecrypt.get_data();
   DataIn.cbData = (DWORD) storageDecrypt.get_size();

//      wchar_t * lpwsz = NULL;

   //--------------------------------------------------------------------
   //  Begin protect phase. Note that the encryption key is created
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
      return true;
   }
   else
   {
      DWORD dwLastError = GetLastError();
      //TRACE("crypt::encrypt Encryption error! (1)");
         return false;
   }

}
