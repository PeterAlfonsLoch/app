#pragma once



namespace ca2
{


   class CLASS_DECL_ca2 xml_data :
      public ::xml::document
   {
   public:


      xml_data(sp(::application) papp, ::xml::parse_info * pparseinfo = NULL);
      virtual ~xml_data();


      virtual void write(::file::byte_output_stream & ostream);
      virtual void read(::file::byte_input_stream & istream);


   };


} // namespace ca2


