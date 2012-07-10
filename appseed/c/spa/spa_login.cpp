#include "framework.h"



spa_login::spa_login(simple_ui * puiParent) :
   simple_ui(puiParent)
{

   m_labelUser.set_parent(this);
   m_editUser.set_parent(this);
   m_labelPassword.set_parent(this);
   m_password.set_parent(this);
   m_tap.set_parent(this);

}


spa_login::~spa_login()
{
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

   plogin->login_result(plogin->login);

   return 0;

}

   char * hex_to_memory(count & count, const char * pszHex)
   {
      count len = strlen(pszHex);
      count = (len + 1) / 2;
      char * memory = ca2_alloc(count);
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
            ca2_free(memory);
            count = 0;
            return NULL;
         }
         pszHex++;
         if(*pszHex == '\0')
         {
            memory[i] = b;
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
            ca2_free(memory);
            count = 0;
            return NULL;
         }
         pszHex++;
         memory[i] = b;
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

   void memory_to_hex(vsstring & strHex, char * memory, ::count count)
   {
      LPSTR lpsz = strHex.alloc(count * 2);
      for(index i = 0; i < count; i++)
      {
         *lpsz++ = (char) nibble_to_low_hex((memory[i] >> 4) & 0xf);
         *lpsz++ = (char) nibble_to_low_hex(memory[i] & 0xf);
      }
      lpsz[count * 2] = '\0';
   }


spa_login::e_result spa_login::login()
{

   vsstring strLoginUrl("https://api.ca2.cc/account/login");

   xml_document doc(get_app());

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

      if(!doc.load(strLogin))
         continue;

      if(doc.get_root()->get_name() != "login")
         continue;

      strSessId = doc.get_root()->attr("sessid");

      if(strSessId.is_empty())
         continue;

      strRsaModulus = doc.get_root()->attr("rsa_modulus");

      if(strRsaModulus.has_char())
         break;

   }

   if(strRsaModulus.is_empty())
      return "";

   string strPass;
   if(m_strPasshash.is_empty())
   {
      strPass = System.crypt().nessie(m_strPassword);
   }
   else
   {
      strPass = m_strPasshash;
   }

   RSA * rsa = RSA_new();

   BN_hex2bn(&rsa->n, strRsaModulus);
   BN_hex2bn(&rsa->e, "10001");


   char * memory = (char *) ca2_alloc(2048);
   char * memIn = hex_to_memory(strPass);

   memory.allocate(2048);

   int i = RSA_public_encrypt((int) memIn.get_size(), (const unsigned char * ) (const char *) memIn.get_data(), memory.get_data(), rsa, RSA_PKCS1_PADDING);

   const char * psz = ERR_error_string(ERR_get_error(), NULL);

   TRACE(psz);


   string strHex;
   Application.memory_to_hex(strHex, memory, i);

   ca2_free(memory);
   ca2_free(memIn);

   RSA_free(rsa);

   m_puser->m_strLogin = m_strUsername;

   vsstring strResponse;

   {

      string strAuthUrl("https://" + strApiServer + "/account/auth?" + m_pcallback->oprop("defer_registration").get_string()
         +"&ruri=" + System.url().url_encode((m_pcallback->oprop("ruri").get_string())));

      gen::property_set post;
      gen::property_set headers;
      gen::property_set set;

      if(m_strPasshash.is_empty())
      {
         post["entered_password"] = strHex;
      }
      else
      {
         post["entered_passhash"] = strHex;
      }
      string strCrypt;

      post["entered_login"] = m_strUsername;
      if(m_strLicense.has_char())
      {
         post["entered_license"] = m_strLicense;
      }

      strAuthUrl += "&sessid="

      strResponse = ms_get_dup(strAuthUrl);

   }

      ca4::http::e_status estatus;
      int iAuth;
      xml::document doc(get_app());
      doc.load(strResponse);
      if(doc.get_root()->get_name() == "response")
      {
         if(doc.get_root()->attr("id") == "auth" && doc.get_root()->attr("passhash").has_char() && doc.get_root()->attr("secureuserid").has_char())
         {
            System.m_authmap[m_strUsername].m_mapServer[m_strRequestingServer] = strResponse;
            System.m_authmap[m_strUsername].m_mapFontopus[m_strFontopusServer] = strResponse;
            m_puser->m_strLogin = m_strUsername;
            m_puser->m_strFontopusServerSessId = doc.get_root()->attr("sessid");
            m_puser->m_strRequestingServer = m_strRequestingServer;
            m_puser->m_strFunUserId = doc.get_root()->attr("secureuserid");
            m_strPasshash = doc.get_root()->attr("passhash");
            iAuth = 1;
            if(m_bFontopusServer)
            {
               Application.file().put_contents(System.dir().appdata("database\\text\\last_good_known_fontopus_com.txt"), m_strRequestingServer);
            }
            execute();
            if(m_strLicense.has_char())
            {
               m_strValidUntil = doc.get_root()->attr("valid_until");
            }
         }
         else if(doc.get_root()->attr("id") == "registration_deferred")
         {
            delete m_puser;
            iAuth = 5;
         }
         else
         {
            delete m_puser;
            iAuth = -1;
         }
      }
      else
      {
         delete m_puser;
         if(estatus == ca4::http::status_connection_timed_out)
         {
            iAuth = -2;
         }
         else
         {
            iAuth = 0;
         }
      }
      //      char * psz = NULL;
      //    *psz = '2';
      m_pcallback->on_login_thread_response(iAuth, strResponse);

}