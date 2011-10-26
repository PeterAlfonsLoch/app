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
         string as_string(var varFile, var varQuery);
         void as_memory(var varFile, primitive::memory & mem);
         void lines(stringa & stra, var varFile);

         bool put_contents(var varFile, const void * pvoidContents, count count);
         bool put_contents(var varFile, const char * lpcszContents);
         bool put_contents(var varFile, ex1::file & file);
         bool put_contents(var varFile, primitive::memory & mem);
         bool put_contents_utf8(var varFile, const char * lpcszContents);

         virtual bool exists(const char * pszPath);


      };

   } // namespace file


} // namespace ca2

