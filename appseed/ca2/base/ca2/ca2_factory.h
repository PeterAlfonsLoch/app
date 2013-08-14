#pragma once


#include "ca2_fixed_alloc.h"


class strid_array;
class mutex;


class CLASS_DECL_ca2 factory_allocator :
   virtual public ::ca2::object
{
public:


   uint32_t                      m_uiAllocSize;
   int32_t                       m_iCount;
   int64_t                       m_iAllocCount;
   id                            m_idType;


   factory_allocator(sp(::ca2::application) papp, int32_t iCount, UINT uiAllocSize, id idType) :
      ca2(papp),
      m_iCount(iCount),
      m_uiAllocSize(uiAllocSize),
      m_idType(idType)
   {
      m_iAllocCount = 0;
   }

   virtual ~factory_allocator() {}

   inline void * alloc()
   {
      m_iAllocCount++;
#if MEMDLEAK
      return ca2_alloc_dbg(m_uiAllocSize, 0, "typeid://" + *m_idType.m_pstr, 0);
#else
      return ca2_alloc(m_uiAllocSize);
#endif
   }


   virtual void discard(::ca2::ca2 * pca) = 0;

};

template < class TYPE >
class factory_allocator_impl :
   public factory_allocator
{
public:

#ifdef WINDOWS
   factory_allocator_impl(sp(::ca2::application) papp, int32_t iCount) :
      factory_allocator(papp, iCount, sizeof(TYPE), typeid(TYPE).name())
   {
   }
#else
   factory_allocator_impl(sp(::ca2::application) papp, int32_t iCount) :
      factory_allocator(papp, iCount, sizeof(TYPE), typeid(TYPE).name())
   {
   }
#endif

   virtual void discard(::ca2::ca2 * pca)
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
      try
      {
         ca2_free(ptype);
         m_iAllocCount--;
      }
      catch(...)
      {
      }
      //m_alloc.Free(ptype);
   }
};


class CLASS_DECL_ca2 factory_item_base :
   virtual public ::ca2::object
{
public:

   sp(factory_allocator)    m_pallocator;

   inline factory_item_base(sp(::ca2::application) papp, sp(factory_allocator) pallocator) : ca2(papp), m_pallocator(pallocator) {}
   virtual ~factory_item_base();

   virtual sp(::ca2::ca2) create(sp(::ca2::application) papp) = 0;
   virtual sp(::ca2::ca2) clone(sp(::ca2::ca2) pobject) = 0;

};

template < class CREATABLE_TYPE >
class creatable_factory_item :
   public factory_item_base
{
public:

   inline creatable_factory_item(sp(::ca2::application) papp, sp(factory_allocator) pallocator) : ca2(papp), factory_item_base(papp, pallocator) {}

   virtual sp(::ca2::ca2) create(sp(::ca2::application) papp)
   {

      if(m_pallocator == NULL)
         return NULL;

      void * pv = m_pallocator->alloc();
#undef new
      CREATABLE_TYPE * pt = ::new (pv) CREATABLE_TYPE(papp);
#define new DEBUG_NEW
      ::ca::dereference_no_delete(pt);
      pt->::ca2::ca2::set_ca_flag(::ca2::ca2::flag_discard_to_factory);
      pt->m_pfactoryitembase = this;
      pt->m_pthis = pt;
      return pt;
   }

   virtual sp(::ca2::ca2) clone(sp(::ca2::ca2) pobject)
   {
      UNREFERENCED_PARAMETER(pobject);
      throw not_implemented(get_app());
   }

};

template < class CLONEABLE_TYPE >
class cloneable_factory_item :
   public creatable_factory_item < CLONEABLE_TYPE >
{
public:

   inline cloneable_factory_item(sp(::ca2::application) papp, sp(factory_allocator) pallocator) : ::ca2::ca2(papp), creatable_factory_item < CLONEABLE_TYPE > (papp, pallocator) {}

   virtual sp(::ca2::ca2) clone(sp(::ca2::ca2) pobject)
   {
      const CLONEABLE_TYPE * ptSrc = dynamic_cast < const CLONEABLE_TYPE * > (pobject.m_p);
      void * pv = this->m_pallocator->alloc();
#undef new
      CLONEABLE_TYPE * pt = ::new (pv) CLONEABLE_TYPE(*ptSrc);
#define new DEBUG_NEW
      ::ca::dereference_no_delete(pt);
      pt->::ca2::ca2::set_ca_flag(::ca2::ca2::flag_discard_to_factory);
      pt->m_pfactoryitembase = this;
      pt->m_pthis = pt;
      return pt;
   }

};


namespace ca2
{


   class CLASS_DECL_ca2 factory :
      virtual public ::ca2::object
   {
   public:


      bool                             m_bSimpleFactoryRequest;
      spa(::ca2::type_info)             m_typeinfoptraSimpleFactoryRequest;



      factory(sp(::ca2::application) papp);
      virtual ~factory();


      template < class T >
      void creatable_small(bool bOverwrite = false)
      {
         creatable < T > (32, bOverwrite);
      }

      template < class T >
      void cloneable_small(bool bOverwrite = false)
      {
         cloneable < T > (32, bOverwrite);
      }

      template < class T >
      void creatable_large(bool bOverwrite = false)
      {
         creatable < T > (1024, bOverwrite);
      }

      template < class T >
      void cloneable_large(bool bOverwrite = false)
      {
         cloneable < T > (1024, bOverwrite);
      }

      template < class T >
      void creatable_small(sp(::ca2::type_info) info, bool bOverwrite = false)
      {
         creatable < T > (info, 32, bOverwrite);
      }

      template < class T >
      void cloneable_small(sp(::ca2::type_info) info, bool bOverwrite = false)
      {
         cloneable < T > (info, 32, bOverwrite);
      }

      template < class T >
      void creatable_large(sp(::ca2::type_info) info, bool bOverwrite = false)
      {
         creatable < T > (info, 1024, bOverwrite);
      }

      template < class T >
      void cloneable_large(sp(::ca2::type_info) info, bool bOverwrite = false)
      {
         cloneable < T > (info, 1024, bOverwrite);
      }

      template < class T >
      void creatable(int32_t iCount, bool bOverwrite = false);

      template < class T >
      void cloneable(int32_t iCount, bool bOverwrite = false);

      template < class T >
      void creatable(sp(::ca2::type_info) info, int32_t iCount, bool bOverwrite = false)
      {
         if(bOverwrite || !is_set(info->name()))
            set_at(info->name(), new creatable_factory_item<T>(get_app(), get_allocator<T>(iCount)));
      }

      template < class T >
      void cloneable(sp(::ca2::type_info)  info, int32_t iCount, bool bOverwrite = false)
      {
         if(bOverwrite || !is_set(info->name()))
            set_at(info->name(), new cloneable_factory_item<T>(get_app(), get_allocator<T>(iCount)));
      }

      virtual sp(::ca2::ca2) create(sp(::ca2::application) papp, sp(::ca2::type_info) info);
      virtual sp(::ca2::ca2) base_clone(sp(::ca2::ca2) pobject);
      template < class T >
      sp(T) clone(sp(T) pobject)
      {
         return base_clone(pobject);
      }

      template < class T >
      sp(factory_allocator) get_allocator(int32_t iCount);


      bool is_set(const char * pszType);

      void set_at(const char * pszType, factory_item_base * pitem);
      void set_at(const char * pszType, sp(factory_allocator) pitem);

      sp(factory_allocator) get_allocator(const char * pszType);

      void discard(sp(::ca2::ca2) pobject);

      void enable_simple_factory_request(bool bEnable = true);


   private:
      sp(mutex)                                                   m_pmutex;
      sp(strid_array)                                             m_pstrida;
      spa(factory_item_base)                                      m_itemptra;
      sp(strid_array)                                             m_pstridaAllocator;
      spa(factory_allocator)                                      m_itemptraAllocator;
   };




} // namespace ca2

