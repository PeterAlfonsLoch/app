#pragma once


namespace xml
{


   class CLASS_DECL_ca xml :
      public ::radix::object
   {
   public:


      xml(::ca::application * papp);


      string special_chars(const char * psz);


   };


} // namespace ca2


