#pragma once

#include "radix/fixed_alloc.h"

class mutex;

template<>
inline UINT HashKey(::ca::type_info key)
{
   // default identity hash - works for most primitive values
   return HashKey(key.raw_name());
}

class CLASS_DECL_ca factory_allocator
{
public:

   DWORD                   m_uiAllocSize;
   int                     m_iCount;
   __int64                 m_iAllocCount;
   id                      m_idType;

   factory_allocator(int iCount, UINT uiAllocSize, id idType) :
      m_iCount(iCount),
      m_uiAllocSize(uiAllocSize),
      m_idType(idType)
   {
      m_iAllocCount = 0;
   }

   inline void * alloc()
   {
      m_iAllocCount++;
      return ca2_alloc(m_uiAllocSize);
   }

   virtual void discard(::ca::ca * pca) = 0;

};

template < class TYPE >
class factory_allocator_impl :
   public factory_allocator
{
public:

   factory_allocator_impl(int iCount) :
      factory_allocator(iCount, sizeof(TYPE), ::ca::get_type_info < TYPE > ().raw_name())
   {
   }

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
   virtual public ::radix::object
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
      throw not_implemented_exception();
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
   virtual public ::radix::object
{
public:



   bool                             m_bSimpleFactoryRequest;
   raw_array < ::ca::type_info * >  m_typeinfoptraSimpleFactoryRequest;



   factory(::ca::application * papp);
   virtual ~factory();

   template < class T >
   void creatable_small()
   {
      creatable < T > (32);
   }

   template < class T >
   void cloneable_small()
   {
      cloneable < T > (32);
   }

   template < class T >
   void creatable_large()
   {
      creatable < T > (1024);
   }

   template < class T >
   void cloneable_large()
   {
      cloneable < T > (1024);
   }

   template < class T >
   void creatable_small(::ca::type_info info)
   {
      creatable < T > (info, 32);
   }

   template < class T >
   void cloneable_small(::ca::type_info info)
   {
      cloneable < T > (info, 32);
   }

   template < class T >
   void creatable_large(::ca::type_info info)
   {
      creatable < T > (info, 1024);
   }

   template < class T >
   void cloneable_large(::ca::type_info info)
   {
      cloneable < T > (info, 1024);
   }

   template < class T >
   void creatable(int iCount)
   {
      set_at(::ca::get_type_info < T > ().raw_name(), new creatable_factory_item<T>(get_app(), get_allocator<T>(iCount)));
   }

   template < class T >
   void cloneable(int iCount)
   {
      set_at(::ca::get_type_info < T > ().raw_name(), new cloneable_factory_item<T>(get_app(), get_allocator<T>(iCount)));
   }

   template < class T >
   void creatable(::ca::type_info info, int iCount)
   {
      set_at(info.raw_name(), new creatable_factory_item<T>(get_app(), get_allocator<T>(iCount)));
   }

   template < class T >
   void cloneable(::ca::type_info  info, int iCount)
   {
      set_at(info.raw_name(), new cloneable_factory_item<T>(get_app(), get_allocator<T>(iCount)));
   }

   virtual ::ca::ca * create(::ca::application * papp, ::ca::type_info & info);
   virtual ::ca::ca * base_clone(::ca::ca * pobject);
   template < class T >
   T * clone(T * pobject)
   {
      return dynamic_cast < T * > (base_clone(pobject));
   }

   template < class T >
   factory_allocator * get_allocator(int iCount)
   {
      factory_allocator * pallocator = get_allocator(::ca::get_type_info < T > ().raw_name());
      if(pallocator != NULL)
         return pallocator;
      pallocator = new factory_allocator_impl<T>(iCount);
      set_at(::ca::get_type_info < T > ().raw_name(), pallocator);
      return pallocator;
   }

   void set_at(const char * pszType, factory_item_base * pitem);
   void set_at(const char * pszType, factory_allocator * pitem);

   factory_allocator * get_allocator(const char * pszType);

   void discard(::ca::ca * pobject);

   void enable_simple_factory_request(bool bEnable = true);


private:
   mutex *                                                     m_pmutex;
   base_array < void *, void * >                               m_ida;
   base_array < factory_item_base *, factory_item_base * >     m_itemptra;
   base_array < void *, void * >                               m_idaAllocator;
   base_array < factory_allocator *, factory_allocator * >     m_itemptraAllocator;
};
