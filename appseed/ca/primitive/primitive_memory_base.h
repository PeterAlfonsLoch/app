#pragma once


namespace primitive
{


   class memory_container;


   class CLASS_DECL_ca memory_base :
      public ::radix::object,
      public ex1::byte_serializable
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


      memory_base();
      virtual ~memory_base();


      inline bool is_enabled() const;
      inline bool is_locked() const;

      virtual bool allocate(memory_size dwNewLength);
      virtual bool allocate_internal(memory_size dwNewLength);

      virtual void remove_offset();

      virtual void FullLoad(ex1::file &file);

      inline ::primitive::memory_size read(ex1::file & file);

      void write(ex1::byte_output_stream & ostream);
      void read(ex1::byte_input_stream & ostream);

      inline  void allocate_add_up(memory_size dwAddUp);


      inline LPBYTE           internal_get_data() const;
      inline memory_size      get_size() const;
      inline const LPBYTE     get_data() const;
      inline LPBYTE           get_data();


      memory_base & operator = (const memory_base & s);


      inline void from_string(const wchar_t * pwsz);
      inline void from_string(const char * psz);
      inline void from_string(const string & str);
      inline void from_string(const var & var);
      inline void to_string(string & str) const;

      void delete_begin(memory_size iSize);
      inline void eat_begin(void * pdata, memory_size iSize);
      inline void set_data(void * pdata, memory_size uiSize);
      inline void copy_from(const memory_base * pstorage);

      inline void append(const void * pdata, memory_size iCount);
      inline void assign(const void * pdata, memory_position iStart, memory_size iCount);
      inline void append(memory_size iCount, unsigned char uch);
      inline void assign(memory_size iCount, unsigned char uch);

      inline byte operator [] (memory_size i) const;
      inline byte & operator [] (memory_size i);

      inline operator const byte *() const;
      inline operator byte *();

      inline operator const char *() const { return (const char *) operator const byte *(); }
      inline operator char *() { return (char *) operator byte *(); }

      inline operator const void *() const;
      inline operator void *();


      inline void To(string & str, memory_position iStart = 0, memory_position iEnd = -1);
      inline void From(const char * psz);

      inline void ToAsc(string & str);
      inline void FromAsc(const char * psz);

      inline bool operator == (const memory_base & s);


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

   inline void memory_base::To(string & str, memory_position dwStart, memory_position dwEnd)
   {
      dwStart = max(dwStart, 0);
      if(dwEnd == ((memory_position)(-1)))
         dwEnd = this->get_size() - 1;
      char * pch = (char *) get_data();
      for(uint64_t dw = dwStart; dw <= dwEnd; dw++)
      {
         if(((pch[dw] & 0xf0) >> 4) < 10)
            str += (char)(((pch[dw] & 0xf0) >> 4) + '0');
         else
            str += (char)(((pch[dw] & 0xf0) >> 4) + 'A' - 10);
         if(((pch[dw] & 0x0f)) < 10)
            str += (char)((pch[dw] & 0x0f) + '0');
         else
            str += (char)((pch[dw] & 0x0f) + 'A' - 10);
      }
   }

   inline void memory_base::From(const char * psz)
   {

      char ch;

      strsize iLen = strlen(psz);

      allocate(iLen / 2);

      char * pch = (char *) get_data();

      while(*psz != '\0')
      {

         ch = 0;

         if(*psz > '9')
            ch |= ((*psz - 'A' + 10) & 0x0f) << 4;
         else
            ch |= ((*psz - '0') & 0x0f) << 4;

         if(*psz == '\0')
            break;

         psz++;

         if(*psz > '9')
            ch |= ((*psz - 'A' + 10) & 0x0f);
         else
            ch |= ((*psz - '0') & 0x0f);

         *pch = ch;

         psz++;

         pch++;

      }

   }

   inline void memory_base::ToAsc(string & str)
   {

      string strTo;

      To(strTo);

      char ch;

      strsize iLen = strTo.get_length() - 1;

      for(int i = 0; i < iLen; i+=2)
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

   inline void memory_base::FromAsc(const char * psz)
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

      From(str);

   }


   inline void memory_base::from_string(const wchar_t * pwsz)
   {

      from_string(gen::international::unicode_to_utf8(pwsz));

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

      LPTSTR lpsz = str.GetBufferSetLength(this->get_size() + 1);

      memcpy(lpsz, get_data(), this->get_size());

      lpsz[this->get_size()] = '\0';

      str.ReleaseBuffer();

   }

   inline void memory_base::append(const void * pdata, memory_size iCount)
   {

      if(iCount <= 0)
         return;

      allocate_add_up(iCount);

      memcpy(&get_data()[this->get_size() - iCount], pdata, (size_t) iCount);

   }

   inline void memory_base::assign(const void * pdata, memory_position iStart, memory_size iCount)
   {

      allocate(iCount);

      memcpy(get_data(), &((LPBYTE)pdata)[iStart], (size_t) iCount);

   }

   inline void memory_base::append(memory_size iCount, unsigned char uch)
   {

      allocate_add_up(iCount);

      memory_position iStart = this->get_size() - iCount;

      memory_position iEnd = iStart + iCount -1;

      for(memory_position i = iStart; i <= iEnd; i++)
      {

         get_data()[i] = uch;

      }

   }

   inline void memory_base::assign(memory_size iCount, unsigned char uch)
   {

      allocate(iCount);

      memory_position iEnd = iCount - 1;

      for(memory_position i = 0; i <= iEnd; i++)
      {

         this->get_data()[i] = uch;

      }

   }

   inline unsigned char memory_base::operator [] (memory_size i) const
   {

      return this->get_data()[i];

   }

   inline unsigned char & memory_base::operator [] (memory_size i)
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


} // namespace primitive



