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

   void writer::transfer_from_begin(reader & reader, ::primitive::memory_size uiBufSize)
   {

      reader.seek_to_begin();

      transfer_from(reader, uiBufSize);

   }

   void writer::transfer_from(reader & reader, ::primitive::memory_size uiBufSize)
   {


      if(reader.get_internal_data() != NULL && reader.get_internal_data_size() > reader.get_position())
      {

         write((byte *) reader.get_internal_data() + reader.get_position(), (::primitive::memory_size) (reader.get_internal_data_size() - reader.get_position()));

         return;

      }


      ::primitive::memory_size uiRead;
      ::primitive::memory_size uiSize = 0;
      uiBufSize = max(8 * 1024, uiBufSize);

      ::primitive::memory buf;

      buf.allocate(uiBufSize);

      if(buf.get_data() == NULL)
         throw memory_exception(get_app());

      try
      {
         while(true)
         {
            uiRead = reader.read(buf.get_data(), buf.get_size());
            write(buf.get_data(), uiRead);
            if(uiRead <= 0)
            {
               break;
            }
            uiSize += uiBufSize;
         }
      }
      catch(...)
      {
      }

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

   void writer::write (const RECT & rect)
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


   HRESULT write(writer * pwriter, const void * data, ::primitive::memory_size size)
   {
      HRESULT res = S_OK;
      try
      {
         pwriter->write(data, size);
      }
      catch(...)
      {
         res = E_FAIL;
      }
      RINOK(res);
      return res;
   }

} // namespace file




