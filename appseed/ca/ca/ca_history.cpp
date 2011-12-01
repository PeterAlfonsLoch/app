#include "StdAfx.h"

namespace ca
{

   history::history()
   {
      m_phistory = NULL;
   }
   
   history::history(::ca::application * papp) :
      ca(papp)
   {
      m_phistory = NULL;
   }
         
   
   bool history::hist(const char * psz)
   {
      if(m_phistory != NULL)
      {
         return m_phistory->hist(psz);
      }
      return false;
   }

} // namespace ca


