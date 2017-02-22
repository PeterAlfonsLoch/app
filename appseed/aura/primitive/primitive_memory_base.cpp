#include "framework.h"

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
      m_bOwn               = false;
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

      m_cbStorage          = 0;
      m_dwAllocation       =  0;
      m_pbStorage          = NULL;
      m_pbComputed         = NULL;
      m_iOffset            = 0;

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
         m_pbComputed   = m_pbStorage + m_iOffset;
         m_iOffset = 0;
         m_cbStorage = 0;
         return true;
      }

      if((m_iOffset + dwNewLength) > m_dwAllocation)
      {
         
         if (!allocate_internal(m_iOffset + dwNewLength))
         {

            return false;

         }

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

      if(m_pbStorage == NULL || !m_bOwn)
      {

         lpb = (LPBYTE) impl_alloc(dwAllocation);

         if(lpb == NULL)
         {

            return false;

         }

         if (!m_bOwn)
         {

            memcpy(lpb, m_pbStorage, MIN(m_dwAllocation, dwAllocation));

         }

      }
      else
      {

         if(dwNewLength < m_dwAllocation)
         {

            return true;

         }

         if (m_bOwn)
         {

            lpb = impl_realloc(m_pbStorage, (size_t)dwAllocation);

         }
         else
         {

            lpb = NULL;

         }

         if(lpb == NULL)
         {

            lpb = impl_alloc((size_t) dwAllocation);

            if(lpb == NULL)
            {

               return false;

            }

            memcpy(lpb,m_pbStorage,m_cbStorage);

            if (!m_bOwn)
            {

               impl_free(m_pbStorage);

            }

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

      m_bOwn            = true;

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

   void memory_base::random_bytes(::count c)
   {

      if (c >= 0)
      {

         allocate(c);

      }

      if (get_size() > 0)
      {

         ::aura::system::g_p->math().random_bytes(get_data(), get_size());

      }

   }


   memory_size_t memory_base::calc_allocation(memory_size_t size)
   {

      return (memory_size_t) (((size + m_dwAllocationAddUp) ) / m_dwAllocationAddUp * m_dwAllocationAddUp);

   }


   void memory_base::read(::file::istream & istream)
   {

      transfer_from(istream);

   }


   void memory_base::write(::file::ostream & ostream) const
   {

      transfer_to(ostream);

   }


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

         pos = get_size() + pos;

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

      memmove(m_pbStorage + pos,m_pbStorage + pos + len,get_size() - (pos + len));

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


   bool memory_base::is_locked() const
   {

      if (m_spmutex.is_null())
         return false;
      else
         return m_spmutex->is_locked();

   }

   bool memory_base::is_enabled() const
   {

      if (m_bLockMode)
         return is_locked();
      else
         return true;

   }

   void memory_base::allocate_add_up(memory_size_t dwAddUp)
   {

      allocate(get_size() + dwAddUp);

   }



   bool memory_base::operator == (const memory_base & s)
   {

      bool b = false;

      single_lock sl(m_spmutex);

      sl.lock();

      if (this->get_size() == s.get_size())
         b = memcmp(get_data(), s.get_data(), (size_t) this->get_size()) == 0;

      sl.unlock();

      return b;

   }


   void memory_base::copy_from(const memory_base *pstorage)
   {

      ASSERT(pstorage != NULL);

      allocate(pstorage->get_size());

      memcpy(get_data(), pstorage->get_data(), (size_t) this->get_size());

   }

   
   void memory_base::set_data(void *pdata, memory_size_t uiSize)
   {

      allocate(uiSize);

      memcpy(get_data(), pdata, (size_t)uiSize);

   }


   void memory_base::set(byte b, memory_position_t iStart, memory_size_t uiSize)
   {

      if (uiSize + iStart > get_size())
         uiSize = get_size() - iStart;

      memset(get_data() + iStart, b, (size_t)uiSize);

   }


   void memory_base::zero(memory_position_t iStart, memory_size_t uiSize)
   {

      set(0, iStart, uiSize);

   }


   void memory_base::eat_begin(void * pdata, memory_size_t iSize)
   {

      ASSERT(iSize <= this->get_size());

      if (iSize <= this->get_size())
      {

         delete_begin(iSize);

      }

   }


   memory_base & memory_base::operator = (const memory_base & s)
   {

      if (this != &s)
      {

         copy_from(&s);

      }

      return *this;

   }


   memory_base & memory_base::operator += (const memory_base & s)
   {

      append(s);

      return *this;

   }


   void memory_base::to_hex(string & str, memory_position_t pos, memory_size_t size)
   {

      if (pos > this->get_size())
      {

         throw invalid_argument_exception(get_app());

      }

      if (pos + size > get_size())
      {

         size = get_size() - pos;

      }

      char * pchSrc = (char *)get_data();

      char * pchDst = str.GetBufferSetLength(size * 2);

      uint64_t dwEnd = pos + size;

      for (uint64_t dw = pos; dw < dwEnd; dw++)
      {

         if (((pchSrc[dw] & 0xf0) >> 4) < 10)
         {

            *pchDst = (char)(((pchSrc[dw] & 0xf0) >> 4) + '0');

         }
         else
         {

            *pchDst = (char)(((pchSrc[dw] & 0xf0) >> 4) + 'A' - 10);

         }

         pchDst++;
         
         if (((pchSrc[dw] & 0x0f)) < 10)
         {

            *pchDst = (char)((pchSrc[dw] & 0x0f) + '0');

         }
         else
         {

            *pchDst = (char)((pchSrc[dw] & 0x0f) + 'A' - 10);

         }

         pchDst++;

      }

      str.ReleaseBuffer();

   }

   
   string memory_base::to_hex(memory_position_t pos, memory_size_t size)
   {

      string str;

      to_hex(str, pos, size);

      return str;

   }

   void memory_base::from_hex(const char * psz, strsize nCount)
   {

      char ch;

      bool bOdd = false;

      strsize iLen = nCount < 0 ? strlen(psz) + nCount + 1 : nCount;

      bOdd = (iLen % 2) != 0;

      if (bOdd)
      {

         iLen++;

      }

      allocate(iLen / 2);

      char * pch = (char *)get_data();

      while (*psz != '\0')
      {

         ch = 0;

         if (bOdd)
         {

            bOdd = false;

         }
         else
         {

            if (*psz > '9')
            {

               ch |= ((*psz - 'A' + 10) & 0x0f) << 4;

            }
            else
            {

               ch |= ((*psz - '0') & 0x0f) << 4;

            }

            if (*psz == '\0')
            {

               break;

            }

            psz++;

         }

         if (*psz > '9')
         {

            ch |= ((*psz - 'A' + 10) & 0x0f);

         }
         else
         {

            ch |= ((*psz - '0') & 0x0f);

         }

         *pch = ch;

         psz++;

         pch++;

      }

   }


   void memory_base::to_asc(string & str)
   {

      str.Empty();

      string strTo;

      to_hex(strTo);

      char ch;

      strsize iLen = strTo.get_length() - 1;

      for (int32_t i = 0; i < iLen; i += 2)
      {

         if (strTo[i] <= '9')
         {

            ch = (strTo[i] - '0') << 4;

         }
         else
         {

            ch = (strTo[i] - 'A' + 10) << 4;

         }

         if (strTo[i + 1] <= '9')
         {

            ch |= (strTo[i + 1] - '0');

         }
         else
         {

            ch |= (strTo[i + 1] - 'A' + 10);

         }

         str += ch;

      }

   }


   void memory_base::from_asc(const char * psz)
   {

      string str;

      while (*psz)
      {

         char ch = ((*psz & 0xf0) >> 4);

         if (ch < 10)
         {

            ch += '0';

         }
         else
         {

            ch += 'A' - 10;

         }

         str += ch;

         ch = ((*psz & 0xf));

         if (ch < 10)
         {

            ch += '0';

         }
         else
         {

            ch += 'A' - 10;

         }

         str += ch;

         psz++;

      }

      from_hex(str);

   }


   void memory_base::from_string(const unichar * pwsz)
   {

      from_string(::str::international::unicode_to_utf8(pwsz));

   }


   void memory_base::from_string(const char * psz)
   {

      allocate(strlen(psz));

      memcpy(get_data(), psz, this->get_size());

   }


   void memory_base::from_string(const string & str)
   {

      allocate(str.length());

      memcpy(get_data(), str, this->get_size());

   }


   void memory_base::from_string(const var & var)
   {

      from_string((const string &)var.get_string());

   }


   void memory_base::to_string(string & str, memory_position_t iStart, memory_size_t iCount) const
   {

      if ((memory_offset_t)iStart < 0)
      {

         *((memory_offset_t*)iStart) += this->get_size();

      }

      if (iStart > this->get_size())
      {

         return;

      }

      if (iStart + iCount > this->get_size())
      {

         iCount = this->get_size() - iStart - iCount;

      }

      if (iCount <= 0)
      {

         return;

      }

      LPSTR lpsz = str.GetBufferSetLength(iCount + 1);

      memcpy(lpsz, &get_data()[iStart], iCount);

      lpsz[iCount] = '\0';

      str.ReleaseBuffer();

   }


   string memory_base::to_string(memory_position_t iStart, memory_size_t iCount) const
   {

      string str;

      to_string(str, iStart, iCount);

      return str;

   }


   void memory_base::move_and_grow(memory_offset_t offset)
   {

      move(offset, true);

   }


   void memory_base::move(memory_offset_t offset, bool bGrow)
   {

      if (offset > 0)
      {

         if (bGrow)
         {

            this->allocate_add_up(offset);

         }

         if ((memory_size_t)offset > this->get_size())
         {

            return;

         }

         memmove(&this->get_data()[offset], this->get_data(), this->get_size() - offset);

      }
      else if (offset < 0)
      {

         offset = -offset;

         if (bGrow)
         {

            this->allocate_add_up(offset);

         }

         if ((memory_size_t)offset > this->get_size())
         {

            return;

         }

         memmove(this->get_data(), &this->get_data()[offset], this->get_size() - offset);

      }

   }


   void memory_base::append(const memory_base & mem, memory_position_t iStart, memory_size_t iCount)
   {

      if ((memory_offset_t)iStart < 0)
      {

         *((memory_offset_t*)iStart) += this->get_size();

      }

      if (iStart > this->get_size())
      {

         return;

      }

      if (iStart + iCount > this->get_size())
      {

         iCount = this->get_size() - iStart - iCount;

      }

      if (iCount <= 0)
      {

         return;

      }

      allocate_add_up(iCount);

      memcpy(&get_data()[this->get_size() - iCount], &mem.get_data()[iStart], (size_t)iCount);

   }


   void memory_base::append(const void * pdata, memory_size_t iCount)
   {

      if (iCount <= 0)
      {

         return;

      }

      memory_size_t iOldSize = get_size();

      allocate_add_up(iCount);

      memcpy(&get_data()[iOldSize], pdata, (size_t)iCount);

   }


   void memory_base::assign(const void * pdata, memory_size_t iCount)
   {

      allocate(iCount);

      memcpy(get_data(), pdata, (size_t)iCount);

   }


   void memory_base::assign(const void * pdata, memory_position_t iStart, memory_size_t iCount)
   {

      allocate(iCount);

      memcpy(get_data(), &((LPBYTE)pdata)[iStart], (size_t)iCount);

   }

   
   void memory_base::append(memory_size_t iCount, uchar uch)
   {

      allocate_add_up(iCount);

      memory_position_t iStart = this->get_size() - iCount;

      memory_position_t iEnd = iStart + iCount - 1;

      for (memory_position_t i = iStart; i <= iEnd; i++)
      {

         get_data()[i] = uch;

      }

   }

   
   void memory_base::assign(memory_size_t iCount, uchar uch)
   {

      allocate(iCount);

      memory_position_t iEnd = iCount - 1;

      for (memory_position_t i = 0; i <= iEnd; i++)
      {

         this->get_data()[i] = uch;

      }

   }


   
   void memory_base::assign(const char * psz)
   {

      return from_string(psz);

   }



#if defined(METROWIN) && defined(__cplusplus_winrt)

   Array < uchar, 1U > ^ memory_base::get_os_bytes(memory_position_t pos, memory_size_t size) const
   {
      if (pos > get_size())
         throw invalid_argument_exception(get_app());
      if (size < 0 || pos + size > get_size())
         size = get_size() - pos;
      return ref new Array < uchar, 1U >((uchar *)&get_data()[pos], size);
   }

   ::Windows::Storage::Streams::IBuffer ^ memory_base::get_os_crypt_buffer(memory_position_t pos, memory_size_t size) const
   {
      return ::Windows::Security::Cryptography::CryptographicBuffer::CreateFromByteArray(get_os_bytes(pos, size));
   }

   ::Windows::Storage::Streams::IBuffer ^ memory_base::get_os_buffer(memory_position_t pos, memory_size_t size) const
   {
      ::Windows::Storage::Streams::DataWriter ^ writer = ref new ::Windows::Storage::Streams::DataWriter();
      writer->WriteBytes(get_os_bytes(pos, size));
      return writer->DetachBuffer();
   }


   void memory_base::set_os_bytes(Array < uchar, 1U > ^ a, memory_position_t pos, memory_size_t size)
   {

      if (!a)
         return;

      if (pos > a->Length)
         throw invalid_argument_exception(get_app());

      if (pos > a->Length)
         throw invalid_argument_exception(get_app());

      if (size < 0 || pos + size > a->Length)
         size = a->Length - pos;

      allocate(size);

      memcpy(get_data(), &a->Data[pos], size);

   }


   void memory_base::set_os_crypt_buffer(::Windows::Storage::Streams::IBuffer ^ ibuf, memory_position_t pos, memory_size_t size)
   {
      Array < uchar, 1U > ^ a = nullptr;
      ::Windows::Security::Cryptography::CryptographicBuffer::CopyToByteArray(ibuf, &a);
      return set_os_bytes(a, pos, size);
   }

   void memory_base::set_os_buffer(::Windows::Storage::Streams::IBuffer ^ ibuf, memory_position_t pos, memory_size_t size)
   {
      Windows::Storage::Streams::DataReader^ r = Windows::Storage::Streams::DataReader::FromBuffer(ibuf);
      Array<uchar, 1U>^ a = ref new Array<uchar, 1U>(ibuf->Length);
      r->ReadBytes(a);
      return set_os_bytes(a, pos, size);
   }

#elif defined(APPLEOS)

   CFDataRef memory_base::get_os_cf_data(memory_position_t pos, memory_size_t size) const
   {
      if (pos > get_size())
         throw invalid_argument_exception(get_app());
      if (pos + size > get_size())
         size = get_size() - pos;
      return CFDataCreate(kCFAllocatorDefault, (const UInt8 *)&get_data()[pos], (CFIndex)size);
   }

   void memory_base::set_os_cf_data(CFDataRef data, memory_position_t pos, memory_size_t size)
   {
      if (pos > CFDataGetLength(data))
         throw invalid_argument_exception(get_app());
      if (pos > CFDataGetLength(data))
         throw invalid_argument_exception(get_app());
      if (pos + size > CFDataGetLength(data))
         size = CFDataGetLength(data) - pos;
      allocate(size);
      memcpy(get_data(), &CFDataGetBytePtr(data)[pos], size);
   }


#endif

   memory_base & memory_base::reverse()
   {
      if (this->get_data() != NULL)
      {
         ::mem_reverse(this->get_data(), this->get_size());
      }
      return *this;
   }


   memory_size_t memory_base::get_length() const
   {

      return get_size();

   }


   memory_size_t memory_base::length() const
   {

      return get_size();

   }


} // namespace primitive


