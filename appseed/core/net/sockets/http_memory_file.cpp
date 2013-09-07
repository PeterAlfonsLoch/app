#include "framework.h"


namespace http
{


   memory_buffer::memory_buffer(sp(base_application) papp) :
      element(papp),
      ::file::memory_buffer(papp),
      primitive::memory_container(papp)
   {
   }
      
   void memory_buffer::to_string(string & str)
   {
      ::file::memory_buffer::to_string(str);
   }


} // namespace http


