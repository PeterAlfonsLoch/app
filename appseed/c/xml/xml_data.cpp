#include "framework.h"


namespace xml
{


   data::data(sp(base_application) papp, ::xml::parse_info * pparseinfo) :
      ::xml::document(papp, pparseinfo)
   {



   }


   data::~data()
   {



   }
   

   void data::write(::file::byte_output_stream & ostream)
   {

      ostream << (::xml::document &) *this;

   }
   

   void data::read(::file::byte_input_stream & istream)
   {

      istream >> (::xml::document &) *this;

   }


} // namespace ca2



