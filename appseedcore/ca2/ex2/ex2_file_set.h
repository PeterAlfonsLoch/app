#pragma once

namespace ex2
{

   class CLASS_DECL_ca file_set :
      virtual public ::radix::object
   {
   public:
      file_set();
      virtual ~file_set();

   // composite
      virtual void add_search(stringa & stra, bool_array & baRecursive);
      virtual void add_filter(stringa & stra);
      virtual int get_file_count();
      virtual void file_at(int i, string & str);
      virtual int find_first_file(const char * lpcszFilePath);
      virtual void clear_file();
      virtual void clear_search();
      virtual void clear_filter();
      virtual void refresh();

   // derived
      virtual bool get_next_file(const char * lpcszCurrentFilePath, string & wstrNextFilePath);
      virtual string get_next_file(const char * psz);

   };

   typedef ca::smart_pointer < file_set > file_set_sp;

} // namespace ex1
