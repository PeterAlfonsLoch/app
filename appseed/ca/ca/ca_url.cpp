#include "framework.h"


#if defined(LINUX)
#include <ctype.h>
#endif



namespace ca
{


   string url::get_protocol(const char * psz)
   {
      string str(psz);
      index iPos = str.find(":");
      if(iPos == -1)
         return "";
      return str.Mid(0, iPos);
   }

   string url::get_root(const char * psz)
   {
      string str(psz);
      index iPos = str.find(":");
      if(iPos == -1)
         return "";
      iPos++;
      while(iPos < str.get_length() && str[iPos] == '/')
      {
         iPos++;
      }
      index iStart = iPos;
      index iEnd = str.find("/", iStart);
      if(iEnd < 0)
         return str.Mid(iStart);
      else
         return str.Mid(iStart, iEnd - iStart);
   }

   string url::get_server(const char * psz)
   {

      string strRoot = get_root(psz);

      strsize iPos = strRoot.find(":");

      if(iPos < 0)
         return strRoot;

      return strRoot.Left(iPos);

   }

   int32_t url::get_port(const char * psz, int32_t iDefault)
   {

      string strRoot = get_root(psz);

      strsize iPos = strRoot.find(":");

      if(iPos < 0)
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

      strsize iPos = str.find("://");

      if(iPos < 0)
         return psz;

      iPos += 3;

      strsize iStart = str.find("/", iPos);

      if(iStart < 0)
         return "/";
      else
         return str.Mid(iStart);

   }

   string url::object_get_script(const char * psz) // page
   {

      string str(psz);

      strsize iFind = str.find('?');

      if(iFind < 0)
         return url_decode(str);
      else
         return url_decode(str.Left(iFind));

   }

   string url::object_get_query(const char * psz) // id=1
   {

      string str(psz);

      strsize iFind = str.find('?');

      if(iFind < 0)
         return "";
      else
         return str.Mid(iFind + 1);

   }

   string url::object_set(const char * pszObject, const char * pszKey, var var)
   {

      string strQuery = object_get_query(pszObject);

      return object_get_script(pszObject) + ::ca::str::has_char(query_set(strQuery, pszKey, var), "?");

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

      strsize iQueryStart = str.find('?');

      if(iQueryStart < 0)
         iQueryStart = str.get_length();

      str = str.Left(iQueryStart);

      strsize iLastSlash = str.reverse_find('/');

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

         if(isdigit((uchar)*psz)
         || isalpha((uchar)*psz)
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

      strsize iStart = 0;

      while(true)
      {

         strsize iFind = str.find("%", iStart);

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

   string url::url_decode(const char * lpszUrl, strsize iLen)
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
               *psz = (char) (uchar) (from_hex_char(*lpszUrl) * 16 + from_hex_char(*(lpszUrl + 1)));
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

   string url::query_append(const char * pszUrl, const char * pszQuery)
   {

      string strUrl(pszUrl);

      strsize iStart = strUrl.find("://");

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

      strsize iLen = strCandidate.get_length();

      strsize i = 0;

      char ch;

      while(i < iLen)
      {

         ch = strCandidate[i];

         if(isalpha((uchar) ch))
            i++;
         else if(ch == '.')
            i++;
         else if(ch == ':' && (((i + 1) == iLen) ||
            (iLen > (i + 3)
            && strCandidate[i + 1] == '/'
            && strCandidate[i + 2] == '/')))
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

   ::ca::property & url::set(::ca::property & propUrl, const char * pszKey, var var)
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

      strsize iPos = strUrl.find("?");

      if(iPos < 0)
         iPos = strUrl.get_length();

      return strUrl.Left(iPos)
         + "?" +
         query_set(strUrl.Mid(iPos + 1), pszKey, var);

   }

   void url::set_key(string & strUrl, const char * pszUrl, const char * pszKey, var var)
   {

      strUrl = pszUrl;

      strsize iPos = strUrl.find('?');

      if(iPos < 0)
         iPos = strUrl.get_length();

      strUrl = strUrl.Left(iPos) + "?" + query_set(strUrl.Mid(iPos + 1), pszKey, var);

   }

   void url::set_param(string & strUrl, const char * pszUrl, const char * pszKey, const string & strParam)
   {

      const char * pszQuery = strchr(pszUrl, '?');

      string strKey = url_encode(pszKey);
      string strValue = url_encode(strParam);

      strsize iLenUrl = strlen(pszUrl);
      strsize iLenKey = strKey.length();

      string str;

      char * psz = str.GetBufferSetLength(iLenUrl + iLenKey + strValue.get_length() + 2);

      if(pszQuery == NULL)
      {
         strcpy(psz, pszUrl);
         psz[iLenUrl] = '?';
         strcpy(&psz[iLenUrl + 1], strKey);
         psz[iLenUrl + 1 + iLenKey] = '=';
         strcpy(&psz[iLenUrl + 1 + iLenKey + 1], strValue);
         str.ReleaseBuffer(iLenUrl + iLenKey + strValue.get_length() + 2);
      }
      else
      {
         strsize iFinalLen = pszQuery - pszUrl;
//         int32_t iPos = 0;
         strncpy(psz, pszUrl, iFinalLen);
         psz[iFinalLen] = '?';
         iFinalLen++;
         pszQuery++;
         bool bRemove = false;
         bool bAlreadyInsertedFirstParam = false;
         const char * pszQueryEnd;
         bool bInserted = false;
         while(true)
         {
            pszQueryEnd = strchr(pszQuery + 1, '&');
            if(strncmp(pszQuery, pszKey, iLenKey) == 0 && pszQuery[iLenKey] == '=')
            {
               if(!bRemove)
               {
                  if(bAlreadyInsertedFirstParam)
                  {
                     psz[iFinalLen] = '&';
                     iFinalLen++;
                  }
                  strncpy(&psz[iFinalLen], strKey, iLenKey);
                  iFinalLen += iLenKey;
                  psz[iFinalLen] = '=';
                  iFinalLen++;
                  strncpy(&psz[iFinalLen], strValue, strValue.get_length());
                  iFinalLen += strValue.get_length();
                  bRemove = true;
                  bAlreadyInsertedFirstParam = true;
                  bInserted = true;
               }
            }
            else
            {
               if(bAlreadyInsertedFirstParam)
               {
                  psz[iFinalLen] = '&';
                  iFinalLen++;
               }
               if(pszQueryEnd == NULL)
               {
                  strncpy(&psz[iFinalLen], pszQuery, iLenUrl - (pszQuery - pszUrl));
                  iFinalLen += iLenUrl - (pszQuery - pszUrl);
                  bAlreadyInsertedFirstParam = true;
                  break;
               }
               else
               {
                  strncpy(&psz[iFinalLen], pszQuery, pszQueryEnd - pszQuery);
                  iFinalLen += pszQueryEnd - pszQuery;
                  bAlreadyInsertedFirstParam = true;
               }
            }
            pszQuery = pszQueryEnd;
            if(pszQuery == NULL)
               break;
            pszQuery++;
         }
         if(!bInserted)
         {
            if(bAlreadyInsertedFirstParam)
            {
               psz[iFinalLen] = '&';
               iFinalLen++;
            }
            strncpy(&psz[iFinalLen], strKey, iLenKey);
            iFinalLen += iLenKey;
            psz[iFinalLen] = '=';
            iFinalLen++;
            strncpy(&psz[iFinalLen], strValue, strValue.get_length());
            iFinalLen += strValue.get_length();
            bRemove = true;
            bAlreadyInsertedFirstParam = true;
            bInserted = true;
         }

         str.ReleaseBuffer(iFinalLen);

      }

      strUrl = str;


   }

   var & url::remove(var & varUrl, const char * pszKey)
   {

      return varUrl = remove_key(varUrl, pszKey);

   }

   ::ca::property & url::remove(::ca::property & propUrl, const char * pszKey)
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

      strsize iPos = strUrl.find("?");

      if(iPos < 0)
         return strUrl;

      return strUrl.Left(iPos) + ::ca::str::has_char(query_remove(strUrl.Mid(iPos + 1), pszKey), "?");

   }

   var url::get_var(const char * pszUrl, const char * pszKey)
   {

      string strUrl(pszUrl);

      strsize iPos = strUrl.find('?');

      if(iPos < 0)
         return var(var::type_empty);
      else
         return query_get_var(strUrl.Mid(iPos + 1), pszKey);

   }

   string url::get_param(const char * pszUrl, const char * pszKey)
   {

      string strUrl(pszUrl);

      strsize iPos = strUrl.find('?');

      if(iPos < 0)
         return var(var::type_empty);
      else
         return query_get_param(strUrl.Mid(iPos + 1), pszKey);

   }

   string url::query_set(const char * pszQuery, const char * pszKey, var var)
   {

      string strQuery(pszQuery);

      string strKey(url_encode(pszKey));

      string strKeyEqual = strKey + "=";

      string strAndKeyEqual = "&" + strKeyEqual;

      string strKey2(url_encode(pszKey));

      string strKeyEqual2 = strKey + "=";

      string strAndKeyEqual2 = "&" + strKeyEqual;

      string strValue = url_encode(var.get_string());

      if(::ca::str::begins(strQuery, strKeyEqual))
      {
         strsize iPos = strQuery.find("&");
         if(iPos < 0)
         {
            strQuery = strKeyEqual2 + strValue;
         }
         else
         {
            strQuery = strKeyEqual2 + strValue + __query_remove(strQuery.Mid(iPos), strAndKeyEqual);
         }
      }
      else if(::ca::str::begins(strQuery, strKeyEqual2))
      {
         strsize iPos = strQuery.find("&");
         if(iPos < 0)
         {
            strQuery = strKeyEqual2 + strValue;
         }
         else
         {
            strQuery = strKeyEqual2 + strValue + __query_remove(strQuery.Mid(iPos), strAndKeyEqual);
         }
      }
      else
      {
         strsize iPos = strQuery.find(strAndKeyEqual);
         if(iPos < 0)
         {
            if(strQuery.has_char())
            {
               strQuery += strAndKeyEqual2 + strValue;
            }
            else
            {
               strQuery = strKeyEqual2 + strValue;
            }
         }
         else
         {
            iPos = strQuery.find(strAndKeyEqual2);
            if(iPos < 0)
            {
               if(strQuery.has_char())
               {
                  strQuery += strAndKeyEqual2 + strValue;
               }
               else
               {
                  strQuery = strKeyEqual2 + strValue;
               }
            }
            else
            {
               strQuery = strQuery.Left(iPos) + strAndKeyEqual2 + strValue + __query_remove(strQuery.Mid(iPos), strAndKeyEqual);
            }
         }
      }


      return strQuery;

   }

   string url::query_set_param(const char * pszQuery, const char * pszKey, const string & strParam)
   {

      string strQuery(pszQuery);

      string strKey(pszKey);

      string strKeyEqual = strKey + "=";

      string strAndKeyEqual = "&" + strKeyEqual;

      if(::ca::str::begins(strQuery, strKeyEqual))
      {
         strsize iPos = strQuery.find("&");
         if(iPos < 0)
         {
            strQuery = strKey + strParam;
         }
         else
         {
            strQuery = strKey + strParam + __query_remove(strQuery.Mid(iPos), strAndKeyEqual);
         }
      }
      else
      {
         strsize iPos = strQuery.find(strAndKeyEqual);
         if(iPos < 0)
         {
            if(strQuery.has_char())
            {
               strQuery += strAndKeyEqual + strParam;
            }
            else
            {
               strQuery = strKeyEqual + strParam;
            }
         }
         else
         {
            strQuery = strKey + strParam + __query_remove(strQuery.Mid(iPos), strAndKeyEqual);
         }
      }


      return strQuery;

   }

   string url::query_remove(const char * pszQuery, const char * pszKey)
   {

      ::ca::property_set set(get_app());

      set.parse_url_query(pszQuery);

      set.remove_by_name(pszKey);

      return set.get_http_post();

   }

   string url::__query_remove(const char * pszQuery, const char * pszAndKeyEqual)
   {

      string strQuery(pszQuery);

      while(true)
      {
         strsize iFind = strQuery.find(pszAndKeyEqual);
         if(iFind < 0)
            break;
         strsize iNextParam = strQuery.find("&", iFind + 1);
         if(iNextParam < 0)
         {
            strQuery = strQuery.Left(iFind);
         }
         else
         {
            strQuery = strQuery.Left(iFind) + strQuery.Mid(iNextParam);
         }
      }

      return strQuery;

   }

   string url::query_remove(const char * pszQuery, stringa & straKey)
   {

      ::ca::property_set set(get_app());

      set.parse_url_query(pszQuery);

      set.remove_by_name(straKey);

      return set.get_http_post();

   }


   var url::query_get_var(const char * pszQuery, const char * pszKey)
   {

      string strQuery(pszQuery);

      string strKey(pszKey);

      string strKeyEqual = strKey + "=";

      string strAndKeyEqual = "&" + strKeyEqual;

      var varValue;

      strsize iPos = 0;

      if(::ca::str::begins(strQuery, strKeyEqual))
      {
         iPos = strQuery.find('&');
         if(iPos < 0)
         {
            varValue = strQuery.Mid(strKeyEqual.get_length());
            return varValue;
         }
         else
         {
            varValue = strQuery.Mid(strKeyEqual.get_length(), iPos - strKeyEqual.get_length());
         }
      }

      while(true)
      {
         iPos = strQuery.find(strAndKeyEqual, iPos);
         if(iPos < 0)
            break;
         strsize iEnd = strQuery.find('&', iPos + 1);
         if(iEnd < 0)
         {
            if(varValue.is_new())
            {
               varValue = strQuery.Mid(iPos + strKeyEqual.get_length());
            }
            else
            {
               varValue.vara().add(strQuery.Mid(iPos + strKeyEqual.get_length()));
            }
            return varValue;
         }
         else
         {
            if(varValue.is_new())
            {
               varValue = strQuery.Mid(iPos + strKeyEqual.get_length(), iEnd - (iPos + strKeyEqual.get_length()));
            }
            else
            {
               varValue.vara().add(strQuery.Mid(iPos + strKeyEqual.get_length(), iEnd - (iPos + strKeyEqual.get_length())));
            }
         }
         iPos++;
      }


      return varValue;

   }

   string url::query_get_param(const char * pszQuery, const char * pszKey)
   {

      string strQuery(pszQuery);

      string strKey(pszKey);

      string strKeyEqual = strKey + "=";

      string strAndKeyEqual = "&" + strKeyEqual;

      string strValue;

      strsize iPos = 0;

      if(::ca::str::begins(strQuery, strKeyEqual))
      {
         iPos = strQuery.find('&');
         if(iPos < 0)
         {
            strValue = strQuery.Mid(strKeyEqual.get_length());
         }
         else
         {
            strValue = strQuery.Mid(strKeyEqual.get_length(), iPos - strKeyEqual.get_length());
         }
         return strValue;
      }

      iPos = strQuery.find(strAndKeyEqual, iPos);
      if(iPos < 0)
         return "";
      strsize iEnd = strQuery.find('&', iPos + 1);
      if(iEnd < 0)
      {
         strValue = strQuery.Mid(iPos + strKeyEqual.get_length());
      }
      else
      {
         strValue = strQuery.Mid(iPos + strKeyEqual.get_length(), iEnd - (iPos + strKeyEqual.get_length()));
      }

      return strValue;

   }

   bool url::locale_is_eu(const char * pszLocale)
   {

      string strLocale(pszLocale);

      ::ca::str::ends_eat_ci(strLocale, ".com");
      ::ca::str::ends_eat_ci(strLocale, ".net");
      ::ca::str::ends_eat_ci(strLocale, ".org");

      ::ca::str::begins_eat_ci(strLocale, "co.");
      ::ca::str::begins_eat_ci(strLocale, "or.");
      ::ca::str::begins_eat_ci(strLocale, "ne.");
      ::ca::str::begins_eat_ci(strLocale, "com.");
      ::ca::str::begins_eat_ci(strLocale, "org.");
      ::ca::str::begins_eat_ci(strLocale, "net.");

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

      if(strLocale == "ar"
      || strLocale == "bo"
      || strLocale == "br"
      || strLocale == "cl"
      || strLocale == "co"
      || strLocale == "ec"
      || strLocale == "gs"
      || strLocale == "pe"
      || strLocale == "py"
      || strLocale == "uy"
      || strLocale == "ve"
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

      return get_protocol(pszUrl) + "://" + get_root(pszUrl) + string(pszScript) + ::ca::str::has_char(get_query(pszUrl), "?");

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

      if(!::ca::str::begins(strScript, "/"))
         strScript = "/" + strScript;

      return strProtocol + "://" + strRoot + strScript + ::ca::str::has_char(strQuery, "?");
   }


   string url::override_if_set_at_source(const char * pszDst, const char * pszSrc)
   {

      string strProtocol = get_protocol(pszDst);
      string strProtocolOver = get_protocol(pszSrc);
      string strRoot = get_root(pszDst);
      string strRootOver = get_root(pszSrc);
      string strScript = get_script(pszDst);
      string strScriptOver = get_script(pszSrc);
      string strQuery = get_query(pszDst);
      string strQueryOver = get_query(pszSrc);

      if(strProtocolOver.has_char())
         strProtocol = strProtocolOver;

      if(strRootOver.has_char())
         strRoot = strRootOver;

      if(strScriptOver.has_char())
         strScript = strScriptOver;

      if(strQueryOver.has_char())
         strQuery = strQueryOver;

      if(!::ca::str::begins(strScript, "/"))
         strScript = "/" + strScript;

      return strProtocol + "://" + strRoot + strScript + ::ca::str::has_char(strQuery, "?");
   }

   inline bool isalnum_dup(int32_t i)
   {
      return (i >= '0' && i <= '9') || (i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z');
   }


   bool is_url(const char * pszCandidate, const char ** ppszRequest)
   {
      const char * psz = pszCandidate;
      while(*psz != '\0' && (*psz == '.' || *psz == '_' || isalnum_dup(*psz)))
      {
         psz++;
      }
      if(psz == pszCandidate)
         return false;
      if(*psz != ':')
         return false;
      psz++;
      if(*psz != '/')
         return false;
      psz++;
      if(*psz != '/')
         return false;
      psz++;
      while(*psz != '\0' && (*psz == '.' || *psz == '_' || isalnum_dup(*psz)))
      {
         psz++;
      }
      if(*psz != '\0' && *psz != '/')
         return false;
      if(ppszRequest != NULL)
      {
         *ppszRequest = psz;
      }
      return true;

   }

} // namespace ca


