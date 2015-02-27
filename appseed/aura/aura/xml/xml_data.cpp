//#include "framework.h"


namespace xml
{


   data::data(::aura::application * papp, ::xml::parse_info * pparseinfo) :
      ::object(papp),
      ::data::data(papp)
//      ::xml::document(papp) //, ppareserinfo)
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



