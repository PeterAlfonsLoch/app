#pragma once


namespace ex1
{


   class CLASS_DECL_ca output_file_stream :
      virtual public ::ex1::file_composite
   {
   public:


      output_file_stream(::ca::application * papp, const char * pszFileName, DWORD dwFlags);
      virtual ~output_file_stream();


   };



} // namespace ex1



