#include "framework.h"


namespace file
{


   plain_text_serializable::plain_text_serializable()
   {

   }

   plain_text_serializable::~plain_text_serializable()
   {

   }

   void plain_text_serializable::write(::file::writer & writer)
   {
      plain_text_output_stream ostream(&writer);
      write(ostream);
   }

   void plain_text_serializable::read(::file::reader & reader)
   {
      plain_text_input_stream istream(&reader);
      read(istream);
   }

}


