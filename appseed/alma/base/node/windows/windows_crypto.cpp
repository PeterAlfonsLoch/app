#include "framework.h"


namespace windows
{


   crypto::crypto(sp(::base::application) papp) :
      element(papp),
      ::crypto::crypto(papp)
   {
   }


   crypto::~crypto()
   {
   }


   bool crypto::decrypt(primitive::memory & storageDecrypt, const primitive::memory & storageEncrypt, const char * pszSalt)
   {
      DATA_BLOB DataIn;
      DATA_BLOB DataOut;

      if(pszSalt == NULL)
         pszSalt = "";

      DATA_BLOB DataSalt;
      primitive::memory memorySalt;
      memorySalt.from_string(pszSalt);
      DataSalt.pbData = memorySalt.get_data();
      DataSalt.cbData = (DWORD) memorySalt.get_size();

      //--------------------------------------------------------------------
      // Initialize the DataIn structure.

      DataIn.pbData = storageEncrypt.get_data();
      DataIn.cbData = (DWORD) storageEncrypt.get_size();

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
         TRACE("crypto::decrypt The encryption phase worked. \n");
         storageDecrypt.allocate(DataOut.cbData);
         memcpy(storageDecrypt.get_data(), DataOut.pbData, DataOut.cbData);
         LocalFree(lpwsz);
         LocalFree(DataOut.pbData);
         return true;
      }
      else
      {
//         TRACELASTERROR();
         TRACE("crypto::decrypt Decryption error! (1)");
         return false;
      }
   }

   bool crypto::encrypt(primitive::memory & storageEncrypt, const primitive::memory & storageDecrypt, const char * pszSalt)
   {
      DATA_BLOB DataIn;
      DATA_BLOB DataOut;

      if(pszSalt == NULL)
         pszSalt = "";

      DATA_BLOB DataSalt;
      primitive::memory memorySalt;
      memorySalt.from_string(pszSalt);
      DataSalt.pbData = memorySalt.get_data();
      DataSalt.cbData = (DWORD) memorySalt.get_size();


      //--------------------------------------------------------------------
      // Initialize the DataIn structure.

      DataIn.pbData = (BYTE *) storageDecrypt.get_data();
      DataIn.cbData = (DWORD) storageDecrypt.get_size();

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
         TRACE("crypto::encrypt The encryption phase worked. \n");
         storageEncrypt.allocate(DataOut.cbData);
         memcpy(storageEncrypt.get_data(), DataOut.pbData, DataOut.cbData);
         LocalFree(DataOut.pbData);
         return true;
      }
      else
      {
         TRACE("crypto::encrypt Encryption error! (1)");
          return false;
      }

   }


} // namespace windows



