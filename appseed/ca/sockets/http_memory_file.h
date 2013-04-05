#pragma once


namespace http
{


   class CLASS_DECL_ca memory_file : 
      virtual public ::http::file,
      virtual public ::primitive::memory_file
   {
   public:


      memory_file(::ca::applicationsp papp);


      void to_string(string & str);


   };


} // namespace http


