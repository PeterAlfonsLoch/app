#include "framework.h"



namespace file
{


   file_input_stream::file_input_stream()
   {


   }




   file_input_stream::file_input_stream(stream_buffer * preader)
   {

      m_spbuffer = preader;

   }

   file_input_stream::file_input_stream(const file_input_stream & istream)
   {

      m_spbuffer = istream.m_spbuffer;

   }

   file_input_stream::~file_input_stream()
   {

      close();



   }


} // namespace file









