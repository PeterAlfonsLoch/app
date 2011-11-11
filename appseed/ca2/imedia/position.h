#pragma once

namespace imedia
{

   class CLASS_DECL_ca position :
      public c_number < int64_t >
   {
   public:

      position();
      position(int i);
      position(unsigned int ui);
      position(unsigned long ul);
      position(int64_t i);
      position(uint64_t ui);
      position(double d);


      void set_to_maximum();
      
      
      
   };


} // namespace imedia

CLASS_DECL_ca ex1::byte_input_stream &  operator >>(ex1::byte_input_stream & istream, ::imedia::position & pos);
CLASS_DECL_ca ex1::byte_output_stream &  operator <<(ex1::byte_output_stream & ostream, const ::imedia::position & pos);


namespace numeric_info
{

   template <> inline ::imedia::position get_maximum_value < ::imedia::position > ()
   {
      return (::imedia::position) 0x7fffffffffffffff;
   }
   template <> inline ::imedia::position get_minimum_value < ::imedia::position > ()
   {
      return (::imedia::position) 0x8000000000000000;
   }
   template <> inline ::imedia::position get_null_value < ::imedia::position > ()
   {
      return 0;
   }
   template <> inline ::imedia::position get_unitary_value < ::imedia::position >()
   {
      return 1;
   }

} // namespace numeric_info

