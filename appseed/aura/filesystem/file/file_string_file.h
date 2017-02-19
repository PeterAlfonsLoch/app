#pragma once


#include "file_plain_text_stream_base.h"
#include "file_plain_text_istream.h"
#include "file_plain_text_ostream.h"
#include "file_plain_text_stream.h"



namespace file
{


   class string_file;


   typedef sp(string_file) string_buffer_sp;


   class CLASS_DECL_AURA string_file :
      virtual public ::file::file
   {
   public:

      string *       m_pstr;
      strsize        m_iPos;
      bool           m_bOwn;

      string_file();
      string_file(string * pstr, bool bReferenceOnly = true);
      string_file(::aura::application * papp);
      string_file(const string & str);
      string_file(const string_file & str);
      virtual ~string_file();


      using ::file::reader::read;
      virtual memory_size_t read(void *lpBuf, memory_size_t nCount);
      void read(istream & istream);


      using ::file::writer::write;
      virtual void write(const void *lpBuf, memory_size_t nCount);
      void write(ostream & ostream);

      ::string str() const;

      virtual void flush();

      virtual void close();






      file_size_t get_length() const
      {
         return m_pstr->get_length();
      }


      virtual file_position_t get_position() const;

      void destroy();
      //void alloc(strsize iSize);

      //void alloc_up(strsize iAtLeast);

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
         return *m_pstr;
      }

      string & to_string(string &str) const
      {

         str = *m_pstr;

         return str;

      }

      string_file & operator += (const string & str)
      {
         append(str);
         return *this;
      }

      string_file & operator = (const string & str)
      {
         set(str);
         return *this;
      }

   };



} // namespace file





#include "file_plain_text_ostream_string_buffer.h"
#include "file_plain_text_stream_string_buffer.h"




