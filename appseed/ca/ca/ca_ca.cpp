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
      m_pplanebergedge          = NULL;
      m_pplanesystem            = NULL;
      m_pptraListener      = NULL;
      m_pptraListened      = NULL;
      m_pfactoryitembase   = NULL;
   }

   ca::ca(const ca & o)
   {
      m_ulFlags            = o.m_ulFlags;
      m_papp               = o.m_papp;
      m_countReference     = 1; // avoid creating a "perambulator" phantom  
      m_pplanebergedge          = o.m_pplanebergedge;
      m_pplanesystem            = o.m_pplanesystem;
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
            m_pplanebergedge          = papp->m_pplanebergedge;
         }
         catch(...)
         {
         }
         try
         {
            m_pplanesystem            = papp->m_pplanesystem;
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


