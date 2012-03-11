#pragma once



namespace ca2
{


   class CLASS_DECL_ca xml_data :
      
      public ::xml::document
   {
   public:


      ::xml::document      m_xmldocument;


      virtual void write(ex1::byte_output_stream & ostream);
      virtual void read(ex1::byte_input_stream & istream);


   };


};


