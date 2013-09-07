#include "framework.h"


namespace core
{
   
   namespace http
   {
         
      signal::signal()
      {
         m_pcookies     = NULL;
         m_puser        = NULL;
         m_estatusRet   = status_unchanged;
      }

   }

} // namespace core
