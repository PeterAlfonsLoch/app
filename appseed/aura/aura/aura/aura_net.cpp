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


void openURL(const string &url_str) {
   CFURLRef url = CFURLCreateWithBytes(
      NULL,                        // allocator
      (UInt8*)url_str.c_str(),     // URLBytes
      url_str.length(),            // length
      kCFStringEncodingASCII,      // encoding
      NULL                         // baseURL
      );
   //    LSOpenCFURLRef(url,0);
   CFRelease(url);
}


#endif






open_url::open_url(sp(::aura::application) papp,const string & strLink,const string & pszTarget) :
   element(papp)
{

   m_strLink = strLink;

   m_strTarget = pszTarget;

}




static bool open_url::start(sp(::aura::application) papp,const string & strLink,const string & strTarget)
{

   return __begin_thread(papp,thread_proc_open_url,new open_url(papp,strLink,pszTarget)) != FALSE;

}


uint32_t c_cdecl open_url::thread_proc(void * p)
{

   open_url * popenurl = (open_url *)p;

   if(!popenurl->open())
      return -1;

   return 0;
}

bool open_url::open()
{
   string strLink = m_strLink;
   string pszTarget = m_strTarget;
#ifdef WINDOWSEX
   string strUrl = strLink;
   if(!::str::begins_ci(strUrl,"http://")
      && !::str::begins_ci(strUrl,"https://"))
   {
      strUrl = "http://" + strUrl;
   }
   ::ShellExecuteA(NULL,"open",strUrl,NULL,NULL,SW_SHOW);
   return true;
#elif defined METROWIN
#pragma push_macro("System")
#undef System
   ::Windows::Foundation::Uri ^ uri = ref new ::Windows::Foundation::Uri(strLink);
   ::Windows::System::LauncherOptions ^ options = ref new ::Windows::System::LauncherOptions();
   options->TreatAsUntrusted = false;
   bool success = ::wait(::Windows::System::Launcher::LaunchUriAsync(uri,options));

   return success;

#pragma pop_macro("System")
#elif defined(LINUX)
   ::system("xdg-open " + strLink);
   return true;
#elif defined(APPLEOS)
   openURL(strLink);
   return true;
#else
   throw not_implemented(get_thread_app());
#endif

}
