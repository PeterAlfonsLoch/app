#include "framework.h"


namespace ca2
{


   xml_data::xml_data(::ca::application * papp, ::xml::parse_info * pparseinfo) :
      ::xml::document(papp, pparseinfo)
   {



   }


   xml_data::~xml_data()
   {



   }
   

   void xml_data::write(gen::byte_output_stream & ostream)
   {

      ostream << (::xml::document &) *this;

   }
   

   void xml_data::read(gen::byte_input_stream & istream)
   {

      istream >> (::xml::document &) *this;

   }


} // namespace ca2



