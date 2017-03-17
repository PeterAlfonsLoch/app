#include "framework.h"


CLASS_DECL_AURA string url_decode_dup(const char * psz)
{
   string str(psz);

   string strDecode;

   str.replace("+"," ");

   strsize iStart = 0;

   while(true)
   {

      strsize iFind = str.find("%",iStart);

      if(iFind == -1)
      {
         strDecode += str.Mid(iStart);
         break;
      }

      strDecode += str.Mid(iStart,iFind - iStart);

      if(str[iFind + 1] == '%')
      {

         strDecode += "%";
         iStart = iFind + 2;

      }
      else
      {

         char ch = (char)strtol(str.Mid(iFind + 1,2),NULL,16);

         if(ch != 0)
         {
            strDecode += ch;
         }

         iStart = iFind + 3;

      }


   }

   return strDecode;


}



string url_decode_dup(const char * lpszUrl,strsize iLen)
{

   string strDecode;

   char * psz = strDecode.GetBufferSetLength(iLen * 4);

   strsize i = 0;

   while(*lpszUrl != '\0' && i < iLen)
   {
      if(*lpszUrl == '+')
      {
         i++;
         *psz = ' ';
         psz++;
         lpszUrl++;
      }
      else if(*lpszUrl == '%')
      {
         iLen--;
         lpszUrl++;
         if(*lpszUrl == '%')
         {
            i++;
            *psz = '%';
            psz++;
            lpszUrl++;
         }
         else
         {
            i++;
            iLen--;
            *psz = (char)(uchar)(hex::to(*lpszUrl) * 16 + hex::to(*(lpszUrl + 1)));
            psz++;
            lpszUrl += 2;
         }
      }
      else
      {
         i++;
         *psz = *lpszUrl;
         psz++;
         lpszUrl++;
      }
   }

   strDecode.ReleaseBuffer(iLen);

   return strDecode;

}






CLASS_DECL_AURA bool url_query_get_param_dup(string & strParam,const char * pszKey,const char * pszUrl)
{

   const char * pszBeg;
   const char * pszEnd;

   {

      string strKey;

      strKey = "?";
      strKey += pszKey;
      strKey += "=";

      pszBeg = strstr_dup(pszUrl,strKey);

      if(pszBeg != NULL)
      {

         pszBeg += strKey.get_length();

         goto success;

      }

   }

   {

      string strKey;

      strKey = "&";
      strKey += pszKey;
      strKey += "=";

      pszBeg = strstr_dup(pszUrl,strKey);

      if(pszBeg != NULL)
      {

         pszBeg += strKey.get_length();

         goto success;

      }

   }

   {

      string strKey;

      strKey = "?";
      strKey += pszKey;
      strKey += "&";

      pszBeg = strstr_dup(pszUrl,strKey);

      if(pszBeg != NULL)
      {

         strParam = "";

         return true;

      }

   }

   {

      string strKey;

      strKey = "&";
      strKey += pszKey;
      strKey += "&";

      pszBeg = strstr_dup(pszUrl,strKey);

      if(pszBeg != NULL)
      {

         strParam = "";

         return true;

      }

   }

   return false;

success:

   pszEnd = strstr_dup(pszBeg,"&");

   if(pszEnd == NULL)
   {
      strParam = pszBeg;
   }
   else
   {
      strParam = string(pszBeg,pszEnd - pszBeg);
   }

   return true;

}








string url_encode_dup(const char * psz)
{

   string str;

   char sz[256];

   while(*psz != '\0')
   {

      unsigned char uch = *psz;

      if(isdigit_dup(uch)
         || isalpha_dup(uch)
         || uch == '.'
         || uch == '-'
         || uch == '_')
      {

         str += uch;

      }
      else if(uch == ' ')
      {

         str += "+";

      }
      else
      {

         itoa_dup(sz,uch,16);

         to_upper(sz);

         if(strlen_dup(sz) == 0)
         {

            str += "%00";

         }
         else if(strlen_dup(sz) == 1)
         {

            str += "%0";

            str += sz;

         }
         else if(strlen_dup(sz) == 2)
         {

            str += "%";

            str += sz;

         }

      }

      psz++;

   }

   return str;

}


//string str;
//
//string strChar;
//
//while (*psz != '\0')
//{
//
//   if (isdigit_dup(*psz)
//      || isalpha_dup(*psz)
//      || *psz == '.'
//      || *psz == '-'
//      || *psz == '_')
//   {
//      str += *psz;
//   }
//   else if (*psz == ' ')
//   {
//      str += "+";
//   }
//   else
//   {
//      strChar.Format("%02X", *psz);
//      str += "%" + strChar.Right(2);
//   }
//
//   psz++;
//}
//
//return str;






















#if defined(MACOS)

void openURL(const string &url_str);


void openURL(const string &url_str) {
   CFURLRef url = CFURLCreateWithBytes(
      NULL,                        // allocator
      (UInt8*)url_str.c_str(),     // URLBytes
      url_str.length(),            // length
      kCFStringEncodingASCII,      // encoding
      NULL                         // baseURL
      );
   LSOpenCFURLRef(url,0);
   CFRelease(url);
}

#elif defined(APPLE_IOS)

void openURL(const string &url_str);

int ui_open_url(const char * psz);

void openURL(const string &url_str) {
//   throw todo(get_thread_app());
//   CFURLRef url = CFURLCreateWithBytes(
//      NULL,                        // allocator
//      (UInt8*)url_str.c_str(),     // URLBytes
//      url_str.length(),            // length
//      kCFStringEncodingASCII,      // encoding
//      NULL                         // baseURL
//      );
//       LSOpenCFURLRef(url,0);

   ui_open_url(url_str);

//   CFRelease(url);
}


#endif









BEGIN_EXTERN_C

#ifdef WINDOWS
#define strdup _strdup
#endif

CLASS_DECL_AURA int_bool freerdp_authenticate(void * instance, char** username,char** password,char** domain, const char * pszServerName, int bInteractive)
{

   ::aura::application * papp = ::get_aura(instance);

   string strUsername;

   string strUser;

   string strDomain;

   string strPassword;

   string strToken;

   strToken = Sys(papp).crypto_md5_text(pszServerName);

   string strTitle;

   strTitle = "Enter Credentials for : " + string(pszServerName);

   strUsername = file_as_string_dup(::dir::system() / "config\\user.txt");

   strPassword = file_as_string_dup(::dir::system() / "config\\pass.txt");

   if(strUsername.has_char() && strPassword.has_char())
   {

   }
   else
   {

      if(papp->fontopus_get_cred(papp, "",null_rect(),strUsername,strPassword,strToken,strTitle, bInteractive != FALSE) != "ok")
         return FALSE;

   }

   index iFind = strUsername.find('/');

   if(iFind > 0)
   {

      strUser = strUsername.Mid(iFind + 1);

      strDomain = strUsername.Left(iFind);

   }
   else
   {

      strUser = strUsername;

   }

   if(username != NULL)
   {

      *username = strdup(strUser);

   }

   if(domain != NULL && strDomain.has_char())
   {

      *domain = strdup(strDomain);

   }

   if(password != NULL)
   {

      *password = strdup(strPassword);

   }

   return TRUE;

}

END_EXTERN_C






