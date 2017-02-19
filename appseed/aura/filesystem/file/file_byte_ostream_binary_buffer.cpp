//#include "framework.h"


namespace file
{



   byte_ostream_binary_buffer::byte_ostream_binary_buffer(::aura::application * papp, const char * pszFilePath, uint32_t uiFlags) :
      object(papp)
   {

      m_spfile.alloc(allocer());

      m_spfile->open(pszFilePath, ((uiFlags & ~type_text) | type_binary) | mode_write);

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


   byte_ostream_binary_buffer::~byte_ostream_binary_buffer()
   {

   }


} // namespace file


