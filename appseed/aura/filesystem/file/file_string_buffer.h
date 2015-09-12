#pragma once


#include "file_plain_text_stream_base.h"
#include "file_plain_text_istream.h"
#include "file_plain_text_ostream.h"
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
      string_buffer(::aura::application * papp);
      string_buffer(const string & str);
      string_buffer(const string_buffer & str);
      virtual ~string_buffer();


      using ::file::reader::read;
      virtual ::primitive::memory_size read(void *lpBuf, ::primitive::memory_size nCount);
      void read(istream & istream);


      using ::file::writer::write;
      virtual void write(const void *lpBuf, ::primitive::memory_size nCount);
      void write(ostream & ostream);

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

      void destroy();
      void alloc(strsize iSize);

      void alloc_up(strsize iAtLeast);

      void set(const char * psz,strsize len);

      void set(const string & str)
      {
         set(str, str.length());
      }


      void append(const char * psz,strsize len);

      void append(const string & str)
      {
         append(str, str.length());
      }



      operator const char *() const
      {
         return m_psz;
      }

      string & to_string(string &str) const
      {

         str.assign(m_psz, m_iSize);

         return str;

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





#include "file_plain_text_ostream_string_buffer.h"
#include "file_plain_text_stream_string_buffer.h"




