#include "framework.h"


namespace file
{


   string_buffer::string_buffer()
   {
      m_psz       = NULL;
      m_iSize     = 0;
      m_iAlloc    = 0;
   }

   string_buffer::string_buffer(sp(base_application) papp) :
      element(papp)
   {
      m_psz       = NULL;
      m_iSize     = 0;
      m_iAlloc    = 0;
   }

   string_buffer::string_buffer(const string & str)
   {
      m_psz       = NULL;
      m_iSize     = 0;
      m_iAlloc    = 0;
      append(str);
   }

   string_buffer::string_buffer(const string_buffer & text)
   {
      m_psz       = NULL;
      m_iSize     = 0;
      m_iAlloc    = 0;
      append(text);
   }

   string_buffer::~string_buffer()
   {
      close();
   }


   ::primitive::memory_size string_buffer::read(void *lpBuf, ::primitive::memory_size nCount)
   {
      primitive::memory_size uiRead = min(nCount, (primitive::memory_size) (m_iSize - m_dwPos));
      memcpy(lpBuf, &m_psz[m_dwPos], uiRead);
      m_dwPos += uiRead;
      return uiRead;
   };

   void string_buffer::write(const void *lpBuf, ::primitive::memory_size nCount)
   {
      append((const char *) lpBuf, nCount);
   }


   ::string string_buffer::str() const
   {

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

} // namespace file


