#pragma once


class strid_array;
class mutex;


extern CLASS_DECL_AXIS mutex * g_pmutexFactory;


class CLASS_DECL_AXIS factory_allocator :
   virtual public ::object
{
public:


   uint32_t                      m_uiAllocSize;
   int32_t                       m_iCount;
   int64_t                       m_iAllocCount;
   id                            m_idType;
   bool                          m_bAligned;


   factory_allocator(sp(::axis::application) papp, int32_t iCount, UINT uiAllocSize, id idType, bool bAligned) :
      element(papp),
      m_iCount(iCount),
      m_uiAllocSize(uiAllocSize),
      m_idType(idType),
      m_bAligned(bAligned)
   {
      m_iAllocCount = 0;
   }

   virtual ~factory_allocator() {}

   inline void * alloc()
   {
      m_iAllocCount++;
      if(m_bAligned)
      {
#if MEMDLEAK
         return aligned_memory_alloc_dbg(m_uiAllocSize, 0, "typeid://" + *m_idType.m_pstr, 0);
#else
         return aligned_memory_alloc(m_uiAllocSize);
#endif
      }
      else
      {
#if MEMDLEAK
         return memory_alloc_dbg(m_uiAllocSize, 0, "typeid://" + *m_idType.m_pstr, 0);
#else
         return memory_alloc(m_uiAllocSize);
#endif
      }
   }


   virtual void discard(element * pca) = 0;

};


template < class TYPE >
class factory_allocator_impl :
   public factory_allocator
{
public:

#ifdef WINDOWS
   factory_allocator_impl(sp(::axis::application) papp, int32_t iCount, bool bAligned) :
      factory_allocator(papp, iCount, sizeof(TYPE), typeid(TYPE).name(), bAligned)
   {
   }
#else
   factory_allocator_impl(sp(::axis::application) papp, int32_t iCount, bool bAligned) :
      factory_allocator(papp, iCount, sizeof(TYPE), typeid(TYPE).name(), bAligned)
   {
   }
#endif

   virtual void discard(element * pca)
   {
      TYPE * ptype = (TYPE *) pca->m_pthis;
      if(ptype == NULL)
         return;
      try
      {
         ptype->~TYPE();
      }
      catch(...)
      {
      }
      synch_lock sl(g_pmutexFactory);
      try
      {
         memory_free(ptype);
         m_iAllocCount--;
      }
      catch(...)
      {
      }
      //m_alloc.Free(ptype);
   }
};


class CLASS_DECL_AXIS factory_item_base :
   virtual public ::object
{
public:

   sp(factory_allocator)    m_pallocator;

   inline factory_item_base(sp(::axis::application) papp, sp(factory_allocator) pallocator) : element(papp), m_pallocator(pallocator) {}
   virtual ~factory_item_base();

   
   using ::object::create;
   virtual sp(element) create(sp(::axis::application) papp) = 0;
   
   using ::object::clone;
   virtual sp(element) clone(sp(element) pobject) = 0;

};

template < class CREATABLE_TYPE >
class creatable_factory_item :
   public factory_item_base
{
public:

   inline creatable_factory_item(sp(::axis::application) papp, sp(factory_allocator) pallocator) : element(papp), factory_item_base(papp, pallocator) {}

   using ::factory_item_base::create;
   virtual sp(element) create(sp(::axis::application) papp);

   using ::factory_item_base::clone;
   virtual sp(element) clone(sp(element) pobject);

};

template < class CLONEABLE_TYPE >
class cloneable_factory_item :
   public creatable_factory_item < CLONEABLE_TYPE >
{
public:

   inline cloneable_factory_item(sp(::axis::application) papp, sp(factory_allocator) pallocator) : element(papp), creatable_factory_item < CLONEABLE_TYPE > (papp, pallocator) {}

   
   using creatable_factory_item < CLONEABLE_TYPE >::clone;
   virtual sp(element) clone(sp(element) pobject);

};



class CLASS_DECL_AXIS axis_factory :
   virtual public ::object
{
public:


   bool                             m_bSimpleFactoryRequest;
   spa(type)             m_typeinfoptraSimpleFactoryRequest;



   axis_factory(sp(::axis::application) papp);
   virtual ~axis_factory();



   template < class T >
   void creatable_small(bool bOverwrite = true, bool bAligned = false)
   {
      creatable < T > (32, bOverwrite, bAligned);
   }

   template < class T >
   void cloneable_small(bool bOverwrite = true, bool bAligned = false)
   {
      cloneable < T > (32, bOverwrite, bAligned);
   }

   template < class T >
   void creatable_large(bool bOverwrite = true, bool bAligned = false)
   {
      creatable < T > (1024, bOverwrite, bAligned);
   }

   template < class T >
   void cloneable_large(bool bOverwrite = true, bool bAligned = false)
   {
      cloneable < T > (1024, bOverwrite, bAligned);
   }

   template < class T >
   void creatable_small(sp(type) info, bool bOverwrite = true, bool bAligned = false)
   {
      creatable < T > (info, 32, bOverwrite, bAligned);
   }

   template < class T >
   void cloneable_small(sp(type) info, bool bOverwrite = true, bool bAligned = false)
   {
      cloneable < T > (info, 32, bOverwrite, bAligned);
   }

   template < class T >
   void creatable_large(sp(type) info, bool bOverwrite = true, bool bAligned = false)
   {
      creatable < T > (info, 1024, bOverwrite, bAligned);
   }

   template < class T >
   void cloneable_large(sp(type) info, bool bOverwrite = true, bool bAligned = false)
   {
      cloneable < T > (info, 1024, bOverwrite, bAligned);
   }

   template < class T >
   void creatable(int32_t iCount, bool bOverwrite = true, bool bAligned = false);

   template < class T >
   void cloneable(int32_t iCount, bool bOverwrite = true, bool bAligned = false);

   template < class T >
   void creatable(sp(type) info, int32_t iCount, bool bOverwrite = true, bool bAligned = false);

   template < class T >
   void cloneable(sp(type)  info, int32_t iCount, bool bOverwrite = true, bool bAligned = false);

   using ::object::create;
   virtual sp(element) create(sp(::axis::application) papp, sp(type) info);
   
   virtual sp(element) axis_clone(sp(element) pobject);

   virtual sp(element) typed_clone(id idType, sp(element) pobject);
   
   using ::object::clone;
   template < class T >
   sp(T) clone(sp(T) pobject)
   {
#ifdef WINDOWSEX
      return typed_clone(typeid(T).raw_name(), pobject);
#else
      return typed_clone(typeid(T).name(),pobject);
#endif
   }

   template < class T >
   sp(factory_allocator) get_allocator(int32_t iCount, bool bAligned);


   bool is_set(const char * pszType);

   void set_at(const char * pszType, factory_item_base * pitem);
   void set_at(const char * pszType, sp(factory_allocator) pitem);

   sp(factory_allocator) get_allocator(const char * pszType);

   void discard(sp(element) pobject);

   void enable_simple_factory_request(bool bEnable = true);


private:
   sp(mutex)                                                   m_pmutex;
   sp(strid_array)                                             m_pstrida;
   spa(factory_item_base)                                      m_itemptra;
   sp(strid_array)                                             m_pstridaAllocator;
   spa(factory_allocator)                                      m_itemptraAllocator;
};



