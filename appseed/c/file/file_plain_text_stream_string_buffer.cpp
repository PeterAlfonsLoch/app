#include "framework.h"


namespace file
{



   plain_text_stream_string_buffer::plain_text_stream_string_buffer(sp(base_application) papp)
   {

      m_spstringbuffer.create(papp.is_set() ? papp : ::ca2::get_thread_app());

      if(m_spstringbuffer.is_set())
      {

         clear();

         m_spbuffer = m_spstringbuffer;

      }
      else
      {

         setstate(failbit);

      }

   }

   plain_text_stream_string_buffer::~plain_text_stream_string_buffer()
   {

   }


   string plain_text_stream_string_buffer::str() const
   {

      return m_spstringbuffer->str();

   }

   plain_text_stream_string_buffer::operator const char *() const
   {

      return m_spstringbuffer->operator const char *();

   }

} // namespace file


