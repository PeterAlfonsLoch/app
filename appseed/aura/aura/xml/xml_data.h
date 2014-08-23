#pragma once



namespace xml
{


   class CLASS_DECL_AXIS data :
      public ::xml::document
   {
   public:


      data(sp(::axis::application) papp, ::xml::parse_info * pparseinfo = NULL);
      virtual ~data();


      virtual void write(::file::output_stream & ostream);
      virtual void read(::file::input_stream & istream);


   };


} // namespace xml





