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
   string                  m_strName;

   factory_allocator(int iCount, UINT uiAllocSize, const char * pszName) : 
      m_iCount(iCount),
      m_uiAllocSize(uiAllocSize),
      m_strName(pszName)
   {
   }

   inline void * alloc()
   {
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
      factory_allocator(iCount, sizeof(TYPE), typeid(TYPE).raw_name())
   {
   }

   virtual void discard(::ca::ca * pca)
   {
      TYPE * ptype = NULL;
      try
      {
         ptype = dynamic_cast < TYPE * > (pca);
      }
      catch(...)
      {
         return;
      }
      if(ptype == NULL)
         return;
      try
      {
         ptype->~TYPE();
      }
      catch(...)
      {
      }
      ca2_free(ptype, 0);
      //m_alloc.Free(ptype);
   }
};


class CLASS_DECL_ca factory_item_base
{
public:

   factory_allocator * m_pallocator;

   inline factory_item_base(factory_allocator * pallocator) : m_pallocator(pallocator) {}
   
   virtual ::ca::ca * create(::ca::application * papp) = 0;
   virtual ::ca::ca * clone(::ca::ca * pobject) = 0;
   
};

template < class CREATABLE_TYPE >
class creatable_factory_item :
   public factory_item_base
{
public:

   inline creatable_factory_item(factory_allocator * pallocator) : factory_item_base(pallocator) {}

   virtual ::ca::ca * create(::ca::application * papp)
   {
      void * pv = m_pallocator->alloc();
#undef new
      CREATABLE_TYPE * pt = ::new (pv) CREATABLE_TYPE(papp);
#define new DEBUG_NEW
      pt->::ca::ca::set(::ca::ca::flag_discard_to_factory);
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

   inline cloneable_factory_item(factory_allocator * pallocator) : creatable_factory_item(pallocator) {}

   virtual ::ca::ca * clone(::ca::ca * pobject)
   {
      const CLONEABLE_TYPE * ptSrc = dynamic_cast < const CLONEABLE_TYPE * > (pobject);
      void * pv = m_pallocator->alloc();
#undef new
      CLONEABLE_TYPE * pt = ::new (pv) CLONEABLE_TYPE(*ptSrc);
#define new DEBUG_NEW
      pt->::ca::ca::set(::ca::ca::flag_discard_to_factory);
      return dynamic_cast < ::ca::ca * > (pt);
   }

};

class CLASS_DECL_ca factory :
   virtual public ::radix::object
{
public:
   factory();
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
   void creatable_small(const std_type_info & info)
   {
      creatable < T > (info, 32);
   }

   template < class T >
   void cloneable_small(const std_type_info & info)
   {
      cloneable < T > (info, 32);
   }

   template < class T >
   void creatable_large(const std_type_info & info)
   {
      creatable < T > (info, 1024);
   }

   template < class T >
   void cloneable_large(const std_type_info & info)
   {
      cloneable < T > (info, 1024);
   }

   template < class T >
   void creatable(int iCount)
   {
      set_at(typeid(T).raw_name(), new creatable_factory_item<T>(get_allocator<T>(iCount)));
   }

   template < class T >
   void cloneable(int iCount)
   {
      set_at(typeid(T).raw_name(), new cloneable_factory_item<T>(get_allocator<T>(iCount)));
   }

   template < class T >
   void creatable(const std_type_info & info, int iCount)
   {
      set_at(info.raw_name(), new creatable_factory_item<T>(get_allocator<T>(iCount)));
   }

   template < class T >
   void cloneable(const std_type_info & info, int iCount)
   {
      set_at(info.raw_name(), new cloneable_factory_item<T>(get_allocator<T>(iCount)));
   }

   virtual ::ca::ca * create(::ca::application * papp, const ::ca::type_info & info);
   virtual ::ca::ca * base_clone(::ca::ca * pobject);
   template < class T >
   T * clone(T * pobject)
   {
      return dynamic_cast < T * > (base_clone(pobject));
   }

   template < class T >
   factory_allocator * get_allocator(int iCount)
   {
      factory_allocator * pallocator = get_allocator(typeid(T).raw_name());
      if(pallocator != NULL)
         return pallocator;
      pallocator = new factory_allocator_impl<T>(iCount);
      set_at(typeid(T).raw_name(), pallocator);
      return pallocator;
   }

   void set_at(const char * pszType, factory_item_base * pitem);
   void set_at(const char * pszType, factory_allocator * pitem);

   factory_allocator * get_allocator(const char * pszType);

   void discard(::ca::ca * pobject);


private:
   mutex *                                                     m_pmutex;
   base_array < void *, void * >                               m_ida;
   base_array < factory_item_base *, factory_item_base * >     m_itemptra;
   base_array < void *, void * >                               m_idaAllocator;
   base_array < factory_allocator *, factory_allocator * >     m_itemptraAllocator;
};