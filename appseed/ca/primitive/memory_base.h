#pragma once


namespace primitive
{


   class memory_container;


   class CLASS_DECL_ca base_memory :
      virtual public ex1::byte_serializable
   {
   public:

      
      LPBYTE                  m_pbStorage;

      memory_offset           m_iOffset;
      memory_size             m_cbStorage;
      memory_size             m_dwAllocation;
      memory_size             m_dwAllocationAddUp;

      memory_container *      m_pcontainer;

      sp(mutex)               m_spmutex;
      bool                    m_bLockMode;
      bool                    m_bLock;


      base_memory();
      virtual ~base_memory();


      inline bool is_enabled() const;
      inline bool is_locked() const;

      virtual bool allocate(memory_size dwNewLength);
      virtual bool allocate_internal(memory_size dwNewLength);

      virtual void            base_remove_offset();

      virtual void            base_from_string(const wchar_t * pwsz) = 0;
      virtual void            base_from_string(const char * psz) = 0;
      virtual void            base_from_string(const string & str) = 0;
      virtual void            base_from_string(const var & var) = 0;
      virtual void            base_to_string(string & str) const = 0;

      virtual void            base_copy_from(const base_memory * pstorage);

      virtual void FullLoad(ex1::file &file);

      inline ::primitive::memory_size read(ex1::file & file);

      inline void write(ex1::byte_output_stream & ostream);
      inline void read(ex1::byte_input_stream & ostream);

      inline  void allocate_add_up(memory_size dwAddUp);


      inline LPBYTE           internal_get_data() const;
      inline memory_size      get_size() const;
      inline const LPBYTE     get_data() const;
      inline LPBYTE           get_data();

   };







   inline bool base_memory::is_locked() const
   {

      if(m_spmutex.is_null())
         return false;
      else
         return m_spmutex->is_locked();

   }

   inline bool base_memory::is_enabled() const
   {

      if(m_bLockMode)
         return is_locked();
      else
         return true;

   }

   inline void base_memory::allocate_add_up(memory_size dwAddUp)
   {
      allocate(m_cbStorage + dwAddUp);
   }


   inline LPBYTE base_memory::internal_get_data() const
   {
      return m_pbStorage;
   }

   inline memory_size base_memory::get_size() const
   {
      return m_cbStorage;
   }


   
   inline const LPBYTE base_memory::get_data() const
   {

      if(is_enabled())
         return internal_get_data() + m_iOffset;
      else
      {
         ASSERT(FALSE);
         return NULL;
      }

   }

   inline LPBYTE base_memory::get_data()
   {

      if(is_enabled())
         return internal_get_data() + m_iOffset;
      else
      {
         ASSERT(FALSE);
         return NULL;
      }

   }

























   template < class BASE_MEMORY >
   class memory_base :
      virtual public BASE_MEMORY
   {
   public:


      memory_base();
      virtual ~memory_base();


      memory_base & operator = (const memory_base & s);
      memory_base & operator = (const base_memory & s);


      
      inline void from_string(const wchar_t * pwsz);
      inline void from_string(const char * psz);
      inline void from_string(const string & str);
      inline void from_string(const var & var);
      inline void to_string(string & str) const;

      inline void delete_begin(memory_size iSize);
      inline void eat_begin(void * pdata, memory_size iSize);
      inline void set_data(void * pdata, memory_size uiSize);
      inline void copy_from(const memory_base * pstorage);

      inline void append(const void * pdata, memory_size iCount);
      inline void assign(const void * pdata, memory_position iStart, memory_size iCount);
      inline void append(memory_size iCount, unsigned char uch);
      inline void assign(memory_size iCount, unsigned char uch);

      inline void _RemoveOffset();

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
      inline bool operator == (const base_memory & s);



      //inline bool allocate_internal(memory_size dwNewLength);


      virtual void *          base_get_data();
      virtual const void *    base_get_data() const;
      virtual memory_size     base_get_size() const;
      virtual void            base_remove_offset();

      inline void             base_from_string(const wchar_t * pwsz);
      inline void             base_from_string(const char * psz);
      inline void             base_from_string(const string & str);
      inline void             base_from_string(const var & var);
      inline void             base_to_string(string & str) const;

      virtual void            base_copy_from(const base_memory * pstorage);


   };


   template < class BASE_MEMORY >
   memory_base < BASE_MEMORY >::memory_base()
   {


   }


   template < class BASE_MEMORY >
   memory_base < BASE_MEMORY >::~memory_base()
   {
   }


   
   /*
   template < class BASE_MEMORY >
   inline LPBYTE memory_base < BASE_MEMORY >::internal_get_data() const
   {
      return NULL;
   }
   */

   template < class BASE_MEMORY >
   inline bool memory_base < BASE_MEMORY >::operator == (const memory_base& s)
   {

      bool b = false;

      single_lock sl(m_spmutex);

      sl.lock();

      if(this->get_size() == s.get_size())
         b = memcmp(get_data(), s.get_data(), (size_t) this->get_size()) == 0;

      sl.unlock();

      return b;

   }

   template < class BASE_MEMORY >
   inline bool memory_base < BASE_MEMORY >::operator == (const base_memory & s)
   {

      bool b = false;

      single_lock sl(m_spmutex);

      sl.lock();

      if(this->get_size() == s.get_size())
         b = memcmp(get_data(), s.get_data(), (size_t) this->get_size()) == 0;

      sl.unlock();

      return b;

   }

/*   template < class BASE_MEMORY >
   bool memory_base < BASE_MEMORY >::allocate_internal(memory_size dwNewLength)
   {
      UNREFERENCED_PARAMETER(dwNewLength);
      return false;
   }*/



   template < class BASE_MEMORY >
   inline void memory_base < BASE_MEMORY >::copy_from(const memory_base *pstorage)
   {
      ASSERT(pstorage != NULL);
      allocate(pstorage->get_size());
      memcpy(get_data(), pstorage->get_data(), (size_t) this->get_size());
   }

   template < class BASE_MEMORY >
   inline void memory_base < BASE_MEMORY >::base_copy_from(const base_memory *pstorage)
   {
      ASSERT(pstorage != NULL);
      allocate(pstorage->get_size());
      memcpy(get_data(), pstorage->get_data(), (size_t) this->get_size());
   }

   template < class BASE_MEMORY >
   inline void memory_base < BASE_MEMORY >::set_data(void *pdata, memory_size uiSize)
   {
      allocate(uiSize);
      memcpy(get_data(), pdata, (size_t) uiSize);
   }

   template < class BASE_MEMORY >
   inline void memory_base < BASE_MEMORY >::delete_begin(memory_size iSize)
   {
      ASSERT(iSize >= 0);
      ASSERT(iSize <= this->get_size());
      if(iSize >= 0 &&
         iSize <= this->get_size())
      {
         m_iOffset += iSize;
         if(m_pcontainer != NULL)
         {
            m_pcontainer->offset_kept_pointers((::primitive::memory_offset) iSize);
         }
         m_cbStorage -= iSize;
      }
   }

   template < class BASE_MEMORY >
   inline void memory_base < BASE_MEMORY >::eat_begin(void * pdata, memory_size iSize)
   {
      ASSERT(iSize >= 0);
      ASSERT(iSize <= this->get_size());
      if(iSize >= 0 &&
         iSize <= this->get_size())
      {
         memcpy(pdata, get_data(), (size_t) iSize);
         delete_begin(iSize);
      }
   }

   template < class BASE_MEMORY >
   inline void memory_base < BASE_MEMORY >::_RemoveOffset()
   {
      if(get_data() != NULL && m_cbStorage > (uint64_t) m_iOffset)
      {
         memmove(get_data(), get_data() + m_iOffset, (size_t) (m_cbStorage - m_iOffset));
      }
      m_iOffset = 0;
   }

   template < class BASE_MEMORY >
   void memory_base < BASE_MEMORY >::base_remove_offset()
   {
      _RemoveOffset();
   }

   template < class BASE_MEMORY >
   inline memory_base < BASE_MEMORY > & memory_base < BASE_MEMORY >::operator = (const memory_base & s)
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

   template < class BASE_MEMORY >
   inline memory_base < BASE_MEMORY > & memory_base < BASE_MEMORY >::operator = (const base_memory & s)
   {
      if(&s == NULL)
      {
         allocate(0);
      }
      else if(this != &s)
      {
         base_copy_from(&s);
      }
      return *this;
   }


   template < class BASE_MEMORY >
   inline void memory_base < BASE_MEMORY >::To(string & str, memory_position dwStart, memory_position dwEnd)
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

   template < class BASE_MEMORY >
   inline void memory_base < BASE_MEMORY >::From(const char * psz)
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

   template < class BASE_MEMORY >
   inline void memory_base < BASE_MEMORY >::ToAsc(string & str)
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
   
   template < class BASE_MEMORY >
   inline void memory_base < BASE_MEMORY >::FromAsc(const char * psz)
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


   template < class BASE_MEMORY >
   inline void memory_base < BASE_MEMORY >::from_string(const wchar_t * pwsz)
   {

      from_string(gen::international::unicode_to_utf8(pwsz));

   }

   template < class BASE_MEMORY >
   void memory_base < BASE_MEMORY >::base_from_string(const wchar_t * pwsz)
   {

      from_string(pwsz);

   }

   template < class BASE_MEMORY >
   inline void memory_base < BASE_MEMORY >::from_string(const char * psz)
   {

      allocate(strlen(psz));

      memcpy(get_data(), psz, this->get_size());

   }

   template < class BASE_MEMORY >
   void memory_base < BASE_MEMORY >::base_from_string(const char * psz)
   {

      from_string(psz);

   }

   template < class BASE_MEMORY >
   inline void memory_base < BASE_MEMORY >::from_string(const string & str)
   {

      allocate(str.length());

      memcpy(get_data(), str, this->get_size());

   }

   template < class BASE_MEMORY >
   void memory_base < BASE_MEMORY >::base_from_string(const string & str)
   {

      from_string(str);

   }


   template < class BASE_MEMORY >
   inline void memory_base < BASE_MEMORY >::from_string(const var & var)
   {

      from_string((const string &) var.get_string());

   }

   template < class BASE_MEMORY >
   void memory_base < BASE_MEMORY >::base_from_string(const var & var)
   {

      from_string(var);

   }


   template < class BASE_MEMORY >
   inline void memory_base < BASE_MEMORY >::to_string(string & str) const
   {

      LPTSTR lpsz = str.GetBufferSetLength(this->get_size() + 1);

      memcpy(lpsz, get_data(), this->get_size());

      lpsz[this->get_size()] = '\0';

      str.ReleaseBuffer();

   }

   template < class BASE_MEMORY >
   void memory_base < BASE_MEMORY >::base_to_string(string & str) const
   {

      to_string(str);

   }


   template < class BASE_MEMORY >
   inline void memory_base < BASE_MEMORY >::append(const void * pdata, memory_size iCount)
   {

      if(iCount <= 0)
         return;

      allocate_add_up(iCount);

      memcpy(&get_data()[this->get_size() - iCount], pdata, (size_t) iCount);

   }

   template < class BASE_MEMORY >
   inline void memory_base < BASE_MEMORY >::assign(const void * pdata, memory_position iStart, memory_size iCount)
   {

      if(iCount < 0)
         iCount = 0;

      allocate(iCount);

      memcpy(get_data(), &((LPBYTE)pdata)[iStart], (size_t) iCount);

   }

   template < class BASE_MEMORY >
   inline void memory_base < BASE_MEMORY >::append(memory_size iCount, unsigned char uch)
   {

      if(iCount < 0)
         iCount = 0;

      allocate_add_up(iCount);

      memory_position iStart = this->get_size() - iCount;

      memory_position iEnd = iStart + iCount -1;

      for(memory_position i = iStart; i <= iEnd; i++)
      {

         get_data()[i] = uch;

      }

   }

   template < class BASE_MEMORY >
   inline void memory_base < BASE_MEMORY >::assign(memory_size iCount, unsigned char uch)
   {

      if(iCount < 0)
         iCount = 0;

      allocate(iCount);

      memory_position iEnd = iCount - 1;

      for(memory_position i = 0; i <= iEnd; i++)
      {

         this->get_data()[i] = uch;

      }

   }

   template < class BASE_MEMORY >
   inline unsigned char memory_base < BASE_MEMORY >::operator [] (memory_size i) const
   {

      return this->get_data()[i];

   }

   template < class BASE_MEMORY >
   inline unsigned char & memory_base < BASE_MEMORY >::operator [] (memory_size i)
   {

      return this->get_data()[i];

   }

   template < class BASE_MEMORY >
   memory_base < BASE_MEMORY >::operator const byte *() const
   {

      return this->get_data();

   }

   template < class BASE_MEMORY >
   memory_base < BASE_MEMORY >::operator byte *()
   {

      return this->get_data();

   }

   template < class BASE_MEMORY >
   memory_base < BASE_MEMORY >::operator const void *() const
   {

      return this->get_data();

   }

   template < class BASE_MEMORY >
   memory_base < BASE_MEMORY >::operator void *()
   {

      return this->get_data();

   }

   template < class BASE_MEMORY >
   void * memory_base < BASE_MEMORY >::base_get_data()
   {

      return this->get_data();

   }

   template < class BASE_MEMORY >
   const void * memory_base < BASE_MEMORY >::base_get_data() const
   {

      return this->get_data();

   }

   template < class BASE_MEMORY >
   memory_size memory_base < BASE_MEMORY >::base_get_size() const
   {

      return this->get_size();

   }

} // namespace primitive


