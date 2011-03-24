#pragma once

namespace http
{

   class CLASS_DECL_ca memory_file : 
      virtual public ::http::file,
      virtual public gen_memory_file
   {
   public:
      memory_file(::ca::application * papp) :
         ca(papp),
         gen_memory_file(papp),
         primitive_memory_container(papp)
      {
      };
      inline void to_string(string & str)
      {
         gen_memory_file::to_string(str);
      }
   };

} // namespace http