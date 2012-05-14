#include "framework.h"

namespace fs
{

   data::data(::ca::application * papp) :
      ca(papp),
      ::ca::data(papp)
   {
   }

   bool data::has_subdir(const char * pszPath)
   {
      UNREFERENCED_PARAMETER(pszPath);
      return false;
   }



   string data::file_name(const char * pszPath)
   {
      UNREFERENCED_PARAMETER(pszPath);
      return "";
   }

   bool data::file_move(const char * pszDst, const char * pszSrc)
   {
      UNREFERENCED_PARAMETER(pszDst);
      UNREFERENCED_PARAMETER(pszSrc);
      return false;
   }

   string data::dir_path(const char * psz1, const char * psz2)
   {
      string str(psz1);
      if(str.Right(1) != '/')
         str += "/";
      return str + psz2;
   }


   string data::eat_end_level(const char * pszPath, int iCount)
   {
      string strPath(pszPath);
      strsize iFind;
      int iStart = strPath.get_length() - 1;
      if(iCount <= 0)
         return pszPath;
      while(iCount > 0)
      {
         iFind = strPath.reverse_find('/', iStart);
         int iPos = iFind - 1;
         if(iPos >= 0 && strPath[iPos] == '/')
         {
            iPos--;
            if(iPos >= 0 && strPath[iPos] == ':')
            {
               if(iFind == iStart)
               {
                  iPos--;
                  // t12n dedicaverse comments : protocol name
                  iFind = strPath.reverse_find('/', iPos);
                  if(iFind < 0)
                     iFind = 0;
               }
               else
               {
                  iFind++;
               }
            }
         }
         iCount--;
         if(iCount <= 0)
            break;
         if(iFind < 0)
            return "";
         iStart = iFind - 1;
      }
      return strPath.Left(iFind);
   }

   bool data::ls(const char * pszDir, stringa * pstraPath, stringa * pstraTitle)
   {
      UNREFERENCED_PARAMETER(pszDir);
      UNREFERENCED_PARAMETER(pstraPath);
      UNREFERENCED_PARAMETER(pstraTitle);
      return false;
   }

   bool data::is_dir(const char * pszPath)
   {
      UNREFERENCED_PARAMETER(pszPath);
      return false;
   }

   void data::root_ones(stringa & stra)
   {
      UNREFERENCED_PARAMETER(stra);
   }

   void data::get_ascendants_path(const char * lpcsz, stringa & straParam)
   {
      stringa stra;
      get_ascendants_name(lpcsz, stra);
      string str;
      for(int i = 0; i < stra.get_size(); i++)
      {
         str += stra[i];
         if(i != 0 || !gen::str::ends(str, "//"))
         {
            str += "/";
         }
         straParam.add(str);
      }
   }

   void data::get_ascendants_name(const char * lpcsz, stringa & straParam)
   {
      stringa straSeparator;
      straSeparator.add("/");
      straSeparator.add("\\");
      straParam.add_smallest_tokens(lpcsz, straSeparator, TRUE);
      for(int i = 0; i < straParam.get_size(); )
      {
         if(straParam[i].is_empty())
         {
            straParam.remove_at(i);
            if(i == 1 && gen::str::ends(straParam[0], ":"))
            {
               straParam[0] = straParam[0] + "//";
            }
         }
         else
         {
            i++;
         }
      }
   }

   ex1::filesp data::get_file(var varFile, UINT nOpenFlags, ::ex1::file_exception_sp * pexception)
   {
      UNREFERENCED_PARAMETER(varFile);
      UNREFERENCED_PARAMETER(nOpenFlags);
      UNREFERENCED_PARAMETER(pexception);
      return 0;
   }

   ::ex1::byte_stream data::get_byte_stream(var varFile, UINT nOpenFlags, ::ex1::file_exception_sp * pexception)
   {
      return ::ex1::byte_stream(get_file(varFile, nOpenFlags, pexception));
   }

   bool data::file_exists(const char * pszPath)
   {
      stringa straTitle;
      ls(eat_end_level(pszPath, 1), NULL, &straTitle);
      return straTitle.contains_ci(file_name(pszPath));
   }

} // namespace fs
