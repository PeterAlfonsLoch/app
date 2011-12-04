#include "StdAfx.h"

namespace ca
{

   const char ca::g_szCarlosGustavoCecynLundgren[] = CarlosGustavoCecynLundgren;
   const char ca::g_szCamiloSasukeTsumanuma[] = CamiloSasukeTsumanuma;
   const char ca::g_szCarlosgustavocecynlundgren[] = carlosgustavocecynlundgren;
   const char ca::g_szCamilosasuketsumanuma[] = camilosasuketsumanuma;
   const char ca::g_szKaarurosu[] = kaarurosu;
   const char ca::g_szKamiiro[] = kamiiro;
   const char ca::g_szZack[] = zack;
   const char ca::g_szCa[] = car;

   ca::ca()
   {
      m_ulFlags            = (unsigned long) flag_auto_clean;
      m_papp               = 0; // NULL
      m_countReference     = 1; // avoid creating a "perambulator" phantom
      m_pbergedge          = NULL;
      m_psystem            = NULL;
      m_pptraListener      = NULL;
      m_pptraListened      = NULL;
      m_pfactoryitembase   = NULL;
   }

   ca::ca(const ca & o)
   {
      m_ulFlags            = o.m_ulFlags;
      m_papp               = o.m_papp;
      m_countReference     = 1; // avoid creating a "perambulator" phantom  
      m_pbergedge          = o.m_pbergedge;
      m_psystem            = o.m_psystem;
      m_pptraListener      = NULL;
      m_pptraListened      = NULL;
      m_pfactoryitembase   = NULL;
   }

   ca::ca(::ca::application * papp)
   {
      m_ulFlags            = (unsigned long) flag_auto_clean;
      m_papp               = papp;
      m_countReference     = 1; // avoid creating a "perambulator" phantom
      if(papp != NULL)
      {
         try
         {
            m_pbergedge          = papp->m_pbergedge;
         }
         catch(...)
         {
         }
         try
         {
            m_psystem            = papp->m_psystem;
         }
         catch(...)
         {
         }
      }
      m_pptraListener      = NULL;
      m_pptraListened      = NULL;
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
   }

   void ca::on_delete(::ca::ca * pca)
   {
   }

   ::ca::ca * ca::clone()
   {
      return NULL;
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

} // namespace ca


