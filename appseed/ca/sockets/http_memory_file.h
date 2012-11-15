#pragma once


namespace http
{


   class CLASS_DECL_ca memory_file : 
      virtual public ::http::file,
      virtual public ::gen::memory_file
   {
   public:


      memory_file(::ca::application * papp);


      void to_string(string & str);


   };


} // namespace http


