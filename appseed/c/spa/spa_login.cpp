#include "framework.h"
#include <openssl/ssl.h>
#include <openssl/md5.h>
#include <openssl/err.h>
#include <Wincrypt.h>

bool crypt_decrypt(simple_memory & storageDecrypt, const simple_memory & storageEncrypt, const char * pszSalt);
bool crypt_encrypt(simple_memory & storageEncrypt, const simple_memory & storageDecrypt, const char * pszSalt);

vsstring crypt_nessie(const char * psz);

/*

int crypt_encrypt(simple_memory & storageEncrypt, const simple_memory & storageDecrypt, simple_memory & key)
{
   int plainlen = (int) storageDecrypt.get_size();
   int cipherlen, tmplen;
   unsigned char iv[8] = {1,2,3,4,5,6,7,8};
   EVP_CIPHER_CTX ctx;
   EVP_CIPHER_CTX_init(&ctx);
   EVP_EncryptInit(&ctx,EVP_bf_cbc(),(unsigned char *) key.get_data(),iv);
   cipherlen = (int) (storageDecrypt.get_size() + 16 - 1); //; 16 = key size
   storageEncrypt.allocate(cipherlen);
   if (!EVP_EncryptUpdate(&ctx,(unsigned char *) storageEncrypt.get_data(),&cipherlen, (const unsigned char *) storageDecrypt.get_data(),plainlen))
   {
      return -1;
   }
   if (!EVP_EncryptFinal(&ctx,((unsigned char *) storageEncrypt.get_data())+cipherlen,&tmplen))
   {
      return -1;
   }
   cipherlen += tmplen;
   storageEncrypt.allocate(cipherlen);
   EVP_CIPHER_CTX_cleanup(&ctx);
   return cipherlen;
}

int crypt_decrypt(simple_memory & storageDecrypt, const simple_memory & storageEncrypt, simple_memory & key)
{
   int cipherlen = (int) storageEncrypt.get_size();
   int plainlen, tmplen;
   unsigned char iv[8] = {1,2,3,4,5,6,7,8};
   EVP_CIPHER_CTX ctx;
   EVP_CIPHER_CTX_init(&ctx);
   EVP_DecryptInit(&ctx,EVP_bf_cbc(), (const unsigned char *) key.get_data(),iv);
   plainlen = (int) storageEncrypt.get_size();
   storageDecrypt.allocate(plainlen);
   if(!EVP_DecryptUpdate(&ctx, (unsigned char *) storageDecrypt.get_data(),&plainlen, (const unsigned char *) storageEncrypt.get_data(),cipherlen))
   {
      return -1;
   }
   if (!EVP_DecryptFinal(&ctx,((unsigned char *) storageDecrypt.get_data())+plainlen,&tmplen))
   {
      storageDecrypt.allocate(plainlen);
      EVP_CIPHER_CTX_cleanup(&ctx);
      return plainlen;
   }
   plainlen += tmplen;
   storageDecrypt.allocate(plainlen);
   EVP_CIPHER_CTX_cleanup(&ctx);
   return plainlen;
}

*/


/*int crypt_encrypt(vsstring & strEncrypt, const char * pszDecrypt, const char * pszKey)
{
   simple_memory storageDecrypt;
   simple_memory storageEncrypt;
   simple_memory storageKey;
   if(pszDecrypt == NULL || strlen(pszDecrypt) == 0)
   {
      strEncrypt = "";
      return 0;
   }
   storageDecrypt.from_string(pszDecrypt);
   base64 base64;
   base64.decode(storageKey, pszKey);
   int cipherlen = crypt_encrypt(storageEncrypt, storageDecrypt, storageKey);
   strEncrypt = base64.encode(storageEncrypt);
   return cipherlen;
}*/


bool crypt_decrypt(vsstring & strDecrypt, const simple_memory & storageEncrypt, const char * pszSalt)
{
   simple_memory memoryDecrypt;
   if(!crypt_decrypt(memoryDecrypt, storageEncrypt, pszSalt))
      return false;
   memoryDecrypt.ToAsc(strDecrypt);
   return true;
}

bool crypt_file_get(const char * pszFile, vsstring & str, const char * pszSalt)
{
   simple_memory memoryEncrypt;
   if(!file_get_memory_dup(memoryEncrypt, pszFile))
      return false;
   if(memoryEncrypt.get_size() <= 0)
      return false;
   crypt_decrypt(str, memoryEncrypt, pszSalt);
   return true;
}

bool crypt_encrypt(simple_memory & storageEncrypt, const char * pszDecrypt, const char * pszSalt)
{
   simple_memory memoryDecrypt;
   memoryDecrypt.FromAsc(pszDecrypt);
   return crypt_encrypt(storageEncrypt, memoryDecrypt, pszSalt);
}

bool crypt_file_set(const char * pszFile, const char * pszData, const char * pszSalt)
{
   simple_memory memoryEncrypt;
   crypt_encrypt(memoryEncrypt, pszData, pszSalt);
   file_put_contents_dup(pszFile, memoryEncrypt);
   return true;
}


spa_login::spa_login()
{
   m_pcallback = NULL;

   m_labelUser.set_parent(this);
   m_editUser.set_parent(this);
   m_labelPassword.set_parent(this);
   m_password.set_parent(this);
   m_tap.set_parent(this);


   m_rect.left = 49;
   m_rect.top = 49;
   m_rect.right = m_rect.left + 840;
   m_rect.bottom = m_rect.top + 840;


   int x1 = m_rect.left + 49; 
   int x2 = m_rect.right - 49;
   int h1 = 23;
   int pad = 5;

   m_labelUser.m_rect.left = x1;
   m_labelUser.m_rect.right = x2;
   m_editUser.m_rect.left = x1;
   m_editUser.m_rect.right = x2;
   m_labelPassword.m_rect.left = x1;
   m_labelPassword.m_rect.right = x2;
   m_password.m_rect.left = x1;
   m_password.m_rect.right = x2;
   m_tap.m_rect.left = x1;
   m_tap.m_rect.right = x2;

   int y = m_rect.top + 49;
   m_labelUser.m_rect.top = y;
   y += h1;
   m_labelUser.m_rect.bottom = y;
   y += pad;
   m_editUser.m_rect.top = y;
   y += h1;
   m_editUser.m_rect.bottom = y;
   y += pad;
   m_labelPassword.m_rect.top = y;
   y += h1;
   m_labelPassword.m_rect.bottom = y;
   y += pad;
   m_password.m_rect.top = y;
   y += h1;
   m_password.m_rect.bottom = y;
   y += pad;
   m_tap.m_rect.top = y;
   y += h1;
   m_tap.m_rect.bottom = y;

   m_labelUser.m_strText = "User:";
   m_labelPassword.m_strText = "Password:";
   m_tap.m_strText = "Enter";

}



spa_login::~spa_login()
{
}


void spa_login::callback::login_result(e_result eresult)
{

   UNREFERENCED_PARAMETER(eresult);

}


void spa_login::initialize()
{

   crypt_file_get(dir::usersystemappdata(dir::default_os_user_path_prefix(), "license_auth", "00001.data"), m_editUser.m_strText, "");

   crypt_file_get(dir::default_userappdata(dir::default_os_user_path_prefix(), m_editUser.m_strText, "license_auth/00002.data"), m_strPasshash, calc_key_hash());

}


vsstring spa_login::calc_key_hash()
{
   if(m_strKeyHash.has_char())
      return m_strKeyHash;
/*#if !core_level_1 && !core_level_2
   ::SetDllDirectoryA(System.get_ca2_module_folder());
#endif
   HMODULE hmoduleSalt = ::LoadLibraryA("salt.dll");
   SALT salt = (SALT) ::GetProcAddress(hmoduleSalt, "salt");
   stringa straSource;
   if(m_loginthread.m_strUsername.has_char())
   {
      m_loginthread.m_strKeyHash = salt(get_app(), m_loginthread.m_strUsername, straSource);
      return m_loginthread.m_strKeyHash;
   }
   else */
   {
      m_strKeyHash = "ca2t12n";
      return "ca2t12n";
   }
}


void spa_login::on_action(const char * pszId)
{

   if(strcmp(pszId, "submit") == 0)
   {
      
      start_login();

   }

}

void spa_login::start_login()
{
   
   ::CreateThread(NULL, 0, &spa_login::thread_proc_login, (LPVOID) this, 0, 0);

}


DWORD WINAPI spa_login::thread_proc_login(LPVOID lpParam)
{

   spa_login * plogin = (spa_login *) lpParam;

   plogin->login_result(plogin->login());

   return 0;

}

   simple_memory hex_to_memory(const char * pszHex)
   {
      ::count len = strlen(pszHex);
      ::count count = (len + 1) / 2;
      simple_memory memory;
      memory.allocate(count);
      index i = 0;
      byte b;
      while(*pszHex != '\0')
      {
         char ch = (char) tolower(*pszHex);
         if(ch >= '0' && ch <= '9')
         {
            b = ch - '0';
         }
         else if(ch >= 'a' && ch <= 'f')
         {
            b = ch - 'a' + 10;
         }
         else
         {
            memory.allocate(0);
            return memory;
         }
         pszHex++;
         if(*pszHex == '\0')
         {
            memory.m_psz[i] = b;
            return memory;
         }
         b = b << 4;
         ch = (char) tolower(*pszHex);
         if(ch >= '0' && ch <= '9')
         {
            b |= (ch - '0');
         }
         else if(ch >= 'a' && ch <= 'f')
         {
            b |= (ch - 'a' + 10);
         }
         else
         {
            memory.allocate(0);
            return memory;
         }
         pszHex++;
         memory.m_psz[i] = b;
         i++;
      }
      return memory;
   }


   int nibble_to_low_hex(byte nibble)
   {
      if(nibble >= 0 && nibble <= 9)
      {
         return nibble + '0';
      }
      else if(nibble >= 10 && nibble <= 15)
      {
         return nibble + 'a' - 10;
      }
      else
      {
         return -1;
      }
   }

   void memory_to_hex(vsstring & strHex, const simple_memory & memory)
   {
      LPSTR lpsz = strHex.alloc(memory.get_size() * 2);
      for(index i = 0; i < memory.get_size(); i++)
      {
         *lpsz++ = (char) nibble_to_low_hex((memory.m_psz[i] >> 4) & 0xf);
         *lpsz++ = (char) nibble_to_low_hex(memory.m_psz[i] & 0xf);
      }
      lpsz[memory.get_size() * 2] = '\0';
   }


spa_login::e_result spa_login::login()
{

   if(m_editUser.m_strText.is_empty())
      return result_fail;

   if(m_password.m_strText.is_empty() && m_strPasshash.is_empty())
      return result_fail;

   vsstring strLoginUrl("https://api.ca2.cc/account/login");

   XDoc doc;

   vsstring strSessId;

   vsstring strRsaModulus;

   vsstring strLogin;

   for(int iRetry = 0; iRetry <= 8; iRetry++)
   {

      if(iRetry > 0)
      {
         Sleep(iRetry * 584);
      }

      try
      {


         strLogin = ms_get_dup(strLoginUrl);

      }
      catch(...)
      {
      }

      strLogin.trim();

      if(strLogin.is_empty())
         continue;

      if(!doc.Load(strLogin))
         continue;

      if(doc.GetRoot()->name != "login")
         continue;

      strSessId = doc.GetRoot()->GetAttrValue("sessid");

      if(strSessId.is_empty())
         continue;

      strRsaModulus = doc.GetRoot()->GetAttrValue("rsa_modulus");

      if(strRsaModulus.has_char())
         break;

   }

   if(strRsaModulus.is_empty())
      return result_fail;

   vsstring strPass;
   if(m_strPasshash.is_empty())
   {
      strPass = crypt_nessie(m_password.m_strText);
   }
   else
   {
      strPass = m_strPasshash;
   }

   RSA * rsa = RSA_new();

   BN_hex2bn(&rsa->n, strRsaModulus);
   BN_hex2bn(&rsa->e, "10001");


   simple_memory memory;
   simple_memory memIn = hex_to_memory(strPass);

   memory.allocate(2048);

   int i = RSA_public_encrypt((int) memIn.get_size(), (const unsigned char * ) (const char *) memIn.get_data(), (unsigned char *)  memory.get_data(), rsa, RSA_PKCS1_PADDING);

   const char * psz = ERR_error_string(ERR_get_error(), NULL);

   //TRACE(psz);


   memory.allocate(i);

   vsstring strHex;
   memory_to_hex(strHex, memory);

   RSA_free(rsa);

   vsstring strResponse;

   {

      vsstring strAuthUrl("https://api.ca2.cc/account/auth?defer_registration");

      if(m_strPasshash.is_empty())
      {
         strAuthUrl += "&entered_password=" + strHex;
      }
      else
      {
         strAuthUrl += "&entered_passhash=" + strHex;
      }
      //string strCrypt;

      strAuthUrl += "&entered_login=" + m_editUser.m_strText;
      /*if(m_strLicense.has_char())
      {
         post["entered_license"] = m_strLicense;
      }*/

      strAuthUrl += "&sessid=" + strSessId;

      strResponse = ms_get_dup(strAuthUrl);

   }

   e_result eresult;
   
   {


      XDoc doc;

      doc.Load(strResponse);

      if(doc.GetRoot()->name == "response")
      {
         if(doc.GetRoot()->GetAttrValue("id") == "auth" && vsstring(doc.GetRoot()->GetAttrValue("passhash")).has_char() && vsstring(doc.GetRoot()->GetAttrValue("secureuserid")).has_char())
         {
            m_strPasshash = doc.GetRoot()->GetAttrValue("passhash");
            eresult = result_ok;
         }
         else if(doc.GetRoot()->GetAttrValue("id") == "registration_deferred")
         {
            eresult = result_registration_deferred;
         }
         else
         {
            eresult = result_fail;
         }
      }
      else
      {
         eresult = result_fail;
      }

   }

   //      char * psz = NULL;
   //    *psz = '2';
   return eresult;

}



void spa_login::login_result(e_result eresult)
{

   if(m_pcallback != NULL)
   {
    
      m_pcallback->login_result(eresult);

   }

}


vsstring crypt_nessie(const char * psz)
{
   vsstring strFormat;
   vsstring str;
//      int i;
   NESSIEstruct ns;
   u8 digest[DIGESTBYTES];
   NESSIEinit(&ns);
   NESSIEadd((const byte *) psz, (unsigned long) (8*strlen(psz)), &ns);
   NESSIEfinalize(&ns, digest);
   for(int i = 0; i < DIGESTBYTES; i++)
   {
      strFormat = itohex_dup(digest[i]);
      zero_pad(strFormat, 2);
      str += strFormat;
   }
   return str;
}

   /*
   string file::nessie(const char * psz)
   {
      ex1::filesp spfile(get_app());
      try
      {
         if(!spfile->open(psz, ::ex1::file::type_binary | ::ex1::file::mode_read))
            return "";
      }
      catch(ex1::file_exception * pe)
      {
         gen::del(pe);
         return "";
      }
      return nessie(spfile);
   }

   string file::nessie(ex1:: file * pfile)
   {
      int iBufSize = 1024 * 256;
      unsigned char * buf = new unsigned char[iBufSize];
      NESSIEstruct ns;
      NESSIEinit(&ns);
      uint64_t iRead;
      while((iRead = pfile->read(buf, iBufSize)) > 0)
      {
         NESSIEadd(buf, 8*iBufSize, &ns);
      }
      u8 digest[DIGESTBYTES];
      NESSIEfinalize(&ns, digest);
      string str;
      string strFormat;
      for(int i = 0; i < DIGESTBYTES; i++)
      {
         strFormat.Format("%02x", digest[i]);
         str += strFormat;
      }
      delete [] buf;
      return str;
   }

*/



void spa_login::authentication_succeeded()
{

   vsstring strUsername = m_editUser.m_strText;
   vsstring strPasshash = m_strPasshash;
   vsstring strPassword = m_password.m_strText;

   vsstring strUsernamePrevious;
   vsstring strPasshashPrevious;
   crypt_file_get(dir::usersystemappdata(dir::default_os_user_path_prefix(), "license_auth", "00001.data"), strUsernamePrevious, "");
   crypt_file_get(dir::default_userappdata(dir::default_os_user_path_prefix(), strUsernamePrevious, "license_auth/00002.data"), strPasshashPrevious, calc_key_hash());

   if((strUsername.has_char() && strPasshash.has_char())
   && (strUsernamePrevious != strUsername || strPasshashPrevious != strPasshash))
   {
      dir::mk(dir::usersystemappdata(dir::default_os_user_path_prefix(), "license_auth", NULL));
      dir::mk(dir::default_userappdata(dir::default_os_user_path_prefix(), strUsername, "license_auth"));
      crypt_file_set(dir::usersystemappdata(dir::default_os_user_path_prefix(), "license_auth", "00001.data"), strUsername, "");
      crypt_file_set(dir::default_userappdata(dir::default_os_user_path_prefix(), strUsername, "license_auth/00002.data"), strPasshash, calc_key_hash());
      /*if(strPassword.has_char())
      {
         string strSalt = System.crypt().v5_get_password_salt();
         System.crypt().file_set(Application.dir().default_userappdata(Application.dir().default_os_user_path_prefix(), strUsername, "license_auth/00005.data"), strSalt, calc_key_hash(), get_app());
         string strPasshash2 = System.crypt().v5_get_password_hash(strSalt, strPassword);
         System.crypt().file_set(Application.dir().default_userappdata(Application.dir().default_os_user_path_prefix(), strUsername, "license_auth/00010.data"), strPasshash2, calc_key_hash(), get_app());
      }*/
   }
   /*if(m_loginthread.m_strLicense.has_char())
   {
      stringa straLicense;
      straLicense.add(m_loginthread.m_strValidUntil);
      straLicense.add(System.datetime().international().get_gmt_date_time());
      System.crypt().file_set(Application.dir().default_userappdata(Application.dir().default_os_user_path_prefix(), strUsername, "license_auth/" + m_loginthread.m_strLicense + ".data"), straLicense.implode(";"), calc_ca2_hash(), get_app());
   }*/

}

void spa_login::authentication_failed()
{

}



bool crypt_decrypt(simple_memory & storageDecrypt, const simple_memory & storageEncrypt, const char * pszSalt)
{
   DATA_BLOB DataIn;
   DATA_BLOB DataOut;

   if(pszSalt == NULL)
      pszSalt = "";

   DATA_BLOB DataSalt;
   simple_memory memorySalt;
   memorySalt.from_string(pszSalt);
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

bool crypt_encrypt(simple_memory & storageEncrypt, const simple_memory & storageDecrypt, const char * pszSalt)
{
   DATA_BLOB DataIn;
   DATA_BLOB DataOut;

   if(pszSalt == NULL)
      pszSalt = "";

   DATA_BLOB DataSalt;
   simple_memory memorySalt;
   memorySalt.from_string(pszSalt);
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
