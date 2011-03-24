#pragma once


namespace ca2
{
   class CLASS_DECL_ca stra :
      public ::radix::object
   {
   public:
      void get_file_lines(stringa & stra, const char * filepath);
   };


} // namespace ca2