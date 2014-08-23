#include "framework.h"


allocator::~allocator()
{

}


element::element()
{

   m_ulFlags            = (uint32_t) flag_auto_clean;
   m_pfactoryitembase   = NULL;

}


element::element(const element & o)
{

   m_pauraapp = o.m_pauraapp;
   m_ulFlags = o.m_ulFlags;
   m_pfactoryitembase   = NULL;

}


element::element(sp(::aura::application) papp)
{

   m_pauraapp = papp;
   m_ulFlags = (uint32_t)flag_auto_clean;
   m_pfactoryitembase   = NULL;

}


element::~element()
{

}


/*sp(::aura::application) element::get_app() const
{

   return m_pauraapp;

}*/


void element::set_app(sp(::aura::application) papp)
{

   m_pauraapp = papp;

}


void element::system(const char * pszProjectName)
{

   UNREFERENCED_PARAMETER(pszProjectName);

}


element & element::operator = (const element & o)
{

   if(this != &o)
   {

      m_ulFlags   = o.m_ulFlags;
      m_pauraapp      = o.m_pauraapp;

   }

   return *this;

}


void element::delete_this()
{

   if(m_pfactoryitembase != NULL && m_pfactoryitembase->m_pallocator)
   {

      m_pfactoryitembase->m_pallocator->discard(this);

   }
   else if(m_ulFlags & flag_discard_to_factory)
   {

      m_pauraapp->m_paxissystem->discard_to_factory(this);

   }
   else if(is_heap())
   {

      delete this;

   }

}


sp(element) element::clone()
{

   if(m_pfactoryitembase != NULL)
      return m_pfactoryitembase->clone(this);

   return NULL;

}


allocatorsp::allocatorsp(sp(::aura::application) papp)
{

   sp(allocator) spallocator = canew(allocator());

   spallocator->m_pauraapp = papp;

   smart_pointer < allocator >::operator = (spallocator);

}


