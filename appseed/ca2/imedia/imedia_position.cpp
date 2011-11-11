#include "StdAfx.h"

namespace imedia
{
   
   position::position() :
      c_number < int64_t >(0)
   {
   }

   position::position(int i) :
      c_number < int64_t >(static_cast < int64_t > (i))
   {
   }

   position::position(unsigned int ui) :
      c_number < int64_t >(static_cast < int64_t > (ui))
   {
   }

   position::position(unsigned long ul) :
      c_number < int64_t >(static_cast < int64_t > (ul))
   {
   }

   position::position(int64_t i) :
      c_number < int64_t >(i)
   {
   }

   position::position(uint64_t ui) :
      c_number < int64_t >(static_cast < int64_t > (ui))
   {
   }

   position::position(double d) :
      c_number < int64_t >((int) d)
   {
   }

   void position::set_to_maximum()
   {
      m_number = numeric_info::get_maximum_value < ::imedia::position >();
   }



} // namespace imedia



CLASS_DECL_ca ex1::byte_input_stream &  operator >>(ex1::byte_input_stream & istream, ::imedia::position & pos)
{
   return istream >> pos.m_number;
}

CLASS_DECL_ca ex1::byte_output_stream &  operator <<(ex1::byte_output_stream & ostream, const ::imedia::position & pos)
{
   return ostream << pos.m_number;
}
