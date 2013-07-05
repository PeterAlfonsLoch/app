#pragma once


namespace ca2
{


   class CLASS_DECL_ca2 string_buffer
   {
   protected:

      char *      m_psz;

   public:

      strsize     m_iSize;
      strsize     m_iAlloc; // if alloced, should be at least one character (for the terminating null character) greater than m_iSize

      string_buffer()
      {
         m_psz       = NULL;
         m_iSize     = 0;
         m_iAlloc    = 0;
      }

      ~string_buffer()
      {
         destroy();
      }

      strsize get_length()
      {
         return m_iSize;
      }

      strsize get_allocation_size()
      {
         return m_iAlloc;
      }

      void destroy()
      {
         if(m_psz != NULL)
         {
            ca2_free(m_psz);
            m_iAlloc = 0;
            m_iSize = 0;
            m_psz = NULL;
         }
      }

      void alloc(strsize iSize)
      {
         
         if(iSize < 0)
            return;

         if(iSize + 1 > m_iAlloc)
         {
//            strsize oldAlloc = m_iAlloc;
            m_iAlloc = iSize + 1024;
            if(m_psz == NULL)
            {
               m_psz = (char *) ca2_alloc(m_iAlloc);
            }
            else
            {
               if(m_iAlloc > 1024 * 1024)
               {
                  ::OutputDebugString("strange string buffer usage");
               }
               m_psz = (char *) ca2_realloc(m_psz, m_iAlloc);
            }
         }


      }

      void alloc_up(strsize iAtLeast)
      {

         if(iAtLeast <= 0)
            return;

         alloc(m_iSize + iAtLeast);

      }

      void set(const char * psz, strsize len)
      {
         if(psz == NULL || *psz == '\0'|| len <= 0)
         {
            psz = "";
            len = 0;
         }
         alloc(len);
         memcpy(m_psz, psz, len);
         m_iSize = len;
      }

      void set(const string & str)
      {
         set(str, str.length());
      }


      void append(const char * psz, strsize len)
      {
         if(psz == NULL || *psz == '\0'|| len <= 0)
            return;
         alloc_up(len);
         memcpy(&m_psz[m_iSize], psz, len);
         m_iSize += len;
      }

      void append(const string & str)
      {
         append(str, str.length());
      }


      void append(const char * psz)
      {
         append(psz, strlen(psz));
      }

      operator const char *() const
      {
         if(m_psz == NULL)
            return NULL;
         m_psz[m_iSize] = '\0';
         return m_psz;
      }


      string_buffer & operator += (const string & str)
      {
         append(str);
         return *this;
      }

      string_buffer & operator = (const string & str)
      {
         set(str);
         return *this;
      }

   };


} // namespace ca2




