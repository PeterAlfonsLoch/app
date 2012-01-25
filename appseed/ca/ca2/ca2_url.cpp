#include "StdAfx.h"

namespace ca2
{

   string url::get_protocol(const char * psz)
   {
      string str(psz);
      int iPos = str.find(":");
      if(iPos == -1)
         return "";
      return str.Mid(0, iPos);
   }

   string url::get_root(const char * psz)
   {
      string str(psz);
      int iPos = str.find(":");
      if(iPos == -1)
         return "";
      iPos++;
      while(iPos < str.get_length() && str[iPos] == '/')
      {
         iPos++;
      }
      int iStart = iPos;
      int iEnd = str.find("/", iStart);
      if(iEnd < 0)
         return str.Mid(iStart);
      else
         return str.Mid(iStart, iEnd - iStart);
   }

   string url::get_server(const char * psz)
   {
      string strRoot = get_root(psz);
      int iPos = strRoot.find(":");
      if(iPos == -1)
         return strRoot;
      return strRoot.Left(iPos);
   }

   int url::get_port(const char * psz, int iDefault)
   {
      string strRoot = get_root(psz);
      int iPos = strRoot.find(":");
      if(iPos == -1)
      {
         if(iDefault == -1)
         {
            string strProtocol = get_protocol(psz);
            if(strProtocol == "http")
               return 80;
            else if(strProtocol == "https")
               return 443;
            else if(strProtocol == "ftp")
               return 21;
         }
         return iDefault;
      }
      return atoi(strRoot.Mid(iPos + 1));
   }

   string url::get_object(const char * psz)
   {
      string str(psz);
      int iPos = str.find("://");
      if(iPos < 0)
         return psz;
      iPos += 3;
      int iStart = str.find("/", iPos);
      if(iStart < 0)
         return "/";
      else
         return str.Mid(iStart);
   }

   string url::object_get_script(const char * psz) // page
   {
      string str(psz);
      int iFind = str.find('?');
      if(iFind < 0)
         return str;
      else 
         return str.Left(iFind);
   }

   string url::object_get_query(const char * psz) // id=1
   {
      string str(psz);
      int iFind = str.find('?');
      if(iFind < 0)
         return "";
      else 
         return str.Mid(iFind + 1);
   }

   string url::object_set(const char * pszObject, const char * pszKey, var var)
   {
      string strQuery = object_get_query(pszObject);
      return object_get_script(pszObject) + gen::str::has_char(query_set(strQuery, pszKey, var), "?");
   }


   string url::get_script(const char * psz) // page
   {
      return object_get_script(get_object(psz));
   }

   string url::get_query(const char * psz) // id=1
   {
      return object_get_query(get_object(psz));
   }

   string url::object(const char * pszScript, const char * pszQuery)
   {
      string strScript(pszScript);
      string strQuery(pszQuery);
      if(strQuery.has_char())
         return strScript + "?" + strQuery;
      else
         return strScript;
   }


   string url::path(const char * psz1, const char * psz2)
   {
      if(psz2 == NULL)
         return psz1;
      string str1(psz1);
      string str2(psz2);
      if(str1.Right(1) == "/")
         str1 = str1.Left(str1.get_length() - 1);
      if(str2.Left(1) == "/")
         str2 = str2.Right(str2.get_length() - 1);
      return str1 + "/" + str2;
   }

   string url::path(const char * psz1, const char * psz2, const char * psz3)
   {
      return path(path(psz1, psz2), psz3);
   }
   
   string url::name(const char * psz)
   {
      string str(psz);
      int iQueryStart = str.find('?');
      if(iQueryStart < 0)
         iQueryStart = str.get_length();
      str = str.Left(iQueryStart);
      int iLastSlash = str.reverse_find('/');
      if(iLastSlash < 0)
         return "";
      else
         return str.Left(iLastSlash);
   }


   string url::url_encode(const char * psz)
   {
      string str;
      string strChar;
      while(*psz != '\0')
      {
         if(isdigit((unsigned char)*psz)
         || isalpha((unsigned char)*psz)
         || *psz == '.'
         || *psz == '-'
         || *psz == '_')
         {
            str += *psz;
         }
         else if(*psz == ' ')
         {
            str += "+";
         }
         else
         {
            strChar.Format("%02X", *psz);
            str += "%" + strChar.Right(2);
         }
         psz++;
      }
      return str;
   }
   string url::url_decode(const char * psz)
   {
      string str(psz);
      string strDecode;
      str.replace("+", " ");
      int iStart = 0;
      while(true)
      {
         int iFind = str.find("%", iStart);
         if(iFind == -1)
         {
            strDecode += str.Mid(iStart);
            break;
         }
         strDecode += str.Mid(iStart, iFind - iStart);
         if(str[iFind + 1] == '%')
         {
            strDecode += "%";
            iStart = iFind + 2;
         }
         else
         {
            char ch = (char) strtol(str.Mid(iFind + 1, 2), NULL, 16);
            if(ch != 0)
            {
               strDecode += ch;
            }
            iStart = iFind + 3;
         }
         
         
      }
      return strDecode;
   }

   string url::query_append(const char * pszUrl, const char * pszQuery)
   {
      string strUrl(pszUrl);
      int iStart = strUrl.find("://");
      if(iStart > 0)
      {
         iStart = strUrl.find("/", iStart + 4);
         if(iStart < 0)
         {
            TRACE("invalid url %s", pszUrl);
            iStart = 0;
         }
      }
      else
      {
         iStart = 0;
      }
      
      if(strUrl.find("?", iStart) > 0)
      {
         return strUrl + "&" + pszQuery;
      }
      else
      {
         return strUrl + "?" + pszQuery;
      }
   }


   bool url::is_url(const char * pszCandidate)
   {
      string strCandidate(pszCandidate);
      int iLen = strCandidate.get_length();
      int i = 0;
      char ch;
      while(i < iLen)
      {
         ch = strCandidate[i];
         if(isalpha((unsigned char) ch))
            i++;
         else if(ch == '.')
            i++;
         else if(ch == ':' && iLen > (i + 3)
            && strCandidate[i + 1] == '/'
            && strCandidate[i + 2] == '/')
            return true;
         else
            return false;
      }
      return false;
      
   }

   var & url::set(var & varUrl, const char * pszKey, var var)
   {
      return varUrl = set_key(varUrl, pszKey, var);
   }

   gen::property & url::set(gen::property & propUrl, const char * pszKey, var var)
   {
      propUrl.set_value(set_key(propUrl.get_value(), pszKey, var));
      return propUrl;
   }

   string url::set(string & strUrl, const char * pszKey, var var)
   {
      return strUrl = set_key(strUrl, pszKey, var);
   }

   string url::set_key(const char * pszUrl, const char * pszKey, var var)
   {
      string strUrl(pszUrl);
      int iPos = strUrl.find("?");
      if(iPos < 0)
         iPos = strUrl.get_length();
      return strUrl.Left(iPos)
         + "?" +
         query_set(strUrl.Mid(iPos + 1), pszKey, var);
   }

   var & url::remove(var & varUrl, const char * pszKey)
   {
      return varUrl = remove_key(varUrl, pszKey);
   }

   gen::property & url::remove(gen::property & propUrl, const char * pszKey)
   {
      propUrl.set_string(remove_key(propUrl.get_value(), pszKey));
      return propUrl;
   }

   string url::remove(string & strUrl, const char * pszKey)
   {
      return strUrl = remove_key(strUrl, pszKey);
   }

   string url::remove_key(const char * pszUrl, const char * pszKey)
   {
      string strUrl(pszUrl);
      int iPos = strUrl.find("?");
      if(iPos < 0)
         return strUrl;
      return strUrl.Left(iPos) + gen::str::has_char(query_remove(strUrl.Mid(iPos + 1), pszKey), "?");
   }

   string url::query_set(const char * pszQuery, const char * pszKey, var var)
   {
      gen::property_set set(get_app());
      set.parse_url_query(pszQuery);
      set[pszKey] = var;
      return set.get_http_post();
   }

   string url::query_remove(const char * pszQuery, const char * pszKey)
   {
      gen::property_set set(get_app());
      set.parse_url_query(pszQuery);
      set.remove_by_name(pszKey);
      return set.get_http_post();
   }

   string url::query_remove(const char * pszQuery, stringa & straKey)
   {
      gen::property_set set(get_app());
      set.parse_url_query(pszQuery);
      set.remove_by_name(straKey);
      return set.get_http_post();
   }

   bool url::locale_is_eu(const char * pszLocale)
   {
      string strLocale(pszLocale);
      if(
         strLocale == "eu"
      || strLocale == "se"
      || strLocale == "at"
      || strLocale == "dk"
      || strLocale == "en-uk" 
      || strLocale == "uk"
      || strLocale == "fi"
      || strLocale == "gr"
      || strLocale == "de"
      || strLocale == "nl"
      || strLocale == "be"
      || strLocale == "fr"
      || strLocale == "it"
      || strLocale == "pt"
      || strLocale == "cz"
      || strLocale == "lu"
      || strLocale == "ie"
      || strLocale == "no"
      || strLocale == "cy"
      || strLocale == "su"
      || strLocale == "lv"
      || strLocale == "li"
      || strLocale == "hu"
      || strLocale == "es"
      || strLocale == "sk"
      || strLocale == "cz"
      || strLocale == "si"
      || strLocale == "ro"
      || strLocale == "kz"
      || strLocale == "ru"
      || strLocale == "pl"
      || strLocale == "tr"
      || strLocale == "ee")
      {
         return true;
      }
      return false;
   }

   bool url::locale_is_asia(const char * pszLocale)
   {
      string strLocale(pszLocale);
      if(strLocale == "asia"
      || strLocale == "cn"
      || strLocale == "tw"
      || strLocale == "vn" 
      || strLocale == "in"
      || strLocale == "kg"
      || strLocale == "kz"
      || strLocale == "kr"
      || strLocale == "my"
      || strLocale == "ph"
      || strLocale == "sg"
      || strLocale == "su"
      || strLocale == "ru"
      || strLocale == "zh"
      || strLocale == "hk"
      || strLocale == "ja"
      || strLocale == "jp"
      || strLocale == "tr")
      {
         return true;
      }
      return false;
   }

   bool url::locale_is_middle_east(const char * pszLocale)
   {
      string strLocale(pszLocale);
      if(strLocale == "sy"
      || strLocale == "tr"
      || strLocale == "il"
      || strLocale == "ps")
      {
         return true;
      }
      return false;
   }



   bool url::locale_is_south_america(const char * pszLocale)
   {
      string strLocale(pszLocale);
      if(strLocale == "cl"
      || strLocale == "br"
      || strLocale == "ar"
      || strLocale == "ec" 
      || strLocale == "pe"
      || strLocale == "ve"
      || strLocale == "bo"
      || strLocale == "co"
      || strLocale == "py"
      || strLocale == "uy"
      || strLocale == "gs"
      || strLocale == "amdesur")
      {
         return true;
      }
      return false;
   }

   bool url::locale_is_oceania(const char * pszLocale)
   {
      string strLocale(pszLocale);
      if(strLocale == "au"
      || strLocale == "oceania" 
      || strLocale == "nz" 
      || strLocale == "tl")
      {
         return true;
      }
      return false;
   }


   bool url::locale_is_africa(const char * pszLocale)
   {
      string strLocale(pszLocale);
      if(strLocale == "ug"
      || strLocale == "sc"
      || strLocale == "cm"
      || strLocale == "za" 
      || strLocale == "africa" )
      {
         return true;
      }
      return false;
   }

   bool url::locale_is_latin_america(const char * pszLocale)
   {
      string strLocale(pszLocale);
      if(strLocale == "mx")
      {
         return true;
      }
      return locale_is_caribe(pszLocale) || locale_is_central_america(pszLocale) || locale_is_south_america(pszLocale);
   }

   bool url::locale_is_north_america(const char * pszLocale)
   {
      string strLocale(pszLocale);
      if(strLocale == "mx"
      || strLocale == "us"
      || strLocale == "ca")
      {
         return true;
      }
      return false;
   }

   bool url::locale_is_caribe(const char * pszLocale)
   {
      string strLocale(pszLocale);
      if(strLocale == "caribe")
         return true;
      if(strLocale == "ht"
      || strLocale == "cu"
      || strLocale == "tc")
      {
         return true;
      }
      return false;
   }


   bool url::locale_is_central_america(const char * pszLocale)
   {
      string strLocale(pszLocale);
      if(strLocale == "central_america")
         return true;
      if(strLocale == "centralam")
         return true;
      if(strLocale == "bz")
      {
         return true;
      }
      return false;
   }

   bool url::locale_is_america(const char * pszLocale)
   {
      string strLocale(pszLocale);
      if(strLocale == "america")
         return true;
      return 
         locale_is_central_america(pszLocale) 
      || locale_is_caribe(pszLocale) 
      || locale_is_south_america(pszLocale) 
      || locale_is_north_america(pszLocale);
   }

   string url::set_script(const char * pszUrl, const char * pszScript)
   {
      return get_protocol(pszUrl) + "://" + get_root(pszUrl) + string(pszScript) + gen::str::has_char(get_query(pszUrl), "?");
   }

   string url::override_if_empty(const char * pszDst, const char * pszSrc, bool bOverrideQuery)
   {
      string strProtocol = get_protocol(pszDst);
      string strProtocolOver = get_protocol(pszSrc);
      string strRoot = get_root(pszDst);
      string strRootOver = get_root(pszSrc);
      string strScript = get_script(pszDst);
      string strScriptOver = get_script(pszSrc);
      string strQuery = get_query(pszDst);
      string strQueryOver = get_query(pszSrc);

      if(strProtocol.is_empty())
         strProtocol = strProtocolOver;
      if(strRoot.is_empty())
         strRoot = strRootOver;
      if(strScript.is_empty())
         strScript = strScriptOver;
      if(bOverrideQuery && strQuery.is_empty())
         strQuery = strQueryOver;
      if(!gen::str::begins(strScript, "/"))
         strScript = "/" + strScript;
      
      return strProtocol + "://" + strRoot + strScript + gen::str::has_char(strQuery, "?");
   }

} // namespace ca2