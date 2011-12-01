#include "StdAfx.h"

namespace ex1
{

   file_set::file_set()
   {
   }

   file_set::~file_set()
   {
   }

   bool file_set::AddSearch(stringa & stra, bool_array & baRecursive, stringa & wstraFilters)
   {
      UNREFERENCED_PARAMETER(stra);
      UNREFERENCED_PARAMETER(wstraFilters);
      UNREFERENCED_PARAMETER(baRecursive);
      return false;
   }

   int file_set::GetFileCount()
   {
      return 0;
   }

   void file_set::FileAt(int i, string & str)
   {
      UNREFERENCED_PARAMETER(i);
      UNREFERENCED_PARAMETER(str);
   }

   int file_set::FindFirstFile(LPCSTR lpcsz)
   {
      UNREFERENCED_PARAMETER(lpcsz);
      return -1;
   }

   void file_set::RemoveAllFiles()
   {
   }

} // namespace ex1