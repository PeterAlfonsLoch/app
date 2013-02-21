#include "framework.h"


namespace ex1
{

   str_stream_base_impl::str_stream_base_impl()
   {
      m_pstr = NULL;
      m_dwPos = 0;
   }

   str_stream_base_impl::~str_stream_base_impl()
   {
   }


   ::primitive::memory_size str_reader::read(void *lpBuf, ::primitive::memory_size nCount)
   {
      primitive::memory_size uiRead = min(nCount, (primitive::memory_size) (m_pstr->get_length() - m_dwPos));
      memcpy(lpBuf, &((const char *) *m_pstr)[m_dwPos], uiRead);
      m_dwPos += uiRead;
      return uiRead;
   };

   void str_writer::write(const void *lpBuf, ::primitive::memory_size nCount)
   {
      string str((const char *) lpBuf, nCount);
      *m_pstr += str;
   }


} // namespace ex1


