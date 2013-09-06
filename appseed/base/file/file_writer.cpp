#include "framework.h"


namespace file
{


   writer::writer()
   {
   }


   writer::~writer()
   {
   }


   void writer::write(const void *lpBuf, ::primitive::memory_size nCount)
   {
      
      ::primitive::memory_size memory_size;
      
      write(lpBuf, nCount, &memory_size);

   }

   void writer::write(const void *lpBuf, ::primitive::memory_size nCount, ::primitive::memory_size * dwWritten)
   {

      throw interface_only_exception(get_app());

   }

   void writer::read_from(reader & reader)
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

   /*
   bool writer::is_writer_null()
   {
      return m_spwriter.is_null();
   }

   bool writer::is_writer_set()
   {
      return m_spwriter.is_set();
   }
   */
   void writer::close()
   {
      /*
      if(m_spwriter.is_set())
      {
         //m_spwriter->close();
         ::release(m_spwriter.m_p);
      }
      */
   }

   /*
   void writer::from_hex(const char * psz)
   {
      primitive::memory memory(get_app());
      memory.from_hex(psz);
      write(memory.get_data(), memory.get_size());
   }*/

   void writer::flush()
   {
   }

   /*
   void writer::write (char ch)
   {
      UNREFERENCED_PARAMETER(ch);
      throw interface_only_exception(get_app());
   }

   void writer::write (uchar uch)
   {
      UNREFERENCED_PARAMETER(uch);
      throw interface_only_exception(get_app());
   }

   void writer::write (int16_t sh)
   {
      UNREFERENCED_PARAMETER(sh);
      throw interface_only_exception(get_app());
   }

   void writer::write (uint16_t ui)
   {
      UNREFERENCED_PARAMETER(ui);
      throw interface_only_exception(get_app());
   }

   void writer::write (wchar_t wch)
   {
      UNREFERENCED_PARAMETER(wch);
      throw interface_only_exception(get_app());
   }

   void writer::write (bool b)
   {
      UNREFERENCED_PARAMETER(b);
      throw interface_only_exception(get_app());
   }

   void writer::write (int32_t i)
   {
      UNREFERENCED_PARAMETER(i);
      throw interface_only_exception(get_app());
   }

   void writer::write (uint32_t ui)
   {
      UNREFERENCED_PARAMETER(ui);
      throw interface_only_exception(get_app());
   }
    
   void writer::write (int64_t i)
   {
      UNREFERENCED_PARAMETER(i);
      throw interface_only_exception(get_app());
   }

   void writer::write (uint64_t ui)
   {
      UNREFERENCED_PARAMETER(ui);
      throw interface_only_exception(get_app());
   }

   void writer::write (float f)
   {
      UNREFERENCED_PARAMETER(f);
      throw interface_only_exception(get_app());
   }

   void writer::write (double d)
   {
      UNREFERENCED_PARAMETER(d);
      throw interface_only_exception(get_app());
   }

   void writer::write (LPCRECT lpcrect)
   {
      UNREFERENCED_PARAMETER(lpcrect);
      throw interface_only_exception(get_app());
   }
    
   void writer::write (SIZE & size)
   {
      UNREFERENCED_PARAMETER(size);
      throw interface_only_exception(get_app());
   }

   void writer::write (sp(type) info)
   {
      UNREFERENCED_PARAMETER(info);
      throw interface_only_exception(get_app());
   }

   void writer::write (serializable & serializable)
   {
      UNREFERENCED_PARAMETER(serializable);
      throw interface_only_exception(get_app());
   }

   void writer::write (const char * psz)
   {
      UNREFERENCED_PARAMETER(psz);
      throw interface_only_exception(get_app());
   }
    
   void writer::write (const id & id)
   {
      UNREFERENCED_PARAMETER(id);
      throw interface_only_exception(get_app());
   }

   void writer::write (const var & var)
   {
      UNREFERENCED_PARAMETER(var);
      throw interface_only_exception(get_app());
   }

   void writer::write (const string & str)
   {
      UNREFERENCED_PARAMETER(str);
      throw interface_only_exception(get_app());
   }
   */

   HRESULT write_writer(writer * stream, const void * data, ::primitive::memory_size size)
   {
      HRESULT res = S_OK;
      try
      {
         stream->write(data, size);
      }
      catch(...)
      {
         res = E_FAIL;
      }
      RINOK(res);
      return res;
   }


} // namespace file




