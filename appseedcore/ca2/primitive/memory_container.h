#pragma once

namespace primitive
{

   template < class MEMORY = class primitive::memory>
   class memory_container :
      virtual public ::radix::object
   {
   protected:

   
      MEMORY *                               m_pmemorystorage;
      bool                                   m_bOwnStorage;
      primitive_array < void ** >            m_vppa;
      DWORD_PTR                              m_dwAllocationAddUp;


   public:

      memory_container(::ca::application * papp);
      memory_container(::ca::application * papp, void * pMemory, DWORD_PTR dwSize);
      memory_container(::ca::application * papp, MEMORY & storage);
      memory_container(const memory_container & container);
      virtual ~memory_container();


      void AllocateAddUp(DWORD_PTR dwAddUp);
      void allocate(DWORD_PTR dwNewLength);

      MEMORY * get_memory() const;

      DWORD_PTR get_size() const;

      void from_string(const wchar_t * pwsz);
      void from_string(const char * psz);
      void to_string(string & str);
   
      void FullLoad(MEMORY *pmemorystorage);
      void FullLoad(ex1::file & file);

      void KeepStoragePointer(void **ppvoid);

      void OffsetStorageKeptPointers(int iOffset);
       
      LPBYTE DetachStorage();

      LPBYTE GetAllocation();


      bool Lock();
      bool Unlock();

      bool IsValid() const;

      memory_container & operator =(const memory_container &container);

      bool Attach(MEMORY *pstorage);

      MEMORY * Detach();

   };






template < class MEMORY >
memory_container < MEMORY > ::memory_container(::ca::application * papp) :
   ca(papp)
{
   m_dwAllocationAddUp = 1024;
   m_pmemorystorage = NULL;
}

template < class MEMORY >
memory_container < MEMORY > ::memory_container(::ca::application * papp, void * pMemory, DWORD_PTR dwSize) :
   ca(papp)
{
   m_pmemorystorage = new MEMORY(this, pMemory, dwSize);
}

template < class MEMORY >
memory_container < MEMORY > ::memory_container(::ca::application * papp, MEMORY & storage) :
   ca(papp)
{
   m_bOwnStorage = false;
   m_pmemorystorage = &storage;
}

template < class MEMORY >
memory_container < MEMORY > ::memory_container(const memory_container & container) :
   ::radix::object(container)
{
   operator = (container);
}

template < class MEMORY >
memory_container < MEMORY > ::   ~memory_container()
   {
       if(m_bOwnStorage)
       {
           if(m_pmemorystorage != NULL)
           {
               delete m_pmemorystorage;
           }
       }
   }
template < class MEMORY >
   void memory_container < MEMORY > ::AllocateAddUp(DWORD_PTR dwAddUp)
   {
      allocate(get_size() + dwAddUp);
   }
template < class MEMORY >
   void memory_container < MEMORY > ::allocate(DWORD_PTR dwNewLength)
   {
      if(m_pmemorystorage == NULL)
      {
         m_pmemorystorage = new MEMORY(this);
         m_pmemorystorage->m_dwAllocationAddUp = m_dwAllocationAddUp;
         if(m_pmemorystorage == NULL)
         {
            throw new memory_exception;
         }
         m_bOwnStorage = true;
      }
      
      m_pmemorystorage->allocate(dwNewLength);
   }
template < class MEMORY >
   MEMORY * memory_container < MEMORY > ::get_memory() const
   {
       return m_pmemorystorage;
   }
template < class MEMORY >
   DWORD_PTR memory_container < MEMORY > ::get_size() const
   {
       return m_pmemorystorage->GetStorageSize();
   }
template < class MEMORY >
   void memory_container < MEMORY > ::from_string(const wchar_t * pwsz)
   {
      m_pmemorystorage->from_string(pwsz);
   }
template < class MEMORY >
   void memory_container < MEMORY > ::from_string(const char * psz)
   {
      m_pmemorystorage->from_string(psz);
   }
template < class MEMORY >
   void memory_container < MEMORY > ::to_string(string & str)
   {
      m_pmemorystorage->to_string(str);
   }

template < class MEMORY >
   void memory_container < MEMORY > ::FullLoad(MEMORY *pmemorystorage)
   {
      if(m_pmemorystorage == NULL)
      {
         m_pmemorystorage = new MEMORY(this);
         m_bOwnStorage = true;
      }

      m_pmemorystorage->copy_from(pmemorystorage);

   }
template < class MEMORY >
   void memory_container < MEMORY > ::FullLoad(ex1::file & file)
   {
       if(m_pmemorystorage == NULL)
       {
           m_pmemorystorage = new MEMORY(this);
           m_bOwnStorage = true;
       }

       m_pmemorystorage->FullLoad(file);
   }

template < class MEMORY >
   void memory_container < MEMORY > ::KeepStoragePointer(void **ppvoid)
   {
       m_vppa.add(ppvoid);
   }

template < class MEMORY >
   void memory_container < MEMORY > ::OffsetStorageKeptPointers(int iOffset)
   {
       for(int i = 0; i < m_vppa.get_size(); i++)
       {
           *m_vppa.element_at(i) =
               ((LPBYTE) *m_vppa.element_at(i)) + iOffset;
       }
   }
       
template < class MEMORY >
   LPBYTE memory_container < MEMORY > ::DetachStorage()
   {
      return m_pmemorystorage->DetachStorage();
   }

template < class MEMORY >
   LPBYTE memory_container < MEMORY > ::GetAllocation()
   {
      if(m_pmemorystorage == NULL)
         return NULL;
      else
         return m_pmemorystorage->GetAllocation();
   }


template < class MEMORY >
   bool memory_container < MEMORY > ::Lock()
   {
      if(m_pmemorystorage == NULL)
         return false;
      else
      {
         m_pmemorystorage->Lock();
         return true;
      }
   }

template < class MEMORY >
   bool memory_container < MEMORY > ::Unlock()
   {
      if(m_pmemorystorage == NULL)
         return false;
      else
      {
         m_pmemorystorage->Unlock();
         return true;
      }
   }

template < class MEMORY >
   bool memory_container < MEMORY > ::IsValid() const
   {
      return m_pmemorystorage != NULL;
   }

template < class MEMORY >
   memory_container < MEMORY > & memory_container < MEMORY > ::operator =(const memory_container &container)
   {
      m_bOwnStorage = container.m_bOwnStorage;
      if(container.m_pmemorystorage == NULL)
         m_pmemorystorage = NULL;
      else
      {
         m_pmemorystorage = new MEMORY(this);
         m_pmemorystorage->copy_from(container.m_pmemorystorage);
      }
      m_vppa.remove_all();
      return *this;
   }

template < class MEMORY >
   bool memory_container < MEMORY > ::Attach(MEMORY *pstorage)
   {
      ASSERT(pstorage != NULL);

      if(m_pmemorystorage != NULL)
      {
         if(m_bOwnStorage)
         {
            delete m_pmemorystorage;
         }
         m_pmemorystorage = NULL;
      }

      if(pstorage == NULL)
         return false;

      m_pmemorystorage = pstorage;

      m_bOwnStorage = true;
      
      return true;
   }

   template < class MEMORY >
   MEMORY * memory_container < MEMORY > ::Detach()
   {
      MEMORY * pstorage = m_pmemorystorage;

      m_pmemorystorage = NULL;

      m_bOwnStorage = false;

      return pstorage;
   }

} // namespace primitive



// vc6 workaround
typedef CLASS_DECL_ca ::primitive::memory_container < primitive::memory > primitive_memory_container;
