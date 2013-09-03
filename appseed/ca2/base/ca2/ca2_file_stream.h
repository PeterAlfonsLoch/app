#pragma once


namespace ca2
{


   class CLASS_DECL_ca2 output_file_stream :
      virtual public ::ca2::file_composite
   {
   public:


      output_file_stream(sp(base_application) papp, const char * pszFileName, uint32_t dwFlags);
      virtual ~output_file_stream();


   };



} // namespace ca2



