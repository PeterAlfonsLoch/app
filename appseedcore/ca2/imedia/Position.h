#pragma once

namespace imedia
{

   class CLASS_DECL_ca position
   {
   public:
      void set_to_maximum();
      
      position();
      position(int i);
      position(unsigned int ui);
      position(unsigned long ul);
#ifdef _AMD64_
      position(LONG_PTR l);
#endif
      position(double d);

      int    m_i;

      operator int();
      operator int() const;

      position & operator += (const position & pos);
      
   };


} // namespace imedia

CLASS_DECL_ca ex1::input_stream &  operator >>(ex1::input_stream & istream, ::imedia::position & pos);
CLASS_DECL_ca ex1::output_stream &  operator <<(ex1::output_stream & ostream, const ::imedia::position & pos);


namespace numeric_info
{
#if !core_level_1
   template <>
   inline ::imedia::position get_maximum_value < ::imedia::position > ()
   {
      return (::imedia::position) 0x7fffffff;
   }
   template <>
   inline ::imedia::position get_minimum_value < ::imedia::position > ()
   {
      return (::imedia::position) 0x80000000;
   }
   template <>
   inline ::imedia::position get_null_value < ::imedia::position > ()
   {
      return 0;
   }
   template <>
   inline ::imedia::position get_unitary_value < ::imedia::position >()
   {
      return 1;
   }
#else // core_level_1
   template <::imedia::position>
   inline ::imedia::position get_maximum_value < ::imedia::position > ()
   {
      return (::imedia::position) 0x7fffffff;
   }
   template <::imedia::position>
   inline ::imedia::position get_minimum_value < ::imedia::position > ()
   {
      return (::imedia::position) 0x80000000;
   }
   template <::imedia::position>
   inline ::imedia::position get_null_value < ::imedia::position > ()
   {
      return 0;
   }
   template <::imedia::position>
   inline ::imedia::position get_unitary_value < ::imedia::position >()
   {
      return 1;
   }
#endif

} // namespace numeric_info

