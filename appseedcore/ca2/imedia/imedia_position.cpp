#include "StdAfx.h"

namespace imedia
{
   
   position::position() :
      m_i(0)
   {
   }

   position::position(int i) :
      m_i(i)
   {
   }

   position::position(unsigned int ui) :
      m_i((int) ui)
   {
   }

   position::position(unsigned long ul) :
      m_i((int) ul)
   {
   }

#ifdef _AMD64_
   position::position(LONG_PTR l) :
      m_i((int) l)
   {
   }
#endif

   position::position(double d) :
      m_i((int) d)
   {
   }

   position::operator int()
   {
      return m_i;
   }

   position::operator int() const
   {
      return m_i;
   }

   position & position::operator += (const position & pos)
   {
      m_i += pos.m_i;
      return *this;
   }

   void position::set_to_maximum()
   {
      m_i = numeric_info::get_maximum_value < ::imedia::position >();
   }



} // namespace imedia



CLASS_DECL_ca ex1::input_stream &  operator >>(ex1::input_stream & istream, ::imedia::position & pos)
{
   return istream >> pos.m_i;
}

CLASS_DECL_ca ex1::output_stream &  operator <<(ex1::output_stream & ostream, const ::imedia::position & pos)
{
   return ostream << pos.m_i;
}
