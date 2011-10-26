#include "StdAfx.h"


namespace http
{


   memory_file::memory_file(::ca::application * papp) :
      ca(papp),
      ::gen::memory_file(papp),
      primitive::memory_container(papp)
   {
   }
      
   void memory_file::to_string(string & str)
   {
      ::gen::memory_file::to_string(str);
   }


} // namespace http


