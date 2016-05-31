//#include "framework.h"


namespace file
{


   ostream::ostream()
   {
   
   }


   ostream::ostream(const char * lpszFileName, uint32_t nOpenFlags, ::ace::application * papp)
   {

      if(papp == NULL)
      {

         m_spbuffer = canew(::file::streambuf(lpszFileName,nOpenFlags | ::file::mode_write));

      }
      else
      {

         m_spbuffer = App(papp).file().get_file(lpszFileName,nOpenFlags | ::file::mode_write);

      }

   }


   ostream::ostream(stream_buffer * pwriter)
   {

      m_spbuffer     = pwriter;

   }


   ostream::ostream(const ostream & ostream) 
   {

      m_spbuffer     = ostream.m_spbuffer;

   }


   ostream::~ostream()
   {
      close();
   }


   void ostream::write_from_hex(const void *lpBuf,memory_size_t nCount)
   {

      m_spbuffer->write_from_hex(lpBuf,nCount);

   }


   void ostream::write(const void *lpBuf,memory_size_t nCount)
   {
      
      m_spbuffer->write(lpBuf, nCount);

   }

   void ostream::write(const void *lpBuf, memory_size_t nCount, memory_size_t * dwWritten)
   {

      m_spbuffer->write(lpBuf, nCount, dwWritten);

   }


   void ostream:: write (bool b)
   {
      
   }

   void ostream:: write (char ch)
   {
      
   }

   void ostream:: write (uchar uch)
   {
      
   }

   void ostream:: write (int16_t i)
   {

   }

   void ostream:: write (uint16_t ui)
   {

   }
#ifdef WINDOWS
   void ostream:: write (unichar wch)
   {

   }
#endif
   void ostream:: write (int32_t i)
   {

   }

   void ostream:: write (uint32_t ui)
   {

   }

   void ostream:: write (int64_t i)
   {

   }

   void ostream:: write (uint64_t ui)
   {

   }
   
#ifdef APPLEOS
   
   void ostream:: write (unsigned long ui)
   {
      
   }
   
#endif
   

   void ostream::write_arbitrary(int32_t i)
   {


   }

   void ostream::write_arbitrary(uint32_t ui)
   {


   }


   void ostream::write_arbitrary(uint64_t ui, int signal)
   {


   }

   void ostream::write_arbitrary(int64_t i)
   {


   }

   void ostream::write_arbitrary(uint64_t ui)
   {

   }

   void ostream:: write (float f)
   {

   }

   void ostream:: write (double d)
   {

   }

   void ostream:: write (const RECT & rect)
   {

   }

   void ostream:: write(LPCRECT lpcrect)
   {
      write(*lpcrect);
   }

   void ostream:: write(const SIZE & size)
   {

   }

   void ostream:: write(const sp(type) info)
   {

   }

   void ostream:: write (const serializable & serializable)
   {
      serializable.write(*this);
   }

   void ostream:: write (const char * psz)
   {
      
   }

   void ostream:: write (const id & id)
   {


   }


   void ostream:: write (const var & var)
   {

   }


   void ostream:: write(const property & property)
   {

   }


   ostream & ostream::operator = (const ostream & ostream)
   {

      m_spbuffer = ostream.m_spbuffer;

      return *this;

   }

   void ostream::flush()
   {
      
      if(m_spbuffer.is_set())
      {

         m_spbuffer->flush();

      }

   }


   void ostream::close()
   {

      flush();

      stream_base::close();

   }
        
   
   bool ostream::is_writer_null()
   {

      return m_spbuffer.is_null();

   }


   bool ostream::is_writer_set()
   {

      return m_spbuffer.is_set();

   }

   
   void ostream:: write (const string & str)
   {

      m_spbuffer->write(str, str.get_length());

   }

   void ostream::set_length(file_size_t len)
   {
   
      m_spbuffer->set_length(len);

   }

   ostream & ostream::put(char ch)
   {
      write(ch);
      return *this;
   }

} // namespace file




