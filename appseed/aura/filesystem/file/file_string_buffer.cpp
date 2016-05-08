//#include "framework.h"


namespace file
{


   string_buffer::string_buffer()
   {
      m_pstr      = NULL;
      m_iPos = 0;
   }

   string_buffer::string_buffer(::aura::application * papp) :
      object(papp)
   {
      m_pstr = NULL;
      m_iPos = 0;
   }

   string_buffer::string_buffer(const string & str)
   {
      m_pstr = NULL;
      m_iPos = 0;
      append(str);
   }

   string_buffer::string_buffer(const string_buffer & text)
   {
      m_pstr       = NULL;
      m_iPos = 0;
      append(::to_string(text));
   }

   string_buffer::string_buffer(string * pstr, bool bReferenceOnly)
   {

      m_pstr = pstr;
      m_bOwn = !bReferenceOnly;
      m_iPos = 0;


   }

   string_buffer::~string_buffer()
   {
      close();
   }


   memory_size_t string_buffer::read(void *lpBuf, memory_size_t nCount)
   {
      if(m_iPos >= m_pstr->get_length())
         return 0;
      memory_size_t uiRead = MIN(nCount, (memory_size_t) (m_pstr->get_length() - m_iPos));
      memcpy(lpBuf, &(*m_pstr)[m_iPos], uiRead);
      m_iPos += uiRead;
      return uiRead;
   };

   void string_buffer::write(const void *lpBuf, memory_size_t nCount)
   {
      append((const char *) lpBuf, nCount);
   }


   ::string string_buffer::str() const
   {

      if(m_pstr == NULL)
         return "";

      if(m_pstr == NULL)
         return "";

      return *m_pstr;

   }


   void string_buffer::flush()
   {
   }

   void string_buffer::close()
   {

      destroy();

   }

   file_position_t string_buffer::get_position() const
   {

      return m_iPos;

   }


   void string_buffer::destroy()
   {
      if (m_bOwn)
      {
         delete m_pstr;
      }
      m_pstr = NULL;
      m_iPos = 0;
   }


   //void string_buffer::alloc(strsize iSize)
   //{

   //   if(iSize < 0)
   //      return;

   //   if(iSize + 1 > m_iAlloc)
   //   {
   //                  strsize oldAlloc = m_iAlloc;
   //      m_iAlloc = iSize + 1024;
   //      if(m_psz == NULL)
   //      {
   //         m_psz = (char *)memory_alloc(m_iAlloc);
   //         m_psz[0] = '\0';
   //      }
   //      else
   //      {
   //         if(m_iAlloc > 1024 * 1024)
   //         {
   //            ::output_debug_string("strange string buffer usage");
   //         }
   //         m_psz = (char *)memory_realloc(m_psz,m_iAlloc);
   //      }
   //   }


   //}

   //void string_buffer::alloc_up(strsize iAtLeast)
   //{

   //   if(iAtLeast <= 0)
   //      return;

   //   alloc(m_iSize + iAtLeast);

   //}

   void string_buffer::set(const char * psz,strsize len)
   {
      if(psz == NULL || *psz == '\0' || len <= 0)
      {
         psz = "";
         len = 0;
      }
      throw todo(get_app());
      //alloc(len);
      //memcpy(m_psz,psz,len);
      //m_iSize = len;
      //m_psz[m_iSize] = '\0';
   }

   void string_buffer::append(const char * psz,strsize len)
   {
      if(psz == NULL || *psz == '\0' || len <= 0)
         return;
      throw todo(get_app());
      //alloc_up(len);
      //memcpy(&m_psz[m_iSize],psz,len);
      //m_iSize += len;
      //m_psz[m_iSize] = '\0'; // for security/safety the buffer is left with a terminating null, even
                             // it if haven't finished appending
   }

} // namespace file


