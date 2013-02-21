#include "framework.h"


namespace ex1
{


   plain_text_serializable::plain_text_serializable()
   {

   }

   plain_text_serializable::~plain_text_serializable()
   {

   }

   void plain_text_serializable::write(ex1::writer & writer)
   {
      plain_text_output_stream ostream(&writer);
      write(ostream);
   }

   void plain_text_serializable::read(ex1::reader & reader)
   {
      plain_text_input_stream istream(&reader);
      read(istream);
   }

}


