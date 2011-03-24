#pragma once

namespace ex1
{
   class output_stream;
   class input_stream;

   class CLASS_DECL_ca serializable :
      virtual public ::radix::object
   {
   public:
      serializable();
      virtual ~serializable();

      virtual void write(output_stream & ostream) = 0;
      virtual void read(input_stream & istream) = 0;
   };


   template < class type_array >
   class serializable_array :
      virtual public type_array,
      virtual public serializable
   {
   public:
      virtual void write(output_stream & ostream);
      virtual void read(input_stream & istream);
      virtual void on_after_read();
   };

   template < class type_array >
   void serializable_array < type_array >::write(output_stream & ostream)
   {
      count count = get_count();
      ostream << count;
      for(index index = 0; index < count; index++)
      {
         ostream << element_at(index);
      }
   }

   template < class type_array >
   void serializable_array < type_array >::read(input_stream & istream)
   {
      count count;
      istream >> count;
      set_size(count);
      for(index index = 0; index < count; index++)
      {
         istream >> element_at(index);
      }
      on_after_read();
   }

   template < class type_array >
   void serializable_array < type_array >::on_after_read()
   {
   }
}
