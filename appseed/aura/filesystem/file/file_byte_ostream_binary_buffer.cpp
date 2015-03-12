//#include "framework.h"


namespace file
{



   byte_ostream_binary_buffer::byte_ostream_binary_buffer(::aura::application * papp, const char * pszFilePath, uint32_t uiFlags) :
      object(papp)
   {

      m_spbinarybuffer.alloc(allocer());

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


   byte_ostream_binary_buffer::~byte_ostream_binary_buffer()
   {

   }


} // namespace file


