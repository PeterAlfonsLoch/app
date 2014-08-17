#include "framework.h"


namespace sockets
{


   sockets::sockets(sp(::base::application) papp) :
      element(papp),
      ::base::departament(papp),
      m_mutexHttpPostBoundary(papp),
      m_mutexResolvCache(papp)
   {

      m_pajpbasesocketinit    = NULL;

   }


   bool sockets::initialize1()
   {
      if(Application.is_system())
      {

/*            ::sockets::SSLInitializer ssl_init(m_psystem);*/

         //System.factory().creatable_small < ::http::memory_file > ();
         //System.factory().cloneable_large < ::sockets::winrt_address  >  (System.template type_info < ::net::address_base > ());
/*            System.factory().cloneable_small < ::sockets::ipv4_address > ();
         System.factory().cloneable_small < ::sockets::ipv6_address > ();*/

         m_pajpbasesocketinit = new AjpBaseSocket::Initializer;
      }

      m_countHttpPostBoundary = 0;

      return true;

   }

   bool sockets::finalize()
   {

      bool bOk = true;

      if(Application.is_system())
      {
         if(m_pajpbasesocketinit != NULL)
         {
            delete m_pajpbasesocketinit;
            m_pajpbasesocketinit = NULL;
         }
      }

      return bOk;

   }


   void sockets::http_config_proxy(const char * pszUrl, http_tunnel * psocket)
   {
      UNREFERENCED_PARAMETER(pszUrl);
      //UNREFERENCED_PARAMETER(psocket);
      //throw not_implemented(get_app());
      psocket->m_bDirect = true;
   }


} // namespace kar


