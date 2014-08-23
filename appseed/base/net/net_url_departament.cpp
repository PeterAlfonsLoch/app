#include "framework.h"


#if defined(LINUX)
//#include <ctype.h>
#endif



namespace url
{


   departament::departament(sp(::aura::application) papp) :
	   element(papp),
      ::aura::departament(papp)
   {

   }

   departament::~departament()
   {

   }


   string departament::get_protocol(const char * psz)
   {
      string str(psz);
      index iPos = str.find(":");
      if(iPos == -1)
         return "";
      return str.Mid(0, iPos);
   }

   string departament::get_root(const char * psz)
   {
      string str(psz);
      index iPos = str.find(":");
      if(iPos == -1)
         return psz;
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

   string departament::get_server(const char * psz)
   {

      string strRoot = get_root(psz);

      strsize iPos = strRoot.find(":");

      if(iPos < 0)
         return strRoot;

      return strRoot.Left(iPos);

   }

   int32_t departament::get_port(const char * psz, int32_t iDefault)
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

   string departament::get_object(const char * psz)
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

   string departament::object_get_script(const char * psz) // page
   {

      string str(psz);

      strsize iFind = str.find('?');

      if(iFind < 0)
         return url_decode(str);
      else
         return url_decode(str.Left(iFind));

   }

   string departament::object_get_query(const char * psz) // id=1
   {

      string str(psz);

      strsize iFind = str.find('?');

      if(iFind < 0)
         return "";
      else
         return str.Mid(iFind + 1);

   }

   string departament::object_set(const char * pszObject, const char * pszKey, var var)
   {

      string strQuery = object_get_query(pszObject);

      return object_get_script(pszObject) + ::str::has_char(query_set(strQuery, pszKey, var), "?");

   }


   string departament::get_script(const char * psz) // page
   {

      return object_get_script(get_object(psz));

   }

   string departament::get_query(const char * psz) // id=1
   {

      return object_get_query(get_object(psz));

   }

   string departament::object(const char * pszScript, const char * pszQuery)
   {

      string strScript(pszScript);

      string strQuery(pszQuery);

      if(strQuery.has_char())
         return strScript + "?" + strQuery;
      else
         return strScript;

   }


   string departament::path(const char * psz1, const char * psz2)
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

   string departament::path(const char * psz1, const char * psz2, const char * psz3)
   {

      return path(path(psz1, psz2), psz3);

   }

   string departament::name(const char * psz)
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


   string departament::url_encode(const char * psz)
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


   string departament::url_decode(const char * psz)
   {

      return url_decode_dup(psz);

   }


   string departament::url_decode(const char * lpszUrl, strsize iLen)
   {

      return url_decode_dup(lpszUrl,iLen);

   }

   string departament::query_append(const char * pszUrl, const char * pszQuery)
   {

      string strUrl(pszUrl);

      strsize iStart = strUrl.find("://");

      if(iStart > 0)
      {

         iStart = strUrl.find("/", iStart + 4);

         if(iStart < 0)
         {

//xxx            TRACE("invalid url %s", pszUrl);

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


   bool departament::is_url(const char * pszCandidate)
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

   var & departament::var_set(var & varUrl, const char * pszKey, var var)
   {

      return varUrl = set_key(varUrl, pszKey, var);

   }

   property & departament::property_set(property & propUrl, const char * pszKey, var var)
   {

      propUrl.set_value(set_key(propUrl.get_value(), pszKey, var));

      return propUrl;

   }

   string departament::string_set(string & strUrl, const char * pszKey, var var)
   {

      return strUrl = set_key(strUrl, pszKey, var);

   }

   string departament::set_key(const char * pszUrl, const char * pszKey, var var)
   {

      string strUrl(pszUrl);

      strsize iPos = strUrl.find("?");

      if(iPos < 0)
         iPos = strUrl.get_length();

      return strUrl.Left(iPos)
         + "?" +
         query_set(strUrl.Mid(iPos + 1), pszKey, var);

   }

   void departament::set_key(string & strUrl, const char * pszUrl, const char * pszKey, var var)
   {

      strUrl = pszUrl;

      strsize iPos = strUrl.find('?');

      if(iPos < 0)
         iPos = strUrl.get_length();

      strUrl = strUrl.Left(iPos) + "?" + query_set(strUrl.Mid(iPos + 1), pszKey, var);

   }

   void departament::set_param(string & strUrl, const char * pszUrl, const char * pszKey, const string & strParam)
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

   var & departament::var_remove(var & varUrl, const char * pszKey)
   {

      return varUrl = remove_key(varUrl, pszKey);

   }

   property & departament::property_remove(property & propUrl, const char * pszKey)
   {

      propUrl.set_string(remove_key(propUrl.get_value(), pszKey));

      return propUrl;

   }

   string departament::string_remove(string & strUrl, const char * pszKey)
   {

      return strUrl = remove_key(strUrl, pszKey);

   }

   string departament::remove_key(const char * pszUrl, const char * pszKey)
   {

      string strUrl(pszUrl);

      strsize iPos = strUrl.find("?");

      if(iPos < 0)
         return strUrl;

      return strUrl.Left(iPos) + ::str::has_char(query_remove(strUrl.Mid(iPos + 1), pszKey), "?");

   }

   var departament::get_var(const char * pszUrl, const char * pszKey)
   {

      string strUrl(pszUrl);

      strsize iPos = strUrl.find('?');

      if(iPos < 0)
         return var(var::type_empty);
      else
         return query_get_var(strUrl.Mid(iPos + 1), pszKey);

   }

   string departament::get_param(const char * pszUrl, const char * pszKey)
   {

      string strUrl(pszUrl);

      strsize iPos = strUrl.find('?');

      if(iPos < 0)
         return var(var::type_empty);
      else
         return query_get_param(strUrl.Mid(iPos + 1), pszKey);

   }

   bool departament::get_param(string & strValue, const string & strUrl, const string & strKey)
   {

      strsize iPos = strUrl.find('?');

      if(iPos < 0)
         return false;
      else
         return query_get_param(strValue, strUrl.Mid(iPos + 1), strKey);

   }

   bool departament::has_param(const string & strUrl, const string & strKey)
   {

      strsize iPos = strUrl.find('?');

      if(iPos < 0)
         return false;
      else
         return query_has_param(strUrl.Mid(iPos + 1), strKey);

   }

   bool departament::param_has_char(const string & strUrl, const string & strKey)
   {

      strsize iPos = strUrl.find('?');

      if(iPos < 0)
         return false;
      else
         return query_param_has_char(strUrl.Mid(iPos + 1), strKey);
   }

   bool departament::has_param_replace(string & strUrl, const string & strKey, const string & strValue)
   {

      strsize iPos = strUrl.find('?');

      if(iPos < 0)
         return false;
      else
      {

         string strQuery = strUrl.Mid(iPos + 1);

         if(!query_has_param_replace(strQuery, strKey, strValue))
            return false;

          strUrl = strUrl.Left(iPos + 1) + strQuery;

          return true;
      }
   }

   string departament::query_set(const char * pszQuery, const char * pszKey, var var)
   {

      string strQuery(pszQuery);

      string strKey(url_encode(pszKey));

      string strKeyEqual = strKey + "=";

      string strAndKeyEqual = "&" + strKeyEqual;

      string strKey2(url_encode(pszKey));

      string strKeyEqual2 = strKey + "=";

      string strAndKeyEqual2 = "&" + strKeyEqual;

      string strValue = url_encode(var.get_string());

      if(::str::begins(strQuery, strKeyEqual))
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
      else if(::str::begins(strQuery, strKeyEqual2))
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

   string departament::query_set_param(const char * pszQuery, const char * pszKey, const string & strParam)
   {

      string strQuery(pszQuery);

      string strKey(pszKey);

      string strKeyEqual = strKey + "=";

      string strAndKeyEqual = "&" + strKeyEqual;

      if(::str::begins(strQuery, strKeyEqual))
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

   string departament::query_remove(const char * pszQuery, const char * pszKey)
   {

      ::property_set set(get_app());

      set.parse_url_query(pszQuery);

      set.remove_by_name(pszKey);

      return set.get_http_post();

   }

   string departament::__query_remove(const char * pszQuery, const char * pszAndKeyEqual)
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

   string departament::query_remove(const char * pszQuery, stringa & straKey)
   {

      ::property_set set(get_app());

      set.parse_url_query(pszQuery);

      set.remove_by_name(straKey);

      return set.get_http_post();

   }


   var departament::query_get_var(const char * pszQuery, const char * pszKey)
   {

      string strQuery(pszQuery);

      string strKey(pszKey);

      string strKeyEqual = strKey + "=";

      string strAndKeyEqual = "&" + strKeyEqual;

      var varValue;

      strsize iPos = 0;

      if(::str::begins(strQuery, strKeyEqual))
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

   string departament::query_get_param(const string & strQuery, const string & strKey)
   {

      string strValue;

      if(!query_get_param(strValue, strQuery, strKey))
         return "";

      return strValue;

   }

   bool departament::query_get_param(string & strValue, const string & strQuery, const string & strKey)
   {

      strsize iCmp = strQuery.length() - strKey.length();
      if(iCmp < 0)
         return false;

      if(strncmp(strQuery, strKey, strKey.length()) == 0)
      {
         if(iCmp == 0)
         {
            strValue = "";
            return true;
         }
         else if(strQuery[strKey.length()] == '=')
         {
            strsize iFind2 = strQuery.find('&', strKey.length() + 1);
            if(iFind2 > 0)
            {
               strValue = strQuery.Mid(strKey.length() + 1, iFind2 - (strKey.length() + 1));
            }
            else
            {
               strValue = strQuery.Mid(strKey.length() + 1);
            }
            return true;
         }

      }

      strsize iStart = strKey.length();

      strsize iFind;

      while((iFind = strQuery.find(strKey, iStart)) >= 0)
      {
         if(strQuery[iFind - 1] == '&')
         {
            if(strQuery.length() == (iFind + strKey.length()))
            {
               strValue = "";
               return true;
            }
            else if(strQuery[iFind + strKey.length()] == '=')
            {
               strsize iFind2 = strQuery.find('&', iFind + strKey.length() + 1);
               if(iFind2 > 0)
               {
                  strValue = strQuery.Mid(iFind + strKey.length() + 1, iFind2 - (iFind + strKey.length() + 1));
               }
               else
               {
                  strValue = strQuery.Mid(iFind + strKey.length() + 1);
               }
               return true;
            }
         }
         iStart = iFind + strKey.length() + 1;
      }

      return false;

   }

   bool departament::query_has_param(const string & strQuery, const string & strKey)
   {

      strsize iCmp = strQuery.length() - strKey.length();
      if(iCmp < 0)
         return false;

      if(strncmp(strQuery, strKey, strKey.length()) == 0)
      {
         if(iCmp == 0)
         {
            return true;
         }
         else if(strQuery[strKey.length()] == '=')
         {
            return true;
         }

      }

      strsize iStart = strKey.length();

      strsize iFind;

      while((iFind = strQuery.find(strKey, iStart)) >= 0)
      {
         if(strQuery[iFind - 1] == '&')
         {
            if(strQuery.length() == (iFind + strKey.length()))
            {
               return true;
            }
            else if(strQuery[iFind + strKey.length()] == '=')
            {
               return true;
            }
         }
         iStart = iFind + strKey.length() + 1;
      }

      return false;
   }

   bool departament::query_param_has_char(const string & strQuery, const string & strKey)
   {

      strsize iCmp = strQuery.length() - strKey.length();
      if(iCmp < 0)
         return false;

      if(strncmp(strQuery, strKey, strKey.length()) == 0)
      {
         if(iCmp == 0)
         {
            return false;
         }
         else if(strQuery[strKey.length()] == '=')
         {
            strsize iFind2 = strQuery.find('&', strKey.length() + 1);
            if(iFind2 > 0)
            {
               return (iFind2 - (strKey.length() + 1)) > 0;
            }
            else
            {
               return (strQuery.length() - (strKey.length() + 1)) > 0;
            }

         }

      }

      strsize iStart = strKey.length();

      strsize iFind;

      while((iFind = strQuery.find(strKey, iStart)) >= 0)
      {
         if(strQuery[iFind - 1] == '&')
         {
            if(strQuery.length() == (iFind + strKey.length()))
            {
               return false;
            }
            else if(strQuery[iFind + strKey.length()] == '=')
            {
               strsize iFind2 = strQuery.find('&', iFind + strKey.length() + 1);
               if(iFind2 > 0)
               {
                  return (iFind2 - (iFind + strKey.length() + 1)) > 0;
               }
               else
               {
                  return (strQuery.length() - (iFind + strKey.length() + 1)) > 0;
               }
            }
         }
         iStart = iFind + strKey.length() + 1;
      }

      return false;

   }

   bool departament::query_has_param_replace(string & strQuery, const string & strKey, const string & strValue)
   {

      strsize iCmp = strQuery.length() - strKey.length();
      if(iCmp < 0)
         return false;

      if(strncmp(strQuery, strKey, strKey.length()) == 0)
      {
         if(iCmp == 0)
         {
            strQuery += "=" + strValue;
            return true;
         }
         else if(strQuery[strKey.length()] == '=')
         {
            strsize iFind2 = strQuery.find('&', strKey.length() + 1);
            if(iFind2 > 0)
            {
               strQuery = strQuery.Left(strKey.length() + 1) + strValue + strQuery.Mid(iFind2);
            }
            else
            {
               strQuery = strQuery.Left(strKey.length() + 1) + strValue;
            }
            return true;
         }

      }

      strsize iStart = strKey.length();

      strsize iFind;

      while((iFind = strQuery.find(strKey, iStart)) >= 0)
      {
         if(strQuery[iFind - 1] == '&')
         {
            if(strQuery.length() == (iFind + strKey.length()))
            {
               strQuery += "=" + strValue;
               return true;
            }
            else if(strQuery[iFind + strKey.length()] == '=')
            {
               strsize iFind2 = strQuery.find('&', iFind + strKey.length() + 1);
               if(iFind2 > 0)
               {
                  strQuery = strQuery.Left(iFind + strKey.length() + 1) + strValue + strQuery.Mid(iFind2);
               }
               else
               {
                  strQuery = strQuery.Left(iFind + strKey.length() + 1) + strValue;
               }
               return true;
            }
         }
         iStart = iFind + strKey.length() + 1;
      }

      return false;

   }

   bool departament::locale_is_eu(id idLocale)
   {


      if(
         idLocale == __id(eu)
      || idLocale == __id(se)
      || idLocale == __id(at)
      || idLocale == __id(dk)
      || idLocale == __id(en_uk)
      || idLocale == __id(uk)
      || idLocale == __id(fi)
      || idLocale == __id(gr)
      || idLocale == __id(de)
      || idLocale == __id(nl)
      || idLocale == __id(be)
      || idLocale == __id(fr)
      || idLocale == __id(it)
      || idLocale == __id(pt)
      || idLocale == __id(cz)
      || idLocale == __id(lu)
      || idLocale == __id(ie)
      || idLocale == __id(no)
      || idLocale == __id(cy)
      || idLocale == __id(su)
      || idLocale == __id(lv)
      || idLocale == __id(li)
      || idLocale == __id(hu)
      || idLocale == __id(es)
      || idLocale == __id(sk)
      || idLocale == __id(cz)
      || idLocale == __id(si)
      || idLocale == __id(ro)
      || idLocale == __id(kz)
      || idLocale == __id(ru)
      || idLocale == __id(pl)
      || idLocale == __id(tr)
      || idLocale == __id(ee))
      {
         return true;
      }

      return false;

   }

   bool departament::locale_is_asia(id idLocale)
   {

      if(idLocale == __id(asia)
      || idLocale == __id(cn)
      || idLocale == __id(tw)
      || idLocale == __id(vn)
      || idLocale == __id(in)
      || idLocale == __id(kg)
      || idLocale == __id(kz)
      || idLocale == __id(kr)
      || idLocale == __id(my)
      || idLocale == __id(ph)
      || idLocale == __id(sg)
      || idLocale == __id(su)
      || idLocale == __id(ru)
      || idLocale == __id(zh)
      || idLocale == __id(hk)
      || idLocale == __id(ja)
      || idLocale == __id(jp)
      || idLocale == __id(tr))
      {
         return true;
      }

      return false;

   }

   bool departament::locale_is_middle_east(id idLocale)
   {

      string strLocale(idLocale);

      if(idLocale == __id(sy)
      || idLocale == __id(tr)
      || idLocale == __id(il)
      || idLocale == __id(ps))
      {
         return true;
      }

      return false;

   }



   bool departament::locale_is_south_america(id idLocale)
   {

      string strLocale(idLocale);

      if(idLocale == __id(ar)
      || idLocale == __id(bo)
      || idLocale == __id(br)
      || idLocale == __id(cl)
      || idLocale == __id(co)
      || idLocale == __id(ec)
      || idLocale == __id(gs)
      || idLocale == __id(pe)
      || idLocale == __id(py)
      || idLocale == __id(uy)
      || idLocale == __id(ve)
      || idLocale == __id(amdesur))
      {
         return true;
      }

      return false;

   }

   bool departament::locale_is_oceania(id idLocale)
   {

      string strLocale(idLocale);

      if(idLocale == __id(au)
      || idLocale == __id(oceania)
      || idLocale == __id(nz)
      || idLocale == __id(tl))
      {
         return true;
      }

      return false;

   }


   bool departament::locale_is_africa(id idLocale)
   {

      string strLocale(idLocale);

      if(idLocale == __id(ug)
      || idLocale == __id(sc)
      || idLocale == __id(cm)
      || idLocale == __id(za)
      || idLocale == __id(africa) )
      {
         return true;
      }

      return false;

   }

   bool departament::locale_is_latin_america(id idLocale)
   {

      string strLocale(idLocale);

      if(idLocale == __id(mx))
      {
         return true;
      }

      return locale_is_caribe(idLocale) || locale_is_central_america(idLocale) || locale_is_south_america(idLocale);

   }

   bool departament::locale_is_north_america(id idLocale)
   {

      string strLocale(idLocale);

      if(idLocale == __id(mx)
      || idLocale == __id(us)
      || idLocale == __id(ca))
      {
         return true;
      }

      return false;

   }

   bool departament::locale_is_caribe(id idLocale)
   {

      string strLocale(idLocale);

      if(idLocale == __id(caribe))
         return true;

      if(idLocale == __id(ht)
      || idLocale == __id(cu)
      || idLocale == __id(tc))
      {
         return true;
      }

      return false;

   }


   bool departament::locale_is_central_america(id idLocale)
   {

      string strLocale(idLocale);

      if(strLocale == "central_america")
         return true;

      if(idLocale == __id(centralam))
         return true;

      if(idLocale == __id(bz))
      {
         return true;
      }

      return false;

   }

   bool departament::locale_is_america(id idLocale)
   {

      string strLocale(idLocale);

      if(idLocale == __id(america))
         return true;

      return
         locale_is_central_america(idLocale)
      || locale_is_caribe(idLocale)
      || locale_is_south_america(idLocale)
      || locale_is_north_america(idLocale);

   }

   string departament::set_script(const char * pszUrl, const char * pszScript)
   {

      return get_protocol(pszUrl) + "://" + get_root(pszUrl) + string(pszScript) + ::str::has_char(get_query(pszUrl), "?");

   }

   string departament::override_if_empty(const char * pszDst, const char * pszSrc, bool bOverrideQuery)
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

      if(!::str::begins(strScript, "/"))
         strScript = "/" + strScript;

      return strProtocol + "://" + strRoot + strScript + ::str::has_char(strQuery, "?");
   }


   string departament::override_if_set_at_source(const char * pszDst, const char * pszSrc)
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

      if(!::str::begins(strScript, "/"))
         strScript = "/" + strScript;

      return strProtocol + "://" + strRoot + strScript + ::str::has_char(strQuery, "?");
   }


   string departament::to_punycode(const char * psz)
   {

      char * p = NULL;

      Idna_rc rc = (Idna_rc) idna_to_ascii_lz(psz, &p, 0);

      if (rc != IDNA_SUCCESS)
      {
         throw idna_strerror(rc);
      }

      string str(p);

      free(p);

      return str;

   }

   string departament::from_punycode(const char * psz)
   {

      if(psz == NULL || *psz == '\0')
         return "";

      {
       
         string str(psz);

         str.trim();

         if(str.is_empty())
            return "";

      }

      char * p = NULL;

      Idna_rc rc = (Idna_rc)idna_to_unicode_lzlz(psz, &p, 0);

      if (rc != IDNA_SUCCESS)
      {
         throw idna_strerror(rc);
      }

      string str(p);

      free(p);

      return str;

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


} // namespace url






