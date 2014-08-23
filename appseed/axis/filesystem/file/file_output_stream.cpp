#include "framework.h"


namespace file
{


   output_stream::output_stream()
   {
   
   }


   output_stream::output_stream(const char * lpszFileName, uint32_t nOpenFlags, sp(::axis::application) papp)
   {

      if(papp == NULL)
      {

         m_spbuffer = canew(::file::streambuf(lpszFileName,nOpenFlags | ::file::mode_write));

      }
      else
      {

         m_spbuffer = App(papp).file_get_file(lpszFileName,nOpenFlags | ::file::mode_write);

      }

   }


   output_stream::output_stream(stream_buffer * pwriter)
   {

      m_spbuffer     = pwriter;

   }


   output_stream::output_stream(const output_stream & ostream) 
   {

      m_spbuffer     = ostream.m_spbuffer;

   }


   output_stream::~output_stream()
   {
      close();
   }


   void output_stream::write(const void *lpBuf, ::primitive::memory_size nCount)
   {
      
      m_spbuffer->write(lpBuf, nCount);

   }

   void output_stream::write(const void *lpBuf, ::primitive::memory_size nCount, ::primitive::memory_size * dwWritten)
   {

      m_spbuffer->write(lpBuf, nCount, dwWritten);

   }


   void output_stream:: write (bool b)
   {
      
   }

   void output_stream:: write (char ch)
   {
      
   }

   void output_stream:: write (uchar uch)
   {
      
   }

   void output_stream:: write (int16_t i)
   {

   }

   void output_stream:: write (uint16_t ui)
   {

   }

   void output_stream:: write (wchar_t wch)
   {

   }

   void output_stream:: write (int32_t i)
   {

   }

   void output_stream:: write (uint32_t ui)
   {

   }

   void output_stream:: write (int64_t i)
   {

   }

   void output_stream:: write (uint64_t ui)
   {

   }
   
#ifdef APPLEOS
   
   void output_stream:: write (unsigned long ui)
   {
      
   }
   
#endif
   

   void output_stream::write_arbitrary(int32_t i)
   {


   }

   void output_stream::write_arbitrary(uint32_t ui)
   {


   }


   void output_stream::write_arbitrary(uint64_t ui, int signal)
   {


   }

   void output_stream::write_arbitrary(int64_t i)
   {


   }

   void output_stream::write_arbitrary(uint64_t ui)
   {

   }

   void output_stream:: write (float f)
   {

   }

   void output_stream:: write (double d)
   {

   }

   void output_stream:: write (const RECT & rect)
   {

   }

   void output_stream:: write(LPCRECT lpcrect)
   {
      write(*lpcrect);
   }

   void output_stream:: write(SIZE & size)
   {

   }

   void output_stream:: write (sp(type) info)
   {

   }

   void output_stream:: write (serializable & serializable)
   {

   }

   void output_stream:: write (const char * psz)
   {
      
   }

   void output_stream:: write (const id & id)
   {


   }

   void output_stream:: write (const var & var)
   {

   }

   output_stream & output_stream::operator = (const output_stream & ostream)
   {

      m_spbuffer = ostream.m_spbuffer;

      return *this;

   }

   void output_stream::flush()
   {
      
      if(m_spbuffer.is_set())
      {

         m_spbuffer->flush();

      }

   }


   void output_stream::close()
   {

      flush();

      stream_base::close();

   }
        
   
   bool output_stream::is_writer_null()
   {

      return m_spbuffer.is_null();

   }


   bool output_stream::is_writer_set()
   {

      return m_spbuffer.is_set();

   }

   
   void output_stream:: write (const string & str)
   {

      m_spbuffer->write(str, str.get_length());

   }

   void output_stream::set_length(file_size len)
   {
   
      m_spbuffer->set_length(len);

   }

   output_stream & output_stream::put(char ch)
   {
      write(ch);
      return *this;
   }

} // namespace file




