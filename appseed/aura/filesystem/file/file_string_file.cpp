//#include "framework.h"


namespace file
{


   string_file::string_file()
   {
      m_pstr      = NULL;
      m_iPos = 0;
   }

   string_file::string_file(::aura::application * papp) :
      object(papp)
   {
      m_pstr = NULL;
      m_iPos = 0;
   }

   string_file::string_file(const string & str)
   {
      m_pstr = NULL;
      m_iPos = 0;
      append(str);
   }

   string_file::string_file(const string_file & text)
   {
      m_pstr       = NULL;
      m_iPos = 0;
      append(::to_string(text));
   }

   string_file::string_file(string * pstr, bool bReferenceOnly)
   {

      m_pstr = pstr;
      m_bOwn = !bReferenceOnly;
      m_iPos = 0;


   }

   string_file::~string_file()
   {
      close();
   }


   memory_size_t string_file::read(void *lpBuf, memory_size_t nCount)
   {
      if(m_iPos >= m_pstr->get_length())
         return 0;
      memory_size_t uiRead = MIN(nCount, (memory_size_t) (m_pstr->get_length() - m_iPos));
      memcpy(lpBuf, &(*m_pstr)[m_iPos], uiRead);
      m_iPos += uiRead;
      return uiRead;
   };

   void string_file::write(const void *lpBuf, memory_size_t nCount)
   {
      append((const char *) lpBuf, nCount);
   }


   ::string string_file::str() const
   {

      if(m_pstr == NULL)
         return "";

      if(m_pstr == NULL)
         return "";

      return *m_pstr;

   }


   void string_file::flush()
   {
   }

   void string_file::close()
   {

      destroy();

   }

   file_position_t string_file::get_position() const
   {

      return m_iPos;

   }


   void string_file::destroy()
   {
      if (m_bOwn)
      {
         delete m_pstr;
      }
      m_pstr = NULL;
      m_iPos = 0;
   }


   //void string_file::alloc(strsize iSize)
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

   //void string_file::alloc_up(strsize iAtLeast)
   //{

   //   if(iAtLeast <= 0)
   //      return;

   //   alloc(m_iSize + iAtLeast);

   //}

   void string_file::set(const char * psz,strsize len)
   {
      
      if(psz == NULL || *psz == '\0' || len <= 0)
      {
         psz = "";
         len = 0;
      }

      if (m_pstr == NULL)
      {

         m_pstr = new string();

         m_bOwn = true;

      }

      m_pstr->assign(psz, len);
   }

   void string_file::append(const char * psz,strsize len)
   {

      if(psz == NULL || *psz == '\0' || len <= 0)
         return;

      if (m_pstr == NULL)
      {

         m_pstr = new string();

         m_bOwn = true;

      }

      m_pstr->append(psz, len);

   }

} // namespace file


