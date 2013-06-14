#pragma once


namespace http
{


   class CLASS_DECL_ca2 memory_file : 
      virtual public ::http::file,
      virtual public ::primitive::memory_file
   {
   public:


      memory_file(sp(::ca2::application) papp);


      void to_string(string & str);


   };


} // namespace http


