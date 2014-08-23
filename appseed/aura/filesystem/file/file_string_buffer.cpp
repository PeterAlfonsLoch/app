#include "framework.h"


namespace file
{


   string_buffer::string_buffer()
   {
      m_psz       = NULL;
      m_iSize     = 0;
      m_iAlloc    = 0;
      m_iPos     = 0;
   }

   string_buffer::string_buffer(sp(::axis::application) papp) :
      element(papp)
   {
      m_psz       = NULL;
      m_iSize     = 0;
      m_iAlloc    = 0;
      m_iPos     = 0;
   }

   string_buffer::string_buffer(const string & str)
   {
      m_psz       = NULL;
      m_iSize     = 0;
      m_iAlloc    = 0;
      m_iPos     = 0;
      append(str);
   }

   string_buffer::string_buffer(const string_buffer & text)
   {
      m_psz       = NULL;
      m_iSize     = 0;
      m_iPos     = 0;
      m_iAlloc    = 0;
      append(text);
   }

   string_buffer::~string_buffer()
   {
      close();
   }


   ::primitive::memory_size string_buffer::read(void *lpBuf, ::primitive::memory_size nCount)
   {
      if(m_iPos >= m_iSize)
         return 0;
      primitive::memory_size uiRead = MIN(nCount, (primitive::memory_size) (m_iSize - m_iPos));
      memcpy(lpBuf, &m_psz[m_iPos], uiRead);
      m_iPos += uiRead;
      return uiRead;
   };

   void string_buffer::write(const void *lpBuf, ::primitive::memory_size nCount)
   {
      append((const char *) lpBuf, nCount);
   }


   ::string string_buffer::str() const
   {

      if(m_psz == NULL)
         return "";

      if(m_psz == NULL)
         return "";

      m_psz[m_iSize] = '\0';

      return string(m_psz, m_iSize);

   }


   void string_buffer::flush()
   {
   }

   void string_buffer::close()
   {

      destroy();

   }

   file_position string_buffer::get_position() const
   {

      return m_iPos;

   }

} // namespace file


