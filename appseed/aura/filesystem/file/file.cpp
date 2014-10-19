#include "framework.h"


string file_extension_dup(const char * path)
{

   string str = file_name_dup(path);

   strsize iPos = str.reverse_find('.');

   if(iPos >= 0)
   {

      return str.Mid(iPos + 1);

   }
   else
   {

      return "";

   }

}






string url_dir_name_for_relative(const char * pszPath)
{
   string strDir(pszPath);

   if(str::ends(strDir,"/"))
      return strDir;

   str::ends_eat(strDir,"/");

   strsize iFind = strDir.reverse_find("/");

   if(iFind < 0)
      return "/";

   return strDir.substr(0,iFind + 1);

}

string defer_solve_relative_compresions(const char * pszAbsolute)
{
   string strAbsolute(pszAbsolute);

   strAbsolute.replace("/./","/");

   strsize iFind;
   strsize iFind2;

   while((iFind = strAbsolute.find("/../")) >= 0)
   {
      iFind2 = strAbsolute.reverse_find("/",iFind - 1);
      if(iFind2 <= 0)
      {
         strAbsolute = strAbsolute.substr(iFind + 3);
      }
      else
      {
         strAbsolute = strAbsolute.substr(0,iFind2) + strAbsolute.substr(iFind + 3);
      }
   }

   return strAbsolute;
}

string defer_solve_relative_name(const char * pszRelative,const char * pszAbsolute)
{
   string strRelative(pszRelative);
   string strAbsolute(pszAbsolute);
   if(strRelative.is_empty())
      return "";
   if(strAbsolute.is_empty())
      return defer_solve_relative_compresions(strRelative);
   if(str::begins_ci(strRelative,"http://"))
      return defer_solve_relative_compresions(strRelative);
   if(str::begins_ci(strRelative,"https://"))
      return defer_solve_relative_compresions(strRelative);
   if(str::begins_ci(strRelative,"ftp://"))
      return defer_solve_relative_compresions(strRelative);
   if(str::begins_ci(strRelative,"ext://"))
      return defer_solve_relative_compresions(strRelative);

   index iFind = strRelative.find(":\\");

   if(iFind >= 0)
   {
      index i = 0;
      for(; i < iFind; i++)
      {
         if(!isalpha_dup(strRelative[i]) && !isdigit_dup(strRelative[i]))
            break;
      }

      if(i == iFind)
         return defer_solve_relative_compresions(strRelative);

   }

   strAbsolute = ::url_dir_name_for_relative(strAbsolute);

   if(!str::ends(strAbsolute,"/"))
      strAbsolute += "/";
   strRelative = strAbsolute + strRelative;


   return defer_solve_relative_compresions(strRelative);

}
