#pragma once


namespace ca2
{


   namespace file
   {


      class CLASS_DECL_ca application :
         public ::radix::object
      {
      public:


         application();


         string as_string(var varFile);
         void as_memory(var varFile, primitive::memory & mem);
         void lines(stringa & stra, var varFile);


      };

   } // namespace file


} // namespace ca2

