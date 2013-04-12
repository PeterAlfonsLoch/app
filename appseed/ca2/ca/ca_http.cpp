#include "framework.h"


namespace ca
{
   
   namespace http
   {
         
      signal::signal()
      {
         m_pcookies     = ::null();
         m_puser        = ::null();
         m_estatusRet   = status_unchanged;
      }

   }

} // namespace ca
