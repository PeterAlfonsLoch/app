#pragma once

namespace ca2
{

   class CLASS_DECL_ca html :
      public ::radix::object
   {
   public:
      string special_chars(const char * psz);
      string entities(const char * psz);
   };

} // namespace ca2