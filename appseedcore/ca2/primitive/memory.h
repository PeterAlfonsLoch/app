#pragma once

namespace primitive
{

   template < class MEMORY >
   class memory_container;

   typedef INT_PTR memory_offset;
   typedef INT_PTR memory_position;
   typedef INT_PTR memory_size;

   class CLASS_DECL_ca memory :
      virtual public ex1::serializable
   {
      friend memory_container < memory >;
   protected:


      memory_offset        m_iOffset;
      LPBYTE               m_pbStorage;
      memory_size            m_cbStorage;
      memory_size            m_dwAllocation;
      memory_size          m_dwAllocationAddUp;

      memory_container < memory > * m_pmsc;


   public:
   
      memory(const void *, int iCount);
      memory(const memory & memorystorage);
      memory(primitive::memory_container < memory > * pmsc = NULL, DWORD_PTR dwAllocationAddUp = 4096, UINT nAllocFlags = 0);
      memory(primitive::memory_container < memory > * pmsc, void * pMemory, memory_size dwSize);
      void Construct(primitive::memory_container < memory > * pmsc, DWORD_PTR dwAllocationAddUp = 4096, UINT nAllocFlags = 0);
      virtual ~memory();

      void FullLoad(ex1::file &file);

      memory & operator = (const memory & s);

      void from_string(const wchar_t * pwsz);

      void from_string(const char * psz);
      void to_string(string & str);

   public:
      void delete_begin(memory_size iSize);
      void eat_begin(void * pdata, memory_size iSize);
      void set_data(void * pdata, memory_size uiSize);
      void copy_from(const memory * pstorage);
      bool IsEnabled() const;
      bool IsLocked() const;
      void Unlock();
      void Lock();

      void append(const void * pdata, DWORD_PTR iCount);
      void assign(const void * pdata, DWORD_PTR iStart, DWORD_PTR iCount);
      void append(DWORD_PTR iCount, unsigned char uch);
      void assign(DWORD_PTR iCount, unsigned char uch);


      byte operator [] (int i) const;
      byte & operator [] (int i);

      operator const byte *() const;
      operator byte *();

      operator const void *() const;
      operator void *();

      void To(string & str, DWORD_PTR iStart = 0, DWORD_PTR iEnd = -1);
      void From(const char * psz);

      void ToAsc(string & str);
      void FromAsc(const char * psz);

      critical_section      m_csLock;
      bool                  m_bLock;
      bool                  m_bLockMode;
      LPBYTE GetAllocation() const;
      
      LPBYTE DetachStorage();
      memory_size GetStorageSize() const;
      memory_size get_size() const;
      bool operator ==(memory & s);
      bool allocate(memory_size dwNewLength);
      void AllocateAddUp(memory_size dwAddUp);

      UINT read(ex1::file & file);

      virtual void write(ex1::output_stream & ostream);
      virtual void read(ex1::input_stream & ostream);

   protected:

      void _RemoveOffset();


   };


} // namespace primitive