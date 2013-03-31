#include "framework.h"


namespace ca
{




   ca::ca()
   {
      m_ulFlags            = (uint32_t) flag_auto_clean;
      m_papp               = 0; // NULL
      //m_countReference     = 1; // avoid creating a "perambulator" phantom
      m_countReference     = 0; // do create a "perambulator" phantom, add_ref to "instantiate"
      m_pptraListener      = NULL;
      m_pptraListened      = NULL;
      m_pfactoryitembase   = NULL;
   }

   ca::ca(const ca & o)
   {
      m_ulFlags            = o.m_ulFlags;
      m_papp               = o.m_papp;
      //m_countReference     = 1; // avoid creating a "perambulator" phantom  
      m_countReference     = 0; // do create a "perambulator" phantom, add_ref to "instantiate"
      m_pptraListener      = NULL;
      m_pptraListened      = NULL;
      m_pfactoryitembase   = NULL;
   }

   ca::ca(::ca::application * papp)
   {
      m_ulFlags            = (uint32_t) flag_auto_clean;
      m_papp               = papp;
      m_countReference     = 1; // avoid creating a "perambulator" phantom
      m_pptraListener      = NULL;
      m_pptraListened      = NULL;
      m_pfactoryitembase   = NULL;
   }

   ca::~ca()
   {
      if(m_papp != NULL)
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
            if(m_papp->m_psystem != NULL)
            {
                  m_papp->m_psystem->on_delete(this);
            }
         }
         catch(...)
         {
         }
      }

      if(m_pptraListener != NULL)
      {
         for(int32_t i = 0; i < m_pptraListener->get_size(); i++)
         {
            ::ca::ca * plistener = m_pptraListener->element_at(i);
            if(plistener != NULL)
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
                  if(plistener->m_pptraListened != NULL)
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
         m_pptraListener = NULL;
      }
      if(m_pptraListened != NULL)
      {
         for(int32_t i = 0; i < m_pptraListened->get_size(); i++)
         {
            ::ca::ca * plistened = m_pptraListened->element_at(i);
            if(plistened != NULL)
            {
               try
               {
                  if(plistened->m_pptraListener != NULL)
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
         m_pptraListened = NULL;
      }


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

   void ca::on_delete(::ca::ca * pca)
   {
   }

   ptra & ca::listenerptra()
   {
      if(m_pptraListener == NULL)
      {
         m_pptraListener = new_ptra();
      }
      return *m_pptraListener;
   }
   
   ptra & ca::listenedptra()
   {
      if(m_pptraListened == NULL)
      {
         m_pptraListened = new_ptra();
      }
      return *m_pptraListened;
   }

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
      if(m_pfactoryitembase != NULL && m_pfactoryitembase->m_pallocator)
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

   ::ca::ca * ca::clone()
   {
      if(m_pfactoryitembase != NULL)
         return m_pfactoryitembase->clone(this);
      else
         return m_papp->m_psystem->clone(this);
   }


   ptra * ca::new_ptra()
   {
      return new ptra();
   }



} // namespace ca


