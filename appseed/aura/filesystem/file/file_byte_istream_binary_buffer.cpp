//#include "framework.h"


namespace file
{



   byte_istream_binary_buffer::byte_istream_binary_buffer(::aura::application * papp, const char * pszFilePath, uint32_t uiFlags) :
      object(papp)
   {

      m_spfile.alloc(allocer());

      m_spfile->open(pszFilePath, (((uiFlags & ~type_text) | type_binary) | mode_read) & ~(defer_create_directory | mode_create | mode_no_truncate));

      if(m_spfile.is_set() && m_spfile->IsOpened())
      {

         clear();

      }
      else
      {

         m_spfile.release();

         setstate(failbit);

      }

   }

   byte_istream_binary_buffer::~byte_istream_binary_buffer()
   {

   }


} // namespace file


