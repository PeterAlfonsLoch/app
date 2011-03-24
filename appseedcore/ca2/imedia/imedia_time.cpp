#include "StdAfx.h"

namespace imedia
{

   time::time() :
      m_i(0)
   {
   }

   time::time(int i) :
      m_i(i)
   {
   }

   time::time(unsigned int ui) :
      m_i((int) ui)
   {
   }

   time::time(unsigned long ul) :
      m_i((int) ul)
   {
   }

#ifdef _AMD64_
   time::time(LONG_PTR l) :
      m_i((int) l)
   {
   }
#endif


   time::time(double d) :
      m_i((int) d)
   {
   }

   // return milliseconds
   time::operator int()
   {
      return m_i;
   }

   time::operator int() const
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
   }


} // namespace imedia


CLASS_DECL_ca ex1::input_stream &  operator >>(ex1::input_stream & istream, ::imedia::time & t)
{
   return istream >> t.m_i;
}

CLASS_DECL_ca ex1::output_stream &  operator <<(ex1::output_stream & ostream, const ::imedia::time & t)
{
   return ostream << t.m_i;
}
