#include "framework.h"



namespace file
{


   file_input_stream::file_input_stream()
   {

      m_gcount = 0;

   }




   file_input_stream::file_input_stream(stream_buffer * preader)
   {

      m_spbuffer = preader;
      m_gcount = 0;

   }

   file_input_stream::file_input_stream(const input_stream & istream)
   {

      m_spbuffer = istream.m_spbuffer;
      m_gcount = 0;

   }

   file_input_stream::~file_input_stream()
   {

      close();



   }


} // namespace file









