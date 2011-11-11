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

factory::factory(::ca::application * papp) :
   ca(papp)
{
   m_pmutex = new mutex();
   m_bSimpleFactoryRequest = false;
}

factory::~factory()
{
   single_lock sl(m_pmutex, TRUE);
   for(int i = 0; i < m_itemptra.get_count(); i++)
   {
      delete m_itemptra[i];
   }
   for(int i = 0; i < m_itemptraAllocator.get_count(); i++)
   {
      delete m_itemptraAllocator[i];
   }
}

::ca::ca * factory::create(::ca::application * papp, ::ca::type_info & info)
{
   if(info.m_spmutex.is_null())
   {
      info.m_spmutex(new mutex());
   }
   single_lock slInfo(info.m_spmutex, TRUE);
   if(info.m_pfactoryitem != NULL)
   {
      if(m_bSimpleFactoryRequest)
      {
         return info.m_pfactoryitem->create(papp);
      }
      info.m_pfactoryitem = NULL;
   }
   single_lock sl(m_pmutex, TRUE);
   const char * pszRawName = info.raw_name();
   void * pvoid = (void *) pszRawName;
   index iFind = m_ida.find_first(pvoid, &idcmp, 0, -1);
   if(iFind < 0)
      return NULL;
   factory_item_base * pitem = m_itemptra.element_at(iFind);
   if(m_bSimpleFactoryRequest)
   {
      m_typeinfoptraSimpleFactoryRequest.add(&info);
      info.m_pfactoryitem = pitem;
   }
   return pitem->create(papp);
}

::ca::ca * factory::base_clone(::ca::ca * pobject)
{
   single_lock sl(m_pmutex, TRUE);
   if(pobject == NULL)
      return NULL;
   class id id = typeid(*pobject).raw_name();
   const char * pszRawName = id;
   void * pvoid = (void *) pszRawName;
   index iFind = m_ida.find_first(pvoid, &idcmp, 0, -1);
   if(iFind < 0)
      return NULL;
   factory_item_base * pitem = m_itemptra.element_at(iFind);
   //sl.unlock();
   return pitem->clone(pobject);
}



void factory::set_at(const char * pszId, factory_item_base * pitem)
{
   single_lock sl(m_pmutex, TRUE);
   m_ida.add((void *) (const char *) (id) pszId);
   m_itemptra.add(pitem);
   sort::QuickSort(m_ida, &idcmp, &itemswap, (void *) &m_itemptra);
}

factory_allocator * factory::get_allocator(const char * pszType)
{
   single_lock sl(m_pmutex, TRUE);
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
   single_lock sl(m_pmutex, TRUE);
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
   single_lock sl(m_pmutex, TRUE);
   factory_allocator * pallocator = get_allocator(typeid(*pobject).raw_name());
   sl.unlock();
   if(pallocator == NULL)
   {
      if(::IsDebuggerPresent())
         AfxDebugBreak();
      return;
   }
   pallocator->discard(pobject);
}


void factory::enable_simple_factory_request(bool bEnable)
{
   m_bSimpleFactoryRequest = bEnable;
   if(!bEnable)
   {
      for(int i = 0; i < m_typeinfoptraSimpleFactoryRequest.get_count(); i++)
      {
         try
         {
            m_typeinfoptraSimpleFactoryRequest[i]->m_pfactoryitem->m_pallocator = NULL;
         }
         catch(...)
         {
         }
         try
         {
            m_typeinfoptraSimpleFactoryRequest[i]->m_pfactoryitem = NULL;
         }
         catch(...)
         {
         }
      }
      m_typeinfoptraSimpleFactoryRequest.remove_all();
   }
}
