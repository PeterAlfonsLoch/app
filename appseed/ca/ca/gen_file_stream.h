#pragma once


namespace gen
{


   class CLASS_DECL_ca output_file_stream :
      virtual public ::gen::file_composite
   {
   public:


      output_file_stream(::ca::application * papp, const char * pszFileName, uint32_t dwFlags);
      virtual ~output_file_stream();


   };



} // namespace gen



