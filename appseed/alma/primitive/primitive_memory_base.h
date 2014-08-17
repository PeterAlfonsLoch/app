#pragma once

template < typename N >
inline int32_t msb(N n)
{

   int32_t i = sizeof(N) * 8;

   do
   {
      i--;
      if(n & (numeric_info::get_unitary_value < N > () << i))
         return i;

   }
   while(i > 0);

   return -1;

}



namespace primitive
{


   class memory_container;
   class memory;
   class shared_memory;
   class virtual_memory;


   class CLASS_DECL_BASE memory_base :
      public object,
      public ::file::serializable
   {
   public:


      LPBYTE                  m_pbStorage;
      LPBYTE                  m_pbComputed;

      memory_offset           m_iOffset;
      memory_size             m_cbStorage;
      memory_size             m_dwAllocation;
      memory_size             m_dwAllocationAddUp;

      memory_container *      m_pcontainer;

      sp(mutex)               m_spmutex;
      bool                    m_bLockMode;
      bool                    m_bLock;

      memory *                m_pprimitivememory;
      shared_memory *         m_psharedmemory;
      virtual_memory *        m_pvirtualmemory;


      memory_base();
      virtual ~memory_base();


      inline bool is_enabled() const;
      inline bool is_locked() const;

      virtual bool allocate(memory_size dwNewLength);
      virtual bool allocate_internal(memory_size dwNewLength);

      virtual void remove_offset();

      //virtual void FullLoad(::file::stream_buffer & buffer);

      //::primitive::memory_size read(::file::stream_buffer & buffer);


      virtual void write(::file::output_stream & ostream);
      virtual void read(::file::input_stream & istream);


      virtual void transfer_to(::file::writer & writer, ::primitive::memory_size uiBufferSize = 1024 * 1024);
      virtual void transfer_from(::file::reader & reader, ::primitive::memory_size uiBufferSize = 1024 * 1024);
      virtual void transfer_from_begin(::file::reader & reader, ::primitive::memory_size uiBufferSize = 1024 * 1024);


      inline  void allocate_add_up(memory_size dwAddUp);


      inline LPBYTE           internal_get_data() const;
      inline memory_size      get_size() const;
      inline const LPBYTE     get_data() const;
      inline LPBYTE           get_data();

      inline memory_size      size() const;
      inline const LPBYTE     data() const;
      inline LPBYTE           data();


      memory_base & operator = (const memory_base & s);
      memory_base & operator += (const memory_base & s);


      inline void from_string(const wchar_t * pwsz);
      inline void from_string(const char * psz);
      inline void from_string(const string & str);
      inline void from_string(const var & var);
      inline void to_string(string & str) const;
      inline string to_string() const;

      void delete_begin(memory_size iSize);
      inline void eat_begin(void * pdata, memory_size iSize);
      inline void set_data(void * pdata, memory_size uiSize);
      inline void copy_from(const memory_base * pstorage);
      inline void set(byte b, memory_size uiSize = -1);

      inline void append(const memory_base & memory, memory_position iStart = 0, memory_size iCount = -1);
      inline void append(const void * pdata, memory_size iCount);
      inline void assign(const void * pdata, memory_size iCount);
      inline void assign(const void * pdata, memory_position iStart, memory_size iCount);
      inline void append(memory_size iCount, uchar uch);
      inline void assign(memory_size iCount, uchar uch);

      void move_and_grow(memory_offset offset);
      void move(memory_offset offset, bool bGrow = false);

      inline void assign(const char * psz);

      inline byte operator [] (memory_size i) const;
      inline byte & operator [] (memory_size i);

      inline operator const byte *() const;
      inline operator byte *();

      inline operator const char *() const { return (const char *) operator const byte *(); }
      inline operator char *() { return (char *) operator byte *(); }

      inline operator const void *() const;
      inline operator void *();


      inline void to_hex(string & str, memory_position iStart = 0, memory_size size = -1);
      inline string to_hex(memory_position iStart = 0, memory_size size = -1);
      inline void from_hex(const char * psz);

      inline void to_asc(string & str);
      inline void from_asc(const char * psz);

      inline bool operator == (const memory_base & s);


      inline memory_base & reverse();

      memory_base & prefix_der_uint_content();
      memory_base & prefix_der_length();
      memory_base & prefix_der_type(int32_t iType);

      memory_base & prefix_der_uint();
      memory_base & prefix_der_sequence();


#if defined(METROWIN) && defined(__cplusplus_winrt)

      inline Platform::Array < uchar, 1U > ^ get_os_bytes(memory_position pos = 0, memory_size size = -1) const;
      inline ::Windows::Storage::Streams::IBuffer ^ get_os_crypt_buffer(memory_position pos = 0, memory_size size = -1) const;
      inline ::Windows::Storage::Streams::IBuffer ^ get_os_buffer(memory_position pos = 0, memory_size size = -1) const;
      inline void set_os_bytes(Platform::Array < uchar, 1U > ^ a, memory_position pos = 0, memory_size size = -1);
      inline void set_os_crypt_buffer(::Windows::Storage::Streams::IBuffer ^ ibuf, memory_position pos = 0, memory_size size = -1);
      inline void set_os_buffer(::Windows::Storage::Streams::IBuffer ^ ibuf, memory_position pos = 0, memory_size size = -1);

#elif defined(APPLEOS)

       inline CFDataRef get_os_cf_data(memory_position pos = 0, memory_size size = -1) const;
       inline void set_os_cf_data(CFDataRef data, memory_position pos = 0, memory_size size = -1);

#endif


   };







   inline bool memory_base::is_locked() const
   {

      if(m_spmutex.is_null())
         return false;
      else
         return m_spmutex->is_locked();

   }

   inline bool memory_base::is_enabled() const
   {

      if(m_bLockMode)
         return is_locked();
      else
         return true;

   }

   inline void memory_base::allocate_add_up(memory_size dwAddUp)
   {
      allocate(m_cbStorage + dwAddUp);
   }


   inline LPBYTE memory_base::internal_get_data() const
   {
      return m_pbComputed;
   }

   inline memory_size memory_base::get_size() const
   {
      return m_cbStorage;
   }

   inline memory_size memory_base::size() const
   {
      return get_size();
   }


   inline const LPBYTE memory_base::get_data() const
   {
      return m_pbComputed;
      /*if(is_enabled())
         return internal_get_data() + m_iOffset;
      else
      {
         ASSERT(FALSE);
         return NULL;
      }*/

   }

   inline LPBYTE memory_base::get_data()
   {
      return m_pbComputed;
/*      if(is_enabled())
         return internal_get_data() + m_iOffset;
      else
      {
         ASSERT(FALSE);
         return NULL;
      }*/

   }



   inline const LPBYTE memory_base::data() const
   {
      return get_data();
   }

   inline LPBYTE memory_base::data()
   {
      return get_data();
   }
























   inline bool memory_base::operator == (const memory_base & s)
   {

      bool b = false;

      single_lock sl(m_spmutex);

      sl.lock();

      if(this->get_size() == s.get_size())
         b = memcmp(get_data(), s.get_data(), (size_t) this->get_size()) == 0;

      sl.unlock();

      return b;

   }



   inline void memory_base::copy_from(const memory_base *pstorage)
   {
      ASSERT(pstorage != NULL);
      allocate(pstorage->get_size());
      memcpy(get_data(), pstorage->get_data(), (size_t) this->get_size());
   }

   inline void memory_base::set_data(void *pdata, memory_size uiSize)
   {
      allocate(uiSize);
      memcpy(get_data(), pdata, (size_t) uiSize);
   }

   inline void memory_base::set(byte b, memory_size uiSize)
   {
      if(uiSize > get_size())
         uiSize = get_size();
      memset(get_data(), b, (size_t) uiSize);
   }

   inline void memory_base::eat_begin(void * pdata, memory_size iSize)
   {
      ASSERT(iSize <= this->get_size());
      if(iSize <= this->get_size())
      {
         delete_begin(iSize);
      }
   }

   inline void memory_base::remove_offset()
   {

      if(m_pbStorage == NULL || m_pbComputed == NULL || m_iOffset <= 0)
         return;

      memmove(m_pbStorage, m_pbComputed, m_cbStorage);

      m_iOffset      = 0;

      m_pbComputed   = m_pbStorage;

   }

   inline memory_base & memory_base::operator = (const memory_base & s)
   {
      if(&s == NULL)
      {
         allocate(0);
      }
      else if(this != &s)
      {
         copy_from(&s);
      }
      return *this;
   }

   inline memory_base & memory_base::operator += (const memory_base & s)
   {
      if(&s != NULL)
      {
         append(s);
      }
      return *this;
   }

   inline void memory_base::to_hex(string & str, memory_position pos, memory_size size)
   {
      if(pos > this->get_size())
         throw invalid_argument_exception(get_app());
      if(pos + size > get_size())
         size = get_size() - pos;
      char * pchSrc = (char *) get_data();
      char * pchDst = str.GetBufferSetLength(size * 2);
      uint64_t dwEnd = pos + size;
      for(uint64_t dw = pos; dw < dwEnd; dw++)
      {
         if(((pchSrc[dw] & 0xf0) >> 4) < 10)
            *pchDst = (char)(((pchSrc[dw] & 0xf0) >> 4) + '0');
         else
            *pchDst = (char)(((pchSrc[dw] & 0xf0) >> 4) + 'A' - 10);
         pchDst++;
         if(((pchSrc[dw] & 0x0f)) < 10)
            *pchDst = (char)((pchSrc[dw] & 0x0f) + '0');
         else
            *pchDst = (char)((pchSrc[dw] & 0x0f) + 'A' - 10);
         pchDst++;
      }
      str.ReleaseBuffer();
   }

   inline string memory_base::to_hex(memory_position pos, memory_size size)
   {

      string str;
      to_hex(str, pos, size);
      return str;

   }

   inline void memory_base::from_hex(const char * psz)
   {

      char ch;

      bool bOdd = false;

      strsize iLen = strlen(psz);

      bOdd = (iLen % 2) != 0;

      if(bOdd)
      {
         iLen++;
      }

      allocate(iLen / 2);

      char * pch = (char *) get_data();

      while(*psz != '\0')
      {

         ch = 0;

         if(bOdd)
         {

            bOdd = false;

         }
         else
         {

            if(*psz > '9')
               ch |= ((*psz - 'A' + 10) & 0x0f) << 4;
            else
               ch |= ((*psz - '0') & 0x0f) << 4;

            if(*psz == '\0')
               break;

            psz++;

         }

         if(*psz > '9')
            ch |= ((*psz - 'A' + 10) & 0x0f);
         else
            ch |= ((*psz - '0') & 0x0f);

         *pch = ch;

         psz++;

         pch++;

      }

   }

   inline void memory_base::to_asc(string & str)
   {

      string strTo;

      to_hex(strTo);

      char ch;

      strsize iLen = strTo.get_length() - 1;

      for(int32_t i = 0; i < iLen; i+=2)
      {

         if(strTo[i] <= '9')
            ch = (strTo[i] - '0') << 4;
         else
            ch = (strTo[i] - 'A' + 10) << 4;

         if(strTo[i + 1] <= '9')
            ch |= (strTo[i + 1] - '0');
         else
            ch |= (strTo[i + 1] - 'A' + 10);

         str += ch;

      }

   }

   inline void memory_base::from_asc(const char * psz)
   {

      string str;

      while(*psz)
      {

         char ch = ((*psz & 0xf0) >> 4);

         if(ch < 10)
            ch += '0';
         else
            ch += 'A' - 10;

         str += ch;

         ch = ((*psz & 0xf));

         if(ch < 10)
            ch += '0';
         else
            ch += 'A' - 10;

         str += ch;

         psz++;

      }

      from_hex(str);

   }


   inline void memory_base::from_string(const wchar_t * pwsz)
   {

      from_string(::str::international::unicode_to_utf8(pwsz));

   }

   inline void memory_base::from_string(const char * psz)
   {

      allocate(strlen(psz));

      memcpy(get_data(), psz, this->get_size());

   }

   inline void memory_base::from_string(const string & str)
   {

      allocate(str.length());

      memcpy(get_data(), str, this->get_size());

   }

   inline void memory_base::from_string(const var & var)
   {

      from_string((const string &) var.get_string());

   }

   inline void memory_base::to_string(string & str) const
   {

      LPSTR lpsz = str.GetBufferSetLength(this->get_size() + 1);

      memcpy(lpsz, get_data(), this->get_size());

      lpsz[this->get_size()] = '\0';

      str.ReleaseBuffer();

   }

   inline string memory_base::to_string() const
   {

      string str;

      to_string(str);

      return str;

   }

   inline void memory_base::move_and_grow(memory_offset offset)
   {

      move(offset, true);

   }

   inline void memory_base::move(memory_offset offset, bool bGrow)
   {

      if(offset > 0)
      {
         if(bGrow)
         {
            this->allocate_add_up(offset);
         }
         if((memory_size) offset > this->get_size())
            return;
         memmove(&this->get_data()[offset], this->get_data(), this->get_size() - offset);
      }
      else if(offset < 0)
      {
         offset = -offset;
         if(bGrow)
         {
            this->allocate_add_up(offset);
         }
         if((memory_size) offset > this->get_size())
            return;
         memmove(this->get_data(), &this->get_data()[offset], this->get_size() - offset);
      }

   }

   inline void memory_base::append(const memory_base & mem, memory_position iStart, memory_size iCount)
   {

      if((memory_offset)iStart < 0)
         *((memory_offset*)iStart) += this->get_size();

      if(iStart > this->get_size())
         return;

      if(iStart + iCount > this->get_size())
         iCount = this->get_size() - iStart - iCount;

      if(iCount <= 0)
         return;

      allocate_add_up(iCount);

      memcpy(&get_data()[this->get_size() - iCount], &mem.get_data()[iStart], (size_t) iCount);

   }


   inline void memory_base::append(const void * pdata, memory_size iCount)
   {

      if(iCount <= 0)
         return;

      allocate_add_up(iCount);

      memcpy(&get_data()[this->get_size() - iCount], pdata, (size_t) iCount);

   }

   inline void memory_base::assign(const void * pdata, memory_size iCount)
   {

      allocate(iCount);

      memcpy(get_data(), pdata, (size_t) iCount);

   }

   inline void memory_base::assign(const void * pdata, memory_position iStart, memory_size iCount)
   {

      allocate(iCount);

      memcpy(get_data(), &((LPBYTE)pdata)[iStart], (size_t) iCount);

   }

   inline void memory_base::append(memory_size iCount, uchar uch)
   {

      allocate_add_up(iCount);

      memory_position iStart = this->get_size() - iCount;

      memory_position iEnd = iStart + iCount -1;

      for(memory_position i = iStart; i <= iEnd; i++)
      {

         get_data()[i] = uch;

      }

   }

   inline void memory_base::assign(memory_size iCount, uchar uch)
   {

      allocate(iCount);

      memory_position iEnd = iCount - 1;

      for(memory_position i = 0; i <= iEnd; i++)
      {

         this->get_data()[i] = uch;

      }

   }

   inline uchar memory_base::operator [] (memory_size i) const
   {

      return this->get_data()[i];

   }

   inline uchar & memory_base::operator [] (memory_size i)
   {

      return this->get_data()[i];

   }

   inline memory_base::operator const byte *() const
   {

      return this->get_data();

   }

   inline memory_base::operator byte *()
   {

      return this->get_data();

   }

   inline memory_base::operator const void *() const
   {

      return this->get_data();

   }

   inline memory_base::operator void *()
   {

      return this->get_data();

   }

   inline void memory_base::assign(const char * psz)
   {

      return from_string(psz);

   }

#if defined(METROWIN) && defined(__cplusplus_winrt)

   inline Platform::Array < uchar, 1U > ^ memory_base::get_os_bytes(memory_position pos, memory_size size) const
   {
      if(pos > get_size())
         throw invalid_argument_exception(get_app());
      if(size < 0 || pos + size > get_size())
         size = get_size() - pos;
      return ref new Platform::Array < uchar, 1U > ((uchar *) &get_data()[pos], size);
   }

   inline ::Windows::Storage::Streams::IBuffer ^ memory_base::get_os_crypt_buffer(memory_position pos, memory_size size) const
   {
      return ::Windows::Security::Cryptography::CryptographicBuffer::CreateFromByteArray(get_os_bytes(pos, size));
   }

   inline ::Windows::Storage::Streams::IBuffer ^ memory_base::get_os_buffer(memory_position pos, memory_size size) const
   {
      ::Windows::Storage::Streams::DataWriter ^ writer = ref new ::Windows::Storage::Streams::DataWriter();
      writer->WriteBytes(get_os_bytes(pos, size));
      return writer->DetachBuffer();
   }


   inline void memory_base::set_os_bytes(Platform::Array < uchar, 1U > ^ a, memory_position pos, memory_size size)
   {
      
      if (a == nullptr)
         return;

      if(pos > a->Length)
         throw invalid_argument_exception(get_app());

      if(pos > a->Length)
         throw invalid_argument_exception(get_app());

      if(size < 0 || pos + size > a->Length)
         size = a->Length - pos;

      allocate(size);

      memcpy(get_data(), &a->Data[pos], size);

   }


   inline void memory_base::set_os_crypt_buffer(::Windows::Storage::Streams::IBuffer ^ ibuf, memory_position pos, memory_size size)
   {
      Platform::Array < uchar, 1U > ^ a = nullptr;
      ::Windows::Security::Cryptography::CryptographicBuffer::CopyToByteArray(ibuf, &a);
      return set_os_bytes(a, pos, size);
   }

   inline void memory_base::set_os_buffer(::Windows::Storage::Streams::IBuffer ^ ibuf, memory_position pos, memory_size size)
   {
      Platform::Array < uchar, 1U > ^ a = nullptr;
      (::Windows::Storage::Streams::DataReader::FromBuffer(ibuf))->ReadBytes(a);
      return set_os_bytes(a, pos, size);
   }

#elif defined(APPLEOS)

    inline CFDataRef memory_base::get_os_cf_data(memory_position pos, memory_size size) const
    {
        if(pos > get_size())
            throw invalid_argument_exception(get_app());
        if(pos + size > get_size())
            size = get_size() - pos;
        return CFDataCreate(kCFAllocatorDefault, (const UInt8 *) &get_data()[pos], (CFIndex) size);
    }

    inline void memory_base::set_os_cf_data(CFDataRef data, memory_position pos, memory_size size)
    {
        if(pos > CFDataGetLength(data))
            throw invalid_argument_exception(get_app());
        if(pos > CFDataGetLength(data))
            throw invalid_argument_exception(get_app());
        if(pos + size > CFDataGetLength(data))
            size = CFDataGetLength(data) - pos;
        allocate(size);
        memcpy(get_data(), &CFDataGetBytePtr(data)[pos] , size);
    }


#endif

   inline memory_base & memory_base::reverse()
   {
      if(this->get_data() != NULL)
      {
         ::mem_reverse(this->get_data(), this->get_size());
      }
      return *this;
   }
} // namespace primitive



