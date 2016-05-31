//#include "framework.h"


namespace file
{



   byte_istream_binary_buffer::byte_istream_binary_buffer(::ace::application * papp, const char * pszFilePath, uint32_t uiFlags) :
      object(papp)
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

   byte_istream_binary_buffer::~byte_istream_binary_buffer()
   {

   }


} // namespace file


