#include "framework.h"


namespace primitive
{


   memory_container ::memory_container(sp(::axis::application) papp) :
      element(papp)
   {
      
//      m_spmemory = canew(primitive::memory(papp));
      
      m_dwAllocationAddUp = 1024;
      
   }


   memory_container ::memory_container(sp(::axis::application) papp, void * pmemory, memory_size dwSize) :
      element(papp)
   {
      m_spmemory = canew(primitive::memory(this, pmemory, dwSize));
   }


   memory_container ::memory_container(sp(::axis::application) papp, memory_base * pmemory) :
      element(papp)
   {
      m_spmemory = pmemory;
   }


   memory_container ::memory_container(const memory_container & container) :
      object(container)
   {
      operator = (container);
   }


   memory_container ::   ~memory_container()
   {
   }


   void memory_container ::allocate_add_up(memory_size dwAddUp)
   {
      allocate(this->get_size() + dwAddUp);
   }


   void memory_container::allocate(memory_size dwNewLength)
   {

      if(dwNewLength <= 0)
      {

         if(m_spmemory.is_set())
         {

            if(!m_spmemory->allocate(dwNewLength))
            {

               throw memory_exception(get_app());

            }

         }

         return;
      }

      if(m_spmemory.is_null())
      {

         m_spmemory = new primitive::memory(this);

         if(m_spmemory.is_null())
         {

            throw memory_exception(get_app());

         }

         m_spmemory->m_dwAllocationAddUp = m_dwAllocationAddUp;

      }

      if(!m_spmemory->allocate(dwNewLength))
      {

         throw memory_exception(get_app());

      }

   }


   void memory_container ::allocate_internal(memory_size dwNewLength)
   {
      if(m_spmemory == NULL)
      {
         m_spmemory = new primitive::memory(this);
         if(m_spmemory.is_null())
         {
            throw new memory_exception(get_app());
         }
         m_spmemory->m_dwAllocationAddUp = m_dwAllocationAddUp;
      }
      m_spmemory->allocate_internal(dwNewLength);
   }


   memory_base * memory_container::get_memory()
   {

      if(m_spmemory.is_null())
      {
         m_spmemory = create_memory();
      }

      return m_spmemory;

   }

   ::primitive::memory_base * memory_container::create_memory()
   {

      return canew(primitive::memory(this));

   }




   void memory_container ::read(memory_base * pmemory)
   {
      if(m_spmemory.is_null())
      {
         m_spmemory = new primitive::memory(this);
      }
      m_spmemory->copy_from(pmemory);
   }


   void memory_container ::read(::file::input_stream & is)
   {
      if(m_spmemory.is_null())
      {
         m_spmemory = new primitive::memory(this);
      }
      m_spmemory->read(is);
   }


   void memory_container ::keep_pointer(void **ppvoid)
   {
         m_vppa.add(ppvoid);
   }


   void memory_container ::offset_kept_pointers(memory_offset iOffset)
   {
      for(int32_t i = 0; i < m_vppa.get_size(); i++)
      {
         *m_vppa.element_at(i) = ((LPBYTE) *m_vppa.element_at(i)) + iOffset;
      }
   }

   bool memory_container ::IsValid() const
   {
      return true;
   }


   memory_container & memory_container ::operator =(const memory_container &container)
   {
      if(container.m_spmemory.is_null())
         m_spmemory.release();
      else
      {
         m_spmemory = new primitive::memory(this);
         m_spmemory->copy_from(container.m_spmemory);
      }
      m_vppa.remove_all();
      return *this;
   }


   bool memory_container ::attach(memory_base * pstorage)
   {

      m_spmemory = pstorage;

      return true;

   }


   memory_base * memory_container::detach()
   {

      return m_spmemory.detach();

   }


   memory *          memory_container::get_primitive_memory()
   {
      
      if (m_spmemory.is_null())
         m_spmemory = canew(::primitive::memory(get_app()));

      return m_spmemory->m_pprimitivememory;

   }


#if !defined(METROWIN)
   shared_memory *   memory_container::get_shared_memory()
   {
      return m_spmemory->m_psharedmemory;
   }
#endif

   virtual_memory *  memory_container::get_virtual_memory()
   {
      return m_spmemory->m_pvirtualmemory;
   }


   memory *          memory_container::detach_primitive_memory()
   {
      ::primitive::memory_base * pmemorybase = m_spmemory.detach();
      if(pmemorybase != NULL)
         return NULL;
      ::primitive::memory * pmemory = pmemorybase->m_pprimitivememory;
      if(pmemory != NULL)
      {
         return pmemory;
      }
      pmemory = new ::primitive::memory(*pmemorybase);
      delete pmemorybase;
      return pmemory;
   }

#if !defined(METROWIN)
   shared_memory *   memory_container::detach_shared_memory()
   {
      ::primitive::memory_base * pmemorybase = m_spmemory.detach();
      if(pmemorybase != NULL)
         return NULL;
      ::primitive::shared_memory * psharedmemory = pmemorybase->m_psharedmemory;
      if(psharedmemory != NULL)
      {
         return psharedmemory;
      }
      psharedmemory = new ::primitive::shared_memory(*pmemorybase);
      delete pmemorybase;
      return psharedmemory;
   }
#endif

   virtual_memory *  memory_container::detach_virtual_memory()
   {
      ::primitive::memory_base * pmemorybase = m_spmemory.detach();
      if(pmemorybase != NULL)
         return NULL;
      ::primitive::virtual_memory * pvirtualmemory = pmemorybase->m_pvirtualmemory;
      if(pvirtualmemory != NULL)
      {
         return pvirtualmemory;
      }
      pvirtualmemory = new ::primitive::virtual_memory(*pmemorybase);
      delete pmemorybase;
      return pvirtualmemory;
   }


   LPBYTE            memory_container::detach_primitive_storage()
   {
      ::primitive::memory * pmemory = detach_primitive_memory();
      LPBYTE p = pmemory->detach();
      delete pmemory;
      return p;
   }

#if !defined(METROWIN)
   HGLOBAL           memory_container::detach_shared_storage()
   {
      ::primitive::shared_memory * psharedmemory = detach_shared_memory();
      HGLOBAL h = psharedmemory->detach();
      delete psharedmemory;
      return h;
   }
#endif

   LPBYTE            memory_container::detach_virtual_storage()
   {
      ::primitive::virtual_memory * pvirtualmemory = detach_virtual_memory();
      LPBYTE p = pvirtualmemory->detach();
      delete pvirtualmemory;
      return p;
   }

   void memory_container::str(const string & str)
   {

      allocate(str.get_length());

      memcpy(get_data(), str, get_size());

   }



} // namespace primitive



