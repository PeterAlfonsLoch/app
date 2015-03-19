//#include "framework.h"


namespace file
{



   plain_text_ostream_string_buffer::plain_text_ostream_string_buffer(::aura::application * papp) :
      object(papp != NULL ? papp : get_thread_app())
   {

      m_spstringbuffer.alloc(allocer());

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

   plain_text_ostream_string_buffer::~plain_text_ostream_string_buffer()
   {

   }


   string plain_text_ostream_string_buffer::str() const
   {

      return m_spstringbuffer->str();

   }

   plain_text_ostream_string_buffer::operator const char *() const
   {

      return m_spstringbuffer->operator const char *();

   }

} // namespace file

