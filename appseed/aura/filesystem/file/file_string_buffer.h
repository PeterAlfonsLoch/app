#pragma once


#include "file_plain_text_stream_base.h"
#include "file_plain_text_input_stream.h"
#include "file_plain_text_output_stream.h"
#include "file_plain_text_stream.h"



namespace file
{


   class string_buffer;


   typedef sp(string_buffer) string_buffer_sp;


   class CLASS_DECL_AURA string_buffer :
      virtual public ::file::stream_buffer
   {
   public:

      char *      m_psz;

   public:

      strsize     m_iSize;
      strsize     m_iAlloc; // if alloced, should be at least one character (for the terminating null character) greater than m_iSize
      strsize     m_iPos;


      string_buffer();
      string_buffer(sp(::aura::application) papp);
      string_buffer(const string & str);
      string_buffer(const string_buffer & str);
      virtual ~string_buffer();


      using ::file::reader::read;
      virtual ::primitive::memory_size read(void *lpBuf, ::primitive::memory_size nCount);
      void read(input_stream & istream);


      using ::file::writer::write;
      virtual void write(const void *lpBuf, ::primitive::memory_size nCount);
      void write(output_stream & ostream);

      ::string str() const;

      virtual void flush();

      virtual void close();






      file_size get_length() const
      {
         return m_iSize;
      }

      strsize get_allocation_size() const
      {
         return m_iAlloc;
      }


      virtual file_position get_position() const;

      void destroy()
      {
         if(m_psz != NULL)
         {
            memory_free(m_psz);
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
               m_psz = (char *) memory_alloc(m_iAlloc);
            }
            else
            {
               if(m_iAlloc > 1024 * 1024)
               {
                  //::output_debug_string("strange string buffer usage");
               }
               m_psz = (char *) memory_realloc(m_psz, m_iAlloc);
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




} // namespace file





#include "file_plain_text_output_stream_string_buffer.h"
#include "file_plain_text_stream_string_buffer.h"




