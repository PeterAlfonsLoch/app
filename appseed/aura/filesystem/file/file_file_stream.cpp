#include "framework.h"


namespace file
{


   file_stream::file_stream()
   {

   }


   file_stream::file_stream(const char * lpszFileName,uint32_t nOpenFlags,sp(::aura::application) papp)
   {

      open(lpszFileName,nOpenFlags,papp);

   }


   file_stream::file_stream(stream_buffer * pbuffer)
   {
      
      m_spbuffer = pbuffer;

   }


   file_stream::file_stream(const file_stream & stream):
      file_input_stream(stream),
      file_output_stream(stream)
   {

   }


   file_stream::~file_stream()
   {

   }


} // namespace file








