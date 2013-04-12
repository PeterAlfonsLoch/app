#pragma once


namespace ca
{
   class CLASS_DECL_ca stra :
      public ::ca::object
   {
   public:
      void get_file_lines(stringa & stra, const char * filepath);
   };


} // namespace ca