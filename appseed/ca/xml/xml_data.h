#pragma once



namespace ca
{


   class CLASS_DECL_ca xml_data :
      public ::xml::document
   {
   public:


      xml_data(::ca::application * papp, ::xml::parse_info * pparseinfo = ::null());
      virtual ~xml_data();


      virtual void write(::ca::byte_output_stream & ostream);
      virtual void read(::ca::byte_input_stream & istream);


   };


} // namespace ca


