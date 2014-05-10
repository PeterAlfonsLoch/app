#include "framework.h"


namespace file
{



   byte_output_stream_binary_buffer::byte_output_stream_binary_buffer(sp(::base::application) papp, const char * pszFilePath, uint32_t uiFlags) :
      element(papp)
   {

      m_spbinarybuffer.create(papp);

      m_spbinarybuffer->open(pszFilePath, ((uiFlags & ~type_text) | type_binary) | mode_write);

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


   byte_output_stream_binary_buffer::~byte_output_stream_binary_buffer()
   {

   }


} // namespace file


