#pragma once


namespace ca
{


   class CLASS_DECL_ca output_file_stream :
      virtual public ::ca::file_composite
   {
   public:


      output_file_stream(sp(::ca::application) papp, const char * pszFileName, uint32_t dwFlags);
      virtual ~output_file_stream();


   };



} // namespace ca



