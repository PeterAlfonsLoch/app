#include "framework.h"

namespace ex2
{

   file_set::file_set()
   {

   }

   file_set::~file_set()
   {

   }

   void file_set::add_search(stringa & stra, bool_array & baRecursive)
   {
      UNREFERENCED_PARAMETER(stra);
      UNREFERENCED_PARAMETER(baRecursive);
   }

   void file_set::add_filter(stringa & stra)
   {
      UNREFERENCED_PARAMETER(stra);
   }

   ::count file_set::get_file_count()
   {
      return 0;
   }

   void file_set::file_at(::index i, string & str)
   {
      UNREFERENCED_PARAMETER(i);
      UNREFERENCED_PARAMETER(str);
   }

   ::index file_set::find_first_file(const char * lpcsz, ::index iStart)
   {
      UNREFERENCED_PARAMETER(lpcsz);
      UNREFERENCED_PARAMETER(iStart);
      return -1;
   }

   void file_set::clear_search()
   {
   }

   void file_set::clear_filter()
   {
   }

   void file_set::clear_file()
   {
   }

   void file_set::refresh()
   {
   }

   bool file_set::get_next_file(const char * lpcszCurrentFilePath, string & strNextFilePath)
   {
      ::index i = find_first_file(lpcszCurrentFilePath);
      i++;
      if(i >= get_file_count())
         i = 0;
      if(i >= get_file_count())
         return false;
      else
      {
         file_at(i, strNextFilePath);
         return true;
      }
   }

   string file_set::get_next_file(const char * pszCurrent)
   {
      string strNextFilePath;
      if(get_next_file(pszCurrent, strNextFilePath))
      {
         return strNextFilePath;
      }
      else
      {
         return "";
      }
   }


} // namespace ex2