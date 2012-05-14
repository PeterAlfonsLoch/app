#include "framework.h"


namespace ca2
{

   
   void xml_data::write(ex1::byte_output_stream & ostream)
   {

      ostream << m_xmldocument;

   }
   

   void xml_data::read(ex1::byte_input_stream & istream)
   {

      istream >> m_xmldocument;

   }


} // namespace ca2