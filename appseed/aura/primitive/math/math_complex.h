#pragma once


namespace math
{


   template < typename T >
   class complex
   {
   public:


      T        m_x;
      T        m_y;


      T real() { return m_x; }
      T imag() { return m_y; }


   };


} // namespace math





