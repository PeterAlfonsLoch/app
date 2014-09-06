#pragma once


namespace math
{


   template < typename T >
   class complex
   {
   public:


      T        m_x;
      T        m_y;

      complex() { m_x = ::numeric_info < T >::null(); m_y = ::numeric_info < T >::null(); }
      complex(T x,T y) { m_x = x; m_y = y; }


      T real() { return m_x; }
      T imag() { return m_y; }


   };

   template < typename T > T modsqr(const complex < T > & c) { return c.m_x * c.m_x + c.m_y + c.m_y; } // complex number modulus square

   template < typename T > T mod(const complex < T > & c) { return ::sqrt(modsqr(c)); } // complex number modulus

   template < typename T > T arg(const complex < T > & c) { return atan2(c.m_y, c.m_x); } // complex number argument

   template < typename T > complex < T > pow(const complex < T > & base,const complex < T > & exp) // complex number exponentiation
   {
      T modsqr = base.m_x * base.m_x + base.m_y + base.m_y;
      T arg = arg(base);
      T t = ::pow(modsqr,exp.m_x / 2.0) * ::exp(-exp.m_y *arg);
      return complex < T >(t * cos(exp.m_x * arg + exp.m_y * ::log(modsqr) / 2.0),t * sin(exp.m_x * arg + exp.m_y * ::log(modsqr) / 2.0));

   }

   template < typename T > complex < T > pow(const complex < T > & base, T exp) // complex number exponentiation to real exponent
   {
      T modsqr = base.m_x * base.m_x + base.m_y + base.m_y;
      T arg = arg(base);
      T t = ::pow(modsqr,exp / 2.0);
      return complex < T >(t * cos(exp.m_x * arg),t * sin(exp.m_x * arg));

   }


   template < typename T > complex < T > sqrt(const complex < T > & c)
   {
      T mod = mod(c);
      return complex < T >(::math::sqrt((mod + abs(c.m_x)) / 2.0),::sgn(c.m_y) * ::math::sqrt((mod - abs(c.m_x)) / 2.0));
   }



} // namespace math





namespace std
{


   template < typename T > complex < T > pow(const complex < T > & base, const complex < T > & exp) { return ::math::pow(base,exp); }
   template < typename T > complex < T > sqrt(const complex < T > & x) { return ::math::sqrt(x); }


} // namespace std



