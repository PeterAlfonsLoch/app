#include "framework.h"


namespace file
{



   byte_input_stream_binary_buffer::byte_input_stream_binary_buffer(sp(::axis::application) papp, const char * pszFilePath, uint32_t uiFlags) :
      element(papp)
   {

      m_spbinarybuffer.alloc(allocer());

      m_spbinarybuffer->open(pszFilePath, (((uiFlags & ~type_text) | type_binary) | mode_read) & ~(defer_create_directory | mode_create | mode_no_truncate));

      if(m_spbinarybuffer.is_set() && m_spbinarybuffer->IsOpened())
      {

         clear();

         m_spbuffer = m_spbinarybuffer;

      }
      else
      {

         m_spbinarybuffer.release();

         setstate(failbit);

      }

   }

   byte_input_stream_binary_buffer::~byte_input_stream_binary_buffer()
   {

   }


} // namespace file


