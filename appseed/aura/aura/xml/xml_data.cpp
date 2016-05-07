//#include "framework.h"


namespace xml
{


   data::data(::aura::application * papp, ::xml::parse_info * pparseinfo) :
      ::object(papp),
      ::xml::node(papp),
      ::data::data(papp),
      ::xml::document(papp, pparseinfo)
   {



   }


   data::~data()
   {



   }
   

   void data::write(::file::ostream & ostream) const
   {

      ostream << (::xml::document &) *this;

   }
   

   void data::read(::file::istream & istream)
   {

      istream >> (::xml::document &) *this;

   }


} // namespace core



