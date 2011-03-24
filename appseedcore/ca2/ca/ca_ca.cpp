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
   }

   ca::ca(const ca & o)
   {
      m_ulFlags            = o.m_ulFlags;
      m_papp               = o.m_papp;
      m_countReference     = 1; // avoid creating a "perambulator" phantom  
   }

   ca::ca(::ca::application * papp)
   {
      m_ulFlags            = (unsigned long) flag_auto_clean;
      m_papp               = papp;
      m_countReference     = 1; // avoid creating a "perambulator" phantom
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
         if(m_papp->m_psystem != NULL)
         {
            try
            {
               m_papp->m_psystem->on_delete(this);
            }
            catch(...)
            {
            }
         }
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

   void ca::delete_this()
   {
      if(is_set(flag_discard_to_factory))
      {
         System.factory().discard(this);
      }
      else
      {
         delete this;
      }
   }

   void ca::on_delete(::ca::ca * pca)
   {
   }

   ::ca::ca * ca::clone()
   {
      return System.clone(this);
   }

} // namespace ca