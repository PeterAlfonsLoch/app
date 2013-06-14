#pragma once


namespace ca2
{


   class plain_text_output_stream;
   class plain_text_input_stream;


   class CLASS_DECL_ca2 plain_text_serializable :
      virtual public ::ca2::object
   {
   public:


      plain_text_serializable();
      virtual ~plain_text_serializable();


      virtual void write(plain_text_output_stream & ostream) = 0;
      virtual void read(plain_text_input_stream & istream) = 0;

      virtual void write(::ca2::writer & writer);
      virtual void read(::ca2::reader & reader);

   };


   template < class type_array >
   class plain_text_serializable_array :
      virtual public type_array,
      virtual public plain_text_serializable
   {
   public:
      virtual void write(plain_text_output_stream & ostream);
      virtual void read(plain_text_input_stream & istream);
      virtual void on_after_read();
   };

   template < class type_array >
   void plain_text_serializable_array < type_array >::on_after_read()
   {
   }


} // namespace ca2



