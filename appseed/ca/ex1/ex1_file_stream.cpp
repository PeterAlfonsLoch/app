#include "framework.h"


namespace ex1
{

   output_file_stream::output_file_stream(::ca::application * papp, const char * pszFileName, DWORD dwFlags, ::ex1::file_exception_sp * perror)
   {

      m_spfile = App(papp).get_file(pszFileName, dwFlags, perror);

   }
      
   output_file_stream::~output_file_stream()
   {
   }



} // namespace ex1


