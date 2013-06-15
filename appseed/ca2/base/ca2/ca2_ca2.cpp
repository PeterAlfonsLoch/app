#include "framework.h"


namespace ca2
{




   ca2::ca2()
   {
      m_ulFlags            = (uint32_t) flag_auto_clean;
//      m_papp               = 0; // NULL
      //m_countReference     = 1; // avoid creating a "perambulator" phantom
      //m_countReference     = 0; // do create a "perambulator" phantom, add_ref to "instantiate"
//      m_pptraListener      = NULL;
  //    m_pptraListened      = NULL;
      m_pfactoryitembase   = NULL;
   }

   ca2::ca2(const ca2 & o) :
      m_papp(o.m_papp)
   {
      m_ulFlags            = o.m_ulFlags;
      //m_countReference     = 1; // avoid creating a "perambulator" phantom
      //m_countReference     = 0; // do create a "perambulator" phantom, add_ref to "instantiate"
    //  m_pptraListener      = NULL;
      //m_pptraListened      = NULL;
      m_pfactoryitembase   = NULL;
   }

   ca2::ca2(sp(::ca2::application) papp) :
      m_papp(papp)
   {
      m_ulFlags            = (uint32_t) flag_auto_clean;
      //m_countReference     = 1; // avoid creating a "perambulator" phantom
//      m_pptraListener      = NULL;
  //    m_pptraListened      = NULL;
      m_pfactoryitembase   = NULL;
   }

   ca2::~ca2()
   {

   }

   ::ca2::application * ca2::get_app() const
   {
      return m_papp;
   }

   void ca2::set_app(::ca2::application * papp)
   {
      m_papp = papp;
   }

   void ca2::system(const char * pszProjectName)
   {
      UNREFERENCED_PARAMETER(pszProjectName);
   }

   ca2 & ca2::operator = (const ca2 & o)
   {
      if(this != &o)
      {
         m_ulFlags   = o.m_ulFlags;
         m_papp      = o.m_papp;
      }
      return *this;
   }

   void ca2::delete_this()
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

   sp(::ca2::ca2) ca2::clone()
   {
      if(m_pfactoryitembase != NULL)
         return m_pfactoryitembase->clone(this);
      else
         return m_papp->m_psystem->clone(this);
   }


/*   ptra * ca2::new_ptra()
   {
      return new ::ca2::ptra();
   }*/


   allocatorsp::allocatorsp(sp(application) papp)
   {

      sp(allocator) spallocator = canew(allocator());

      spallocator->m_papp = papp;

      ::ca::smart_pointer < allocator >::operator = (spallocator);

   }


} // namespace ca2






