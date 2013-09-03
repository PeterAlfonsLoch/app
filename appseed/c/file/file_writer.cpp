#include "framework.h"


namespace file
{


   writer::writer()
   {
   }

   writer::writer(writer * pwriter) :
      m_spwriter(pwriter)
   {
   }

   writer::writer(const writer & writer)
   {
      operator = (writer);
   }

   writer::~writer()
   {
   }


   void writer::write(const void *lpBuf, ::primitive::memory_size nCount)
   {
      if(m_spwriter.is_null())
      {
         ::primitive::memory_size dwWritten;
         while (nCount > 0)
         {
            dwWritten = 0;
            write(lpBuf, nCount, &dwWritten);
            if(dwWritten <= 0)
               throw "written 0 bytes";
            lpBuf = (const void *)((const byte *)lpBuf + dwWritten);
            if(dwWritten > nCount)
               throw "written more than requested ::count of bytes";
            nCount -= dwWritten;
 
         }
      }
      else
      {
         // if stack overflows or function crashes here, probably this member should be overridden
         m_spwriter->write(lpBuf, nCount);
      }
   }

   void writer::write(const void *lpBuf, ::primitive::memory_size nCount, ::primitive::memory_size * dwWritten)
   {
      if(m_spwriter.is_null())
      {
         write(lpBuf, nCount);
         *dwWritten = nCount;
      }
      else
      {
         // if stack overflows or function crashes here, probably this member should be overridden
         m_spwriter->write(lpBuf, nCount, dwWritten);
      }
   }

   void writer::read(reader & reader)
   {
      ::primitive::memory_size uiRead;
      ::primitive::memory_size uiBufSize = 1024 * 1024;
      ::primitive::memory_size uiSize = 0;

      char * buf = (char *) malloc(uiBufSize);
      if(buf == NULL)
         throw "no primitive::memory";
      try
      {
         while(true)
         {
            uiRead = reader.read(buf, uiBufSize);
            write(buf, uiRead);
            if(uiRead < uiBufSize)
            {
               break;
            }
            uiSize += uiBufSize;
         }
      }
      catch(...)
      {
      }
      free(buf);
   }

   writer & writer::operator = (const writer & writer)
   {
      if(this != &writer)
      {
         m_spwriter = writer.m_spwriter;
      }
      return *this;
   }

   bool writer::is_writer_null()
   {
      return m_spwriter.is_null();
   }

   bool writer::is_writer_set()
   {
      return m_spwriter.is_set();
   }

   void writer::close()
   {
      if(m_spwriter.is_set())
      {
         //m_spwriter->close();
         ::release(m_spwriter.m_p);
      }
   }

   void writer::from_hex(const char * psz)
   {
      primitive::memory memory(get_app());
      memory.from_hex(psz);
      write(memory.get_data(), memory.get_size());
   }

   void writer::flush()
   {
   }


} // namespace file




