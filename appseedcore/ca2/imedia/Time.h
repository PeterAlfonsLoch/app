#pragma once

namespace imedia
{

   class CLASS_DECL_ca time
   {
   public:
      
      // return milliseconds
      int    m_i;

      
      time();
      time(int i);
      time(unsigned int ui);
      time(unsigned long ul);

#ifdef _AMD64_
      time(LONG_PTR l);
#endif


      time(double d);

      operator int();

      operator int() const;

      time operator - (const time & t2) const;

      time operator + (const time & t2) const;

      static int Compare(const time & t1, const time & t2);

      time & operator += (const time & pos);

   };


} // namespace imedia


CLASS_DECL_ca ex1::input_stream &  operator >>(ex1::input_stream & istream, ::imedia::time & t);
CLASS_DECL_ca ex1::output_stream &  operator <<(ex1::output_stream & ostream, const ::imedia::time & t);


namespace numeric_info
{
#if !core_level_1
   template <>
   inline ::imedia::time get_maximum_value < ::imedia::time > ()
   {
      return (::imedia::time) 0x7fffffff;
   }
   template <>
   inline ::imedia::time get_minimum_value < ::imedia::time > ()
   {
      return (::imedia::time) 0x80000000;
   }
   template <>
   inline ::imedia::time get_null_value < ::imedia::time > ()
   {
      return 0;
   }
   template <>
   inline ::imedia::time get_unitary_value < ::imedia::time >()
   {
      return 1;
   }
#else // core_level_1
   template <::imedia::time>
   inline ::imedia::time get_maximum_value < ::imedia::time > ()
   {
      return (::imedia::time) 0x7fffffff;
   }
   template <::imedia::time>
   inline ::imedia::time get_minimum_value < ::imedia::time > ()
   {
      return (::imedia::time) 0x80000000;
   }
   template <::imedia::time>
   inline ::imedia::time get_null_value < ::imedia::time > ()
   {
      return 0;
   }
   template <::imedia::time>
   inline ::imedia::time get_unitary_value < ::imedia::time >()
   {
      return 1;
   }
#endif
} // namespace numeric_info