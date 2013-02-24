#pragma once


#include "gen_fixed_alloc.h"


class strid_array;
class mutex;


class CLASS_DECL_ca factory_allocator
{
public:


   uint32_t                   m_uiAllocSize;
   int32_t                     m_iCount;
   int64_t                 m_iAllocCount;
   id                      m_idType;
   ::ca::application *     m_papp;


   factory_allocator(::ca::application * papp, int32_t iCount, UINT uiAllocSize, id idType) :
      m_iCount(iCount),
      m_uiAllocSize(uiAllocSize),
      m_idType(idType),
      m_papp(papp)
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


   virtual void discard(::ca::ca * pca) = 0;

};

template < class TYPE >
class factory_allocator_impl :
   public factory_allocator
{
public:

#ifdef WINDOWS
   factory_allocator_impl(::ca::application * papp, int32_t iCount) :
      factory_allocator(papp, iCount, sizeof(TYPE), typeid(TYPE).name())
   {
   }
#else
   factory_allocator_impl(::ca::application * papp, int32_t iCount) :
      factory_allocator(papp, iCount, sizeof(TYPE), typeid(TYPE).name())
   {
   }
#endif

   virtual void discard(::ca::ca * pca)
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


class CLASS_DECL_ca factory_item_base :
   virtual public ::ca::object
{
public:

   factory_allocator * m_pallocator;

   inline factory_item_base(::ca::application * papp, factory_allocator * pallocator) : ca(papp), m_pallocator(pallocator) {}

   virtual ::ca::ca * create(::ca::application * papp) = 0;
   virtual ::ca::ca * clone(::ca::ca * pobject) = 0;

};

template < class CREATABLE_TYPE >
class creatable_factory_item :
   public factory_item_base
{
public:

   inline creatable_factory_item(::ca::application * papp, factory_allocator * pallocator) : ca(papp), factory_item_base(papp, pallocator) {}

   virtual ::ca::ca * create(::ca::application * papp)
   {
      void * pv = m_pallocator->alloc();
#undef new
      CREATABLE_TYPE * pt = ::new (pv) CREATABLE_TYPE(papp);
#define new DEBUG_NEW
      pt->::ca::ca::set_ca_flag(::ca::ca::flag_discard_to_factory);
      pt->m_pfactoryitembase = this;
      pt->m_pthis = pt;
      return dynamic_cast < ::ca::ca * > (pt);
   }

   virtual ::ca::ca * clone(::ca::ca * pobject)
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

   inline cloneable_factory_item(::ca::application * papp, factory_allocator * pallocator) : ::ca::ca(papp), creatable_factory_item < CLONEABLE_TYPE > (papp, pallocator) {}

   virtual ::ca::ca * clone(::ca::ca * pobject)
   {
      const CLONEABLE_TYPE * ptSrc = dynamic_cast < const CLONEABLE_TYPE * > (pobject);
      void * pv = this->m_pallocator->alloc();
#undef new
      CLONEABLE_TYPE * pt = ::new (pv) CLONEABLE_TYPE(*ptSrc);
#define new DEBUG_NEW
      pt->::ca::ca::set_ca_flag(::ca::ca::flag_discard_to_factory);
      pt->m_pfactoryitembase = this;
      pt->m_pthis = pt;
      return dynamic_cast < ::ca::ca * > (pt);
   }

};

class CLASS_DECL_ca factory :
   virtual public ::ca::object
{
public:



   bool                             m_bSimpleFactoryRequest;
   raw_array < ::ca::type_info * >  m_typeinfoptraSimpleFactoryRequest;



   factory(::ca::application * papp);
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
   void creatable_small(::ca::type_info info, bool bOverwrite = false)
   {
      creatable < T > (info, 32, bOverwrite);
   }

   template < class T >
   void cloneable_small(::ca::type_info info, bool bOverwrite = false)
   {
      cloneable < T > (info, 32, bOverwrite);
   }

   template < class T >
   void creatable_large(::ca::type_info info, bool bOverwrite = false)
   {
      creatable < T > (info, 1024, bOverwrite);
   }

   template < class T >
   void cloneable_large(::ca::type_info info, bool bOverwrite = false)
   {
      cloneable < T > (info, 1024, bOverwrite);
   }

   template < class T >
   void creatable(int32_t iCount, bool bOverwrite = false);

   template < class T >
   void cloneable(int32_t iCount, bool bOverwrite = false);

   template < class T >
   void creatable(::ca::type_info info, int32_t iCount, bool bOverwrite = false)
   {
      if(bOverwrite || !is_set(info.name()))
         set_at(info.name(), new creatable_factory_item<T>(get_app(), get_allocator<T>(iCount)));
   }

   template < class T >
   void cloneable(::ca::type_info  info, int32_t iCount, bool bOverwrite = false)
   {
      if(bOverwrite || !is_set(info.name()))
         set_at(info.name(), new cloneable_factory_item<T>(get_app(), get_allocator<T>(iCount)));
   }

   virtual ::ca::ca * create(::ca::application * papp, ::ca::type_info & info);
   virtual ::ca::ca * base_clone(::ca::ca * pobject);
   template < class T >
   T * clone(T * pobject)
   {
      return dynamic_cast < T * > (base_clone(pobject));
   }

   template < class T >
   factory_allocator * get_allocator(int32_t iCount);


   bool is_set(const char * pszType);

   void set_at(const char * pszType, factory_item_base * pitem);
   void set_at(const char * pszType, factory_allocator * pitem);

   factory_allocator * get_allocator(const char * pszType);

   void discard(::ca::ca * pobject);

   void enable_simple_factory_request(bool bEnable = true);


private:
   mutex *                                                     m_pmutex;
   strid_array *                                               m_pstrida;
   base_array < factory_item_base *, factory_item_base * >     m_itemptra;
   strid_array *                                               m_pstridaAllocator;
   base_array < factory_allocator *, factory_allocator * >     m_itemptraAllocator;
};




