#include "framework.h"


namespace file
{


   set::set()
   {

   }

   set::~set()
   {

   }

   void set::add_search(stringa & stra, bool_array & baRecursive)
   {
      UNREFERENCED_PARAMETER(stra);
      UNREFERENCED_PARAMETER(baRecursive);
   }

   void set::add_filter(stringa & stra)
   {
      UNREFERENCED_PARAMETER(stra);
   }

   ::count set::get_file_count()
   {
      return 0;
   }

   void set::file_at(::index i, string & str)
   {
      UNREFERENCED_PARAMETER(i);
      UNREFERENCED_PARAMETER(str);
   }

   ::index set::find_first_file(const char * lpcsz, ::index iStart)
   {
      UNREFERENCED_PARAMETER(lpcsz);
      UNREFERENCED_PARAMETER(iStart);
      return -1;
   }

   void set::clear_search()
   {
   }

   void set::clear_filter()
   {
   }

   void set::clear_file()
   {
   }

   void set::refresh()
   {
   }

   bool set::get_next_file(const char * lpcszCurrentFilePath, string & strNextFilePath)
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

   string set::get_next_file(const char * pszCurrent)
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


} // namespace file
