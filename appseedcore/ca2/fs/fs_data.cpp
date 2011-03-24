#include "stdafx.h"

namespace fs
{

   data::data(::ca::application * papp) :
      ca(papp),
      ::ca::data(papp)
   {
   }

   bool data::has_subdir(const char * pszPath)
   {
      return false;
   }



   string data::file_name(const char * pszPath)
   {
      return "";
   }
   
   bool data::file_move(const char * pszDst, const char * pszSrc)
   {
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
      int iFind = -1;
      while(iCount > 0)
      {
         iFind = strPath.reverse_find('/', iFind);
         iCount--;
         if(iCount <= 0)
            break;
         if(iFind < 0)
            return "";
      }
      return strPath.Left(iFind);
   }

   bool data::ls(const char * pszDir, stringa * pstraPath, stringa * pstraTitle)
   {
      return false;
   }

   bool data::is_dir(const char * pszPath)
   {
      return false;
   }

   void data::root_ones(stringa & stra)
   {
   }

   void data::get_ascendants_path(const char * lpcsz, stringa & straParam)
   {
      stringa stra;
      get_ascendants_name(lpcsz, stra);
      string str;
      for(int i = 0; i < stra.get_size(); i++)
      {
         str += stra[i];
         str += "/";
         straParam.add(str);
      }
   }

   void data::get_ascendants_name(const char * lpcsz, stringa & straParam)
   {
      stringa straSeparator;
      straSeparator.add("/");
      straSeparator.add("\\");
      straParam.add_smallest_tokens(lpcsz, straSeparator, FALSE);
   }

   ex1::filesp * data::get_file(const char * pszPath)
   {
      return NULL;
   }


} // namespace fs