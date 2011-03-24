#include "StdAfx.h"

index idcmp(void * id1, void * id2)
{
   return (byte *) id1 - (byte *) id2;
}

void itemswap(void * pswaparg, index i1, index i2)
{
   base_array < factory_item_base * > * pitemptra = (base_array < factory_item_base * > *) pswaparg;
   pitemptra->swap(i1, i2);
}

factory::factory()
{
   m_pmutex = new mutex();
}

factory::~factory()
{
   CSingleLock sl(m_pmutex, TRUE);
   for(int i = 0; i < m_itemptra.get_count(); i++)
   {
      delete m_itemptra[i];
   }
   for(int i = 0; i < m_itemptraAllocator.get_count(); i++)
   {
      delete m_itemptraAllocator[i];
   }
}

::ca::ca * factory::create(::ca::application * papp, const ::ca::type_info & info)
{
   CSingleLock sl(m_pmutex, TRUE);
   const char * pszRawName = info.raw_name();
   void * pvoid = (void *) pszRawName;
   index iFind = m_ida.find_first(pvoid, &idcmp, 0, -1);
   if(iFind < 0)
      return NULL;
   factory_item_base * pitem = m_itemptra.element_at(iFind);
   //sl.Unlock();
   return pitem->create(papp);
}

::ca::ca * factory::base_clone(::ca::ca * pobject)
{
   CSingleLock sl(m_pmutex, TRUE);
   if(pobject == NULL)
      return NULL;
   class id id = typeid(*pobject).raw_name();
   const char * pszRawName = id;
   void * pvoid = (void *) pszRawName;
   index iFind = m_ida.find_first(pvoid, &idcmp, 0, -1);
   if(iFind < 0)
      return NULL;
   factory_item_base * pitem = m_itemptra.element_at(iFind);
   //sl.Unlock();
   return pitem->clone(pobject);
}



void factory::set_at(const char * pszId, factory_item_base * pitem)
{
   CSingleLock sl(m_pmutex, TRUE);
   m_ida.add((void *) (const char *) (id) pszId);
   m_itemptra.add(pitem);
   sort::QuickSort(m_ida, &idcmp, &itemswap, (void *) &m_itemptra);
}

factory_allocator * factory::get_allocator(const char * pszType)
{
   CSingleLock sl(m_pmutex, TRUE);
   void * pvoid = NULL;
   try
   {
      pvoid = (void *) (const char *) (id) pszType;
   }
   catch(...)
   {
      return NULL;
   }
   index iFind = m_idaAllocator.find_first(pvoid, &idcmp, 0, -1);
   if(iFind < 0)
      return NULL;
   return m_itemptraAllocator[iFind];
}


void factory::set_at(const char * pszType, factory_allocator * pallocator)
{
   CSingleLock sl(m_pmutex, TRUE);
   void * pvoid = (void *) (const char *) (id) pszType;
   index iFind = m_idaAllocator.find_first(pvoid, &idcmp, 0, -1);
   if(iFind >= 0)
      return;
   m_idaAllocator.add((void *) (const char *) (id) pszType);
   m_itemptraAllocator.add(pallocator);
   sort::QuickSort(m_idaAllocator, &idcmp, &itemswap, (void *) &m_itemptraAllocator);
}

void factory::discard(::ca::ca * pobject)
{
   CSingleLock sl(m_pmutex, TRUE);
   factory_allocator * pallocator = get_allocator(typeid(*pobject).raw_name());
   if(pallocator == NULL)
   {
      if(::IsDebuggerPresent())
         AfxDebugBreak();
      return;
   }
   pallocator->discard(pobject);
}
