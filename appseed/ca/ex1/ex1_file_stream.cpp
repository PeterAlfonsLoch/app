#include "framework.h"


namespace ex1
{


   output_file_stream::output_file_stream(::ca::application * papp, const char * pszFileName, DWORD dwFlags)
   {

      m_spfile = App(papp).get_file(pszFileName, dwFlags);

   }
      
   output_file_stream::~output_file_stream()
   {
   }



} // namespace ex1


