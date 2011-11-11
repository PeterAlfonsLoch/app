#pragma once


#include "ex1_byte_stream.h"


namespace ex1
{


   class byte_input_stream;
   class byte_output_stream;


   class CLASS_DECL_ca byte_serializable :
      virtual public ::radix::object
   {
   public:


      byte_serializable();
      virtual ~byte_serializable();


      virtual void write(byte_output_stream & ostream) = 0;
      virtual void read(byte_input_stream & istream) = 0;


   };


   template < class type_array >
   class byte_serializable_array :
      virtual public type_array,
      virtual public byte_serializable
   {
   public:
      virtual void write(byte_output_stream & ostream);
      virtual void read(byte_input_stream & istream);
      virtual void on_after_read();
   };

   template < class type_array >
   void byte_serializable_array < type_array >::write(byte_output_stream & ostream)
   {
      ::count count = this->get_count();
      ostream << count;
      for(index index = 0; index < count; index++)
      {
         ostream << this->element_at(index);
      }
   }

   template < class type_array >
   void byte_serializable_array < type_array >::read(byte_input_stream & istream)
   {
      ::count count;
      istream >> count;
      this->set_size(count);
      for(index index = 0; index < count; index++)
      {
         istream >> this->element_at(index);
      }
      on_after_read();
   }

   template < class type_array >
   void byte_serializable_array < type_array >::on_after_read()
   {
   }
}
