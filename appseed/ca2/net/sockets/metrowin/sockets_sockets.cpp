#include "framework.h"


namespace sockets
{


   sockets::sockets(sp(::ca::application) papp) :
      ca(papp),
      ::ca::section(papp),
      m_mutexHttpPostBoundary(papp),
      m_mutexResolvCache(papp)
   {

      m_pajpbasesocketinit    = NULL;

   }


   bool sockets::initialize1()
   {
      if(App(dynamic_cast < ::ca::application * >(this)).is_system())
      {

/*            ::sockets::SSLInitializer ssl_init(m_psystem);*/

         System.factory().creatable_small < ::http::memory_file > ();
/*            System.factory().cloneable_small < ::sockets::ipv4_address > ();
         System.factory().cloneable_small < ::sockets::ipv6_address > ();*/

         m_pajpbasesocketinit = new AjpBaseSocket::Initializer;
      }

      m_countHttpPostBoundary = 0;
   }

   bool sockets::finalize()
   {

      if(Application.is_system())
      {
         if(m_pajpbasesocketinit != NULL)
         {
            delete m_pajpbasesocketinit;
            m_pajpbasesocketinit = NULL;
         }
      }

   }


   void sockets::http_config_proxy(const char * pszUrl, http_tunnel * psocket)
   {
      UNREFERENCED_PARAMETER(pszUrl);
      UNREFERENCED_PARAMETER(psocket);
      throw not_implemented(get_app());
   }


} // namespace kar


