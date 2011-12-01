#pragma once

namespace ca2
{

   class CLASS_DECL_ca application_file :
      public ::radix::object
   {
   public:
      application_file();


      string as_string(var varFile);
      void as_memory(var varFile, primitive::memory & mem);
      void lines(stringa & stra, var varFile);


   };

} // namespace ca2