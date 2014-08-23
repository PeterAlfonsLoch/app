#include "framework.h"

namespace fontopus
{

   licensing::licensing(sp(::aura::application) papp) :
      element(papp)
   {
   }

   licensing::~licensing()
   {
   }

   bool licensing::has(const char * pszId, bool bInteractive)
   {
      class info info;
      if(m_mapInfo.Lookup(pszId, info))
      {
         return info.m_bLicensed;
      }
      else
      {
         return check(pszId, bInteractive);
      }
   }

   bool licensing::check(const char * pszId, bool bInteractive)
   {

      class info info;
      m_mapInfo.Lookup(pszId, info);
      info.m_strId = pszId;

      bool bLicensed = false;

      //if(m_pauraapp != NULL && m_pauraapp->m_pbasesession != NULL)
      //{
        // bLicensed = Session.m_pfontopus->check_license(pszId, bInteractive);
      //}
      //else
      {
         bLicensed = Session.m_pfontopus->check_license(pszId, bInteractive);
      }

      info.m_bLicensed = bLicensed;
      m_mapInfo.set_at(pszId, info);
      return info.m_bLicensed;

   }

   ::count licensing::clear_all_cache()
   {
      ::count count = m_mapInfo.get_count();
      m_mapInfo.remove_all();
      return count;
   }

   bool licensing::clear_cache(const char * pszId)
   {
      return m_mapInfo.remove_key(pszId) != FALSE;
   }


} // namespace fontopus



