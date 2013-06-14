#include "framework.h"



void itemswap(void * pswaparg, index i1, index i2);


void itemswap(void * pswaparg, index i1, index i2)
{
   array < factory_item_base * > * pitemptra = (array < factory_item_base * > *) pswaparg;
   pitemptra->swap(i1, i2);
}

namespace ca2
{


   bool is_safe_set(void * p);

   factory::factory(sp(::ca2::application) papp) :
      ca2(papp)
   {
      m_pmutex = new mutex(papp);
      m_pstrida = new strid_array(true);
      m_pstridaAllocator = new strid_array(true);
      m_bSimpleFactoryRequest = false;
   }

   factory::~factory()
   {

      single_lock sl(m_pmutex, TRUE);

      for(int32_t i = 0; i < m_itemptra.get_count(); i++)
      {
         m_itemptra[i].release();
      }

      for(int32_t i = 0; i < m_itemptraAllocator.get_count(); i++)
      {
         m_itemptraAllocator[i].release();
      }

   }




   void factory::set_at(const char * pszId, factory_item_base * pitem)
   {

      single_lock sl(m_pmutex, TRUE);

      class id id = (class id) pszId;

      index iFind;

      if(m_pstrida->find(id, iFind))
      {
         m_itemptra[iFind].release();
      }

      m_pstrida->add(id);

      m_itemptra.add(pitem);

   }



   void factory::set_at(const char * pszType, sp(factory_allocator) pallocator)
   {

      single_lock sl(m_pmutex, TRUE);

      class id id = (class id) pszType;

      index iFind;

      if(m_pstridaAllocator->find(id, iFind))
         return;

      m_pstridaAllocator->add(id);

      m_itemptraAllocator.add(pallocator);

   }

   void factory::discard(sp(::ca2::ca2) pobject)
   {
      single_lock sl(m_pmutex, TRUE);
      sp(factory_allocator) pallocator = get_allocator(typeid(*pobject).name());
      sl.unlock();
      if(pallocator == NULL)
      {
         if(::is_debugger_attached())
            __debug_break();
         return;
      }
      pallocator->discard(pobject);
   }

   bool is_safe_set(void * p)
   {
      return ((int_ptr) p) >= 32768;

   }

   void factory::enable_simple_factory_request(bool bEnable)
   {

      m_bSimpleFactoryRequest = bEnable;

      if(!bEnable)
      {

         single_lock sl(m_pmutex, TRUE);

         m_typeinfoptraSimpleFactoryRequest.remove_all();

      }

   }



   bool factory::is_set(const char * pszType)
   {

      index iFind;

      return m_pstrida->find((id) pszType, iFind);


   }




   sp(factory_allocator) factory::get_allocator(const char * pszType)
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



   sp(::ca2::ca2) factory::create(sp(::ca2::application) papp, sp(::ca2::type_info) info)
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



   sp(::ca2::ca2) factory::base_clone(sp(::ca2::ca2) pobject)
   {

      single_lock sl(m_pmutex, TRUE);

      if(pobject == NULL)
         return NULL;

      index iFind;

      if(!m_pstrida->find((id) typeid(*pobject).name(), iFind))
         return NULL;

      factory_item_base * pitem = m_itemptra.element_at(iFind);

      return pitem->clone(pobject);

   }


} // namespace ca2



































