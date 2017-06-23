#pragma once


#include "aura/filesystem/file/file_serializable.h"


template < typename N >
inline int32_t msb(N n)
{

   int32_t i = sizeof(N) * 8;

   do
   {
      i--;
      if(n & (numeric_info < N >::unitary () << i))
         return i;

   }
   while(i > 0);

   return -1;

}


class bstring_manager;
class memory;


namespace primitive
{


   class memory_container;
   class shared_memory;
   class virtual_memory;

   class CLASS_DECL_AURA memory_base :
      virtual public object,
      public ::file::serializable
   {
   public:

      typedef bstring_manager manager;

      typedef byte value_type;


#if MEMDLEAK

   string m_strTag;

   int m_iLine;

#endif



      bool                    m_bOwn;
      LPBYTE                  m_pbStorage;
      LPBYTE                  m_pbComputed;

      memory_offset_t         m_iOffset;
      memory_offset_t         m_iMaxOffset;
      memory_size_t           m_cbStorage;
      memory_size_t           m_dwAllocation;
      double                  m_dAllocationRateUp;
      DWORD                   m_dwAllocationAddUp;

      memory_container *      m_pcontainer;

      sp(mutex)               m_spmutex;
      bool                    m_bLockMode;
      bool                    m_bLock;

      memory *                m_pprimitivememory;
      shared_memory *         m_psharedmemory;
      virtual_memory *        m_pvirtualmemory;


      memory_base();
      virtual ~memory_base();


      //virtual LPBYTE detach_primitive_memory();
      //virtual LPBYTE detach_virtual_memory();
      //virtual HGLOBAL detach_shared_memory();

      bool is_enabled() const;
      bool is_locked() const;

      virtual bool allocate(memory_size_t dwNewLength);
      virtual bool allocate_internal(memory_size_t dwNewLength);

      virtual LPBYTE impl_alloc(memory_size_t dwAllocation);
      virtual LPBYTE impl_realloc(void * pdata,memory_size_t dwAllocation);
      virtual void impl_free(LPBYTE pdata);

      virtual void reserve(memory_size_t dwNewLength);


      virtual void remove_offset();

      virtual void random_bytes(::count c = -1);

      //virtual void FullLoad(::file::file & buffer);

      //memory_size_t read(::file::file & buffer);


      virtual void write(::file::ostream & ostream) const;
      virtual void read(::file::istream & istream);


      virtual memory_size_t calc_allocation(memory_size_t size);


      virtual void transfer_to(::file::writer & writer, memory_size_t uiBufferSize = 1024 * 1024) const;
      virtual void transfer_from(::file::reader & reader, memory_size_t uiBufferSize = 1024 * 1024);
      virtual void transfer_from_begin(::file::reader & reader, memory_size_t uiBufferSize = 1024 * 1024);


      void allocate_add_up(memory_offset_t iAddUp);


      inline LPBYTE           internal_get_data() const;
      inline memory_size_t    get_size() const;
      inline const LPBYTE     get_data() const;
      inline LPBYTE           get_data();

      inline memory_size_t    size() const;
      inline const LPBYTE     data() const;
      inline LPBYTE           data();

      inline byte operator [] (uint64_t i) const;
      inline byte & operator [] (uint64_t i);
      inline byte operator [] (int i) const;
      inline byte & operator [] (int i);

      inline operator const byte *() const;
      inline operator byte *();

      inline operator const char *() const { return (const char *) operator const byte *(); }
      inline operator char *() { return (char *) operator byte *(); }

      inline operator const void *() const;
      inline operator void *();

      char *                  get_psz(strsize & len);


      memory_base & operator = (const memory_base & s);
      memory_base & operator += (const memory_base & s);


      void from_string(const unichar * pwsz);
      void from_string(const char * psz);
      void from_string(const string & str);
      void from_string(const var & var);
      void to_string(string & str, memory_position_t iStart = 0, memory_size_t uiSize = -1) const;
      string to_string(memory_position_t iStart = 0, memory_size_t uiSize = -1) const;

      void delete_begin(memory_size_t iSize);
      void eat_begin(void * pdata, memory_size_t iSize);
      void set_data(void * pdata, memory_size_t uiSize);
      void copy_from(const memory_base * pstorage);
      void set(byte b,memory_position_t iStart = 0,memory_size_t uiSize = -1);
      void zero(memory_position_t iStart = 0, memory_size_t uiSize = -1);

      void append(const memory_base & memory, memory_position_t iStart = 0, memory_size_t iCount = -1);
      void append(const void * pdata, memory_size_t iCount);
      void assign(const void * pdata, memory_size_t iCount);
      void assign(const void * pdata, memory_position_t iStart, memory_size_t iCount);
      void append(memory_size_t iCount, uchar uch);
      void assign(memory_size_t iCount, uchar uch);

      void splice(const byte * pbMemory, memory_offset_t iCountSrc, memory_offset_t iStartDst = 0, memory_offset_t iCountDst = 0);
      void splice(const memory_base & memory, memory_offset_t iStartDst = 0, memory_offset_t iCountDst = 0, memory_offset_t iStartSrc = 0, memory_offset_t iCountSrc = -1);

      void move_and_grow(memory_offset_t offset);
      void move(memory_offset_t offset, bool bGrow = false);

      void assign(const char * psz);



      void to_hex(string & str, memory_position_t iStart = 0, memory_size_t size = -1);
      string to_hex(memory_position_t iStart = 0, memory_size_t size = -1);
      void from_hex(const char * psz, strsize nCount = -1);

      void to_asc(string & str);
      void from_asc(const char * psz);

      bool operator == (const memory_base & s);


      memory_base & reverse();

      memory_base & prefix_der_uint_content();
      memory_base & prefix_der_length();
      memory_base & prefix_der_type(int32_t iType);

      memory_base & prefix_der_uint();
      memory_base & prefix_der_sequence();

      memory_size_t get_length() const;
      memory_size_t length() const;

      inline void set_char_at_grow(strsize iChar, char ch);


#if defined(METROWIN) && defined(__cplusplus_winrt)

      inline Array < uchar, 1U > ^ get_os_bytes(memory_position_t pos = 0, memory_size_t size = -1) const;
      inline ::Windows::Storage::Streams::IBuffer ^ get_os_crypt_buffer(memory_position_t pos = 0, memory_size_t size = -1) const;
      inline ::Windows::Storage::Streams::IBuffer ^ get_os_buffer(memory_position_t pos = 0, memory_size_t size = -1) const;
      inline void set_os_bytes(Array < uchar, 1U > ^ a, memory_position_t pos = 0, memory_size_t size = -1);
      inline void set_os_crypt_buffer(::Windows::Storage::Streams::IBuffer ^ ibuf, memory_position_t pos = 0, memory_size_t size = -1);
      inline void set_os_buffer(::Windows::Storage::Streams::IBuffer ^ ibuf, memory_position_t pos = 0, memory_size_t size = -1);

#elif defined(APPLEOS)

       CFDataRef get_os_cf_data(memory_position_t pos = 0, memory_size_t size = -1) const;
       void set_os_cf_data(CFDataRef data, memory_position_t pos = 0, memory_size_t size = -1);

#endif

       memory_base & erase(memory_offset_t pos = 0,memory_offset_t len = -1);

#ifdef WINDOWS
       IStream * CreateIStream();
#endif


   };


   inline LPBYTE memory_base::internal_get_data() const { return m_pbComputed; }
   inline memory_size_t memory_base::get_size() const { return m_cbStorage; }
   inline memory_size_t memory_base::size() const { return get_size(); }
   inline const LPBYTE memory_base::get_data() const { return m_pbComputed; }
   inline LPBYTE memory_base::get_data() { return m_pbComputed; }
   inline const LPBYTE memory_base::data() const { return get_data(); }
   inline LPBYTE memory_base::data() { return get_data(); }


   inline uchar memory_base::operator [] (uint64_t ui) const { return this->get_data()[(memory_position_t)ui]; }
   inline uchar & memory_base::operator [] (uint64_t ui) { return this->get_data()[(memory_position_t)ui]; }
   inline uchar memory_base::operator [] (int i) const { return this->get_data()[i]; }
   inline uchar & memory_base::operator [] (int i) { return this->get_data()[i]; }
   inline memory_base::operator const byte *() const { return this->get_data(); }
   inline memory_base::operator byte *() { return this->get_data(); }
   inline memory_base::operator const void *() const { return this->get_data(); }
   inline memory_base::operator void *() { return this->get_data(); }

   inline void memory_base::allocate_add_up(memory_offset_t iAddUp)
   {
      
      if (iAddUp != 0)
      {

         allocate(get_size() + iAddUp);

      }

   }

   inline void memory_base::splice(const memory_base & memory, memory_offset_t iStartDst, memory_offset_t iCountDst, memory_offset_t iStartSrc, memory_offset_t iCountSrc)
   {

      splice(
         &memory.get_data()[iStartSrc], 
         MIN(memory.get_size(), iCountSrc < 0 ? memory.get_size() - iCountSrc + 1 : iCountSrc), 
         iStartDst, 
         iCountDst);

   }


   inline void memory_base::set_char_at_grow(strsize iChar, char ch)
   {

      if (iChar >= get_size())
      {

         allocate(iChar + 1);

      }

      ((char*)get_data())[iChar] = ch;

   }


} // namespace primitive





















