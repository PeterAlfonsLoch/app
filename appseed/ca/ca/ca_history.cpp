#include "framework.h"

namespace ca
{

   history::history()
   {
      m_phistory = ::null();
   }
   
   history::history(::ca::application * papp) :
      ca(papp)
   {
      m_phistory = ::null();
   }
         
   
   bool history::hist(const char * psz)
   {
      if(m_phistory != ::null())
      {
         return m_phistory->hist(psz);
      }
      return false;
   }

} // namespace ca


