#include "framework.h"


namespace plugin
{

   history::history(::ca::application * papp, plugin * pplugin) :
      ca(papp),
      ::ca::history(papp),
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