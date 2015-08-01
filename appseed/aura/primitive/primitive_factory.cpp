//#include "framework.h"



//void itemswap(void * pswaparg, index i1, index i2);
//
//
//void itemswap(void * pswaparg, index i1, index i2)
//{
//   ptr_array < factory_item_base > * pitemptra = (ptr_array < factory_item_base > *) pswaparg;
//   pitemptra->swap(i1, i2);
//}

bool is_safe_set(void * p);

base_factory::base_factory(::aura::application * papp) :
   object(papp)
{
   m_pmutex = new mutex(papp);
   m_bSimpleFactoryRequest = false;
}

base_factory::~base_factory()
{

   single_lock sl(m_pmutex, TRUE);

   m_mapItem.remove_all();

   m_mapAllocator.remove_all();

}





void base_factory::discard(sp(object) pobject)
{
   single_lock sl(m_pmutex, TRUE);
   sp(factory_allocator) & pallocator = m_mapAllocator[typeid(*pobject).name()];
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







object * base_factory::create(::aura::application * papp, ::type * ptype)
{

   if(ptype == NULL)
   {

      return NULL;

   }

   if(ptype->m_spmutex.is_null())
   {

      ptype->m_spmutex = new mutex(papp);

   }

   single_lock slInfo(ptype->m_spmutex,TRUE);

   if(ptype->m_pfactoryitem != NULL)
   {

      if(m_bSimpleFactoryRequest)
         return ptype->m_pfactoryitem->create(papp);

      ptype->m_pfactoryitem.release();

   }

   single_lock sl(m_pmutex, TRUE);

   sp(factory_item_base) & pitem = m_mapItem[ptype->m_id];

   if(pitem.is_null())
   {

      return NULL;

   }

   if(m_bSimpleFactoryRequest)
   {
      
      m_typeinfoptraSimpleFactoryRequest.add(ptype);

      ptype->m_pfactoryitem = pitem;

   }

   return pitem->create(papp);

}



object * base_factory::base_clone(object * pobject)
{

   return typed_clone((id) typeid(*pobject).name(), pobject);

}


object * base_factory::typed_clone(id idType,object * pobject)
{

   single_lock sl(m_pmutex,TRUE);

   if(pobject == NULL)
      return NULL;

   sp(factory_item_base) & pitem = m_mapItem[idType];

   if(pitem.is_null())
      return NULL;

   return pitem->clone(pobject);

}


object * factory_item_base::create(::aura::application * papp)
{
   
   UNREFERENCED_PARAMETER(papp);

   return NULL;

}


object * factory_item_base::create()
{

   return NULL;

}

object * factory_item_base::clone(sp(object) pobject)
{

   UNREFERENCED_PARAMETER(pobject);

   return NULL;

}


factory_item_base::~factory_item_base()
{

   output_debug_string(string("factory_item_base::~factory_item_base :: ") + m_pallocator->m_idType.m_psz + string("\n"));

}

































CLASS_DECL_AURA mutex * g_pmutexFactory = NULL;





















CLASS_DECL_AURA bool safe_destroy_element(object * pelement)
{

   try
   {

      pelement->~object();

   }
   catch(...)
   {

      return false;

   }

   return true;

}


CLASS_DECL_AURA bool safe_free_memory(void * ptype)
{


   try
   {

      memory_free(ptype);
      
   }
   catch(...)
   {

      return false;

   }

   return true;

}






