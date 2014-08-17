#include "framework.h"


namespace xml
{


   data::data(sp(::base::application) papp, ::xml::parse_info * pparseinfo) :
      ::xml::document(papp, pparseinfo)
   {



   }


   data::~data()
   {



   }
   

   void data::write(::file::output_stream & ostream)
   {

      ostream << (::xml::document &) *this;

   }
   

   void data::read(::file::input_stream & istream)
   {

      istream >> (::xml::document &) *this;

   }


} // namespace core



