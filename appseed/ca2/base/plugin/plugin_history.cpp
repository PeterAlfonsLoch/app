#include "framework.h"


namespace plugin
{

   history::history(sp(::ca2::application) papp, plugin * pplugin) :
      ca2(papp),
      ::ca2::history(papp),
      m_pplugin(pplugin)
   {
   }
         
   
   bool history::hist(const char * pszUrl)
   {
      if(m_pplugin != NULL)
      {
         m_pplugin->open_url(pszUrl);
         return true;
      }
      return false;
   }

} // namespace plugin