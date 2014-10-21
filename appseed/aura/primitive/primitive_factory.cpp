#include "framework.h"



void itemswap(void * pswaparg, index i1, index i2);


void itemswap(void * pswaparg, index i1, index i2)
{
   array < factory_item_base * > * pitemptra = (array < factory_item_base * > *) pswaparg;
   pitemptra->swap(i1, i2);
}

bool is_safe_set(void * p);

base_factory::base_factory(sp(::aura::application) papp) :
   element(papp)
{
   m_pmutex = new mutex(papp);
   m_pstrida = new strid_array(true);
   m_pstridaAllocator = new strid_array(true);
   m_bSimpleFactoryRequest = false;
}

base_factory::~base_factory()
{

   single_lock sl(m_pmutex, TRUE);

   for(int32_t i = 0; i < m_itemptra.get_count(); i++)
   {
      m_itemptra[i]->release();
   }

   for(int32_t i = 0; i < m_itemptraAllocator.get_count(); i++)
   {
      m_itemptraAllocator[i]->release();
   }

}




void base_factory::set_at(const char * pszId, factory_item_base * pitem)
{

   single_lock sl(m_pmutex, TRUE);

   class id id = (class id) pszId;

   index iFind;

   if(m_pstrida->find(id, iFind))
   {
      m_itemptra.sp_at(iFind) = pitem;
   }
   else
   {
      m_pstrida->add(id);
      m_itemptra.add(pitem);
   }

}



void base_factory::set_at(const char * pszType, sp(factory_allocator) pallocator)
{

   single_lock sl(m_pmutex, TRUE);

   class id id = (class id) pszType;

   index iFind;

   if(m_pstridaAllocator->find(id, iFind))
      return;

   m_pstridaAllocator->add(id);

   m_itemptraAllocator.add(pallocator);

}

void base_factory::discard(sp(element) pobject)
{
   single_lock sl(m_pmutex, TRUE);
   sp(factory_allocator) pallocator = get_allocator(typeid(*pobject).name());
   sl.unlock();
   if(pallocator == NULL)
   {
      if(::is_debugger_attached())
         debug_break();
      return;
   }
   pallocator->discard(pobject);
}

bool is_safe_set(void * p)
{
   return ((int_ptr) p) >= 32768;

}

void base_factory::enable_simple_factory_request(bool bEnable)
{

   m_bSimpleFactoryRequest = bEnable;

   if(!bEnable)
   {

      single_lock sl(m_pmutex, TRUE);

      m_typeinfoptraSimpleFactoryRequest.remove_all();

   }

}



bool base_factory::is_set(const char * pszType)
{

   index iFind;

   return m_pstrida->find((id) pszType, iFind);


}




sp(factory_allocator) base_factory::get_allocator(const char * pszType)
{

   single_lock sl(m_pmutex, TRUE);

   class id id;

   try
   {
      id = (class id) pszType;
   }
   catch(...)
   {
      return NULL;
   }

   index iFind;

   if(!m_pstridaAllocator->find(id, iFind))
      return NULL;

   return m_itemptraAllocator(iFind);

}



element * base_factory::create(::aura::application * papp, sp(type) info)
{

   if(info->m_spmutex.is_null())
   {
      info->m_spmutex = new mutex(papp);
   }

   single_lock slInfo(info->m_spmutex, TRUE);

   if(info->m_pfactoryitem != NULL)
   {

      if(m_bSimpleFactoryRequest)
         return info->m_pfactoryitem->create(papp);

      info->m_pfactoryitem.release();
   }

   single_lock sl(m_pmutex, TRUE);

   index iFind;

   if(!m_pstrida->find(info->m_id, iFind))
      return NULL;

   factory_item_base * pitem = m_itemptra.element_at(iFind);

   if(m_bSimpleFactoryRequest)
   {
      m_typeinfoptraSimpleFactoryRequest.add(info);
      info->m_pfactoryitem = pitem;
   }

   return pitem->create(papp);

}



element * base_factory::base_clone(sp(element) pobject)
{

   return typed_clone((id) typeid(*pobject).name(), pobject);

}


element * base_factory::typed_clone(id idType, sp(element) pobject)
{

   single_lock sl(m_pmutex,TRUE);

   if(pobject == NULL)
      return NULL;

   index iFind;

   if(!m_pstrida->find(idType, iFind))
      return NULL;

   factory_item_base * pitem = m_itemptra.element_at(iFind);

   return pitem->clone(pobject);

}


factory_item_base::~factory_item_base()
{

}

































CLASS_DECL_AURA mutex * g_pmutexFactory = NULL;

























