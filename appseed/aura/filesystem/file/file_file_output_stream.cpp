#include "framework.h"



namespace file
{


   file_output_stream::file_output_stream()
   {

   }




   file_output_stream::file_output_stream(stream_buffer * preader)
   {

      m_spbuffer = preader;

   }

   file_output_stream::file_output_stream(const input_stream & istream)
   {

      m_spbuffer = istream.m_spbuffer;

   }

   file_output_stream::~file_output_stream()
   {

      close();



   }


} // namespace file









