#pragma once

namespace primitive
{

   class shared_memory;
   template < class MEMORY >
   class memory_container;

   typedef INT_PTR memory_offset;
   typedef INT_PTR memory_position;
   typedef INT_PTR memory_size;

   class CLASS_DECL_ca shared_memory :
      virtual public ex1::serializable
   {
      friend memory_container < shared_memory >;
   public:
      void FullLoad(ex1::file &file);
   
      shared_memory(const shared_memory & memorystorage);
      shared_memory(memory_container < shared_memory > * pmsc = NULL, DWORD dwAllocationAddUp = 4096, UINT nAllocFlags = 0);
      shared_memory(memory_container < shared_memory > * pmsc, void * pMemory, memory_size dwSize);
      void Construct(memory_container < shared_memory > * pmsc, DWORD dwAllocationAddUp = 4096, UINT nAllocFlags = 0);
      virtual ~shared_memory();

      shared_memory & operator = (const shared_memory & s);

      void from_string(const wchar_t * pwsz);
      void from_string(const char * psz);
      void to_string(string & str);

      // shared primitive::memory interface
      virtual void SetHandle(HGLOBAL hGlobalMemory, BOOL bAllowGrow = TRUE);
      virtual BYTE* Alloc(SIZE_T nBytes);
      virtual BYTE* Realloc(BYTE* lpMem, SIZE_T nBytes);
      virtual void Free(BYTE* lpMem);



      void delete_begin(memory_size iSize);
      void eat_begin(void * pdata, memory_size iSize);
      void set_data(void * pdata, memory_size uiSize);
      void copy_from(const shared_memory * pstorage);
      bool IsEnabled() const;
      bool IsLocked() const;
      void Unlock();
      void Lock();


      void To(string & str, int iStart = 0, int iEnd = -1);
      void From(const char * psz);

      void ToAsc(string & str);
      void FromAsc(const char * psz);

      critical_section      m_csLock;
      bool                  m_bLock;
      bool                  m_bLockMode;
      LPBYTE GetAllocation() const;
      
      LPBYTE DetachStorage();
      memory_size GetStorageSize() const;
      bool operator ==(shared_memory & s);
      bool allocate(memory_size dwNewLength);
      void AllocateAddUp(memory_size dwAddUp);

      UINT read(ex1::file & file);

      virtual void write(ex1::output_stream & ostream);
      virtual void read(ex1::input_stream & ostream);

      virtual HGLOBAL Detach();


   protected:
      void _RemoveOffset();
      memory_offset      m_iOffset;
      LPBYTE            m_pbStorage;
      UINT m_nAllocFlags;
      HGLOBAL m_hGlobalMemory;
      BOOL m_bAllowGrow;
      memory_size         m_cbStorage;
      memory_size         m_dwAllocation;
      memory_size        m_dwAllocationAddUp;

      memory_container < shared_memory > * m_pmsc;

   };

} // namespace primitive