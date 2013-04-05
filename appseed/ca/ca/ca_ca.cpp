#include "framework.h"


namespace ca
{




   ca::ca()
   {
      m_ulFlags            = (uint32_t) flag_auto_clean;
      m_papp               = 0; // ::null()
      //m_countReference     = 1; // avoid creating a "perambulator" phantom
      m_countReference     = 0; // do create a "perambulator" phantom, add_ref to "instantiate"
//      m_pptraListener      = ::null();
  //    m_pptraListened      = ::null();
      m_pfactoryitembase   = ::null();
   }

   ca::ca(const ca & o)
   {
      m_ulFlags            = o.m_ulFlags;
      m_papp               = o.m_papp;
      //m_countReference     = 1; // avoid creating a "perambulator" phantom
      m_countReference     = 0; // do create a "perambulator" phantom, add_ref to "instantiate"
    //  m_pptraListener      = ::null();
      //m_pptraListened      = ::null();
      m_pfactoryitembase   = ::null();
   }

   ca::ca(::ca::applicationsp papp)
   {
      m_ulFlags            = (uint32_t) flag_auto_clean;
      m_papp               = papp;
      m_countReference     = 1; // avoid creating a "perambulator" phantom
//      m_pptraListener      = ::null();
  //    m_pptraListened      = ::null();
      m_pfactoryitembase   = ::null();
   }

   ca::~ca()
   {
/*      if(m_papp != ::null())
      {
         try
         {
            m_papp->on_delete(this);
         }
         catch(...)
         {
         }
         try
         {
            if(m_papp->m_psystem != ::null())
            {
                  m_papp->m_psystem->on_delete(this);
            }
         }
         catch(...)
         {
         }
      }

      if(m_pptraListener != ::null())
      {
         for(int32_t i = 0; i < m_pptraListener->get_size(); i++)
         {
            sp(::ca::ca) plistener = m_pptraListener->element_at(i);
            if(plistener != ::null())
            {
               try
               {
                  plistener->on_delete(this);
               }
               catch(...)
               {
               }
               try
               {
                  if(plistener->m_pptraListened != ::null())
                  {
                     plistener->m_pptraListened->remove(this);
                  }
               }
               catch(...)
               {
               }
            }
         }
         try
         {
            delete m_pptraListener;
         }
         catch(...)
         {
         }
         m_pptraListener = ::null();
      }
      if(m_pptraListened != ::null())
      {
         for(int32_t i = 0; i < m_pptraListened->get_size(); i++)
         {
            sp(::ca::ca) plistened = m_pptraListened->element_at(i);
            if(plistened != ::null())
            {
               try
               {
                  if(plistened->m_pptraListener != ::null())
                  {
                     plistened->m_pptraListener->remove(this);
                  }
               }
               catch(...)
               {
               }
            }
         }
         try
         {
            delete m_pptraListened;
         }
         catch(...)
         {
         }
         m_pptraListened = ::null();
      }

*/


   }

   ::ca::applicationsp ca::get_app() const
   {
      return m_papp;
   }

   void ca::set_app(::ca::applicationsp papp)
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

   void ca::on_delete(sp(::ca::ca) pca)
   {
   }

/*   ptra & ca::listenerptra()
   {
      if(m_pptraListener == ::null())
      {
         m_pptraListener = new_ptra();
      }
      return *m_pptraListener;
   }

   ptra & ca::listenedptra()
   {
      if(m_pptraListened == ::null())
      {
         m_pptraListened = new_ptra();
      }
      return *m_pptraListened;
   }
   */
   ::bergedge::bergedge * ca::get_bergedge()
   {
      return m_papp->m_psession->m_pbergedge;
   }

   ::cube::cube * ca::get_cube()
   {
      return m_papp->m_psystem->m_pcube;
   }

   void ca::delete_this()
   {
      if(m_pfactoryitembase != ::null() && m_pfactoryitembase->m_pallocator)
      {

         m_pfactoryitembase->m_pallocator->discard(this);
      }
      else if(m_ulFlags & flag_discard_to_factory)
      {
         m_papp->m_psystem->discard_to_factory(this);
      }
//      else if(m_ulFlags & flag_heap_alloc)
      else
      {
         delete this;
      }
   }

   sp(::ca::ca) ca::clone()
   {
      if(m_pfactoryitembase != ::null())
         return m_pfactoryitembase->clone(this);
      else
         return m_papp->m_psystem->clone(this);
   }


/*   ptra * ca::new_ptra()
   {
      return new ::ca::ptra();
   }*/



} // namespace ca


