#include "framework.h"


namespace ca
{




   ca::ca()
   {
      m_ulFlags            = (uint32_t) flag_auto_clean;
//      m_papp               = 0; // NULL
      //m_countReference     = 1; // avoid creating a "perambulator" phantom
      //m_countReference     = 0; // do create a "perambulator" phantom, add_ref to "instantiate"
//      m_pptraListener      = NULL;
  //    m_pptraListened      = NULL;
      m_pfactoryitembase   = NULL;
   }

   ca::ca(const ca & o) :
      m_papp(o.m_papp)
   {
      m_ulFlags            = o.m_ulFlags;
      //m_countReference     = 1; // avoid creating a "perambulator" phantom
      //m_countReference     = 0; // do create a "perambulator" phantom, add_ref to "instantiate"
    //  m_pptraListener      = NULL;
      //m_pptraListened      = NULL;
      m_pfactoryitembase   = NULL;
   }

   ca::ca(sp(::ca::application) papp) :
      m_papp(papp)
   {
      m_ulFlags            = (uint32_t) flag_auto_clean;
      //m_countReference     = 1; // avoid creating a "perambulator" phantom
//      m_pptraListener      = NULL;
  //    m_pptraListened      = NULL;
      m_pfactoryitembase   = NULL;
   }

   ca::~ca()
   {

   }

   ::ca::application * ca::get_app() const
   {
      return m_papp;
   }

   void ca::set_app(::ca::application * papp)
   {
      m_papp = papp;
   }

   void ca::system(const char * pszProjectName)
   {
      UNREFERENCED_PARAMETER(pszProjectName);
   }

   ca & ca::operator = (const ca & o)
   {
      if(this != &o)
      {
         m_ulFlags   = o.m_ulFlags;
         m_papp      = o.m_papp;
      }
      return *this;
   }

   void ca::delete_this()
   {
      if(m_pfactoryitembase != NULL && m_pfactoryitembase->m_pallocator)
      {

         m_pfactoryitembase->m_pallocator->discard(this);
      }
      else if(m_ulFlags & flag_discard_to_factory)
      {
         m_papp->m_psystem->discard_to_factory(this);
      }
//      else if(m_ulFlags & flag_heap_alloc)
      else if(is_heap())
      {
         delete this;
      }
   }

   sp(::ca::ca) ca::clone()
   {
      if(m_pfactoryitembase != NULL)
         return m_pfactoryitembase->clone(this);
      else
         return m_papp->m_psystem->clone(this);
   }


/*   ptra * ca::new_ptra()
   {
      return new ::ca::ptra();
   }*/


   allocatorsp::allocatorsp(sp(application) papp)
   {

      sp(allocator) spallocator = canew(allocator());

      spallocator->m_papp = papp;

      ::c::smart_pointer < allocator >::operator = (spallocator);

   }


} // namespace ca






