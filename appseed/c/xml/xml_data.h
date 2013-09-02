#pragma once



namespace xml
{


   class CLASS_DECL_c data :
      public ::xml::document
   {
   public:


      data(sp(::application) papp, ::xml::parse_info * pparseinfo = NULL);
      virtual ~data();


      virtual void write(::file::byte_output_stream & ostream);
      virtual void read(::file::byte_input_stream & istream);


   };


} // namespace xml





