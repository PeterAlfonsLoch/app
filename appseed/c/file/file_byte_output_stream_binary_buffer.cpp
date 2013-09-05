#include "framework.h"


namespace file
{



   byte_output_stream_binary_buffer::byte_output_stream_binary_buffer(sp(base_application) papp, const char * pszFilePath, uint32_t uiFlags) :
      element(papp)
   {

      m_spbuffer.create(papp);

      m_spbuffer->open(pszFilePath, ((uiFlags & ~type_text) | type_binary) | mode_write);

      if(m_spbuffer && m_spbuffer->IsOpened())
      {

         clear();

      }
      else
      {

         setstate(failbit);

      }

   }


   byte_output_stream_binary_buffer::~byte_output_stream_binary_buffer()
   {

   }


} // namespace file


