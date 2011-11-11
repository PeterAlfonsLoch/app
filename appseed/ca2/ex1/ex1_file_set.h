#pragma once

namespace ex1
{

   class CLASS_DECL_ca file_set 
   {
   public:
      file_set();
      virtual ~file_set();

      virtual bool AddSearch(stringa & wstraBase, bool_array & baRecursive, stringa & wstraFilter);
      virtual int GetFileCount();
      virtual void FileAt(int i, string & str);
      virtual int FindFirstFile(LPCSTR lpcszFilePath);
      virtual void RemoveAllFiles();

   };

   typedef ca::smart_pointer < file_set > file_set_sp;

} // namespace ex1