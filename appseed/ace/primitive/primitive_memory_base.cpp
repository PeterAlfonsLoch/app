//#include "framework.h"

#ifdef WINDOWS
#include <Shcore.h>
#endif


namespace primitive
{


   memory_base::memory_base()
   {
#if MEMDLEAK
      m_iLine              = 0;
#endif
      m_pbStorage          = NULL;
      m_pbComputed         = NULL;
      m_cbStorage          = 0;
      m_dwAllocation       = 0;
      m_dwAllocationAddUp  = 4096;
      m_dAllocationRateUp  = (double)(1.0 - ((double)m_dwAllocationAddUp /2.0) * log((double) m_dwAllocationAddUp - 1.0))/(1- log((double)m_dwAllocationAddUp - 1.0));
      m_iOffset            = 0;
      m_iMaxOffset         = 16 * 1024;
      m_bLockMode          = false;
      m_bLock              = false;
      m_pcontainer         = NULL;
      m_pprimitivememory   = NULL;
      m_psharedmemory      = NULL;
      m_pvirtualmemory     = NULL;

   }

   memory_base::~memory_base()
   {

      m_cbStorage = 0;
      m_dwAllocation =  0;
      m_pbStorage = NULL;
      m_pbComputed      = NULL;
      m_iOffset         = 0;

   }

   memory_base & memory_base::prefix_der_length()
   {
      int32_t msb = ::msb(get_size());
      if(msb < 7)
      {
         move_and_grow(1);
         get_data()[0] = (BYTE)(get_size() - 1);
      }
      else
      {
         int32_t iLen = (msb + 8) / 8;
         move_and_grow(1 + iLen);
         get_data()[0] = 0x80 | iLen;
         auto s = get_size() - 1 - iLen;
         byte * p = (byte *)&s;
         for(int32_t i = 1; i <= iLen; i++)
         {
            get_data()[i] = p[iLen - i];
         }
      }
      return *this;
   }


   memory_base & memory_base::prefix_der_uint_content()
   {
      if(get_size() > 0)
      {
         if(get_data()[0] & 0x80)
         {
            move_and_grow(1);
            get_data()[0] = 0;
         }
      }
      return *this;
   }

   memory_base & memory_base::prefix_der_type(int32_t iType)
   {

      move_and_grow(1);

      get_data()[0] = iType;

      return *this;

   }

   memory_base & memory_base::prefix_der_uint()
   {
      return prefix_der_uint_content().prefix_der_length().prefix_der_type(2); // 2 - integer
   }

   memory_base & memory_base::prefix_der_sequence()
   {
      return prefix_der_length().prefix_der_type(0x30); // 0x30 - universal sequence
   }



   bool memory_base::allocate(memory_size_t dwNewLength)
   {

      if(!is_enabled())
      {
         ASSERT(FALSE);
         return false;
      }

      if((m_iOffset + dwNewLength) <= 0)
      {
         m_iOffset = 0;
         m_cbStorage = 0;
         return true;
      }

      if((m_iOffset + dwNewLength) > m_dwAllocation)
      {
         if(!allocate_internal(m_iOffset + dwNewLength))
            return false;
      }

      if((m_iOffset + dwNewLength) > m_dwAllocation)
         return false;

      m_cbStorage    = dwNewLength;

      m_pbComputed   = m_pbStorage + m_iOffset;

      return true;
   }

   LPBYTE memory_base::impl_alloc(memory_size_t dwAllocation)
   {

      return NULL;

   }

   LPBYTE memory_base::impl_realloc(void * pdata, memory_size_t dwAllocation)
   {

      return NULL;

   }

   void memory_base::impl_free(LPBYTE pdata)
   {

   }

   bool memory_base::allocate_internal(memory_size_t dwNewLength)
   {

      if(!is_enabled())
      {
         ASSERT(FALSE);
         return false;
      }

      if(dwNewLength <= 0)
      {
         return true;
      }

      remove_offset();

      memory_size_t dwAllocation = calc_allocation(dwNewLength);

      LPBYTE lpb;

      if(m_pbStorage == NULL)
      {

         lpb = (LPBYTE) impl_alloc(dwAllocation);

         if(lpb == NULL)
         {

            return false;

         }

      }
      else
      {

         if(dwNewLength < m_dwAllocation)
         {

            return true;

         }

         lpb = impl_realloc(m_pbStorage,(size_t)dwAllocation);

         if(lpb == NULL)
         {

            lpb = impl_alloc((size_t) dwAllocation);

            if(lpb == NULL)
            {

               return false;

            }

            memcpy(lpb,m_pbStorage,m_cbStorage);

            impl_free(m_pbStorage);

         }

         memory_size_t iOffset = lpb - m_pbStorage;

         if(m_pcontainer != NULL)
         {

            m_pcontainer->offset_kept_pointers(iOffset);

         }

      }

      m_dwAllocation    = dwAllocation;

      m_pbStorage       = lpb;

      m_pbComputed      = m_pbStorage;

      return true;

   }


   void memory_base::reserve(memory_size_t dwNewLength)
   {

      if(dwNewLength <= m_dwAllocation)
         return;

      if(!allocate_internal(dwNewLength))
         throw memory_exception(get_app());

   }


   void memory_base::remove_offset()
   {

      if(m_pbStorage == NULL || m_pbComputed == NULL || m_iOffset <= 0)
         return;

      memmove(m_pbStorage,m_pbComputed,m_cbStorage);

      m_iOffset      = 0;

      m_pbComputed   = m_pbStorage;

   }


   /*
   void memory_base::FullLoad(::file::binary_buffer & file)
   {

   if(!is_enabled())
   {
   ASSERT(false);
   return;
   }

   uint64_t dwTemp;
   memory_size_t cbStorage = (memory_size_t) file.get_length();
   file.seek_to_begin();
   allocate(cbStorage);
   try
   {
   dwTemp = file.read(get_data(), cbStorage);
   }
   #ifdef DEBUG
   catch(::file::exception & e)
   #else
   catch(::file::exception & )
   #endif
   {
   throw "smfOpenFile: read error on image!";
   #ifdef DEBUG
   e.dump(g_dumpcontext);
   #endif
   }
   if (cbStorage != dwTemp)
   {
   throw "smfOpenFile: read error on image!";
   }

   }
   */


   memory_size_t memory_base::calc_allocation(memory_size_t size)
   {

      //int s = size + exp((m_dAllocationRateUp - (double)size) / ((double) m_dAllocationRateUp - (double) m_dwAllocationAddUp / 2.0));

      return (memory_size_t) (((size + m_dwAllocationAddUp) ) / m_dwAllocationAddUp * m_dwAllocationAddUp);

   }


   void memory_base::read(::file::istream & istream)
   {

      transfer_from(istream);

      /*memory_size_t uiRead;

      memory_size_t uiBufSize = 1024 + 1024;

      memory_size_t uiSize = 0;

      while(true)
      {

      allocate(uiSize + uiBufSize);

      uiRead = istream.read(&((byte *)get_data())[uiSize], uiBufSize);

      if(uiRead < uiBufSize)
      {
      allocate(uiSize + uiRead);

      break;

      }

      uiSize += uiBufSize;

      }*/

   }


   void memory_base::write(::file::ostream & ostream) const
   {

      transfer_to(ostream);
      //ostream.write(get_data(), this->get_size());

   }



   /*   memory_size_t memory_base::read(::file::binary_buffer & file)
      {

      file_size_t dwEnd = file.get_length();

      file_position_t dwPos = file.get_position();

      memory_size_t dwRemain = (memory_size_t)(dwEnd - dwPos);

      allocate((memory_size_t) dwRemain);

      memory_size_t dwRead = file.read(get_data(), dwRemain);

      allocate(dwRead);

      return dwRead;

      }
      */

   void memory_base::delete_begin(memory_size_t iSize)
   {

      iSize = MAX(0,MIN(get_size(),iSize));

      m_iOffset += iSize;

      if(m_pcontainer != NULL)
      {

         m_pcontainer->offset_kept_pointers((memory_offset_t) iSize);

      }

      m_cbStorage -= iSize;

      m_pbComputed += iSize;

      if(m_iOffset > m_iMaxOffset)
      {

         remove_offset();

      }


   }


   void memory_base::transfer_to(::file::writer & writer,memory_size_t uiBufferSize) const
   {

      if(get_data() == NULL || get_size() <= 0)
         return;

      if(writer.increase_internal_data_size(get_size()) && writer.get_internal_data() != NULL)
      {

         if(writer.get_internal_data() == get_data())
            return;

         memmove(((byte *)writer.get_internal_data()) + writer.get_position() + get_size(),((byte *)writer.get_internal_data()) + writer.get_position(),writer.get_internal_data_size() - get_size());
         memcpy(((byte *)writer.get_internal_data()) + writer.get_position(),get_data(),get_size());
         writer.seek(get_size(),::file::seek_current);

      }
      else
      {

         writer.write(get_data(),get_size());

      }

   }

   void memory_base::transfer_from_begin(::file::reader & reader,memory_size_t uiBufferSize)
   {

      reader.seek_to_begin();

      transfer_from(reader,uiBufferSize);

   }

   void memory_base::transfer_from(::file::reader & reader,memory_size_t uiBufferSize)
   {

      if(reader.get_internal_data() != NULL && reader.get_internal_data_size() > reader.get_position())
      {

         append((byte *)reader.get_internal_data() + reader.get_position(),(memory_size_t) (reader.get_internal_data_size() - reader.get_position()));

      }
      else
      {

         memory_size_t uiRead;

         memory_size_t uiSize = 0;

         while(true)
         {

            allocate(uiSize + uiBufferSize);

            uiRead = reader.read(&get_data()[uiSize],uiBufferSize);

            if(uiRead <= 0)
            {
               break;

            }

            uiSize += uiRead;

         }

         allocate(uiSize);

      }


   }


   memory_base & memory_base::erase(memory_offset_t pos,memory_offset_t len)
   {

      if(pos < 0)
      {

         len = get_size() + pos;

      }

      if(len < 0)
      {

         len = get_size() - pos + len + 1;

      }

      if(pos < 0)
      {

         pos = 0;

      }

      len = MIN(natural(len),get_size() - pos);

      if(len <= 0)
      {

         return *this;

      }

      if(natural(pos) >= get_size())
      {

         return *this;

      }

      memmove(m_pbStorage + pos,m_pbStorage + pos + len,len);

      allocate(get_size() - len);

      return *this;

   }

#ifdef WINDOWSEX

   IStream * memory_base::CreateIStream()
   {

      if(get_data() == NULL)
         return NULL;

      return LIBCALL(shlwapi,SHCreateMemStream)(get_data(),(UINT)get_size());

   }

#elif defined(METROWIN)

   IStream * memory_base::CreateIStream()
   {

      if(get_data() == NULL)
         return NULL;

      Windows::Storage::Streams::InMemoryRandomAccessStream ^ randomAccessStream = ref new Windows::Storage::Streams::InMemoryRandomAccessStream();

      ::wait(randomAccessStream->WriteAsync(get_os_buffer()));

      IStream * pstream = NULL;

      ::CreateStreamOverRandomAccessStream(randomAccessStream,IID_PPV_ARGS(&pstream));

      return pstream;


   }
#endif


   char * memory_base::get_psz(strsize & len)
   {

      if(get_size() >= 2
         && get_data()[0] == 255
         && get_data()[1] == 60)
      {
         memory mem;
         mem = *this;
         allocate(utf8_len_len((const unichar *)&get_data()[2],get_size() - 2));
         utf16_to_utf8_len((char *) get_data(),(const unichar *)&mem.get_data()[2],(int32_t)(mem.get_size() - 2));
         len = get_size();
         return (char *) get_data();
      }
      else if(get_size() >= 3
         && get_data()[0] == 255
         && get_data()[1] == 254
         && get_data()[2] == 0x73)
      {
         memory mem;
         mem = *this;
         allocate(utf8_len_len((const unichar *)&get_data()[3],get_size() - 3));
         utf16_to_utf8_len((char *)get_data(),(const unichar *)&mem.get_data()[3],(int32_t)(mem.get_size() - 3));
         len = get_size();
         return (char *)get_data();
      }
      else if(get_size() >= 3
         && get_data()[0] == 0xef
         && get_data()[1] == 0xbb
         && get_data()[2] == 0xbf)
      {
         len = get_size() - 3;
         return (char *)&get_data()[3];
      }
      else
      {
         len = get_size();
         return (char *)get_data();
      }


   }

   //LPBYTE memory_base::detach()
   //{

   //   LPBYTE pbStorage = m_pbStorage;

   //   if(m_iOffset > 0)
   //   {

   //      sp(memory_base) pbase = clone();

   //      impl_free(m_pbStorage);

   //      pbStorage = pbase->detach();

   //   }
   //   else
   //   {

   //      pbStorage = m_pbStorage;

   //   }

   //   m_pbStorage       = NULL;

   //   m_pbComputed      = NULL;

   //   m_cbStorage       = 0;

   //   m_dwAllocation    = 0;

   //   m_iOffset         = 0;

   //   return pbStorage;

   //}


   //LPBYTE memory_base::detach_shared_memory(HGLOBAL & hglobal)
   //{

   //   throw not_supported_exception(get_app(),"valid only for Global Memory(\"HGLOBAL\")");

   //}


} // namespace primitive


