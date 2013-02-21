#include "framework.h"


namespace gen
{


   plain_text_serializable::plain_text_serializable()
   {

   }

   plain_text_serializable::~plain_text_serializable()
   {

   }

   void plain_text_serializable::write(gen::writer & writer)
   {
      plain_text_output_stream ostream(&writer);
      write(ostream);
   }

   void plain_text_serializable::read(gen::reader & reader)
   {
      plain_text_input_stream istream(&reader);
      read(istream);
   }

}


