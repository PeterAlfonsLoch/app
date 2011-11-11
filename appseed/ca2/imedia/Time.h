#pragma once

namespace imedia
{

   class CLASS_DECL_ca time : 
      public c_number < int64_t >
   {
   public:
      
      // return milliseconds
      //int64_t    m_i;

      
      time();
      time(int i);
      time(unsigned int ui);
      time(unsigned long ul);
      time(int64_t i);
      time(uint64_t ui);
      time(double d);

/*      operator int64_t();
      operator int64_t() const;

      time operator - (const time & t2) const;

      time operator + (const time & t2) const;

      static int Compare(const time & t1, const time & t2);

      time & operator += (const time & pos);*/

   };


} // namespace imedia


CLASS_DECL_ca ex1::byte_input_stream &  operator >>(ex1::byte_input_stream & istream, ::imedia::time & t);
CLASS_DECL_ca ex1::byte_output_stream &  operator <<(ex1::byte_output_stream & ostream, const ::imedia::time & t);


namespace numeric_info
{

   template <> inline ::imedia::time get_maximum_value < ::imedia::time > ()
   {
      return (::imedia::time) 0x7fffffffffffffff;
   }
   template <> inline ::imedia::time get_minimum_value < ::imedia::time > ()
   {
      return (::imedia::time) 0x8000000000000000;
   }
   template <> inline ::imedia::time get_null_value < ::imedia::time > ()
   {
      return 0;
   }
   template <> inline ::imedia::time get_unitary_value < ::imedia::time >()
   {
      return 1;
   }

} // namespace numeric_info