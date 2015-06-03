//#include "framework.h"


string consume_param(const char * pszCommandLine, const char ** pszEndPtr)
{

   if(pszCommandLine == NULL)
      return "";

   const char * psz = pszCommandLine;

   while(*psz && isspace_dup(*psz))
      psz++;

   const char * pszStart;

   bool bQuoted = *psz == '\"';

   if(bQuoted)
   {
      psz++;
      pszStart = psz;
      while(*psz != '\0' && *psz != '\"')
         psz++;
   }
   else
   {
      pszStart = psz;
      while(*psz != '\0' &&!isspace_dup(*psz))
         psz++;
   }
   
   const char * pszEnd = psz;

   if(pszEndPtr != NULL)
   {
      *pszEndPtr = pszEnd + 1;
   }

   return string(pszStart, pszEnd - pszStart);

}



string get_command_line_param(const char * pszCommandLine, const char * pszParam, const char * pszIfParamValue, const char * pszReplaceParam)
{

   string strValue;

   get_command_line_param(strValue, pszCommandLine,pszParam);

   if(strValue == pszIfParamValue)
   {

      string strReplace;
         
      if(get_command_line_param(strReplace,pszCommandLine,pszReplaceParam) && strReplace.has_char())
      {

         strValue = strReplace;

      }

   }

   return ::str::trim_any_quotes(strValue.trimmed());

}

//string get_command_line_param(const char * pszCommandLine, const char * pszParam)
//{
//
//   string strParam(pszParam);
//
//   strParam = strParam + "=";
//
//   string strValue;
//
//   const char * pszValue = strstr_dup(pszCommandLine, strParam);
//
//   if(pszValue == NULL)
//      return "";
//
//   pszValue += strParam.length();
//
//
//   if(*pszValue == '"')
//   {
//
//      const char * pszValueEnd = strchr_dup(pszValue + 1, '"');
//
//      if(pszValueEnd == NULL)
//      {
//         strValue = string(pszValue);
//      }
//      else
//      {
//         strValue = string(pszValue, pszValueEnd - pszValue + 1);
//      }
//
//   }
//   else
//   {
//
//      const char * pszValueEnd = strstr_dup(pszValue, " ");
//
//      if(pszValueEnd == NULL)
//      {
//         strValue = string(pszValue);
//      }
//      else
//      {
//         strValue = string(pszValue, pszValueEnd - pszValue);
//      }
//
//   }
//
//   return ::str::trim_any_quotes(strValue.trimmed());
//
//
//}


string get_command_line_param2(const char * psz,const char * pszParam)
{

   string str;

   if(!get_command_line_param(str,psz,pszParam))
   {
      
      return "";

   }

   return str;

}


bool get_command_line_param(string & wstrValue,const char * psz,const char * pszParam)
{

   string wstr(psz);

   string wstrParam(pszParam);
   
   auto iFind = wstr.find(wstrParam + "=");

   if(iFind == wstring::npos)
   {

      iFind = wstr.find(wstrParam + " ");

      if(iFind == wstring::npos)
      {

         iFind = wstr.find(wstrParam);

         if(iFind == wstring::npos)
         {

            return false;

         }
         else if(iFind == wstr.length() - wstrParam.length())
         {

            wstrValue = "";

            return true;

         }
         else
         {

            return false;

         }

      }
      else
      {

         wstrValue = "";

         return true;

      }

   }

   auto iEnd = wstr.find(" ",iFind);

   if(iEnd == wstring::npos)
   {
         
      wstrValue = wstr.substr(iFind + wstrParam.length() + 1);

   }
   else
   {

      wstrValue = wstr.substr(iFind + wstrParam.length() + 1,iEnd - iFind - wstrParam.length());

   }

   wstrValue = ::str::trim_any_quotes(wstrValue);

   return true;

}


CLASS_DECL_AURA string process_platform_dir_name()
{

#if defined(_M_IX86)

   return "x86";

#else

   return "x64";

#endif

}



