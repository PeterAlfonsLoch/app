#pragma once


class strid_array;
class mutex;


extern CLASS_DECL_AURA mutex * g_pmutexFactory;

CLASS_DECL_AURA bool safe_destroy_element(element * pelement);

CLASS_DECL_AURA bool safe_free_memory(void * ptype);

class CLASS_DECL_AURA factory_allocator :
   virtual public ::object
{
public:


   uint32_t                      m_uiAllocSize;
   int32_t                       m_iCount;
   int64_t                       m_iAllocCount;
   id                            m_idType;
   bool                          m_bAligned;


   factory_allocator(::aura::application * papp, int32_t iCount, UINT uiAllocSize, id idType, bool bAligned) :
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
   factory_allocator_impl(::aura::application * papp, int32_t iCount, bool bAligned) :
      factory_allocator(papp, iCount, sizeof(TYPE), typeid(TYPE).name(), bAligned)
   {
   }
#else
   factory_allocator_impl(::aura::application * papp, int32_t iCount, bool bAligned) :
      factory_allocator(papp, iCount, sizeof(TYPE), typeid(TYPE).name(), bAligned)
   {
   }
#endif

   virtual void discard(element * pca)
   {
      
      TYPE * ptype = (TYPE *) pca->m_pthis;

      if(ptype == NULL)
         return;

      safe_destroy_element(ptype);

      if(safe_free_memory(ptype))
      {

         m_iAllocCount--;

      }

   }


};


class CLASS_DECL_AURA factory_item_base :
   virtual public ::object
{
public:

   sp(factory_allocator)    m_pallocator;

   inline factory_item_base(::aura::application * papp, factory_allocator * pallocator) : element(papp), m_pallocator(pallocator) {}
   virtual ~factory_item_base();

   
   using ::object::create;
   virtual element *  create(::aura::application * papp);
   virtual element *  create();
   
   using ::object::clone;
   virtual element * clone(sp(element) pobject);

};

template < class CREATABLE_TYPE >
class creatable_factory_item :
   public factory_item_base
{
public:

   inline creatable_factory_item(::aura::application * papp, factory_allocator * pallocator) : element(papp), factory_item_base(papp, pallocator) {}

   using ::factory_item_base::create;
   virtual element * create(::aura::application * papp);

   using ::factory_item_base::clone;
   virtual element * clone(sp(element) pobject);

};

template < class CLONEABLE_TYPE >
class cloneable_factory_item :
   public creatable_factory_item < CLONEABLE_TYPE >
{
public:

   inline cloneable_factory_item(::aura::application * papp, factory_allocator * pallocator) : element(papp), creatable_factory_item < CLONEABLE_TYPE > (papp, pallocator) {}

   
   using creatable_factory_item < CLONEABLE_TYPE >::clone;
   virtual element * clone(sp(element) pobject);

};

template < class CREATABLE_TYPE >
class default_creatable_factory_item:
   public factory_item_base
{
public:

   inline default_creatable_factory_item(::aura::application * papp,factory_allocator * pallocator): element(papp),factory_item_base(papp,pallocator) {}

   using ::factory_item_base::create;
   virtual element * create();

   using ::factory_item_base::clone;
   virtual element * clone(sp(element) pobject);

};

template < class CLONEABLE_TYPE >
class default_cloneable_factory_item:
   public default_creatable_factory_item < CLONEABLE_TYPE >
{
public:

   inline default_cloneable_factory_item(::aura::application * papp,factory_allocator * pallocator): element(papp),default_creatable_factory_item < CLONEABLE_TYPE >(papp,pallocator) {}


   using default_creatable_factory_item < CLONEABLE_TYPE >::clone;
   virtual element * clone(sp(element) pobject);

};


class CLASS_DECL_AURA base_factory :
   virtual public ::object
{
public:


   sp(mutex)                     m_pmutex;
   idsp(factory_item_base)       m_mapItem;
   idsp(factory_allocator)       m_mapAllocator;
   bool                          m_bSimpleFactoryRequest;
   spa(type)                     m_typeinfoptraSimpleFactoryRequest;



   base_factory(::aura::application * papp);
   virtual ~base_factory();



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
   void default_creatable_small(bool bOverwrite = true,bool bAligned = false)
   {
      default_creatable < T >(32,bOverwrite,bAligned);
   }

   template < class T >
   void default_cloneable_small(bool bOverwrite = true,bool bAligned = false)
   {
      default_cloneable < T >(32,bOverwrite,bAligned);
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
   void default_creatable_large(bool bOverwrite = true,bool bAligned = false)
   {
      default_creatable < T >(1024,bOverwrite,bAligned);
   }

   template < class T >
   void default_cloneable_large(bool bOverwrite = true,bool bAligned = false)
   {
      default_cloneable < T >(1024,bOverwrite,bAligned);
   }

   template < class T >
   void creatable_small(const type * info,bool bOverwrite = true,bool bAligned = false)
   {
      creatable < T > (info, 32, bOverwrite, bAligned);
   }

   template < class T >
   void cloneable_small(const type * info,bool bOverwrite = true,bool bAligned = false)
   {
      cloneable < T > (info, 32, bOverwrite, bAligned);
   }

   template < class T >
   void default_creatable_small(const type * info,bool bOverwrite = true,bool bAligned = false)
   {
      default_creatable < T >(info,32,bOverwrite,bAligned);
   }

   template < class T >
   void default_cloneable_small(const type * info,bool bOverwrite = true,bool bAligned = false)
   {
      default_cloneable < T >(info,32,bOverwrite,bAligned);
   }

   template < class T >
   void creatable_large(const type * info,bool bOverwrite = true,bool bAligned = false)
   {
      creatable < T > (info, 1024, bOverwrite, bAligned);
   }

   template < class T >
   void cloneable_large(const type * info,bool bOverwrite = true,bool bAligned = false)
   {
      cloneable < T > (info, 1024, bOverwrite, bAligned);
   }

   template < class T >
   void default_creatable_large(const type * info,bool bOverwrite = true,bool bAligned = false)
   {
      default_creatable < T >(info,1024,bOverwrite,bAligned);
   }

   template < class T >
   void default_cloneable_large(const type * info,bool bOverwrite = true,bool bAligned = false)
   {
      default_cloneable < T >(info,1024,bOverwrite,bAligned);
   }

   template < class T >
   void creatable(int32_t iCount, bool bOverwrite = true, bool bAligned = false);

   template < class T >
   void cloneable(int32_t iCount, bool bOverwrite = true, bool bAligned = false);

   template < class T >
   void default_creatable(int32_t iCount,bool bOverwrite = true,bool bAligned = false);

   template < class T >
   void default_cloneable(int32_t iCount,bool bOverwrite = true,bool bAligned = false);

   template < class T >
   void creatable(const type * info, int32_t iCount, bool bOverwrite = true, bool bAligned = false);

   template < class T >
   void cloneable(const type * info,int32_t iCount,bool bOverwrite = true,bool bAligned = false);

   template < class T >
   void default_creatable(const type * info,int32_t iCount,bool bOverwrite = true,bool bAligned = false);

   template < class T >
   void default_cloneable(const type * info,int32_t iCount,bool bOverwrite = true,bool bAligned = false);


   using ::object::create;
   virtual element * create(::aura::application *  papp, sp(type) & info);
   
   virtual element * base_clone(element * pobject);

   virtual element * typed_clone(id idType, element * pobject);
   
   using ::object::clone;
   template < class T >
   T * clone(sp(T) pobject)
   {
      element * pca =
#ifdef WINDOWS
      pca = typed_clone(typeid(T).raw_name(), pobject);
#else
      pca = typed_clone(typeid(T).name(),pobject);
#endif
      if(pca == NULL)
         return NULL;
      return dynamic_cast < T * >(pca);
   }

   template < class T >
   sp(factory_allocator) & get_allocator(int32_t iCount, bool bAligned);


   inline bool is_set(::id id) {  return m_mapItem[id].is_set(); }


   void discard(sp(element) pobject);

   void enable_simple_factory_request(bool bEnable = true);


};



