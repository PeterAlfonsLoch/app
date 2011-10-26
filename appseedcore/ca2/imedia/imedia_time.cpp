#include "StdAfx.h"


namespace imedia
{


   time::time() :
      c_number < int64_t >(0)
   {
   }

   time::time(int i) :
      c_number < int64_t >(static_cast < int64_t > (i))
   {
   }

   time::time(unsigned int ui) :
      c_number < int64_t >(static_cast < int64_t > (ui))
   {
   }

   time::time(unsigned long ul) :
      c_number < int64_t >(static_cast < int64_t > (ul))
   {
   }

   time::time(int64_t i) :
      c_number < int64_t >(i)
   {
   }

   time::time(uint64_t ui) :
      c_number < int64_t >(static_cast < int64_t > (ui))
   {
   }

   time::time(double d) :
      c_number < int64_t >((int) d)
   {
   }

   // return milliseconds
   /*time::operator int64_t()
   {
      return m_i;
   }

   time::operator int64_t() const
   {
      return m_i;
   }

   time & time::operator += (const time & time)
   {
      m_i += time.m_i;
      return *this;
   }


   time time::operator - (const time & t2) const
   {
      return time(m_i - t2.m_i);
   }

   time time::operator + (const time & t2) const
   {
      return time(m_i + t2.m_i);
   }

   int time::Compare(const time & t1, const time & t2)
   {
      return (int)(t2 - t1);
   }*/


} // namespace imedia


CLASS_DECL_ca ex1::byte_input_stream &  operator >>(ex1::byte_input_stream & istream, ::imedia::time & t)
{
   return istream >> t.m_number;
}

CLASS_DECL_ca ex1::byte_output_stream &  operator <<(ex1::byte_output_stream & ostream, const ::imedia::time & t)
{
   return ostream << t.m_number;
}
