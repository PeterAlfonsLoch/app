#pragma once



template < class CREATABLE_TYPE >
sp(element) creatable_factory_item < CREATABLE_TYPE > ::create(sp(base_application) papp)
{

   if(m_pallocator == NULL)
      return NULL;

   void * pv = m_pallocator->alloc();
#undef new
   CREATABLE_TYPE * pt = ::new (pv) CREATABLE_TYPE(papp);
#define new BASE_NEW
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
}


template < class CLONEABLE_TYPE >
sp(element) cloneable_factory_item < CLONEABLE_TYPE > ::clone(sp(element) pobject)
{
   const CLONEABLE_TYPE * ptSrc = dynamic_cast < const CLONEABLE_TYPE * > (pobject.m_p);
   void * pv = this->m_pallocator->alloc();
#undef new
   CLONEABLE_TYPE * pt = ::new (pv) CLONEABLE_TYPE(*ptSrc);
#define new BASE_NEW
   ::dereference_no_delete(pt);
   pt->::element::set_ca_flag(element::flag_discard_to_factory);
   pt->m_pfactoryitembase = this;
   pt->m_pthis = pt;
   return pt;
}




template < class T >
void base_factory::creatable(int32_t iCount, bool bOverwrite)
{

   if(bOverwrite || !is_set(System.type_info <  T  > ()->name()))
      set_at(System.type_info <  T  > ()->name(), new creatable_factory_item<T>(get_app(), get_allocator<T>(iCount)));

}


template < class T >
void base_factory::cloneable(int32_t iCount, bool bOverwrite)
{

   if(bOverwrite || !is_set(System.type_info <  T  > ()->name()))
      set_at(System.type_info <  T  > ()->name(), new cloneable_factory_item<T>(get_app(), get_allocator<T>(iCount)));

}

template < class T >
sp(factory_allocator) base_factory::get_allocator(int32_t iCount)
{

   sp(factory_allocator) pallocator = get_allocator(System.type_info <  T  > ()->name());

   if(pallocator != NULL)
      return pallocator;

   pallocator = canew(factory_allocator_impl < T > (get_app(), iCount));

   set_at(System.type_info <  T  > ()->name(), pallocator);

   return pallocator;

}
