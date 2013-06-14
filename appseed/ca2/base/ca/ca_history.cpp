#include "framework.h"

namespace ca2
{

   history::history()
   {
      m_phistory = NULL;
   }
   
   history::history(sp(::ca2::application) papp) :
      ca2(papp)
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

} // namespace ca2


