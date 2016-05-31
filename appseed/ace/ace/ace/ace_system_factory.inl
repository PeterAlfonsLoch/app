#pragma once



template < class CREATABLE_TYPE >
object * creatable_factory_item < CREATABLE_TYPE > ::create(::ace::application * papp)
{

   void * pv = NULL;
   
   //sp(::ace::application) spapp;
   
   //spapp = papp;

   {

      synch_lock sl(g_pmutexFactory);

      if(m_pallocator == NULL)
         return NULL;

      pv = m_pallocator->alloc();

   }

#undef new

   CREATABLE_TYPE * pt = ::new (pv) CREATABLE_TYPE(papp);

#define new ACE_NEW

   ::dereference_no_delete(pt);

   pt->::object::set_ca_flag(::object::flag_discard_to_factory);

   pt->m_pfactoryitembase = this;

   pt->m_pthis = pt;

   return pt;

}


template < class CREATABLE_TYPE >
object * creatable_factory_item < CREATABLE_TYPE > ::clone(sp(object) pobject)
{

   UNREFERENCED_PARAMETER(pobject);

   ::exception::throw_not_implemented(get_app());

   return NULL;

}


template < class CLONEABLE_TYPE >
object * cloneable_factory_item < CLONEABLE_TYPE > ::clone(sp(object) pobject)
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

#define new ACE_NEW

   ::dereference_no_delete(pt);

   pt->::object::set_ca_flag(object::flag_discard_to_factory);

   pt->m_pfactoryitembase = this;

   pt->m_pthis = pt;

   return pt;

}







template < class CREATABLE_TYPE >
object * default_creatable_factory_item < CREATABLE_TYPE > ::create()
{

   void * pv = NULL;

   //sp(::ace::application) spapp;

   //spapp = papp;

   {

      synch_lock sl(g_pmutexFactory);

      if(m_pallocator == NULL)
         return NULL;

      pv = m_pallocator->alloc();

   }

#undef new

   CREATABLE_TYPE * pt = ::new (pv)CREATABLE_TYPE();

#define new ACE_NEW

   ::dereference_no_delete(pt);

   pt->::object::set_ca_flag(object::flag_discard_to_factory);

   pt->m_pfactoryitembase = this;

   pt->m_pthis = pt;

   return pt;

}


template < class CREATABLE_TYPE >
object * default_creatable_factory_item < CREATABLE_TYPE > ::clone(sp(object) pobject)
{

   UNREFERENCED_PARAMETER(pobject);

   ::exception::throw_not_implemented(get_app());

   return NULL;

}


template < class CLONEABLE_TYPE >
object * default_cloneable_factory_item < CLONEABLE_TYPE > ::clone(sp(object) pobject)
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

   CLONEABLE_TYPE * pt = ::new (pv)CLONEABLE_TYPE(*ptSrc);

#define new ACE_NEW

   ::dereference_no_delete(pt);

   pt->::object::set_ca_flag(object::flag_discard_to_factory);

   pt->m_pfactoryitembase = this;

   pt->m_pthis = pt;

   return pt;

}




