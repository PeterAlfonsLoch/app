#pragma once



template < class CREATABLE_TYPE >
sp(element) creatable_factory_item < CREATABLE_TYPE > ::create(sp(::axis::application) papp)
{

   void * pv = NULL;

   {

      synch_lock sl(g_pmutexFactory);

      if(m_pallocator == NULL)
         return NULL;

      pv = m_pallocator->alloc();

   }

#undef new

   CREATABLE_TYPE * pt = ::new (pv) CREATABLE_TYPE(papp);

#define new AXIS_NEW

   ::dereference_no_delete(pt);

   pt->::element::set_ca_flag(element::flag_discard_to_factory);

   pt->m_pfactoryitembase = this;

   pt->m_pthis = pt;

   return pt;

}


template < class CREATABLE_TYPE >
sp(element) creatable_factory_item < CREATABLE_TYPE > ::clone(sp(element) pobject)
{

   UNREFERENCED_PARAMETER(pobject);

   throw not_implemented(get_app());

   return NULL;

}


template < class CLONEABLE_TYPE >
sp(element) cloneable_factory_item < CLONEABLE_TYPE > ::clone(sp(element) pobject)
{

   const CLONEABLE_TYPE * ptSrc = dynamic_cast < const CLONEABLE_TYPE * > (pobject.m_p);

   void * pv = NULL;

   {

      synch_lock sl(g_pmutexFactory);

      if(this->m_pallocator == NULL)
         return NULL;

      pv = this->m_pallocator->alloc();

   }

#undef new

   CLONEABLE_TYPE * pt = ::new (pv) CLONEABLE_TYPE(*ptSrc);

#define new AXIS_NEW

   ::dereference_no_delete(pt);

   pt->::element::set_ca_flag(element::flag_discard_to_factory);

   pt->m_pfactoryitembase = this;

   pt->m_pthis = pt;

   return pt;

}




