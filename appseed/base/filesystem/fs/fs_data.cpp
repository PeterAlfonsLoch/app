#include "framework.h"

namespace fs
{

   data::data(sp(base_application) papp) :
      element(papp),
      ::data::data(papp)
   {
   }

   bool data::has_subdir(const char * pszPath)
   {
      UNREFERENCED_PARAMETER(pszPath);
      return false;
   }

   bool data::fast_has_subdir(const char * pszPath)
   {
      return has_subdir(pszPath);
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


   bool data::tree_show_subdir(const char * pszPath)
   {
      
      return true;

   }

   string data::eat_end_level(const char * pszPath, int32_t iCount)
   {
      string strPath(pszPath);
      strsize iFind = 0;
      strsize iStart = strPath.get_length() - 1;
      if(iCount <= 0)
         return pszPath;
      while(iCount > 0)
      {
         iFind = strPath.reverse_find('/', iStart);
         strsize iPos = iFind - 1;
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

   bool data::ls(const char * pszDir, stringa * pstraPath, stringa * pstraTitle, int64_array * piaSize)
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

   void data::root_ones(stringa & straPath, stringa & straTitle)
   {
      UNREFERENCED_PARAMETER(straPath);
      UNREFERENCED_PARAMETER(straTitle);
   }

   void data::get_ascendants_path(const char * lpcsz, stringa & straParam)
   {
      stringa stra;
      get_ascendants_name(lpcsz, stra);
      string str;
      for(int32_t i = 0; i < stra.get_size(); i++)
      {
         str += stra[i];
         if(i != 0 || !::str::ends(str, "//"))
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
      for(int32_t i = 0; i < straParam.get_size(); )
      {
         if(straParam[i].is_empty())
         {
            straParam.remove_at(i);
            if(i == 1 && ::str::ends(straParam[0], ":"))
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

   ::file::buffer_sp data::get_file(var varFile, UINT nOpenFlags)
   {
      UNREFERENCED_PARAMETER(varFile);
      UNREFERENCED_PARAMETER(nOpenFlags);
      return NULL;
   }

   bool data::file_exists(const char * pszPath)
   {
      stringa straTitle;
      ls(eat_end_level(pszPath, 1), NULL, &straTitle, NULL);
      return straTitle.contains_ci(file_name(pszPath));
   }

   var data::file_length(const char * pszPath)
   {
      
      stringa straTitle;

      int64_array iaFileSize;
      
      ls(eat_end_level(pszPath, 1), NULL, &straTitle, &iaFileSize);
      
      index iFind = straTitle.find_first_ci(file_name(pszPath));

      if (iFind < 0)
         return var(var::type_null);

      return iaFileSize[iFind];

   }

   sp(data) data::node_path_data(const char * psz)
   {

      return this;

   }

   sp(data) data::path_data(const char * psz)
   {

      return this;

   }


   bool data::is_link(const char * psz)
   {

      return ::str::ends_ci(psz,".lnk");

   }

} // namespace fs
